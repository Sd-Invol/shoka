#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const int N = 1e6 + 5;

int a[200], b[200], n;

bool pre[101][1000001];
int f[2][N];
bool ans[200];

int check(int a[], int b[]) {
    int cur = 0, nex = 1;
    memset(f[0], -1, sizeof(f[0]));
    memset(pre[0], false, sizeof(pre[0]));
    f[cur][0] = 0;
    for (int i = 1; i <= n; ++i) {
        memset(f[nex], -1, sizeof(f[nex]));
        memset(pre[i], false, sizeof(pre[i]));
        for (int j = 0; j < a[0]; ++j) {
            if (f[cur][j] == -1) continue;
            if (f[nex][j] < f[cur][j]) {
                pre[i][j] = false;
                f[nex][j] = f[cur][j];
            }
            if (j + a[i] < a[0] && f[nex][j + a[i]] < f[cur][j] + b[i]) {
                pre[i][j + a[i]] = true;
                f[nex][j + a[i]] = f[cur][j] + b[i];
            }
        }
        swap(cur, nex);
    }
    for (int i = 0; i < a[0]; ++i)
        if (f[cur][i] >= b[0]) {
            memset(ans, false, sizeof(ans));
            int I = n, J = i;
            while (I > 0) {
                if (pre[I][J]) {
                    ans[I] = true;
                    J -= a[I];
                }
                --I;
            }
            puts("NO");
            for (int j = 1; j <= n; ++j)
                if (ans[j]) putchar('1');
                else putchar('0');
            puts("");
            return 0;
        }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i <= n; ++i)
        scanf("%d", &b[i]);
    if (check(a, b)) {
        if (check(b, a)) {
            puts("YES");
        }
    }
    return 0;
}

/*

  3
  8 4 5 6
  2 1 1 1

  3
  6 4 5 6
  2 1 1 1
 */
