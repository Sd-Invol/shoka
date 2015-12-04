#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <queue>
using namespace std;

int grid[55][55], key[55][55];
const int C[4] = {1, -1, 0, 0};
const int D[4] = {0, 0, 1, -1};

int gett(int ch) {
    if (ch == '#') return 0;
    if (ch == '_') return 1;
    if (ch == '^') return 2;
    if (ch == '|') return 3;
    if (islower(ch)) return 100 + ch - 'a';
    if (isupper(ch)) return 200 + ch - 'A';
    if (ch == '%') return 10000;
    if (ch == '&') return 20000;
    return -1;
}

int MP[10][55][55];
int bo[55][55][3][1 << 10];

struct Pos {
    int x, y, floor, mask;
};

void updata(int x, int y, int floor, int mask, int t, queue<Pos> &que) {
    if (bo[x][y][floor][mask] > 0) return ;
    bo[x][y][floor][mask] = t;
    que.push((Pos){x, y, floor, mask});
}

int main() {
    int n, m;
    scanf("%d%d", &m, &n);
    memset(key, -1, sizeof(key));
    pair<int, int> S, T;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int ch;
            while (ch = getchar(), gett(ch) == -1);
            int t = gett(ch);
            if (t < 10) {
                grid[i][j] = t;
            }
            else if (t <= 1000) {
                grid[i][j] = t / 100;
                key[i][j] = t % 100;
            }
            else if (t == 10000) {
                S = make_pair(i, j);
                grid[i][j] = 1;
            }
            else if (t == 20000) {
                T  = make_pair(i, j);
                grid[i][j] = 1;
            }
        }
    int r;
    scanf("%d", &r);
    for (int t = 0; t < r; ++t) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                int ch;
                while (ch = getchar(), ch != '*' && ch != '|' &&
                    ch != '.' && ch != '#');
                if (ch == '*') MP[t][i][j] = 1;
            }
    }
    bo[S.first][S.second][1][0] = 1;
    queue<Pos> que;
    que.push((Pos){S.first, S.second, 1, 0});
    while (!que.empty()) {
        int x = que.front().x, y = que.front().y, mask = que.front().mask;
        int floor = que.front().floor;
        que.pop();
        if (grid[x][y] == 3) {
            updata(x, y, 3 - floor, mask, bo[x][y][floor][mask] + 1, que);
        }
        if (key[x][y] != -1) {
            int floor1 = floor;
            if (MP[key[x][y]][x][y] == 1)
                floor1 = 3 - floor1;
            updata(x, y, floor1, mask ^ (1 << key[x][y]), bo[x][y][floor][mask] + 1, que);
        }
        for (int k = 0; k < 4; ++k) {
            int xx = x + C[k], yy = y + D[k];
            if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
            int T = 0;
            for (int j = 0; j < r; ++j)
                if (mask >> j & 1) T ^= MP[j][xx][yy];
            int opt = grid[xx][yy];
            if ((opt == 1 || opt == 2) && T == 1)
                opt = 3 - opt;
            if ((opt & floor) != 0) updata(xx, yy, floor, mask, bo[x][y][floor][mask] + 1, que);
        }
    }
    int ans = 1 << 30;
    for (int mask = 0; mask < 1 << r; ++mask) {
        int x = bo[T.first][T.second][1][mask];
        if (x != 0)
            ans = min(x - 1, ans);
        x = bo[T.first][T.second][2][mask];
        if (x != 0)
            ans = min(x - 1, ans);
    }
    if (ans >= (1 << 29)) ans = -1;
    printf("%d\n", ans);
    return 0;
}