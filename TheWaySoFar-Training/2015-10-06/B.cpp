#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
typedef long long LL;
using namespace std;

const int N = 1e5 + 5;
int g[N], a[N], b[N];
pair<int, double> id[N];
const double eps = 1e-10;

int cmp(pair<int, double> a, pair<int, double> b) {
    return a.second > b.second;
}

double xx[N];

int main() {
    freopen("burrito.in", "r", stdin);
    freopen("burrito.out", "w", stdout);
    int n, A, B;
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &g[i], &a[i], &b[i]);
        id[i].first = i;
        if (a[i] == 0) id[i].second = 0;
        else if (b[i] == 0) id[i].second = 1e60;
        else id[i].second = (double)a[i] / b[i];
    }
    sort(id + 1, id + 1 + n, cmp);
    double aa = 0, bb = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[id[i].first] == 0) {
            xx[id[i].first] = g[id[i].first];
        }
        else if (a[id[i].first] == 0) {
            xx[id[i].first] = 0;
        }
        else {
            double T = g[id[i].first];
            T = min(T, (B - bb) / b[id[i].first]);
            xx[id[i].first] = T;
        }
        aa += xx[id[i].first] * a[id[i].first];
        bb += xx[id[i].first] * b[id[i].first];
    }
    if (aa < A - eps || bb > B + eps)
        puts("-1 -1");
    else {
        printf("%.10f %.10f\n", aa, bb);
        for (int i = 1; i <= n; ++i)
            printf("%.10f%c", xx[i], " \n"[i == n]);
    }
    return 0;
}
