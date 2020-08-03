#pragma once

class Bird
{
public:
	Bird(D3DXVECTOR2 position);
	~Bird();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }
	Sprite* GetSprite() { return animation->GetSprite(); }
	void setMoveSpeed(float speed) { moveSpeed = speed; }
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	Animation* animation = nullptr;
	float moveSpeed = 220.0f;
};

