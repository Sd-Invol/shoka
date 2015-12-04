#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

typedef long long LL;
const int N = 4005;

struct Point {
    LL x, y;

    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y};
    }

    LL det(const Point &a) const {
        return x * a.y - y * a.x;
    }
    
}P[N];

struct Son {
    int t, p, f;

    int operator < (const Son &a) const {
        return f < a.f;
    }
}s[N];

LL F[N][N];
int id[N];

LL calc(int t, int k, int i) {
    return F[t][k] - (LL)(s[k].f - s[i].f) * (s[k].f - s[i].f) + s[i].p;
}

void updata(LL &x, LL y) {
    x = max(x, y);
}

int main() {
    int n, T;
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &s[i].t, &s[i].p, &s[i].f);
    sort(s + 1, s + 1 + n);
    memset(F, -1, sizeof(F));
    for (int i = 1; i <= T; ++i) {
        int head = 1, tail = 0;
        for (int j = 1; j <= n; ++j) {
            while (head < tail && calc(i, id[head], j) <= calc(i, id[head + 1], j))
                ++head;
            if (head <= tail && i + s[j].t <= T)
                updata(F[i + s[j].t][j], calc(i, id[head], j));
            if (i >= s[j].t) F[i][j] = max(F[i][j], (LL)s[j].p);
            if (F[i][j] != -1) {
                Point p1;
                p1.x = s[j].f;
                p1.y = F[i][j] - (LL)s[j].f * s[j].f;
                while (head < tail && (P[tail] - P[tail - 1]).det(p1 - P[tail]) >= 0)
                    --tail;
                ++tail;
                P[tail] = p1;
                id[tail] = j;
            }
        }
    }
    LL ans = -1;
    for (int j = 0; j <= T; ++j)
        for (int i = 0; i <= n; ++i)
            ans = max(ans, F[j][i]);
    printf("%lld\n", ans);
    return 0;
}
