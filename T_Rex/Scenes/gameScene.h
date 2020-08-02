#pragma once
#include "Scenes/Scene.h"

class gameScene : public Scene
{
public:
	gameScene(SceneValues* values);
	~gameScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	vector<class Marker*> markers;
};