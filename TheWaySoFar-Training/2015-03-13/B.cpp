#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

char str[N];
int n;

int u[N][4];
int len[N] , f[N];
int nodecnt , root;
void extend(int i , int c) {
    int p = root;
    while (str[i - 1 - len[p]] != str[i])
        p = f[p];
    int& pp = u[p][c];
    if (!pp) {
        pp = ++ nodecnt;
        len[pp] = len[p] + 2;
        memset(u[pp] , 0 , sizeof(u[pp]));
        int q = f[p];
        while (q && str[i - 1 - len[q]] != str[i])
            q = f[q];
        f[pp] = q ? u[q][c] : 2;
    }
    root = pp;
}

int g[N] , h[N] , p[N];
vector<int> e[N] , S;

void dfs(int x , int j) {
    if (~len[x] & 1) {
        S.push_back(x);
        while (j < S.size() && len[S[j]] <= len[x] / 2)
            ++ j;
        p[x] = j ? S[j - 1] : 0;
    }
    for (auto y : e[x])
        dfs(y , j);
   if (~len[x] & 1)
       S.pop_back();
}

void work() {
    scanf("%s" , str);
    n = strlen(str);
    nodecnt = 2;
    len[1] = -1 , len[2] = 0;
    f[1] = 0 , f[2] = 1;
    memset(u[1] , 0 , sizeof(u[1]));
    memset(u[2] , 0 , sizeof(u[2]));
    root = 1;
    for (int i = 0 ; i < n ; ++ i) {
        int j;
        if (str[i] == 'A') j = 0;
        if (str[i] == 'G') j = 1;
        if (str[i] == 'C') j = 2;
        if (str[i] == 'T') j = 3;        
        extend(i , j);
    }
    for (int i = 1 ; i <= nodecnt ; ++ i)
        e[i].clear();
    for (int i = 1 ; i <= nodecnt ; ++ i)
        e[f[i]].push_back(i);
    dfs(2 , 0);
    memset(g , 63 , nodecnt + 1 << 2);
    memset(h , 63 , nodecnt + 1 << 2);
    g[2] = h[2] = 0;
    int res = h[0];
    for (int i = 2 ; i <= nodecnt ; ++ i) {
        if (len[i] & 1) continue;
        int x = f[i];
        g[i] = min(g[i] , g[x] + len[i] - len[x]);
        x = p[i];
        h[i] = min(h[i] , g[x] + len[i] / 2 - len[x]);
        g[i] = min(g[i] , h[i] + 1);
        for (int j = 0 ; j < 4 ; ++ j) {
            x = u[i][j];
            if (!x) continue;
            h[x] = min(h[x] , h[i] + 1);
            g[x] = min(g[x] , g[i] + 2);            
        }
        res = min(res , g[i] + n - len[i]);
    }
    cout << res << endl;
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
