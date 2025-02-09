#include <fstream>
#include <print>
#include <string>

using namespace std;

size_t escape_len(const string& str) {
    size_t len = 0;
    for (size_t i = 1; i < str.size() - 1; ++i) {
        ++len;
        if (str[i] == '\\') {
            if (str[i + 1] == '\\') {
                ++i;
            } else if (str[i + 1] == '\"') {
                ++i;
            } else if (str[i + 1] == 'x') {
                if (isxdigit(str[i + 2]) && isxdigit(str[i + 3])) {
                    i += 3;
                }
            }
        }
    }
    return len;
}

size_t encode_len(const string& str) {
    size_t len = 2;
    for (size_t i = 0; i < str.size(); ++i) {
        ++len;
        if (str[i] == '\\' || str[i] == '\"') {
            ++len;
        }
    }
    return len;
}

void part() {
    ifstream input("input/input08");

    size_t res  = 0;
    size_t res2 = 0;
    for (string line; getline(input, line);) {
        res += line.size() - escape_len(line);
        res2 += encode_len(line) - line.size();
    }

    println("{}", res);
    println("{}", res2);
}

int main() {
    part();
    return 0;
}
