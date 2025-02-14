#include <fstream>
#include <map>
#include <print>
#include <set>
#include <string>

using namespace std;

pair<string, string> parse(const string& str) {
    auto space1 = str.find(' ');
    auto space2 = str.rfind(' ');
    return {{str.begin(), str.begin() + space1}, {str.begin() + space2 + 1, str.end()}};
}

void part1() {
    ifstream input("input/input19");

    multimap<string, string> replacements;

    string line;
    while (getline(input, line) && !line.empty()) {
        replacements.insert(parse(line));
    }
    getline(input, line);

    set<string> molecules;
    for (auto& [k, v] : replacements) {
        size_t pos = 0;
        while ((pos = line.find(k, pos)) != string::npos) {
            auto tmp = line;
            tmp.replace(pos, k.size(), v);
            molecules.insert(tmp);
            pos += k.size();
        }
    }

    println("{}", molecules.size());
}

int main() {
    part1();
    return 0;
}
