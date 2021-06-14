#include "Data_Struct_Static_Search.h"
#include "Data_Struct_Static_Hash_Table_Search.h"

int main()
{
	std::vector<DataType> vecData = { 0,1,16,24,35,47,59,62,73,88,99 };
	StaticSearch::FibonacciSearch(vecData, 59);
	return EXIT_SUCCESS;
}