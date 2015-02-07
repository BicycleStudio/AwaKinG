#include "QuadTree.h"

QuadTree::QuadTree(TerrainSector* sector)
{
	land = true;
	terrainSector = sector;
	ps[0] = &sector->max;
	ps[1] = &sector->min;
}
QuadTree::QuadTree()
{
	land = false;
	terrainSector = 0;
	ps[0] = new float3(0.0f, 0.0f, 0.0f);
	ps[1] = new float3(0.0f, 0.0f, 0.0f);
}
QuadTree::~QuadTree()
{
	for(int i = 0; i < childs.size(); i++)
		delete childs[i];
	childs.clear();
}
bool QuadTree::intersect(precomputeRay *r)
{
	
	return r->intersect(ps, -1000.0f,1000.0f);
}
void QuadTree::findMaxMinFromChilds()
{
	ps[0]->x = childs[0]->ps[0]->x; ps[0]->z = childs[0]->ps[0]->z;
	ps[1]->x = childs[childs.size() - 1]->ps[1]->x; ps[1]->z = childs[childs.size() - 1]->ps[1]->z;

	ps[0]->y = childs[0]->ps[0]->y; ps[1]->y = childs[0]->ps[1]->y;

	for(int i = 0; i < childs.size(); i++)
	{
		if(childs[i]->ps[1]->y > ps[1]->y) ps[1]->y = childs[i]->ps[1]->y;
		if(childs[i]->ps[0]->y < ps[0]->y) ps[0]->y = childs[i]->ps[0]->y;
	}
}

