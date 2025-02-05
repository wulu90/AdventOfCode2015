#include <fstream>
#include <iostream>
#include <map>
#include <string_view>

using namespace std;

bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool badsub(char p, char c) {
    return (p == 'a' && c == 'b') || (p == 'c' && c == 'd') || (p == 'p' && c == 'q') || (p == 'x' && c == 'y');
}

bool is_nice(string_view sv) {
    size_t vowel_count = 0;
    bool has_same      = false;
    char p;
    for (size_t i = 0; i < sv.size(); ++i) {
        if (is_vowel(sv[i])) {
            ++vowel_count;
        }

        if (i > 0) {
            if (!has_same && p == sv[i]) {
                has_same = true;
            }
            if (badsub(p, sv[i])) {
                return false;
            }
        }
        p = sv[i];
    }
    if (vowel_count >= 3 && has_same) {
        return true;
    }
    return false;
}

void part1() {
    size_t res = 0;
    ifstream input("input/input05");
    for (string str; getline(input, str);) {
        if (is_nice(str)) {
            ++res;
        }
    }
    cout << res << endl;
}

bool is_nice2(string_view sv) {
    bool r1 = false;
    bool r2 = false;
    map<pair<char, char>, size_t> cmap;
    for (size_t i = 1; i < sv.size(); ++i) {
        if (!r1 && cmap.count({sv[i - 1], sv[i]}) != 0 && cmap[{sv[i - 1], sv[i]}] != i - 2) {
            r1 = true;
        } else {
            cmap.insert({{sv[i - 1], sv[i]}, i - 1});
        }
        if (i >= 2 && !r2 && sv[i] == sv[i - 2]) {
            r2 = true;
        }
        if (r1 && r2) {
            return true;
        }
    }
    return false;
}

void part2() {
    size_t res = 0;
    ifstream input("input/input05");
    for (string str; getline(input, str);) {
        if (is_nice2(str)) {
            ++res;
        }
    }
    cout << res << endl;
}

int main() {
    part1();
    part2();
}
