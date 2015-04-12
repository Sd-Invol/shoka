#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 1e6 + 5;
const int P = 1e9 + 9;
char str[3][N];
int len[3];
int f[N][4];
int D[30][30][30][4];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int F[30][30][2];

int gett(int i, int j, int pos, int mask) {
    int i1, i2;
    if (len[i] < pos) i1 = 0;
    else if (str[i][pos] == '?') i1 = 27;
    else i1 = str[i][pos] - 'a' + 1;
    if (len[j] < pos) i1 = 0;
    else if (str[j][pos] == '?') i2 = 27;
    else i2 = str[j][pos] - 'a' + 1;
    return F[i1][i2][mask];
}

void work() {
    int n = 0; 
    for (int i = 0; i < 3; ++i) {
        scanf("%s", str[i] + 1);
        len[i] = strlen(str[i] + 1);
        n = max(n, len[i]);
    }
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < 4; ++j)
            f[i][j] = 0;
    f[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        {
            int K = 1;
            for (int j = 0; j < 3; ++j)
                if (len[j] >= i + 1 && str[j][i + 1] == '?')
                    K *= 26;
            updata(f[i + 1][3], (LL)f[i][3] * K % P);
        }// 11;
        {
            int K = 1;
            if (len[0] >= i + 1 && str[0][i + 1] == '?') K = 26;
            int K0 = gett(1, 2, i + 1, 0) * K;
            int K1 = gett(1, 2, i + 1, 1) * K;
            updata(f[i + 1][3], (LL)f[i][1] * K1 % P);
            updata(f[i + 1][1], (LL)f[i][1] * K0 % P);
        } // 01
        {
            int K = 1;
            if (len[2] >= i + 1 && str[2][i + 1] == '?') K = 26;
            int K0 = gett(0, 1, i + 1, 0) * K;
            int K1 = gett(0, 1, i + 1, 1) * K;
            updata(f[i + 1][3], (LL)f[i][2] * K1 % P);
            updata(f[i + 1][2], (LL)f[i][2] * K0 % P);
        } // 10
        {
            int p[3];
            for (int j = 0; j < 3; ++j)
                if (len[j] < i + 1) p[j] = 0;
                else if (str[j][i + 1] == '?') p[j] = 27;
                else p[j] = str[j][i + 1] - 'a' + 1;
            for (int mask = 0; mask < 4; ++mask)
                updata(f[i + 1][mask], (LL)D[p[0]][p[1]][p[2]][mask] * f[i][0] % P);
        } // 00
    }
    printf("%d\n", f[n][3]);
}

int main() {
    int T, p[3];
    for (p[0] = 0; p[0] <= 26; ++p[0])
        for (p[1] = 0; p[1] <= 26; ++p[1])
            for (p[2] = 0; p[2] <= 26; ++p[2]) {
                if (p[0] > p[1] || p[1] > p[2]) continue;
                int mask = (p[0] < p[1]) | ((p[1] < p[2]) << 1);
                ++D[p[0]][p[1]][p[2]][mask];
                for (int opt = 1; opt < 1 << 3; ++opt) {
                    int L[3];
                    for (int i = 0; i < 3; ++i)
                        if (opt >> i & 1) {
                            if (p[i] != 0) L[i] = 27;
                            else L[i] = -1;
                        }
                        else L[i] = p[i];
                    if (L[0] == -1 || L[1] == -1 || L[2] == -1) continue;
                    D[L[0]][L[1]][L[2]][mask]++;
                }
            }
    for (int i = 0; i <= 26; ++i)
        for (int j = 0; j <= 26; ++j)
            if (i <= j) {
                int mask = i < j;
                ++F[i][j][mask];
                for (int opt = 1; opt < 1 << 2; ++opt) {
                    int pi, pj;
                    if (opt & 1)
                        if (i == 0) continue;
                        else pi = 27;
                    else pi = i;
                    if (opt & 2)
                        if (j == 0) continue;
                        else pj = 27;
                    else pj = j;
                    ++F[pi][pj][mask];
                }
            }
    scanf("%d", &T);
    while (T--) work();
    return 0;
}
