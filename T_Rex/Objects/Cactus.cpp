#include "stdafx.h"
#include "Cactus.h"

Cactus::Cactus(D3DXVECTOR2 position, float startX, float startY, float endX, float endY)
	: position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile = L"Effect.fx";
	wstring textureFile = L"t_rex_sprite.png";

	sprite = new Sprite(textureFile, shaderFile, startX, startY, endX, endY);

	sprite->Position(position);
	sprite->Scale(scale);
}

Cactus::~Cactus()
{
	SAFE_DELETE(sprite);
}

void Cactus::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	position.x -= moveSpeed * Time::Delta();
	sprite->Position(position);
	sprite->Update(V, P);
}

void Cactus::Render()
{
	sprite->Render();
}
