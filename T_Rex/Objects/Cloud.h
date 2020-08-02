#pragma once

class Cloud
{
public:
	Cloud(D3DXVECTOR2 position);
	~Cloud();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	
	Sprite* sprite = nullptr;
	float moveSpeed = 50.0f;
};