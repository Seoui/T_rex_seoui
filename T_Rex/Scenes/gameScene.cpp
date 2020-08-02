#include "stdafx.h"
#include "gameScene.h"
#include "Collider/Collider.h"
#include "Objects/t_rex.h"
#include "Objects/Background.h"

/*
	T-rex 만들기 (방학기간동안)
*/
// 숙제 lambda 함수 공부

T_rex* t_rex = nullptr;
Background* background = nullptr;

Collider* collider = nullptr;
bool bSwapGround = false;

gameScene::gameScene(SceneValues * values)
	:Scene(values)
{
	wstring shaderFile = L"Effect.fx";
	background = new Background(shaderFile);
	

	t_rex = new T_rex(D3DXVECTOR2(-290, 0), D3DXVECTOR2(1, 1));

	collider = new Collider();
}

gameScene::~gameScene()
{
	SAFE_DELETE(background);
	SAFE_DELETE(t_rex);
	SAFE_DELETE(collider);
}

void gameScene::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	
	background->Update(V, P);

	collider->World(t_rex->GetSprite()->World());
	collider->Update(V, P);
	
	bSwapGround = Collider::Aabb(t_rex->GetSprite()->World(), background->getLineTriggerWorld());
	background->SwapGround(bSwapGround);
	t_rex->Update(V, P);
}

void gameScene::Render()
{
	background->Render();
	t_rex->Render();
	collider->Render();
	collider->DrawColliderColor(bSwapGround);
}
