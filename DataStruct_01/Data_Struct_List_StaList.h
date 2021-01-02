#ifndef DATA_STRUCT_LIST_STALIST_H
#define DATA_STRUCT_LIST_STALIST_H
#include "Data_Struct_List_Base.h"

class StaticList :public List
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
	int Malloc_StaNode();
	void Free_StaNode(int iIndex);
private:
	StaLinkList m_StaLinkList;
};

Status StaticList::InitList()
{
	ClearList();
	return OK;
}

Status StaticList::DestroyList()
{
	ClearList();
	return OK;
}

Status StaticList::ClearList()
{
	for (int i = 0; i < MAX_SIZE - 2; ++i)
	{
		m_StaLinkList[i].m_uiCur = i + 1;
	}
	m_StaLinkList[MAX_SIZE - 2].m_uiCur = 0;
	m_StaLinkList[MAX_SIZE - 1].m_uiCur = 0;
	return OK;
}

Status StaticList::GetElem(const int iIndex, ElemType& eData) const
{
	if (iIndex<1 || iIndex>ListLength())
	{
		LogDevError("Index out of the list");
		return ERROR;
	}
	int iLocate(1);
	int pTempIndex = m_StaLinkList[MAX_SIZE - 1].m_uiCur;
	while (iLocate < iIndex)
	{
		pTempIndex = m_StaLinkList[pTempIndex].m_uiCur;
		iLocate++;
	}
	eData = m_StaLinkList[pTempIndex].m_eData;
	return OK;
}

int StaticList::LocateElem(const ElemType& eData, bool(*Compare)(ElemType, ElemType)) const
{
	int pTempIndex = m_StaLinkList[MAX_SIZE - 1].m_uiCur;
	while (pTempIndex)
	{
		if (Compare(eData, m_StaLinkList[pTempIndex].m_eData))
		{
			return pTempIndex;
		}
		pTempIndex = m_StaLinkList[pTempIndex].m_uiCur;
	}
	return 0;
}

Status StaticList::ListInsert(const int iIndex, const ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength() + 1)
	{
		LogDevError("Index out of the list");
		return ERROR;
	}
	int iMallocIndex = Malloc_StaNode();
	int pTempIndex = MAX_SIZE - 1;
	int iLocate(1);
	while (iLocate < iIndex)
	{
		pTempIndex = m_StaLinkList[pTempIndex].m_uiCur;
		iLocate++;
	}
	m_StaLinkList[iMallocIndex].m_uiCur = m_StaLinkList[pTempIndex].m_uiCur;
	m_StaLinkList[iMallocIndex].m_eData = eData;
	m_StaLinkList[pTempIndex].m_uiCur = iMallocIndex;
	return OK;
}

Status StaticList::ListDelete(const int iIndex, ElemType& eData)
{
	if (iIndex<1 || iIndex>ListLength())
	{
		LogDevError("Index out of the list");
		return ERROR;
	}
	int iTempIndex = MAX_SIZE - 1;
	int iLocate(1);
	while (iLocate < iIndex)
	{
		iTempIndex = m_StaLinkList[iTempIndex].m_uiCur;
		iLocate++;
	}
	int iDeleteIndex = m_StaLinkList[iTempIndex].m_uiCur;
	eData = m_StaLinkList[iDeleteIndex].m_eData;
	m_StaLinkList[iTempIndex].m_uiCur = m_StaLinkList[iDeleteIndex].m_uiCur;

	Free_StaNode(iDeleteIndex);
	return OK;
}

int StaticList::ListLength() const
{
	int iLength(0);
	int iIndex = m_StaLinkList[MAX_SIZE - 1].m_uiCur;
	while (iIndex)
	{
		iIndex = m_StaLinkList[iIndex].m_uiCur;
		iLength++;
	}
	return iLength;
}

int StaticList::Malloc_StaNode()
{
	int iMallocIndex = m_StaLinkList[0].m_uiCur;
	if (iMallocIndex)
	{
		m_StaLinkList[0].m_uiCur = m_StaLinkList[iMallocIndex].m_uiCur;
	}
	return iMallocIndex;
}

void StaticList::Free_StaNode(int iIndex)
{
	m_StaLinkList[iIndex].m_eData = 0;
	m_StaLinkList[iIndex].m_uiCur = m_StaLinkList[0].m_uiCur;
	m_StaLinkList[0].m_uiCur = iIndex;
}

#endif// !DATA_STRUCT_LIST_STALIST_H
