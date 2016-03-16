#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 2e5 + 5;

int degree[N];
int first[N], tot;

struct Edge {
    int y, nex;    
}edge[N * 20];

void addedge(int x, int y) {
    // printf("%d %d\n", x, y);
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
    ++degree[y];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    tot = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y, ch1, ch2;
        while (ch1 = getchar(), ch1 != '+' && ch1 != '-');
        scanf("%d", &x);
        while (ch2 = getchar(), ch2 != '-' && ch2 != '+');
        scanf("%d", &y);
        if (ch1 == '-') x += n;
        if (ch2 == '+') y += n;
        addedge(x, y);
        if (x > n) x -= n;
        else x += n;
        if (y > n) y -= n;
        else y += n;
        addedge(y, x);
    }
    queue<int> que;
    for (int i = 1; i <= 2 * n; ++i)
        if (degree[i] == 0) {
            que.push(i);
        }
    int sum = 0;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        ++sum;
        for (int k = first[x]; k != -1; k = edge[k].nex) {
            int y = edge[k].y;
            if (--degree[y] == 0) {
                que.push(y);
            }
        }
    }
    if (sum == 2 * n) puts("TAK");
    else puts("NIE");
    return 0;
}
