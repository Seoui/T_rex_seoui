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
	
	void SpawnGameOverSprite();
	void RemoveGameOverSprite();
	void setCrash(bool bCrash) { isCrash = bCrash; }
	bool Crash(bool bCrash);
	void Reset();

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	vector<Animation*> animation;
	vector<Sprite*> HIsprite;
	Sprite* gameOverSprite = nullptr;
	bool isCrash = false;
	float curGamePlayTime = 0.0f;
	float prevGamePlayTime = 0.0f;
};