#include "stdafx.h"
#include "GameState_Light.h"


GameState_Light::GameState_Light()
{
	ZeroMemory(walls, sizeof(Cube_Material*) * WALL_COUNT);
}


GameState_Light::~GameState_Light()
{
}

void GameState_Light::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
		grid->SetShowArrow(true);
	}
	if ( cubeMan == nullptr )
	{
		cubeMan = new CubeMan_Light;
		cubeMan->Initialize();
	}
	D3DXVECTOR3 size = D3DXVECTOR3(0,0,0);
	for ( int i = 0; i < WALL_COUNT; ++i )
	{
		walls[i] = new Cube_Material;		
	}
	size = D3DXVECTOR3(15,5,1);
	walls[0]->Initialize(size, D3DXVECTOR3(0, 0, 15));
	walls[1]->Initialize(size, D3DXVECTOR3(0, 0, -15));
	size = D3DXVECTOR3(1, 5, 15);
	walls[2]->Initialize(size, D3DXVECTOR3(15, 0, 0));
	walls[3]->Initialize(size, D3DXVECTOR3(-15, 0, 0));
	Reset();
}

void GameState_Light::Destroy()
{
	for ( int i = 0; i < WALL_COUNT; ++i )
	{
		SAFE_DELETE(walls[i]);
	}
	SAFE_DELETE(grid);
	SAFE_DELETE(cubeMan);
}

void GameState_Light::Reset()
{
}

void GameState_Light::Update()
{
	if ( cubeMan )
	{
		cubeMan->Update();
	}
}

void GameState_Light::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	for ( int i = 0; i < WALL_COUNT; ++i )
	{
		if ( walls[i] )
		{
			walls[i]->Render();
		}		 
	}
	if ( cubeMan )
	{
		cubeMan->Render();
	}

	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_Light", strlen("GameState_Light"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_Light::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(30.0f);
	Initialize();
	if ( cubeMan )
	{
		GameManager::GetCamera()->SetLookTarget(cubeMan->GetPositionAdress());
	}

	D3DLIGHT9 mainLight;
	GameManager::GetDevice()->GetLight(0, &oldMainLight);
	memcpy_s(&mainLight, sizeof(D3DLIGHT9), &oldMainLight, sizeof(D3DLIGHT9));
	mainLight.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	mainLight.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	GameManager::GetDevice()->SetLight(0, &mainLight);
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
}

void GameState_Light::OnLeaveState()
{
	GameManager::GetDevice()->SetLight(0, &oldMainLight);
	Destroy();
}

LRESULT GameState_Light::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && cubeMan )
	{
		cubeMan->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
