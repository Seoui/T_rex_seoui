#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position(0, 0)
{
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	// D3DXMatrixTranslation(&view, -position.x, -position.y, 0.0f);

	// View(Camera)
	D3DXVECTOR3 eye = D3DXVECTOR3(position.x, position.y, 0.0f);
	D3DXVECTOR3 at(0, 0, 1);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&view, &eye, &(eye + at), &up);
}
