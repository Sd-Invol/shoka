#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <cmath> 
using namespace std;

const int N = 1e5 + 5;
int f[2][350][350];

struct PEO {
    int A, C, S;

    int operator < (const PEO &a) const {
        if (a.C != C) return C < a.C;
        return A < a.A;
    }
}p[N];

void updata(int &x, int y) {
    x = min(x, y);
}

int main() {
    int n, K;
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &p[i].A, &p[i].C, &p[i].S);
        if (p[i].A == 1) p[i].A = 3;
        else if (p[i].A == 2) p[i].A = 1;
        else p[i].A = 2;
    }
    sort(p + 1, p + 1 + n);
    //for (int i = 1; i <= n; ++i)
    //    printf("%d %d %d\n", p[i].A, p[i].C, p[i].S);
    memset(f, 63, sizeof(f));
    int cur = 0, nex = 1;
    f[cur][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= K; ++j)
            for (int k = 0; k <= K; ++k)
                f[nex][j][k] = 1 << 29;
        for (int j = 0; j <= K; ++j)
            for (int k = 0; k <= K; ++k) {
                if (j < K && p[i].A != 3)
                    updata(f[nex][j + 1][k], f[cur][j][k] + p[i].S);
                if (k < j && p[i].A != 1)
                    updata(f[nex][j][k + 1], f[cur][j][k] + p[i].S);
                updata(f[nex][j][k], f[cur][j][k]);
            }
        swap(cur, nex);
    }
    printf("%d\n", f[cur][K][K]);
}
