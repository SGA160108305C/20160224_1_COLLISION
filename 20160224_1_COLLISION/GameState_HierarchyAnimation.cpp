#include "stdafx.h"
#include "GameState_HierarchyAnimation.h"


GameState_HierarchyAnimation::GameState_HierarchyAnimation()
{
}


GameState_HierarchyAnimation::~GameState_HierarchyAnimation()
{
}

void GameState_HierarchyAnimation::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}
	if ( cubeMan == nullptr )
	{
		cubeMan = new CubeMan;
		cubeMan->Initialize();
	}
	Reset();
}

void GameState_HierarchyAnimation::Destroy()
{
	SAFE_DELETE(grid);
	SAFE_DELETE(cubeMan);
}

void GameState_HierarchyAnimation::Reset()
{
}

void GameState_HierarchyAnimation::Update()
{
	if ( cubeMan )
	{
		cubeMan->Update();
	}
}

void GameState_HierarchyAnimation::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( cubeMan )
	{
		cubeMan->Render();
	}

	RECT rc = { 10, RESOLUTION_Y - 55, 11, 11 };
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_HierarchyAnimation", strlen("GameState_HierarchyAnimation"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_HierarchyAnimation::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(30.0f);
	Initialize();
	GameManager::GetCamera()->SetLookTarget(cubeMan->GetPositionAdress());
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
}

void GameState_HierarchyAnimation::OnLeaveState()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	Destroy();
}

LRESULT GameState_HierarchyAnimation::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && cubeMan )
	{
		cubeMan->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
