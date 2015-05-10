#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int N = 205;
const ULL M = 1ULL << 63;
ULL C[N][N];
bool f[N];
int p[N] , tot;
map<ULL , ULL> Hash;

void dfs(int k , ULL x , ULL y , int cnt , int lim) {
    if (lim == 0) {
        if (y == 1)
            return;
        if (!Hash.count(x))
            Hash[x] = y;
        else
            Hash[x] = min(Hash[x] , y);
        return;
    }
    ULL z = 1;
    for (int i = 0 ; i <= lim ; ++ i) {        
        if (y >= (M + z - 1) / z)
            break;
        if (x >= (M + C[cnt + i][i] - 1) / C[cnt + i][i])
            break;
        dfs(k + 1 , x * C[cnt + i][i] , y * z , cnt + i , i);
        z *= p[k];
    }    
}

void init() {
    for (int i = 0 ; i < N ; ++ i) {
        C[i][0] = 1;
        for (int j = 1 ; j <= i ; ++ j) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            C[i][j] = min(C[i][j] , M - 1);
        }
    }
    for (int i = 2 ; i < N ; ++ i) {
        if (f[i]) continue;
        p[tot ++] = i;
        for (int j = i * i ; j < N ; j += i)
            f[j] = 1;
    }
    dfs(0 , 1 , 1 , 0 , 63);
    ULL n;
    while (cin >> n)
        cout << n << ' ' << Hash[n] << endl;
}

int main() {
    init();
    return 0;
}
