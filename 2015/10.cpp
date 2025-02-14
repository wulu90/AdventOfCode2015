#include <print>
#include <string>
#include <vector>

using namespace std;

void part(int times) {
    string input{"1113122113"};
    char prev = input[0];

    vector<int> vec;

    for (size_t i = 0; i < input.size(); ++i) {
        vec.push_back(input[i] - '0');
    }

    for (int i = 0; i < times; ++i) {
        vector<int> tmp;
        int prevnum  = vec[0];
        int numcount = 1;
        for (size_t j = 1; j < vec.size(); ++j) {
            if (vec[j] == prevnum) {
                ++numcount;
            } else {
                tmp.push_back(numcount);
                tmp.push_back(prevnum);
                numcount = 1;
                prevnum  = vec[j];
            }
        }

        if (vec.back() == prevnum) {
            tmp.push_back(numcount);
            tmp.push_back(prevnum);
        } else {
            tmp.push_back(1);
            tmp.push_back(vec.back());
        }

        vec = std::move(tmp);
    }

    println("{}", vec.size());
}

int main(int argc, char* argv[]) {
    part(40);
    part(50);
    return 0;
}
