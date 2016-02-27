#pragma once
#include "BoundingVolume.h"

class Collision
{
public:
	Collision();
	~Collision();

	static bool IsSphereToSphere(BoundingShere& sphere1, BoundingShere& sphere2);
	static bool IsBoxToSphere(BoundingBox& aabb, BoundingShere& sphere);
	static bool IsBoxToBox(BoundingBox& aabb1, BoundingBox& aabb2);
};

