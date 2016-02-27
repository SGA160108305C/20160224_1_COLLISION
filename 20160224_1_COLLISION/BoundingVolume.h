#pragma once

enum BoundingVolumeType
{
	BOUNDING_SPHERE = 0,
	BOUNDING_AABB,
};

struct BoundingShere
{
	BoundingShere(){};
	BoundingShere(D3DXVECTOR3& _center, float _radius)
	{
		center = _center;
		radius = _radius;
	};

	float radius = 0.0f;
	D3DXVECTOR3 center = D3DXVECTOR3(0,0,0);	
};

struct BoundingBox
{
	BoundingBox(){};
	BoundingBox(D3DXVECTOR3& _min, D3DXVECTOR3& _max){ min = _min; max = _max; };

	bool IsPointIn(D3DXVECTOR3& point)
	{
		if ( point.x >= min.x && point.y >= min.y && point.z >= min.z &&
			point.x <= max.x && point.y <= max.y && point.z <= max.z )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	D3DXVECTOR3 min = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	D3DXVECTOR3 max = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
};