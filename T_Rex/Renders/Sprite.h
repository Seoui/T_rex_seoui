#pragma once

class Sprite
{
public:
	Sprite(wstring textureFile, wstring shaderFile);
	Sprite(wstring textureFile, wstring shaderFile, float endX, float endY);
	Sprite(
		wstring textureFile,
		wstring shaderFile,
		float startX,
		float startY,
		float endX,
		float endY
	);
	~Sprite();

	

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() {return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 RotationDegree();

	D3DXVECTOR2 TextureSize() { return textureSize; }
	D3DXMATRIX World() { return world; }

	void setEffectScalar(bool bCheck) { sScalar->SetBool(bCheck); }

private:
	void UpdateWorld();
	void Initialize
	(
		wstring textureFile,
		wstring shaderFile,
		float startX,
		float startY,
		float endX,
		float endY
	);

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};

private:
	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	D3DXMATRIX world;
	ID3DX11EffectMatrixVariable* sWorld;
	ID3DX11EffectMatrixVariable* sView;
	ID3DX11EffectMatrixVariable* sProjection;
	ID3DX11EffectScalarVariable* sScalar;

	D3DXVECTOR2 textureSize;

	wstring textureFile;
	ID3D11ShaderResourceView* srv;

	
};

///////////////////////////////////////////////////////////////////////////////
// SRV관리 클래스
class Sprites
{
private:
	friend class Sprite;

private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);

private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = nullptr;
	};

	static map<wstring, SpriteDesc> spriteMap;
};