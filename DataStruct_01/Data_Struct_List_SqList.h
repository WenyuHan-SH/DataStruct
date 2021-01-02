#ifndef DATA_STRUCT_LIST_SQLIST_H
#define DATA_STRUCT_LIST_SQLIST_H
#include "Data_Struct_List_Base.h"

class SqList :public List
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
	SqListNode m_pSqListNode;
};

Status SqList::InitList()
{
	DestroyList();
	m_pSqListNode = static_cast<SqListNode>(malloc(sizeof(SqNode)));
	if (!m_pSqListNode)
	{
		LogDevError("Init list failed");
		return OVERFLOW;
	}
	m_pSqListNode->m_uiLength = 0;
	m_pSqListNode->m_eData[0] = 0;
	return OK;
}

Status SqList::DestroyList()
{
	free(m_pSqListNode);
	return OK;
}

Status SqList::ClearList()
{
	for (int iIndex = 0; iIndex <= m_pSqListNode->m_uiLength; ++iIndex)
	{
		m_pSqListNode->m_eData[iIndex] = 0;
	}
	m_pSqListNode->m_uiLength = 0;
	return OK;
}

int SqList::LocateElem(const ElemType& eData, bool(*Compare)(ElemType, ElemType)) const
{
	for (int iIndex = 1; iIndex <= ListLength(); ++iIndex)
	{
		if (Compare(eData, m_pSqListNode->m_eData[iIndex]))
		{
			return iIndex;
		}
	}
	return 0;
}

int SqList::ListLength() const
{
	return m_pSqListNode->m_uiLength;
}

Status SqList::GetElem(const int iIndex, ElemType& eData) const
{
	if (ListEmpty())
	{
		LogDevError("List is empty");
		return ERROR;
	}
	if (iIndex > ListLength() || iIndex < 1)
	{
		LogDevError("Index out of the list");
		return ERROR;
	}
	eData = m_pSqListNode->m_eData[iIndex];
	return OK;
}

Status SqList::ListInsert(const int iIndex, const ElemType& eData)
{
	if (MAX_SIZE == ListLength())
	{
		LogDevError("SqListNode is Full");
		return ERROR;
	}
	if (iIndex > ListLength() + 1 || iIndex < 1)
	{
		LogDevError("insert out of SqListNode");
		return ERROR;
	}

	for (int iListIndex = ListLength(); iListIndex >= iIndex; --iListIndex)
	{
		m_pSqListNode->m_eData[iListIndex + 1] = m_pSqListNode->m_eData[iListIndex];
	}
	m_pSqListNode->m_eData[iIndex] = eData;
	m_pSqListNode->m_uiLength++;

	return OK;
}

Status SqList::ListDelete(const int iIndex, ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength())
	{
		LogDevError("Out of list");
		return ERROR;
	}
	if (iIndex > ListLength() || iIndex < 1)
	{
		LogDevError("insert out of SqListNode");
		return ERROR;
	}

	eData = m_pSqListNode->m_eData[iIndex];
	for (int iListIndex = iIndex; iListIndex <= ListLength(); ++iListIndex)
	{
		m_pSqListNode->m_eData[iListIndex] = m_pSqListNode->m_eData[iListIndex + 1];
	}
	m_pSqListNode->m_uiLength--;
	return OK;
}
#endif // !DATA_STRUCT_LIST_SQLIST_H