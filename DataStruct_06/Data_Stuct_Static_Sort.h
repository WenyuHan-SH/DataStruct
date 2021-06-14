#ifndef DATA_STRUCT_STATIC_SORT_H
#define DATA_STRUCT_STATIC_SORT_H
#include "Data_Struct_Sort_Define.h"
class Sort
{
public:

	static void BubbleSort_0(std::vector<int>& vecData);
	static void BubbleSort_1(std::vector<int>& vecData);
	static void BubbleSort_2(std::vector<int>& vecData);
	static void SelectSort(std::vector<int>& vecData);
	static void InsertSort(std::vector<int>& vecData);
	static void ShellSort(std::vector<int>& vecData);
	static void HeapSort(std::vector<int>& vecData);
	static void MergeSort_0(std::vector<int>& vecData);
	static void MergeSort_1(std::vector<int>& vecData);
	static void QuickSort(std::vector<int>& vecData);
};
namespace
{
	void HeapAdjust(std::vector<int>& vecData, const int len, const int index)
	{
		int left = 2 * index + 1;
		int right = 2 * index + 2;

		int max = index;
		if (left<len && vecData[left]>vecData[max])
		{
			max = left;
		}
		if (right<len && vecData[right] > vecData[max])
		{
			max = right;
		}
		if (max != index)
		{
			std::swap(vecData[max], vecData[index]);
			HeapAdjust(vecData, len, max);
		}
	}

	void MMerge(std::vector<int>& vecData, const int left, const int mid, const int right)
	{
		std::vector<int> vecTemp;
		vecTemp.resize(right - left + 1);
		int p1(left), p2(mid + 1), i(0);
		while (p1 <= mid && p2 <= right)
		{
			vecTemp[i++] = vecData[p1] < vecData[p2] ? vecData[p1++] : vecData[p2++];
		}
		while (p1 <= mid)
		{
			vecTemp[i++] = vecData[p1++];
		}
		while (p2 <= right)
		{
			vecTemp[i++] = vecData[p2++];
		}
		for (int i = 0; i < right - left + 1; i++)
		{
			vecData[left + i] = vecTemp[i];
		}
	}

	void MSortProcess(std::vector<int>& vecData, const int left, const int right)
	{
		if (left < right)
		{
			int mid = (right + left) / 2;
			MSortProcess(vecData, left, mid);
			MSortProcess(vecData, mid + 1, right);
			MMerge(vecData, left, mid, right);
		}
	}

	int Partition_1(std::vector<int>& vecData, const int low, const int high)
	{
		//int mid = (low + high) / 2;
		//if (vecData[low] > vecData[high])
		//{
		//	std::swap(vecData[low], vecData[high]);
		//}
		//if (vecData[mid] > vecData[high])
		//{
		//	std::swap(vecData[mid], vecData[high]);
		//}
		//if (vecData[mid] > vecData[low])
		//{
		//	std::swap(vecData[mid], vecData[low]);
		//}

		int point(vecData[low]), iLow(low), iHigh(high);
		while (iLow < iHigh)
		{
			while (iLow < iHigh && vecData[iHigh] >= point)
			{
				iHigh--;
			}
			vecData[iLow] = vecData[iHigh];

			while (iLow < iHigh && vecData[iLow] <= point)
			{
				iLow++;
			}
			vecData[iHigh] = vecData[iLow];
		}
		vecData[iLow] = point;
		return iLow;
	}

	int Partition_0(std::vector<int>& vecData, const int low, const int high)
	{
		int mid = (low + high) / 2;
		if (vecData[low] > vecData[high])
		{
			std::swap(vecData[low], vecData[high]);
		}
		if (vecData[mid] > vecData[high])
		{
			std::swap(vecData[mid], vecData[high]);
		}
		if (vecData[mid] > vecData[low])
		{
			std::swap(vecData[mid], vecData[low]);
		}

		int point(vecData[low]), iLow(low), iHigh(high);
		while (iLow < iHigh)
		{
			while (iLow < iHigh && vecData[iHigh] >= point)
			{
				iHigh--;
			}
			std::swap(vecData[iLow], vecData[iHigh]);

			while (iLow < iHigh && vecData[iLow] <= point)
			{
				iLow++;
			}
			std::swap(vecData[iLow], vecData[iHigh]);
		}
		return iLow;
	}

	void QSort_1(std::vector<int>& vecData, const int low, const int high)
	{
		int iLow(low), iHigh(high);
		if (iHigh - iLow > MAX_LENGTH_INSERT_SORT)
		{
			while (iLow < iHigh)
			{
				//int pivot = Partition_0(vecData, low, high);
				int pivot = Partition_1(vecData, iLow, iHigh);
				if (pivot - iLow < iHigh - pivot)
				{
					QSort_1(vecData, iLow, pivot - 1);
					iLow = pivot + 1;
				}
				else
				{
					QSort_1(vecData, pivot + 1, iHigh);
					iHigh = pivot - 1;
				}
			}
		}
		else
		{
			Sort::InsertSort(vecData);
		}
	}

	void QSort_0(std::vector<int>& vecData, const int low, const int high)
	{
		if (high - low > MAX_LENGTH_INSERT_SORT)
		{
			//int pivot = Partition_0(vecData, low, high);
			int pivot = Partition_1(vecData, low, high);
			QSort_0(vecData, low, pivot - 1);
			QSort_0(vecData, pivot + 1, high);
		}
		else
		{
			Sort::InsertSort(vecData);
		}
	}
}

void Sort::BubbleSort_0(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	for (int i = 0; i < iDataSize; i++)
	{
		for (int j = i + 1; j < iDataSize; j++)
		{
			if (vecData[i] > vecData[j])
			{
				std::swap(vecData[i], vecData[j]);
			}
		}
	}
}

void Sort::BubbleSort_1(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	for (int i = 0; i < iDataSize; i++)
	{
		//for (int j = iDataSize - 2; j >= i; j--)
		//{
		//	if (vecData[j] < vecData[j + 1])
		//	{
		//		std::swap(vecData[j], vecData[j + 1]);
		//	}
		//}
		for (int j = 0; j < iDataSize - i - 1; j++)
		{
			if (vecData[j + 1] < vecData[j])
			{
				std::swap(vecData[j + 1], vecData[j]);
			}
		}
	}
}

void Sort::BubbleSort_2(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	bool flag(true);
	for (int i = 0; i < iDataSize && flag; i++)
	{
		flag = false;
		//for (int j = iDataSize - 2; j >= i; j--)
		//{
		//	if (vecData[j] > vecData[j + 1])
		//	{
		//		std::swap(vecData[j], vecData[j + 1]);
		//		flag = true;
		//	}
		//}

		for (int j = 0; j < iDataSize - i - 1; j++)
		{
			if (vecData[j + 1] < vecData[j])
			{
				std::swap(vecData[j + 1], vecData[j]);
				flag = true;
			}
		}
	}
}

void Sort::SelectSort(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	for (int i = 0; i < iDataSize; i++)
	{
		int min(i);
		for (int j = i + 1; j < iDataSize; j++)
		{
			if (vecData[min] > vecData[j])
			{
				min = j;
			}
		}
		if (min!=i)
		{
			std::swap(vecData[min], vecData[i]);
		}
	}
}

void Sort::InsertSort(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	//for (int i = 0; i < iDataSize - 1; i++)
	//{
	//	if (vecData[i] > vecData[i + 1])
	//	{
	//		int temp(vecData[i + 1]), j(0);
	//		for (j = i; j >= 0 && vecData[j] > temp; j--)
	//		{
	//			vecData[j + 1] = vecData[j];
	//		}
	//		vecData[j + 1] = temp;
	//	}
	//}

	for (int i = 1; i < iDataSize; i++)
	{
		for (int j = i - 1; j >= 0 && vecData[j + 1] < vecData[j]; j--)
		{
			std::swap(vecData[j + 1], vecData[j]);
		}
	}
}

void Sort::ShellSort(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	int gap(vecData.size());
	do
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < iDataSize; i ++)
		{
			for (int j = i - gap; j >= 0 && vecData[i] < vecData[j]; j -= gap)
			{
				std::swap(vecData[i], vecData[j]);
			}
		}
	} while (gap > 1);
}

void Sort::HeapSort(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	for (int i = iDataSize / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(vecData, iDataSize, i);
	}

	for (int i = iDataSize - 1; i >= 1; i--)
	{
		std::swap(vecData[0], vecData[i]);
		HeapAdjust(vecData, i, 0);
	}
}

void Sort::MergeSort_0(std::vector<int>& vecData)
{
	if (vecData.size()<2)
	{
		return;
	}
	MSortProcess(vecData, 0, vecData.size() - 1);
}

void Sort::MergeSort_1(std::vector<int>& vecData)
{
	int iDataSize(vecData.size());
	for (int lengthTocombine = 1; lengthTocombine < iDataSize; lengthTocombine *= 2)
	{
		int begin = 0;//开始合并时第一个序列的起始位置下标，每次都是从0开始
		while (begin + 2 * lengthTocombine < iDataSize)
		{
			int right = begin + 2 * lengthTocombine - 1;
			int mid = (begin + right) / 2;
			MMerge(vecData, begin, mid, right);
			begin += 2 * lengthTocombine;
		}
		//剩下长度小于lengthTocombine序列
		if (begin + lengthTocombine < iDataSize)
			MMerge(vecData, begin, begin + lengthTocombine - 1, iDataSize - 1);
	}
}

void Sort::QuickSort(std::vector<int>& vecData)
{
	//QSort_0(vecData, 0, vecData.size() - 1);
	QSort_1(vecData, 0, vecData.size() - 1);
}
#endif // !DATA_STRUCT_STATIC_SORT_H
