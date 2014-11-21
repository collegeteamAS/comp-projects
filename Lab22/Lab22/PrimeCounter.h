// FILE: PrimeCounter.h
// Programmer: Dan Cliburn
// Date: 10/22/2014
// Purpose: This is the header file for the PrimeCounter class.

#ifndef PRIMECOUNTER_H
#define PRIMECOUNTER_H

class PrimeCounter
{
	private:
		static int total_primes;
		static bool *values;

		static void isPrime(int num);

	public:
		PrimeCounter(int SIZE);

		void resetCounters(int SIZE);
		int getTotalPrimes() {return total_primes;}
		int countPrimeValues(int start, int stop);  //This one you will need to rewrite in PrimeCounter.cpp

		static void serialDeterminePrimes(int start, int stop);
		static void parallelDeterminePrimes(int start, int stop);
		
		~PrimeCounter();
};

#endif
