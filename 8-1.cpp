#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("input.txt");
     
    int count = 0;
    while (fin) {
        string line;
        getline(fin, line);

        if (line.length() != 0) {
            stringstream ss(line);
            
            vector<string> signal_patterns;
            vector<string> output_values;

            for (int i = 0; i < 10; i++) {
                string signal_pattern;
                ss >> signal_pattern;
                signal_patterns.push_back(signal_pattern);
            }

            char pipe;
            ss >> pipe;

            cout << "output values: ";
            for (int i = 0; i < 4; i++) {
                string output_value;
                ss >> output_value;
                output_values.push_back(output_value);
                cout << output_value << " ";
                int length = output_value.length();
                if (length == 2 || length == 4 || length == 7 || length == 3)
                    count++;
            }
            cout << '\n';
        }
    }
    cout << "count " << count << '\n';
}

