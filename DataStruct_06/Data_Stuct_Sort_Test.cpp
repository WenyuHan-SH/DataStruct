#include "Data_Stuct_Static_Sort.h"

int main()
{
	std::vector<int>vecData{ 50,10,90,30,70,40,80,60,20 };

	//Sort::BubbleSort_0(vecData);

	//Sort::BubbleSort_1(vecData);

	//Sort::BubbleSort_2(vecData);

	//Sort::SelectSort(vecData);

	//Sort::InsertSort(vecData);

	//Sort::ShellSort(vecData);

	//Sort::HeapSort(vecData);

	//Sort::MergeSort_0(vecData);

	//Sort::MergeSort_1(vecData);

	Sort::QuickSort(vecData);
	for(const auto data : vecData)
	{
		std::cout << data << " ";
	}
	std::cout << std::endl;
	return EXIT_SUCCESS;
}