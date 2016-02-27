#pragma once
#include <list>
#include "GameState.h"
#include "Grid.h"
#include "Character_Collision.h"

class GameState_Collision :
	public GameState
{
public:
	GameState_Collision();
	virtual ~GameState_Collision();

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
	Character_Collision* girl = nullptr;

	std::list<Collider_Box*> boxList;
	std::list<Collider_Sphere*> sphereList;
};

