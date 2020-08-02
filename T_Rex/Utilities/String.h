#pragma once

class String 
{
public:
	static wstring ToWString(string value);
	static string ToString(wstring value);

private:
};