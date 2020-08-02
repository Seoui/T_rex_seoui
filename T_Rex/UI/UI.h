#pragma once

class UI
{
public:
	UI(D3DXVECTOR2 position);
	~UI();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	vector<Animation*> animation;
	//HX 최고점수 저장
};