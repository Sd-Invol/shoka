#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef unsigned long long ULL;

int n;
ULL K;
int str[100];

ULL dp[100];

ULL check(int x) {
    for (int m = 1; m <= n; ++m) {
        dp[m] = 1ULL << max(0, m - x);
        for (int i = 1; i * 2 <= m; ++i) {
            int flag = 1;
            for (int j = 1; j <= i && flag; ++j)
                if (m - i + j <= x && str[j] != str[m - i + j]) {
                    flag = 0;
                }
            
            if (flag == 0) continue;
            ULL res = 1;
            for (int j = i + 1; j <= m - i; ++j)
                if (j > x) res <<= 1;
            dp[m] -= res * dp[i];
            //if (x == 5 && m == 5) printf("%d %llu\n", i, res);
        }
    }
    //if (x == 5)
    //    for (int i = 1; i <= n; ++i)
    //        printf("%d %llu\n", i, dp[i]);
    return dp[n];
}

void dfs(int x) {
    if (x > n) {
        for (int i = 1; i <= n; ++i)
            if (str[i] == 0) putchar('a');
            else putchar('b');
        puts("");
        return ;
    }
    str[x] = 0;
    ULL res = check(x);
    if (res >= K) {
        dfs(x + 1);
        return;
    }
    K -= res;
    str[x] = 1;
    //if (x == 5) {
    //    cout << check(x) << endl;
    // }
    dfs(x + 1);
}

int main() {
    freopen("borderless.in", "r", stdin);
    freopen("borderless.out", "w", stdout);
    while (scanf("%d%llu", &n, &K), n) {
        dfs(1);
    }
    return 0;
}
