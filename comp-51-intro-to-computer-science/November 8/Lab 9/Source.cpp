#include <iostream>
#include <Windows.h>
using namespace std;

void setcolor(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

class Coordinate {
public:
	double x, y;
	int color;
	void set(int x1, int y1) {
		x = x1;
		y = y1;
		/*cout << "Coordinates are set to (" << x << "," << y << ")" << endl;*/
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	void move(int x1, int y1) {
		x = x + x1;
		y = y + y1;
	}
	void rotate() {
		int temp;
		temp = x;
		x = -y;
		y = temp;
	}
	void display() {
		cout << "(" << x << "," << y << ") located ";
		if (x != 0 && y != 0) {
			cout << "in quadrant ";
			if (x < 0 && y < 0)
			{
				setcolor(11);
				cout << "III" << endl;
				setcolor(7);
			}
			else
			{
				if (x < 0)
				{
					setcolor(10);
					cout << "II" << endl;
					setcolor(7);
				}
				if (y < 0)
				{
					setcolor(12);
					cout << "IV" << endl;
					setcolor(7);
				}
				if (x > 0 && y > 0)
				{
					setcolor(9);
					cout << "I" << endl;
					setcolor(7);
				}
			}
		}
		else
		{
			if (x == 0 && y == 0)
			{
				cout << "at the ";
				setcolor(5);
				cout << "origin" << endl;
				setcolor(7);
			}
			else
			{
				cout << "on the ";
				if (x == 0)
				{
					setcolor(13);
					cout << "Y-axis" << endl;
					setcolor(7);
				}
				if (y == 0)
				{
					setcolor(14);
					cout << "X-axis" << endl;
					setcolor(7);
				}
			}
		}
	}

};

double slope(Coordinate p1, Coordinate p2) {
	return (p2.y - p1.y) / (p2.x - p1.x);
}

int main() {
	Coordinate A, B, C;
	cout << "Rotating A:" << endl;
	A.set(1, 2);
	A.display();
	for (int i = 0; i < 4; i++)
	{
		A.rotate();
		A.display();
	}

	cout << "Incrementing B:" << endl;
	B.set(2, 3);
	B.display();
	B.move(1, 1);
	B.display();
	
	cout << "Move C to origin:" << endl;
	C.set(5, -4);
	C.display();
	C.move(-5, 4);
	C.display();

	cout << "Slope of A to B = ";
	setcolor(3);
	cout << slope(A, B);
	setcolor(7);
}