#ifndef  HUMMAN_DEFINE_H
#define  HUMMAN_DEFINE_H
#include <iostream>

const int MAX_SZ = 256;

//htTree
typedef struct _htNode
{
	char symbol;
	struct _htNode* left;
	struct _htNode* right;
}htNode, * HTNode;

typedef struct _htTree
{
	htNode* root;
}htTree, * HTtree;

//hlTable
typedef struct _hlNode
{
	char symbol;
	char* code;
	struct _hlNode* next;
} hlNode;

typedef struct _hlTable
{
	hlNode* first;
	hlNode* last;
}hlTable, * HLTable;

//Queue
typedef struct _pQueueNode
{
	htNode* val;
	unsigned int priority;
	struct _pQueueNode* next;
}pQueueNode;

typedef struct _pQueue
{
	unsigned int size;
	pQueueNode* first;
} pQueue, * Queue;
#endif // ! HUMMAN_DEFINE_H

