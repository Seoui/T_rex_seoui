#include "stdafx.h"
#include "Moon.h"

Moon::Moon(D3DXVECTOR2 position)
	: position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile = L"Effect.fx";
	wstring textureFile = L"t_rex_sprite.png";

	animation = new Animation();
	Clip* clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 484, 1, 504, 42), 3.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 505, 1, 524, 42), 3.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 524, 1, 544, 42), 3.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 544, 1, 584, 42), 3.5f);
	animation->AddClip(clip);

	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 544, 1, 584, 42), 3.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 584, 1, 604, 42), 3.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 604, 1, 624, 42), 3.5f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 624, 1, 644, 42), 3.5f);
	animation->AddClip(clip);

	animation->Play(0);
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
