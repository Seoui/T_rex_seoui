#pragma once
#include "Viewer/IFollowing.h"

class T_rex : public IFollowing
{
public:
	T_rex(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~T_rex();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Sprite* GetSprite();

	void Jump();
	void Landing();
	void Physics();

private:
	// IFollowing을(를) 통해 상속됨
	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;

private:
	Animation* animation;
	D3DXVECTOR2 focusOffset;
	D3DXVECTOR2 startPosition;
	
	float jumpSpeed = 0;
	float jumpTime = 0;
	float jumpHeight = 0;
	float GravityAcceleration = -3.0f;

};
