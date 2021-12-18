#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

    int sum_risk_levels() {
        int sum  = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (is_risk_point(i, j)) {
                    cout << "risk point (" << i << "," << j << "):" << map[i][j] << "\n";
                    sum += map[i][j] + 1;
                }
            }
        }
        return sum;
    }

    friend ostream& operator<<(ostream& out, const HeightMap& map);

private:
    bool exists(int x, int y) {
        bool exists = x >= 0 && x < this->height && y >= 0 && y < this->width;
        //cout << "exists(" << x << "," << y << "):" << exists << '\n';
        return exists;
    }
    
    bool is_risk_point(int x, int y) {
        cout << "scanning directions for point (" << x << "," << y << ")\n"; 
        int directions_x[] = {1, -1, 0, 0};
        int directions_y[] = {0, 0, 1, -1};
        int number_of_directions = 4;

        bool is_risk_point = true;
        for (int i = 0; i < number_of_directions; i++) {
            int new_x = x + directions_x[i];
            int new_y = y + directions_y[i];
            cout << "new point: (" << new_x << "," << new_y << ")\n";
            exists(new_x, new_y) ? cout << "the point exists!\n" : cout << "the point doesnt exist!\n";
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

    int sum = map.sum_risk_levels();
    cout << "sum: " << sum << '\n';
}
