#ifndef DATA_STRUCT_Link_LIST_H
#define DATA_STRUCT_Link_LIST_H
#include "Data_Struct_List_Base.h"

class LinkList :public List
{
public:
	LinkList(ListNode pListNode) :m_pListNode(pListNode) {}
	virtual ~LinkList() {}
	virtual bool ListEmpty() const;
	virtual void ClearList();
	virtual Status GetElem(const int iIndex, int& iElement) const;
	virtual int LocateElem(const int iElement) const;
	virtual Status ListInsert(const int iIndex, const int iElement);
	virtual Status ListDelete(const int iIndex, int& iElement);
	virtual int ListLength() const;
	virtual void PrintList()  const;
private:
	ListNode m_pListNode;
};

bool LinkList::ListEmpty() const
{
	return !m_pListNode->pNext;
}

void LinkList::ClearList()
{
	if (!ListEmpty())
	{
		ListNode freeListNode;
		ListNode tempListNode = m_pListNode->pNext;
		while (tempListNode)
		{
			freeListNode = tempListNode->pNext;
			free(tempListNode);
			tempListNode = freeListNode;
		}
		m_pListNode->pNext = nullptr;
	}
}

Status LinkList::GetElem(const int iIndex, int& iElement) const
{
	if (ListEmpty())
	{
		return ERROR;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext && temp <= iIndex)
	{
		tempListNode = tempListNode->pNext;
		temp++;
	}
	iElement = tempListNode->m_idata;
	return OK;
}

int LinkList::LocateElem(const int iElement) const
{
	if (ListEmpty())
	{
		return 0;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext)
	{
		if (iElement == tempListNode->pNext->m_idata)
		{
			return temp;
		}
		tempListNode = tempListNode->pNext;
		temp++;
	}
	return 0;
}

Status LinkList::ListInsert(const int iIndex, const int iElement)
{
	if (ListEmpty())
	{
		return ERROR;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext && temp < iIndex)
	{
		tempListNode = tempListNode->pNext;
		temp++;
	}
	ListNode newListNode = (ListNode)malloc(sizeof(Node));
	newListNode->m_idata = iElement;
	newListNode->pNext = tempListNode->pNext;
	tempListNode->pNext = newListNode;
	return OK;
}

Status LinkList::ListDelete(const int iIndex, int& iElement)
{
	if (ListEmpty())
	{
		return ERROR;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext && temp <= iIndex)
	{
		tempListNode = tempListNode->pNext;
		temp++;
	}
	ListNode deleListNode = tempListNode->pNext;
	tempListNode->pNext = deleListNode->pNext;
	iElement = deleListNode->m_idata;
	free(deleListNode);
	return OK;
}

int LinkList::ListLength() const
{
	int temp(0);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext)
	{
		tempListNode = tempListNode->pNext;
		temp++;
	}
	return temp;
}

void LinkList::PrintList() const
{
	if (!ListEmpty())
	{
		ListNode tempListNode = m_pListNode;
		while (tempListNode->pNext)
		{
			std::cout << tempListNode->pNext->m_idata << " ";
			tempListNode = tempListNode->pNext;
		}
		std::cout << std::endl;
	}
}
#endif // !DATA_STRUCT_SQ_LIST_H