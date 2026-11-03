#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int table[12][13] = {
    {-4, 11, 1, -4, -4, -4, -4, -4, -4, -4, -4, 0, -4},
    {-4, 11, 1, 2, -4, -4, -4, -4, -4, -4, -4, 0, -4},
    {-4, 11, 1, -4, 3, -4, -4, -4, 7, -4, -4, 0, -4},
    {-4, 11, 1, -4, -4, 4, -4, -4, -4, -4, -4, 0, -4},
    {-4, 11, 1, -4, -4, -4, 5, -4, -4, -4, -4, 0, -4},
    {-4, 11, 1, -4, -4, -4, -4, 6, -4, -4, -4, 0, -4},
    {-4, 11, 1, -4, -1, -4, -4, -4, -4, -4, -4, 0, -4},
    {-4, 11, 8, -4, -4, -4, -4, -4, -4, -4, -4, 0, -4},
    {-4, 11, 1, 2, -4, -4, -4, -4, -4, 9, -4, 0, -4},
    {-4, 11, 10, -4, -4, -4, -4, -4, -4, -4, -4, 0, -4},
    {-4, 11, 1, 2, -4, -4, -4, -4, -4, -4, -2, 0, -4},
    {-3, -3, 1, -4, -4, -4, -4, -4, -4, -4, -4, 0, -4}
};

int lengths[12] = {0, 1, 2, 3, 4, 5, 6, 3, 4, 5, 6, 1};

int symbolClass(char c) {
    if (c == '0') return 0;
    if (c >= '1' && c <= '9') return 1;
    if (c == 'i') return 2;
    if (c == 's') return 3;
    if (c == 'a') return 4;
    if (c == 'l') return 5;
    if (c == 'p') return 6;
    if (c == 'h') return 7;
    if (c == 'd') return 8;
    if (c == 'g') return 9;
    if (c == 't') return 10;
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n') return 11;
    return 12;
}

int main() {
    ifstream input("../input.txt");
    ofstream output("../output_cpp.txt");
    if (!input || !output) {
        cout << "File error\n";
        return 1;
    }

    string line;
    int row = 0;
    while (getline(input, line)) {
        row++;
        int state = 0;
        string value;
        for (char c : line) {
            value += c;
            state = table[state][symbolClass(c)];
            int keep = 0;
            if (state >= 0) keep = lengths[state];
            if (state == -1 || state == -2) keep = 7;
            if (state == -3) keep = 2;
            value = value.substr((int)value.size() - keep);
            if (state < 0) {
                if (state != -4) {
                    string type = "NUMBER";
                    if (state == -1) type = "ISALPHA";
                    if (state == -2) type = "ISDIGIT";
                    output << "<" << row << ", " << type << ", " << value << ">\n";
                }
                value = "";
                state = 0;
            }
        }
    }
    cout << "Done: output_cpp.txt\n";
}
