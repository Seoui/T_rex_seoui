#pragma once

class Background
{
public:
	class LineTrigger
	{
	public:
		LineTrigger();
		~LineTrigger();

		void CreateBuffer();
		D3DXMATRIX getWorld() { return world; }
		void setWorld(D3DXMATRIX& w) { world = w; }
		D3DXVECTOR2 Position() { return position; }
		void Position(D3DXVECTOR2& p) { position = p; }
		void Position(float x, float y) { Position(D3DXVECTOR2(x, y)); }

		void Update(D3DXMATRIX& V, D3DXMATRIX& P);
		void Render(); //이건 지워줄 예정임 그릴필요 없음

	private:
		struct Vertex
		{
			D3DXVECTOR3 Position;
		};

		Shader* shader;
		D3DXMATRIX world;
		ID3D11Buffer* vertexBuffer;
		ID3DX11EffectMatrixVariable* sWorld;
		ID3DX11EffectMatrixVariable* sProjection;
		ID3DX11EffectMatrixVariable* sView;
		ID3DX11EffectVectorVariable* sColor;

		D3DXVECTOR2 position;
	};

public:
	Background();
	~Background();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	void SwapGround(bool bSwapGround);

	D3DXMATRIX getLineTriggerWorld() { return lineTrigger->getWorld(); }
	D3DXMATRIX getCurSpriteWorld() { return sprites[nCurSprite]->World(); }
	D3DXVECTOR2 GetBackGroundTrigger() { return backGroundTrigger; }

private:
	LineTrigger* lineTrigger;
	Sprite* sprites[3];
	D3DXVECTOR2 position;
	D3DXVECTOR2 backGroundTrigger;
	
	int nPrevSprite;
	int nCurSprite;
	int nNextSprite;
	bool bSwapGround;
	float moveSpeed;
};

