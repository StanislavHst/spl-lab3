#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int table[18][13] = {
    {16, 1, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {2, 2, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 4, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 5, 17, 17, 17, 10, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 6, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 7, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 8, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 9, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 11, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 12, 17, 17, 17},
    {17, 17, 13, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 14, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 15, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
    {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17}
};

string types[18] = {"", "UNKNOWN", "NUMBER", "UNKNOWN", "", "", "", "", "", "ISALPHA", "", "", "", "", "ISDIGIT", "SKIP", "UNKNOWN", ""};

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
        int pos = 0;
        while (pos < (int)line.size()) {
            int state = 0;
            int lastState = 0;
            int lastPos = pos;
            int next = pos;

            while (next < (int)line.size()) {
                state = table[state][symbolClass(line[next])];
                if (state == 17) break;
                next++;
                if (types[state] != "") {
                    lastState = state;
                    lastPos = next;
                }
            }

            string value = line.substr(pos, lastPos - pos);
            pos = lastPos;
            if (types[lastState] != "SKIP")
                output << "<" << row << ", " << types[lastState]
                       << ", " << value << ">\n";
        }
    }
    cout << "Done: output_cpp.txt\n";
}
