#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
using namespace std;

const int N = 1e5 + 100;
int m1[N], m2[N];
int nex[N];
int bo[N], f[N], Next[N];
int size[N];

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

int first[N], tot;

struct Edge {
    int y, nex;
}edge[N];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int n, m;
vector<int> ans;

void print(int x) {
    int L = ans.size();
    int R = L;
    while (x != -1) {
        ans.push_back(x);
        x = Next[x];
        ++R;
    }
    reverse(ans.begin() + L, ans.begin() + R);
}

int dfs(int x, int s) {
    if (s == n) {
        int flag = 0;
        for (int k = first[x]; k != -1; k = edge[k].nex)
            if (edge[k].y == find(1)) {
                flag = 1;
                break;
            }
        if (flag == 0) return 0;
        print(x);
        // printf("!%d\n", x);
        return 1;
    }
    bo[x] = 1;
    for (int k =first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (!bo[y]) {
            if (dfs(y, s + size[find(y)])) {
                print(x);
                //  printf("!%d\n", y);
                return 1;
            }
        }
    }
    bo[x] = 0;
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    //n = 100000;
    //m = 100020;
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        size[i] = 1;
        Next[i] = -1;
    }
    for (int i = 1; i <= m; ++i) {
        int &x = m1[i], &y = m2[i];
        scanf("%d%d", &x, &y);
        f[find(x)] = find(y);
        if (nex[x] == 0) nex[x] = i;
        else nex[x] = -1;
    }
    for (int i = 1; i <= n; ++i)
        if (find(i) != find(1)) {
            puts("There is no route, Karl!");
            return 0;
        }
    for (int i = 1; i <= n; ++i)
        f[i] = i;
    for (int i = 1; i <= n; ++i)
        if (nex[i] > 0) {
            int x = i, y = m2[nex[i]];
            if (find(x) != find(y)) {
                if (find(y) != y) {
                    continue;
                }
                Next[x] = y;
                size[find(x)] += size[find(y)];
                f[find(y)] = find(x);
                bo[nex[i]] = 1;
            }
        }
    memset(nex, 0, sizeof(nex));
    for (int i = 1; i <= m; ++i) {
        int x = m1[i], y = m2[i];
        if (nex[y] == 0) nex[y] = i;
        else nex[y] = -1;
    }
    for (int i = 1; i <= n; ++i)
        if (nex[i] > 0 && bo[nex[i]] == 0) {
            int y = i, x = m2[nex[i]];
            if (find(x) != find(y)) {
                if (find(y) != y) {
                    continue;
                }
                Next[x] = y;
                size[find(x)] += size[find(y)];
                f[find(y)] = find(x);
                bo[nex[i]] = 1;
            }
        }
    memset(first, -1, sizeof(first));
    tot = 0;
    for (int i = 1; i <= m; ++i)
        if (!bo[i]) {
            if (Next[m1[i]] == -1 && find(m2[i]) == m2[i]) {
                addedge(find(m1[i]), find(m2[i]));
            }
        }
    memset(bo, 0, sizeof(bo));
    // cout << size[find(1)] << endl;
    if (!dfs(find(1), size[find(1)])) {
        puts("There is no route, Karl!");
    }
    else {
        reverse(ans.begin(), ans.end());
        int flag = 0;
        for (int i = 0; i < ans.size(); ++i)
            if (ans[i] == 1) {
                flag = i;
            }
        for (int i = 0; i <= n; ++i)
            printf("%d%c", ans[(i + flag) % n], " \n"[i == n]);
    }
    return 0;
}
