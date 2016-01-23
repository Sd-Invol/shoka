#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
const int N = 1005;

int main() {
    long long n , m;
    int T;
    cin >> T;
    while (T --) {
        cin >> n; m = n;
        bool flag = 0;
        for (int i = 2 ; i <= m ; ++ i) {
            if (n % i == 0) {
                puts("-1");
                flag = 1;
                break;
            }
            n -= n / i;
            m -= m / i;
        }
        if (!flag)
            cout << n << endl;
    }
    return 0;
}
