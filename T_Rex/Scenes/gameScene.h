#pragma once
#include "Scenes/Scene.h"

class GameScene : public Scene
{
public:
	GameScene(SceneValues* values);
	~GameScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	vector<class Marker*> markers;
	bool bSwapGround = false;
	bool bCrash = false;
};