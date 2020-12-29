#include "Data_Struct_SQ_List.h"
#include "Data_Struct_Link_List.h"
#include "Data_Struct_Static_List.h"
#include "Data_Struct_Circular_List.h"
#include "Data_Struct_Dual_List.h"
#include<iostream>
namespace
{
	const int LIST_LENGTH = 10;
	const int KILL_NUMBER = 1;
	const int ALPH_NUMBER = 1;
	void TestSQList()
	{
		SQListNode sqListNode;
		sqListNode.m_iLength = LIST_LENGTH;
		for (size_t i = 0; i < LIST_LENGTH; ++i)
		{
			sqListNode.m_idata[i] = i + 1;
		}

		SQList sqList(sqListNode);

		int iEleIndex(0), iDeleEle(0), iNumEle;

		iEleIndex = sqList.LocateElem(3);
		std::cout << iEleIndex << std::endl;

		sqList.ListInsert(3, 11);

		sqList.GetElem(2, iNumEle);
		std::cout << iNumEle << std::endl;

		sqList.ListDelete(2, iDeleEle);
		std::cout << iDeleEle << std::endl;

		SQListNode sqUnionListNode;
		sqUnionListNode.m_iLength = 1;
		sqUnionListNode.m_idata[0] = 20;
		SQList sqUniotList(sqUnionListNode);

		sqList.UnionList(&sqUniotList);

		sqList.PrintList();
	}

	ListNode CreateLinkListHead()
	{
		ListNode listHeadNode = (ListNode)malloc(sizeof(Node));
		listHeadNode->pNext = nullptr;
		for (size_t i = 0; i < LIST_LENGTH; ++i)
		{
			ListNode listNode = (ListNode)malloc(sizeof(Node));
			listNode->m_idata = i + 1;
			listNode->pNext = listHeadNode->pNext;
			listHeadNode->pNext = listNode;
		}
		return listHeadNode;
	}

	ListNode CreateLinkListTail()
	{
		ListNode listHeadNode = (ListNode)malloc(sizeof(Node));
		listHeadNode->pNext = nullptr;
		ListNode listTempNode(listHeadNode);
		for (size_t i = 0; i < LIST_LENGTH; ++i)
		{
			ListNode listNode = (ListNode)malloc(sizeof(Node));
			listNode->m_idata = i + 10;
			listNode->pNext = nullptr;
			listTempNode->pNext = listNode;
			listTempNode = listNode;
		}
		return listHeadNode;
	}

	void TestLinkList()
	{
		LinkList linkListHead = CreateLinkListHead();

		//LinkList linkListTail = CreateLinkListTail();

		//int iEleIndex(0), iDeleEle(0);

		//iEleIndex = linkListHead.LocateElem(3);
		//std::cout << iEleIndex << std::endl;

		
		//linkListHead.ListInsert(1, 22);
		linkListHead.PrintList();
		linkListHead.ClearList();

		//linkListHead.GetElem(2, iNumEle);
		//std::cout << iNumEle << std::endl;

		//linkListHead.ListDelete(2, iDeleEle);
		//std::cout << iDeleEle << std::endl;
		//std::cout << linkListHead.ListLength() << std::endl;
		//std::cout << linkListTail.ListLength() << std::endl;

		//linkListHead.PrintList();
		//linkListHead.UnionList(&linkListTail);

		//linkListHead.PrintList();
		//linkListTail.PrintList();
	}

	void TestStaticList()
	{

		StaticList staticList0;
		staticList0.Initial();

		StaticList staticList1;
		staticList1.Initial();
		staticList0.ListInsert(6, 99);

		int iEleIndex(0), iDeleEle(0), iNumEle;

		iEleIndex = staticList0.LocateElem(12);
		std::cout << iEleIndex << std::endl;

		staticList0.ListInsert(3, 5);

		staticList0.GetElem(2, iNumEle);
		std::cout << iNumEle << std::endl;

		staticList0.ListDelete(2, iDeleEle);
		std::cout << iDeleEle << std::endl;

		staticList0.UnionList(&staticList1);

		staticList0.PrintList();
		staticList1.PrintList();
	}

	ListNode CreateCircularList()
	{
		ListNode listHeadNode = (ListNode)malloc(sizeof(Node));
		ListNode listTempNode(listHeadNode);
		for (size_t i = 0; i < KILL_NUMBER; ++i)
		{
			ListNode listNode = (ListNode)malloc(sizeof(Node));
			listNode->m_idata = i+1;
			listTempNode->pNext = listNode;
			listTempNode = listNode;
		}
		listTempNode->pNext = listHeadNode->pNext;
		free(listHeadNode);
		return listTempNode->pNext;
	}

	void TestCircularList()
	{
		CircularList circularList = CreateCircularList();
		//circularList.ListKillIndex(3);
		circularList.PrintList();
		circularList.ClearList();
		std::cout << std::endl;
	}

	void TestDualList()
	{
		DualList dualList;
		dualList.InitAlphabet(ALPH_NUMBER);
		dualList.PrintList();
		std::cout << dualList.ListLength() << std::endl;
		dualList.ClearList();
		//dualList.PrintList();
	}
}

int main()
{
	//TestSQList();
	//TestLinkList();
	//TestStaticList();
	TestCircularList();
	//TestDualList();
	return EXIT_SUCCESS;
}