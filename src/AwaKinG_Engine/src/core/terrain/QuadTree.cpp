#include "QuadTree.h"


QuadTree::QuadTree(TerrainSector* sector)
{
	worldMatrix = new XMFLOAT4X4();
	land = true;
	terrainSector = sector;
	ps[0] = &sector->min;
	ps[1] = &sector->max;

	max.x = ps[1]->x - ps[0]->x;max.y = ps[1]->y - ps[0]->y;max.z = ps[1]->z - ps[0]->z;
	XMStoreFloat4x4(worldMatrix, (XMMatrixMultiply(XMMatrixScaling(max.x, max.y, max.z), XMMatrixTranslation(ps[0]->x, ps[0]->y, ps[0]->z))));
}
QuadTree::QuadTree()
{
	worldMatrix = new XMFLOAT4X4();
	land = false;
	terrainSector = 0;
	ps[0] = new float3(0.0f, 0.0f, 0.0f);
	ps[1] = new float3(0.0f, 0.0f, 0.0f);
}
QuadTree::~QuadTree()
{
}
bool QuadTree::intersect(precomputeRay *r)
{
	return r->intersect(ps, -1000.0f,100000.0f);
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
	max.x = ps[1]->x - ps[0]->x; max.y = ps[1]->y - ps[0]->y; max.z = ps[1]->z - ps[0]->z;
	XMStoreFloat4x4(worldMatrix, (XMMatrixMultiply(XMMatrixScaling(max.x, max.y, max.z), XMMatrixTranslation(ps[0]->x, ps[0]->y, ps[0]->z))));
}
void QuadTree::update()
{
	vector<QuadTree*>* fathers_ = new vector<QuadTree*>;
	vector<QuadTree*>* fathers2_ = new vector<QuadTree*>;
	fathers_->push_back(this);
	vector<QuadTree*> childs_;
	childs_.push_back(this);
	int prevSize_ = 1;
	while(!childs_[childs_.size() - 1]->land)
	{
		prevSize_ = childs_.size();
		for(int i = 0; i < fathers_->size(); i++)
		{
			for(int j = 0; j < fathers_[0][i]->childs.size(); j++)
			{
				childs_.push_back(fathers_[0][i]->childs[j]);
				fathers2_->push_back(fathers_[0][i]->childs[j]);
			}
		}
		fathers_ = fathers2_;
		fathers2_ = new vector<QuadTree*>;
	}
	fathers_->clear();	fathers2_->clear();
	delete fathers_;		delete fathers2_;
	for(int i = childs_.size() - 1; i>=prevSize_; i--)
	{
		childs_[i]->max.y = childs_[i]->ps[1]->y - childs_[i]->ps[0]->y;
		//worldMatrix->_22 = max.y;
		//worldMatrix->_42 = ps[0]->y;

		XMStoreFloat4x4(worldMatrix, (XMMatrixMultiply(XMMatrixScaling(max.x, max.y, max.z), XMMatrixTranslation(ps[0]->x, ps[0]->y, ps[0]->z))));
		//XMStoreFloat4x4(worldMatrix, (XMMatrixMultiply(XMMatrixScaling(max.x, max.y, max.z), XMMatrixTranslation(center.x, center.y, center.z))));

		childs_.erase(childs_.begin() + i);
	}
	for(int i = childs_.size() - 1; i>=0; i--)
	{
		childs_[i]->findMaxMinFromChilds();
		childs_.erase(childs_.begin() + i);
	}
}
