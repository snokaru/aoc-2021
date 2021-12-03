#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream fin("input.txt");

	int depth = 0, horizontal = 0;
	int aim = 0;

	string direction;
	int count;
	while (fin >> direction >> count) {
		if (direction ==  "forward") {
			horizontal += count;
			depth += aim * count;
		}
		else if (direction ==  "down")
			aim += count;
		else if (direction ==  "up")
			aim -= count;
	}

	cout << horizontal * depth << endl;
	
}
