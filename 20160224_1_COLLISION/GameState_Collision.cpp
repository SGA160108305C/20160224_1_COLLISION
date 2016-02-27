#include "stdafx.h"
#include "GameState_Collision.h"
#include "Collision.h"


GameState_Collision::GameState_Collision()
{
}


GameState_Collision::~GameState_Collision()
{
}

void GameState_Collision::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
		grid->SetShowArrow(true);
	}	
	if ( girl == nullptr )
	{
		girl = new Character_Collision;
		girl->Initialize();		
	}

	Collider_Box* box = nullptr;
	box = new Collider_Box;
	box->Initialize(D3DXVECTOR3(-1.0f, 0.0f, -1.0f), D3DXVECTOR3(1.0f, 2.0f, 1.0f));
	box->SetPosition(D3DXVECTOR3(5,0,5));
	box->Update();
	boxList.push_back(box);
	box = new Collider_Box;
	box->Initialize(D3DXVECTOR3(-1.0f, 0.0f, -1.0f), D3DXVECTOR3(1.0f, 2.0f, 1.0f));
	box->SetPosition(D3DXVECTOR3(-5, 0, 5));
	box->Update();
	boxList.push_back(box);

	Collider_Sphere* sphere = nullptr;
	sphere = new Collider_Sphere;
	sphere->Initialize(D3DXVECTOR3(3, 1, -3), 1.0f);
	sphere->Update();
	sphereList.push_back(sphere);
	sphere = new Collider_Sphere;
	sphere->Initialize(D3DXVECTOR3(-3, 1, -3), 1.0f);
	sphere->Update();
	sphereList.push_back(sphere);

	Reset();
}

void GameState_Collision::Destroy()
{	
	for ( auto iter = boxList.begin(); iter != boxList.end(); ++iter )
	{
		SAFE_DELETE(*iter);
	}
	boxList.clear();
	for ( auto iter = sphereList.begin(); iter != sphereList.end(); ++iter )
	{
		SAFE_DELETE(*iter);
	}
	sphereList.clear();

	SAFE_DELETE(girl);
	SAFE_DELETE(grid);	
}

void GameState_Collision::Reset()
{
}

void GameState_Collision::Update()
{
	if ( girl )
	{
		girl->Update();
	}
	bool isCollisioin = false;
	for (auto iter = boxList.cbegin(); iter != boxList.cend() ; ++iter)
	{		
		if (girl->GetBoundingVolumeType() == BoundingVolumeType::BOUNDING_SPHERE)
		{
			isCollisioin = Collision::IsBoxToSphere((*iter)->GetBoundingBox(), girl->GetBoundingSphere());
		}
		else if (girl->GetBoundingVolumeType() == BoundingVolumeType::BOUNDING_AABB)
		{
			isCollisioin = Collision::IsBoxToBox(girl->GetBoundingBox(), (*iter)->GetBoundingBox());			
		}		
		if (isCollisioin == true)
		{
			( *iter )->SetMaterialColor(D3DXCOLOR(0.f, 0.8f, 0.f, 1.0f));
			break;
		}
		else
		{
			( *iter )->SetMaterialColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
		}
	}
	if (isCollisioin == false)
	{
		for (auto iter = sphereList.cbegin(); iter != sphereList.cend(); ++iter)
		{
			if (girl->GetBoundingVolumeType() == BoundingVolumeType::BOUNDING_SPHERE)
			{
				isCollisioin = Collision::IsSphereToSphere(girl->GetBoundingSphere(), (*iter)->GetBoundingSphere());

			}
			else if (girl->GetBoundingVolumeType() == BoundingVolumeType::BOUNDING_AABB)
			{
				isCollisioin = Collision::IsBoxToSphere(girl->GetBoundingBox(), (*iter)->GetBoundingSphere());
			}
			if (isCollisioin == true)
			{
				( *iter )->SetMaterialColor(D3DXCOLOR(0.8f, 0.f, 0.f, 1.0f));
				break;
			}
			else
			{
				( *iter )->SetMaterialColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
			}
		}
	}
	girl->SetCollision(isCollisioin);
}

void GameState_Collision::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( girl )
	{
		girl->Render();
	}
	for ( auto iter = boxList.cbegin(); iter != boxList.cend(); ++iter )
	{
		( *iter )->Render();
	}
	for ( auto iter = sphereList.cbegin(); iter != sphereList.cend(); ++iter )
	{
		( *iter )->Render();
	}

	

	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_Collision", strlen("GameState_Collision"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_Collision::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
}

void GameState_Collision::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_Collision::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
