#include <iostream>
using namespace std;

class Fraction
{
public:
	Fraction() {
		num = 1;
		den = 1;
	}
	Fraction(int num1, int den1) {
		setNum(num1);
		setDen(den1);
	}
	int getNum() {
		return num;
	}
	int getDen() {
		return den;
	}
	void setNum(int num1) {
		num = num1;
	}
	void setDen(int den1) {
		while (den1 == 0)
		{
			cout << "Denominator cannot be a zero!. Please enter a new number: ";
			cin >> den1;
		}
		den = den1;
	}
	void print() {
		cout << num << "/" << den << endl;
	}
	double getDecimal() {
		return double(num) / double(den);
	}
private:
	int num;
	int den;
};

int main() {
	Fraction frac(6, 10);
	frac.print();

	Fraction fracArray[3];
	int num;
	int den;
	cout << "Enter numerator for first fraction: ";
	cin >> num;
	cout << "Enter denominator for first fraction: ";
	cin >> den;
	fracArray[0].setNum(num);
	fracArray[0].setDen(den);

	cout << "Enter numerator for second fraction: ";
	cin >> num;
	cout << "Enter denominator for second fraction: ";
	cin >> den;
	fracArray[1].setNum(num);
	fracArray[1].setDen(den);

	cout << "Enter numerator for third fraction: ";
	cin >> num;
	cout << "Enter denominator for third fraction: ";
	cin >> den;
	fracArray[2].setNum(num);
	fracArray[2].setDen(den);

	int bigNum = 0;
	int bigDen = 0;
	double bigDec = -999;
	double dec;
	for (int i = 0; i < 3; i++)
	{
		num = fracArray[i].getNum();
		den = fracArray[i].getDen();
		dec = fracArray[i].getDecimal();
		if (bigNum < num)
		{
			bigNum = num;
		}
		if (bigDen < den)
		{
			bigDen = den;
		}
		if (bigDec < dec)
		{
			bigDec = dec;
		}
	}
	cout << "Biggest numerator: " << bigNum << endl;
	cout << "Biggest denominator: " << bigDen << endl;
	cout << "Biggest decimal: " << bigDec << endl;
}
