#pragma once
#include "TerrainSector.h"

struct QuadTree
{
	QuadTree();
	QuadTree(TerrainSector* sector);
	~QuadTree();

	bool intersect(precomputeRay* ray);
	void findMaxMinFromChilds();

// public for fast non-function use
	vector<QuadTree*>			childs;
	TerrainSector*				terrainSector;
	bool									land;
	float3*								ps[2];
};

