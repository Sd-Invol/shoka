#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int C[4] = {1, -1, 0, 0};
const int D[4] = {0, 0, 1, -1};

struct Point {
    int x, y, ti;

    int operator == (const Point &a) const {
        return make_pair(x, y) == make_pair(a.x, a.y);
    }
}P[3];

typedef long long LL;

int bo[10][10];
int n, m;
LL ans;
int f[70];

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

int check(int xL, int xR, int yL, int yR) {
    xL = max(xL, 0);
    xR = min(xR, n - 1);
    yL = max(yL, 0);
    yR = min(yR, m - 1);
    int cnt = 0, p = 0;
    int dis[3][3];
    memset(dis, 0, sizeof(dis));
    for (int i = xL; i <= xR; ++i)
        for (int j = yL; j <= yR; ++j) {
            if (!bo[i][j]) {
                ++p;
                if (cnt) continue;
                queue<int> que;
                que.push(i * m + j);
                dis[i - xL][j - yL] = 1;
                while (!que.empty()) {
                    int x = que.front() / m, y = que.front() % m;
                    que.pop();
                    ++cnt;
                    for (int k = 0; k < 4; ++k) {
                        int xx = x + C[k], yy = y + D[k];
                        if (xx < xL || yy < yL || xx > xR || yy > yR)
                            continue;
                        if (bo[xx][yy]) continue;
                        if (dis[xx - xL][yy - yL] != 0) continue;
                        dis[xx - xL][yy - yL] = 1;
                        que.push(xx * m + yy);
                    }
                }
            }
        }
    if (p != cnt) return 1;
    return 0;
}

int pd(int x, int y, int t) {
    static int dis[64];
    /*memset(dis, 0, sizeof(dis));
    dis[x * m + y] = t;
    queue<int> que;
    que.push(x * m + y);
    while (!que.empty()) {
        int x = que.front() / m, y = que.front() % m;
        que.pop();
        for (int k = 0; k < 4; ++k) {
            int xx = x + C[k], yy = y + D[k];
            if (xx < 0 || yy < 0 || xx >= n || yy >= m)
                continue;
            if (bo[xx][yy]) continue;
            if (dis[xx * m + yy] != 0) continue;
            dis[xx * m + yy] = dis[x * m + y] + 1;
            que.push(xx * m + yy);
        }
        }*/
    for (int i = 0; i < 3; ++i)
        if (!bo[P[i].x][P[i].y]) {
            int tmp = t + abs(P[i].x - x) + abs(P[i].y - y);
            if (tmp > P[i].ti) return 1; 
        }
    return check(x - 1, x + 1, y - 1, y + 1);
    return 0;
}

void dfs(int x, int y, int t, int K) {
    Point q = (Point) {x, y, 0};
    for (int i = 0; i < 3; ++i) {
        if (q == P[i]) {
            if (t != P[i].ti) return ;
        }
        else {
            if (t == P[i].ti) return ;
        }
    }
    if (pd(x, y, t)) return ;
    if (t == m * n) {
        if (x == 0 && y == 1) ++ans;
        return ;
    }
    for (int k = 0; k < 4; ++k) {
        int xx = x + C[k], yy = y + D[k];
        if (xx < 0 || yy < 0 || xx >= n || yy >= m) continue;
        if (bo[xx][yy]) continue;
        bo[xx][yy] = 1;
        dfs(xx, yy, t + 1, k);
        bo[xx][yy] = 0;
    }
}

int main() {
    while (scanf("%d%d", &n, &m), n || m) {
        memset(bo, 0, sizeof(bo));
        for (int i = 0; i < 3; ++i) {
            scanf("%d%d", &P[i].x, &P[i].y);
            P[i].ti = (i + 1) * n * m / 4;
        }
        ans = 0;
        memset(bo, 0, sizeof(bo));
        bo[0][0] = 1;
        dfs(0, 0, 1, 0);
        static int ca = 0;
        printf("Case %d: %lld\n", ++ca, ans);
    }
    return 0;
}
