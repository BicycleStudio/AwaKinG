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
void Entity::setTransformation(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 rot)
{

	XMStoreFloat4x4(_worldMatrix, XMMatrixMultiply(XMMatrixMultiply(XMMatrixScaling(scl.x, scl.y, scl.z), XMMatrixRotationRollPitchYaw(rot.x*0.0174532925, rot.y*0.0174532925, rot.z*0.0174532925)), XMMatrixTranslation(pos.x, pos.y, pos.z)));
	//XMMatrixAffineTransformation(XMLoadFloat3(&pos),)

}
