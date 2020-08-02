#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		up.set(i, false);
		down.set(i, false);
	}
}

// up.set(i) : i의 값을 세팅 (true or false)
// up.reset() : 인덱스의 값을 false로 세팅
// up.flip() : 비트값을 반대로 변환시켜줌(false->true, true->false)
// up.all() : 모든 원소의 값이 true이면 true반환    and연산
// up.none() : 모든 원소의 값이 false이면 true반환     and연산
// up.any() : 한 개의 원소라도true이면 true         or연산
// up.count() : true의 개수를 리턴

Keyboard::~Keyboard()
{

}

bool Keyboard::Down(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (down[key] == false)
		{
			down.set(key, true);
			return true;
		}
	}
	else
	{
		down.set(key, false);
	}

	return false;
}

bool Keyboard::Up(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		up.set(key, true);
	}
	else
	{
		if (up[key] == true)
		{
			up.set(key, false);
			return true;
		}
	}

	return false;
}

bool Keyboard::Press(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	return false;
}

bool Keyboard::Toggle(int key)
{
	if (GetAsyncKeyState(key) & 0x0001) // toggle 판단하는 마스크 값
		return true;

	return false;
}
