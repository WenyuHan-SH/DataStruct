#include "Data_Struct_Graph_Adjacency_Matrix.h"
#include "Data_Struct_Graph_Adjacency_List.h"
#include "Data_Struct_Graph_Orthogonal_List.h"
#include "Data_Struct_Graph_Adjacency_Multiple_List.h"

void TestChessBoard()
{
	auto spGraphAdjacencyMatrix = std::make_shared<GraphAdjacencyMatrix>();
	spGraphAdjacencyMatrix->TravelChessBoard(2, 0);
}

void TestAdjMatrix()
{
	auto spGraphAdjacencyMatrix = std::make_shared<GraphAdjacencyMatrix>();
	spGraphAdjacencyMatrix->CreateGraph();
	std::cout << "----DFSTraverse----" << std::endl;
	spGraphAdjacencyMatrix->DFSTraverse();
	std::cout << "----HFSTraverse----" << std::endl;
	spGraphAdjacencyMatrix->HFSTraverse();
}

void TestAdjList()
{
	auto spGraphAdjacencyList = std::make_shared<GraphAdjacencyList>();
	spGraphAdjacencyList->CreateGraph();
	std::cout << "----List DFSTraverse----" << std::endl;
	spGraphAdjacencyList->DFSTraverse();
	std::cout << "----List HFSTraverse----" << std::endl;
	spGraphAdjacencyList->HFSTraverse();
}

void TestMiniSpanTree()
{
	auto spGraphAdjacencyMatrix = std::make_shared<GraphAdjacencyMatrix>();
	spGraphAdjacencyMatrix->CreateGraph();
	//std::cout << "----MiniSpanTree_Prim----" << std::endl;
	//spGraphAdjacencyMatrix->MiniSpanTree_Prim();
	//std::cout << "----MiniSpanTree_Kruskal----" << std::endl;
	//spGraphAdjacencyMatrix->MiniSpanTree_Kruskal();
	//std::cout << "----ShortestPath_Dijkstra----" << std::endl;
	//spGraphAdjacencyMatrix->ShortestPath_Dijkstra(8);
	std::cout << "----ShortestPath_Ployd----" << std::endl;
	spGraphAdjacencyMatrix->ShortestPath_Ployd();
}

void TestCirtical()
{
	auto spGraphAdjacencyList = std::make_shared<GraphAdjacencyList>();
	spGraphAdjacencyList->CreatePSGraph();
	spGraphAdjacencyList->CriticalPath();
}

int main()
{
	//TestChessBoard();
	//TestAdjMatrix();
	//TestAdjList();
	//TestMiniSpanTree();
	TestCirtical();
	return EXIT_SUCCESS;
}