#ifndef DATA_STRUCT_DUAL_LIST_H
#define DATA_STRUCT_DUAL_LIST_H
#include "Data_Struct_List_Base.h"
class DualList :public List
{
public:
	// Í¨¹ý List ¼Ì³Ð 
	virtual Status InitAlphabet(const int iAlphNum);
	virtual bool ListEmpty() const;
	virtual void ClearList();
	virtual Status GetElem(const int iIndex, int& iElement) const;
	virtual int LocateElem(const int iElement) const;
	virtual Status ListInsert(const int iIndex, const int iElement);
	virtual Status ListDelete(const int iIndex, int& iElement);
	virtual int ListLength() const;
	virtual void PrintList() const;
private:
	DuLinkList m_pListNode;
};

Status DualList::InitAlphabet(const int iAlphNum)
{
	DualNode* pTempDualNodeHead(nullptr);
	DualNode* pListHead(nullptr);
	pListHead = static_cast<DuLinkList>(malloc(sizeof(DualNode)));
	if (!pListHead)
	{
		return ERROR;
	}
	pListHead->next = nullptr;
	pListHead->prior = nullptr;
	pTempDualNodeHead = pListHead;
	for (int i = 0; i < iAlphNum; i++)
	{
		DualNode* pTempDualNode(nullptr);
		pTempDualNode = static_cast<DuLinkList>(malloc(sizeof(DualNode)));
		if (!pTempDualNode)
		{
			return ERROR;
		}
		pTempDualNode->data = 'A' + i;
		pTempDualNode->prior = pTempDualNodeHead;
		pTempDualNode->next = nullptr;
		pTempDualNodeHead->next = pTempDualNode;
		pTempDualNodeHead = pTempDualNode;
	}
	pListHead->next->prior = pTempDualNodeHead;
	pTempDualNodeHead->next = pListHead->next;
	m_pListNode = pListHead->next;
	free(pListHead);
	return OK;
}

bool DualList::ListEmpty() const
{
	return !m_pListNode;
}

void DualList::ClearList()
{
	if (!ListEmpty())
	{
		DuLinkList freeListNode(nullptr);
		DuLinkList tempListNode(nullptr);
		tempListNode = m_pListNode;
		do
		{
			freeListNode = tempListNode->next;
			free(tempListNode);
			tempListNode = freeListNode;
		} while (tempListNode);
	}
}

Status DualList::GetElem(const int iIndex, int& iElement) const
{
	return Status();
}

int DualList::LocateElem(const int iElement) const
{
	return 0;
}

Status DualList::ListInsert(const int iIndex, const int iElement)
{
	return Status();
}

Status DualList::ListDelete(const int iIndex, int& iElement)
{
	return Status();
}

int DualList::ListLength() const
{
	int iListSize(0);
	if (!ListEmpty())
	{
		auto tempListNode = m_pListNode;
		do
		{
			iListSize++;
			tempListNode = tempListNode->next;
		} while (tempListNode != m_pListNode);
	}
	return iListSize;
}

void DualList::PrintList() const
{
	if (!ListEmpty())
	{
		DuLinkList tempListNode = m_pListNode;
		do
		{
			std::cout << tempListNode->data << " ";
			tempListNode = tempListNode->next;
		} while (tempListNode != m_pListNode);
		std::cout << std::endl;
	}
}
#endif // !DATA_STRUCT_DUAL_LIST_H

