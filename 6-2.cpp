#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <iomanip>
using namespace std;

const int DAYS = 256;
const int BASE_FISH_TIMER = 6;
const int NEW_FISH_TIMER = 8;
long long computed[NEW_FISH_TIMER + 1][DAYS + 1];

long long number_of_fish(int lifetime, int days) {
    if (lifetime >= days) {
        return 1;
    }
    if (!computed[lifetime][days])
        computed[lifetime][days] = number_of_fish(BASE_FISH_TIMER, days - lifetime - 1) + number_of_fish(NEW_FISH_TIMER, days - lifetime - 1);
    return computed[lifetime][days];
}

int main() {
    ifstream fin("input.txt");

    char comma;
    int num;
    bool first = true;

    vector<int> lanternfish;
    set<int> unique_fish;

    while ((first && fin >> num) || fin >> comma >> num) {
        if (first) first = false;
        lanternfish.push_back(num);
        unique_fish.insert(num);
    }

    long long result = 0;
    for (int unique: unique_fish) {
        long long current = number_of_fish(unique, DAYS);
        long long count = 0;
        for (int fish: lanternfish) {
            if (fish == unique) count++;
        }
        result += count * current;
    }
    cout << result << endl;
}
