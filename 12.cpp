#include <fstream>
#include <print>

#include <boost/json.hpp>

using namespace std;

void part1() {
    ifstream input("input/input12");

    int postive = 1;
    int sum     = 0;
    for (char c; input; c = input.get()) {
        if (isdigit(c) || c == '-') {
            if (c == '-') {
                c       = input.get();
                postive = -1;
            } else {
                postive = 1;
            }

            int n = 0;
            while (isdigit(c)) {
                n = n * 10 + c - '0';
                c = input.get();
            }

            sum += n * postive;
        }
    }

    println("{}", sum);
}

int sum_except_red(const boost::json::value& val) {
    int sum = 0;
    if (val.is_int64()) {
        sum += val.as_int64();
    } else if (val.is_array()) {
        for (auto& arr : val.as_array()) {
            sum += sum_except_red(arr);
        }
    } else if (val.is_object()) {
        bool red_property = false;
        for (auto& [k, v] : val.as_object()) {
            if (v.is_string() && v.as_string() == "red"s) {
                red_property = true;
                break;
            }
        }

        if (red_property) {
            return 0;
        } else {
            for (auto& [k, v] : val.as_object()) {
                sum += sum_except_red(v);
            }
        }
    }
    return sum;
}

void part2() {
    ifstream input("input/input12");

    boost::json::value val = boost::json::parse(input);
    println("{}", sum_except_red(val));
}

int main() {
    part1();
    part2();
    return 0;
}
