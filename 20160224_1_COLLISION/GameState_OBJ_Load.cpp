#include "stdafx.h"
#include "GameState_OBJ_Load.h"


GameState_OBJ_Load::GameState_OBJ_Load()
{
}


GameState_OBJ_Load::~GameState_OBJ_Load()
{
}

void GameState_OBJ_Load::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
		grid->SetShowArrow(true);
	}	
	if ( objBox == nullptr )
	{
		objBox = new Obj();
		objBox->Initialize("Box.obj");
		objBox->SetPosition(D3DXVECTOR3(10, 0, 10));
	}
	if ( objMap == nullptr )
	{
		objMap = new Obj();
		objMap->Initialize("map.obj", "map_surface.obj");		
	}
	Reset();
}

void GameState_OBJ_Load::Destroy()
{
	SAFE_DELETE(objMap);
	SAFE_DELETE(objBox);	
	SAFE_DELETE(grid);	
}

void GameState_OBJ_Load::Reset()
{
}

void GameState_OBJ_Load::Update()
{
	if ( objBox )
	{
		objBox->Update();
	}
}

void GameState_OBJ_Load::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( objMap )
	{
		objMap->Render();
	}
	if ( objBox )
	{
		objBox->Render();
	}

	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_OBJ_Load", strlen("GameState_OBJ_Load"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_OBJ_Load::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
}

void GameState_OBJ_Load::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_OBJ_Load::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
