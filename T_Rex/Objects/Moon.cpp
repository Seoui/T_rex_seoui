#include "stdafx.h"
#include "Moon.h"

Moon::Moon(D3DXVECTOR2 position)
	: position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile = L"Effect.fx";
	wstring textureFile = L"t_rex_sprite.png";

	animation = new Animation();
	Clip* clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 483, 1, 504, 42), 0.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 504, 1, 524, 42), 0.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 523, 1, 544, 42), 0.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 543, 1, 584, 42), 0.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 583, 1, 604, 42), 0.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 603, 1, 624, 42), 0.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 623, 1, 644, 42), 0.5f);
	animation->AddClip(clip);

	animation->Position(position);
	animation->Scale(scale);
}

Moon::~Moon()
{
	SAFE_DELETE(animation);
}

void Moon::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	position.x -= moveSpeed * Time::Delta();
	animation->Position(position);
	animation->Update(V, P);
}

void Moon::Render()
{
	animation->Render();
}
