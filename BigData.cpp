#include"BigData.h"



BigData BigData::operator+( BigData &b)
{
	if (!IsINT64Overflow() && !b.IsINT64Overflow())
	{
		if (_strData[0] != b._strData[0])
			return BigData(_value + b._value);
		else if (_strData[0] == '+'&&MaxValue - _value >= b._value
			|| _strData[0] == '-'&&MinValue - _value <= b._value)
			return BigData(_value + b._value);
	}
	if (_strData[0] == b._strData[0])  //处理同号
		return BigData(Add(_strData, b._strData));
	//到这必然是异号向加                           
	if ('+' == _strData[0])//正数加负数 结果为正：5+（-3）相当于5-3  
		//             结果为负：5+（-7）相当于5-7  
	{					//	           都是把b._strData符号变为正号
		BigData b1(b._strData);
		b1._strData[0] = '+';
		return BigData(Sub(_strData, b1._strData)); //处理异号相当于减法
	}
	else if ('-' == _strData[0])   // 负数加正数  结果为正： -5+7  相当于 7-5
	{							  //             结果为负： -5+3  相当于 3-5
		BigData b1(_strData);
		b1._strData[0] = '+';       //             都是把_strData变为正数，左右操作数互换
		return BigData(Sub(b._strData, b1._strData));
	}
}

string BigData::Add(string left, string right)
{
	int Lsize = left.size() ;
	int Rsize = right.size() ;

	if (Lsize<Rsize)
	{
		std::swap(left, right);
		std::swap(Lsize, Rsize);
	}

	string strRet;
	strRet.resize(Lsize + 1);
	strRet[0] = left[0];

	char step = 0;
	for(int idx = 1; idx < Lsize; ++idx)
	{
		char temp = left[Lsize - idx] - '0' + step;
		if (idx < Rsize)
			temp += right[Rsize - idx] - '0';
		step = temp / 10;
		strRet[Lsize + 1 - idx] = temp % 10 + '0';
	}


	strRet[1] = step + '0';
	return strRet;
}

string BigData::Sub(string left, string right)
{
	int Lsize = left.size();
	int Rsize = right.size();
	char symbol = '+';
	if (Lsize<Rsize ||                            //左操作数比右操作数短
		(Lsize == Rsize && left<right))
	{
		std::swap(left, right);
		std::swap(Lsize, Rsize);
		if (right[0] == '+')        //结果的符号号总是与右边的值得符号相反
			symbol = '-';
	}
	std::string strRet;
	strRet.resize(Lsize);
	strRet[0] = symbol;
	for (int idx = 1; idx < Lsize; ++idx)
	{
		char temp = left[Lsize - idx] - '0' ;
		if (idx < Rsize)
			temp -= right[Rsize - idx] - '0';
		if (temp < 0)
		{
			left[Lsize - idx - 1] -= 1;
			temp += 10;
		}
		strRet[Lsize - idx] = temp + '0';
	}
	return strRet;
}

//string BigData::Add(string left, string right)
//{
//	size_t Lsize = left.size();
//	size_t Rsize = right.size();
//	if (Lsize < Rsize)
//	{
//		std::swap(Lsize, Rsize);
//		std::swap(left, right);
//	}
//	string res;
//	res.resize(Lsize + 1);//可能最后产生进位
//	res[0] = left[0];
//	char takeover = 0;//进位
//	for (size_t idx = 1; idx < Lsize; ++idx)
//	{
//		char temp = left[Lsize - idx] - '0' + takeover;
//		if (Rsize > idx)
//			temp += right[Rsize - idx] - '0';
//		takeover = temp / 10;
//		res[Lsize + 1 - idx] = temp % 10 + '0';
//	}
//	res[1] = takeover + '0';
//	return res;
//}
//string BigData::Sub(string left, string right)
//{
//	size_t Lsize = left.size();
//	size_t Rsize = right.size();
//	if (Lsize < Rsize || (Lsize == Rsize && strcmp(left.c_str() + 1, right.c_str() + 1) < 0))
//	{
//		std::swap(Lsize, Rsize);
//		std::swap(left, right);
//	}
//	string res;
//	res.resize(Lsize);// 减去不可能产生进位
//	res[0] = left[0];
//	for (size_t idx = 1; idx < Lsize; ++idx)
//	{
//		char temp = left[Lsize - idx] - '0';
//		if (Rsize > idx)
//			temp -= right[Rsize - idx] - '0';
//		if (temp < 0)
//		{
//			int step = 1;//向前step位借位
//			while ((Lsize >(idx + step)) && left[Lsize - idx - step] == 0)
//			{
//				left[Lsize - idx - step] = '9';
//				step++;
//			}
//			left[Lsize - idx - step]--; //不为0时 要-1
//			temp += 10;
//		}
//		res[Lsize - idx] = temp % 10 + '0';
//	}
//	return res;
//}

BigData BigData::operator-(BigData &b)
{
	if (!IsINT64Overflow() && !b.IsINT64Overflow())
	{
		if (_strData[0] == b._strData[0])
			return BigData(_value - b._value);
		else if (_strData[0] == '+'&&MaxValue + b._value >= _value
			|| _strData[0] == '-'&&MinValue + b._value <= _value)
			return BigData(_value - b._value);
	}
	if (_strData[0] == '+' && b._strData[0] == '+')
		return BigData(Sub(_strData, b._strData));
	//异号相减  正数减负数   结果为正 5 - （-7）= 5+7   5-（-3）= 5+3 5-（-12） = 5+12
	else if (_strData[0] == '-' && b._strData[0] == '-')
	{
		BigData b1(_strData);
		BigData b2(b._strData);
		b1._strData[0] = '+';
		b2._strData[0] = '+';
		return BigData(Sub(b2._strData, b1._strData));
	}
	else if ('+' == _strData[0])
	{
		BigData b1(b._strData);        //相当于把b._strData变为正数相加
		b1._strData[0] = '+';
		return BigData(Add(_strData, b1._strData));
	}
	else  //   负数减正数   结果为负  -5 -7 = -（5+7） = -5 +(-7)
	{
		BigData b1(b._strData);
		b1._strData[0] = '-';             //相当于把b._strData变为负数相加
		return BigData(Add(_strData, b1._strData));
	}

}
BigData BigData::operator*(BigData &b)
{
	if (_value == 0 || b._value == 0)
		return BigData('0');
	if (strcmp(_strData.c_str() + 1, "1") == 0)
		return BigData(b._strData);
	if (strcmp(b._strData.c_str() + 1, "1") == 0)
		return BigData(b._strData);
	return BigData(Mul(_strData, b._strData));
}

string BigData::Mul(string left, string right)
{
	int Lsize = left.size();
	int Rsize = right.size() ;
	if (Lsize<Rsize)
	{
		std::swap(left, right);
		std::swap(Lsize, Rsize);
	}
	size_t retsize=Lsize +Rsize-1;
	string strRet(retsize, '0');
	char step = 0;
	size_t offset = 0;
	for(int i = 1; i < Lsize; ++i)
	{
		char cleft = left[Lsize - i] - '0';
		step = 0;
		for (int j = 1; j < Rsize; ++j)
		{
			char retbit = strRet[retsize - offset - j] - '0';
			char mulbit = (right[Rsize - j] - '0') * cleft + step + retbit;
			step = mulbit / 10;
			strRet[retsize - offset - j] = mulbit % 10 + '0';
		}
		offset++;
	}
	
	strRet[1] = step + '0';
	if (left[0] != right[0])
		strRet[0] = '-';
	else
		strRet[0] = '+';
	return strRet;
}




BigData BigData::operator/(BigData &b)
{
	char *left = (char *)_strData.c_str();
	char *right = (char *)b._strData.c_str();
	if (b._value == 0)
		cout << "无意义" << endl;
	if (_strData.size() < b._strData.size())
		return BigData(0);
	else if (_strData.size() == b._strData.size() &&
		strcmp(_strData.c_str() + 1, b._strData.c_str() + 1) < 0)
		return BigData(0);
	if (strcmp(left, right) == 0)
		return BigData(1);
	//商值为-1
	if (strcmp(_strData.c_str() + 1, b._strData.c_str() + 1) == 0 && *left != *right)
		return BigData(-1);

	else if (b._value == 1) //被除数为1
		return BigData(_strData);
	else if (b._value == -1) //被除数为-1
		return BigData(b._strData);

	return BigData(Div(_strData, b._strData));
}


string BigData::Div(string left, string right)
{
	char symbol = '+';
	if (left[0] != right[0])
		symbol = '-';
	size_t Lsize = left.size() - 1;
	size_t Rsize = right.size() - 1;
	string strRet;
	strRet.append(1, symbol);
	char *pLeft = (char *)left.c_str() + 1;
	char *pRight = (char *)right.c_str() + 1;
	size_t len = Rsize;

	while (*(pLeft + len - 1) != '\0')
	{
		if (!isLeftBig(pLeft, len, pRight, Rsize))
		{
			len++;
			strRet.append(1, '0');
			continue;
		}
		else
		{

			strRet.append(1, loopsub(pLeft, len, pRight, Rsize));
			len++;
		}
	}
	return strRet;
}
