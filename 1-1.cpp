#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream fin("input.txt");

	int previous = -1;
	int current;
	int increases = 0;

	while (fin >> current) {
		if (previous != -1 && current > previous)
			increases++;
		previous = current;
	}

	cout << increases << endl;
}
