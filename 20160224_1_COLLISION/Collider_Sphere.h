#pragma once
#include "BoundingVolume.h"

class Collider_Sphere
{
public:
	Collider_Sphere();
	~Collider_Sphere();

	void Initialize(D3DXVECTOR3& center, float radius, D3DXMATRIXA16* _parent = nullptr);
	void Destroy();
	void Update();
	void Render();

	inline void SetWireRender(bool wire){ wireMode = wire; }
	inline BoundingShere& GetBoundingSphere(){ return boundingSphere; }

	inline void SetMaterialColor(D3DXCOLOR& color){ material.Ambient = color; material.Diffuse = color; }

protected:
	BoundingShere boundingSphere = BoundingShere(D3DXVECTOR3(0, 0, 0), 1.0f);
	LPD3DXMESH sphereMesh = nullptr;

	D3DXMATRIXA16 world;
	D3DXMATRIXA16* parent = nullptr;

	bool wireMode = false;

	D3DMATERIAL9 material;
};

