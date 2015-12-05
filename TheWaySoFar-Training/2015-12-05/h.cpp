#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 505;

const double eps = 1e-9;
int h[N], r[N], R[N];
double f[N][N];

int main() {
    int n, H;
    scanf("%d%d", &n, &H);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &h[i], &r[i], &R[i]);
    }
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = 1e60;
    for (int i = 1; i <= n; ++i)
        f[i][1] = h[i];
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            double res;
            if (r[j] <= R[i]) {
                res = h[j] - h[i]; 
                if (r[j] > r[i])
                    res = max(h[j] - (h[i] - (double)r[j] / R[i] * h[i]), res);
                if (R[j] > R[i]) 
                    res =  max(h[j] - (double)R[i] / R[j] * h[j], res);
            }
            else res = h[j]; 

            //cout << res << endl;
            //cout << h[j] - (h[i] - (double)r[j] / R[i] * h[i]) << endl;
            //cout <<  h[j] - (double)R[i] / R[j] * h[j] << endl;
            for (int k = 1; k <= i; ++k)
                f[j][k + 1] = min(f[j][k + 1], f[i][k] + res);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            if (f[i][j] - eps <= H)
                ans = max(ans, j);
    //cout << f[2][2] << endl;
    cout << ans << endl;
    return 0;
}
