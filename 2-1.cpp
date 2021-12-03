#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream fin("input.txt");

	int depth = 0, horizontal = 0;

	string direction;
	int count;
	while (fin >> direction >> count) {
		if (direction ==  "forward") 
			horizontal += count;
		else if (direction ==  "down")
			depth += count;
		else if (direction ==  "up")
			depth -= count;
	}

	cout << horizontal * depth << endl;
	
}
