#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cmath> 
using namespace std;
const int N = 1e5 + 5;
typedef long long LL;
const int P = 1e9 + 7;

int L, n, K;
int x[N];
int len[N];
LL a[N];
double pre[N], suf[N];

int check(double x) {
    LL num = 0;
    for (int i = 1; i <= n; ++i) {
        a[i] = 0;
        if (len[i] <= x) continue;
        LL m = ceil((len[i] - x) / x);
        if (m + num > K + 1) return 0;
        a[i] = m;
        num += m;
    }
    pre[0] = 0;
    for (int i = 1; i <= n; ++i)
        pre[i] = max(pre[i - 1], (double)len[i] / (a[i] + 1));
    suf[n + 1] = 0;
    for (int i = n; i >= 1; --i)
        suf[i] = max(suf[i + 1], (double)len[i] / (a[i] + 1));
    if (num <= K) return 1;
    if (num > K + 1) return 0;
    for (int i = 1; i <= n; ++i)
        if (a[i] == 1) {
            double mx = max(pre[i - 1], suf[i + 1]);
            if (len[i] + mx <= 2 * x) return 1;
        }
    return 0;
}

int main() {
    scanf("%d%d%d", &L, &n, &K);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x[i]);
    }
    x[n] = L;
    for (int i = 1; i <= n; ++i)
        len[i] = x[i] - x[i - 1];
    double head = 0, tail = L;
    for (int i = 1; i <= 100; ++i) {
        double mid = (head + tail) / 2;
        if (check(mid)) tail = mid;
        else head = mid;
    }
    printf("%.15f\n", head);
    return 0;
}

