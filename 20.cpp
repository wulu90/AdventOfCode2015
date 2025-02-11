#include <print>

using namespace std;

int factor_sum(int num) {
    int sum = 0;
    for (int i = 1; i * i <= num; ++i) {
        if (num % i == 0) {
            sum += i + num / i;
            if (i * i == num) {
                sum -= i;
            }
        }
    }
    return sum;
}

void part1() {
    const int input = 34000000;
    int i           = 1;
    while (true) {
        if (factor_sum(i) * 10 >= input) {
            break;
        }
        ++i;
    }

    println("{}", i);
}

int presents_sum(int num) {
    int sum = 0;
    for (int i = 1; i * i <= num; ++i) {
        if (num % i == 0) {
            if (i * 50 >= num) {
                sum += i;
            }
            if (i <= 50) {
                sum += num / i;
            }

            if (i * i == num) {
                sum -= i;
            }
        }
    }
    return sum;
}

void part2() {
    const int input = 34000000;
    int i           = 1;
    while (true) {
        if (presents_sum(i) * 11 >= input) {
            break;
        }
        ++i;
    }

    println("{}", i);
}

int main() {
    part1();
    part2();
    return 0;
}
