#include <array>
#include <fstream>
#include <print>
#include <string>
#include <vector>

using namespace std;

struct instruction {
    string name;
    size_t reg_inx;
    int offset;
};

instruction parse(const string& str) {
    auto name  = str.substr(0, 3);
    int off    = 0;
    size_t reg = 0;
    if (name == "jmp"s) {
        size_t offpos = str[4] == '+' ? 5 : 4;
        from_chars(str.data() + offpos, str.data() + str.size(), off);
    } else if (name == "jie"s || name == "jio"s) {
        reg           = str[4] - 'a';
        size_t offpos = str[7] == '+' ? 8 : 7;
        from_chars(str.data() + offpos, str.data() + str.size(), off);
    } else {
        reg = str[4] - 'a';
    }

    return {name, reg, off};
}

void part1() {
    ifstream input("input/input23");

    vector<instruction> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(parse(line));
    }

    static array<int, 2> regs;

    size_t ins_inx = 0;
    while (ins_inx < ins_vec.size()) {
        auto& [name, reg, off] = ins_vec[ins_inx];
        if (name == "hlf"s) {
            regs[reg] /= 2;
            ++ins_inx;
        } else if (name == "tpl"s) {
            regs[reg] *= 3;
            ++ins_inx;
        } else if (name == "inc"s) {
            ++regs[reg];
            ++ins_inx;
        } else if (name == "jmp"s) {
            ins_inx += off;
        } else if (name == "jie"s) {
            ins_inx += regs[reg] % 2 == 0 ? off : 1;
        } else {
            ins_inx += regs[reg] == 1 ? off : 1;
        }
    }

    println("{}", regs[1]);
}

int main() {
    part1();
    return 0;
}
