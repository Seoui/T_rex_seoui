#include "stdafx.h"
#include "Systems/Device.h"
#include "Viewer/Camera.h"
#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"

SceneValues* values;
vector<Scene*> scenes;
GameScene* gameScene;

void InitScene()
{
	values = new SceneValues();

	values->MainCamera = new Camera();
	D3DXMatrixIdentity(&values->Projection);

	gameScene = new GameScene(values);
	scenes.push_back(gameScene);
	
}

void DestroyScene()
{
	for (Scene* scene : scenes)
		SAFE_DELETE(scene);
	SAFE_DELETE(values);
}

void Update()
{
	values->MainCamera->Update();
		
	// Projection
	D3DXMatrixOrthoOffCenterLH
	(
		&values->Projection,
		(float)Width* -0.5f, (float)Width*0.5f,
		(float)Height* -0.3f, (float)Height*0.7f,
		-1, 1
	); //Åõ¿µ
	
	for (Scene* scene : scenes)
		scene->Update();
	
}

void Render()
{
	if (gameScene->getNight())
	{
		D3DXCOLOR bgcolor = D3DXCOLOR(0, 0, 0, 0);
		DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
		{
			for (Scene* scene : scenes)
				scene->Render();
		}
	}
	else
	{
		D3DXCOLOR bgcolor = D3DXCOLOR(1, 1, 1, 1);
		DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
		{
			for (Scene* scene : scenes)
				scene->Render();
		}
	}
	
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		RECT rect = { 0, 0, 500, 200 };
		wstring text = L"FPS : " + to_wstring((int)ImGui::GetIO().Framerate);
		DirectWrite::RenderText(text, rect);
	}
	DirectWrite::GetDC()->EndDraw();

	SwapChain->Present(0, 0);
} 