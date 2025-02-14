#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

map<string, int> parse(const string& str) {
    map<string, int> sue;
    auto colon = str.find(':');
    auto spv   = string_view{str.begin() + colon + 2, str.end()} | views::split(", "sv);
    for (auto subv : spv) {
        string_view sv{subv};
        auto pos = sv.find(':');
        int num  = 0;
        from_chars(sv.begin() + pos + 2, sv.end(), num);
        sue.insert({{sv.begin(), sv.begin() + pos}, num});
    }
    return sue;
}

void part1() {
    ifstream input("input/input16");
    vector<map<string, int>> sue_vec;
    for (string line; getline(input, line);) {
        sue_vec.push_back(parse(line));
    }

    map<string, int> gift{{"children"s, 3}, {"cats"s, 7},     {"samoyeds"s, 2}, {"pomeranians"s, 3}, {"akitas"s, 0},
                          {"vizslas"s, 0},  {"goldfish"s, 5}, {"trees"s, 3},    {"cars"s, 2},        {"perfumes"s, 1}};

    for (size_t i = 0; i < sue_vec.size(); ++i) {
        bool find = true;
        for (auto& [k, v] : sue_vec[i]) {
            if (gift[k] != v) {
                find = false;
                break;
            }
        }

        if (find) {
            println("{}", i + 1);
            break;
        }
    }
}

void part2() {
    ifstream input("input/input16");
    vector<map<string, int>> sue_vec;
    for (string line; getline(input, line);) {
        sue_vec.push_back(parse(line));
    }

    map<string, int> gift{{"children"s, 3}, {"cats"s, 7},     {"samoyeds"s, 2}, {"pomeranians"s, 3}, {"akitas"s, 0},
                          {"vizslas"s, 0},  {"goldfish"s, 5}, {"trees"s, 3},    {"cars"s, 2},        {"perfumes"s, 1}};

    for (size_t i = 0; i < sue_vec.size(); ++i) {
        bool find = true;
        for (auto& [k, v] : sue_vec[i]) {
            if ((k == "cats"s || k == "trees"s) && v <= gift[k]) {
                find = false;
                break;
            }
            if ((k == "pomeranians"s || k == "goldfish"s) && v >= gift[k]) {
                find = false;
                break;
            }

            if ((k == "children"s || k == "samoyeds"s || k == "akitas"s || k == "vizslas"s || k == "cars"s || k == "perfumes"s) &&
                gift[k] != v) {
                find = false;
                break;
            }
        }

        if (find) {
            println("{}", i + 1);
            break;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
