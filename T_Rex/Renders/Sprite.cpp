#include "stdafx.h"
#include "Sprite.h"

//-----------------------------------------------------------------------------
// Sprite
//-----------------------------------------------------------------------------

Sprite::Sprite(wstring textureFile, wstring shaderFile)
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float endX, float endY)
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);
}

void Sprite::Initialize(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	this->textureFile = L"./_Textures/" + textureFile;

	shader = new Shader(shaderFile);

	srv = Sprites::Load(this->textureFile);
	shader->AsShaderResource("DiffuseMap")->SetResource(srv);

	D3DX11_IMAGE_INFO info;
	HRESULT hr = D3DX11GetImageInfoFromFile(this->textureFile.c_str(), nullptr, &info, nullptr);
	assert(SUCCEEDED(hr));

	// Uv좌표=> startX, startY, endX, endY
	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	Vertex vertices[6];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = D3DXVECTOR2(startX,	endY);
	vertices[1].Uv = D3DXVECTOR2(startX,	startY);
	vertices[2].Uv = D3DXVECTOR2(endX,		endY);
	vertices[3].Uv = D3DXVECTOR2(endX,		endY);
	vertices[4].Uv = D3DXVECTOR2(startX,	startY);
	vertices[5].Uv = D3DXVECTOR2(endX,		startY);

	// 실제 좌표
	float sizeX = (endX > 0) ? endX * (float)info.Width : (float)info.Width;
	sizeX -= startX * (float)info.Width;

	float sizeY = (endY > 0) ? endY * (float)info.Height : (float)info.Height;
	sizeY -= startY * (float)info.Height;

	textureSize = D3DXVECTOR2(sizeX, sizeY);

	//Default World
	scale = D3DXVECTOR2(1.0f, 1.0f);
	position = D3DXVECTOR2(0, 0);
	rotation = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixIdentity(&world);

	sWorld = shader->AsMatrix("World");
	sView = shader->AsMatrix("View");
	sProjection = shader->AsMatrix("Projection");
	sScalar = shader->AsScalar("Scalar");
	sScalar->SetBool(0);

	UpdateWorld();

	// Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;  // CPU 와 GPU의 읽기 쓰기 권한 설정
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

Sprite::~Sprite()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);

	Sprites::Remove(textureFile);
}

void Sprite::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	sView->SetMatrix(V);
	sProjection->SetMatrix(P);
}

void Sprite::Render()
{
	UINT stride = sizeof(Vertex); // 자를 크기
	UINT offset = 0;

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	shader->Draw(0, 0, 6);
}

void Sprite::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 & vec)
{
	position = vec;

	UpdateWorld();
}

void Sprite::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;

	UpdateWorld();
}

void Sprite::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Sprite::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;

	UpdateWorld();
}

void Sprite::RotationDegree(float x, float y, float z)
{
	RotationDegree(D3DXVECTOR3(x, y, z));
}

void Sprite::RotationDegree(D3DXVECTOR3 & vec)
{
	vec.x = Math::ToRadian(vec.x);
	vec.y = Math::ToRadian(vec.y);
	vec.z = Math::ToRadian(vec.z);

	Rotation(vec);
}

D3DXVECTOR3 Sprite::RotationDegree()
{
	D3DXVECTOR3 vec;
	vec.x = Math::ToDegree(rotation.x);
	vec.y = Math::ToDegree(rotation.y);
	vec.z = Math::ToDegree(rotation.z);
	
	return vec;
}

void Sprite::UpdateWorld()
{
	// aline all object
	D3DXMATRIX W, S, R, T;
	D3DXMatrixScaling(&S, textureSize.x * scale.x, textureSize.y * scale.y, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x + textureSize.x * 0.5f, position.y + textureSize.y * 0.5f, 0.0f);

	W = S * R * T;
	world = W;
	sWorld->SetMatrix(W);
}

//-----------------------------------------------------------------------------
// Sprites
//-----------------------------------------------------------------------------

map<wstring, Sprites::SpriteDesc> Sprites::spriteMap;

ID3D11ShaderResourceView * Sprites::Load(wstring file)
{
	if (spriteMap.count(file) > 0)
	{
		spriteMap[file].RefCount++;
		return spriteMap[file].SRV;
	}

	ID3D11ShaderResourceView* srv;
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		Device, file.c_str(), nullptr, nullptr, &srv, nullptr
	);
	assert(SUCCEEDED(hr));
	
	SpriteDesc desc;
	desc.RefCount++;
	desc.SRV = srv;

	spriteMap[file] = desc;

	return desc.SRV;
}

void Sprites::Remove(wstring file)
{
	UINT count = spriteMap.count(file);
	assert(count > 0);

	spriteMap[file].RefCount--;

	if (spriteMap[file].RefCount < 1)
	{
		SAFE_RELEASE(spriteMap[file].SRV);
		spriteMap.erase(file);
	}
}
