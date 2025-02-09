#include <fstream>
#include <map>
#include <print>
#include <set>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

using namespace std;

enum class gate { AND, OR, NOT, LSHIFT, RSHIFT, DIRECT };

struct instruction {
    variant<string, int> input_0;
    variant<string, int> input_1;
    string output;
    gate g;
};

instruction parse(const string& str) {
    instruction inst;
    if (str.starts_with("NOT"s)) {
        auto space1  = str.find(' ');
        auto space2  = str.find(' ', space1 + 1);
        inst.input_0 = string{str.data() + space1 + 1, str.data() + space2};

        auto space3 = str.rfind(' ');
        inst.output = string{str.data() + space3 + 1, str.data() + str.size()};

        inst.g = gate::NOT;

    } else if (str.contains("AND"s) || str.contains("OR"s) || str.contains("LSHIFT"s) || str.contains("RSHIFT"s)) {
        auto space1 = str.find(' ');
        auto space2 = str.find(' ', space1 + 1);
        auto space3 = str.find(' ', space2 + 1);
        auto space4 = str.rfind(' ');

        auto num = 0;
        auto re  = from_chars(str.data(), str.data() + space1, num);
        if (re.ec == errc()) {
            inst.input_0 = num;
        } else {
            inst.input_0 = string{str.data(), str.data() + space1};
        }

        re = from_chars(str.data() + space2 + 1, str.data() + space3, num);
        if (re.ec == errc()) {
            inst.input_1 = num;
        } else {
            inst.input_1 = string{str.data() + space2 + 1, str.data() + space3};
        }

        inst.output = string{str.data() + space4 + 1, str.data() + str.size()};

        string_view sv{str.data() + space1 + 1, str.data() + space2};
        if (sv == "AND"sv) {
            inst.g = gate::AND;
        } else if (sv == "OR"sv) {
            inst.g = gate::OR;
        } else if (sv == "LSHIFT") {
            inst.g = gate::LSHIFT;
        } else {
            inst.g = gate::RSHIFT;
        }

    } else {
        auto space1 = str.find(' ');
        int num     = 0;
        auto re     = from_chars(str.data(), str.data() + space1, num);
        if (re.ec == errc()) {
            inst.input_0 = num;
        } else {
            inst.input_0 = string{str.data(), str.data() + space1};
        }

        auto space2 = str.rfind(' ');
        inst.output = string{str.data() + space2 + 1, str.data() + str.size()};

        inst.g = gate::DIRECT;
    }

    return inst;
}

int run(const vector<instruction>& ins_vec, map<string, int> name_val, set<string> unknown) {
    while (!unknown.empty()) {
        for (auto& ins : ins_vec) {
            if (ins.g == gate::DIRECT && (ins.input_0.index() == 0 && name_val.contains(get<0>(ins.input_0)))) {
                name_val.insert({ins.output, name_val[get<0>(ins.input_0)]});
                unknown.erase(ins.output);
            }

            if (ins.g == gate::NOT && name_val.contains(get<0>(ins.input_0))) {
                name_val.insert({ins.output, ~name_val[get<0>(ins.input_0)]});
                unknown.erase(ins.output);
            }

            if (ins.g == gate::AND || ins.g == gate::OR) {
                bool b0 = false;
                bool b1 = false;
                int n0, n1;
                if (ins.input_0.index() == 0 && name_val.contains(get<0>(ins.input_0))) {
                    b0 = true;
                    n0 = name_val[get<0>(ins.input_0)];
                }
                if (ins.input_0.index() == 1) {
                    b0 = true;
                    n0 = get<1>(ins.input_0);
                }

                if (ins.input_1.index() == 0 && name_val.contains(get<0>(ins.input_1))) {
                    b1 = true;
                    n1 = name_val[get<0>(ins.input_1)];
                }
                if (ins.input_1.index() == 1) {
                    b1 = true;
                    n1 = get<1>(ins.input_0);
                }

                if (b0 && b1) {
                    name_val[ins.output] = ins.g == gate::AND ? n0 & n1 : n0 | n1;
                    unknown.erase(ins.output);
                }
            }

            if (ins.g == gate::LSHIFT || ins.g == gate::RSHIFT) {
                if (name_val.contains(get<0>(ins.input_0))) {
                    int a                = name_val[get<0>(ins.input_0)];
                    int b                = get<1>(ins.input_1);
                    name_val[ins.output] = ins.g == gate::LSHIFT ? a << b : a >> b;
                    unknown.erase(ins.output);
                }
            }
        }
    }
    return name_val["a"];
}

void part1() {
    ifstream input("input/input07");
    vector<instruction> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(parse(line));
    }

    set<string> unknown;
    map<string, int> name_val;

    for (auto& ins : ins_vec) {
        if (ins.input_0.index() == 0) {
            unknown.insert(get<0>(ins.input_0));
        }
        if (ins.g != gate::DIRECT && ins.g != gate::NOT && ins.input_1.index() == 0) {
            unknown.insert(get<0>(ins.input_1));
        }

        unknown.insert(ins.output);

        if (ins.g == gate::DIRECT && ins.input_0.index() == 1) {
            name_val.insert({ins.output, get<1>(ins.input_0)});
            unknown.erase(ins.output);
        }
    }

    println("{}", run(ins_vec, name_val, unknown));
}

void part2() {
    ifstream input("input/input07");
    vector<instruction> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(parse(line));
    }

    set<string> unknown;
    map<string, int> name_val;

    for (auto& ins : ins_vec) {
        if (ins.input_0.index() == 0) {
            unknown.insert(get<0>(ins.input_0));
        }
        if (ins.g != gate::DIRECT && ins.g != gate::NOT && ins.input_1.index() == 0) {
            unknown.insert(get<0>(ins.input_1));
        }

        unknown.insert(ins.output);

        if (ins.g == gate::DIRECT && ins.input_0.index() == 1) {
            name_val.insert({ins.output, get<1>(ins.input_0)});
            unknown.erase(ins.output);
        }
    }
    name_val["b"] = run(ins_vec, name_val, unknown);

    println("{}", run(ins_vec, name_val, unknown));
}

int main() {
    part1();
    part2();
    return 0;
}
