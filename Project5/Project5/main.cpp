
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
void saveToFile(std::string* data, std::string fileName);
void sorter(std::string* data, int size, int max);

// sorting (calls methods from Sorts class)
std::string sortUsingBubble(std::vector<int>* arr, int size);
std::string sortUsingInsertion(std::vector<int>* arr, int size);
std::string sortUsingMerge(std::vector<int>* arr, int size);
std::string sortUsingQuick(std::vector<int>* arr, int size);
std::string sortUsingSelection(std::vector<int>* arr, int size);

int main(){
	srand(time(0));
	bool action;
	int vectorSize;
	std::ostringstream oss;
	std::string* data = new std::string[5];
	int MAX_VECTOR_SIZE;
	do{
		std::cout << "Auto mode or manual mode? (A/m): ";
		char mode;
		std::cin >> mode;
		if(mode == 'A' || mode == 'a'){
			std::cout << "Enter starting data size: ";
			std::cin >> vectorSize;
			oss << "SortResults_Auto_" << vectorSize;
			MAX_VECTOR_SIZE = vectorSize*32;
			action = true;
		}
		else if(mode == 'M' || mode == 'm'){
			std::cout << "Enter data size to sort: ";
			std::cin >> vectorSize;
			oss << "SortResults_" << vectorSize;
			MAX_VECTOR_SIZE = vectorSize;
			action = true;
		}
		else{
			std::cout << "bad input, try again\n";
			action = false;
		}
	}while(!action);
	std::string FILENAME = oss.str();
	sorter(data, vectorSize, MAX_VECTOR_SIZE);
	saveToFile(data,FILENAME);
	delete [] data;
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

/*
	@author Andre Allan Ponce
	saves data to file in this format:
	<sort name>:
	<vectorSize> elements in <time taken>
	...

	<sort name>:
	...
*/
void saveToFile(std::string* data, std::string fileName){
	std::ofstream out (fileName.c_str(), std::ofstream::out);
	for(int i = 0; i < 5; i++){
		switch(i){
		case 0:{
			out << "Selection Sort\n" << "------------------------\n";
			break;
		}
		case 1:{
			out << "Insertion Sort\n" << "------------------------\n";
			break;
		}
		case 2:{
			out << "Bubble Sort\n" << "------------------------\n";
			break;
		}
		case 3:{
			out << "Merge Sort\n" << "------------------------\n";
			break;
		}
		case 4:{
			out << "Quick Sort\n" << "------------------------\n";
			break;
		}
		default :{
			// we should never be going here
			break;
		}
		}
		//std::cout << data[i] << "\n";
		out << data[i] << "\n";
	}
	out.close();
	std::cout << "File Saved as " << fileName << "\n";
}

// @author Andre Allan Ponce
// does the sorting, using states
// can be done for a certain number of elements or does from vectorSize to MAX_VECTOR_SIZE in factors of 2 
void sorter(std::string* data, int size, int max){
	int VECTOR_SIZE_INCREASE_FACTOR = 2;
	int state = 0;
	while(size <= max){
		std::cout << "\n\n"<< size << ": \n";
		while(state < 5){
			std::vector<int>* arrayToSort = new std::vector<int>();
			createRandomizedVector(arrayToSort,size);
			//std::cout << "array made";
			std::string result = "";
			switch(state){
			case 0:{
				result = sortUsingSelection(arrayToSort,size);
				
				state++;
				break;
			}
			case 1:{
				result = sortUsingInsertion(arrayToSort,size);
				state++;
				break;
			}
			case 2:{
				result = sortUsingBubble(arrayToSort,size);
				
				state++;
				break;
			}
			case 3:{
				result = sortUsingMerge(arrayToSort,size);
				state++;
				break;
			}
			case 4:{
				result = sortUsingQuick(arrayToSort,size);
				debugPrintElements(arrayToSort, 100);
				state++;
				break;
			}
			default :
				// we should not be going here
				break;
			}
			delete arrayToSort;
			std::cout << result << "\n"; // change this to save to file later // for debug
			data[state-1] += result + "\n";
		}
		size *= VECTOR_SIZE_INCREASE_FACTOR;
		state = 0;
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
	Sorts::insertionSort(arr);
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
std::string sortUsingQuick(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	Sorts::quickSort(arr);
	clock_t timeTaken = clock() - startTime;
	std::ostringstream oss;
	oss << "Quick Sort: " << size << " elements took " << timeTaken << " milliseconds.";
	return oss.str();
}

// @author Andre Allan Ponce
// sorts using Selection sort (from Sorts class)
std::string sortUsingSelection(std::vector<int>* arr, int size){
	clock_t startTime = clock();
	Sorts::selectionSort(arr);
	clock_t timeTaken = clock() - startTime;
	std::ostringstream oss;
	oss << "Selection Sort: " << size << " elements took " << timeTaken << " milliseconds.";
	return oss.str();
}
