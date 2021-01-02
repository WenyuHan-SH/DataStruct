#ifndef DATA_STRUCT_LIST_DEFINE_H
#define DATA_STRUCT_LIST_DEFINE_H
#include <iostream>

#define			OK			1
#define			ERROR		0
#define			OVERFLOW	-1

typedef			int			Status;
typedef			int			ElemType;

#define			MAX_SIZE			1000
#define			ACCURACY_ERROR		1e-6

#define			INSERT_MIN_NUMBER	1
#define			INSERT_MAX_NUMER	10
#define			DELETE_INDEX		1
#define			GET_INDEX			3
//顺序表

typedef struct SqNode
{
	ElemType m_eData[MAX_SIZE];
	unsigned int m_uiLength;
} SqNode,*SqListNode;

//单链表
typedef struct SnlNode
{
	ElemType m_eData;
	SnlNode* m_pNext;
} SnlNode, * SnlListNode;

//静态链表
typedef struct StaNode
{
	ElemType m_eData;
	unsigned int m_uiCur;
}StaNode, StaLinkList[MAX_SIZE];

//双向循环链表
typedef struct DulNode
{
	ElemType m_eData;
	DulNode* m_pPre;
	DulNode* m_pNext;
}DulNode, * DulLinkList;

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
#endif // !DATA_STRUCT_LIST_DEFINE_H
