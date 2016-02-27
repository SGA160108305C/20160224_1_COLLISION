#pragma once
#include "GameState.h"
#include "Grid.h"
#include "Cube_Textured.h"

class GameState_Texture :
	public GameState
{
public:
	GameState_Texture();
	virtual ~GameState_Texture();

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
	Cube_Textured* cube = nullptr;
};

