#include "Camera.h"

Camera::Camera()
{
	XMStoreFloat4x4(&_viewMatrixRender, XMMatrixIdentity());
	_position = XMFLOAT3(0.0f, 0.0f, -10.0f);
	_look = XMFLOAT3(0.0f, 0.0f, 1.0f);
	_up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_right = XMFLOAT3(1.0f, 0.0f, 0.0f);
}
Camera::~Camera()
{

}
XMFLOAT4X4* Camera::getViewMatrixPointer()
{
	return &_viewMatrixRender;
}
void Camera::shutdown()
{

}
void Camera::update()
{
	XMVECTOR look_ = XMVector3Normalize(XMLoadFloat3(&_look));
	XMVECTOR up_ = XMVector3Cross(look_, XMLoadFloat3(&_right));
	up_ = XMVector3Normalize(up_);
	XMStoreFloat3(&_up, up_);
	XMStoreFloat3(&_look, look_);

	XMStoreFloat4x4(&_viewMatrixRender, XMMatrixLookAtLH(XMLoadFloat3(&_position), XMLoadFloat3(&_look), XMLoadFloat3(&_up)));
}
void Camera::pitch(float angle)
{
	XMMATRIX t_ = XMMatrixRotationAxis(XMLoadFloat3(&_right), angle);
	XMStoreFloat3(&_up, XMVector3TransformCoord(XMLoadFloat3(&_up), t_));

	if(_up.y >= 0)
		XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), t_));
}
void Camera::yaw(float angle)
{
	XMMATRIX t_ = XMMatrixRotationY(angle);
	XMStoreFloat3(&_right, XMVector3TransformCoord(XMLoadFloat3(&_right), t_));
	XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), t_));
}
void Camera::walk(float units)
{
	XMStoreFloat3(&_position, XMVectorAdd(XMLoadFloat3(&_position), XMVectorMultiply(XMLoadFloat3(&_look), XMLoadFloat(&units))));
}
void Camera::strafe(float units)
{
	XMStoreFloat3(&_position, XMVectorAdd(XMLoadFloat3(&_position), XMVectorMultiply(XMLoadFloat3(&_right), XMLoadFloat(&units))));
}