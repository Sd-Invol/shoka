#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 4005;
double D[N];
int a[N], bo[N];
int degree[N];
double F[4005][2005];
double f[4005][2005];

int main() {
    int T;
    scanf("%d", &T);
    F[0][0] = 0;
    f[0][0] = 1;
    for (int j = 0; j < N; ++j)
        for (int i = 0; i + i + j < N; ++i)
            if (i + j != 0) {
                if (i > 0) {
                    {
                        F[j][i] += F[j][i - 1] + 1 * f[j][i - 1];
                        f[j][i] += f[j][i - 1];
                    }
                    if (i > 1) {
                        F[j][i] += F[j][i - 1] * (i - 1);
                        f[j][i] += f[j][i - 1] * (i - 1);
                    }
                    if (j > 0) {
                        F[j][i] += F[j - 1][i] * j;
                        f[j][i] += f[j - 1][i] * j;
                    }
                }
                if (i == 0) {
                    if (j > 1) {
                        F[j][i] += F[j - 2][i + 1] * (j - 1);// / (j - 1);
                        f[j][i] += f[j - 2][i + 1] * (j - 1);
                    }
                }
                F[j][i] /= (double)(i + j);
                f[j][i] /= (double)(i + j);
            }
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        double num = 0;
        for (int i = 1; i <= n; ++i)
            degree[i] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            //a[i] = 0;
            bo[i] = 0;
            ++degree[a[i]];
        }
        int t1 = 0, t2 = 0;
        for (int i = 1; i <= n; ++i)
            if (degree[i] == 0 && !bo[i]) {
                if (a[i] == 0) ++t1;
                else ++t2;
                int x = i;
                do {
                    bo[x] = 1;
                    x = a[x];
                } while (x != 0 && !bo[x]);
            }
        for (int i = 1; i <= n; ++i)
            if (!bo[i]) {
                num = num + 1;
                int x = i;
                while (!bo[x]) {
                    bo[x] = 1;
                    x = a[x];
                }
            }
        printf("%.10f\n", (F[t1][t2] / f[t1][t2] + num) * m);
    }
    //cout << (sizeof(F) + sizeof(bb)) / 1024 / 1024 << endl;
    return 0;
}