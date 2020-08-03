#pragma once
#include "Scenes/Scene.h"

enum class GAMESTATE { RUN, STOP };
class GameScene : public Scene
{
public:
	GameScene(SceneValues* values);
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;
	
	void CheckCrash(D3DXMATRIX& V, D3DXMATRIX& P);
	void ChangeDayNight();
	void Reset();
	bool getNight() { return bNight; }

private:
	GAMESTATE gameState = GAMESTATE::RUN;
	float nightTime = 12.0f;
	float nightPlayTime = 0.0f;
	float dayTime = 12.0f;
	float dayPlayTime = 0.0f;
	float gameTime = 15.0f;
	float gamePlayTime = 0.0f;
	float multipleTime = 1;
	float moveSpeed = 220.0f;
	bool bSwapGround = false;
	bool bCrash = false;
	bool bNight = false;
	bool bDay = true;
	bool bdevelopMode = false;
};