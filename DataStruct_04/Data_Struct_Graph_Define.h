#ifndef DATA_STRUCT_GRAPH_DEFINE
#define DATA_STRUCT_GRAPH_DEFINE
#include <iostream>

typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define MAXEDGE 100
#define INFINITY 65535

//邻接矩阵
typedef struct
{
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes;
	int numEdges;
} MGraph;

//邻接表
typedef struct EdgeNode
{
	int adjvex;
	EdgeType weight;
	struct EdgeNode* next;
} EdgeNode;

typedef struct VertexNode
{
	VertexType data;
	EdgeNode* firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes;
	int numEdges;
}LGraph;

//十字链表
typedef struct OLEdgeNode
{
	int tailvex;
	int headvex;
	EdgeType weight;
	struct OLEdgeNode* headlink;
	struct OLEdgeNode* taillink;
} OLEdgeNode;

typedef struct OLNode
{
	VertexType data;
	OLEdgeNode* firstin;
	OLEdgeNode* firstout;
} OLNode, OLList[MAXVEX];

typedef struct
{
	OLList olList;
	int numVertexes;
	int numEdges;
}OLGraph;

//邻接多重表
typedef struct AMEdgeNode
{
	int ivex;
	int jvex;
	EdgeType weight;
	struct AMEdgeNode* ilink;
	struct AMEdgeNode* jlink;
} AMEdgeNode;

typedef struct AMVertexNode
{
	VertexType data;
	AMEdgeNode* firstedge;
} AMVertexNode, AMList[MAXVEX];

typedef struct
{
	AMList amList;
	int numVertexes;
	int numEdges;
}AMGraph;

//Kruskal_Edge
struct Kruskal_Edge
{
	Kruskal_Edge(const int& iBegin, const int& iEnd, const int& iWeight)
		:begin(iBegin), end(iEnd), weight(iWeight)
	{}
	bool operator < (const Kruskal_Edge& edge) { return weight < edge.weight; }
	int begin;
	int end;
	int weight;
};

//PologicalSort
typedef struct PSEdgeNode
{
	int adjvex;
	int weight;
	struct PSEdgeNode* next;
} PSEdgeNode;

typedef struct PSVertexNode
{
	int in;
	char data;
	PSEdgeNode* firstedge;
}PSVertexNode, PSAdjList[MAXVEX];

typedef struct
{
	PSAdjList adjList;
	int numVertexes;
	int numEdges;
}PSgraphAdjList, * PSGraphAdjList;
#endif // !DATA_STRUCT_GRAPH_DEFINE

