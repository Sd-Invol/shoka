int ncnt , scnt , bel[N] , low[N] , dfn[N];
int f[N];
stack<int> S;
void dfs(int x) {
    low[x] = dfn[x] = ++ ncnt;
    f[x] = 1;
    S.push(x);
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!dfn[y]) {
            dfs(y);
            low[x] = min(low[x] , low[y]);
        } else if (f[y]) {
            low[x] = min(low[x] , dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        do {
            int i = S.top();
            S.pop();
            f[i] = 0;
            bel[i] = scnt;
        } while (i != x);
        ++ scnt;
    }
}

memset(dfn , 0 , sizeof(dfn));
ncnt = scnt = 0;
for (int i = 1 ; i <= n ; ++ i) {
    !dfn[i] && dfs(i;
}
                    
/***********************************************/
int dfn[N] , low[N] , ncnt;
stack<int> S;
int bel[M] , tmp[N];
void dfs(int x , int fa) {
    dfn[x] = low[x] = ++ ncnt;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!dfn[y]) {
            S.push(i);
            dfs(y , i ^ 1);
            low[x] = min(low[x] , low[y]);
            if (low[y] > dfn[x]) {}//(x , y) is bridge
            if (low[y] >= dfn[x]) {
                ++ n; int j;
                do {
                    j = S.top() , S.pop();
                    if (tmp[e[j].x] != n)
                        E[m ++] = make_pair(n , e[j].x) , tmp[e[j].x] = n;
                    if (tmp[e[j ^ 1].x] != n)
                        E[m ++] = make_pair(n , e[j ^ 1].x) , tmp[e[j ^ 1].x] = n;
                    bel[j >> 1] = n;
                } while (j != i);
            }
        } else if (i != fa && dfn[y] < dfn[x])
            S.push(i) , low[x] = min(low[x] , dfn[y]);
    }
}
