#include "stdafx.h"
#include "T_rex.h"

T_rex::T_rex(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	: focusOffset(180, 160)
{
	wstring shaderFile = L"Effect.fx";
	wstring spriteFile = L"t_rex_sprite.png";

	animation = new Animation();
	Clip* clip;
	// Run[0]
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 848, 2, 891, 48), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 892, 2, 935, 48), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 936, 2, 979, 48), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 980, 2, 1023, 48), 0.1f);
		animation->AddClip(clip);
	}

	// Jump[1]
	{	
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 848, 2, 891, 48), 0.1f);
		animation->AddClip(clip);
	}

	// Duck[2]
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1112, 19, 1170, 48), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1171, 19, 1229, 48), 0.2f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	startPosition = position;
}

T_rex::~T_rex()
{
	SAFE_DELETE(animation);
}

void T_rex::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	D3DXVECTOR2 position = animation->Position();

	if (Key->Press(VK_SPACE) || Key->Press(VK_UP))
	{
		animation->Play(1);
		Jump();
	}
	else if (Key->Press(VK_DOWN))
	{
		animation->Play(2);
	}
	
	if (Key->Up(VK_SPACE) || Key->Up(VK_UP))
	{
		animation->Play(0);
		Landing();
	}
	if (Key->Up(VK_DOWN))
	{
		animation->Play(0);
	}

	Physics();

	animation->Update(V, P);
}

void T_rex::Render()
{
	animation->Render();
}

Sprite* T_rex::GetSprite()
{
	return animation->GetSprite();
}

void T_rex::Jump()
{
	jumpSpeed = 25.0f;
}

void T_rex::Landing()
{
	if (-jumpSpeed / GravityAcceleration > jumpTime)
		jumpTime = (-2 * jumpSpeed) / GravityAcceleration - jumpTime;
}

void T_rex::Physics()
{
	D3DXVECTOR2 position = animation->Position();
	
	if (jumpSpeed > 0)
	{
		jumpHeight = (GravityAcceleration * jumpTime * jumpTime / 2) + (jumpTime * jumpSpeed);
		jumpTime += jumpSpeed * Time::Delta();
		animation->Position(position.x, startPosition.y + jumpHeight);
	}

	if (jumpHeight < 0.0f)
	{
		jumpSpeed = 0.0f;
		jumpTime = 0.0f;
		animation->Position(position.x, startPosition.y);
	}

	return;
}

void T_rex::Focus(D3DXVECTOR2* position, D3DXVECTOR2* size)
{
	*position = animation->Position() + focusOffset;
	*size = D3DXVECTOR2(1, 1);
}
