#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

int L, N, K;

int check(LL x) {
    if (x == 0) return 1;
    int n = L;
    while (n > 0) {
        LL t = 0;
        if (x == 1) t = 1;
        else {
            t = (x - 1 + K - 3) / (K - 2);
        }
        //printf("%lld %lld\n", x, t);
        LL y = (LL)(t) * (K - 2) + 2;
        LL len = (y - x + t * 2 - 2) / (t * 2 - 1);
        len = min(len, (LL)n);
        x += len * (t * 2 - 1);
        n -= len;
        if (x > N) return  0;
    }
    return 1;
}

int main() {
    scanf("%d%d%d", &L, &N, &K);
    if (K < 2) puts("0");
    else if (K == 2) {
        if (L == 1)puts("1");
        else puts("0");
    }
    else {
        int head = 0, tail = N;
        while (head + 1 < tail) {
            int mid = (head + tail) >> 1;
            if (check(mid)) head = mid;
            else tail = mid;
        }
        cout << head << endl;
    }
}
