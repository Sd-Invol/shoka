#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
using namespace std;

const double eps = 1e-11;

struct Point {
    double x, y;

    Point() {}

    Point(double _x, double _y) : x(_x), y(_y) {}

    void input() {
        scanf("%lf%lf", &x, &y);
    }
    
    Point operator - (const Point &a) const {
        return Point(x - a.x, y - a.y);
    }

    Point operator + (const Point &a) const {
        return Point(x + a.x, y + a.y);
    }

    Point operator / (double a) const {
        return Point(x / a, y / a);
    }

    Point operator * (double a) const {
        return Point(x * a, y * a);
    }

    double operator * (const Point &a) const {
        return x * a.x + y * a.y;
    }
    
    double len() {
        return sqrt(x * x + y * y);
    }

    double det(const Point &a) const {
        return x * a.y - y * a.x;
    }

    int operator < (const Point &a) const {
        if (fabs(a.x - x) > eps) return x < a.x - eps;
        return y < a.y - eps;
    }

    
    int operator == (const Point &a) const {
        return (fabs(a.x - x) < eps) && (fabs(a.y - y) < eps);
    }
};

int gett(double ch) {
    if (ch < -eps) return -1;
    if (ch > eps) return 1;
    return 0;
}

struct Line {
    Point x, y;
    
    Line() {}

    Line(Point _x, Point _y): x(_x), y(_y) {}

    int interact(const Line &a) const {  
        if (gett((y - x).det(a.x - x)) * gett((y - x).det(a.y - x)) <= 0 &&
            gett((a.y - a.x).det(x - a.x)) * gett((a.y - a.x).det(y - a.x)) <= 0)
            return 1;
        return 0;
    }

    int onSegment(const Point &a) const { 
        if (fabs((x - y).det(a - y)) < eps &&
            (x - a) * (y - a) <= eps) return 1;
        return 0;
    }
}l[305];

Point interactPoint(const Line &a, const Line &b) {
    if (a.x == b.x || a.x == b.y) return a.x;
    if (a.y == b.x || a.y == b.y) return a.y;
    if (a.x == a.y) return a.x;
    if (b.x == b.y) return b.x;
    Point u = (a.y - a.x) / (a.y - a.x).len();
    Point v = (b.y - b.x) / (b.y - b.x).len();
    double a1 = u.x, b1 = -v.x, c1 = a.x.x - b.x.x;
    double a2 = u.y, b2 = -v.y, c2 = a.x.y - b.x.y;
    double t1 = (-c1 * b2 + c2 * b1) / (a1 * b2 - a2 * b1);
    return a.x + u * t1; 
}

const int N = 2e5 + 5;

Point swit[2005], key[N];
Point S, T;
int first[N], tot;

struct Edge {
    int y;
    double s;
    int nex;
}edge[N * 5];

void addedge(int x, int y, double s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

void buildGraph(int n, int m, int r) {
    memset(first, -1, sizeof(first));
    tot = 0;
    static double ins[2005];
    for (int i = 1; i <= n; ++i) {
        int p = 2;
        ins[1] = 0;
        ins[2] = (l[i].y - l[i].x).len();
        if (fabs(ins[2]) < eps) continue;
        for (int j = 1; j <= n; ++j)
            if (i != j && l[i].interact(l[j])) {
                Point c = interactPoint(l[i], l[j]);
                ins[++p] = (c - l[i].x).len();
            }
        for (int j = 1; j <= m; ++j) {
            if (l[i].onSegment(swit[j])) ins[++p] = (swit[j] - l[i].x).len(); 
        }
        if (l[i].onSegment(S)) ins[++p] = (S - l[i].x).len();
        if (l[i].onSegment(T)) ins[++p] = (T - l[i].x).len();
        sort(ins + 1, ins + p + 1);
        Point unit = (l[i].y - l[i].x) / (l[i].y - l[i].x).len();
        for (int j = 2; j <= p; ++j) {
            if (fabs(ins[j] - ins[j - 1]) < eps) continue;
            Point c1 = l[i].x + unit * ins[j - 1];
            Point c2 = l[i].x + unit * ins[j];
            int t1 = lower_bound(key + 1, key + 1 + r, c1) - key;
            int t2 = lower_bound(key + 1, key + 1 + r, c2) - key;
            addedge(t1, t2, ins[j] - ins[j - 1]);
            addedge(t2, t1, ins[j] - ins[j - 1]);
        }
    }
}

int b1[N], b2[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int r = 0;
    for (int i = 1; i <= n; ++i) {
        l[i].x.input();
        l[i].y.input();
        key[++r] = l[i].x;
        key[++r] = l[i].y;
    }
    for (int i = 1; i <= m; ++i) {
        swit[i].input();
        key[++r] = swit[i];
    }
    sort(swit + 1, swit + 1 + m);
    m = unique(swit + 1, swit + 1 + m) - swit - 1;
    S.input();
    T.input();
    key[++r] = S;
    key[++r] = T;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (l[i].interact(l[j]))
                key[++r] = interactPoint(l[i], l[j]);
    sort(key + 1, key + 1 + r);
    r = unique(key + 1, key + 1 + r) - key - 1;
    buildGraph(n, m, r);
    for (int i = 1; i <= r; ++i) {
        Point c = key[i];
        int t = lower_bound(swit + 1, swit + 1 + m, key[i]) - swit;
        if (t <= m && swit[t] == key[i]) {
            b1[i] = 1;
        }
    }
    queue<int> que;
    int flag = 0;
    for (int i = 1; i <= r; ++i)
        if (T == key[i]) {
            b2[i] = 1;
            que.push(i);
            if (b1[i]) while (1);
        }
    while (!que.empty()) {
        int x = que.front(); que.pop();
        if (S == key[x]) {
            flag = 1;
            break;
        }
        for (int k = first[x]; k != -1; k = edge[k].nex) {
            int y = edge[k].y;
            if (b2[y]) continue;
            b2[y] = 1;
            if (!b1[y]) que.push(y);
        }
    }
    if (flag) {
        puts("-1");
        return 0;
    }
    double ans = 0;
    for (int i = 1; i <= r; ++i)
        if (key[i] == S) {
            que.push(i);
            b2[i] = 1;
            if (b1[i]) while (1); 
        }
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int k = first[x]; k != -1; k = edge[k].nex) {
            int y = edge[k].y;
            ans += edge[k].s;
            edge[k].s = edge[k ^ 1].s = 0;
            if (!b2[y]) {
                b2[y] = 1;
                
                que.push(y);
            }
        }
    }
    ans = -ans;
    for (int i = 1; i <= n; ++i)
        ans += (l[i].x - l[i].y).len();
    printf("%.15f\n", ans);
    return 0;
}