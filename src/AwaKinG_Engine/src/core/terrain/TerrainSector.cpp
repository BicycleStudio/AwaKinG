#include "TerrainSector.h"

TerrainSector::TerrainSector()
{
	min = float3(0.0f, 0.0f, 0.0f);
	max = float3(0.0f, 0.0f, 0.0f);

	father = 0;
}
void TerrainSector::release()
{

}
void TerrainSector::setMaxMinHeight(float value)
{
	max.y = value; min.y = value;
}
void TerrainSector::checkMaxMinHeight(float value)
{
	if(max.y < value) max.y = value;
	if(min.y > value) min.y = value;
}
