
#include <vector>
#include <time.h>
#include <random>
#include <string>
#include <iostream> // probably wont need this
#include <sstream>
#include <fstream>
#include "sorts.h"

void createRandomizedVector(std::vector<int>* arr, int size);
int createRandomNumber(int range);
void debugPrintElements(std::vector<int>* arr, int range);

// sorting (calls methods from Sorts class)
std::string sortUsingBubble(std::vector<int>* arr, int size);
std::string sortUsingInsertion(std::vector<int>* arr, int size);
std::string sortUsingMerge(std::vector<int>* arr, int size);
std::string sortUsingQuick(std::vector<int>* arr, int size);
std::string sortUsingSelection(std::vector<int>* arr, int size);

int main(){
	srand(time(0);
	int state = 0;
	int vectorSize = 20000;
	int VECTOR_SIZE_INCREASE_FACTOR = 2;
	while(vectorSize <= 640000){
		while(state < 5){
			std::vector<int>* arrayToSort = new std::vector<int>();
			createRandomizedVector(arrayToSort,vectorSize);
			//std::cout << "array made";
			std::string result = "";
			switch(state){
			case 0:{
				result = sortUsingSelection(arrayToSort,vectorSize);
				state++;
				break;
			}
			case 1:{
				result = sortUsingInsertion(arrayToSort,vectorSize);
				state++;
				break;
			}
			case 2:{
				result = sortUsingBubble(arrayToSort,vectorSize);
				debugPrintElements(arrayToSort, 100);
				state++;
				break;
			}
			case 3:{
				result = sortUsingMerge(arrayToSort,vectorSize);
				state++;
				break;
			}
			case 4:{
				result = sortUsingQuick(arrayToSort,vectorSize);
				state++;
				break;
			}
			default :
				// we should not be going here
				break;
			}
			delete arrayToSort;
			std::cout << result << "\n"; // change this to save to file later
		}
		vectorSize *= VECTOR_SIZE_INCREASE_FACTOR;
		state = 0;
	}
	return 0;
}

// @author Andre Allan Ponce
// creates a vector full of random ints
// assume arr is empty
void createRandomizedVector(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	for(int i = 0; i < size; i++){
		arr->push_back(createRandomNumber(size));
	}
	clock_t timeTaken = clock() - startTime;
	std::cout << "Generated Array of " << size << " elements in " << timeTaken << " milliseconds\n";
}

// @author Andre Allan Ponce
// creates random number from 1 to range
int createRandomNumber(int range){
	//std::random_device rd;
	return (rand() % range + 1);
	//std::cout << test << "\n";
}

// @author Andre Allan Ponce
// debug print elements (for testing)
void debugPrintElements(std::vector<int>* arr, int range){
	for(int i = 0; i < range; i++){
		std::cout<< i << ":" << arr->at(i) << "\n";
	}
}


// @author Andre Allan Ponce
// sorts using bubble sort (from Sorts class)
std::string sortUsingBubble(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	Sorts::bubbleSort(arr);
	clock_t timeTaken = clock() - startTime;
	std::ostringstream oss;
	oss << "Bubble Sort: " << size << " elements took " << timeTaken << " milliseconds.";
	return oss.str();
}

// @author Andre Allan Ponce
// sorts using Insertion sort (from Sorts class)
std::string sortUsingInsertion(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	//Sorts::insertionSort(arr);
	clock_t timeTaken = clock() - startTime;
	std::ostringstream oss;
	oss << "Insertion Sort: " << size << " elements took " << timeTaken << " milliseconds.";
	return oss.str();
}

// @author Andre Allan Ponce
// sorts using mergeSort (from Sorts class)
std::string sortUsingMerge(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	Sorts::mergeSort(arr);
	clock_t timeTaken = clock() - startTime;
	std::ostringstream oss;
	oss << "Merge Sort: " << size << " elements took " << timeTaken << " milliseconds.";
	return oss.str();
}

// @author Andre Allan Ponce
// sorts using Quick sort (from Sorts class)
std::string sortUsingInsertion(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	//Sorts::quickSort(arr);
	clock_t timeTaken = clock() - startTime;
	std::ostringstream oss;
	oss << "Quick Sort: " << size << " elements took " << timeTaken << " milliseconds.";
	return oss.str();
}

// @author Andre Allan Ponce
// sorts using Selection sort (from Sorts class)
std::string sortUsingInsertion(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	//Sorts::selectionSort(arr);
	clock_t timeTaken = clock() - startTime;
	std::ostringstream oss;
	oss << "Selection Sort: " << size << " elements took " << timeTaken << " milliseconds.";
	return oss.str();
}
