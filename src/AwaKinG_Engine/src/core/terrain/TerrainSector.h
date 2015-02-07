#pragma once
#include "../../render/D3dRender.h"

struct TerrainSector
{
	TerrainSector();
	void release();
	int										terrainId;
	int										id;

	float3								min;
	float3								max;
};

