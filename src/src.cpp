#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

typedef vector<vector<char>> matrix;

matrix loadMatrix(ifstream& file);
vector<string> loadAnswers(ifstream& file);
void printMatrix(matrix m);
void check(matrix mat, string answer, int r, int c, int dr, int dc);
string clean(string s);

int main() {
    string filename = "test.txt";
    // cout << "Masukkan nama file : ";
    // cin >> filename;
    ifstream file(filename);

    matrix board = loadMatrix(file);
    vector<string> answers = loadAnswers(file);

    // debug
    printMatrix(board);

    for (const string& answer : answers) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {

                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr == 0 && dc == 0) continue;
                        check(board, answer, i, j, dr, dc);
                    }
                }
            }
        }
    }
    file.close();
}

matrix loadMatrix(ifstream& file) {
    string line;
    matrix res;
    while (getline(file, line)) {
        line = clean(line);
        if (line.length() == 0) break;

        vector<char> row;
        for (const char& cc : line) {
            if ('A' <= cc && cc <= 'Z') {
                row.push_back(cc);
            }
        }
        res.push_back(row);
    }
    
    return res;
}

vector<string> loadAnswers(ifstream& file) {
    string line;
    vector<string> res;
    while (getline(file, line)) {
        res.push_back(clean(line));
    }
    return res;
}

void printMatrix(matrix m) {
    for (const vector<char>& row : m) {
        for (char cc : row) {
            cout << cc << " ";
        }
        cout << endl;
    }
}

void check(matrix mat, string answer, int r, int c, int dr, int dc) {
    bool correct = true;
    for (int i = 0; i < answer.length(); i++) {
        int ri = r + dr * i;
        int ci = c + dc * i;
        if (
            ri < 0 || ri >= mat.size() || // overflow vertically
            ci < 0 || ci >= mat[ri].size() || // overflow horizontally
            mat[ri][ci] != answer[i]
        ) {
            correct = false;
            break;
        }
    }

    if (!correct) {
        return;
    }

    vector<vector<char>> displayedMatrix(mat);

    for (int i = 0; i < answer.length(); i++) {
        int ri = r + dr * i;
        int ci = c + dc * i;
        displayedMatrix[ri][ci] = '-';
    }

    cout << answer << endl;
    printMatrix(displayedMatrix);
    cout << endl;
}

string clean(string s) {
    // sometimes the file can have CRLF ending, so we need to clean the string first before using it.
    if (s.length() == 0) return s;
    if (s[s.length()-1] != '\x0D') return s;
    return s.substr(0, s.length()-1);
}
