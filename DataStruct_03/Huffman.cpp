#include "Huffman.h"

HuffmanCode::HuffmanCode()
{
	m_pQueue = static_cast<Queue>(malloc(sizeof(pQueue)));
	m_pQueue->first = nullptr;
	m_pQueue->size = 0;

	m_htTree = static_cast<HTtree>(malloc(sizeof(HTtree)));

	m_hlTable = static_cast<hlTable*>(malloc(sizeof(hlTable)));
	m_hlTable->first = nullptr;
	m_hlTable->last = nullptr;
}

void HuffmanCode::addPQueue(HTNode value, const unsigned int priority)
{
	if (MAX_SZ == m_pQueue->size)
	{
		std::cout << "Queue is full" << std::endl;
		return;
	}

	pQueueNode* aux = static_cast<pQueueNode*>(malloc(sizeof(pQueueNode)));
	aux->priority = priority;
	aux->val = value;

	if (0 == m_pQueue->size || nullptr == m_pQueue->first)
	{
		aux->next = nullptr;
		m_pQueue->first = aux;
		m_pQueue->size = 1;
	}
	else
	{
		if (priority <= m_pQueue->first->priority)
		{
			aux->next = m_pQueue->first;
			m_pQueue->first = aux;
			m_pQueue->size++;
		}
		else
		{
			pQueueNode* iterator = m_pQueue->first;
			while (nullptr != iterator->next)
			{
				if (priority <= iterator->next->priority)
				{
					aux->next = iterator->next;
					iterator->next = aux;
					m_pQueue->size++;
					return;
				}
				iterator = iterator->next;
			}

			if (nullptr == iterator->next)
			{
				aux->next = nullptr;
				iterator->next = aux;
				m_pQueue->size++;
				return;
			}
		}
	}
}

HTNode HuffmanCode::getPQueue()
{
	HTNode returnValue(nullptr);
	if (0 < m_pQueue->size)
	{
		returnValue = m_pQueue->first->val;
		m_pQueue->first = m_pQueue->first->next;
		m_pQueue->size--;
	}
	else
	{
		std::cout << "Queue is empty" << std::endl;
	}
	return returnValue;
}

void HuffmanCode::BuildTree(const std::string& inputString)
{
	int probability[256] = { 0 };
	for (int i = 0; i < inputString.size(); ++i)
	{
		probability[inputString[i]]++;
	}

	for (int k = 0; k < 256; k++)
	{
		if (probability[k])
		{
			htNode* aux = static_cast<htNode*>(malloc(sizeof(htNode)));
			aux->left = nullptr;
			aux->right = nullptr;
			aux->symbol = static_cast<char>(k);
			addPQueue(aux, probability[k]);
		}
	}

	while (1 != m_pQueue->size)
	{
		int priority = m_pQueue->first->priority;
		priority += m_pQueue->first->next->priority;
		htNode* left = getPQueue();
		htNode* right = getPQueue();
		htNode* newNode = static_cast<htNode*>(malloc(sizeof(htNode)));
		newNode->left = left;
		newNode->right = right;
		addPQueue(newNode, priority);
	}
	m_htTree->root = getPQueue();

	//BuildTable
	char code[256] = { ' ' };
	traverseTree(m_htTree->root, 0, code);
}

void HuffmanCode::traverseTree(HTNode treeNode, const int k, char code[256])
{
	if (nullptr == treeNode->left && nullptr == treeNode->right)
	{
		code[k] = '\0';
		hlNode* aux = static_cast<hlNode*>(malloc(sizeof(hlNode)));
		aux->code = static_cast<char*>(malloc(sizeof(char) * (strlen(code) + 1)));
		memcpy(aux->code, code, strlen(code) + 1);
		aux->symbol = treeNode->symbol;
		aux->next = nullptr;
		if (nullptr == m_hlTable->first)
		{
			m_hlTable->first = aux;
			m_hlTable->last = aux;
		}
		else
		{
			m_hlTable->last->next = aux;
			m_hlTable->last = aux;
		}
	}

	if (nullptr != treeNode->left)
	{
		code[k] = '0';
		traverseTree(treeNode->left, k + 1, code);
	}
	if (nullptr != treeNode->right)
	{
		code[k] = '1';
		traverseTree(treeNode->right, k + 1, code);
	}
}

void HuffmanCode::EnCode(const std::string& stringToEnCode)
{
	hlNode* traversal;
	std::cout << "Encoding..." << std::endl;
	for (int i = 0; i < stringToEnCode.size(); ++i)
	{
		traversal = m_hlTable->first;
		while (traversal->symbol != stringToEnCode[i])
		{
			traversal = traversal->next;
		}
		std::cout << traversal->code;
	}
	std::cout << std::endl;
}

void HuffmanCode::DeCode(const std::string& stringToDeCode)
{
	htNode* traversl = m_htTree->root;
	std::cout << "Decoding..." << std::endl;
	for (int i = 0; i < stringToDeCode.size(); ++i)
	{
		if (nullptr == traversl->left && nullptr == traversl->right)
		{
			std::cout << traversl->symbol << " ";
			traversl = m_htTree->root;
		}
		if ('0' == stringToDeCode[i])
		{
			traversl = traversl->left;
		}
		if ('1' == stringToDeCode[i])
		{
			traversl = traversl->right;
		}
		if ('0' != stringToDeCode[i] && '1' != stringToDeCode[i])
		{
			std::cout << "The input string is not coded correctly" << std::endl;
			return;
		}
	}

	if (nullptr == traversl->left && nullptr == traversl->right)
	{
		std::cout << "The tree is null" << std::endl;
	}
}