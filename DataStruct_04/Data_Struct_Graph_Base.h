#ifndef DATA_STRUCT_GRAPH_BASE
#define DATA_STRUCT_GRAPH_BASE
#include "Data_Struct_Graph_Define.h"
class Graph
{
public:
	virtual void CreateGraph() = 0;
	virtual void DestroyGraph() = 0;
	virtual int LocateVex(const VertexType& value) const = 0;
	virtual VertexType GetVex(const int& iIndex) const = 0;
	virtual void  PutVex(const int& iIndex, const VertexType& value) = 0;
	virtual int FirstAdjVex(const int& iIndex)const = 0;
	virtual int NextAdjVex(const int& iIndex, const int& iPreIndex) const = 0;
	virtual void InsertVex(const int& iIndex) = 0;
	virtual void InsertArc(const int& iFirIndex, const int& iSecIndex) = 0;
	virtual void DeleteArc(const int& iFirIndex, const int& iSecIndex) = 0;
	virtual void DFSTraverse() const = 0;
	virtual void HFSTraverse() const = 0;
protected:
	virtual void DFS(const int& iIndex) const = 0;
	virtual void HFS() const = 0;
};

#endif // !DATA_STRUCT_GRAPH_BASE
