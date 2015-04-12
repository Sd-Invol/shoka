#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <queue>
#include <cmath>
using namespace std;

typedef long long LL;
const int N = 5e4 + 5;
int xx[N], rr[N];
double px[N], h[N];
int n;
const double esp = 1e-9;

int stack[N], p;

double sqr(double x) {
    return x * x;
}

int check(double x) {
    int m = 0;
    static pair<double, double> interval[N]; 
    for (int i = 1; i <= n; ++i) {
        double C = sqr(rr[i]) - sqr(x / 2);
        if (C <= 0) continue;
        interval[m++] = make_pair(xx[i] - sqrt(C), -(xx[i] + sqrt(C)));
    }
    sort(interval, interval + m);
    int r = 0;
    for (int i = 0; i < m; ++i)
        interval[i].second = -interval[i].second;
    for (int i = 0; i < m; ++i)
        if (r != 0 && interval[r - 1].second > interval[i].first - esp)
            interval[r - 1].second = max(interval[r - 1].second, interval[i].second);
        else interval[r++] = interval[i];
    for (int i = 0; i < r; ++i)
        if (interval[i].second - interval[i].first > x - esp) return 1;
    
    return 0;
}

int main() {
    while (scanf("%d", &n), n) {
        double ans = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &xx[i], &rr[i]);
            ans = max(ans, (double)rr[i] * sqrt(2));
        }
        double head = ans, tail = ans * sqrt(2);
        while (tail - head > 1e-8) {
            double mid = (head + tail) / 2;
            if (check(mid)) head = mid;
            else tail = mid;
        }
        printf("%.10f\n", max(ans, head));
    }
    return 0;
}
