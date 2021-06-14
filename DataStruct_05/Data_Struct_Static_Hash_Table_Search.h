#ifndef DATA_STRUCT_STATICHASE_TABLE_SEARCH_H_
#define DATA_STRUCT_STATICHASE_TABLE_SEARCH_H_
#include "Data_Struct_Search_Define.h"

class HashTable
{
public:
	bool InitHashTabel();
	void InsertHash(const int key);
	bool SearchHash(const int key, int& addr);
private:
	int Hash(const int key);
private:
	HashTableData m_HashTable;
};

bool HashTable::InitHashTabel()
{
	m_HashTable.count = HASHSIZE;
	m_HashTable.elem = (int*)(HASHSIZE * sizeof(int));
	for (int i = 0; i < HASHSIZE; i++)
	{
		m_HashTable.elem[i] = NULLKEY;
	}
}

int HashTable::Hash(const int key)
{
	return key % HASHSIZE;
}

void HashTable::InsertHash(const int key)
{
	auto addr = Hash(key);
	while (m_HashTable.elem[addr] != NULLKEY)
	{
		addr = Hash(addr + 1);
	}
	m_HashTable.elem[addr] = key;
}

bool HashTable::SearchHash(const int key, int& addr)
{
	addr = Hash(key);
	while (m_HashTable.elem[addr] != key)
	{
		addr = Hash(addr + 1);
		if (m_HashTable.elem[addr] == NULLKEY || addr == Hash(key))
		{
			return false;
		}
	}
	return true;
}
#endif //DATA_STRUCT_STATICHASE_TABLE_SEARCH_H_
