#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int table[17][13] = {
    {16, 1, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {2, 2, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 4, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 5, 16, 16, 16, 10, 16, 16, 15, 16},
    {16, 1, 3, 16, 16, 6, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 16, 16, 7, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 16, 16, 16, 8, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 9, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 11, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 4, 16, 16, 16, 16, 16, 12, 16, 15, 16},
    {16, 1, 13, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 4, 16, 16, 16, 16, 16, 16, 14, 15, 16},
    {16, 1, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16},
    {16, 1, 3, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16}
};

int lengths[17] = {0, 1, 2, 1, 2, 3, 4, 5, 6, 7, 3, 4, 5, 6, 7, 0, 0};

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
            int remove = (int)value.size() - lengths[state];
            for (int i = 0; i < remove; i++) {
                char ch = value[i];
                if (ch != ' ' && ch != '\t' && ch != '\r')
                    output << "<" << row << ", UNKNOWN, " << ch << ">\n";
            }
            value = value.substr(remove);
            if (state == 2 || state == 9 || state == 14) {
                string type = "NUMBER";
                if (state == 9) type = "ISALPHA";
                if (state == 14) type = "ISDIGIT";
                output << "<" << row << ", " << type << ", " << value << ">\n";
                value = "";
                state = 0;
            }
        }
        for (char c : value)
            output << "<" << row << ", UNKNOWN, " << c << ">\n";
    }
    cout << "Done: output_cpp.txt\n";
}
