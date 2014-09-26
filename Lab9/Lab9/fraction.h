/*
	Andre Allan Ponce
	a_ponce1@u.pacific.edu


	Notes:
	1.0 - 2014-09-26
		project done

*/


class Fraction{
private:
	int numerator;
	int denominator;
public:
	Fraction(int n=0,int d=1);

	void divideBy(int num);
	void multiplyBy(int num);

	operator double();
	friend std::istream& operator>>(std::istream& in, Fraction& f);
	friend std::ostream& operator<<(std::ostream& out, Fraction& f);
	bool operator>(Fraction& f2);
	bool operator<(Fraction& f2);
	bool operator==(Fraction& f2);
	Fraction operator++();
	Fraction operator--();
	Fraction operator+(Fraction& f2);
	Fraction operator-(Fraction& f2);
	Fraction operator*(Fraction& f2);
	Fraction operator/(Fraction& f2);

	void simplify();
};