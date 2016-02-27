#include "stdafx.h"
#include "GameState_Actions.h"


GameState_Actions::GameState_Actions()
{
}


GameState_Actions::~GameState_Actions()
{
}

void GameState_Actions::Initialize()
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

		ActionSequence* sequence = new ActionSequence;

		ActionMove* move1 = new ActionMove;
		move1->SetStart(D3DXVECTOR3(0, 0, 0));
		move1->SetGoal(D3DXVECTOR3(0, 0, 15));
		move1->SetDuration(1.0f);
		move1->SetTarget(girl);
		move1->SetDelegate(sequence);
		sequence->AddAction(move1);

		ActionMove* move2 = new ActionMove;
		move2->SetStart(D3DXVECTOR3(0, 0, 15));
		move2->SetGoal(D3DXVECTOR3(-7, 0, 7));
		move2->SetDuration(1.0f);
		move2->SetTarget(girl);
		move2->SetDelegate(sequence);
		sequence->AddAction(move2);

		ActionMove* move3 = new ActionMove;
		move3->SetStart(D3DXVECTOR3(-7, 0, 7));
		move3->SetGoal(D3DXVECTOR3(-7, 0, -7));
		move3->SetDuration(1.0f);
		move3->SetTarget(girl);
		move3->SetDelegate(sequence);
		sequence->AddAction(move3);

		ActionMove* move4 = new ActionMove;
		move4->SetStart(D3DXVECTOR3(-7, 0, -7));
		move4->SetGoal(D3DXVECTOR3(0, 0, -15));
		move4->SetDuration(1.0f);
		move4->SetTarget(girl);
		move4->SetDelegate(sequence);
		sequence->AddAction(move4);

		ActionMove* move5 = new ActionMove;
		move5->SetStart(D3DXVECTOR3(0, 0, -15));
		move5->SetGoal(D3DXVECTOR3(7, 0, -7));
		move5->SetDuration(1.0f);
		move5->SetTarget(girl);
		move5->SetDelegate(sequence);
		sequence->AddAction(move5);

		ActionMove* move6 = new ActionMove;
		move6->SetStart(D3DXVECTOR3(7, 0, -7));
		move6->SetGoal(D3DXVECTOR3(7, 0, 7));
		move6->SetDuration(1.0f);
		move6->SetTarget(girl);
		move6->SetDelegate(sequence);
		sequence->AddAction(move6);

		ActionMove* move7 = new ActionMove;
		move7->SetStart(D3DXVECTOR3(7, 0, 7));
		move7->SetGoal(D3DXVECTOR3(0, 0, 15));
		move7->SetDuration(1.0f);
		move7->SetTarget(girl);
		move7->SetDelegate(sequence);
		sequence->AddAction(move7);

		girl->SetAction(sequence);
	}
	Reset();
}

void GameState_Actions::Destroy()
{	
	SAFE_DELETE(girl);
	SAFE_DELETE(grid);	
}

void GameState_Actions::Reset()
{
}

void GameState_Actions::Update()
{
	if ( girl )
	{
		girl->Update();
	}
}

void GameState_Actions::Render()
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
	UI_Manager::GetFont()->DrawTextA(NULL, "GameState_Actions", strlen("GameState_Actions"), &rc, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void GameState_Actions::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
}

void GameState_Actions::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_Actions::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
