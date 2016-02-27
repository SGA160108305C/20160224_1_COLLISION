#pragma once
#include "GameState.h"
#include "Grid.h"
#include "Cube.h"

class GameState_FVF :
	public GameState
{
public:
	GameState_FVF();
	virtual ~GameState_FVF();

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
	Cube* cube = nullptr;
};

