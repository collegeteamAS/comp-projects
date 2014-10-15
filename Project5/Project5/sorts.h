
#ifndef _SORTS_H_INCLUDED_
#define _SORTS_H_INCLUDED_

#include <vector>

class Sorts{
private:
	static void fillVector(std::vector<int>* input, std::vector<int>* output, int start, int end);
	static void merge(std::vector<int>* left, std::vector<int>* right, std::vector<int>* arr);
	// static int iterations; // debug
	
public:
	static void bubbleSort(std::vector<int>* arr);
	static void insertionSort(std::vector<int>* arr);
	static void mergeSort(std::vector<int>* arr);

	//steve suh ------
	static void selectionSort(std::vector<int>* arr);
	static void quickSort(std::vector<int>* arr);
	static void quickSortRec(std::vector<int>* arr, int a, int z);
	static int partition(std::vector<int>* arr,int left, int right);

};

#endif