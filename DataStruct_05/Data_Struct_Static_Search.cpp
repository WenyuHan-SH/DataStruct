#include "Data_Struct_Static_Search.h"

namespace 
{
	const int FIB_SIZE = 15;
	int Fib(const int n)
	{
		if (0 == n)
		{
			return 0;
		}
		else if (1 == n)
		{
			return 1;
		}
		else
		{
			return Fib(n - 1) + Fib(n - 2);
		}
	}
}
int StaticSearch::SequentialSearch(const std::vector<DataType>& vecData, const DataType key)
{
	auto iter = std::find(vecData.begin(), vecData.end(), key);
	return iter != vecData.end() ? std::distance(vecData.begin(), iter) : -1;
}

int StaticSearch::BinarySearch(const std::vector<DataType>& vecData, const DataType key)
{
	int low(0), high(vecData.size()), mid(0);
	while (low < high)
	{
		mid = static_cast<int>((low + high) / 2);
		if (key < vecData[mid])
		{
			high = mid - 1;
		}
		else if (key > vecData[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int StaticSearch::InterpolationSearch(const std::vector<DataType>& vecData, const DataType key)
{
	int low(0), high(vecData.size()), mid(0);
	while (low < high)
	{
		mid = static_cast<int>((key - vecData[low]) / (vecData[high] - vecData[low]) * (high - low));
		if (key < vecData[mid])
		{
			high = mid - 1;
		}
		else if (key > vecData[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int StaticSearch::FibonacciSearch(const std::vector<DataType>& vecData, const DataType key)
{
	//创建斐波那契数列
	std::vector<int> Fibonacci;
	Fibonacci.resize(FIB_SIZE);
	for (int i = 0; i < FIB_SIZE; ++i)
	{
		Fibonacci[i] = Fib(i);
	}
	//斐波那契查找
	const int dataSize(vecData.size());
	int low(0), high(dataSize), mid(0), index(0);
	while (dataSize > Fibonacci[index] - 1)
	{
		index++;
	}
	std::vector<DataType> vecSearchData;
	vecSearchData.assign(vecData.begin(), vecData.end());
	for (int n = dataSize; n < Fibonacci[index] - 1; ++n)
	{
		vecSearchData.push_back(vecData[dataSize - 1]);
	}

	while (low <= high)
	{
		mid = low + Fibonacci[index - 1] - 1;
		if (key < vecSearchData[mid])
		{
			high = mid - 1;
			index -= 1;
		}
		else if (key > vecSearchData[mid])
		{
			low = mid + 1;
			index -= 2;
		}
		else
		{
			return mid <= vecData.size() ? mid : vecData.size();
		}
	}
	return -1;
}