// FILE: PrimeCounter.cpp
// Programmer: Dan Cliburn
// Date: 10/22/2014
// Purpose: This file defines the methods for the PrimeCounter class.
// Since Visual Studio 2010 does not support the C++ thread class, I have include the thread
// class from the Boost library (http://www.boost.org/). The following comment is required by
// the Boost Software Licensing Agreement:

//			Copyright	Daniel Cliburn	2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "PrimeCounter.h"
#include <stdlib.h>
#include <iostream>
#include <thread>  //include if you are using Visual Studio 2012 or 2013 to use C++ threads
//#include <boost/thread.hpp> //include if you are using Visual Studio 2010 to use Boost threads
//using namespace boost; //include if you are using Visual Studio 2010 to use Boost threads
using namespace std;

//Initialize the constants and static class variables
const int TOTAL_THREADS = 100;
int PrimeCounter::total_primes = 0;
bool *PrimeCounter::values = 0;

PrimeCounter::PrimeCounter(int SIZE)
{
	if (SIZE > 0)
	{
		values = new bool[SIZE];
		resetCounters(SIZE);
	}
	else
	{
		cout << "ERROR: cannot create a PrimeCounter object with a nonpositive number. Exiting ..." << endl;
		exit(0);
	}
}

void PrimeCounter::resetCounters(int SIZE)
{
	for (int i = 0; i < SIZE; i++) 
		values[i] = false;

	total_primes = 0;
}

int PrimeCounter::countPrimeValues(int start, int stop)
{
	int total = 0;
	for(int i = start; i < stop; i++){
		if(values[i]){
			total++;
		}
	}
	return total;
}


void PrimeCounter::isPrime(int index)
{
	for (int i = 2; i <= index/2; i++)
	{
		if (index%i == 0)  //we found a divisor, the number is NOT prime
		{
			values[index] = false;
			return;  //No need to keep checking numbers
		}
	}
	//Number was prime if the loop finished
	total_primes++;
	values[index] = true;
}

//Finds the number of primes values beginning at start and ending at (but not including) stop
void PrimeCounter::serialDeterminePrimes(int start, int stop)
{
	for (int i = start; i < stop; i++)
	{
		isPrime(i);
	}
}

//Finds the number of primes values beginning at start and ending at (but not including) stop
void PrimeCounter::parallelDeterminePrimes(int start, int stop)
{
	int i;
	int SIZE = stop-start+1;
	int step = SIZE/TOTAL_THREADS;

	thread **threads = new thread *[TOTAL_THREADS];
	int first = start, last = start + step;
	for (i = 0; i < TOTAL_THREADS; i++)  //make threads and give them work to do
	{
		threads[i] = new thread(PrimeCounter::serialDeterminePrimes, first, last);
		first += step;
		last += step;
		if (last > stop) last = stop; //Ensure we don't do an extra one with the last thread
	}
	for (i = 0; i < TOTAL_THREADS; i++)
	{
		threads[i]->join();  //wait for the thread to finish (synchronize)
	}
	for (i = 0; i < TOTAL_THREADS; i++)  //delete the threads
	{
		delete threads[i];
	}
	delete [] threads;  //delete the array that pointed to the threads
}

PrimeCounter::~PrimeCounter()
{
	delete [] values;
}