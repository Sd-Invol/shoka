#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6 + 5;

int bo[N];
typedef long long LL;

int main() {
    LL n, a, b;
    scanf("%lld%lld%lld", &a, &b, &n);
    if (n >= a + b) {
        puts("YES");
        return 0;
    }
    for (int i = 2; i < N; ++i)
        if (!bo[i]) {
            for (int j = i * 2; j < N; j += i)
                bo[j] = 1;
            LL num = 0;
            for (LL x = n; x > 0; x /= i)
                num += x / i;
            for (LL x = a; x > 0; x /= i)
                num -= x / i;
            for (LL x = b; x > 0; x /= i)
                num -= x / i;
            if (num != 0) {
                puts("NO");
            }
        }
    return 0;
}
