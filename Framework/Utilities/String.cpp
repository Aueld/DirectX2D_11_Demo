#include "Framework.h"
#include "String.h"

#include <iomanip>	// 입출력 스트림의 조작자를 정의하는 헤더, 스트림의 출력 형식을 제어하는 데 사용
#include <sstream>	// 문자열 스트림을 정의, 메모리 버퍼에 데이터를 읽고 쓰는데 사용
#include <atlconv.h>

// 문자열을 지정된 구분자로 분할하는 기능
#pragma region SplitString
void String::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();
	int cutAt = 0; //자를 위치
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크다면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은것이 있다면
		result->push_back(origin.substr(0, cutAt));
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //자를 위치
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크다면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은것이 잇다면
		result->push_back(origin.substr(0, cutAt));
}
#pragma endregion

// 특정한 문자로 시작하는지 체크
#pragma region StartWith
bool String::StartWith(string str, string comp)
{
	//npos no position 즉 없다는 소리
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool String::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;
	return false;
}
#pragma endregion

// 특정한 문자를 포함하는지 체크
#pragma region Contain
bool String::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}
#pragma endregion

// 특정한 문자들을 다른 문자들로 대체
#pragma region Replace
void String::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

void String::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}
#pragma endregion

// 벡터를 문자열로 바꿔서 출력
#pragma region ToString
// setprecision : 부동 소수점 숫자의 정밀도를 설정하는 조작자

string String::ToString(D3DXVECTOR3 vec3, int precision)
{
	string temp;
	stringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = "X : " + stream1.str() + " Y : " + stream2.str()
		 + " Z : " + stream3.str();
	return temp;
}

wstring String::ToWstring(D3DXVECTOR3 vec3, int precision)
{
	wstring temp;
	wstringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = L"X : " + stream1.str() + L" Y : " + stream2.str()
		 + L" Z : " + stream3.str();
	return temp;
}
#pragma endregion

// string -> wstring
wstring String::ToWstring(string str)
{
	USES_CONVERSION;
	//wstring temp = L"";
	//temp.assign(str.begin(), str.end());
	//return temp;
	wstring temp = A2W(str.c_str());
	return temp;
}

// wstring -> string
string String::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());
	return temp;
}