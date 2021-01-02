#ifndef DATA_STRUCT_LIST_DULLIST_H
#define DATA_STRUCT_LIST_DULLIST_H
#include "Data_Struct_List_Base.h"
class DualList :public List
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
	DulLinkList m_pDulLinkList;
};

Status DualList::InitList()
{
	m_pDulLinkList = static_cast<DulLinkList>(malloc(sizeof(DulNode)));
	m_pDulLinkList->m_pNext = m_pDulLinkList;
	m_pDulLinkList->m_pPre = m_pDulLinkList;
	m_pDulLinkList->m_eData = 0;
	return OK;
}

Status DualList::DestroyList()
{
	DulLinkList freeListNode(nullptr);
	DulLinkList tempListNode = m_pDulLinkList;
	while (tempListNode->m_pNext != m_pDulLinkList)
	{
		freeListNode = tempListNode->m_pNext;
		free(tempListNode);
		tempListNode = freeListNode;
	}
	m_pDulLinkList = nullptr;
	return OK;
}

Status DualList::ClearList()
{
	DulLinkList freeListNode(nullptr);
	DulLinkList tempListNode = m_pDulLinkList;
	while (tempListNode->m_pNext != m_pDulLinkList)
	{
		freeListNode = tempListNode->m_pNext;
		free(tempListNode);
		tempListNode = freeListNode;
	}
	m_pDulLinkList->m_pNext = m_pDulLinkList;
	m_pDulLinkList->m_pPre = m_pDulLinkList;
	return OK;
}

int DualList::LocateElem(const ElemType& eData, bool(*Compare)(ElemType, ElemType)) const
{
	if (ListEmpty())
	{
		LogDevError("DualList is empty");
		return 0;
	}
	int iLocate(1);
	DulLinkList pTempNode = m_pDulLinkList;
	while (pTempNode->m_pNext != m_pDulLinkList)
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

int DualList::ListLength() const
{
	int iListSize(0);
	DulLinkList tempDulNode = m_pDulLinkList;
	while (tempDulNode->m_pNext != m_pDulLinkList)
	{
		tempDulNode = tempDulNode->m_pNext;
		iListSize++;
	}
	return iListSize;
}

Status DualList::GetElem(const int iIndex, ElemType& eData) const
{
	if (ListEmpty())
	{
		LogDevError("DualList is empty");
		return ERROR;
	}
	int iLocate(1);
	DulLinkList pTempNode = m_pDulLinkList;
	while (pTempNode->m_pNext && iLocate <= iIndex)
	{
		pTempNode = pTempNode->m_pNext;
		iLocate++;
	}
	eData = pTempNode->m_eData;
	return OK;
}

Status DualList::ListInsert(const int iIndex, const ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength() + 1)
	{
		LogDevError("Out of list");
		return ERROR;
	}
	DulLinkList pInsertDualNode = static_cast<DulLinkList>(malloc(sizeof(DulNode)));
	if (!pInsertDualNode)
	{
		LogDevError("pTempDualNode is null");
		return ERROR;
	}
	int iLocate(1);
	DulLinkList pTempNode = m_pDulLinkList;
	while (pTempNode->m_pNext && iLocate < iIndex)
	{
		pTempNode = pTempNode->m_pNext;
		iLocate++;
	}
	pInsertDualNode->m_eData = eData;
	pInsertDualNode->m_pNext = pTempNode->m_pNext;
	pTempNode->m_pNext->m_pPre = pInsertDualNode;
	pTempNode->m_pNext = pInsertDualNode;
	pInsertDualNode->m_pPre = pTempNode;
	return OK;
}

Status DualList::ListDelete(const int iIndex, ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength())
	{
		LogDevError("Out of list");
		return ERROR;
	}
	int iLocate(1);
	DulLinkList pTempNode = m_pDulLinkList->m_pNext;
	while (pTempNode->m_pNext != m_pDulLinkList && iLocate < iIndex)
	{
		pTempNode = pTempNode->m_pNext;
		iLocate++;
	}
	eData = pTempNode->m_eData;
	pTempNode->m_pPre->m_pNext = pTempNode->m_pNext;
	pTempNode->m_pNext->m_pPre = pTempNode->m_pPre;
	free(pTempNode);
	return OK;
}
#endif // !DATA_STRUCT_LIST_DULLIST_H

