#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
using namespace std;

const int N = 3e5 + 5;
const int D = 20;
const int P = 1e4 + 7;

typedef unsigned long long ULL;

int first[N], tot;

struct Edge {
    int y, s, nex;
}edge[N << 2];

set<ULL> ext;

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, x, first[x]};
    first[x] = tot++;
}

ULL f[N], power[N];
int size[N];

void dp1(int x, int fa) {
    vector<pair<ULL, int> > pr;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        dp1(y, x);
        pr.push_back(make_pair(f[y], size[y]));
    }
    sort(pr.begin(), pr.end());
    f[x] = 'L';
    size[x] = 1;
    for (int i = 0; i < pr.size(); ++i) {
        f[x] = f[x] * power[pr[i].second] + pr[i].first;
        size[x] += pr[i].second;
    }
    ++size[x];
    f[x] = f[x] * P + 'R';
}

struct Point {
    ULL hash;
    int size;
    int x;

    int operator < (const Point &a) const {
        return make_pair(hash, size) < make_pair(a.hash, a.size);
    }
};

int n;
int bo[N], gs[N];
ULL g[N];
int degree[N];

void dp2(int x, int fa, int flag) {
    vector<Point> pr;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) pr.push_back((Point){g[y], gs[y], y});
        else pr.push_back((Point) {f[y], size[y], y});
    }
    sort(pr.begin(), pr.end());
    vector<ULL> sum;
    vector<int> sz;
    ULL tmp = 'L';
    sum.push_back(tmp);
    int tot = 2;
    for (int i = 0; i < pr.size(); ++i) {
        tmp = tmp * power[pr[i].size] + pr[i].hash;
        sum.push_back(tmp);
        tot += pr[i].size;
    }
    if (flag == 0) {
        //cout << size[2] << endl;
        ext.insert((sum.back() * P + 'R'));
        //printf("+%llu\n", sum.back() * P + 'R');
    }
    else {
        if (degree[x] == 1) {
            int y = edge[first[x]].y;
            //printf("$%d %d %llu\n", x, y, f[2]);
            ULL res;
            if (y == fa) res = g[y];
            else res = f[y];
            //printf("!%llu\n", res);
            if (ext.count(res)) bo[x] = 1;
        }
    }
    tmp = 'R';
    for (int i = (int)pr.size() - 1, sz = 1; i >= 0; --i) {
        if (pr[i].x != fa) {
            g[x] = tmp;
            g[x] += sum[i] * power[sz];
            gs[x] = tot - pr[i].size;
            //printf("~~~~%d %d %llu\n", x, pr[i].x, g[x]);
            dp2(pr[i].x, x, flag);

        }
        tmp += pr[i].hash * power[sz];
        sz += pr[i].size;
    }
}

int main() {
    power[0] = 1;
    for (int i = 1; i < N; ++i)
        power[i] = power[i - 1] * P;
    memset(first, -1, sizeof(first));
    tot = 0;
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    dp1(1, 0);
    dp2(1, 0, 0);
    memset(first, -1, sizeof(first));
    tot = 0;
    ++n;
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
        ++degree[x];
        ++degree[y];
    }
    
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    dp1(1, 0);
    dp2(1, 0, 1);
    //for (int i = 1; i <= n; ++i)
    //    printf("( 2 %d %llu)\n", i, f[i]);
    for (int i = 1; i <= n; ++i)
        if (bo[i]) {
            printf("%d\n", i);
            break;
        }
    return 0;
}
