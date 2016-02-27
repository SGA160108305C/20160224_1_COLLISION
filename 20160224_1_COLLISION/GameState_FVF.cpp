

#include "stdafx.h"
#include "GameState_FVF.h"


GameState_FVF::GameState_FVF()
{
}


GameState_FVF::~GameState_FVF()
{
}

void GameState_FVF::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}
	if ( cube == nullptr )
	{
		cube = new Cube;
		cube->Initialize();
	}
	Reset();
}

void GameState_FVF::Destroy()
{
	SAFE_DELETE(grid);
	SAFE_DELETE(cube);
}

void GameState_FVF::Reset()
{
	if ( cube )
	{
		cube->Reset();
	}
}

void GameState_FVF::Update()
{
	if ( cube )
	{
		cube->Update();
	}
}

void GameState_FVF::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( cube )
	{
		cube->Render();
	}

	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_FVF", strlen("GameState_FVF"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_FVF::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
	GameManager::GetCamera()->SetLookTarget(cube->GetPositionAdress());
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
}

void GameState_FVF::OnLeaveState()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	Destroy();
}

LRESULT GameState_FVF::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && cube )
	{
		cube->CubeInputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
