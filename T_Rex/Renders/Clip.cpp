#include "stdafx.h"
#include "Clip.h"


//-----------------------------------------------------------------------------
// Frame(Struct)
//-----------------------------------------------------------------------------

Frame::Frame(Sprite * image, float time)
{
	Image = image;
	Time = time;
}

Frame::~Frame()
{
	SAFE_DELETE(Image);
}

//-----------------------------------------------------------------------------
// Clip
//-----------------------------------------------------------------------------

Clip::Clip(PlayMode mode, float speed)
	:mode(mode), speed(speed), length(0),
	playTime(0), bPlay(false), currentFrame(0),
	position(0, 0), scale(1, 1), rotation(0, 0, 0)
{
}

Clip::~Clip()
{
	for (Frame* frame : frames)
		SAFE_DELETE(frame);
}

void Clip::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Clip::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void Clip::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Clip::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;
}

void Clip::RotationDegree(float x, float y, float z)
{
	RotationDegree(D3DXVECTOR3(x, y, z));
}

void Clip::RotationDegree(D3DXVECTOR3 & vec)
{
	D3DXVECTOR3 temp;
	temp.x = Math::ToRadian(vec.x);
	temp.y = Math::ToRadian(vec.y);
	temp.z = Math::ToRadian(vec.z);

	Rotation(temp);
}

D3DXVECTOR3 Clip::RotationDegree()
{
	D3DXVECTOR3 temp = rotation;
	temp.x = Math::ToDegree(rotation.x);
	temp.y = Math::ToDegree(rotation.y);
	temp.z = Math::ToDegree(rotation.z);

	return temp;
}

void Clip::AddFrame(Sprite * sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play()
{
	playTime = 0.0f;
	currentFrame = 0;
	bPlay = true;
}

void Clip::Play(UINT startFrame)
{
	playTime = 0.0f;
	currentFrame = startFrame;
	bPlay = true;
}

void Clip::Stop()
{
	bPlay = false;
	currentFrame = 0;
}

void Clip::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	Frame* frame = frames[currentFrame];

	if (bPlay == true)
	{
		float time = frame->Time * speed;
		playTime += Time::Delta();

		if (playTime >= time)
		{
			switch (mode)
			{
				case PlayMode::End:
				{
					currentFrame++;

					if (currentFrame >= frames.size())
					{
						Stop();
					}
				}
				break;

				case PlayMode::Loop:
				{
					currentFrame++;
					currentFrame %= frames.size();
				}
				break;
			}
			playTime = 0.0f;
		}
	}
	
	frames[currentFrame]->Image->Scale(scale);
	frames[currentFrame]->Image->Rotation(rotation);
	frames[currentFrame]->Image->Position(position);

	frames[currentFrame]->Image->Update(V, P);
}

void Clip::Render()
{
	/*
	for (Frame* frame : frames){
		frame->Image->Render();
	}
	*/
	Frame* frame = frames[currentFrame];
	frame->Image->Render();
}

D3DXVECTOR2 Clip::TextureSize()
{
	return frames[currentFrame]->Image->TextureSize();
}

Sprite * Clip::CurrentSprite()
{
	return frames[currentFrame]->Image;
}
