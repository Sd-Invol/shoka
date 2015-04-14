#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1 << 18;

int first[N], tot;

struct Edge {
    int y, s, nex;
}edge[N * 20];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, 1, first[x]};
    first[x] = tot++;
}

int a[N * 20], m;

void dfs(int x) {
    for (int &k = first[x]; ~k; k = edge[k].nex) {
        if (edge[k].s) {
            int y = edge[k].y;
            --edge[k].s;
            dfs(y);
        }
        k = first[x];
    }
    a[m++] = x; 
}

int mark[1 << 19];

int main() {
    int n;
    scanf("%d", &n);
    memset(first, -1, sizeof(first));
    tot = 0;
    for (int i = 0; i < n; ++i)
        mark[1 << i] = i;
    for (int mask = 0; mask < 1 << n; ++mask)
        for (int i = 0; i < n; ++i)
            addedge(mask, mask ^ (1 << i));
    dfs(0);
    reverse(a, a + m);
    printf("%d\n", (1 << n) * n);
    for (int i = 1; i < m; ++i) {
        int x = a[i] ^ a[i - 1];
        int p = mark[x] + 1;
        printf("%d%c", p, " \n"[i == m - 1]);
    }
    return 0;
}
