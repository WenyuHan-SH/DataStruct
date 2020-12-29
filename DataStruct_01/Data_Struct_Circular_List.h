#ifndef DATA_STRUCT_CIRCULAR_LIST_H
#define DATA_STRUCT_CIRCULAR_LIST_H
#include "Data_Struct_List_Base.h"

class CircularList :public List
{
public:
	// Í¨¹ý List ¼Ì³Ð
	CircularList(ListNode listNode) :m_pListNode(listNode) {}
	virtual bool ListEmpty() const;
	virtual void ClearList();
	virtual Status GetElem(const int iIndex, int& iElement) const;
	virtual int LocateElem(const int iElement) const;
	virtual Status ListInsert(const int iIndex, const int iElement);
	virtual Status ListDelete(const int iIndex, int& iElement);
	virtual int ListLength() const;
	virtual void PrintList() const;
	Status ListKillIndex(const int iIndex);
private:
	ListNode m_pListNode;
};

bool CircularList::ListEmpty() const
{
	return !m_pListNode;
}

void CircularList::ClearList()
{
	if (!ListEmpty())
	{
		ListNode freeListNode(nullptr);
		ListNode tempListNode(m_pListNode);
		do
		{
			freeListNode = tempListNode->pNext;
			free(tempListNode);
			tempListNode = freeListNode;
		} while (tempListNode->pNext);

		m_pListNode->pNext = nullptr;
	}
}

Status CircularList::GetElem(const int iIndex, int& iElement) const
{
	if (ListEmpty())
	{
		return ERROR;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext != m_pListNode && temp <= iIndex)
	{
		tempListNode = tempListNode->pNext;
		temp++;
	}
	iElement = tempListNode->m_idata;
	return OK;
}

int CircularList::LocateElem(const int iElement) const
{
	if (ListEmpty())
	{
		return 0;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext != m_pListNode)
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

Status CircularList::ListInsert(const int iIndex, const int iElement)
{
	if (ListEmpty())
	{
		return ERROR;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext != m_pListNode && temp < iIndex)
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

Status CircularList::ListDelete(const int iIndex, int& iElement)
{
	if (ListEmpty())
	{
		return ERROR;
	}
	int temp(1);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext != m_pListNode && temp <= iIndex)
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

Status CircularList::ListKillIndex(const int iIndex)
{
	if (ListEmpty())
	{
		return ERROR;
	}

	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext != tempListNode)
	{
		for (int i = 0; i < iIndex-1; i++)
		{
			tempListNode = tempListNode->pNext;
		}
		ListNode deleListNode = tempListNode->pNext;
		std::cout << deleListNode->m_idata << " ";
		tempListNode->pNext = deleListNode->pNext;
		free(deleListNode);
	}
	return OK;
}

int CircularList::ListLength() const
{
	int temp(0);
	ListNode tempListNode = m_pListNode;
	while (tempListNode->pNext != m_pListNode)
	{
		tempListNode = tempListNode->pNext;
		temp++;
	}
	return temp;
}

void CircularList::PrintList() const
{
	if (!ListEmpty())
	{
		ListNode tempListNode = m_pListNode;
		do
		{
			std::cout << tempListNode->m_idata << " ";
			tempListNode = tempListNode->pNext;
		} while (tempListNode != m_pListNode);
		std::cout << std::endl;
	}
}

#endif // !DATA_STRUCT_CIRCULAR_LIST_H

