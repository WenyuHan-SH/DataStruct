#ifndef DATA_STRUCT_LIST_CIRLIST_H
#define DATA_STRUCT_LIST_CIRLIST_H
#include "Data_Struct_List_Base.h"

class CircularList :public List
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
	SnlListNode m_pSnlListNode;
};

Status CircularList::InitList()
{
	m_pSnlListNode = static_cast<SnlListNode>(malloc(sizeof(SnlNode)));
	m_pSnlListNode->m_pNext = m_pSnlListNode;
	m_pSnlListNode->m_eData = 0;
	return OK;
}

Status CircularList::DestroyList()
{
	SnlListNode freeListNode(nullptr);
	SnlListNode tempListNode = m_pSnlListNode;
	while (tempListNode->m_pNext != m_pSnlListNode)
	{
		freeListNode = tempListNode->m_pNext;
		free(tempListNode);
		tempListNode = freeListNode;
	}
	m_pSnlListNode = nullptr;
	return OK;
}

Status CircularList::ClearList()
{
	SnlListNode freeListNode(nullptr);
	SnlListNode tempListNode = m_pSnlListNode->m_pNext;
	while (tempListNode->m_pNext != m_pSnlListNode)
	{
		freeListNode = tempListNode->m_pNext;
		free(tempListNode);
		tempListNode = freeListNode;
	}
	m_pSnlListNode->m_pNext = m_pSnlListNode;
	return OK;
}

int CircularList::LocateElem(const ElemType& eData, bool(*Compare)(ElemType, ElemType)) const
{
	if (ListEmpty())
	{
		LogDevError("CircularList is empty");
		return 0;
	}
	int iLocate(1);
	SnlListNode pTempNode = m_pSnlListNode;
	while (pTempNode->m_pNext != m_pSnlListNode)
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

int CircularList::ListLength() const
{
	int iListSize(0);
	SnlListNode pTempNode = m_pSnlListNode;
	while (pTempNode->m_pNext != m_pSnlListNode)
	{
		pTempNode = pTempNode->m_pNext;
		iListSize++;
	}
	return iListSize;
}

Status CircularList::GetElem(const int iIndex, ElemType& eData) const
{
	if (ListEmpty())
	{
		LogDevError("CircularList is empty");
		return ERROR;
	}
	int iLocate(1);
	SnlListNode pTempNode = m_pSnlListNode;
	while (pTempNode->m_pNext != m_pSnlListNode && iLocate <= iIndex)
	{
		pTempNode = pTempNode->m_pNext;
		iLocate++;
	}
	eData = pTempNode->m_eData;
	return OK;
}

Status CircularList::ListInsert(const int iIndex, const ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength() + 1)
	{
		LogDevError("Out of list");
		return ERROR;
	}
	SnlListNode pInsertSnlNode = static_cast<SnlListNode>(malloc(sizeof(SnlNode)));
	if (!pInsertSnlNode)
	{
		LogDevError("pTempDualNode is null");
		return ERROR;
	}
	int iLocate(1);
	SnlListNode pTempNode = m_pSnlListNode;
	while (pTempNode->m_pNext != m_pSnlListNode && iLocate < iIndex)
	{
		pTempNode = pTempNode->m_pNext;
		iLocate++;
	}
	pInsertSnlNode->m_eData = eData;
	pInsertSnlNode->m_pNext = pTempNode->m_pNext;
	pTempNode->m_pNext = pInsertSnlNode;
	return OK;
}

Status CircularList::ListDelete(const int iIndex, ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength())
	{
		LogDevError("Out of list");
		return ERROR;
	}
	int iLocate(1);
	SnlListNode pTempNode = m_pSnlListNode;
	while (pTempNode->m_pNext != m_pSnlListNode && iLocate < iIndex)
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

#endif // !DATA_STRUCT_LIST_CIRLIST_H

