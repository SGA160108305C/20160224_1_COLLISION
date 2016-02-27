#include "stdafx.h"
#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}
 
bool Collision::IsSphereToSphere(BoundingShere& sphere1, BoundingShere& sphere2)
{
	bool result = false;
	D3DXVECTOR3 dv = sphere1.center - sphere2.center;
	float d = D3DXVec3LengthSq(&dv);
	float rSum = (sphere1.radius + sphere2.radius)*(sphere1.radius + sphere2.radius);

	if (d <= rSum)
	{
		result = true;
	}

	return result;
}

bool Collision::IsBoxToSphere(BoundingBox& aabb, BoundingShere& sphere)
{
	float distance = 0.0f;
	float diff = 0.0f;
	if (sphere.center.x < aabb.min.x)
	{
		diff = aabb.min.x - sphere.center.x;
		distance += (diff * diff);
	}
	else if (sphere.center.x > aabb.max.x)
	{
		diff = sphere.center.x - aabb.max.x;
		distance += (diff * diff);
	}

	if (sphere.center.y < aabb.min.y)
	{
		diff = aabb.min.y - sphere.center.y;
		distance += (diff * diff);
	}
	else if (sphere.center.y > aabb.max.y)
	{
		diff = sphere.center.y - aabb.max.y;
		distance += (diff * diff);
	}

	if (sphere.center.z < aabb.min.z)
	{
		diff = aabb.min.z - sphere.center.z;
		distance += (diff * diff);
	}
	else if (sphere.center.z > aabb.max.z)
	{
		diff = sphere.center.z - aabb.max.z;
		distance += (diff * diff);
	}

	if (distance > (sphere.radius * sphere.radius))
	{
		return false;
	}

	return true;
}

bool Collision::IsBoxToBox(BoundingBox& aabb1, BoundingBox& aabb2)
{
	if (aabb1.max.x < aabb2.min.x || aabb1.min.x > aabb2.max.x)
		return false;

	if (aabb1.max.y < aabb2.min.y || aabb1.min.y > aabb2.max.y)
		return false;

	if (aabb1.max.z < aabb2.min.z || aabb1.min.z > aabb2.max.z)
		return false;

	return true;
}