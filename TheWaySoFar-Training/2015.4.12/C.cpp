#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

double f[205][205], g[2][205], item[205];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int ci, fi;
        scanf("%d", &ci);
        scanf("%d", &fi);
        vector<pair<int, int> > ver;
        for (int j = 0; j < fi; ++j) {
            char str[20];
            scanf("%s", str);
            pair<int, int> side = make_pair(0, 0);
            char *p = str;
            if (*p == '+') {
                side.second = 1;
                ++p;
            }
            sscanf(p, "%d", &side.first);
            if (side.first != 0) ver.push_back(side);
        }
        fi = ver.size();
        memset(g, 0, sizeof(g));
        g[0][0] = 1;
        for (int j = 0; j < 200; ++j) {
            for (int k = 0; k < ver.size(); ++k) {
                int _j = j + ver[k].first;
                if (_j > 200) _j = 200;
                g[ver[k].second ^ 1][_j] += g[0][j] / fi;
            }
        }
        double pp = 1;
        for (int j = 0; j < 200; ++j)
            item[j] = g[1][j], pp -= g[1][j];
        item[200] = pp;
        static double F[13][205];
        memset(F, 0, sizeof(F));
        F[0][0] = 1;
        for (int I = 0; I < ci; ++I)
            for (int j = 0; j <= 200; ++j) 
                for (int k = 0; k <= 200; ++k) {
                    int _k = min(200, j + k);
                    F[I + 1][_k] += F[I][j] * item[k];
                }
        for (int j = 200; j >= 0; --j) {
            f[i][j] = F[ci][j];
            if (j != 200) f[i][j] += f[i][j + 1];
        }
        //if (i < 3)
        //    for (int j = 0; j <= 10; ++j)
        //        printf("%d %.10f\n", j, f[i][j]);
    }
    int K;
    scanf("%d", &K);
    for (int i = 1; i <= K; ++i) {
        int k = -1;
        double pn = -1;
        for (int j = 1; j <= n; ++j) {
            double pi = 0;
            for (int L = 1; L <= i; ++L)
                pi += 1.0 / i * f[j][L + 1];
            pi = f[j][i + 1];
            if (pi > pn) {
                k = j;
                pn = pi;
            }
            //printf("%d %d %.5f\n", i, j, pi);
        }
        printf("%d\n", k);
    }
    return 0;
}
