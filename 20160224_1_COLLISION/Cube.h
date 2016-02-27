#pragma once
#include "FVF.h"
#include "Triangle.h"

class Cube
{
public:
	Cube();
	~Cube();

	void Initialize();
	void Destroy();
	void Render();
	void Update();

	void Reset();

	LRESULT CubeInputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	inline const LPD3DXVECTOR3 GetPositionAdress(){ return &position; }

protected:
	float rotationAxisX = 0.0f;
	float rotationAxisY = 0.0f;

	static const int TRIANGLE_COUNT = 12;

	Triangle triangles[TRIANGLE_COUNT];

	D3DXMATRIXA16 world;

	bool mouseLDown = false;
	POINT mouseStart;

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 direction = D3DXVECTOR3(0, 0, 1);
	float moveSpeed = 10.0f;
	float rotationSpeed = 3.0f;


	float jumpPower = 10.0f;
	float jumpTime = 0.0f;
	bool isJumping = false;

	void Spin(float x, float y);
};

