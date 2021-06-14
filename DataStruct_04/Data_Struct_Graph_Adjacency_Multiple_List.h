#ifndef DATA_STRUCT_GRAPH_ADJACENCY_MULTIPLE_LIST
#define DATA_STRUCT_GRAPH_ADJACENCY_MULTIPLE_LIST
#include "Data_Struct_Graph_Base.h"
class AdjacencyMultipleList :public Graph
{
public:
	void CreateGraph() override;
	void DestroyGraph() override;
	int LocateVex(const VertexType& value) const override;
	VertexType GetVex(const int& iIndex)const override;
	void  PutVex(const int& iIndex, const VertexType& value)override;
	int FirstAdjVex(const int& iIndex)const override;
	int NextAdjVex(const int& iIndex, const int& iPreIndex)const override;
	void InsertVex(const int& iIndex);
	void InsertArc(const int& iFirIndex, const int& iSecIndex) override;
	void DeleteArc(const int& iFirIndex, const int& iSecIndex) override;
	void DFSTraverse() const override;
	void HFSTraverse() const override;
private:
	void DFS(const int& iIndex) const override;
	void HFS() const override;
private:
	AMGraph m_AMGraph;
};
void AdjacencyMultipleList::CreateGraph()
{
	std::cout << "请输入顶点数和边数:" << std::endl;
	std::cin >> m_AMGraph.numVertexes >> m_AMGraph.numEdges;

	std::cout << "请输入顶点信息:" << std::endl;
	for (int i = 0; i < m_AMGraph.numVertexes; ++i)
	{
		std::cin >> m_AMGraph.amList[i].data;
		m_AMGraph.amList[i].firstedge = nullptr;
	}

	for (int k = 0; k < m_AMGraph.numEdges; ++k)
	{
		std::cout << "请输入边(vi,vj)上的顶点序号:" << std::endl;
		VertexType first(0);
		VertexType second(0);
		std::cin >> first >> second;
		AMEdgeNode* amEdgeNode = static_cast<AMEdgeNode*>(malloc(sizeof(AMEdgeNode)));
		amEdgeNode->ivex = first;
		amEdgeNode->jvex = second;

		amEdgeNode->ilink = m_AMGraph.amList[first].firstedge;
		m_AMGraph.amList[first].firstedge = amEdgeNode;

		amEdgeNode->jlink = m_AMGraph.amList[second].firstedge;
		m_AMGraph.amList[second].firstedge = amEdgeNode;
	}
}

void AdjacencyMultipleList::DestroyGraph()
{

}

int AdjacencyMultipleList::LocateVex(const VertexType& value) const
{
	return NULL;
}

VertexType AdjacencyMultipleList::GetVex(const int& iIndex)const
{
	return NULL;
}

void  AdjacencyMultipleList::PutVex(const int& iIndex, const VertexType& value)
{

}

int AdjacencyMultipleList::FirstAdjVex(const int& iIndex)const
{
	return NULL;
}

int AdjacencyMultipleList::NextAdjVex(const int& iIndex, const int& iPreIndex)const
{
	return NULL;
}

void AdjacencyMultipleList::InsertVex(const int& iIndex)
{

}

void AdjacencyMultipleList::InsertArc(const int& iFirIndex, const int& iSecIndex)
{

}

void AdjacencyMultipleList::DeleteArc(const int& iFirIndex, const int& iSecIndex)
{

}

void AdjacencyMultipleList::DFSTraverse() const
{

}

void AdjacencyMultipleList::HFSTraverse() const
{

}

void AdjacencyMultipleList::DFS(const int& iIndex) const
{

}

void AdjacencyMultipleList::HFS() const
{

}
#endif // !DATA_STRUCT_GRAPH_ADJACENCY_MULTIPLE_LIST

