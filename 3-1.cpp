#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	ifstream fin("input.txt");

	int total_count {0};
	vector<int> count_of_ones;

	string binary;
	while (fin >> binary) {
		if (total_count == 0) {
			count_of_ones.resize(binary.size(), 0);
		}
		++total_count;
		for (auto i = 0; i < binary.size(); ++i) {
			if (binary.at(i) == '1') {
				count_of_ones[i]++;
			}
		}
	}

	int half = total_count / 2;
	int gamma_rate = 0;
	int epsilon_rate = 0;

	int digits_count = count_of_ones.size();
	for (int i = 0; i < digits_count; i++) {
		int gamma_digit = count_of_ones[i] > half ? 1 : 0;
		int epsilon_digit = gamma_digit == 1 ? 0 : 1;

		gamma_rate += gamma_digit << (digits_count - i - 1);
		epsilon_rate += epsilon_digit << (digits_count - i - 1);
	}

	cout << gamma_rate * epsilon_rate << endl;
}

