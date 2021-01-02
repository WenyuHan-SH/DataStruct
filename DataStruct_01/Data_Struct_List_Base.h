#ifndef DATA_STRUCT_LIST_BASE_H
#define DATA_STRUCT_LIST_BASE_H
#include "Data_Struct_List_Define.h"

namespace
{
	void Print(const ElemType eData)
	{
		std::cout << eData << " ";
	}

	bool Compare(const ElemType eData0, const ElemType eData1)
	{
		return abs(eData0 - eData1) < ACCURACY_ERROR;
	}
}

class List
{
public:
	List() {}
	virtual ~List() {}
	virtual Status InitList() = 0;
	virtual Status DestroyList() = 0;
	virtual Status ClearList() = 0;
	virtual int ListLength()  const = 0;
	virtual Status GetElem(const int iIndex, ElemType& eData) const = 0;
	virtual int LocateElem(const ElemType& eData, bool(*Compare)(ElemType, ElemType)) const = 0;
	virtual Status ListInsert(const int iIndex, const ElemType& eData) = 0;
	virtual Status ListDelete(const int iIndex, ElemType& eData) = 0;
public:
	Status PriorElem(const ElemType& eDataCur, ElemType& eDataPre) const;
	Status NextElem(const ElemType& eDataCur, ElemType& eDataNext) const;
	void ListTraverse(void(*Print)(const ElemType)) const;
	void ListTraverseBack(void(*Print)(const ElemType)) const;
	bool ListEmpty() const;
	void UnionList(List* const pList);
};

void List::UnionList(List* const pList)
{
	for (int index = 1; index <= pList->ListLength(); ++index)
	{
		int iTemp;
		if (pList->GetElem(index, iTemp))
		{
			if (!LocateElem(iTemp, Compare))
			{
				ListInsert(ListLength(), iTemp);
			}
		}
	}
}

Status List::PriorElem(const ElemType& eDataCur, ElemType& eDataPre) const
{
	int iLocate = LocateElem(eDataCur, Compare);
	if (iLocate - 1 < 1 || iLocate - 1 >= ListLength())
	{
		LogDevError("Locate out of length");
		return ERROR;
	}
	GetElem(iLocate - 1, eDataPre);
	return OK;
}

Status List::NextElem(const ElemType& eDataCur, ElemType& eDataNext) const
{
	int iLocate = LocateElem(eDataCur, Compare);
	if (iLocate + 1 <= 1 || iLocate + 1 > ListLength())
	{
		LogDevError("Locate out of length");
		return ERROR;
	}
	return GetElem(iLocate + 1, eDataNext);
}

bool List::ListEmpty() const
{
	return 0 == ListLength();
}

void List::ListTraverse(void(*Print)(const ElemType)) const
{
	for (int iIndex = 1; iIndex <= ListLength(); ++iIndex)
	{
		ElemType eDataCur;
		GetElem(iIndex, eDataCur);
		Print(eDataCur);
	}
	std::cout << std::endl;
}

void List::ListTraverseBack(void(*Print)(const ElemType)) const
{
	for (int iIndex = ListLength(); iIndex > 0; --iIndex)
	{
		ElemType eDataCur;
		GetElem(iIndex, eDataCur);
		Print(eDataCur);
	}
	std::cout << std::endl;
}

#endif // !DATA_STRUCT_LIST_BASE_H
