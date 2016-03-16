#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

typedef unsigned long long ULL;

const int P = 998244353;

unordered_map<ULL, int> f[2];

int trans[100000], cnt ;
int n, m, L;

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int C[100][100];

void dfs(int x, vector<int> &ver, int nex, int res, int num) {
    if (num > (m >> 1)) return ;
    if (x >= m) {
        if (num < (m >> 1)) return ;
        ULL opt = 0;
        vector<int> ver1 = ver;
        sort(ver1.begin(), ver1.end());
        for (int i = 0; i < m; ++i)
            opt |= (ULL)ver1[i] << (i * 4);
        updata(f[nex][opt], res);
        return ;
    }
    int j = x;
    while (j + 1 < m && ver[j + 1] == ver[x]) ++j;
    if (ver[x] == L) {
        dfs(j + 1, ver, nex, res, num);
        return ;
    }
    for (int i = x; i <= j + 1; ++i) {
        dfs(j + 1, ver, nex, (ULL)C[j - x + 1][i - x] * res % P, i - x + num);
        if (i <= j) ++ver[i];
    }
    for (int i = x; i <= j; ++i)
        --ver[i];
}

ULL I[20], inv[20];

int solve(int N, int M) {
    n = N;
    m = M;
    if (n < m) swap(n, m);
    L = n >> 1;
    int cur = 0, nex = 1;
    f[cur].clear();
    f[cur][0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[nex].clear();
        //printf("%d %d\n", i, (int)f[cur].size());
        for (auto x : f[cur]) {
            int res = x.second;
            ULL mask = x.first;
            vector<int> ver;
            for (int j = 0; j < m; ++j)
                ver.push_back(mask >> (j * 4) & 15);
            dfs(0, ver, nex, res, 0);
        }
        swap(cur, nex);
    }
    int ans = 0;
    ULL mask = 0;
    for (int i = 0; i < m; ++i)
        mask |= (ULL)L << (i * 4);
        ans = f[cur][mask];
    return ans;
}

int a[20][20];

int main() {
    /*for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j) {
            if (j == 0) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        }
    for (int n = 2; n <= 16; n += 2)
        for (int m = 2; m <= 16; m += 2)
        printf("a[%d][%d] = %d; \n", n, m, solve(n, m));*/
    a[2][2] = 2; 
    a[2][4] = 6; 
    a[2][6] = 20; 
    a[2][8] = 70; 
    a[2][10] = 252; 
    a[2][12] = 924; 
    a[2][14] = 3432; 
    a[2][16] = 12870; 
    a[4][2] = 6; 
    a[4][4] = 90; 
    a[4][6] = 1860; 
    a[4][8] = 44730; 
    a[4][10] = 1172556; 
    a[4][12] = 32496156; 
    a[4][14] = 936369720; 
    a[4][16] = 817760799; 
    a[6][2] = 20; 
    a[6][4] = 1860; 
    a[6][6] = 297200; 
    a[6][8] = 60871300; 
    a[6][10] = 392323778; 
    a[6][12] = 932185828; 
    a[6][14] = 944343811; 
    a[6][16] = 180846167; 
    a[8][2] = 70; 
    a[8][4] = 44730; 
    a[8][6] = 60871300; 
    a[8][8] = 169206949; 
    a[8][10] = 660469253; 
    a[8][12] = 209560164; 
    a[8][14] = 202780073; 
    a[8][16] = 710851014; 
    a[10][2] = 252; 
    a[10][4] = 1172556; 
    a[10][6] = 392323778; 
    a[10][8] = 660469253; 
    a[10][10] = 395384428; 
    a[10][12] = 821780699; 
    a[10][14] = 605240292; 
    a[10][16] = 714213243; 
    a[12][2] = 924; 
    a[12][4] = 32496156; 
    a[12][6] = 932185828; 
    a[12][8] = 209560164; 
    a[12][10] = 821780699; 
    a[12][12] = 584498879; 
    a[12][14] = 268950048; 
    a[12][16] = 673945339; 
    a[14][2] = 3432; 
    a[14][4] = 936369720; 
    a[14][6] = 944343811; 
    a[14][8] = 202780073; 
    a[14][10] = 605240292; 
    a[14][12] = 268950048; 
    a[14][14] = 55183176; 
    a[14][16] = 563571987; 
    a[16][2] = 12870; 
    a[16][4] = 817760799; 
    a[16][6] = 180846167; 
    a[16][8] = 710851014; 
    a[16][10] = 714213243; 
    a[16][12] = 673945339; 
    a[16][14] = 563571987; 
    a[16][16] = 844138055;
    freopen("enigmatic.in", "r", stdin);
    freopen("enigmatic.out", "w", stdout);
    int n, m;
    while (scanf("%d%d", &n, &m), n) {
        printf("%d\n", a[n][m]);
    }
    return 0; 
}
