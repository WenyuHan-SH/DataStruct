#ifndef Data_STRUCT_LIST_BASE_H_
#define Data_STRUCT_LIST_BASE_H_
#include <iostream>

namespace
{
	#define MAX_SIZE 20

	#define OK 1
	#define ERROR 0
	#define TRUE 1
	#define FALSE 0
	typedef int Status;
	typedef int ElemType;

	typedef struct Node
	{
		ElemType m_idata;
		Node* pNext;
	} Node, * ListNode;

	typedef struct
	{
		ElemType m_idata[MAX_SIZE];
		int m_iLength;
	} SQListNode;

	#define MAXSIZE 1000
	#define STATIC_LIST_LENGTH 10
	typedef struct
	{
		ElemType data;
		int cur;
	}Component, StatciLinkList[MAXSIZE];

	typedef struct DualNode
	{
		char data;
		struct DualNode* prior;
		struct DualNode* next;
	}DualNode, * DuLinkList;
}

class List
{
public:
	List() {}
	virtual ~List() {}
	virtual bool ListEmpty() const = 0;
	virtual void ClearList() = 0;
	virtual Status GetElem(const int iIndex, int& iElement) const = 0;
	virtual int LocateElem(const int iElement) const = 0;
	virtual Status ListInsert(const int iIndex, const int iElement) = 0;
	virtual Status ListDelete(const int iIndex, int& iElement) = 0;
	virtual int ListLength()  const = 0;
	virtual void PrintList()  const = 0;
	virtual void UnionList(List* const pList);
};

void List::UnionList(List* const pList)
{
	for (int index = 1; index <= pList->ListLength(); ++index)
	{
		int iTemp;
		if (pList->GetElem(index, iTemp))
		{
			if (!LocateElem(iTemp))
			{
				ListInsert(ListLength(), iTemp);
			}
		}
	}
}
#endif // !Data_STRUCT_LIST_BASE_H_
