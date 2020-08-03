#pragma once
#include "Collider/Collider.h"
#include "Objects/Bird.h"
#include "Objects/Cactus.h"
#include "Objects/Cloud.h"
#include "Objects/Moon.h"
#include "Objects/Star.h"

struct SxyExy
{
	float startX;
	float startY;
	float endX;
	float endY;
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	vector<Bird*>& GetBird() { return bird; }
	vector<Cactus*>& GetCactus() { return cactus; }
	vector<Collider*>& GetBirdColliders() { return birdColliders; }
	vector<Collider*>& GetCactusColliders() { return cactusColliders; }
	void setNight(bool bState) { bNight = bState; }
	void setMoveSpeed(float speed);
	void Reset();

private:
	void SpawnBirdOrCactus();
	void SpawnBird();
	void SpawnCactus();
	void SpawnCloud();
	void SpawnMoon();
	void SpawnStar();
	void RemoveObject();

private:
	random_device randomDevice;
	mt19937 randomEngine{ randomDevice() };

	vector<Collider*> birdColliders;
	vector<Collider*> cactusColliders;
	vector<Bird*> bird;
	vector<Cactus*> cactus;
	vector<Cloud*> cloud;
	vector<Moon*> moon;
	vector<Star*> star;
	SxyExy cactusXY[6];
	SxyExy starXY[3];

	bool bNight = false;
	float moveSpeed = 200.0f;
	float bcPlayTime = 0.0f;
	float bcRandTime;
	float cloudPlayTime = 0.0f;
	float cloudRandTime;
	float moonPlayTime = 0.0f;
	float moonRandTime;
	float starPlayTime = 0.0f;
	float starRandTime;
};