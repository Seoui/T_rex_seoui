#include "stdafx.h"
#include "GameScene.h"
#include "Collider/Collider.h"
#include "Objects/t_rex.h"
#include "Objects/Background.h"
#include "Objects/Cactus.h"
#include "Objects/Bird.h"
#include "Objects/Cloud.h"
#include "UI/UI.h"
/*
	T-rex 만들기 (방학기간동안)
*/
// 숙제 lambda 함수 공부

T_rex* t_rex = nullptr;
Background* background = nullptr;
Collider* collider = nullptr;
Cactus* cactus = nullptr;
Cloud* cloud = nullptr;
Bird* bird = nullptr;
UI* ui = nullptr;

bool bSwapGround = false;

GameScene::GameScene(SceneValues * values)
	:Scene(values)
{
	background = new Background();

	t_rex = new T_rex(D3DXVECTOR2(-290, 0), D3DXVECTOR2(1, 1));
	collider = new Collider();
	cactus = new Cactus(L"t_rex_sprite.png", 407, 2, 481, 51);
	bird = new Bird();
	ui = new UI();
	cloud = new Cloud();
}

GameScene::~GameScene()
{
	SAFE_DELETE(background);
	SAFE_DELETE(t_rex);
	SAFE_DELETE(collider);
	SAFE_DELETE(cactus);
	SAFE_DELETE(bird);
	SAFE_DELETE(ui);
	SAFE_DELETE(cloud);
}

void GameScene::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	
	background->Update(V, P);

	collider->World(t_rex->GetSprite()->World());
	collider->Update(V, P);
	
	bSwapGround = Collider::Aabb(t_rex->GetSprite()->World(), background->getLineTriggerWorld());
	background->SwapGround(bSwapGround);
	t_rex->Update(V, P);
	cactus->Update(V, P);
	bird->Update(V, P);
	ui->Update(V, P);
	cloud->Update(V, P);
}

void GameScene::Render()
{

	background->Render();
	cloud->Render();
	t_rex->Render();
	cactus->Render();
	bird->Render();
	ui->Render();
	collider->Render();
	collider->DrawColliderColor(bSwapGround);
}
