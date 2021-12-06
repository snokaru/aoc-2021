#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int DAYS = 80;
const int BASE_FISH_TIMER = 6;
const int NEW_FISH_TIMER = 8;

int main() {
    ifstream fin("input.txt");

    char comma;
    int num;
    bool first = true;

    vector<int> lanternfish;
    while ((first && fin >> num) || fin >> comma >> num) {
        if (first) first = false;
        lanternfish.push_back(num);
    }

    for (auto i = 0; i < DAYS; ++i) {
        int new_fish = 0;
        for (int& fish: lanternfish) {
            if (fish == 0) {
                fish = BASE_FISH_TIMER;
                new_fish++;
            } else fish--;
        }
        for (int i = 0; i < new_fish; ++i) {
            lanternfish.push_back(NEW_FISH_TIMER);
        }
    }

    cout << lanternfish.size() << endl;
}
