#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

enum Segment {
    UP = 0,
    UP_LEFT,
    UP_RIGHT,
    MIDDLE,
    DOWN,
    DOWN_LEFT,
    DOWN_RIGHT,
};

const vector<string>::iterator find_segment_by_length(vector<string> vec, int length) {
    return find_if(begin(vec), end(vec), [length](auto item) { return item.length() == length; });
}

vector<string> get_segments(const vector<string>& signal_patterns) {
    vector<char> v(7);
    auto segment_seven = *find_segment_by_length(signal_patterns, 3);
    auto segment_one = *find_segment_by_length(signal_patterns, 2);
    auto segment_four = *find_segment_by_length(signal_patterns, 4);
    auto segment_eight = *find_segment_by_length(signal_patterns, 7);

    cout << "segment one: " << segment_one << '\n';
    cout << "segment seven: " << segment_seven << '\n';
    cout << "segment four: " << segment_four << '\n';

    for (auto letter : segment_seven) {
        if (segment_one.find(letter) == string::npos) {
            v[UP] = letter;
        }
    }
    cout << "UP: " << v[UP] << '\n';

    auto segment_three = *find_if(signal_patterns.begin(), signal_patterns.end(), [segment_one](auto pattern) {
        return pattern.length() == 5 && pattern.find(segment_one[0]) != string::npos && pattern.find(segment_one[1]) != string::npos;
    });

    cout << "segment three: " << segment_three << '\n';

    for (auto letter: segment_three) {
        if (letter != v[UP] && segment_four.find(letter) == string::npos)
            v[DOWN] = letter;
        else if (letter != v[UP] && letter != segment_one[0] && letter != segment_one[1] && segment_four.find(letter) != string::npos)
            v[MIDDLE] = letter;
    }
    cout << "DOWN: " << v[DOWN] << '\n';
    cout << "MIDDLE: " << v[MIDDLE] << '\n';


    auto segment_nine = *find_if(signal_patterns.begin(), signal_patterns.end(), [segment_one, v](auto pattern) {
        return pattern.length() == 6 && pattern.find(segment_one[0]) != string::npos && pattern.find(segment_one[1]) != string::npos && pattern.find(v[MIDDLE]) != string::npos;
    });

    auto segment_six = *find_if(signal_patterns.begin(), signal_patterns.end(), [segment_nine, v](auto pattern) {
        return pattern.length() == 6 && pattern.compare(segment_nine) != 0 && pattern.find(v[MIDDLE]) != string::npos;
    });

    auto segment_zero = *find_if(signal_patterns.begin(), signal_patterns.end(), [segment_nine, v](auto pattern) {
        return pattern.length() == 6 && pattern.compare(segment_nine) != 0 && pattern.find(v[MIDDLE]) == string::npos;
    });

    for (auto letter: segment_nine) {
        if (segment_one.find(letter) != string::npos && segment_six.find(letter) != string::npos) {
            v[DOWN_RIGHT] = letter;
        }
    }
    cout << "DOWN_RIGHT: " << v[DOWN_RIGHT] << '\n';

    for (auto letter: segment_one) {
        if (letter != v[DOWN_RIGHT]) {
            v[UP_RIGHT] = letter;
        }
    }
    cout << "UP_RIGHT: " << v[UP_RIGHT] << '\n';

    auto segment_two = *find_if(signal_patterns.begin(), signal_patterns.end(), [v](auto pattern) {
        return pattern.length() == 5 && pattern.find(v[UP_RIGHT]) != string::npos && pattern.find(v[DOWN_RIGHT]) == string::npos;
    });

    auto segment_five = *find_if(signal_patterns.begin(), signal_patterns.end(), [segment_two, segment_three, v](auto pattern) {
        return pattern.length() == 5 && pattern.compare(segment_two) != 0 && pattern.compare(segment_three) != 0;
    });

    for (auto letter: segment_five) {
        if (segment_four.find(letter) != string::npos && v[MIDDLE] != letter && v[UP_RIGHT] != letter && v[DOWN_RIGHT] != letter) {
            v[UP_LEFT] = letter;
        }
    }
    cout << "UP_LEFT: " << v[UP_LEFT] << '\n';

    for (auto letter: segment_six) {
        if (segment_five.find(letter) == string::npos) {
            v[DOWN_LEFT] = letter;
        }
    }
    cout << "DOWN_LEFT: " << v[DOWN_LEFT] << '\n';

    vector<string> res { segment_zero, segment_one, segment_two, segment_three, segment_four, segment_five, segment_six, segment_seven, segment_eight, segment_nine };
    return res;
}

int main() {
    ifstream fin("input.txt");
     
    int sum = 0;
    while (fin) {
        string line;
        getline(fin, line);

        if (line.length() != 0) {
            stringstream ss(line);
            vector<string> signal_patterns;
            
            for (int i = 0; i < 10; i++) {
                string signal_pattern;
                ss >> signal_pattern;
                signal_patterns.push_back(signal_pattern);
            }
            cout << "patterns: ";
            for (auto pattern: signal_patterns) {
                cout << pattern << " ";
            }
            cout << '\n';
            
            auto segments = get_segments(signal_patterns);
            for (auto i = 0; i < segments.size(); ++i) {
                cout << "segment " << i << ": " << segments[i] << '\n';
            }

            char pipe;
            ss >> pipe;

            int current_power = 1000;
            int number = 0;
            cout << "result for output values ";
            for (int i = 0; i < 4; i++) {
                string output_value;
                ss >> output_value;
                cout << output_value << " ";

                sort(output_value.begin(), output_value.end());
                auto output_it = find_if(segments.begin(), segments.end(), [output_value](string item) {
                        sort(item.begin(), item.end());
                        return item.compare(output_value) == 0;
                });

                auto digit = output_it - segments.begin();

                number += digit * current_power;
                current_power /= 10;
            }
            cout << ": " << number << '\n';
            sum += number;
            cout << "sum until now: " << sum << '\n';
        }
    }
    cout << "resulting sum: " << sum << '\n';
}

