#ifndef DATA_STRUCT_STATIC_LIST_H
#define DATA_STRUCT_STATIC_LIST_H
#include "Data_Struct_List_Base.h"

class StaticList :public List
{
public:
	// Í¨¹ý List ¼Ì³Ð
	virtual void Initial();
	virtual bool ListEmpty() const;
	virtual void ClearList();
	virtual Status GetElem(const int iIndex, int& iElement) const;
	virtual int LocateElem(const int iElement) const;
	virtual Status ListInsert(const int iIndex, const int iElement);
	virtual Status ListDelete(const int iIndex, int& iElement);
	virtual int ListLength() const;
	virtual void PrintList() const;
private:
	int Malloc_SLL();
	void Free_SSL(int iIndex);
private:
	StatciLinkList m_StaticList;
};

void StaticList::Initial()
{
	ClearList();
	for (int i = 1; i <= STATIC_LIST_LENGTH; ++i)
	{
		m_StaticList[i].data = i + 10;
	}
	m_StaticList[MAXSIZE - 1].cur = 1;
	m_StaticList[STATIC_LIST_LENGTH].cur = 0;
	m_StaticList[0].cur = STATIC_LIST_LENGTH + 1;
}

bool StaticList::ListEmpty() const
{
	return 0 == m_StaticList[MAXSIZE - 1].cur;
}

void StaticList::ClearList()
{
	for (int i = 0; i < MAXSIZE - 1; ++i)
	{
		m_StaticList[i].cur = i + 1;
	}
	m_StaticList[MAXSIZE - 1].cur = 0;
}

Status StaticList::GetElem(const int iIndex, int& iElement) const
{
	if (iIndex<1 || iIndex>ListLength())
	{
		return ERROR;
	}
	iElement = m_StaticList[iIndex].data;
	return OK;
}

int StaticList::LocateElem(const int iElement) const
{
	int iIndex = m_StaticList[MAXSIZE - 1].cur;
	while (iIndex)
	{
		if (iElement == m_StaticList[iIndex].data)
		{
			return iIndex;
		}
		iIndex = m_StaticList[iIndex].cur;
	}
	return 0;
}

int StaticList::Malloc_SLL()
{
	int iMallocIndex = m_StaticList[0].cur;
	if (m_StaticList[0].cur)
	{
		m_StaticList[0].cur = m_StaticList[iMallocIndex].cur;
	}
	return iMallocIndex;
}

Status StaticList::ListInsert(const int iIndex, const int iElement)
{
	if (iIndex<1 || iIndex>ListLength() + 1)
	{
		return ERROR;
	}
	int iMallocIndex = Malloc_SLL();
	int iInsertIndex(MAXSIZE-1);
	if (iMallocIndex)
	{
		m_StaticList[iMallocIndex].data = iElement;
		for (int index = 0; index < iIndex; ++index)
		{
			iInsertIndex = m_StaticList[iInsertIndex].cur;
		}
		m_StaticList[iMallocIndex].cur = m_StaticList[iInsertIndex].cur;
		m_StaticList[iInsertIndex].cur = iMallocIndex;
		return OK;
	}
	return ERROR;
}

void StaticList::Free_SSL(int iIndex)
{
	m_StaticList[iIndex].cur = m_StaticList[0].cur;
	m_StaticList[0].cur = iIndex;
}

Status StaticList::ListDelete(const int iIndex, int& iElement)
{
	if (iIndex<1 || iIndex>ListLength())
	{
		return ERROR;
	}
	int iDeleteIndex(0);

	for (int index = 0; index < iIndex; ++index)
	{
		iDeleteIndex = m_StaticList[index].cur;
	}
	int iDeleteCur = m_StaticList[iDeleteIndex].cur;
	m_StaticList[iDeleteIndex].cur = m_StaticList[iDeleteCur].cur;
	return OK;
}

int StaticList::ListLength() const
{
	int iLength(0);
	int iIndex = m_StaticList[MAXSIZE - 1].cur;
	while (iIndex)
	{
		iIndex = m_StaticList[iIndex].cur;
		iLength++;
	}
	return iLength;
}

void StaticList::PrintList() const
{
	int iIndex = m_StaticList[MAXSIZE - 1].cur;
	while (iIndex)
	{
		std::cout << m_StaticList[iIndex].data << " ";
		iIndex = m_StaticList[iIndex].cur;
	}
	std::cout << std::endl;
}

#endif DATA_STRUCT_STATIC_LIST_H
