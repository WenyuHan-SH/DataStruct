#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Huffman_Define.h"

class HuffmanCode
{
public:
	HuffmanCode();
	void EnCode(const std::string& stringToEnCode);
	void DeCode(const std::string& stringToDeCode);
	void BuildTree(const std::string& inputString);
private:
	void traverseTree(HTNode treeNode, const int k, char code[256]);
	void addPQueue(HTNode value, const unsigned int priority);
	HTNode getPQueue();
private:
	Queue m_pQueue;
	HTtree m_htTree;
	HLTable m_hlTable;
};


#endif // ! HUFFMAN_H

