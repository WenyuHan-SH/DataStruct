#ifndef DATA_STRUCT_STATIC_SEARCH_H_
#define DATA_STRUCT_STATIC_SEARCH_H_
#include "Data_Struct_Search_Define.h"
class StaticSearch
{
public:
	static int SequentialSearch(const std::vector<DataType>& vecData, const DataType key);
	static int BinarySearch(const std::vector<DataType>& vecData, const DataType key);
	static int InterpolationSearch(const std::vector<DataType>& vecData, const DataType key);
	static int FibonacciSearch(const std::vector<DataType>& vecData, const DataType key);
};
		


#endif // !DATA_STRUCT_STATIC_SEARCH_H_



