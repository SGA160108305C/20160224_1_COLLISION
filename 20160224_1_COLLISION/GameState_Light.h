#pragma once
#include "GameState.h"
#include "Grid.h"
#include "CubeMan_Light.h"
#include "Cube_Material.h"

class GameState_Light :
	public GameState
{
public:
	GameState_Light();
	virtual ~GameState_Light();

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
	CubeMan_Light* cubeMan = nullptr;

	static const int WALL_COUNT = 4;
	Cube_Material* walls[WALL_COUNT];

	D3DLIGHT9 oldMainLight;
};

