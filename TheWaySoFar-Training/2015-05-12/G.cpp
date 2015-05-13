#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

double f[105][105];
pair<int, int> pre[105][105];

int xx[105], yy[105];

double sqr(double x) {
    return x * x;
}

double dis(int i, int j) {
    return sqrt(sqr(xx[i] - xx[j]) + sqr(yy[i] - yy[j]));
}

int main() {
    int n, b1, b2;
    while (scanf("%d%d%d", &n, &b1, &b2), n) {
        for (int i = 0; i < n; ++i)
            scanf("%d%d", &xx[i], &yy[i]);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                f[i][j] = 1e60;
        f[0][0] = 0;
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < i; ++j) {
                double s = dis(i - 1, i);
                if (f[i][j] > f[i - 1][j] + s && i != b2) {
                    pre[i][j] = make_pair(i - 1, j);
                    f[i][j] = f[i - 1][j] + s;
                }
                if (f[j][i] > f[j][i - 1] + s && i != b1) {
                    pre[j][i] = make_pair(j, i - 1);
                    f[j][i] = f[j][i - 1] + s;
                }
                s = dis(j, i);
                if (f[i - 1][i] > f[i - 1][j] + s && i != b1) {
                    pre[i - 1][i] = make_pair(i - 1, j);
                    f[i - 1][i] = f[i - 1][j] + s;
                }
                if (f[i][i - 1] > f[j][i - 1] + s && i != b2) {
                    pre[i][i - 1] = make_pair(j, i - 1);
                    f[i][i - 1] = f[j][i - 1] + s;
                }
            }
        for (int i = 0; i < n - 1; ++i) {
            double s = dis(i, n - 1);
            if (f[n - 1][n - 1] > f[i][n - 1] + s) {
                f[n - 1][n - 1] = f[i][n - 1] + s;
                pre[n - 1][n - 1] = make_pair(i, n - 1);
            }
            if (f[n - 1][n - 1] > f[n - 1][i] + s) {
                f[n - 1][n - 1] = f[n - 1][i] + s;
                pre[n - 1][n - 1] = make_pair(n - 1, i);
            }
        }
        static int ca = 0;
        printf("Case %d: %.2f\n", ++ca, f[n - 1][n - 1]);
        int x = n - 1, y = n - 1;
        vector<int> ans1, ans2;
        while (x != 0 || y != 0) {
            int _x = pre[x][y].first;
            int _y = pre[x][y].second;
            if (_x != x) ans1.push_back(x);
            else ans2.push_back(y);
            x = _x; y = _y;
            //printf("%d %d\n", _x, _y);
        }
        ans1.push_back(0);
        ans2.push_back(0);
        /*printf("%d %d\n", ans1.size(), ans2.size());
        for (int i = 0; i < ans1.size(); ++i)
            printf("%d%c", ans1[i], " \n"[i == ans1.size() - 1]);
            for (int i = 0; i < ans2.size(); ++i)                                     printf("%d%c", ans2[i], " \n"[i == ans2.size() - 1]);*/
        reverse(ans1.begin(), ans1.end());
        ans1.pop_back();
        vector<int> ans = ans1;
        ans.insert(ans.end(), ans2.begin(), ans2.end());
        if (ans[1] != 1)
            reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); ++i)
            printf("%d%c", ans[i], " \n"[i == ans.size() - 1]);
    }
    return 0;
}
