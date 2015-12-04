#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#include <string>
#include <queue>
using namespace std;

const int N = 5e3 + 5;

pair<int, int> pos[N];
pair<int, int> ini[N];

int val[N];

const int C[4] = {0, 1, 0, -1};
const int D[4] = {1, 0, -1, 0};
int edge[N][4];

struct Pos {
    pair<int, int> p;
    int id;

    int operator < (const Pos &a) const {
        return p < a.p;
    }
}T[N];

int solve(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            edge[i][j] = -1;
        }
        int t = upper_bound(pos, pos + n, pos[i]) - pos;
        if (t < n && pos[t].first == pos[i].first) edge[i][0] = t;
        t = lower_bound(pos, pos + n, pos[i]) - pos - 1;
        if (t < n && t >= 0 && pos[t].first == pos[i].first)
            edge[i][2] = t;
    }
    for (int i = 0; i < n; ++i) {
        T[i] = (Pos){make_pair(pos[i].second, pos[i].first), i};
    }
    sort(T, T + n);
    for (int i = 0; i < n; ++i) {
        int t = upper_bound(T, T + n, T[i]) - T;
        if (t < n && T[t].p.first == T[i].p.first) edge[T[i].id][1] = T[t].id;
        t = lower_bound(T, T + n, T[i]) - T - 1;
        if (t < n && t >= 0 && T[t].p.first == T[i].p.first)
            edge[T[i].id][3] = T[t].id;
    }
    static int bo[N][4];
    memset(bo, -1, sizeof(bo));
    int S;
    //for (int i = 0; i < n; ++i) {
    //    printf("%d %d\n", pos[i].first, pos[i].second);
    //    for (int j = 0; j < 4; ++j)
    //        printf("%d ", edge[i][j]);
    //    puts("");
    // }
    for (int i = 0; i < n; ++i)
        if (pos[i] == make_pair(0, 0)) S = i;
    for (int i = 1; i <= 1; ++i) {
        int x = S, y = i;
        if (bo[x][y] != -1) continue;
        bo[x][y] = 0;
        //puts("----");
        int res = 0;
        while (1) {
            // printf("%d %d %d %d %d\n", pos[x].first, pos[x].second, y, pos[edge[x][y]].first, pos[edge[x][y]].second);
            int t = edge[x][y];
            if (t == -1) return res;
            if (val[t]) {
                y = (y + 1) % 4;
                ++res;
            } else x = t;
            if (bo[x][y] != -1) break;
            bo[x][y] = 1;
        }
    }
    return -1;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int r = 0;
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            for (int j = 0; j < 4; ++j) {
                pos[r++] = make_pair(x + C[j], y + D[j]);
            }
            ini[i] = make_pair(x, y);
            pos[r++] = make_pair(x, y);
        }
        pos[r++] = make_pair(0, 0);
        sort(ini, ini + n);
        n = unique(ini, ini + n) - ini;
        sort(pos, pos + r);
        r = unique(pos, pos + r) - pos;
        for (int i = 0; i < r; ++i) {
            int t = lower_bound(ini, ini + n, pos[i]) - ini;
            if (t < n && pos[i] == ini[t]) val[i] = 1;
            else val[i] = 0;
        }
        printf("%d\n", solve(r));
    }
    return 0;
}