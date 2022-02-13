#include <iostream>
#include <string>
using namespace std;

class student {
public:
	string firstName;
	string lastName;
	int studentID;
	double gpa;
	void printName() {
		cout << lastName << "," << firstName << endl;
	}
};

int main() {
	student josh, kelvin;
	josh.firstName = "Josh";
	
}