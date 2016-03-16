#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long LL;

const int P = 1e9 + 9;

int power(int a, LL n) {
    int ans = 1, z = a;
    while (n > 0) {
        if (n & 1) ans = (LL)ans *z % P;
        n >>= 1;
        z = (LL)z * z % P;
    }
    return ans;
}

int solve(LL n, int num) {
    int ans = 0;
    for (int i = 0; i <= num && i <= 1 ; ++i) {
        int res = power(num - i + 1, n);
        if (i & 1) ans = (ans - res + P) % P;
        else ans = (ans + res) % P;
    }
    return ans;
}

int main() {
    LL k;
    LL d, m;
    scanf("%lld%lld%lld", &k, &d, &m);
    if (m % d != 0) {
        puts("0");
    }
    else {
        m /= d;
        int ans = 1;
        for (int i = 2; i <= 100000; ++i) {
            int num = 0;
            while (m % i == 0){
                m /= i;
                ++num;
            }
            if (num != 0)
                ans = (LL)ans * (solve(k, num) - solve(k, num - 1) + P) % P;
        }
        if (m > 1) ans = (LL)ans * (solve(k, 1) - solve(k , 0) + P) % P;
        cout << ans << endl;
    }
}
