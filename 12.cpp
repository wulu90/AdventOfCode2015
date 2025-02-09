#include <fstream>
#include <print>

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

int main() {
    part1();
    return 0;
}
