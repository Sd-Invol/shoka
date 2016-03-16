#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int N = 2005;
const int C[4] = {1, -1, 0, 0};
const int D[4] = {0, 0, 1, -1};

int n, m;
int grid[N][N], dis[N][N];
int M[N][N], nex1[N][N], nex2[N][N];
vector<pair<int, int> > ver;

int solve(int x, int y, int dx, int dy) {
    int res = 0;
    if (M[x][y]) dis[x][y] = 0;
    while (grid[x + 1][y] + grid[x][y + 1] > 0) {
        if (grid[x + dx][y + dy] == 0) {
            swap(dx, dy);
            ++res;
            continue;
        }
        while (grid[x + dx][y + dy] == 1) {
            x += dx;
            y += dy;
            if (M[x][y]) dis[x][y] = min(res, dis[x][y]);
            if (grid[x + dx][y + dy] > 0) {
                if (dy == 1) {
                    int xx = nex1[x][y]; 
                    while (xx != 0) {
                        dis[xx][y] = min(res + 1, dis[xx][y]);
                        xx = nex1[xx][y];
                    }
                }
                else {
                    int yy = nex2[x][y];
                    while (yy != 0) {
                        dis[x][yy] = min(res + 1, dis[x][yy]);
                        yy = nex2[x][yy];
                    }
                }
            }
        }
    }
}

int check() {
    for (int i = 1; i <= n + 1; ++i) {
        memset(nex1[i], 0, sizeof(int) * (m + 2));
        memset(nex2[i], 0, sizeof(int) * (m + 2));
    }
    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j) {
            if (M[i + 1][j]) nex1[i][j] = i + 1;
            else nex1[i][j] = nex1[i + 1][j];
            if (M[i][j + 1]) nex2[i][j] = j + 1;
            else nex2[i][j] = nex2[i][j + 1];
        }
    int ans = 0;
    for (auto S : ver) {
        int i = S.first, j = S.second;
        for (auto x : ver)
            dis[x.first][x.second] = 1 << 30;
        solve(i, j, 1, 0);
        solve(i, j, 0, 1);
        for (auto x : ver) {
            int tmp = dis[x.first][x.second];
            if (tmp <= 100000)
                ans = max(ans, tmp);
        }
    }
    return ans;
}

int main() {
    freopen("jinxiety.in", "r", stdin);
    freopen("jinxiety.out", "w", stdout);
    while (scanf("%d%d", &n, &m), n || m) {
        for (int i = 0; i <= n + 1; ++i) {
            memset(grid[i], 0, sizeof(int) * (m + 2));
            memset(M[i], 0, sizeof(int) * (m + 2));
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                int ch;
                while (ch = getchar(), ch != '.' && ch != '#');
                grid[i][j] = (ch == '#');
            }
        ver.clear();
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (grid[i][j] == 1) {
                    int flag = 0;
                    for (int k = 0; k < 4; ++k)
                        if (grid[i + C[k]][j + D[k]] == 0) {
                            flag = 1;
                            break;
                        }
                    M[i][j] = flag;
                }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (!M[i][j]) continue;
                if (M[i - 1][j] && M[i + 1][j]) continue;
                if (M[i][j - 1] && M[i][j + 1]) continue;
                //if (M[i - 1][j - 1] && M[i + 1][j + 1]) continue;
                //if (M[i - 1][j + 1] && M[i + 1][j - 1]) continue;
                ver.push_back(make_pair(i, j));
            }
        for (int i = 0; i <= n + 1; ++i)
            memset(M[i], 0, sizeof(int) * (m + 2));
        for (auto S : ver)
            M[S.first][S.second] = 1;
        int ans = 0;
        for (int i = 0; i < 2; ++i) {
            ans = max(ans, check());
            for (int j = 1; j < n - j + 1; ++j)
                for (int k = 1; k <= m; ++k) {
                    int t = n - j + 1;
                    swap(grid[j][k], grid[t][k]);
                    swap(M[j][k], M[t][k]);
                    
                }
            for (int j = 0; j < ver.size(); ++j)
                ver[j].first = n - ver[j].first + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
