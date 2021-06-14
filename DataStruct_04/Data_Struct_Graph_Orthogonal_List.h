#ifndef DATA_STRUCT_GRAPH_ORTHOGONAL_LIST
#define DATA_STRUCT_GRAPH_ORTHOGONAL_LIST
#include "Data_Struct_Graph_Base.h"

class OrthogonalList:public Graph
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
	OLGraph m_OLGraph;
};
void OrthogonalList::CreateGraph()
{
	std::cout << "请输入顶点数和边数:" << std::endl;
	std::cin >> m_OLGraph.numVertexes >> m_OLGraph.numEdges;

	std::cout << "请输入顶点信息:" << std::endl;
	for (int i = 0; i < m_OLGraph.numVertexes; ++i)
	{
		std::cin >> m_OLGraph.olList[i].data;
		m_OLGraph.olList[i].firstin = nullptr;
		m_OLGraph.olList[i].firstout = nullptr;
	}

	for (int k = 0; k < m_OLGraph.numEdges; ++k)
	{
		std::cout << "请输入边(vi,vj)上的顶点序号:" << std::endl;
		VertexType first(0);
		VertexType second(0);
		std::cin >> first >> second;
		OLEdgeNode* olEdgeNode = static_cast<OLEdgeNode*>(malloc(sizeof(OLEdgeNode)));
		olEdgeNode->tailvex = first;
		olEdgeNode->headvex = second;

		olEdgeNode->taillink = m_OLGraph.olList[first].firstout;
		m_OLGraph.olList[first].firstout = olEdgeNode;

		olEdgeNode->headlink = m_OLGraph.olList[second].firstin;
		m_OLGraph.olList[first].firstin = olEdgeNode;
	}
}

void OrthogonalList::DestroyGraph()
{

}

int OrthogonalList::LocateVex(const VertexType& value) const
{
	return NULL;
}

VertexType OrthogonalList::GetVex(const int& iIndex)const
{
	return NULL;
}

void  OrthogonalList::PutVex(const int& iIndex, const VertexType& value)
{

}

int OrthogonalList::FirstAdjVex(const int& iIndex)const
{
	return NULL;
}

int OrthogonalList::NextAdjVex(const int& iIndex, const int& iPreIndex)const
{
	return NULL;
}

void OrthogonalList::InsertVex(const int& iIndex)
{

}

void OrthogonalList::InsertArc(const int& iFirIndex, const int& iSecIndex)
{

}

void OrthogonalList::DeleteArc(const int& iFirIndex, const int& iSecIndex)
{

}

void OrthogonalList::DFSTraverse() const
{

}

void OrthogonalList::HFSTraverse() const
{

}

void OrthogonalList::DFS(const int& iIndex) const
{

}

void OrthogonalList::HFS() const
{

}
#endif // !DATA_STRUCT_GRAPH_ORTHOGONAL_LIST

