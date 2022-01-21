#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
int n, m, anssize;
vector<vector<char>> mat;
vector<string> ans;

void loadMatrix(string filename);
void printMatrix(vector<vector<char>> matrix, vector<string> answer);
void checkHorizontalRight(string answer, int x, int y);
void checkHorizontalLeft(string answer, int x, int y);
void checkVerticalUp(string answer, int x, int y);
void checkVerticalDown(string answer, int x, int y);
void checkDiagonalUpRight(string answer, int x, int y);
void checkDiagonalUpLeft(string answer, int x, int y);
void checkDiagonalDownRight(string answer, int x, int y);
void checkDiagonalDownLeft(string answer, int x, int y);

int main() {
    string filename;
    cout << "Masukkan nama file : ";
    cin >> filename;
    loadMatrix(filename);

    for (int a = 0; a < anssize; a++) {
        string answer = ans[a];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j+answer.length() <= m) {
                    checkHorizontalRight(answer, i, j);
                }
                if (i+answer.length() <= n) {
                    checkVerticalDown(answer, i, j);
                }
                if (j-answer.length()+1 >= 0) {
                    checkHorizontalLeft(answer, i, j);
                }
                // if (i-answer.length()+1 >= 0) {
                //     checkVerticalUp(answer, i, j);
                // }
                // if ((i-answer.length()+1 >= 0) && (j+answer.length() <= m)) {
                //     checkDiagonalUpRight(answer, i, j);
                // }
                // if ((i-answer.length()+1 >= 0) && (j-answer.length()+1 >= 0)) {
                //     checkDiagonalUpLeft(answer, i, j);
                // }
                if ((i+answer.length() <= n) && (j+answer.length() <= m)) {
                    checkDiagonalDownRight(answer, i, j);
                }
                if ((i+answer.length() <= n) && (j-answer.length()+1 >= 0)) {
                    checkDiagonalDownLeft(answer, i, j);
                }
            }
        }
    }
}

void loadMatrix(string filename) {
    fstream f;
    f.open(filename.c_str());
    string line;
    int i = 0;
    int j = 0;
    while(getline(f, line)) {
        if (!f) break;
        mat.push_back(vector<char>());
        istringstream fline(line);
        j = 0;
        while (true) {
            char val;
            fline >> val;
            if (!fline) break;
            mat[i].push_back(val);
            j++;
        }
        if (n == 0) {
            m = j;
        }
        if (line.length() == 0) {
            break;
        }
        i++;
        n++;
    }
    while(!f.eof()) {
        getline(f, line);
        string val;
        istringstream fline(line);
        fline >> val;
        ans.push_back(val);
        anssize++;
    }
}

void printMatrix(vector<vector<char>> matrix, vector<string> answer) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << n << " " << m << endl;

    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << endl;
    }
    cout << anssize;
}

void checkHorizontalRight(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int i = 0;
    for (int j = y; j < y + answer.length(); ++j) {
        if (mat[x][j] != answer[i]) {
            correct = false;
            return;
        }
        i++;

        if (i == len) {
            correct = true;
            break;
        }
    }

    if (correct) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i != x || j < y || (j >= y + answer.length())) {
                    cout << "- ";
                } else {
                    if (j==y) {
                        while (len !=0) {
                            cout << mat[i][j] << " "; 
                            len--;
                            ++j;
                        }
                        j-=1;
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

void checkHorizontalLeft(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int i = 0;
    for (int j = y; j > y - answer.length(); j--) {
        if (mat[x][j] != answer[i]) {
            correct = false;
            return;
        }
        i++;

        if (i == len) {
            correct = true;
            break;
        }
    }

    if (correct) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i != x || j > y || (j <= y - answer.length())) {
                    cout << "- ";
                } else {
                    if (j==y-len+1) {
                        while (len !=0) {
                            cout << mat[i][j] << " "; 
                            len--;
                            ++j;
                        }
                        j-=1;
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

void checkVerticalUp(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int j = 0;
    for (int i = x; i > x - answer.length(); i--) {
        if (mat[i][y] != answer[j]) {
            j = 0;
            correct = false;
            return;
        }
        j++;

        if (j == len) {
            correct = true;
            break;
        }
    }

    if (correct) {
        bool done = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j != y || i > x || i <= x - answer.length()) {
                    cout << "- ";
                } else {
                    if (i==x-len+1 || !done) {
                        cout << mat[i][j] << " ";
                    }
                    if (i==x) {
                        done = true;
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};


void checkVerticalDown(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int j = 0;
    for (int i = x; i < x + answer.length(); i++) {
        if (mat[i][y] != answer[j]) {
            j = 0;
            correct = false;
            break;
        }
        j++;

        if (j == len) {
            correct = true;
            break;
        }
    }

    if (correct) {
        bool done = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j != y || i < x || i >= x + answer.length()) {
                    cout << "- ";
                } else {
                    if (i==x|| !done) {
                        cout << mat[i][j] << " ";
                    }
                    if (i==x+len-1) {
                        done = true;
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};

void checkDiagonalUpRight(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int i = x, j = y;
    int k = 0;
    vector<vector<char>> copy = mat;
    while ((i < i + len) && (j < j + len)) {
        if (mat[i][j] != answer[k]) {
            correct = false;
            return;
        } else {
            copy[i][j] = '1';
            k++;
            i--;
            j++;
        }
        if (k == len) {
            correct = true;
            break;
        }
    }
    
    if (correct) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (copy[i][j] == '1') {
                    cout << mat[i][j] << " ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};

void checkDiagonalUpLeft(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int i = x, j = y;
    int k = 0;
    vector<vector<char>> copy = mat;
    while ((i < i + len) && (j < j + len)) {
        if (mat[i][j] != answer[k]) {
            correct = false;
            return;
        } else {
            copy[i][j] = '1';
            k++;
            i--;
            j--;
        }
        if (k == len) {
            correct = true;
            break;
        }
    }
    
    if (correct) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (copy[i][j] == '1') {
                    cout << mat[i][j] << " ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};

void checkDiagonalDownRight(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int i = x, j = y;
    int k = 0;
    vector<vector<char>> copy = mat;
    while ((i < i + len) && (j < j + len)) {
        if (mat[i][j] != answer[k]) {
            correct = false;
            return;
        } else {
            copy[i][j] = '1';
            k++;
            i++;
            j++;
        }
        if (k == len) {
            correct = true;
            break;
        }
    }
    
    if (correct) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (copy[i][j] == '1') {
                    cout << mat[i][j] << " ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};

void checkDiagonalDownLeft(string answer, int x, int y) {
    int len = answer.length();
    bool correct = true;
    int i = x, j = y;
    int k = 0;
    vector<vector<char>> copy = mat;
    while ((i < i + len) && (j < j + len)) {
        if (mat[i][j] != answer[k]) {
            correct = false;
            return;
        } else {
            copy[i][j] = '1';
            k++;
            i++;
            j--;
        }
        if (k == len) {
            correct = true;
            break;
        }
    }
    
    if (correct) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (copy[i][j] == '1') {
                    cout << mat[i][j] << " ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};