#include "stdafx.h"
#include "Star.h"

Star::Star(D3DXVECTOR2 position, float startX, float startY, float endX, float endY)
	: position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile(L"Effect.fx");
	wstring textureFile = L"t_rex_sprite.png";

	sprite = new Sprite(textureFile, shaderFile, startX, startY, endX, endY);

	sprite->Position(position);
	sprite->Scale(scale);
}

Star::~Star()
{
	SAFE_DELETE(sprite);
}

void Star::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	position.x -= moveSpeed * Time::Delta();
	sprite->Position(position);
	sprite->Update(V, P);
}

void Star::Render()
{
	sprite->Render();
}
