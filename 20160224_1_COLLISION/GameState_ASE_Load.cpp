#include "stdafx.h"
#include "GameState_ASE_Load.h"


GameState_ASE_Load::GameState_ASE_Load()
{
}


GameState_ASE_Load::~GameState_ASE_Load()
{
}

void GameState_ASE_Load::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
		grid->SetShowArrow(true);
	}	
	if ( girl == nullptr )
	{
		girl = new Character;
		girl->Initialize();		
	}
	Reset();
}

void GameState_ASE_Load::Destroy()
{	
	SAFE_DELETE(girl);
	SAFE_DELETE(grid);	
}

void GameState_ASE_Load::Reset()
{
}

void GameState_ASE_Load::Update()
{
	if ( girl )
	{
		girl->Update();
	}
}

void GameState_ASE_Load::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( girl )
	{
		girl->Render();
	}

	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_ASE_Load", strlen("GameState_ASE_Load"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_ASE_Load::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
}

void GameState_ASE_Load::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_ASE_Load::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
