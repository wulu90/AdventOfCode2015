#include <map>
#include <print>
#include <string>

using namespace std;

void incrementing(string& str, size_t inx) {
    if (str[inx] == 'z') {
        str[inx] = 'a';
        incrementing(str, inx - 1);
    } else {
        str[inx] += 1;
    }
}

bool straight_three(const string& str) {
    bool res = false;
    for (size_t i = 0; i < str.size() - 3; ++i) {
        if (str[i + 1] == str[i] + 1 && str[i + 2] == str[i] + 2) {
            res = true;
            break;
        }
    }
    return res;
}

bool confusing_letter(const string& str) {
    if (str.contains('i') || str.contains('o') || str.contains('l')) {
        return true;
    }
    return false;
}

bool letter_pairs(const string& str) {
    map<char, size_t> char_inx;
    for (size_t i = 1; i < str.size(); ++i) {
        if (str[i] == str[i - 1]) {
            char_inx[str[i]] = i - 1;
        }
    }

    if (char_inx.size() > 1) {
        return true;
    }
    return false;
}

bool valid(const string& str) {
    return straight_three(str) && (!confusing_letter(str)) && letter_pairs(str);
}

void part1() {
    string input{"cqjxjnds"};

    do {
        incrementing(input, input.size() - 1);
    } while (!valid(input));

    println("{}", input);
}

void part2() {
    string input{"cqjxjnds"};

    do {
        incrementing(input, input.size() - 1);
    } while (!valid(input));

    do {
        incrementing(input, input.size() - 1);
    } while (!valid(input));

    println("{}", input);
}

int main() {
    part1();
    part2();
    return 0;
}
