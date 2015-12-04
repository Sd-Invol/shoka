#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <cmath> 
using namespace std;

const int N = 1e4 + 5;
typedef long long LL;

struct Point {
    int x, y;

    void input() {
        scanf("%d%d", &x, &y);
    }

    LL det(const Point &a) const {
        return (LL)x * a.y - (LL)y * a.x;
    }

    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y};
    }
    
    LL operator * (const Point &a) const {
        return (LL)x * a.x + (LL)y * a.y; 
    }

    double len() {
        return sqrt((*this) * (*this));
    }
}P[N], Q[N], T[N];

int color[N];
Point S;

int cmp(Point a, Point b) {
    if ((a - S).det((b - S)) != 0) return (a - S).det((b - S)) < 0;
    return (a - S) * (a - S) < (b - S) * (b - S);
}

double f[44][1 << 6];
int opt[44][44];

int main() {
    int n, m, K;
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 1; i <= n; ++i) {
        P[i].input();
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &color[i]);
        --color[i];
    }
    for (int i = 1; i <= m; ++i) {
        Q[i].input();
    }
    double ans = 1e60;
    for (int i = 1; i <= m; ++i) {
        int r = 0;
        S = Q[i];
        for (int j = 1; j <= m; ++j) {
            Point C = Q[j] - Q[i];
            if (C.x > 0 || (C.x == 0 && C.y > 0))
                T[r++] = Q[j];
        }
        sort(T, T + r, cmp);
        for (int p = 0; p < r; ++p)
            for (int j = p + 1; j < r; ++j) {
                int mask = 0;
                for (int k = 1; k <= n; ++k) {
                    if ((T[p] - Q[i]).det(P[k] - Q[i]) <= 0 &&
                        (T[j] - T[p]).det(P[k] - T[p]) <= 0 &&
                        (Q[i] - T[j]).det(P[k] - T[j]) <= 0)
                        mask |= 1 << color[k];
                }
                opt[p][j] = mask;
            }
        for (int j = 0; j < r; ++j)
            for (int mask = 0; mask < 1 << K; ++mask)
                f[j][mask] = 1e60;
        for (int j = 0; j < r; ++j) {
            f[j][0] = min(f[j][0], (T[j] - Q[i]).len());
            for (int mask = 0; mask < 1 << K; ++mask)
                if (f[j][mask] < 1e50) {
                    for (int k = j + 1; k < r; ++k)
                        f[k][mask | opt[j][k]] = min(f[k][mask | opt[j][k]], f[j][mask] + (T[k] - T[j]).len());
                }
        }
        for (int j = 0; j < r; ++j)
            ans = min(ans, f[j][(1 << K) - 1] + (T[j] - Q[i]).len());
    }
    if (ans > 1e50) puts("-1");
    else printf("%.15f\n", ans);
    return 0;
}
