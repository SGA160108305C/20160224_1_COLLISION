#pragma once
#include "FVF.h"
#include "Triangle.h"
#include "GameObject.h"

class Cube_Textured : public GameObject
{
public:
	Cube_Textured();
	~Cube_Textured();

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

	TextureTriangle triangles[TRIANGLE_COUNT];

	D3DXMATRIXA16 world;

	bool mouseLDown = false;
	POINT mouseStart;

	float moveSpeed = 10.0f;
	float rotationSpeed = 3.0f;


	float jumpPower = 10.0f;
	float jumpTime = 0.0f;
	bool isJumping = false;

	void Spin(float x, float y);

	LPDIRECT3DTEXTURE9 texture = nullptr;
};

