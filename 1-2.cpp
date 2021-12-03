#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	vector<int> measurements;
	ifstream fin("input.txt");

	int measurement;
	while (fin >> measurement) {
		measurements.push_back(measurement);
	}

	int number_of_increases = 0;
	for (auto it = measurements.begin(); it != measurements.end() - 3; ++it) {
		if (*it < *(it + 3)) {
			++number_of_increases;
		}
	}

	cout << number_of_increases << endl;
}
