#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int M = 10005;
int ca , n;
int a[N][N] , s[N], Point[N], T[N];
int f[2][N] , S[M];

void work() {
    int i , j , k;
    memset(S , 0 , sizeof(S));
    for (i = 1; i <= n; i ++) {
        scanf("%d", s + i);
        for (int j = 1; j <= s[i]; j ++) {
            scanf("%d", &a[i][j]);
            S[a[i][j]] = 1;
        }
        s[i] = unique(a[i] + 1, a[i] + s[i] + 1) - a[i] - 1;
        Point[i] = 1;
    }
    for (int i = 1; i < M; i ++)
        S[i] += S[i - 1];
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= s[i]; j ++)
            a[i][j] = S[a[i][j]];

    printf("Case %d: ", ++ ca);
    for (int i = 0; i <= n; i ++)
        f[0][i] = 0;
    for (int i = 1; i <= S[M - 1]; i ++) {
        T[0] = 0;
        f[1][0] = 0x7f7f7f7f;
        for (int j = 1; j <= n; j ++) {
            if (a[j][Point[j]] == i)
                T[++ T[0]] = j, Point[j] ++;
            f[1][j] = 0x7f7f7f7f;
        }
        for (int j = 1; j <= T[0]; j ++) {
            for (int k = 1; k <= T[0]; k ++) {
                if (j == k && T[0] > 1)
                    continue;
                f[1][T[k]] = min(f[1][T[k]], f[0][T[j]] + T[0] - 1);
            }
            for (int k = 0; k <= n; k ++)
                f[1][T[j]] = min(f[1][T[j]], f[0][k] + T[0]);
        }
        for (int j = 0; j <= n; j ++)
            f[0][j] = f[1][j];
    }
    int res = 0x7f7f7f7f;
    for (int i = 0; i <= n; i ++)
        res = min(res, f[0][i]);
    printf("%d\n", res * 2 - n + 1);
}

int main() {
    while (~scanf("%d" , &n))
        work();
    return 0;
}
