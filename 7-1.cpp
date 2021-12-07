#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;


int main(void) {
    ifstream fin("input.txt");

    int next;
    int max_position = 0;
    char comma;
    vector<int> crabs;
    
    bool first = true;
    while ((first && fin >> next) || fin >> comma >> next) {
        if (first) first = false;
        crabs.push_back(next);
        if (next > max_position) max_position = next;
    }
    
    for (int c: crabs) {
        cout << c << " ";
    }
    cout << endl;

    int minimum = -1, minimum_pos;
    for (int i = 0; i <= max_position; ++i) {
        int distance = 0;
        for (auto it = crabs.begin(); it != crabs.end(); ++it) {
            distance += abs(i - *it);
        }
        if (distance < minimum || minimum == -1) {
            minimum = distance;
            minimum_pos = i;
        }
    }
    cout << "minimum fuel: " <<  minimum << endl;
    cout << "minimum position: " << minimum_pos << endl;

}
