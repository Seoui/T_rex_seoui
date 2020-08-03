#pragma once

class Moon
{
public:
	Moon(D3DXVECTOR2 position);
	~Moon();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Play(int num) { animation->Play(num); }
	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	Animation* animation = nullptr;
	float moveSpeed = 50.0f;

};