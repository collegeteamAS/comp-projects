

#include <vector>
#include <algorithm>
#include <iostream> // debug
#include "sorts.h"

// int Sorts::iterations = 0; // debug

void Sorts::bubbleSort(std::vector<int>* arr){
	for(int i = 0; i < arr->size(); i++){
		//bool swapping = true;
		//std::cout << "ehck";
		//int n = arr->size()-1;
		//std::cout << arr->at(n) << "\n";
		//std::cout << arr->at(n-1) << "\n";
		for(int n = arr->size()-1; n > 0; n--){
			if(arr->at(n) < arr->at(n-1)){
				int temp = arr->at(n);
				(*arr)[n] = arr->at(n-1);
				(*arr)[n-1] = temp;
				std::cout << temp << "\n";
				n--;
			}
			else{
				break;
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
	@author Andre Allan Ponce
	divides the vector into two halves,
	recursively calls this method until the size of the vector is 1
	uses merge to merge it at the end
	@param arr - the vector to be sorted
*/
void Sorts::mergeSort(std::vector<int>* arr){
	if(arr->size() > 1){
		int pivot = arr->size()/2; // finds halfway index

		// create vector of left side 
		std::vector<int>* left = &std::vector<int>();
		fillVector(arr,left,0,pivot);

		// create vector of right side
		std::vector<int>* right = &std::vector<int>();
		fillVector(arr,right,pivot,arr->size());

		// recursively call this method with left and right vectors
		mergeSort(left);
		mergeSort(right);

		// finally merge to sort
		merge(left,right,arr);
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