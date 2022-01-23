#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

typedef vector<vector<char>> matrix;

matrix loadMatrix(ifstream& file);
vector<string> loadAnswers(ifstream& file);
void printMatrix(matrix mat);
void check(matrix mat, string answer, int r, int c, int dr, int dc);
string clean(string s);

int counter;

int main() {
    string filename;
    char isPuzzleDone;
    do {
        cout << "============================" << endl;
        cout << "Masukkan nama file : ";
        cin >> filename;
        string filedir = "../test/" + filename;
        ifstream file(filedir.c_str());
        matrix board;
        board = loadMatrix(file);
        printMatrix(board);
        vector<string> answers = loadAnswers(file);
        auto start = high_resolution_clock::now();
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
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by program: " << duration.count() << "seconds" << endl;
        cout << "Jumlah total perbandingan huruf yang dilakukan untuk menemukan kata di dalam puzzle: " << counter << " kali" << "\n\n";
        file.close();

        isPuzzleDone = 'n';
        cout << "Apakah anda ingin memecahkan puzzle lain? (y/n)" << endl;
        cin >> isPuzzleDone;
    } while ((isPuzzleDone == 'Y') || (isPuzzleDone == 'y'));
    cout << "============================" << endl;
    cout << "\nWord search puzzle solver by Kristo Abdi 13520058." << endl;
}

matrix loadMatrix(ifstream& file) {
    string line;
    matrix mat;
    while (getline(file, line)) {
        line = clean(line);
        if (line.length() == 0) break; //EOF

        vector<char> row;
        for (const char& cc : line) {
            if (cc >= 'A' && cc <= 'Z') {
                row.push_back(cc);
            }
        }
        mat.push_back(row);
    }
    
    return mat;
}

vector<string> loadAnswers(ifstream& file) {
    vector<string> answers;
    string line;
    while (getline(file, line)) {
        if (line.length() == 0) break;
        answers.push_back(clean(line));
    }
    return answers;
};

void printMatrix(matrix mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

string clean(string s) {
    // sometimes the file can have CRLF ending, so we need to clean the string first before using it.
    if (s.length() == 0) return s;
    if (s[s.length()-1] != '\x0D') return s;
    return s.substr(0, s.length()-1);
}

void check(matrix mat, string answer, int r, int c, int dr, int dc) {
    bool correct = true;
    matrix res = mat;
    matrix temp = mat;
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
        } else {
            temp[ri][ci] = '1';
        }
        counter++;
    }

    if (!correct) {
        return;
    }

    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (temp[i][j] != '1') {
                res[i][j] = '-';
            }
        }
    }
    printMatrix(res);
    cout << endl;
}

