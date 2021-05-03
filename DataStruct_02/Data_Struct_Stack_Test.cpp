#include "Data_Struct_Stack_Point.h"
#include "Data_Struct_Stack_Array.h"

void BinToDec()
{
	auto spStackPoint = std::make_shared<StackPoint>();
	spStackPoint->InitStack();
	std::string sBin("");
	std::cout << "���������������" << std::endl;
	std::cin >> sBin;
	for (int i = 0; i < sBin.length(); ++i)
	{
		spStackPoint->Push(static_cast<ElemType>(sBin[i] - 48));
	}
	auto iLength = spStackPoint->StackLength();
	std::cout << "ջ�ĵ�ǰ�����ǣ�" << iLength << std::endl;
	ElemType iSum(0), iTemp(0);
	for (int i = 0; i < iLength; ++i)
	{
		spStackPoint->Pop(iTemp);
		iSum += iTemp * pow(2, i);
	}
	std::cout << "ת��Ϊʮ�������ǣ�" << iSum << std::endl;
	spStackPoint->DestroyStack();
}

void PostExpress()
{
	auto spStackPoint = std::make_shared<StackPoint>();
	spStackPoint->InitStack();
	char str[INCREMENT];
	int iIndex(0);
	std::cout << "�밴�沨�����ʽ������������ݣ������������֮���ÿո������" << std::endl;
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
				LogDevError("��������ĵ������ݹ���");
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
	std::cout << "���յļ�����Ϊ��" << result << std::endl;
}

void InfixExpress()
{
	auto spStackPoint = std::make_shared<StackPoint>();
	spStackPoint->InitStack();
	std::cout << "��������׺���ʽ����#��Ϊ������־��" << std::endl;
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
			LogDevError("��ʽ����");
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

//��n�����Ӵ�x����y�ƶ���z
void Move(int n, char x, char y, char z)
{
	if (1 == n)
	{
		std::cout << x << "-->" << z << std::endl;
	}
	else
	{
		Move(n - 1, x, z, y);						//��n-1�����Ӵ�x����z�ƶ���y;
		std::cout << x << "-->" << z << std::endl;	//����n�����Ӵ�x�ƶ���z�ϣ�
		Move(n - 1, y, x, z);						//��n-1�����Ӵ�y����x�ƶ���z;
	}
}

int count(0);
bool Danger(const int& colum, const int& row, int(*chess)[8])
{
	//��
	for (int i = 0; i < 8; i++)
	{
		if (chess[i][row])
		{
			return true;
		}
	}

	//���Ϸ�
	for (int i = colum, j = row; i >= 0 && j >= 0; i--, j--)
	{
		if (chess[i][j])
		{
			return true;
		}
	}

	//���·�
	for (int i = colum, j = row; i < 8 && j >= 0; i++, j--)
	{
		if (chess[i][j])
		{
			return true;
		}
	}

	//���Ϸ�
	for (int i = colum, j = row; i >= 0 && j < 8; i--, j++)
	{
		if (chess[i][j])
		{
			return true;
		}
	}

	//���·�
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
		std::cout << "�� " << count + 1 << "��" << std::endl;
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
		//�ж����λ���Ƿ���Σ��
		//���û��Σ�գ���������
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

