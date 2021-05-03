#ifndef DATA_STRUCT_STACK_DEFINE
#define DATA_STRUCT_STACK_DEFINE
#include <iostream>

#define			OK			1
#define			ERROR		0
#define			OVERFLOW	-1

const int MAXSIZE = 1000000;
const int INCREMENT = 100;

typedef			int				Status;
typedef			char			ElemType;

typedef struct
{
	ElemType* base;
	ElemType* top;
	int stackSize;
}SqStackPoint;

typedef struct
{
	ElemType data[MAXSIZE];
	int top;
}SqStackArray;

void LogDevInfo(const std::string sInfo)
{
	std::cout << "Info:" << sInfo << std::endl;
}

void LogDevWarning(const std::string sInfo)
{
	std::cout << "Warning:" << sInfo << std::endl;
}

void LogDevError(const std::string sInfo)
{
	std::cout << "Error:" << sInfo << std::endl;
}
#endif // !DATA_STRUCT_STACK_DEFINE

