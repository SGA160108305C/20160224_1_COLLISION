#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
{
}


Cube::~Cube()
{
	Destroy();
}

void Cube::Initialize()
{
	rotationAxisX = 0.0f;
	rotationAxisY = 0.0f;

	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vertex[1] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vertex[2] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vertex[3] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vertex[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vertex[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vertex[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vertex[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 0);
	
	triangles[0] = Triangle(vertex[0], vertex[1], vertex[2], color);
	triangles[1] = Triangle(vertex[0], vertex[2], vertex[3], color);
	triangles[2] = Triangle(vertex[4], vertex[5], vertex[1], color);
	triangles[3] = Triangle(vertex[4], vertex[1], vertex[0], color);
	triangles[4] = Triangle(vertex[7], vertex[6], vertex[5], color);
	triangles[5] = Triangle(vertex[7], vertex[5], vertex[4], color);
	triangles[6] = Triangle(vertex[3], vertex[2], vertex[6], color);
	triangles[7] = Triangle(vertex[3], vertex[6], vertex[7], color);
	triangles[8] = Triangle(vertex[1], vertex[5], vertex[6], color);
	triangles[9] = Triangle(vertex[1], vertex[6], vertex[2], color);
	triangles[10] = Triangle(vertex[4], vertex[0], vertex[3], color);
	triangles[11] = Triangle(vertex[4], vertex[3], vertex[7], color);
}

void Cube::Destroy()
{

}

void Cube::Update()
{	
	float tick = (float)GameManager::GetTick();
	jumpTime += tick;

	if ((GetAsyncKeyState('A') & 0x8000) != 0)
	{
		rotationAxisY -= (rotationSpeed * tick);
	}
	else if ((GetAsyncKeyState('D') & 0x8000) != 0)
	{
		rotationAxisY += (rotationSpeed * tick);
	}
	if ((GetAsyncKeyState('W') & 0x8000) != 0)
	{
		position += (direction * moveSpeed * tick);
	}
	else if ((GetAsyncKeyState('S') & 0x8000) != 0)
	{
		position -= (direction * moveSpeed * tick);
	}
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0 && isJumping == false )
	{
		isJumping = true;
		jumpTime = 0.0f;
	}

	D3DXMATRIX rotX, rotY, move;
	D3DXMatrixRotationX(&rotX, rotationAxisX);
	D3DXMatrixRotationY(&rotY, rotationAxisY);
		
	world = rotX * rotY;

	D3DXVECTOR3 baseDirection(0, 0, 1);
	D3DXVec3TransformCoord(&direction, &baseDirection, &world);

	if (isJumping)
	{
		position.y = jumpPower * jumpTime - 4.9f/*0.5f * ( 9.8f ) */* jumpTime * jumpTime;
		if (position.y < 0.0)
		{
			isJumping = false;
			position.y = 0.0f;
		}
	}

	D3DXMatrixTranslation(&move, position.x, position.y, position.z);
	world *= move;
}

void Cube::Render()
{
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionColor::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		TRIANGLE_COUNT,
		&triangles[0],
		sizeof(FVF_PositionColor));
}

LRESULT Cube::CubeInputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		mouseLDown = true;
		mouseStart.x = GET_X_LPARAM(lParam);
		mouseStart.y = GET_Y_LPARAM(lParam);
		result = WM_LBUTTONDOWN;
	}
	break;
	case WM_LBUTTONUP:
	{
		mouseLDown = false;
		result = WM_LBUTTONUP;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (mouseLDown)
		{
			POINT mouseCurrent;
			mouseCurrent.x = GET_X_LPARAM(lParam);
			mouseCurrent.y = GET_Y_LPARAM(lParam);

			int deltaX = mouseCurrent.x - mouseStart.x;
			int deltaY = mouseCurrent.y - mouseStart.y;

			Spin(deltaX / 100.f, deltaY / 100.f);

			mouseStart = mouseCurrent;
			result = WM_MOUSEMOVE;
		}
	}
	break;
	}
	return result;
}

void Cube::Spin(float x, float y)
{
	rotationAxisY -= x;
	rotationAxisX -= y;
}

void Cube::Reset()
{
	rotationAxisX = 0.0f;
	rotationAxisY = 0.0f;

	position = D3DXVECTOR3(0, 0, 0);
	direction = D3DXVECTOR3(0, 0, 1);

	mouseLDown = false;
}