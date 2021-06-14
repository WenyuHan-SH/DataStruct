#ifndef DATA_STRUCT_SEARCH_DEFINE_H_
#define DATA_STRUCT_SEARCH_DEFINE_H_
#include <iostream>
#include <vector>
typedef int DataType;
const int HASHSIZE = 12;
const int NULLKEY = -32768;

typedef struct
{
	int* elem;
	int count;
} HashTableData;



#endif // !DATA_STRUCT_SEARCH_DEFINE_H_

