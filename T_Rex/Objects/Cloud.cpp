#include "stdafx.h"
#include "Cloud.h"

Cloud::Cloud(D3DXVECTOR2 position)
	:position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile = L"Effect.fx";
	wstring textureFile = L"t_rex_sprite.png";
	
	sprite = new Sprite(textureFile, shaderFile, 85, 1, 132, 15);

	sprite->Position(position);
	sprite->Scale(scale);
}

Cloud::~Cloud()
{
	SAFE_DELETE(sprite);
}

void Cloud::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	position.x -= moveSpeed * Time::Delta();
	sprite->Position(position);
	sprite->Update(V, P);
}

void Cloud::Render()
{
	sprite->Render();
}
