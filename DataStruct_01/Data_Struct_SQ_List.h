#ifndef DATA_STRUCT_SQ_LIST_H
#define DATA_STRUCT_SQ_LIST_H
#include "Data_Struct_List_Base.h"

class SQList :public List
{
public:
	SQList(const SQListNode sqListNode) :m_SQList(sqListNode) {}
	virtual ~SQList() {}
	virtual bool ListEmpty() const;
	virtual void ClearList();
	virtual Status GetElem(const int iIndex, int& iElement) const;
	virtual int LocateElem(const int iElement) const;
	virtual Status ListInsert(const int iIndex, const int iElement);
	virtual Status ListDelete(const int iIndex, int& iElement);
	virtual int ListLength() const;
	virtual void PrintList()  const;
private:
	SQListNode m_SQList;
};

bool SQList::ListEmpty() const
{
	return 0 == ListLength();
}

void SQList::ClearList()
{
	m_SQList.m_iLength = 0;
}

Status SQList::GetElem(const int iIndex, int& iElement) const
{
	if (ListEmpty())
	{
		return ERROR;
	}
	if (iIndex > m_SQList.m_iLength || iIndex < 1)
	{
		return ERROR;
	}
	iElement = m_SQList.m_idata[iIndex - 1];
	return OK;
}


int SQList::LocateElem(const int iElement) const
{
	for (int index = 0; index < m_SQList.m_iLength; ++index)
	{
		if (iElement == m_SQList.m_idata[index])
		{
			return index + 1;
		}
	}
	return 0;
}


Status SQList::ListInsert(const int iIndex, const int iElement)
{
	if (MAX_SIZE == m_SQList.m_iLength)
	{
		return ERROR;
	}
	if (iIndex > m_SQList.m_iLength || iIndex < 1)
	{
		return ERROR;
	}
	if (iIndex <= m_SQList.m_iLength)
	{
		for (int i = m_SQList.m_iLength - 1; i >= iIndex - 1; --i)
		{
			m_SQList.m_idata[i + 1] = m_SQList.m_idata[i];
		}
	}
	m_SQList.m_idata[iIndex - 1] = iElement;
	m_SQList.m_iLength++;
	return OK;
}

Status SQList::ListDelete(const int iIndex, int& iElement)
{
	if (ListEmpty())
	{
		return ERROR;
	}
	if (iIndex > m_SQList.m_iLength || iIndex < 1)
	{
		return ERROR;
	}
	iElement = m_SQList.m_idata[iIndex - 1];
	if (iIndex < m_SQList.m_iLength)
	{
		for (int i = iIndex - 1; i < m_SQList.m_iLength; ++i)
		{
			m_SQList.m_idata[i] = m_SQList.m_idata[i + 1];
		}
	}
	m_SQList.m_iLength--;
	return OK;
}

int SQList::ListLength() const
{
	return m_SQList.m_iLength;
}

void SQList::PrintList() const
{
	for (int i = 0; i < m_SQList.m_iLength; ++i)
	{
		std::cout << m_SQList.m_idata[i] << " ";
	}
	std::cout << std::endl;
}
#endif // !DATA_STRUCT_SQ_LIST_H