#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
typedef long long LL;
using namespace std;
const int N = 1e4 + 5;
double f[N][2], a[N];
int b[N];
int pre[N][2];

const double eps = 1e-4;
int m;

int main() {
    int n;
    scanf("%d", &n);
    m = 0;
    int mark = 0;
    for (int i = 1; i <= n; ++i) { 
        scanf("%lf", &a[i]);
        if (fabs(a[i]) > eps) {
            a[++m] = a[i];
            b[m] = i;
        }
        else mark = i;
    }
    if (m == 0) {
        puts("1");
        puts("1");
        return 0;
    }
    if (m == 1 && a[m] < 0) {
        if (mark != 0) {
            printf("1\n%d\n", mark);
            return 0;
        }
        printf("1\n%d\n", b[m]);
        return 0;
    }
    f[0][0] = f[0][1] = -1e60;
    for (int i = 1; i <= m; ++i) {
        int k = 0;
        if (a[i] < 0) k = 1;
        double x = log(fabs(a[i]));
        x = x * 100000 - 1;
        for (int j = 0; j < 2; ++j) {
            if (f[i - 1][j] < f[i - 1][j ^ k] + x) {
                f[i][j] = f[i - 1][j ^ k] + x;
                pre[i][j] = 1;
            }
            else {
                f[i][j] = f[i - 1][j];
                pre[i][j] = 0;
            }
        }
        if (x > f[i][k]) {
            f[i][k] = x;
            pre[i][k] = -1;
        }
    }
    int x = m, y = 0;
    vector<int> ver;
    while (x > 0) {
        int k = 0;
        if (a[x] < 0) k = 1;
        if (pre[x][y] == 1 || pre[x][y] == -1) {
            ver.push_back(b[x]);
            if (pre[x][y] == -1) break;
            y ^= k;
        }
        --x;
    }
    printf("%d\n", (int)ver.size());
    reverse(ver.begin(), ver.end());
    for (int i = 0; i < ver.size(); ++i)
        printf("%d%c", ver[i], " \n"[i == (int)ver.size() - 1]);
    return 0;
}