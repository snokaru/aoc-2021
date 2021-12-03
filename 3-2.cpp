#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;

vector<string> filter_by_bit(const vector<string>& binaries, int bit, bool most_common) {

	int count_of_ones = 0;
	for (const string& binary: binaries) {
		if (binary.at(bit) == '1') {
			count_of_ones++;
		}
	}
	
	char bit_to_use;
	cout << "count of ones: " << count_of_ones << endl;
	if (count_of_ones == binaries.size() - count_of_ones) {
		bit_to_use = most_common ? '1' : '0';
	}
	else {
		char most_common_bit = count_of_ones > binaries.size() - count_of_ones ? '1' : '0';
		char least_common_bit = most_common_bit == '0' ? '1' : '0';
		bit_to_use = most_common ? most_common_bit : least_common_bit;
	}

	vector<string> filtered_binaries;
	for (const string& binary: binaries) {
		if (binary.at(bit) == bit_to_use) {
			filtered_binaries.push_back(binary);
		}
	}

	cout << "ran filter resulting in " << filtered_binaries.size() << " binaries remaining" << endl;
	return filtered_binaries;
}

int main() {
	ifstream fin("input.txt");

	vector<string> binaries;

	string binary;
	while (fin >> binary)
		binaries.push_back(binary);


	int binary_size = binaries[0].size();

	int bit = 0;
	vector<string> filtered_binaries = binaries;

	cout << "filtering binaries for oxygen generator" << endl;
	while (bit < binary_size && filtered_binaries.size() != 1) {
		filtered_binaries = filter_by_bit(filtered_binaries, bit, true);
		bit++;
	}
	cout << "resulting oxygen generator: " << filtered_binaries[0] << endl;
	unsigned long long oxygen_generator = bitset<64>(filtered_binaries[0]).to_ullong();

	bit = 0;
	filtered_binaries = binaries;
	cout << "filtering binaries for co2 scrubber" << endl;
	while (bit < binary_size && filtered_binaries.size() != 1) {
		filtered_binaries = filter_by_bit(filtered_binaries, bit, false);
		bit++;
	}
	cout << "resulting co2 scrubberl: " << filtered_binaries[0] << endl;
	unsigned long long co2_scrubber = bitset<64>(filtered_binaries[0]).to_ullong();

	cout << oxygen_generator * co2_scrubber << endl;
}

