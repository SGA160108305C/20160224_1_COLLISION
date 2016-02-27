#pragma once
#include "GameState.h"
#include "Grid.h"
#include "Character.h"

class GameState_Actions :
	public GameState
{
public:
	GameState_Actions();
	virtual ~GameState_Actions();

	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Reset() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnEnterState() override;
	virtual void OnLeaveState() override;

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	Grid* grid = nullptr;
	Character* girl = nullptr;
};

