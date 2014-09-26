/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu


	Notes:
	1.0 - 2014-09-26
		project done

*/


#include <iostream>
#include <string>
#include "fraction.h"

// @author Andre Allan Ponce
Fraction::Fraction(int n, int d) : numerator(n), denominator(d){
	
}

// assume we can actually divide evenly
// @author Andre Allan Ponce
void Fraction::divideBy(int num){
	if(num != 0){
		numerator/=num;
		denominator/=num;
	}
}

// @author Andre Allan Ponce
void Fraction::multiplyBy(int num){
	numerator*=num;
	denominator*=num;
}

// @author Andre Allan Ponce
Fraction::operator double(){
	return (double)numerator / (double)denominator;
}

/*
	overloads extraction operator for Fraction
	input relies on '/' char to denote numerator or denominator
	@author Andre Allan Ponce
*/
std::istream& operator>>(std::istream& in, Fraction& f){
	std::string line;
	in >> line;
	int mid = line.find("/"); // find method locates index where the char is located
	if(mid > -1){ // find returns -1 if not char is not found
		int num = atoi(line.substr(0,mid).c_str()); // converts first half of string to int
		int den = atoi(line.substr(mid+1).c_str()); // converts second half of string to int (after the '/')
		if(den != 0){ // check if the denominator is 0, because thats bad
			f.numerator = num;
			f.denominator = den;
		}
		else{
			std::cout << "you can't divide by zero"; // you really can't
			f.denominator = 1;
		}
		f.simplify(); 
	}
	else{
		std::cout << "invalid number entered, defaulting to 0/1"; // and you can't type nothing either
	}
	return in;
}
//*/

// @author Andre Allan Ponce
std::ostream& operator<<(std::ostream& out, Fraction& f){
	out << f.numerator << "/" << f.denominator;
	return out;
}

bool Fraction::operator>(Fraction& f2)
{
	if(numerator*f2.denominator>f2.numerator*denominator)
		return true;
	else
		return false;
}

// @author Andre Allan Ponce
// @author Steve Suh
bool Fraction::operator<(Fraction& f2){
	return !(operator>(f2) || operator==(f2)); // don't need to rewrite the wheel
}

bool Fraction::operator==(Fraction& f2)
{
	if(numerator*f2.denominator == f2.numerator*denominator)
		return true;
	else
		return false;
}

// @author Andre Allan Ponce
Fraction Fraction::operator++(){
	int temp = numerator + denominator;
	return Fraction(temp, denominator);
}

// @author Andre Allan Ponce
Fraction Fraction::operator--(){
	int temp = numerator - denominator;
	return Fraction(temp,denominator);
}

Fraction Fraction::operator+(Fraction& f2)
{
	Fraction a(numerator*f2.denominator+f2.numerator*denominator,denominator*f2.denominator);
	a.simplify();
	return a;
}

Fraction Fraction::operator-(Fraction& f2)
{
	Fraction a(numerator*f2.denominator-f2.numerator*denominator,denominator*f2.denominator);
	a.simplify();
	return a;
}

// @author Andre Allan Ponce
Fraction Fraction::operator*(Fraction& f2){
	Fraction temp = Fraction(numerator*f2.numerator,denominator*f2.denominator);
	temp.simplify();
	return temp;
}

// @author Andre Allan Ponce
// almost like operator*, except flipped
Fraction Fraction::operator/(Fraction& f2){
	Fraction temp = Fraction(numerator*f2.denominator,denominator*f2.numerator);
	temp.simplify();
	return temp;
}

// @author Andre Allan Ponce
// @author Steve Suh
// simplifies a fraction
// can also simplify a negative fraction 
// EXCEPTION: if the denominator gets the negative sign, this method is toast.
// assume user does not input negative denominator
void Fraction::simplify()
{
	int count = 2; // starting at one would be infinite loop
	bool negativeNum = false;
	if(numerator < 0){ 
		negativeNum = true; // remember that this num is negative
		numerator = std::abs(numerator); // abs value is easier to deal with
	}
	while(numerator>= count && denominator >= count){ // if our divsor number (count) is greater than the numerator or denominator, then we cant simplify no more

		if(numerator%count==0 && denominator%count==0) // numerator and denominator divisble by count
		{
			 //std::cout << numerator << "/" << denominator << "\n"; // debug
			divideBy(count); 
		}
		else{
			count++; 
		}
	}
	if(negativeNum){ // if we started with a negative number, make this number negative again
		numerator = -numerator;
	}
}


