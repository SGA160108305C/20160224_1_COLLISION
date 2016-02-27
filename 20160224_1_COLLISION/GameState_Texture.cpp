#include "stdafx.h"
#include "GameState_Texture.h"


GameState_Texture::GameState_Texture()
{
}


GameState_Texture::~GameState_Texture()
{
}

void GameState_Texture::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}
	if ( cube == nullptr )
	{
		cube = new Cube_Textured;
		cube->Initialize();
	}
	Reset();
}

void GameState_Texture::Destroy()
{
	SAFE_DELETE(grid);
	SAFE_DELETE(cube);
}

void GameState_Texture::Reset()
{
	if ( cube )
	{
		cube->Reset();
	}
}

void GameState_Texture::Update()
{
	if ( cube )
	{
		cube->Update();
	}
}

void GameState_Texture::Render()
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
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_Texture", strlen("GameState_Texture"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_Texture::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(30.0f);
	Initialize();
	GameManager::GetCamera()->SetLookTarget(cube->GetPositionAdress());
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
}

void GameState_Texture::OnLeaveState()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	Destroy();
}

LRESULT GameState_Texture::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && cube )
	{
		cube->CubeInputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
