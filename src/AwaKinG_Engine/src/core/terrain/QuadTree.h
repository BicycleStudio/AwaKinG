#pragma once
#include "TerrainSector.h"

struct QuadTree
{
	QuadTree();
	QuadTree(TerrainSector* sector);
	~QuadTree();

	bool intersect(precomputeRay* ray);
	void findMaxMinFromChilds();
	void update();

// public for fast non-function use
	vector<QuadTree*>			childs;
	TerrainSector*				terrainSector;
	bool									land;
	float3*								ps[2];
	float3								max;
	float3								center;
};

