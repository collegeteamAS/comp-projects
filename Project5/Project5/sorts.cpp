

#include <vector>
#include <algorithm>
// #include <iostream> // debug
#include "sorts.h"

// int Sorts::iterations = 0; // debug

/*
	sorts by comparing two objects at a time
	@author Andre Allan Ponce
	@param arr - the vector to be sorted
*/
void Sorts::bubbleSort(std::vector<int>* arr){
	for(unsigned int i = 0; i < arr->size(); i++){

		// Ive always done bubble sorts by reverse iterating 
		for(unsigned int n = arr->size()-1; n > i; n--){
			if(arr->at(n) < arr->at(n-1)){
				int temp = arr->at(n);
				(*arr)[n] = arr->at(n-1);
				(*arr)[n-1] = temp;
			}
		}
	}
}

/*
	For some reason, the std::copy function was throwing bad errors
	@author Andre Allan Ponce
	@param input - input vector to copy
	@param output - output vector to fill
	@param start - starting index (on input)
	@param end - ending index (on input)
*/
void Sorts::fillVector(std::vector<int>* input, std::vector<int>* output, int start, int end){
	for(int i = start; i < end; i++){
		output->push_back(input->at(i)); // push_back is to vectors like add is to ArrayLists
	}
}//*/

/*
	Sorts by adding the next value,
	then sorts the value into place
	@author Andre Allan Ponce
	@param arr - the vector to sort
*/
void Sorts::insertionSort(std::vector<int>* arr){
	for(unsigned int i = 1; i < arr->size(); i++){
		int n = i;
		while(n > 0 && arr->at(n) < arr->at(n-1)){
			int temp = arr->at(n);
			(*arr)[n] = arr->at(n-1);
			(*arr)[n-1] = temp;
			n--;
		}
	}
}

/*
	@author Andre Allan Ponce
	merges two vectors to sort them
	@param left - the left vector to merge
	@param right - the right vector to merge
	@param arr - the vector to be sorted
*/
void Sorts::merge(std::vector<int>* left, std::vector<int>* right, std::vector<int>* arr){
	unsigned int lIndex = 0;
	unsigned int rIndex = 0;
	unsigned int index = 0;
	while(index < arr->size()){ // do this until we have iterated through the vector to be sorted
		if(lIndex < left->size() && rIndex < right->size()){ 
			if(left->at(lIndex) < right->at(rIndex)){ // sorting from least to greatest
				(*arr)[index++] = left->at(lIndex++);
			}
			else{
				(*arr)[index++] = right->at(rIndex++);
			}
		}
		else{
			if(lIndex < left->size()){
				(*arr)[index++] = left->at(lIndex++);
			}
			else{
				(*arr)[index++] = right->at(rIndex++);
			}
		}
	}
}

/*
	@author Andre Allan Ponce
	divides the vector into two halves,
	recursively calls this method until the size of the vector is 1
	uses merge to merge it at the end
	@param arr - the vector to be sorted
*/
void Sorts::mergeSort(std::vector<int>* arr){
	if(arr->size() > 1){
		int q = arr->size()/2; // finds halfway index

		// create vector of left side 
		std::vector<int>* left = &std::vector<int>();
		fillVector(arr,left,0,q);

		// create vector of right side
		std::vector<int>* right = &std::vector<int>();
		fillVector(arr,right,q,arr->size());

		// recursively call this method with left and right vectors
		mergeSort(left);
		mergeSort(right);

		// finally merge to sort
		merge(left,right,arr);
	}
}


//Steve Suh
void Sorts::selectionSort(std::vector<int>* arr)
{
	int curr, min; //curr is current value checking, min is the index of minimum value in arr
	int n = arr->size()-1; // number of elements
	min = 0; //assuming the first value is the minimum
	int temp;

	for(int j=0; j<n; j++)
	{
		for(int i = j; i < n; i++)
		{
			if((*arr)[i+1] < (*arr)[min])
				min=i+1;
		}

			temp = (*arr)[j];
			(*arr)[j] = (*arr)[min];
			(*arr)[min] = temp; //swaping the min value to the resulting location
	}
	
}


//Steve Suh
void Sorts::quickSort(std::vector<int>* arr)
{
	quickSortRec(arr, 0,arr->size()-1);
}

//recursion function
void Sorts::quickSortRec(std::vector<int>* arr, int a, int z)
{
	int piv = partition(arr,a,z);

	//do recursion on the left of pivot

	if(a<piv-1)
	{
		quickSortRec(arr,a,piv-1);
	}

	if(z>piv)
	{
		quickSortRec(arr,piv,z);
	}


}


//arranges pivot index
int Sorts::partition(std::vector<int>* arr, int left, int right)
{
	int piv = left;
	while (left<=right)
	{
		//checking if any values left of pivot is greater than pivot
		while(arr-> at(left) < arr-> at(piv))
		{
			left++;
		}

		//checking any values less than pivot on right side
		while(arr-> at(right) > arr-> at(piv))
		{
			right--;
		}
	
		//swap two values
		if(left<=right)
		{
			int temp = arr->at(left);
			(*arr)[left] =  arr-> at(right);
			(*arr)[right] = temp;
			right--;
			left++;
		}
	}

	return left;

}
