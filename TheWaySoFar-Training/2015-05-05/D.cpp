#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

const int N = 1e5 + 5;

char f[2][N], g[2][N], p[N], tmp[N * 2];
char ff[N], gg[N];
ULL num[105];
int next[N];

ULL gett(char *p, char *a) {
    int m = strlen(p), n = strlen(a);
    ULL ans = 0;
    //printf("!%d\n", m);
    for (int i = 0, j = -1; i < n; ++i) {
        while (j != -1 && p[j + 1] != a[i]) j = next[j];
        if (p[j + 1] == a[i]) ++j;
        if (j == m - 1) {
            ++ans;
            j = next[j];
        }
    }
    return ans;
}

void solve(char *a, char *b, char *c, int len, int flag) {
    static char p[N * 2];
    int n0 = strlen(a), n1 = strlen(b);
    int n = 0;
    for (int i = 0; i < n0; ++i) p[n++] = a[i];
    for (int i = 0; i < n1; ++i) p[n++] = b[i];
    p[n] = 0;
    if (len >= n) {
        for (int i = 0; i <= n; ++i)
            c[i] = p[i];
        return ;
    }
    if (flag == 0) {
        for (int i = 0; i < len; ++i) c[i] = p[i];
    }
    else {
        for (int i = 1; i <= len; ++i)
            c[len - i] = p[n - i];
    }
    c[len] = 0;
}

int main() {
    int n, ca = 0;
    while (scanf("%d", &n) == 1) {
        scanf("%s", p);
        int m = strlen(p);
        printf("Case %d: ", ++ca);
        if (n < 2) {
            if (m != 1) puts("0");
            else {
                if (n == 0 && p[0] == '0') puts("1");
                else if (n == 1 && p[0] == '1') puts("1");
                else puts("0");
            }
            continue;
        }
        for (int i = 0; i < m; ++i) next[i] = -1;
        for (int i = 1; i < m; ++i) {
            int j = next[i - 1];
            while (j != -1 && p[j + 1] != p[i]) j = next[j];
            if (p[j + 1] == p[i]) next[i] = j + 1;
        }
        memset(num, 0, sizeof(num));
        f[0][0] = '0'; f[0][1] = '\0';
        g[0][0] = '0'; g[0][1] = '\0';
        f[1][0] = '1'; f[1][1] = '\0';
        g[1][0] = '1'; g[1][1] = '\0';
        num[0] = gett(p, f[0]);
        num[1] = gett(p, f[1]);
        if (m == 1) {
            g[0][0] = f[0][0] = g[1][0] = f[1][0] = 0;
        }
        for (int i = 2; i <= n; ++i) {
            num[i] = num[i - 1] + num[i - 2];
            solve(g[1], f[0], tmp, m * 2, 0);
            num[i] += gett(p, tmp);
            //printf("%d %llu\n", i, num[0]);
            solve(f[1], f[0], ff, m - 1, 0);
            solve(g[1], g[0], gg, m - 1, 1);
            memcpy(f[0], f[1], sizeof(f[0]));
            memcpy(g[0], g[1], sizeof(g[0]));
            memcpy(f[1], ff, sizeof(ff));
            memcpy(g[1], gg, sizeof(gg));
        }
        printf("%llu\n", num[n]);
    }
    return 0;
}
