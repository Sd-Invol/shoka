#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
typedef long long LL;

int m1[N], m2[N], m3[N];
LL val[N];
int bo[N], mark[N];

int main() {
    freopen("flights.in", "r", stdin);
    freopen("flights.out", "w", stdout);
    int n, m;
    while (scanf("%d%d", &n, &m), n || m) {
        //printf("!%d %d\n", n, m);
        for (int i = 1; i <= n; ++i) {
            val[i] = 0;
            bo[i] = 0;
        }
        int tot = 0;
        for (int i = 1; i <= m; ++i) {
            int &x = m1[i], &y = m2[i];
            scanf("%d%d", &x, &y);
            if (m1[i] > m2[i]) swap(m1[i], m2[i]);
            if (m1[i] != 1) {
                m3[i] = ++tot;
                val[m1[i]] += tot;
                val[m2[i]] += tot;
            }
            else mark[m2[i]] = i;
        }
        for (int i = 2; i <= n; ++i) {
            int K = -1;
            for (int j = 2; j <= n; ++j)
                if (!bo[j] && (K == -1 || val[K] > val[j]))
                    K = j;
            bo[K] = 1;
            m3[mark[K]] = ++tot;
        }
        puts("Yes");
        for (int i = 1; i <= m; ++i)
            printf("%d%c", m3[i], " \n"[i == m]);
    }
    return 0;
}
