#ifndef DATA_STRUCT_GRAPH_ADJACENCY_MATRIX
#define DATA_STRUCT_GRAPH_ADJACENCY_MATRIX
#include "Data_Struct_Graph_Base.h"
#include <queue>
namespace
{
	const int CHESSX = 8;
	const int CHESSY = 8;
	bool visited[MAXVEX] = { false };
	int ChessVisited[CHESSX][CHESSY] = { 0 };

	enum NEXT_POSITION
	{
		TOP_LEFT_X = 1,
		TOP_LEFT_Y,
		TOP_RIGHT_X,
		TOP_RIGHT_Y,
		BUTTON_LEFT_X,
		BUTTON_LEFT_Y,
		BUTTON_RIGHT_X,
		BUTTON_RIGHT_Y
	};

	bool NextPosition(int& x, int& y, const NEXT_POSITION& nextPosion)
	{
		switch (nextPosion)
		{
		case TOP_LEFT_X:
		{
			if (x - 2 >= 0 && y - 1 >= 0 && !ChessVisited[x - 2][y - 1])
			{
				x -= 2;
				y -= 1;
				return true;
			}
			break;
		}
		case TOP_LEFT_Y:
		{
			if (x - 1 >= 0 && y - 2 >= 0 && !ChessVisited[x - 1][y - 2])
			{
				x -= 1;
				y -= 2;
				return true;
			}
			break;
		}
		case TOP_RIGHT_X:
		{
			if (x + 2 <= CHESSX - 1 && y - 1 >= 0 && !ChessVisited[x + 2][y - 1])
			{
				x += 2;
				y -= 1;
				return true;
			}
			break;
		}
		case TOP_RIGHT_Y:
		{
			if (x + 1 <= CHESSX - 1 && y - 2 >= 0 && !ChessVisited[x + 1][y - 2])
			{
				x += 1;
				y -= 2;
				return true;
			}
			break;
		}
		case BUTTON_LEFT_X:
		{
			if (x - 2 >= 0 && y + 1 <= CHESSY - 1 && !ChessVisited[x - 2][y + 1])
			{
				x -= 2;
				y += 1;
				return true;
			}
			break;
		}
		case BUTTON_LEFT_Y:
		{
			if (x - 1 >= 0 && y + 2 <= CHESSY - 1 && !ChessVisited[x - 1][y + 2])
			{
				x -= 1;
				y += 2;
				return true;
			}
			break;
		}
		case BUTTON_RIGHT_X:
		{
			if (x + 2 <= CHESSX - 1 && y + 1 <= CHESSY - 1 && !ChessVisited[x + 2][y + 1])
			{
				x += 2;
				y += 1;
				return true;
			}
			break;
		}
		case BUTTON_RIGHT_Y:
		{
			if (x + 1 <= CHESSX - 1 && y + 2 <= CHESSY - 1 && !ChessVisited[x + 1][y + 2])
			{
				x += 1;
				y += 2;
				return true;
			}
			break;
		}
		}
		return false;
	}

	bool TravelChess(const int& x, const int& y, int iTag)
	{
		int iOriX(x), iOriY(y);
		NEXT_POSITION ePosition(TOP_LEFT_X);
		ChessVisited[x][y] = iTag;

		if (CHESSX * CHESSY == iTag)
		{
			for (int i = 0; i < CHESSX; ++i)
			{
				for (int j = 0; j < CHESSY; ++j)
				{
					std::cout << " " << ChessVisited[i][j];
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			return true;
		}

		bool Flag(NextPosition(iOriX, iOriY, ePosition));
		while (!Flag && ePosition < BUTTON_RIGHT_Y)
		{
			ePosition = static_cast<NEXT_POSITION>(ePosition + 1);
			Flag = NextPosition(iOriX, iOriY, ePosition);
		}

		while (Flag)
		{
			if (TravelChess(iOriX, iOriY, iTag + 1))
			{
				return true;
			}

			//失败后寻找
			iOriX = x;
			iOriY = y;
			ePosition = static_cast<NEXT_POSITION>(ePosition + 1);
			Flag = NextPosition(iOriX, iOriY, ePosition);
			while (!Flag && ePosition < BUTTON_RIGHT_Y)
			{
				ePosition = static_cast<NEXT_POSITION>(ePosition + 1);
				Flag = NextPosition(iOriX, iOriY, ePosition);
			}
		}

		if (!Flag)
		{
			ChessVisited[x][y] = 0;
		}
		return false;
	}

	int Find(const std::vector<int>& vecParent, const int& f)
	{
		int temp(f);
		while (vecParent[temp] > 0 && temp != vecParent.size())
		{
			temp = vecParent[temp];
		}
		return temp;
	}
}

class GraphAdjacencyMatrix :public Graph
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
	void TravelChessBoard(const int& x, const int& y);
	void MiniSpanTree_Prim();
	void MiniSpanTree_Kruskal();
	void ShortestPath_Dijkstra(const int& v0);
	void ShortestPath_Ployd();
private:
	void DFS(const int& iIndex) const override;
	void HFS() const override;
private:
	MGraph m_MGraph;
	std::vector<Kruskal_Edge> m_vecKruskalEdges;
};

void GraphAdjacencyMatrix::CreateGraph()
{
	std::cout << "请输入顶点数和边数:" << std::endl;
	std::cin >> m_MGraph.numVertexes >> m_MGraph.numEdges;

	std::cout << "请输入顶点信息:" << std::endl;
	for (int i = 0; i < m_MGraph.numVertexes; ++i)
	{
		std::cin >> m_MGraph.vexs[i];
	}

	for (int i = 0; i < m_MGraph.numVertexes; ++i)
	{
		for (int j = 0; j < m_MGraph.numVertexes; j++)
		{
			m_MGraph.arc[i][j] = INFINITY;
		}
	}

	for (int k = 0; k < m_MGraph.numEdges; ++k)
	{
		std::cout << "请输入边(vi,vj)上的下标i,下标j和权w:" << std::endl;
		int i(0), j(0), w(0);
		std::cin >> i;
		std::cin >> j;
		std::cin >> w;
		m_MGraph.arc[i][j] = w;
		m_MGraph.arc[j][i] = w;
		m_vecKruskalEdges.push_back(Kruskal_Edge(i, j, w));
	}
}

void GraphAdjacencyMatrix::DestroyGraph()
{

}

int GraphAdjacencyMatrix::LocateVex(const VertexType& value) const
{
	return NULL;
}

VertexType GraphAdjacencyMatrix::GetVex(const int& iIndex)const
{
	return NULL;
}

void  GraphAdjacencyMatrix::PutVex(const int& iIndex, const VertexType& value)
{

}

int GraphAdjacencyMatrix::FirstAdjVex(const int& iIndex)const
{
	return NULL;
}

int GraphAdjacencyMatrix::NextAdjVex(const int& iIndex, const int& iPreIndex)const
{
	return NULL;
}

void GraphAdjacencyMatrix::InsertVex(const int& iIndex)
{

}

void GraphAdjacencyMatrix::InsertArc(const int& iFirIndex, const int& iSecIndex)
{

}

void GraphAdjacencyMatrix::DeleteArc(const int& iFirIndex, const int& iSecIndex)
{

}

void GraphAdjacencyMatrix::DFSTraverse() const
{
	for (int i = 0; i < m_MGraph.numVertexes; ++i)
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

void GraphAdjacencyMatrix::DFS(const int& iIndex) const
{
	visited[iIndex] = true;
	std::cout << m_MGraph.vexs[iIndex] << " ";
	for (int i = 0; i < m_MGraph.numVertexes; ++i)
	{
		if (m_MGraph.arc[iIndex][i] != INFINITY && !visited[i])
		{
			DFS(i);
		}
	}
}

void GraphAdjacencyMatrix::TravelChessBoard(const int& x, const int& y)
{
	TravelChess(x, y, 1);
}

void GraphAdjacencyMatrix::HFSTraverse() const
{
	std::queue<int> Queue;
	for (int i = 0; i < m_MGraph.numVertexes; ++i)
	{
		if (!visited[i])
		{
			visited[i] = true;
			std::cout << " " << m_MGraph.vexs[i];
			Queue.push(i);
			while (!Queue.empty())
			{
				int tempNode(Queue.front());
				Queue.pop();
				for (int j = 0; j < m_MGraph.numVertexes; ++j)
				{
					if (m_MGraph.arc[tempNode][j] != INFINITY && !visited[j])
					{
						visited[j] = true;
						std::cout << " " << m_MGraph.vexs[j];
						Queue.push(j);
					}
				}
			}
		}
	}
	std::cout << std::endl;
}

void GraphAdjacencyMatrix::HFS() const
{

}

void GraphAdjacencyMatrix::MiniSpanTree_Prim()
{
	int adjvex[MAXVEX] = { 0 };
	int lowcost[MAXVEX] = { 0 };
	for (int i = 0; i < m_MGraph.numVertexes; ++i)
	{
		for (int j = 0; j < m_MGraph.numVertexes; ++j)
		{
			if (i == j)
			{
				m_MGraph.arc[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < m_MGraph.numVertexes; ++i)
	{
		lowcost[i] = m_MGraph.arc[0][i];
	}
	for (int i = 1; i < m_MGraph.numVertexes; ++i)
	{
		int min(INFINITY), j(1), k(0);
		while (j < m_MGraph.numVertexes)
		{
			if (0 != lowcost[j] && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		std::cout << "(" << adjvex[k] << ", " << k << ")";
		lowcost[k] = 0;
		for (int j = 0; j < m_MGraph.numVertexes; ++j)
		{
			if (0 != lowcost[j] && m_MGraph.arc[k][j] < lowcost[j])
			{
				lowcost[j] = m_MGraph.arc[k][j];
				adjvex[j] = k;
			}
		}
	}
	std::cout << std::endl;
}

void GraphAdjacencyMatrix::MiniSpanTree_Kruskal()
{
	//int parent[MAXVEX] = { 0 };
	std::vector<int> parent;
	parent.assign(MAXVEX, 0);
	std::sort(m_vecKruskalEdges.begin(), m_vecKruskalEdges.end());

	for (int i = 0; i < m_MGraph.numEdges; ++i)
	{
		int n = Find(parent, m_vecKruskalEdges[i].begin);
		int m = Find(parent, m_vecKruskalEdges[i].end);
		if (n!=m)
		{
			parent[n] = m;
			std::cout << "(" << m_vecKruskalEdges[i].begin
				<< "," << m_vecKruskalEdges[i].end << ")";
		}
	}
}

void GraphAdjacencyMatrix::ShortestPath_Dijkstra(const int& v0)
{
	for (int i = 0; i < m_MGraph.numVertexes; ++i)
	{
		for (int j = 0; j < m_MGraph.numVertexes; ++j)
		{
			if (i == j)
			{
				m_MGraph.arc[i][j] = 0;
			}
		}
	}

	int final[MAXVEX] = { 0 };
	int D[MAXVEX] = { 0 };
	int P[MAXVEX] = { 0 };
	for (int  v = 0; v < m_MGraph.numVertexes; ++v)
	{
		D[v] = m_MGraph.arc[v0][v];
	}
	D[v0] = 0;
	P[0] = v0;
	final[v0] = 1;
	int k(0);
	for (int v = 0; v < m_MGraph.numVertexes; ++v)
	{
		int min(INFINITY);
		for (int w = 0; w < m_MGraph.numVertexes; ++w)
		{
			if (!final[w] && D[w] < min)
			{
				k = w;
				min = D[w];
			}
		}
		final[k] = 1;
		for (int w = 0; w < m_MGraph.numVertexes; ++w)
		{
			if (!final[w] && (min + m_MGraph.arc[k][w]) < D[w])
			{
				D[w] = min + m_MGraph.arc[k][w];
				P[w] = k;
			}
		}
	}
}

void GraphAdjacencyMatrix::ShortestPath_Ployd()
{
	int D[MAXVEX][MAXVEX] = { 0 };
	int P[MAXVEX][MAXVEX] = { 0 };
	for (int v = 0; v < m_MGraph.numVertexes; ++v)
	{
		for (int w = 0; w < m_MGraph.numVertexes; ++w)
		{
			if (v == w)
			{
				m_MGraph.arc[v][w] = 0;
			}
			D[v][w] = m_MGraph.arc[v][w];
			P[v][w] = w;
		}
	}

	for (int k = 0; k < m_MGraph.numVertexes; ++k)
	{
		for (int v = 0; v < m_MGraph.numVertexes; ++v)
		{
			for (int w = 0; w < m_MGraph.numVertexes; ++w)
			{
				if (D[v][w] > D[v][k] + D[k][w])
				{
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k];
				}
			}
		}
	}

	int k(0);
	for (int v = 0; v < m_MGraph.numVertexes; ++v)
	{
		for (int w = v + 1; w < m_MGraph.numVertexes; ++w)
		{
			std::cout << " v" << v << "-v" << w << " weight:" << D[v][w];
			k = P[v][w];
			std::cout << " path: " << v;
			while (k != w)
			{
				std::cout << "-> " << k;
				k = P[k][w];
			}
			std::cout << "-> " << w << std::endl;
		}
		std::cout << std::endl;
	}
}
#endif // !DATA_STRUCT_GRAPH_ADJACENCY_MATRIX

