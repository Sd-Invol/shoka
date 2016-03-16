#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long n , s = 0;
    cin >> n;
    while (n > 1) {
        if (n % 2 == 0) {
            s += n;
            n /= 2;
        } else {
            s += n + 1;
            n = (n + 1) / 2 * 3 - 1;
        }
    }
    cout << s << endl;
}
