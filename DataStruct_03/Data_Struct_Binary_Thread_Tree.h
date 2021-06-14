#ifndef DATA_STRUCT_BINARY_THREAD_TREE
#define DATA_STRUCT_BINARY_THREAD_TREE
#include "Data_Struct_Tree_Base.h"
namespace
{
	void CreateTreeNode(BiThrTree* pTreeNode)
	{
		ElemType ch = getchar();
		if ('#' == ch)
		{
			*pTreeNode = nullptr;
		}
		else
		{
			*pTreeNode = static_cast<BiThrTree>(malloc(sizeof(BiThrNode)));
			if (!*pTreeNode)
			{
				LogDevError("malloc failed");
			}
			(*pTreeNode)->data = ch;
			(*pTreeNode)->ltag = LINK;
			(*pTreeNode)->rtag = LINK;
			CreateTreeNode(&(*pTreeNode)->lchild);
			CreateTreeNode(&(*pTreeNode)->rchild);
		}
	}

	void PreOrderTraverse(const BiThrTree pTreeNode)
	{
		if (pTreeNode)
		{
			std::cout << pTreeNode->data << " ";
			PreOrderTraverse(pTreeNode->lchild);
			PreOrderTraverse(pTreeNode->rchild);
		}
	}

	void InOrderTraverse(const BiThrTree pTreeNode)
	{
		if (pTreeNode)
		{
			PreOrderTraverse(pTreeNode->lchild);
			std::cout << pTreeNode->data << " ";
			PreOrderTraverse(pTreeNode->rchild);
		}
	}

	void PostOrderTraverse(const BiThrTree pTreeNode)
	{
		if (pTreeNode)
		{
			PreOrderTraverse(pTreeNode->lchild);
			PreOrderTraverse(pTreeNode->rchild);
			std::cout << pTreeNode->data << " ";
		}
	}

	void InOrderTraverse_Thr(const BiThrTree pTreeNode)
	{
		if (pTreeNode)
		{
			BiThrTree spTempBiThrTree = pTreeNode->lchild; //根节点
			while (spTempBiThrTree != pTreeNode)
			{
				while (LINK == spTempBiThrTree->ltag)
				{
					spTempBiThrTree = spTempBiThrTree->lchild;
				}
				std::cout << spTempBiThrTree->data << " ";
				while (THREAD == spTempBiThrTree->rtag
					&& spTempBiThrTree->rchild != pTreeNode)
				{
					spTempBiThrTree = spTempBiThrTree->rchild;
					std::cout << spTempBiThrTree->data << " ";
				}
				spTempBiThrTree = spTempBiThrTree->rchild;
			}
		}
	}
}

class BinaryThreadTree :public Tree
{
public:
	void InitTree() override;
	void DestroyTree() override;
	void CreateTree() override;
	void ClearTree() override;
	bool TreeEmpty() const override;
	int TreeDepth() const override;
	ElemType Value() const override;
	void Assign(const ElemType& eFindData, const ElemType& eAssignData) override;
	void TreePreview()const;
public:
	BiThrTree Root() const;
	BiThrTree Parent(const ElemType& eFindData) const;
	BiThrTree LeftChild(const ElemType& eFindData) const;
	BiThrTree RightSibling(const ElemType& eFindData) const;
	void InsertChild(const ElemType& eFindData, const ElemType& eInsertData);
	void DeletChilde(const ElemType& eFindData);
	void InThreading();
private:
	void InThreading(BiThrTree pTreeNode);
private:
	BiThrTree m_pBiThrTree;
	BiThrTree m_pHeadBiThrTree;
	BiThrTree m_pPreBiThrTree;
};

void BinaryThreadTree::InitTree()
{

}

void BinaryThreadTree::DestroyTree()
{

}

void BinaryThreadTree::CreateTree()
{
	std::cout << "Create BinaryTree Begin:" << std::endl;
	ElemType ch = getchar();
	if ('#' == ch)
	{
		m_pBiThrTree = nullptr;
	}
	else
	{
		m_pBiThrTree = static_cast<BiThrTree>(malloc(sizeof(BiThrNode)));
		if (!m_pBiThrTree)
		{
			LogDevError("malloc failed");
		}
		m_pBiThrTree->data = ch;
		m_pBiThrTree->ltag = LINK;
		m_pBiThrTree->rtag = LINK;
		CreateTreeNode(&m_pBiThrTree->lchild);
		CreateTreeNode(&m_pBiThrTree->rchild);
	}
}

void BinaryThreadTree::ClearTree()
{

}

bool BinaryThreadTree::TreeEmpty() const
{
	return true;
}

int BinaryThreadTree::TreeDepth() const
{
	return 0;
}

ElemType BinaryThreadTree::Value() const
{
	return 0;
}

void BinaryThreadTree::Assign(const ElemType& eFindData, const ElemType& eAssignData)
{

}

void BinaryThreadTree::TreePreview()const
{
	switch (m_eTraverseOrder)
	{
	case PreOrder:
		std::cout << "PreOrder Traverse:" << std::endl;
		PreOrderTraverse(m_pBiThrTree);
		break;
	case InOrder:
		std::cout << "InOrder Traverse:" << std::endl;
		//InOrderTraverse(m_pBiThrTree);
		InOrderTraverse_Thr(m_pHeadBiThrTree);
		break;
	case PostOrder:
		std::cout << "PostOrder Traverse:" << std::endl;
		PostOrderTraverse(m_pBiThrTree);
		break;
	default:
		break;
	}
}

void BinaryThreadTree::InThreading()
{
	if (!m_pBiThrTree)
	{
		LogDevWarning("Binary Thread Tree is Null");
		return;
	}

	m_pHeadBiThrTree = static_cast<BiThrTree>(malloc(sizeof(BiThrNode)));
	m_pHeadBiThrTree->data = ' ';
	m_pHeadBiThrTree->ltag = LINK;
	m_pHeadBiThrTree->rtag = THREAD;
	m_pHeadBiThrTree->lchild = m_pBiThrTree;
	m_pHeadBiThrTree->rchild = m_pHeadBiThrTree;

	m_pPreBiThrTree = m_pHeadBiThrTree;

	InThreading(m_pBiThrTree);
	m_pPreBiThrTree->rchild = m_pHeadBiThrTree; //最后一个访问节点
	m_pPreBiThrTree->rtag = THREAD;

	m_pHeadBiThrTree->rchild = m_pPreBiThrTree;
}

void BinaryThreadTree::InThreading(BiThrTree pTreeNode)
{
	if (pTreeNode)
	{
		InThreading(pTreeNode->lchild);
		if (!pTreeNode->lchild)
		{
			pTreeNode->ltag = THREAD;
			pTreeNode->lchild = m_pPreBiThrTree;
		}
		if (!m_pPreBiThrTree->rchild)
		{
			m_pPreBiThrTree->rtag = THREAD;
			m_pPreBiThrTree->rchild = pTreeNode;
		}
		m_pPreBiThrTree = pTreeNode;
		InThreading(pTreeNode->rchild);
	}
}
#endif // !DATA_STRUCT_BINARY_THREAD_TREE

