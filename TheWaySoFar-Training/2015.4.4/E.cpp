#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int p[N], bo[N], a[N];

void work() {
    int n, flag = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        p[x] = i;
        if (i != x) flag = 1;
        bo[i] = 0;
    }
    if (!flag) {
        puts("0");
        //for (int i = 1; i <= n; ++i)
        //    printf("%d%c", i, " \n"[i == n]);
        return ;
    }
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    flag = 0;
    for (int i = 1; i <= n; ++i)
        if (!bo[i]) {
            static int b[N];
            int m = 1, j = i;
            b[1] = i;
            j = p[i];
            bo[i] = 1;
            while (j != i) {
                bo[j] = 1;
                b[++m] = j;
                j = p[j];
            }
            for (int j = 2; j < m - j + 2; ++j) {
                swap(a[b[j]], a[b[m - j + 2]]);
                swap(p[b[j]], p[b[m - j + 2]]);
                flag = 1;
            }
        }
    if (flag) {
        puts("2");
        for (int i = 1; i <= n; ++i)
            printf("%d%c", a[i], " \n"[i == n]);
    }
    else puts("1");
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    for (int i = 1; i <= n; ++i)
        if (p[i] != i) {
            swap(a[i], a[p[i]]);
            swap(p[p[i]], p[i]);
        }
    for (int i = 1; i <= n; ++i)
        printf("%d%c", a[i], " \n"[i == n]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) work();
    return 0;
}
