#include "stdafx.h"
#include "UI.h"

UI::UI(D3DXVECTOR2 position)
	:position(position), scale(1.0f, 1.0f)
{
	wstring shaderFile = L"Effect.fx";
	wstring textureFile = L"t_rex_sprite.png";

	double time = 0.1f;

	gameOverSprite = new Sprite(textureFile, shaderFile, 654, 14, 846, 26);
	gameOverSprite->Scale(2, 2);
	gameOverSprite->Position(-90.0f, 80.0f);
	// 점수 애니메이션
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
	SAFE_DELETE(gameOverSprite);
}

void UI::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	curGamePlayTime += Time::Delta();
	for (int i = 0; i < 5; i++)
	{
		animation[i]->Update(V, P);
	}

	if (isCrash)
	{
		D3DXVECTOR2 position(220.0f, 220.0f);
		gameOverSprite->Update(V, P);
		for (int i = 0; i < 7; i++)
		{
			HIsprite[i]->Position(position);
			HIsprite[i]->Update(V, P);
			position.x -= 11.0f;
		}
	}
}

void UI::Render()
{
	for (int i = 0; i < 5; i++)
	{
		animation[i]->Render();
	}

	if (isCrash)
	{
		gameOverSprite->Render();
		for (int i = 0; i < 7; i++)
		{
			HIsprite[i]->Render();
		}
	}
}

bool UI::Crash(bool bCrash)
{
	if(prevGamePlayTime < curGamePlayTime)
	{
		isCrash = bCrash;
		HIsprite.clear();
		for (int i = 0; i < 5; i++)
		{
			D3DXVECTOR4 textureCoord = animation[i]->GetSprite()->getTextureCoord();

			HIsprite.push_back(new Sprite(L"t_rex_sprite.png",L"Effect.fx",
				textureCoord.x, textureCoord.y,
				textureCoord.z, textureCoord.w
			));
		}
		HIsprite.push_back(new Sprite(L"t_rex_sprite.png", L"Effect.fx",
			765, 1, 774, 13));
		HIsprite.push_back(new Sprite(L"t_rex_sprite.png", L"Effect.fx",
			754, 1, 764, 13));
	}
	
	prevGamePlayTime = curGamePlayTime;
	return isCrash;
}
