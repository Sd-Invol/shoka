#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <cmath> 
using namespace std;

const int N = 1e5 + 5;
int a[N];

typedef long long LL;

LL b[N], c[N];

struct Point {
    LL x, y;
    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y};
    }

    LL det(const Point &a) const {
        return x * a.y - y * a.x;
    }
};

LL f[2][5005];
int cur, nex;
Point p[5005];
int id[5005];

LL gett(int k, int j) {
    return f[cur][k] + c[j] - c[k] - (LL)k * b[j] + (LL)k * b[k];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        c[i] = a[i] * i;
        b[i] = a[i];
    }
    for (int i = 1; i <= n; ++i) {
        c[i] += c[i - 1];
        b[i] += b[i - 1];
    }
    memset(f, 63, sizeof(f));
    cur = 0, nex = 1;
    f[cur][0] = 0;
    for (int i = 1; i <= m; ++i) {
        memset(f[nex], 63, sizeof(f[nex]));
        int head = 1, tail = 0;
        
        for (int j = 0; j <= n; ++j) {
            while (head < tail && gett(id[head], j) >= gett(id[head + 1], j))
                ++head;
            if (head <= tail) f[nex][j] = gett(id[head], j);
            if (f[cur][j] > (1LL << 31)) continue;
            Point p1;
            p1.x = j;
            p1.y = f[cur][j] - c[j] + b[j] * j;
            while (head < tail && (p[tail] - p[tail - 1]).det(p1 - p[tail]) <= 0)
                --tail;
            ++tail;
            id[tail] = j;
            p[tail] = p1;
        }
        swap(cur, nex);
    }
    cout << f[cur][n] << endl;
    return 0;
}
