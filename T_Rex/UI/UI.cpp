#include "stdafx.h"
#include "UI.h"

UI::UI(D3DXVECTOR2 position)
	:position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile = L"Effect.fx";
	wstring textureFile = L"t_rex_sprite.png";
	
	float time = 0.5f;

	for(int i = 0; i<5;i++)
	{
		animation.push_back(new Animation());
		Clip* clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 654, 1, 664, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 665, 1, 674, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 674, 1, 684, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 684, 1, 694, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 694, 1, 704, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 704, 1, 714, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 714, 1, 724, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 724, 1, 734, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 734, 1, 744, 13), time);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 744, 1, 754, 13), time);
		animation[i]->AddClip(clip);
		time *= 10.0f;
	}

	for (int i = 0; i < 5; i++)
	{
		animation[i]->Position(position);
		animation[i]->Scale(scale);
		animation[i]->Play(0);
		position.x -= 11.0f;
	}
}

UI::~UI()
{
	for (auto& i : animation)
		SAFE_DELETE(i);
}

void UI::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i]->Update(V, P);
	}
}

void UI::Render()
{
	for (int i = 0; i < 5; i++)
	{
		animation[i]->Render();
	}
}
