#ifndef DATA_STRUCT_LIST_SNLLIST_H
#define DATA_STRUCT_LIST_SNLLIST_H
#include "Data_Struct_List_Base.h"

class SnlList :public List
{
public:
	// Í¨¹ý List ¼Ì³Ð
	virtual Status InitList() override;
	virtual Status DestroyList() override;
	virtual Status ClearList() override;
	virtual int ListLength()  const override;
	virtual Status GetElem(const int iIndex, ElemType& eData) const override;
	virtual int LocateElem(const ElemType& eData, bool(*Compare)(ElemType, ElemType)) const override;
	virtual Status ListInsert(const int iIndex, const ElemType& eData) override;
	virtual Status ListDelete(const int iIndex, ElemType& eData) override;
private:
	SnlListNode m_pListNode;
};

Status SnlList::InitList()
{
	DestroyList();
	m_pListNode = static_cast<SnlListNode>(malloc(sizeof(SnlNode)));
	if (!m_pListNode)
	{
		LogDevError("InitList failed");
		return OVERFLOW;
	}
	m_pListNode->m_eData = 0;
	m_pListNode->m_pNext = nullptr;
	return OK;
}

Status SnlList::DestroyList()
{
	SnlListNode pTempNode(nullptr), pFreeNode(nullptr);
	pFreeNode = m_pListNode;
	while (pFreeNode)
	{
		pTempNode = pFreeNode->m_pNext;
		free(pFreeNode);
		pFreeNode = pTempNode;
	}
	m_pListNode = nullptr;
	return OK;
}

Status SnlList::ClearList()
{
	SnlListNode pTempNode(nullptr), pFreeNode(nullptr);
	pFreeNode = m_pListNode->m_pNext;
	while (pFreeNode)
	{
		pTempNode = pFreeNode->m_pNext;
		free(pFreeNode);
		pFreeNode = pTempNode;
	}
	m_pListNode->m_pNext = nullptr;
	return OK;
}

int SnlList::LocateElem(const ElemType& eData, bool(*Compare)(ElemType, ElemType)) const
{
	if (ListEmpty())
	{
		LogDevError("SnlList is empty");
		return 0;
	}
	int iLocate(1);
	SnlListNode pTempNode = m_pListNode;
	while (pTempNode->m_pNext)
	{
		pTempNode = pTempNode->m_pNext;
		if (Compare(eData, pTempNode->m_eData))
		{
			return iLocate;
		}
		iLocate++;
	}
	return 0;
}

Status SnlList::GetElem(const int iIndex, ElemType& eData) const
{
	if (ListEmpty())
	{
		LogDevError("SnlList is empty");
		return ERROR;
	}
	int iLocate(1);
	SnlListNode pTempNode = m_pListNode;
	while (pTempNode->m_pNext && iLocate <= iIndex)
	{
		pTempNode = pTempNode->m_pNext;
		iLocate++;
	}
	eData = pTempNode->m_eData;
	return OK;
}

Status SnlList::ListInsert(const int iIndex, const ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength() + 1)
	{
		LogDevError("Out of list");
		return ERROR;
	}
	int iLocate(1);
	SnlListNode tempListNode = m_pListNode;
	while (tempListNode->m_pNext && iLocate <= iIndex)
	{
		tempListNode = tempListNode->m_pNext;
		iLocate++;
	}
	SnlListNode snlListNode = static_cast<SnlListNode>(malloc(sizeof(SnlNode)));
	snlListNode->m_eData = eData;
	snlListNode->m_pNext = tempListNode->m_pNext;
	tempListNode->m_pNext = snlListNode;
	return OK;
}

Status SnlList::ListDelete(const int iIndex, ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength())
	{
		LogDevError("Out of list");
		return ERROR;
	}
	int iLocate(1);
	SnlListNode pTempNode = m_pListNode;
	while (pTempNode->m_pNext && iLocate < iIndex)
	{
		pTempNode = pTempNode->m_pNext;
		iLocate++;
	}
	SnlListNode deleListNode = pTempNode->m_pNext;
	pTempNode->m_pNext = deleListNode->m_pNext;
	eData = deleListNode->m_eData;
	free(deleListNode);
	return OK;
}

int SnlList::ListLength() const
{
	int iListLength(0);
	SnlListNode tempListNode = m_pListNode;
	while (tempListNode->m_pNext)
	{
		tempListNode = tempListNode->m_pNext;
		iListLength++;
	}
	return iListLength;
}
#endif // !DATA_STRUCT_Link_SNLLIST_H