#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}
bool Entity::initialize(XMFLOAT4X4* worldMatrix)
{
	_worldMatrix = worldMatrix;
	return true;
}
void Entity::update()
{

}
void Entity::shutdown()
{

}
