#pragma once

#include<iostream>
#include<string>
using namespace std;

typedef long long INT64;
const INT64 MaxValue = 9223372036854775807;
const INT64 MinValue = -9223372036854775807;
const INT64 UN_INT = 0xcccccccccccccccc;
class BigData
{

public:
	BigData(const INT64 value=UN_INT)
		:_value(value)
	{
		_strData = "+";
		INT64 temp = _value;
		if (temp < 0)
		{
			_strData[0] = '-';
			temp = 0 - temp;
		}
		else if (temp == 0)
			_strData = "+0";
		while (temp != 0)
		{
			_strData += temp % 10 + '0';
			temp /= 10;
		}
		reverse(_strData.begin() + 1, _strData.end());
	}
	BigData::BigData(const string& strData)
		: _value(0)
		, _strData("+0")
	{
		if (strData.empty())
			return ;
		char *pData = (char *)strData.c_str();

		while (isblank(*pData))
			pData++;
		if (pData == '\0')
			return;
		char symbol = '+';
		if ('+' == *pData || '-' == *pData)
		{
			if (*pData == '-')
				symbol = '-';
			pData++;		
		}
		else if ('0' <= *pData || '9' >= *pData)
			symbol = '+';
		else
			return;

		while ('0' == *pData)
			pData++;

		if (pData == '\0')
			return;

		_strData.resize(strlen(pData) + 1);
		_strData[0] = symbol;
		size_t count = 1;
		while (*pData <= '9'&&*pData >= '0')
		{
			_value = _value * 10 + *pData - '0';
			_strData[count] = *pData;
			count++;
			pData++;
		}
		if (symbol == '-')
			_value = 0 - _value;
	}

	friend ostream&operator<<(ostream &_cout,  BigData& b)
	{
		char *pData = (char *)b._strData.c_str();
		if (*pData == '+')
			pData++;
		_cout << pData;
		return _cout;
	}

	BigData operator+(BigData &b);
	BigData operator-(BigData &b);
	BigData operator*(BigData &b);
	BigData operator/(BigData &b);

	bool isLeftBig(char* left, size_t Lsize, char* right, size_t Rsize)
	{
		if (Lsize > Rsize)
			return true;
		if (Lsize == Rsize&&strncmp(left, right, Rsize) >= 0)
			return true;
		return false;
	}

	char loopsub(char*& left, size_t& Lsize, char*& right, size_t Rsize)
	{
		char count = '0';
		while (isLeftBig(left, Lsize, right, Rsize))
		{
			for (size_t i = 0; i < Lsize; i++)
			{
				char temp = left[Lsize - 1 - i] - '0';
				if (i < Rsize)
					temp -= (right[Rsize - i - 1] - '0');
				if (temp < 0)
				{
					size_t step = 1;
					while ((1 + i + step < Lsize) && left[Lsize - 1 - i - step] == 0)
					{
						left[Lsize - 1 - i - step] = '9';
						step++;
					}
					left[Lsize - 1 - i - step]--;
					temp += 10;
				}
				left[Lsize - i - 1] = temp + '0';
			}
			count++;
			while (Lsize > 0 && *left == '0') //去除前面的0
			{
				left++;
				Lsize--;
			}
		}
		return count;
	}

private:
	bool IsINT64Overflow()
	{
		string temp("9223372036854775807");
		if (_strData[0] == '-')
			temp = "-9223372036854775808";
		if (_strData.size() < temp.size())
			return false;
		else if (_strData.size() == temp.size() && _strData < temp)
			return false;
		return true;
	}

	string Add(string left, string right);
	string Sub(string left, string right);
	string Mul(string left, string right);
	string Div(string left, string right);

private:
	INT64 _value;
	std::string _strData;
};
