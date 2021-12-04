#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class BingoBoard {
public:
    BingoBoard(int rows, int columns)
    : rows(rows), columns(columns), board(rows, vector<int>(columns)) {}

    int mark(int number) {
        for (auto i = 0; i < board.size(); ++i) {
            for (auto j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == number) {
                    board[i][j] = -1;
                }
            }
        }

        if (!check_win())
            return 0;

        cout << "winning number: " << number << "\n";

        int sum = 0;
        for (auto i = 0; i < board.size(); ++i) {
            for (auto j = 0; j < board[i].size(); ++j) {
                if (board[i][j] != -1) {
                    sum += board[i][j];
                }
            }
        }
        return sum * number;

    }

    void set(int i, int j, int num) {
        board[i][j] = num;
    }

    int get(int i, int j) const {
        return board[i][j];
    }

    int get_rows() const {
        return rows;
    }

    int get_columns() const {
        return columns;
    }

private:
    bool check_win() {
        for (auto i = 0; i < board.size(); ++i) {
            bool is_marked_row = true;
            bool is_marked_column = true;
            for (auto j = 0; j < board[i].size(); ++j) {
                if (board[i][j] != -1)
                    is_marked_row = false;
                if (board[j][i] != -1)
                    is_marked_column = false;
            }
            if (is_marked_row || is_marked_column)
                return true;
        }
        return false;
    }


    int rows, columns;
    vector<vector<int>> board;
};

int main() {
    ifstream fin("input.txt");

    string first_line;
    getline(fin, first_line);

    vector<int> bingo_numbers;

    int pos;
    while ((pos = first_line.find(",")) != string::npos) {
        string token = first_line.substr(0, pos);
        bingo_numbers.push_back(stoi(token));
        first_line.erase(0, pos + 1);
    }
    bingo_numbers.push_back(stoi(first_line));

    cout << "bingo numbers:" << endl;
    for (auto& i: bingo_numbers) cout << i << " ";
    cout << endl;


    vector<BingoBoard> boards;

    while (!fin.eof()) {
        BingoBoard board(5, 5);
        int scan_over = false;
        for (auto i = 0; i < board.get_rows(); ++i) {
            for (auto j = 0; j < board.get_columns(); ++j) {
                if (fin.eof()) {
                    scan_over = true;
                    break;
                }
                int num;
                fin >> num;
                board.set(i, j, num);
            }
        }
        if (scan_over)
            break;
        boards.push_back(board);
    }

    cout << "scanned " << boards.size() << " boards" << endl;

    cout << endl;
    for (const BingoBoard& board: boards) {
        for (auto i = 0; i < board.get_rows(); ++i) {
            for (auto j = 0; j < board.get_columns(); ++j) {
                cout << board.get(i, j) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    vector<bool> already_won(boards.size());
    int winning_score = 0;
    for (int num: bingo_numbers) {
        for (int i = 0; i < boards.size(); i++) {
            if (already_won[i]) continue;
            int score = boards[i].mark(num);
            if (score > 0) {
                winning_score = score;
                already_won[i] = true;
            }
        }
    }
    cout << winning_score << endl;
}
