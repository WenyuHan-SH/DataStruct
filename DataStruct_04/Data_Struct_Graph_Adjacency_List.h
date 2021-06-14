#ifndef DATA_STRUCT_GRAPH_ADJACENCY_LIST
#define DATA_STRUCT_GRAPH_ADJACENCY_LIST
#include "Data_Struct_Graph_Base.h"
#include <stack>

class GraphAdjacencyList :public Graph
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
public:
	void CreatePSGraph();
	void TopologicalSort();
	void CriticalPath();
private:
	void DFS(const int& iIndex) const override;
	void HFS() const override;
private:
	LGraph m_LGraph;
	PSgraphAdjList m_PSGraph;
	std::stack<int> m_stack;
	int m_etv[MAXVEX];
	int m_ltv[MAXVEX];
};

void GraphAdjacencyList::CreateGraph()
{
	std::cout << "请输入顶点数和边数:" << std::endl;
	std::cin >> m_LGraph.numVertexes >> m_LGraph.numEdges;
	std::cout << "请输入顶点信息:" << std::endl;
	for (int i = 0; i < m_LGraph.numVertexes; ++i)
	{
		std::cin >> m_LGraph.adjList[i].data;
		m_LGraph.adjList[i].firstedge = nullptr;
	}

	int iNode(0), jNode(0);
	for (int i = 0; i < m_LGraph.numEdges; ++i)
	{
		std::cout << "请输入边(vi,vj)上的顶点序号:" << std::endl;
		std::cin >> iNode;
		std::cin >> jNode;

		EdgeNode* jEdgeNode = static_cast<EdgeNode*>(malloc(sizeof(EdgeNode)));
		jEdgeNode->adjvex = jNode;
		jEdgeNode->next = m_LGraph.adjList[iNode].firstedge;
		m_LGraph.adjList[iNode].firstedge = jEdgeNode; //头插法

		EdgeNode* iEdgeNode = static_cast<EdgeNode*>(malloc(sizeof(EdgeNode)));
		iEdgeNode->adjvex = iNode;
		iEdgeNode->next = m_LGraph.adjList[jNode].firstedge;
		m_LGraph.adjList[jNode].firstedge = iEdgeNode;
	}
}

void GraphAdjacencyList::CreatePSGraph()
{
	std::cout << "请输入顶点数和边数:" << std::endl;
	std::cin >> m_PSGraph.numVertexes >> m_PSGraph.numEdges;
	for (int i = 0; i < m_PSGraph.numVertexes; ++i)
	{
		std::cout << "请输入入度和顶点信息:" << std::endl;
		std::cin >> m_PSGraph.adjList[i].in;
		std::cin >> m_PSGraph.adjList[i].data;
		m_PSGraph.adjList[i].firstedge = nullptr;
	}

	int iNode(0), jNode(0), weight(0);
	for (int i = 0; i < m_PSGraph.numEdges; ++i)
	{
		std::cout << "请输入边(vi,vj)上的顶点序号和权值:" << std::endl;
		std::cin >> iNode;
		std::cin >> jNode;
		std::cin >> weight;

		PSEdgeNode* jEdgeNode = static_cast<PSEdgeNode*>(malloc(sizeof(PSEdgeNode)));
		jEdgeNode->adjvex = jNode;
		jEdgeNode->weight = weight;
		jEdgeNode->next = m_PSGraph.adjList[iNode].firstedge;
		m_PSGraph.adjList[iNode].firstedge = jEdgeNode; //头插法
	}
}

void GraphAdjacencyList::DestroyGraph()
{

}

int GraphAdjacencyList::LocateVex(const VertexType& value) const
{
	return NULL;
}

VertexType GraphAdjacencyList::GetVex(const int& iIndex)const
{
	return NULL;
}

void  GraphAdjacencyList::PutVex(const int& iIndex, const VertexType& value)
{

}

int GraphAdjacencyList::FirstAdjVex(const int& iIndex)const
{
	return NULL;
}

int GraphAdjacencyList::NextAdjVex(const int& iIndex, const int& iPreIndex)const
{
	return NULL;
}

void GraphAdjacencyList::InsertVex(const int& iIndex)
{

}

void GraphAdjacencyList::InsertArc(const int& iFirIndex, const int& iSecIndex)
{

}

void GraphAdjacencyList::DeleteArc(const int& iFirIndex, const int& iSecIndex)
{

}

void GraphAdjacencyList::DFSTraverse() const
{
	for (int i = 0; i < m_LGraph.numVertexes; ++i)
	{
		if (!visited[i])
		{
			DFS(i);
		}
	}
	for (int i = 0; i < MAXVEX; ++i)
	{
		visited[i] = false;
	}
	std::cout << std::endl;
}

void GraphAdjacencyList::HFSTraverse() const
{
	std::queue<int> Queue;
	for (int i = 0; i < m_LGraph.numVertexes; ++i)
	{
		if (!visited[i])
		{
			visited[i] = true;
			std::cout << " " << m_LGraph.adjList[i].data;
			Queue.push(i);
			while (!Queue.empty())
			{
				int tempNode(Queue.front());
				Queue.pop();
				auto adjEdge = m_LGraph.adjList[tempNode].firstedge;
				while (adjEdge)
				{
					if (!visited[adjEdge->adjvex])
					{
						visited[adjEdge->adjvex] = true;
						std::cout << " " << m_LGraph.adjList[adjEdge->adjvex].data;
						Queue.push(adjEdge->adjvex);
					}
					adjEdge = adjEdge->next;
				}
			}
		}
	}
}

void GraphAdjacencyList::DFS(const int& iIndex) const
{
	visited[iIndex] = true;
	EdgeNode* pEdgeNode = m_LGraph.adjList[iIndex].firstedge;
	std::cout << m_LGraph.adjList[iIndex].data << " ";
	while (pEdgeNode)
	{
		if (!visited[pEdgeNode->adjvex])
		{
			DFS(pEdgeNode->adjvex);
		}
		pEdgeNode = pEdgeNode->next;
	}
}

void GraphAdjacencyList::HFS() const
{

}

void GraphAdjacencyList::TopologicalSort()
{
	std::stack<int> stack;
	for (int i = 0; i < m_PSGraph.numVertexes; ++i)
	{
		if (0 == m_PSGraph.adjList[i].in)
		{
			stack.push(i);
		}
	}
	int count(0);
	while (!stack.empty())
	{
		auto gettop = stack.top();
		stack.pop();
		m_stack.push(gettop);
		std::cout << m_PSGraph.adjList[gettop].data << " -> ";

		count++;
		auto e = m_PSGraph.adjList[gettop].firstedge;
		while (e)
		{
			if (!(--m_PSGraph.adjList[e->adjvex].in))
			{
				stack.push(e->adjvex);
			}
			if ((m_etv[gettop] + e->weight) > m_etv[e->adjvex])
			{
				m_etv[e->adjvex] = m_etv[gettop] + e->weight;
			}
			e = e->next;
		}
	}
	std::cout << std::endl;
}

void GraphAdjacencyList::CriticalPath()
{
	for (int i = 0; i < MAXVEX; ++i)
	{
		m_etv[i] = 0;
		m_ltv[i] = 0;
	}
	int ete(0), lte(0);
	TopologicalSort();
	for (int i = 0; i < m_PSGraph.numVertexes; ++i)
	{
		m_ltv[i] = m_etv[m_PSGraph.numVertexes - 1];
	}
	while (!m_stack.empty())
	{
		auto gettop = m_stack.top();
		m_stack.pop();
		auto e = m_PSGraph.adjList[gettop].firstedge;
		while (e)
		{
			auto k = e->adjvex;
			if (m_ltv[k] - e->weight < m_ltv[gettop])
			{
				m_ltv[gettop] = m_ltv[k] - e->weight;
			}
			e = e->next;
		}
	}

	for (int j = 0; j < m_PSGraph.numVertexes; ++j)
	{
		auto e = m_PSGraph.adjList[j].firstedge;
		while (e)
		{
			auto k = e->adjvex;
			ete = m_etv[j];
			lte = m_ltv[k] - e->weight;
			if (ete == lte)
			{
				std::cout << " <v" << m_PSGraph.adjList[j].data << ",v"
					<< m_PSGraph.adjList[k].data << "> length: " << e->weight;
			}
			e = e->next;
		}
	}
}

#endif // !DATA_STRUCT_GRAPH_ADJACENCY_LIST

