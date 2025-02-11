#include <fstream>
#include <print>
#include <vector>

using namespace std;

void combination_sum(size_t inx, int curr_sum, vector<size_t> curr, vector<vector<size_t>>& combinatio_vec, int target,
                     const vector<int>& vec) {
    if (curr_sum == target) {
        combinatio_vec.push_back(curr);
        return;
    }

    for (size_t i = inx; i < vec.size(); ++i) {
        if (curr_sum + vec[i] > target) {
            continue;
        }
        curr.push_back(i);
        combination_sum(i + 1, curr_sum + vec[i], curr, combinatio_vec, target, vec);
        curr.pop_back();
    }
}

void part1() {
    ifstream input("input/input17");
    vector<int> vec;
    for (int i; input >> i;) {
        vec.push_back(i);
    }

    vector<vector<size_t>> combinatio_vec;
    combination_sum(0, 0, {}, combinatio_vec, 150, vec);

    println("{}", combinatio_vec.size());
}

int main() {
    part1();
    return 0;
}
