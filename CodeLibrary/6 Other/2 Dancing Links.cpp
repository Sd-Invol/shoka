int U[M] , D[M] , L[M] , R[M], col[M] , row[M];
int cnt , p[N] , s[N];

#define FOR(i,A,s) for (int i = A[s]; i != s ; i = A[i])
//由矩阵建立十字链表
cnt = n + 1;
for (i = 0 ; i <= n ;i ++)
    L[i] = i - 1 , R[i] = i + 1;
memset(s , 0 , sizeof(s));
L[0] = n , R[n] = 0;
for (i = 1 ; i <= n ; i ++)
    p[i] = i;
for (i = 1 ; i <= n ; ++ i) {
    x = y = -1;
    for (j = 1 ; j <= n ;j ++)
        if (g[i][j]) {
            if (x == -1)
                x = cnt , y = cnt;
            else
                L[cnt] = y , R[y] = cnt , y = cnt;
            D[p[j]] = cnt , U[cnt] = p[j]  , p[j] = cnt;
            col[cnt] = j , row[cnt] = i, s[j] ++;
            ++ cnt;
        }
    L[x] = y , R[y] = x;
}
for (i = 1 ; i <= n ;i ++)
    D[p[i]] = i , U[i] = p[i];
//可重复覆盖：
void remove(int c) {
    FOR(i,D,c) L[R[i]] = L[i] , R[L[i]] = R[i];
}
void resume(int c) {
    FOR(i,U,c) L[R[i]] = R[L[i]] = i;
}
int H() {
    int val = 0; bool u[N] = {0};
    FOR(i,R,0) if (!u[i]) {
        ++ val;
        FOR (j,D,i) FOR(k,R,j)
            u[col[k]] = 1;
    }
    return val;
}
bool dfs(int d) {
    if (d + H() > K)return 0 ;
    if (R[0] == 0) {
        return 1;
    }
    int c = R[0];
    FOR(i,R,0) if (s[i] < s[c]) c = i;
    FOR(i,D,c) {
        remove(i);
        FOR(j,R,i) remove(j);
        if (dfs(d + 1))
            return 1;
        FOR(j,L,i) resume(j);
        resume(i);
    }
    return 0;
}
//精确覆盖
void remove(int c) {
    L[R[c]] = L[c] , R[L[c]] = R[c];
    FOR(i,D,c) FOR(j,R,i)
        U[D[j]] = U[j] , D[U[j]] = D[j] , -- s[col[j]];
}
void resume(int c) {
    FOR(i,U,c) FOR(j,L,i)
        U[D[j]] = D[U[j]] = j , ++ s[col[j]];
    L[R[c]] = R[L[c]] = c;
}

bool dfs(int d) {
    if (R[0] == 0)
        return 1;
    int c = R[0];
    FOR(i,R,0) if (s[i] < s[c]) c = i;
    remove(c);
    FOR(i,D,c) {
        ans.pb(row[i]);
        FOR(j,R,i) remove(col[j]);
        if (dfs(d + 1)) return 1;
        FOR(j,L,i) resume(col[j]);
        ans.pop_back();
    }
    resume(c);
    return 0;
}

