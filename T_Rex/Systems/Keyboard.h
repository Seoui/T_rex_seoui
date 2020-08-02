#pragma once

#define KEYMAX 256

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	bool Down(int key);
	bool Up(int key);
	bool Press(int Key);
	bool Toggle(int key);

private:
	bitset<KEYMAX> up; //bool up[256]
	bitset<KEYMAX> down;

};