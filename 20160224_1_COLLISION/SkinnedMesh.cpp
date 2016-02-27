#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"


SkinnedMesh::SkinnedMesh()
{
}


SkinnedMesh::~SkinnedMesh()
{
	SAFE_RELEASE(animController);
}


SkinnedMesh::SkinnedMesh(char* path, char* fileName)
{
	SkinnedMesh* skinnedMesh = SkinnedMeshManager::Get().GetSkinnedMesh(path, fileName);

	rootFrame = skinnedMesh->rootFrame;
	workingPaletteSize = skinnedMesh->workingPaletteSize;
	workingPalette = skinnedMesh->workingPalette;
	effect = skinnedMesh->effect;
	boundingSphere = skinnedMesh->boundingSphere;

	skinnedMesh->animController->CloneAnimationController(
		skinnedMesh->animController->GetMaxNumAnimationOutputs(),
		skinnedMesh->animController->GetMaxNumAnimationSets(),
		skinnedMesh->animController->GetMaxNumTracks(),
		skinnedMesh->animController->GetMaxNumEvents(),
		&animController);
}

void SkinnedMesh::Load(char* path, char* fileName)
{
	effect = LoadEffect("MultiAnimation.hpp");

	int paletteSize = 0;
	effect->GetInt("MATRIX_PALETTE_SIZE", &paletteSize);

	AllocateHierarchy ah;
	ah.SetDirectory(path);
	ah.SetDefaultPaletteSize(paletteSize);

	boundingSphere.center = ( ah.GetMin() + ah.GetMax() ) / 2.0f;
	boundingSphere.radius = D3DXVec3Length(&( ah.GetMin() - ah.GetMax() ));

	char fullPath[512];
	strcpy_s(fullPath, path);
	strcat_s(fullPath, fileName);
	HRESULT result = D3DXLoadMeshHierarchyFromXA(
		fullPath,
		D3DXMESH_MANAGED,
		GameManager::GetDevice(),
		&ah,
		NULL,
		(LPD3DXFRAME*)&rootFrame,
		&animController);

	if ( workingPalette )
		delete[] workingPalette;

	workingPaletteSize = ah.GetMaxPaletteSize();
	workingPalette = new D3DXMATRIX[workingPaletteSize];
	if ( workingPalette == NULL )
	{
		workingPaletteSize = 0;
	}

	if ( rootFrame )
		SetupBoneMatrixPointers(rootFrame);
}

void SkinnedMesh::UpdateAndRender()
{
	if ( animController )
	{
		animController->AdvanceTime(GameManager::GetTick(), NULL);
	}

	if ( rootFrame )
	{
		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, position.x, position.y, position.z);

		Update(rootFrame, &mat);
		Render(rootFrame);
	}
}

void SkinnedMesh::Render(Bone* bone /*= nullptr*/)
{
	assert(bone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 boneMatrixPointers에 연결한다.
	if ( bone->pMeshContainer )
	{
		BoneMesh* boneMesh = (BoneMesh*)bone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos =
			(LPD3DXBONECOMBINATION)( boneMesh->bufferBoneCombos->GetBufferPointer() );

		D3DXMATRIXA16 matViewProj, matView, matProj;
		GameManager::GetDevice()->GetTransform(D3DTS_VIEW, &matView);
		GameManager::GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		GameManager::GetDevice()->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for ( DWORD dwAttrib = 0; dwAttrib < boneMesh->numAttrGroups; ++dwAttrib )
		{
			// set each transform into the palette
			for ( DWORD dwPalEntry = 0; dwPalEntry < boneMesh->numPaletteEntries; ++dwPalEntry )
			{
				DWORD dwMatrixIndex = pBoneCombos[dwAttrib].BoneId[dwPalEntry];
				if ( dwMatrixIndex != UINT_MAX )
				{
					workingPalette[dwPalEntry] =
						boneMesh->boneOffsetMatrices[dwMatrixIndex] *
						( *boneMesh->boneMatrixPointers[dwMatrixIndex] );
				}
			}

			// set the matrix palette into the effect
			effect->SetMatrixArray("amPalette",
				workingPalette,
				boneMesh->numPaletteEntries);

			effect->SetMatrix("g_mViewProj", &matViewProj);
			effect->SetVector("vLightDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			effect->SetVector("vWorldLightPos", &D3DXVECTOR4(500.0f, 500.0f, 500.0f, 1.0f));
			effect->SetVector("vWorldCameraPos", &D3DXVECTOR4(vEye, 1.0f));
			effect->SetVector("vMaterialAmbient", &D3DXVECTOR4(0.53f, 0.53f, 0.53f, 0.53f));
			effect->SetVector("vMaterialDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			effect->SetTexture("g_txScene", boneMesh->textures[pBoneCombos[dwAttrib].AttribId]);

			// set the current number of bones; this tells the effect which shader to use
			effect->SetInt("CurNumBones", boneMesh->maxNumFaceInfls - 1);

			// set the technique we use to draw
			effect->SetTechnique("Skinning20");

			UINT uiPasses, uiPass;

			// run through each pass and draw
			effect->Begin(&uiPasses, 0);
			for ( uiPass = 0; uiPass < uiPasses; ++uiPass )
			{
				effect->BeginPass(uiPass);
				boneMesh->workingMesh->DrawSubset(dwAttrib);
				effect->EndPass();
			}
			effect->End();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if ( bone->pFrameSibling )
	{
		Render((Bone*)bone->pFrameSibling);
	}

	if ( bone->pFrameFirstChild )
	{
		Render((Bone*)bone->pFrameFirstChild);
	}
}

LPD3DXEFFECT SkinnedMesh::LoadEffect(char* fileName)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL, NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	GameManager::GetDevice()->GetDeviceCaps(&caps);
	if ( caps.VertexShaderVersion > D3DVS_VERSION(1, 1) )
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if ( FAILED(D3DXCreateEffectFromFileA(GameManager::GetDevice(),
		fileName,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)) )
	{
		// if creation fails, and debug information has been returned, output debug info
		if ( pBuffer )
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}

void SkinnedMesh::Update(Bone* current, D3DXMATRIXA16* parentMatrix)
{
	current->CombinedTransformationMatrix = current->TransformationMatrix;
	if ( parentMatrix )
	{
		current->CombinedTransformationMatrix =
			current->CombinedTransformationMatrix * ( *parentMatrix );
	}

	if ( current->pFrameSibling )
	{
		Update((Bone*)current->pFrameSibling, parentMatrix);
	}

	if ( current->pFrameFirstChild )
	{
		Update((Bone*)current->pFrameFirstChild, &( current->CombinedTransformationMatrix ));
	}
}

void SkinnedMesh::SetupBoneMatrixPointers(Bone* bone)
{
	assert(bone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 boneMatrixPointers에 연결한다.
	if ( bone->pMeshContainer )
	{
		BoneMesh* boneMesh = (BoneMesh*)bone->pMeshContainer;
		if ( boneMesh->pSkinInfo )
		{
			LPD3DXSKININFO pSkinInfo = boneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
			// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
			// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
			// 찾아서 월드매트릭스를 걸어줘라.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for ( DWORD i = 0; i < dwNumBones; ++i )
			{
				LPCSTR boneName = pSkinInfo->GetBoneName(i);
				if ( boneName == nullptr || strlen(boneName) == 0 )
					continue;
				Bone* influence = (Bone*)D3DXFrameFind(rootFrame, boneName);
				boneMesh->boneMatrixPointers[i] = &( influence->CombinedTransformationMatrix );
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if ( bone->pFrameSibling )
	{
		SetupBoneMatrixPointers((Bone*)bone->pFrameSibling);
	}

	if ( bone->pFrameFirstChild )
	{
		SetupBoneMatrixPointers((Bone*)bone->pFrameFirstChild);
	}
}

void SkinnedMesh::SetAnimationIndex(int nIndex)
{
	if ( !animController )
		return;
	LPD3DXANIMATIONSET animSet = NULL;
	animController->GetAnimationSet(nIndex, &animSet);
	animController->SetTrackAnimationSet(0, animSet);
	SAFE_RELEASE(animSet);
}

void SkinnedMesh::Destroy()
{
	AllocateHierarchy ah;
	D3DXFrameDestroy((LPD3DXFRAME)rootFrame, &ah);
	SAFE_DELETE_ARRAY_ONLY(workingPalette);
	SAFE_RELEASE(effect);
	SAFE_RELEASE(animController);
}

void SkinnedMesh::SetRandomTrackPosition()
{
	animController->SetTrackPosition(0, ( rand() % 100 ) / 10.0f);
}
