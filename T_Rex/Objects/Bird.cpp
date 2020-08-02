#include "stdafx.h"
#include "Bird.h"

Bird::Bird(D3DXVECTOR2 position)
	: position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile = L"Effect.fx";
	wstring textureFile = L"t_rex_sprite.png";
	
	animation = new Animation();
	Clip* clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 134, 8, 179, 41), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 180, 2, 225, 31), 0.1f);
	animation->AddClip(clip);

	animation->Play(0);
	animation->Position(position);
	animation->Scale(scale);
}	

Bird::~Bird()
{
	SAFE_DELETE(animation);
}

void Bird::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	position.x -= moveSpeed * Time::Delta();
	animation->Position(position);
	animation->Update(V, P);
}

void Bird::Render()
{
	animation->Render();
}
