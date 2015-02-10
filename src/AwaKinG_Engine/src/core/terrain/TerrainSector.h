#pragma once
#include "../../render/D3dRender.h"

struct TerrainSector
{
	TerrainSector();
	void release();
	void setMaxMinHeight(float value);
	void checkMaxMinHeight(float value);
	int										terrainId;
	int										id;

	float3								min;
	float3								max;
};
