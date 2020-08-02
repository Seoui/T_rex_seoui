#pragma once
#include "Camera.h"
#include "IFollowing.h"

class Following : public Camera
{
public:
	Following(IFollowing* focus = nullptr);
	~Following();

	void Update();
	void Change(IFollowing* focus);

private:
	IFollowing* focus;

};