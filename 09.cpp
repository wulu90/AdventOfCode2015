#include <algorithm>
#include <fstream>
#include <map>
#include <print>
#include <set>
#include <string>
#include <vector>

using namespace std;

tuple<string, string, int> parse(const string& str) {
    auto space1 = str.find(' ');
    auto space2 = str.find(' ', space1 + 1);
    auto space3 = str.find(' ', space2 + 1);
    auto space4 = str.find(' ', space3 + 1);
    int dist    = 0;
    from_chars(str.data() + space4 + 1, str.data() + str.size(), dist);
    return {{str.data(), str.data() + space1}, {str.data() + space2 + 1, str.data() + space3}, dist};
}

void part() {
    ifstream input("input/input09");
    map<pair<string, string>, int> citymap;
    set<string> cityset;
    for (string line; getline(input, line);) {
        auto [s1, s2, n] = parse(line);
        citymap.insert({{s1, s2}, n});
        citymap.insert({{s2, s1}, n});
        cityset.insert(s1);
        cityset.insert(s2);
    }

    vector<string> city_vec;
    for (auto& s : cityset) {
        city_vec.push_back(s);
    }

    int min_dist = INT32_MAX;
    int max_dist = 0;
    while (next_permutation(city_vec.begin(), city_vec.end())) {
        int dist   = 0;
        bool valid = true;
        for (size_t i = 0; i < city_vec.size() - 1; ++i) {
            if (citymap.contains({city_vec[i], city_vec[i + 1]})) {
                dist += citymap[{city_vec[i], city_vec[i + 1]}];
            } else {
                valid = false;
                break;
            }
        }
        if (valid) {
            min_dist = min(min_dist, dist);
            max_dist = max(max_dist, dist);
        }
    }

    println("{}", min_dist);
    println("{}", max_dist);
}

int main(int argc, char* argv[]) {
    part();
    return 0;
}
