

#include <iostream>
#include <string>

using namespace std;

class Fraction
{
	private:
		int num;
		int den;
	public:
		Fraction()
		{
			num = 1;
			den = 1;
		}
		Fraction(int n, int d)
		{
			num = n;
			if(d == 0)
			{
				den = 1;
				cout << "You can't have zero in the denominator!\n" << "Setting the denominator to 1.\n";
			}
			else
				den = d;
		}

		double getDecimal()
		{
			return ((double)num) / den;
		}
		int getDenominator()
		{
			return den;
		}

		int getNumerator()
		{
			return num;
		}

		void print()
		{
			cout << num << "/" << den;
		}

		void setDenominator(int d)
		{
			if(d == 0)
				den = 1;
			else
				den = d;
		}
		void setNumerator(int n)
		{
			num = n;
		}
};

int findIndexOfLargestDecimal(Fraction fractions[], int size); // returns the index of the fraction with the largest decimal equivalent
int findIndexOfLargestDenominator(Fraction fractions[], int size); // returns the index of the fraction with the largest denominator
int findIndexOfLargestNumerator(Fraction fractions[], int size); // returns the index of the fraction with largest numerator
void fractionPrompt(Fraction fractions[], int index); // prompts for fraction data and sets fraction num and den
int numberPrompt(bool isDenominator); // prompts for a number

int main()
{
	Fraction fraction = Fraction(6,10);
	fraction.print();
	cout << "\n";
	const int FRACTIONS_SIZE = 3;
	Fraction fractions[FRACTIONS_SIZE];
	for(int i = 0; i < 3; i++)
	{
		fractionPrompt(fractions,i);
	}
	cout << "The fraction with the largest numerator is ";
	fractions[findIndexOfLargestNumerator(fractions,FRACTIONS_SIZE)].print();
	cout << ".\n" << "The fraction with the largest denominator is ";
	fractions[findIndexOfLargestDenominator(fractions,FRACTIONS_SIZE)].print();
	cout << ".\n" << "The fraction with the largest decimal equivalent is ";
	fractions[findIndexOfLargestDecimal(fractions,FRACTIONS_SIZE)].print();
	cout << ".\n";
	system("pause");

	return 0;
}

int findIndexOfLargestDecimal(Fraction fractions[], int size)
{
	double max = 0.0;
	int maxIndex;
	for(int i = 0; i < size; i++)
	{
		if(fractions[i].getDecimal() > max)
		{
			max = fractions[i].getDecimal();
			maxIndex = i;
		}
	}
	return maxIndex;
}

int findIndexOfLargestDenominator(Fraction fractions[], int size)
{
	int max = 0;
	int maxIndex;
	for(int i = 0; i < size; i++)
	{
		if(fractions[i].getDenominator() > max)
		{
			max = fractions[i].getDenominator();
			maxIndex = i;
		}
	}
	return maxIndex;
}

int findIndexOfLargestNumerator(Fraction fractions[], int size)
{
	int max = 0;
	int maxIndex;
	for(int i = 0; i < size; i++)
	{
		if(fractions[i].getNumerator() > max)
		{
			max = fractions[i].getNumerator();
			maxIndex = i;
		}
	}
	return maxIndex;
}

void fractionPrompt(Fraction fractions[], int index)
{
	int numerator = numberPrompt(false);
	int denominator = numberPrompt(true);
	fractions[index].setNumerator(numerator);
	fractions[index].setDenominator(denominator);
	cout << "Creating fraction ";
	fractions[index].print();
	cout << ".\n";
}

int numberPrompt(bool isDenominator)
{
	bool invalid = false;
	int number;
	string choice;
	if(isDenominator)
		choice = "denominator";
	else
		choice = "numerator";

	do
	{
		cout << "Enter a value for the " << choice << ": ";
		cin >> number;
		if(isDenominator && number == 0)
		{
			invalid = true;
			cout << "The denominator cannot be zero! Try again.\n";
		}
	}while(invalid);
	return number;
}