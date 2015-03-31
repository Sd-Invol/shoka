#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int N = 1e3 + 5;
int bo[N];
int ansa[N], ansb[N];

void solve(int n) {
    if (n == 2) {
        ansa[1] = 2; ansa[2] = 3;
        ansb[1] = 1; ansb[2] = 4;
        return ;
    }
    solve(n >> 1);
    int m = n / 2;
    for (int i = m + 1; i <= n; ++i) {
        ansa[i] = ansb[i - m] + n;
        ansb[i] = ansa[i - m] + n;
    }
}

int main() {
    freopen("analogous.in", "r", stdin);
    freopen("analogous.out", "w", stdout);
    int n;
    for (int i = 1; 1 << i < N; ++i)
        bo[1 << i] = 1;
    while (scanf("%d", &n), n) {
        if (!bo[n]) puts("No");
        else {
            puts("Yes");
            solve(n);
            for (int i = 1; i <= n; ++i)
                printf("%d%c", ansa[i], " \n"[i == n]);
            for (int i = 1; i <= n; ++i)
                printf("%d%c", ansb[i], " \n"[i == n]);
        }
    }
    return 0;
}
