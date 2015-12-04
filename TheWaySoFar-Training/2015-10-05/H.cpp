#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
using namespace std;

const int N = 305;
const double eps = 1e-10;

pair<int, int> X[N], Y[N];
double len[N][N];

double getlen(double x, double y) {
    return sqrt(x * x + y * y);
}

double dx[N], dy[N];
int my[N], mx[N];
double slack[N];
int bx[N], by[N];
int n;

int find(int x) {
    bx[x] = 1;
    for (int i = 0; i < n; ++i)
        if (!by[i]) {
            if ((len[x][i] - dx[x] - dy[i]) < eps) {
                by[i] = 1;
                if (my[i] == -1 || find(my[i])) {
                    my[i] = x;
                    mx[x] = i;
                    return 1;
                }
            }
            else slack[i] = min(slack[i], len[x][i] - dx[x] - dy[i]);
        }
    return 0;
}

int main() {
    
    scanf("%d", &n);
    scanf("%d%d", &X[0].first, &X[0].second);
    Y[0] = X[0];
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &X[i].first, &X[i].second);
        scanf("%d%d", &Y[i].first, &Y[i].second);
    }
    ++n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            len[i][j] = getlen(X[i].first - Y[j].first, X[i].second - Y[j].second);
        }
    for (int i = 0; i < n; ++i) {
        dx[i] = 1e40;
        for (int j = 0; j < n; ++j) {
            dx[i] = min(dx[i], len[i][j]);
            //dy[i] = min(dy[i], len[j][i]);
        }
    }
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
//    cout << 1 << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            slack[j] = 1e40;
        }
        while (1) {
            memset(bx, 0, sizeof(bx));
            memset(by, 0, sizeof(by));
            
            if (find(i)) break;
            double d = 1e40;
            for (int j = 0; j < n; ++j)
                if (!by[j]) d = min(d, slack[j]);
            for (int j = 0; j < n; ++j) {
                if (bx[j]) dx[j] += d;
                if (by[j]) dy[j] -= d;
                else slack[j] -= d;
            }
        }
    }
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += len[i][mx[i]];
        ans += getlen(X[i].first - Y[i].first, X[i].second - Y[i].second);
    }
    printf("%.10f\n", ans);
    return 0;
}
