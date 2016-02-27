#pragma once
#include "BoundingVolume.h"

class FrustumCulling
{
public:
	FrustumCulling();
	~FrustumCulling();

	void Initialize();	
	void Update();
	bool IsInFrustum(BoundingShere* boundingSphere);
	
private:
	std::vector<D3DXVECTOR3> projectionSpacePointArray;
	std::vector<D3DXPLANE> frustumPlaneArray;
};

