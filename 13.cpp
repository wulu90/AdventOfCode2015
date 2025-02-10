#include <fstream>
#include <map>
#include <print>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

tuple<string, string, int> parse(const string& str) {
    auto space1 = str.find(' ');
    auto space2 = str.find(' ', space1 + 1);
    auto space3 = str.find(' ', space2 + 1);
    auto space4 = str.find(' ', space3 + 1);
    auto space5 = str.rfind(' ');

    int num = 0;
    from_chars(str.data() + space3 + 1, str.data() + space4, num);

    if (string_view{str.data() + space2 + 1, str.data() + space3} == "lose"sv) {
        num = -num;
    }

    return {{str.data(), str.data() + space1}, {str.data() + space5 + 1, str.data() + str.size() - 1}, num};
}

void part1() {
    ifstream input("input/input13");

    map<pair<string, string>, int> comfort_map;
    set<string> person_set;
    for (string line; getline(input, line);) {
        auto [s1, s2, num] = parse(line);
        comfort_map.insert({{s1, s2}, num});
        person_set.insert(s1);
        person_set.insert(s2);
    }

    vector<string> person_vec;
    for (auto& p : person_set) {
        person_vec.push_back(p);
    }

    int fitmax = 0;

    do {
        int fitval = 0;
        for (size_t i = 0; i < person_vec.size() - 1; ++i) {
            fitval += comfort_map[{person_vec[i], person_vec[i + 1]}];
            fitval += comfort_map[{person_vec[i + 1], person_vec[i]}];
        }

        fitval += comfort_map[{person_vec.back(), person_vec.front()}];
        fitval += comfort_map[{person_vec.front(), person_vec.back()}];

        fitmax = max(fitmax, fitval);
    } while (next_permutation(person_vec.begin(), person_vec.end()));

    println("{}", fitmax);
}

void part2() {
    ifstream input("input/input13");

    map<pair<string, string>, int> comfort_map;
    set<string> person_set;
    for (string line; getline(input, line);) {
        auto [s1, s2, num] = parse(line);
        comfort_map.insert({{s1, s2}, num});
        person_set.insert(s1);
        person_set.insert(s2);
    }

    string you{"hy"};

    vector<string> person_vec;
    for (auto& p : person_set) {
        person_vec.push_back(p);

        comfort_map.insert({{you, p}, 0});
        comfort_map.insert({{p, you}, 0});
    }

    person_vec.push_back(you);

    int fitmax = 0;

    do {
        int fitval = 0;
        for (size_t i = 0; i < person_vec.size() - 1; ++i) {
            fitval += comfort_map[{person_vec[i], person_vec[i + 1]}];
            fitval += comfort_map[{person_vec[i + 1], person_vec[i]}];
        }

        fitval += comfort_map[{person_vec.back(), person_vec.front()}];
        fitval += comfort_map[{person_vec.front(), person_vec.back()}];

        fitmax = max(fitmax, fitval);
    } while (next_permutation(person_vec.begin(), person_vec.end()));

    println("{}", fitmax);
}

int main() {
    part1();
    part2();
    return 0;
}
