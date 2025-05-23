#pragma once

enum class PlayMode { End = 0, Loop };

struct Frame
{
	Sprite* Image;
	double Time;

	Frame(Sprite* image, double time);
	~Frame();
};

class Clip
{
public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f);
	~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 RotationDegree();

	void AddFrame(Sprite* sprite, float time);
	void AddFrame(Sprite* sprite, double time);

	void Play();
	void Play(UINT startFrame);
	void Stop();
	void SetCurrentFrame(UINT num) { currentFrame = num; }
	void resetPlayTime() { playTime = 0.0f; }
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	D3DXVECTOR2 TextureSize();

	Sprite* CurrentSprite();

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	float length;
	float speed;
	bool bPlay;
	UINT currentFrame;
	float playTime;

	PlayMode mode;

	vector<Frame*> frames;
};