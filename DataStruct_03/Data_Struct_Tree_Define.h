#ifndef DATA_STRUCT_TREE_DEFINE
#define DATA_STRUCT_TREE_DEFINE
#include <iostream>
#include <vector>
#define MAX_TREE_SIZE 100
typedef char ElemType;

typedef enum
{
	PreOrder = 1,
	InOrder,
	PostOrder,
	LevelOrder
} Traverse;

typedef enum
{
	LH = 1,
	EH = 0,
	RH = -1
}Balance;

//˫�ױ�ʾ��
typedef struct PTNode
{
	ElemType data;
	int parent;
} PTNode;

typedef struct
{
	PTNode nodes[MAX_TREE_SIZE];
	int r; //����λ��
	int n; //�����
}PTree;

//���ӱ�ʾ��
typedef struct CTNode
{
	int child;
	struct CTNode* next;
}*ChildPtr;

typedef struct
{
	ElemType data;
	ChildPtr firstchild;
} CTBox;

typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];
	int r;
	int n;
}CTree;

//�����ֵܱ�ʾ��
typedef struct CSNode
{
	ElemType data;
	struct CSNode* firstchild;
	struct CSNode* rightsib;
}CSNode, * CSTree;

//������
typedef struct BiTNode
{
	ElemType data;
	Balance balance;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
}BiTNode, * BiTree;

//����������
typedef enum
{
	LINK = 1,
	THREAD
}PointerTag;

typedef struct BiThrNode
{
	ElemType data;
	struct BiThrNode* lchild;
	struct BiThrNode* rchild;
	PointerTag ltag;
	PointerTag rtag;
}BiThrNode, * BiThrTree;

void LogDevInfo(const std::string sInfo)
{
	std::cout << "Info:" << sInfo << std::endl;
}

void LogDevWarning(const std::string sInfo)
{
	std::cout << "Warning:" << sInfo << std::endl;
}

void LogDevError(const std::string sInfo)
{
	std::cout << "Error:" << sInfo << std::endl;
}
#endif // !DATA_STRUCT_TREE_DEFINE
