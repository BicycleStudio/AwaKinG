#pragma once
#include "../../render/D3dRender.h"

struct QuadTree
{
	QuadTree();
	QuadTree(float3* terMax, float3* terMin, int sectorId, int terrainId);
	~QuadTree();

	bool intersect(precomputeRay* ray);
	void findMaxMinFromChilds();
	void update();
	void updateInside();

	QuadTree*							father;
	vector<QuadTree*>			childs;
	bool									land;
	float3*								ps[2];
	float3								max;
	int										sectorID;
	int										terrainID;

	XMFLOAT4X4*						worldMatrix;
};

