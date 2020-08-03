#include "stdafx.h"
#include "Background.h"

Background::Background()
	: nPrevSprite(0), nCurSprite(1), nNextSprite(2),
	moveSpeed(220.0f), bSwapGround(false), position(0, 0),
	backGroundTrigger(600, 2)
{
	wstring shaderFile = L"Effect.fx";
	sprites[0] = new Sprite(L"t_rex_sprite.png", shaderFile, 0, 53, 1200, 68);
	sprites[1] = new Sprite(L"t_rex_sprite.png", shaderFile, 0, 53, 1200, 68);
	sprites[2] = new Sprite(L"t_rex_sprite.png", shaderFile, 0, 53, 1200, 68);
	
	// 시작은 sprites[1]
	sprites[0]->Position(position.x - 1198, 0);
	sprites[2]->Position(position.x + 1198, 0);

	lineTrigger = new LineTrigger();
}

Background::~Background()
{
	for (auto& i : sprites)
		SAFE_DELETE(i);
	SAFE_DELETE(lineTrigger);
}

void Background::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	sprites[0]->Update(V, P);
	sprites[1]->Update(V, P);
	sprites[2]->Update(V, P);
	lineTrigger->Update(V, P);

	D3DXVECTOR2 SpritePosition0 = sprites[0]->Position();
	D3DXVECTOR2 SpritePosition1 = sprites[1]->Position();
	D3DXVECTOR2 SpritePosition2 = sprites[2]->Position();
	D3DXVECTOR2 LinePosition = lineTrigger->Position();

	SpritePosition0.x -= moveSpeed * Time::Delta();
	SpritePosition1.x -= moveSpeed * Time::Delta();
	SpritePosition2.x -= moveSpeed * Time::Delta();
	LinePosition.x -= moveSpeed * Time::Delta();

	sprites[0]->Position(SpritePosition0);
	sprites[1]->Position(SpritePosition1);
	sprites[2]->Position(SpritePosition2);
	lineTrigger->Position(LinePosition);
}

void Background::Render()
{
	if(bdevelopMode == true)
		lineTrigger->Render();
	sprites[0]->Render();
	sprites[1]->Render();
	sprites[2]->Render();
}

void Background::SwapGround(bool bSwapGround)
{
	if (bSwapGround)
	{
		Sprite* NextSprite = sprites[nNextSprite];
		D3DXVECTOR2 NextPosition(NextSprite->Position());

		lineTrigger->Position(NextPosition.x, NextPosition.y);
		sprites[nPrevSprite]->Position(NextPosition.x + 1198, NextPosition.y);

		// 과거가 cur, 현재가 next, 다음이 prev(다시 원위치)
		int temp;
		temp = nPrevSprite;
		nPrevSprite = nCurSprite;
		nCurSprite = nNextSprite;
		nNextSprite = temp;

		/*	점 트리거이다.	
		backGroundTrigger += sprites[nCurSprite]->Position();
		*/
		bSwapGround = false;
	}
}

Background::LineTrigger::LineTrigger()
	: position(300.0f, 0.0f)
{
	shader = new Shader(L"Bounding.fx");
	CreateBuffer();

	D3DXMatrixIdentity(&world);
	sWorld = shader->AsMatrix("World");
	sView = shader->AsMatrix("View");
	sProjection = shader->AsMatrix("Projection");
	sColor = shader->AsVector("LineColor");
}

void Background::LineTrigger::CreateBuffer()
{
	Vertex vertices[2];

	vertices[0].Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	// Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 2;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Background::LineTrigger::~LineTrigger()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_DELETE(shader);
}

void Background::LineTrigger::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	D3DXMATRIX S, T;
	D3DXMatrixScaling(&S, 1.0f, 300.0f, 1.0f);
	D3DXMatrixTranslation(&T, position.x+200.0f, position.y, 0.0f);
	world = S * T;

	sWorld->SetMatrix(world);
	sView->SetMatrix(V);
	sProjection->SetMatrix(P);
}

void Background::LineTrigger::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	sColor->SetFloatVector(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	shader->Draw(0, 0, 2);
}

