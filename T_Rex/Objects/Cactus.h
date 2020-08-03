#pragma once

class Cactus
{
public:
	Cactus(D3DXVECTOR2 position, float startX, float startY, float endX, float endY);
	~Cactus();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }
	Sprite* GetSprite() { return sprite; }
	void setMoveSpeed(float speed) { moveSpeed = speed; }

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	
	Sprite* sprite = nullptr;
	float moveSpeed = 220.0f;
};

