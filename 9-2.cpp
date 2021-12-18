#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <set>

using namespace std;

class HeightMap {
public:
    HeightMap(istream& in) {
        while (!in.eof()) {
            string line;
            getline(in, line); 

            if (line.length() > 0) {
                vector<int> new_line;
                stringstream ss(line);

                char num;
                while (ss >> num) {
                    new_line.push_back(num - '0');
                }

                if (!width) width =  new_line.size();
                map.push_back(new_line);
            }
        }
        
        height = map.size();
    }

    long long int sum_risk_levels() {
        long long int largest_1 = 0, largest_2 = 0, largest_3 = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (is_risk_point(i, j)) {
                    int size = find_basin_size(i, j);
                    cout << "basin size: " << size << '\n';
                    if (size >= largest_1) {
                        largest_3 = largest_2;
                        largest_2 = largest_1;
                        largest_1 = size;
                    } else if (size < largest_1 && size >= largest_2) {
                        largest_3 = largest_2;
                        largest_2 = size;
                    } else if (size < largest_2 && size >= largest_1) {
                        largest_1 = size;
                    }
                }
            }
        }
        cout << "LARGEST: " << largest_1 << '\n';
        cout << "SECOND LARGEST: " << largest_2 << '\n';
        cout << "THIRD LARGEST: " << largest_3 << '\n';
        return largest_1 * largest_2 * largest_3;
    }

    friend ostream& operator<<(ostream& out, const HeightMap& map);

private:
    int find_basin_size(int x, int y) {
        int directions_x[] = {1, -1, 0, 0};
        int directions_y[] = {0, 0, 1, -1};
        int number_of_directions = 4;
        int basin_size = 0;

        set<pair<int, int>> marked;
        queue<pair<int, int>> q;

        q.push(make_pair(x, y));
        while(!q.empty()) {
            basin_size++;
            pair<int, int> current = q.front();
            q.pop();
            int x = current.first;
            int y = current.second;

            for (int i = 0; i < number_of_directions; i++) {
                int new_x = x + directions_x[i];
                int new_y = y + directions_y[i];
                pair<int, int> p(new_x, new_y);

                if (exists(new_x, new_y) && marked.find(p) == marked.end() && map[new_x][new_y] != 9 && map[new_x][new_y] > map[x][y]) {
                    q.push(p);
                    marked.insert(p);
                }
            }
        }

        return basin_size;
    }

    bool exists(int x, int y) {
        bool exists = x >= 0 && x < this->height && y >= 0 && y < this->width;
        //cout << "exists(" << x << "," << y << "):" << exists << '\n';
        return exists;
    }
    
    bool is_risk_point(int x, int y) {
        int directions_x[] = {1, -1, 0, 0};
        int directions_y[] = {0, 0, 1, -1};
        int number_of_directions = 4;

        bool is_risk_point = true;
        for (int i = 0; i < number_of_directions; i++) {
            int new_x = x + directions_x[i];
            int new_y = y + directions_y[i];
            if (exists(new_x, new_y) && map[new_x][new_y] <= map[x][y]) {
                is_risk_point = false;
            }
        }

        return is_risk_point;
    } 
    
    vector<vector<int>> map;
    int width = 0;
    int height = 0;
};

ostream& operator<<(ostream& out, const HeightMap& map) {
    out << "HeightMap{" << map.width << "," << map.height << "}\n";
    for (auto line: map.map) {
        for (auto number: line) {
            out << number;
        }
        out << '\n';
    }
    return out;
}

int main(void) {
    ifstream fin("input.txt");

    HeightMap map(fin);
    cout << map << '\n';

    long long int product = map.sum_risk_levels();
    cout << "sum: " << product << '\n';
}

