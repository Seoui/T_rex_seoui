#include "stdafx.h"
#include "String.h"

wstring String::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());
	// assign은 value를 모두 복사해서 temp에 저장한다

	return temp;
}

string String::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
