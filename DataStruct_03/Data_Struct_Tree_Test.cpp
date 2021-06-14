#include "Data_Struct_Binary_Tree.h"
#include "Data_Struct_Binary_Thread_Tree.h"
#include "Huffman.h"

void Test01()
{
	auto spBinaryTree = std::make_shared<BinaryTree>();
	spBinaryTree->SetTraverOrder(PreOrder);
	spBinaryTree->CreateTree();
	spBinaryTree->TreePreview();
	auto spBinaryThreadTree = std::make_shared<BinaryThreadTree>();
	spBinaryThreadTree->SetTraverOrder(InOrder);
	spBinaryThreadTree->CreateTree();
	spBinaryThreadTree->InThreading();
	spBinaryThreadTree->TreePreview();
}

void TestHumman()
{
	auto spHuffmanCode = std::make_shared<HuffmanCode>();
	spHuffmanCode->BuildTree("I love FishC.com!");
	spHuffmanCode->EnCode("I love FishC.com!");
	spHuffmanCode->DeCode("0011111000111");
}

void TestAVL()
{
	auto spAVLTree = std::make_shared<BinaryTree>();
	std::vector<ElemType> AVLData{ 3,2,1,4,5,6,7,10,9,8 };
	for (int i = 0; i < AVLData.size(); ++i)
	{
		spAVLTree->InsertAVL(AVLData[i]);
	}
}

int main()
{
	//TestHumman();
	TestAVL();
	return EXIT_SUCCESS;
}