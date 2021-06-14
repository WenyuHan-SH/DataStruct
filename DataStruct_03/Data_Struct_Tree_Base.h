#ifndef DATA_STRUCT_TREE_BASE
#define DATA_STRUCT_TREE_BASE
#include "Data_Struct_Tree_Define.h"

class Tree
{
public:
	virtual void InitTree() = 0;
	virtual void DestroyTree() = 0;
	virtual void CreateTree() = 0;
	virtual void ClearTree() = 0;
	virtual bool TreeEmpty()const = 0;
	virtual int TreeDepth() const = 0;
	virtual ElemType Value() const = 0;
	virtual void Assign(const ElemType& eFindData, const ElemType& eAssignData) = 0;
	virtual void TreePreview()const = 0;
	void SetTraverOrder(const Traverse& eTraverseOrder);
protected:
	Traverse m_eTraverseOrder;
};

void Tree::SetTraverOrder(const Traverse& eTraverseOrder)
{
	m_eTraverseOrder = eTraverseOrder;
}

#endif // !DATA_STRUCT_TREE_BASE
