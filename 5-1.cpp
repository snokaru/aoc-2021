#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;


int main() {
    ifstream fin("input.txt");
    vector<pair<pair<int, int>, pair<int, int>>> lines;
    

    int n = 0, m = 0;
    char gt, ms, comma; // greater than, minus sign, comma
    int x1, y1, x2, y2;
    while (fin >> x1 >> comma >> y1 >> ms >> gt >> x2 >> comma >> y2) {
        lines.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2))); 
        if (x1 > n) n = x1;
        if (x2 > n) n = x2;
        if (y1 > m) m = y1;
        if (y2 > m) m = y2;
    }
    m++;
    n++;

    for (auto& item: lines) {
        cout << "(" << item.first.first << "," << item.first.second << ")";
        cout << "->";
        cout << "(" << item.second.first << "," << item.second.second << ")";
        cout << endl;
    }

    vector<vector<int>> diagram(n, vector<int>(m, 0));

    for (auto& line: lines) {
        int x1 = line.first.first;
        int y1 = line.first.second;
        int x2 = line.second.first;
        int y2 = line.second.second;

        if (x1 == x2) {
            int line_start = min(y1, y2);
            int line_end = max(y1, y2);
            
            for (int i = line_start; i <= line_end; ++i)
                diagram[x1][i]++;
        }
        else if (y1 == y2) {
            int line_start = min(x1, x2);
            int line_end = max(x1, x2);

            for (int i = line_start; i <= line_end; ++i)
                diagram[i][y1]++;
        }
    }

    int count = 0;
    for (auto i = diagram.begin(); i != diagram.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            if (*j >= 2) count++;
        }
    }
    cout << count << endl;
}
