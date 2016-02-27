#include "stdafx.h"
#include "ObjFileGroup.h"


ObjFileGroup::ObjFileGroup(MaterialTexture* _materialTexture, std::vector<FVF_PositionNormalTexture>& _vertex)
	:materialTexture(_materialTexture)
{
	if (materialTexture)
	{
		materialTexture->AddReference();
	}
	vertex = std::move(_vertex);
}


ObjFileGroup::~ObjFileGroup()
{
	SAFE_RELEASE(materialTexture);
}

void ObjFileGroup::Render()
{
	if ( materialTexture )
	{
		GameManager::GetDevice()->SetMaterial(&( materialTexture->material ));
		GameManager::GetDevice()->SetTexture(0, materialTexture->texture);
	}
	GameManager::GetDevice()->SetFVF(FVF_PositionNormalTexture::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		vertex.size() / 3,
		&vertex[0],
		sizeof(FVF_PositionNormalTexture));
}