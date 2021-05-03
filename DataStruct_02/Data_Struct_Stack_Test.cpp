#include "Data_Struct_Stack_Point.h"
#include "Data_Struct_Stack_Array.h"

void BinToDec()
{
	auto spStackPoint = std::make_shared<StackPoint>();
	spStackPoint->InitStack();
	std::string sBin("");
	std::cout << "请输入二进制数：" << std::endl;
	std::cin >> sBin;
	for (int i = 0; i < sBin.length(); ++i)
	{
		spStackPoint->Push(static_cast<ElemType>(sBin[i] - 48));
	}
	auto iLength = spStackPoint->StackLength();
	std::cout << "栈的当前容量是：" << iLength << std::endl;
	ElemType iSum(0), iTemp(0);
	for (int i = 0; i < iLength; ++i)
	{
		spStackPoint->Pop(iTemp);
		iSum += iTemp * pow(2, i);
	}
	std::cout << "转换为十进制数是：" << iSum << std::endl;
	spStackPoint->DestroyStack();
}

void PostExpress()
{
	auto spStackPoint = std::make_shared<StackPoint>();
	spStackPoint->InitStack();
	char str[INCREMENT];
	int iIndex(0);
	std::cout << "请按逆波兰表达式输入待计算数据，数据与运算符之间用空格隔开：" << std::endl;
	char c = getchar();
	ElemType dLeft(0.0), dRight(0.0), dTemp(0);
	while ('#' != c)
	{
		while (isdigit(c) || '.' == c)
		{
			str[iIndex++] = c;
			str[iIndex] = '\0';
			if (INCREMENT <= iIndex)
			{
				LogDevError("出错，输入的单个数据过大");
				return;
			}
			c = getchar();
			if (' ' == c)
			{
				dTemp = atof(str);
				spStackPoint->Push(dTemp);
				iIndex = 0;
				break;
			}
		}
		switch (c)
		{
		case'+':
			spStackPoint->Pop(dLeft);
			spStackPoint->Pop(dRight);
			spStackPoint->Push(dRight + dLeft);
			break;
		case'-':
			spStackPoint->Pop(dLeft);
			spStackPoint->Pop(dRight);
			spStackPoint->Push(dRight - dLeft);
			break;
		case'*':
			spStackPoint->Pop(dLeft);
			spStackPoint->Pop(dRight);
			spStackPoint->Push(dRight * dLeft);
			break;
		case'/':
			spStackPoint->Pop(dLeft);
			spStackPoint->Pop(dRight);
			if (abs(dLeft) < 1e-6)
			{
				LogDevError("dLeft is 0!");

			}
			else
			{
				spStackPoint->Push(dRight / dLeft);
			}
			break;
		}
		c = getchar();
	}
	ElemType result(0.0);
	spStackPoint->GetTop(result);
	std::cout << "最终的计算结果为：" << result << std::endl;
}

void InfixExpress()
{
	auto spStackPoint = std::make_shared<StackPoint>();
	spStackPoint->InitStack();
	std::cout << "请输入中缀表达式，以#作为结束标志：" << std::endl;
	char c = getchar();
	while ('#' != c)
	{
		while (c >= '0' && c <= '9')
		{
			std::cout << c;
			c = getchar();
			if (c < '0' || c > '9')
			{
				std::cout << " ";
			}
		}

		if (')' == c)
		{
			ElemType temp;
			spStackPoint->Pop(temp);
			while ('(' != temp)
			{
				std::cout << temp << " ";
				spStackPoint->Pop(temp);
			}
		}
		else if ('+' == c || '-' == c)
		{
			if (!spStackPoint->StackLength())
			{
				spStackPoint->Push(c);
			}
			else
			{
				ElemType temp;
				do
				{
					spStackPoint->Pop(temp);
					if ('(' == temp)
					{
						spStackPoint->Push(temp);
					}
					else
					{
						std::cout << temp << " ";
					}
				} while (spStackPoint->StackLength() && '(' != temp);
				spStackPoint->Push(c);
			}
		}
		else if ('*' == c || '/' == c || '(' == c)
		{
			spStackPoint->Push(c);
		}
		else if ('#' == c)
		{
			break;
		}
		else
		{
			LogDevError("格式错误");
			return;
		}

		c = getchar();
	}

	while (spStackPoint->StackLength())
	{
		ElemType temp;
		spStackPoint->Pop(temp);
		std::cout << temp << " ";
	}
}

void print()
{
	char a = getchar();
	if ('#' != a)
	{
		print();
	}
	if ('#' != a)
	{
		std::cout << a;
	}
}

//将n个盘子从x借助y移动到z
void Move(int n, char x, char y, char z)
{
	if (1 == n)
	{
		std::cout << x << "-->" << z << std::endl;
	}
	else
	{
		Move(n - 1, x, z, y);						//将n-1个盘子从x借助z移动到y;
		std::cout << x << "-->" << z << std::endl;	//将第n个盘子从x移动到z上；
		Move(n - 1, y, x, z);						//将n-1个盘子从y借助x移动到z;
	}
}

int count(0);
bool Danger(const int& colum, const int& row, int(*chess)[8])
{
	//列
	for (int i = 0; i < 8; i++)
	{
		if (chess[i][row])
		{
			return true;
		}
	}

	//左上方
	for (int i = colum, j = row; i >= 0 && j >= 0; i--, j--)
	{
		if (chess[i][j])
		{
			return true;
		}
	}

	//左下方
	for (int i = colum, j = row; i < 8 && j >= 0; i++, j--)
	{
		if (chess[i][j])
		{
			return true;
		}
	}

	//右上方
	for (int i = colum, j = row; i >= 0 && j < 8; i--, j++)
	{
		if (chess[i][j])
		{
			return true;
		}
	}

	//右下方
	for (int i = colum, j = row; i < 8 && j < 8; i++, j++)
	{
		if (chess[i][j])
		{
			return true;
		}
	}

	return false;
}

void EightQueen(const int& colum, const int& row, int(*chess)[8])
{
	int tempChess[8][8] = { 0 };
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			tempChess[i][j] = chess[i][j];
		}
	}

	if (8 == colum)
	{
		std::cout << "第 " << count + 1 << "种" << std::endl;
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				std::cout << tempChess[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		count++;
	}
	else
	{
		//判断这个位置是否有危险
		//如果没有危险？继续往下
		for (int j = 0; j < row; ++j)
		{
			if (!Danger(colum, j, tempChess))
			{
				for (int i = 0; i < 8; i++)
				{
					tempChess[colum][i] = 0;
				}
				tempChess[colum][j] = 1;
				EightQueen(colum + 1, row, tempChess);
			}
		}
	}
}

//KMP
void Get_Next(const std::string& t, int* next)
{
	int i(0), j(-1);
	int tSize = t.size();
	next[0] = -1;
	while (i < tSize-1)
	{
		if (-1 == j || t[i] == t[j])
		{
			++i;
			++j;
			t[i] != t[j] ? next[i] = j : next[i] = next[j];
		}
		else
		{
			j = next[j];
		}
	}
}

int Index_KMP(const std::string& s, const std::string& t, const int& pos)
{
	int indexS(pos), indexT(0), sSize(s.size()), tSize(t.size());
	int next[255] = { 0 };
	Get_Next(t, next);
	while (indexS < sSize && indexT < tSize)
	{
		if (-1 == indexT || s[indexS] == t[indexT])
		{
			indexS++;
			indexT++;
		}
		else
		{
			indexT = next[indexT];
		}
	}

	return indexT == t.size() ? indexS - indexT : -1;
}

int main()
{
	//BinToDec();
	//PostExpress();
	//InfixExpress();
	//print();
	//Move(3, 'A', 'B', 'C');
	//int Chess[8][8] = { 0 };
	//EightQueen(0, 8, Chess);
	std::string s = "ababaaaba";
	std::string t = "ababaaaba";
	std::cout << "index is :" << Index_KMP(s, t, 0);
	return EXIT_SUCCESS;
}

