#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ifstream input("input/input01");
    string str;
    input >> str;
    int res = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '(') {
            ++res;
        } else {
            --res;
        }
        if (res == -1) {
            cout << i + 1 << endl;
        }
    }
    cout << res << endl;
    return 0;
}
