/*
Lab 2
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include "Cities.h"
#include <iostream>

class State {
public:
	State() { name = "N/A"; }
	void setName(string stateName) { name = stateName; }
	string getName() const { return name; }
	void readStateCities() { stateCities.readCities(); }
	void printStateCities() { stateCities.printCityList(); }
private:
	string name;
	Cities stateCities;
};

int main() {
	State yourState;
	string stateName;

	cout << "Enter state: ";
	cin >> stateName;
	yourState.setName(stateName);
	yourState.readStateCities();

	cout << "The state " << yourState.getName() << " has the following cities/populations: " << endl;
	yourState.printStateCities();
	system("pause");
}