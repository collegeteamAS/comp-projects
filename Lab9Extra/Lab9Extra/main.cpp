/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu
	Steve Suh
	h_suh@u.pacific.edu
	Notes:
	1.0 - 2014-09-26
		project done

*/


#include <iostream>
#include "fraction.h"


int main()
{
	
	 Fraction X, Y, Z;

	 std::cout << "Enter two fractions (in the form numerator/denominator): \n";
	 std::cin >> X;
	 std::cin >> Y;

	 Z = X + Y;
	 std::cout << X << " + " << Y << " = " << Z << "\n";
	 Z = X - Y;
	 std::cout << X << " - " << Y << " = " << Z << "\n";
	 Z = X * Y;
	 std::cout << X << " * " << Y << " = " << Z << "\n";
	 Z = X / Y;
	 std::cout << X << " / " << Y << " = " << Z << "\n";

	 std::cout << X << " as a double is " << (double)X << "\n";

	 system("pause");
	 

	/*Fraction test(36,54);
	test.simplify();
	std::cout << test << "\n";
	Fraction test2(567,4079);
	test2.simplify();
	std::cout << test2;
	//*/ // debug
	 return 0;
}