#pragma once
#include "Scenes/Scene.h"

enum class GAMESTATE { RUN, STOP, RESUME };
class GameScene : public Scene
{
public:
	GameScene(SceneValues* values);
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;
	GAMESTATE getGameState() { return gameState; }
	bool getNight() { return bNight; }

private:
	vector<class Marker*> markers;
	GAMESTATE gameState = GAMESTATE::RUN;
	float nightTime = 12.0f;
	float nightPlayTime = 0.0f;
	float dayTime = 60.0f;
	float dayPlayTime = 0.0f;
	float gameTime = 10.0f;
	float gamePlayTime = 0.0f;
	float multipleTime = 1;
	bool bSwapGround = false;
	bool bCrash = false;
	bool bNight = false;
	bool bDay = true;
};