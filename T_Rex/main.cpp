#include "stdafx.h"
#include "Systems/Device.h"
#include "Viewer/Camera.h"
#include "Scenes/Scene.h"
#include "Scenes/gameScene.h"

SceneValues* values;
vector<Scene*> scenes;


void InitScene()
{
	values = new SceneValues();

	values->MainCamera = new Camera();
	D3DXMatrixIdentity(&values->Projection);

	scenes.push_back(new gameScene(values));
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
		(float)Height* -0.5, (float)Height*0.5f,
		-1, 1
	); //Åõ¿µ
	
	for (Scene* scene : scenes)
		scene->Update();
}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(1, 1, 1, 1 );
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{


		for (Scene* scene : scenes)
			scene->Render();
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