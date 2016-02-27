#include "stdafx.h"
#include "GameState_DX_Base.h"


GameState_DX_Base::GameState_DX_Base()
{
}


GameState_DX_Base::~GameState_DX_Base()
{
}

void GameState_DX_Base::Initialize()
{
	Reset();
}

void GameState_DX_Base::Destroy()
{
}

void GameState_DX_Base::Reset()
{
}

void GameState_DX_Base::Update()
{
}

void GameState_DX_Base::Render()
{
	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_DX_Base", strlen("GameState_DX_Base"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_DX_Base::OnEnterState()
{
	Initialize();
}

void GameState_DX_Base::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_DX_Base::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
