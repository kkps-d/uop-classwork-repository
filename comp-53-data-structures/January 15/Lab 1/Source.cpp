/*

Lab 1
Kaung Khant Pyae Sone
Kaung Min Sett (Tim)

*/
#include <iostream>
#include <string>
using namespace std;

class State {
public:
	State();
	void setName(string n) {
		name = n;
	}
	void setPopulation(int p) {
		population = p;
	}
	string getName() const {
		return name;
	}
	int getPopulation() const {
		return population;
	}
	void printSize() const;

private:
	string name;
	int population;
	string size(int p) const;
};

State::State() {
	name = "N/A";
	population = 0;
}

string State::size(int p) const {
	if (p < 1000000)
	{
		return "small";
	}
	if (p >= 1000000 && p < 5000000)
	{
		return "medium";
	}
	if (p >= 5000000)
	{
		return "large";
	}
}

void State::printSize() const {
	cout << getName() << ": " << size(population) << endl;
}

int main() {
	State state1;
	state1.printSize();
	state1.setName("California");
	state1.setPopulation(40000000);
	state1.printSize();
}