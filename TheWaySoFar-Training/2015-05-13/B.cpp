#include <bits/stdc++.h>
using namespace std;
const int N = 255;

typedef long long LL;

struct DD {
    int wi, ti, dti;
};

struct CC {
    int ti, dti;

    int operator < (const CC &a) const {
        return ti > a.ti;
    }
};
     
vector <DD> verD;
vector <CC> verC;

LL f[2][10005];

struct Point {
    LL x, y;
    int id;

    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y, 0};
    }
    
    LL operator * (const Point &a) const {
        return x * a.y - a.x * y;
    }
    
};

Point P[100000];

LL calc(int cur, int k, int j, int i) {
    int n = (j - k) / verD[i].wi;
    //printf("%d\n", n * verD[i].ti * 2 - (n * n - n) * verD[i].dti);
    return f[cur][k] + (LL)n * verD[i].ti * 2 - ((LL)n * n - n) * verD[i].dti;
}

const double esp = 1e-11;

double work(int m) {
    int cur = 0, nex = 1;
    for (int i = 0; i <= m; ++i)
        f[cur][i] = -(1LL << 50);
    f[cur][0] = 0;
    for (int i = 0; i < verD.size(); ++i) {
        for (int j = 0; j <= m; ++j)
            f[nex][j] = -(1LL << 50);
        int len = verD[i].wi, dti = verD[i].dti, ti = verD[i].ti;
        for (int L = 0; L < len; ++L) {
            int head = 1, tail = 0;
            for (int j = 0; j * len + L <= m; ++j) {
                if (f[cur][j * len + L] > -(1LL << 50)) {
                    LL x = (LL)j * dti;
                    LL y = f[cur][j * len + L] - (LL)2 * j * ti - (LL)j * j * dti - (LL)j * dti;  
                    Point t = (Point) {x, y, j * len + L};
                    while (head < tail && (P[tail] - P[tail - 1]) * (t - P[tail]) >= 0)
                        --tail;
                    P[++tail] = t;
                }
                while (head < tail && calc(cur, P[head].id, j * len + L, i)
                       <= calc(cur, P[head + 1].id, j * len + L, i))
                    ++head;
                
                if (head <= tail)
                    f[nex][j * len + L] = calc(cur, P[head].id, j * len + L, i);
            }
        }
        swap(cur, nex);
    }
    //for (int i = 0; i <= m; ++i)
    //    printf("!%d %.2f\n", i, f[cur][i] * 1.0 / 2);
    sort(verC.begin(), verC.end());
    double ans = -1e60;
    for (int i = 0; i <= m; ++i)
        if (f[cur][i] > -(1LL << 50)) {
            double ans1 = (double)f[cur][i] / 2;
            if (i == m) {
                ans = max(ans, ans1);
                continue;
            }
            if (verC.empty()) continue;
            static double res[255];
            memset(res, 0, sizeof(res));
            double w = m - i, di = 0;
            for (int j = 0; j < verC.size(); ++j) {
                if (fabs(w) < esp) break;
                if (verC[j].dti == 0) {
                    res[j] += w;
                    break;
                }
                di += 1.0 / verC[j].dti;
                double len = 1e60;
                if (j + 1 < verC.size())
                    len = (verC[j].ti - verC[j + 1].ti) * di;
                len = min(len, w);
                w -= len;
                for (int k = 0; k <= j; ++k)
                    res[k] += len / di;
            }
            for (int j = 0; j < verC.size(); ++j) {
                if (verC[j].dti != 0)
                    res[j] = res[j] / verC[j].dti;
                ans1 += res[j] * verC[j].ti - res[j] * res[j] / 2 * verC[j].dti;
                //printf("!%.10f\n", res[j]);
            }
            //printf("%d %.10f %lld\n", i, ans1, f[cur][i]);
            ans = max(ans, ans1);
        }
    return ans;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int ch;
        while (ch = getchar(), !isupper(ch));
        if (ch == 'D') {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            verD.push_back((DD) {x, y, z});
        }
        else {
            int x, y;
            scanf("%d%d", &x, &y);
            verC.push_back((CC) {x, y});
        }
    }
    double t = work(m);
    if (t < -(1e50)) puts("impossible");
    else printf("%.10f\n", t);
    return 0;
}
