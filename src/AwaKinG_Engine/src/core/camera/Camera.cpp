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
	XMStoreFloat3(&_look, look_);
	XMVECTOR up_ = XMVector3Cross(look_, XMLoadFloat3(&_right));
	up_ = XMVector3Normalize(up_);
	XMStoreFloat3(&_up, up_);
	XMVECTOR right_ = XMVector3Cross(up_, look_);
	right_ = XMVector3Normalize(right_);
	XMStoreFloat3(&_right, right_);
	
	float x;
	XMStoreFloat(&x, XMVector3Dot(XMLoadFloat3(&_right), XMLoadFloat3(&_position)));x = -x;
	float y;
	XMStoreFloat(&y, XMVector3Dot(XMLoadFloat3(&_up), XMLoadFloat3(&_position))); y = -y;
	float z;
	XMStoreFloat(&z, XMVector3Dot(XMLoadFloat3(&_look), XMLoadFloat3(&_position))); z = -z;

	_viewMatrixRender._11 = _right.x; _viewMatrixRender._12 = _up.x;
	_viewMatrixRender._21 = _right.y; _viewMatrixRender._22 = _up.y;
	_viewMatrixRender._31 = _right.z; _viewMatrixRender._32 = _up.z;
	_viewMatrixRender._41 = x;				_viewMatrixRender._42 = y;

	_viewMatrixRender._13 = _look.x; _viewMatrixRender._14 = 0.0f;
	_viewMatrixRender._23 = _look.y; _viewMatrixRender._24 = 0.0f;
	_viewMatrixRender._33 = _look.z; _viewMatrixRender._34 = 0.0f;
	_viewMatrixRender._43 = z;				_viewMatrixRender._44 = 1.0f;

	//XMStoreFloat4x4(&_viewMatrixRender, XMMatrixLookAtLH(XMLoadFloat3(&_position), XMLoadFloat3(&_look), XMLoadFloat3(&_up)));
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
	_position.x += _look.x*units;
	_position.y += _look.y*units;
	_position.z += _look.z*units;
}
void Camera::strafe(float units)
{
	_position.x += _right.x*units;
	_position.y += _right.y*units;
	_position.z += _right.z*units;
}