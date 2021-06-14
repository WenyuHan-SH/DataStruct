#ifndef DATA_STRUCT_BINARY_TREE
#define DATA_STRUCT_BINARY_TREE
#include "Data_Struct_Tree_Base.h"
namespace
{
	void CreateTreeNode(BiTree* pTreeNode)
	{
		ElemType ch = getchar();
		if ('#' == ch)
		{
			*pTreeNode = nullptr;
		}
		else
		{
			*pTreeNode = static_cast<BiTree>(malloc(sizeof(BiTNode)));
			if (!*pTreeNode)
			{
				LogDevError("malloc failed");
			}
			(*pTreeNode)->data = ch;
			CreateTreeNode(&(*pTreeNode)->lchild);
			CreateTreeNode(&(*pTreeNode)->rchild);
		}
	}

	void PreOrderTraverse(const BiTree pTreeNode)
	{
		if (pTreeNode)
		{
			std::cout << pTreeNode->data << " ";
			PreOrderTraverse(pTreeNode->lchild);
			PreOrderTraverse(pTreeNode->rchild);
		}
	}

	void InOrderTraverse(const BiTree pTreeNode)
	{
		if (pTreeNode)
		{
			PreOrderTraverse(pTreeNode->lchild);
			std::cout << pTreeNode->data << " ";
			PreOrderTraverse(pTreeNode->rchild);
		}
	}

	void PostOrderTraverse(const BiTree pTreeNode)
	{
		if (pTreeNode)
		{
			PreOrderTraverse(pTreeNode->lchild);
			PreOrderTraverse(pTreeNode->rchild);
			std::cout << pTreeNode->data << " ";
		}
	}

	bool SearchBST_i(const BiTree biTree, const ElemType eData, const BiTree biTreeParNode, BiTree* biTreeNode)
	{
		if (!biTree)
		{
			*biTreeNode = biTreeParNode;
			return false;
		}
		else if (eData == biTree->data)
		{
			*biTreeNode = biTree;
			return true;
		}
		else if (eData < biTree->data)
		{
			SearchBST_i(biTree->lchild, eData, biTree, biTreeNode);
		}
		else
		{
			SearchBST_i(biTree->rchild, eData, biTree, biTreeNode);
		}
	}

	bool Delete_i(BiTree* biTree)
	{
		BiTree biTempNode(nullptr);
		if (nullptr == (*biTree)->rchild)
		{
			biTempNode = *biTree;
			*biTree = (*biTree)->lchild;
			free(biTempNode);
		}
		else if (nullptr == (*biTree)->lchild)
		{
			biTempNode = *biTree;
			*biTree = (*biTree)->rchild;
			free(biTempNode);
		}
		else
		{
			biTempNode = *biTree;
			auto biTreeChild = (*biTree)->lchild;
			while (biTreeChild->rchild)
			{
				biTempNode = biTreeChild;
				biTreeChild = biTreeChild->rchild;
			}
			(*biTree)->data = biTreeChild->data;
			if (biTempNode != *biTree)
			{
				biTempNode->rchild = biTreeChild->lchild;
			}
			else
			{
				biTempNode->lchild = biTreeChild->rchild;
			}
			free(biTreeChild);
		}
		return true;
	}

	bool DeleteBST_i(BiTree* biTree, const ElemType eData)
	{
		if (!biTree)
		{
			return false;
		}
		else
		{
			if (eData == (*biTree)->data)
			{
				return Delete_i(&(*biTree));
			}
			else if (eData < (*biTree)->data)
			{
				return DeleteBST_i(&(*biTree)->lchild, eData);
			}
			else
			{
				return DeleteBST_i(&(*biTree)->rchild, eData);
			}
		}
	}

	void R_Rotate(BiTree* biTree)
	{
		BiTree biTempTree;
		biTempTree = (*biTree)->lchild;
		(*biTree)->lchild = biTempTree->rchild;
		biTempTree->rchild = (*biTree);
		*biTree = biTempTree;
	}

	void L_Rotate(BiTree* biTree)
	{
		BiTree biTempTree;
		biTempTree = (*biTree)->rchild;
		(*biTree)->rchild = biTempTree->lchild;
		biTempTree->lchild = (*biTree);
		*biTree = biTempTree;
	}

	void LeftBalance(BiTree* biTree)
	{
		auto leftTree = (*biTree)->lchild;
		switch (leftTree->balance)
		{
		case LH:
			(*biTree)->balance = leftTree->balance = EH;
			R_Rotate(biTree);
			break;
		case RH:
			auto rightChild = leftTree->rchild;
			switch (rightChild->balance)
			{
			case LH:
				(*biTree)->balance = RH;
				leftTree->balance = EH;
				break;
			case EH:
				(*biTree)->balance = leftTree->balance = EH;
				break;
			case RH:
				(*biTree)->balance = EH;
				leftTree->balance = LH;
				break;
			}
			rightChild->balance = EH;
			L_Rotate(&(*biTree)->lchild);
			R_Rotate(biTree);
			break;
		}
	}

	void RightBalance(BiTree* biTree)
	{
		auto rightTree = (*biTree)->rchild;
		switch (rightTree->balance)
		{
		case RH:
			(*biTree)->balance = rightTree->balance = EH;
			L_Rotate(biTree);
			break;
		case LH:
			auto leftChild = rightTree->lchild;
			switch (leftChild->balance)
			{
			case RH:
				(*biTree)->balance = LH;
				rightTree->balance = EH;
				break;
			case EH:
				(*biTree)->balance = rightTree->balance = EH;
				break;
			case LH:
				(*biTree)->balance = EH;
				rightTree->balance = RH;
				break;
			}
			leftChild->balance = EH;
			R_Rotate(&(*biTree)->rchild);
			L_Rotate(biTree);
			break;
		}
	}

	bool InsertAVL_i(BiTree* biTree, const ElemType eData, bool& bTaller)
	{
		if (!(*biTree))
		{
			(*biTree) = static_cast<BiTree>(malloc(sizeof(BiTNode)));
			(*biTree)->data = eData;
			(*biTree)->lchild = (*biTree)->rchild = nullptr;
			(*biTree)->balance = EH;
			bTaller = true;
			return true;
		}
		else
		{
			if (eData == (*biTree)->data)
			{
				bTaller = false;
				return false;
			}
			if (eData < (*biTree)->data)
			{
				if (!InsertAVL_i(&(*biTree)->lchild, eData, bTaller))
				{
					return false;
				}
				if (bTaller)
				{
					switch ((*biTree)->balance)
					{
					case LH:
						LeftBalance(biTree);
						bTaller = false;
						break;
					case EH:
						(*biTree)->balance = LH;
						bTaller = true;
						break;
					case RH:
						(*biTree)->balance = EH;
						bTaller = false;
						break;
					default:
						break;
					}
				}
			}
			else
			{
				if (!InsertAVL_i(&(*biTree)->rchild, eData, bTaller))
				{
					return false;
				}
				if (bTaller)
				{
					switch ((*biTree)->balance)
					{
					case LH:
						(*biTree)->balance = EH;
						bTaller = false;
						break;
					case EH:
						(*biTree)->balance = RH;
						bTaller = true;
						break;
					case RH:
						RightBalance(biTree);
						bTaller = false;
						break;
					}
				}
			}
			return true;
		}
	}
}

class BinaryTree :public Tree
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
	BiTree Root() const;
	BiTree Parent(const ElemType& eFindData) const;
	BiTree LeftChild(const ElemType& eFindData) const;
	BiTree RightSibling(const ElemType& eFindData) const;
	void InsertChild(const ElemType& eFindData, const ElemType& eInsertData);
	void DeletChilde(const ElemType& eFindData);

public:
	//¶þ²æÅÅÐòÊ÷
	bool InsertBST(const ElemType eData);
	bool SearchBST(const ElemType eData, BiTree* biTreeNode);
	bool DeleteBST(const ElemType eData);
	
public:
	//Æ½ºâ¶þ²æÊ÷
	bool InsertAVL(const ElemType eData);
private:
	BiTree m_pBiTree;
};

bool BinaryTree::InsertAVL(const ElemType eData)
{
	if (!m_pBiTree)
	{
		m_pBiTree = static_cast<BiTree>(malloc(sizeof(BiTNode)));
		m_pBiTree->data = eData;
		m_pBiTree->lchild = m_pBiTree->rchild = nullptr;
		m_pBiTree->balance = EH;
		return true;
	}
	else
	{
		if (eData == m_pBiTree->data)
		{
			return false;
		}
		bool bTaller(false);
		if (eData < m_pBiTree->data)
		{
			if (!InsertAVL_i(&m_pBiTree->lchild, eData, bTaller))
			{
				return false;
			}
			if (bTaller)
			{
				switch (m_pBiTree->balance)
				{
				case LH:
					LeftBalance(&m_pBiTree);
					break;
				case EH:
					m_pBiTree->balance = LH;
					break;
				case RH:
					m_pBiTree->balance = EH;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			if (!InsertAVL_i(&m_pBiTree->rchild, eData, bTaller))
			{
				return false;
			}
			if (bTaller)
			{
				switch (m_pBiTree->balance)
				{
				case LH:
					m_pBiTree->balance = EH;
					break;
				case EH:
					m_pBiTree->balance = RH;
					break;
				case RH:
					RightBalance(&m_pBiTree);
					break;
				}
			}
		}
		return true;
	}
}

bool BinaryTree::InsertBST(const ElemType eData)
{
	BiTree biTreeNode(nullptr), biTreeInsert(nullptr);
	if (!SearchBST(eData, &biTreeNode))
	{
		biTreeInsert = static_cast<BiTree>(malloc(sizeof(BiTNode)));
		biTreeInsert->data = eData;
		biTreeInsert->lchild = biTreeInsert->rchild = nullptr;
		if (!biTreeNode)
		{
			m_pBiTree = biTreeInsert;
		}
		else if (eData < biTreeNode->data)
		{
			biTreeNode->lchild = biTreeInsert;
		}
		else
		{
			biTreeNode->rchild = biTreeInsert;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool BinaryTree::SearchBST(const ElemType eData, BiTree* biTreeNode)
{
	if (!m_pBiTree)
	{
		biTreeNode = nullptr;
		return false;
	}
	else if (eData == m_pBiTree->data)
	{
		*biTreeNode = m_pBiTree;
		return true;
	}
	else if (eData < m_pBiTree->data)
	{
		SearchBST_i(m_pBiTree->lchild, eData, m_pBiTree, biTreeNode);
	}
	else
	{
		SearchBST_i(m_pBiTree->rchild, eData, m_pBiTree, biTreeNode);
	}
}

bool BinaryTree::DeleteBST(const ElemType eData)
{
	if (!m_pBiTree)
	{
		return false;
	}
	else
	{
		if (eData == m_pBiTree->data)
		{
			return Delete_i(&m_pBiTree);
		}
		else if (eData < m_pBiTree->data)
		{
			return DeleteBST_i(&m_pBiTree->lchild, eData);
		}
		else
		{
			return DeleteBST_i(&m_pBiTree->rchild, eData);
		}
	}
}

void BinaryTree::InitTree()
{

}

void BinaryTree::DestroyTree()
{

}

void BinaryTree::CreateTree()
{
	std::cout << "Create BinaryTree Begin:" << std::endl;
	ElemType ch = getchar();
	if ('#' == ch)
	{
		m_pBiTree = nullptr;
	}
	else
	{
		m_pBiTree = static_cast<BiTree>(malloc(sizeof(BiTNode)));
		m_pBiTree->data = ch;
		CreateTreeNode(&m_pBiTree->lchild);
		CreateTreeNode(&m_pBiTree->rchild);
	}
}

void BinaryTree::ClearTree()
{

}

bool BinaryTree::TreeEmpty() const
{
	return true;
}

int BinaryTree::TreeDepth() const
{
	return 0;
}

ElemType BinaryTree::Value() const
{
	return 0;
}

void BinaryTree::Assign(const ElemType& eFindData, const ElemType& eAssignData)
{

}

void BinaryTree::TreePreview()const
{
	switch (m_eTraverseOrder)
	{
	case PreOrder:
		std::cout << "PreOrder Traverse:" << std::endl;
		PreOrderTraverse(m_pBiTree);
		break;
	case InOrder:
		std::cout << "InOrder Traverse:" << std::endl;
		InOrderTraverse(m_pBiTree);
		break;
	case PostOrder:
		std::cout << "PostOrder Traverse:" << std::endl;
		PostOrderTraverse(m_pBiTree);
		break;
	default:
		break;
	}
}
#endif // !DATA_STRUCT_BINARY_TREE

