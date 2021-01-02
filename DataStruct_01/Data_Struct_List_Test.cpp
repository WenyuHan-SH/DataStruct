#include "Data_Struct_List_SqList.h"
#include "Data_Struct_List_SnlList.h"
#include "Data_Struct_List_StaList.h"
#include "Data_Struct_List_CirList.h"
#include "Data_Struct_List_DulList.h"

namespace
{
	void TestList(std::shared_ptr<List> spList)
	{
		std::cout << "********************************************" << std::endl;
		spList->InitList();
		for (int iInserIndex = 0; iInserIndex < INSERT_MIN_NUMBER; ++iInserIndex)
		{
			spList->ListInsert(iInserIndex + 1, iInserIndex + 5);
		}
		std::cout << "Print TraverseBack: ";
		spList->ListTraverseBack(Print);
		std::cout << "Print Traverse:     ";
		spList->ListTraverse(Print);

		ElemType eDeleteElem;
		spList->ListDelete(DELETE_INDEX, eDeleteElem);
		std::cout << "DeleteIndex= " << DELETE_INDEX << " DeleteElem= " << eDeleteElem << std::endl;
		spList->ListTraverse(Print);

		spList->ClearList();
		for (int iInserIndex = 0; iInserIndex < INSERT_MAX_NUMER; ++iInserIndex)
		{
			spList->ListInsert(iInserIndex + 1, iInserIndex);
		}
		std::cout << "Print TraverseBack: ";
		spList->ListTraverseBack(Print);
		std::cout << "Print Traverse:     ";
		spList->ListTraverse(Print);

		ElemType eGetElem;
		spList->GetElem(GET_INDEX, eGetElem);
		int iLocate = spList->LocateElem(eGetElem, Compare);
		std::cout << "DeleteIndex= " << iLocate << " LocateElem= " << eGetElem << std::endl;

		ElemType eGetPriElem;
		spList->PriorElem(eGetElem, eGetPriElem);
		std::cout << "Elem= " << eGetElem << " PriElem= " << eGetPriElem << std::endl;

		ElemType eGetNextElem;
		spList->NextElem(eGetElem, eGetNextElem);
		std::cout << "Elem= " << eGetElem << " NextElem= " << eGetNextElem << std::endl;

		spList->DestroyList();

		std::cout << "********************************************" << std::endl;
	}
}

int main()
{
	auto spList = std::make_shared<CircularList>();
	//auto spList = std::make_shared<DualList>();
	//auto spList = std::make_shared<SnlList>();
	//auto spList = std::make_shared<SqList>();
	//auto spList = std::make_shared<StaticList>();
	TestList(spList);
	return EXIT_SUCCESS;
}
