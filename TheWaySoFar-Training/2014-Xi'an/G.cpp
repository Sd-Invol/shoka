#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int ca;

struct PalinTree {
    char str[N];
    int n;

    int u[N][26];
    int len[N] , f[N] , cnt[N];
    int nodecnt , root;

    void init() {
        scanf("%s" , str);
        n = strlen(str);

        nodecnt = 2;
        len[1] = -1 , len[2] = 0;
        f[1] = 0 , f[2] = 1;
        memset(u[1] , 0 , sizeof(u[1]));
        memset(u[2] , 0 , sizeof(u[2]));
        root = 1;

        for (int i = 0 ; i < n ; ++ i)
            extend(i , str[i] - 'a');
    }

    void extend(int i , int c) {
        int p = root;
        while (str[i - 1 - len[p]] != str[i])
            p = f[p];
        int& pp = u[p][c];
        if (!pp) {
            pp = ++ nodecnt;
            len[pp] = len[p] + 2;
            cnt[pp] = 0;
            memset(u[pp] , 0 , sizeof(u[pp]));
            int q = f[p];
            while (q && str[i - 1 - len[q]] != str[i])
                q = f[q];
            f[pp] = q ? u[q][c] : 2;
        }
        ++ cnt[pp];
        root = pp;
    }
}S , T;

LL res;

void dfs(int p , int q) {
    if (!p || !q)
        return;
    if (p > 2 && q > 2)
        res += (LL) S.cnt[p] * T.cnt[q];
    for (int i = 0 ; i < 26 ; ++ i)
        dfs(S.u[p][i] , T.u[q][i]);
}

void work() {
    S.init();
    T.init();
    for (int i = S.nodecnt ; i > 2 ; -- i)
        S.cnt[S.f[i]] += S.cnt[i];
    for (int i = T.nodecnt ; i > 2 ; -- i)
        T.cnt[T.f[i]] += T.cnt[i];
    res = 0;
    dfs(1 , 1);
    dfs(2 , 2);
    printf("Case #%d: %I64d\n" , ++ ca , res);
}

int main() {
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}