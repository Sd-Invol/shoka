#include <bits/stdc++.h>
using namespace std;

const int N = 100;
const int M = 30005;

int n , ca , dep;
char g[N][N];
int U[M] , D[M] , L[M] , R[M] , col[M] , row[M];
int cnt , p[N] , s[N];

#define FOR(i,A,p) for (int i = A[p] ; i != p ; i = A[i])

void remove(int c) {
    FOR(i,D,c) L[R[i]] = L[i] , R[L[i]] = R[i];
}
void resume(int c) {
    FOR(i,U,c) L[R[i]] = R[L[i]] = i;
}
int res;
vector<int> ans , V;

int H() {
    int val = 0;
    bool u[N] = {};
    FOR (i , R , 0) if (!u[i]) {
        ++ val;
        FOR (j , D , i) FOR(k , R , j)
            u[col[k]] = 1;
    }
    return val;
}

bool dfs(int d) {
    if (d > dep)
        return 0;
    if (R[0] == 0) {
        ans = V;
        return 1;
    }
    if (d == dep)
        return 0;
    int c = R[0];
    FOR(i,R,0) if (s[i] < s[c]) c = i;
    FOR(i,D,c) {
        V.push_back(row[i]);
        remove(i);
        FOR(j,R,i) remove(j);
        if (dfs(d + 1))
            return 1;
        FOR(j,L,i) resume(j);
        resume(i);
        V.pop_back();
    }
    return 0;
}

void work() {
    int i , j , k;
    for (i = 1 ; i <= n ; ++ i)
        scanf("%s" , g[i] + 1);
    /*memset(g , '0' , sizeof(g));
    for (i = 1 ; i <= n ; ++ i)
        for (j = i + 1 ; j <= n ; ++ j)
            if (rand() % 3)
                g[i][j] = '1';
            else
            g[j][i] = '1';*/
    cnt = n + 1;
    for (i = 0 ; i <= n ; ++ i)
        L[i] = i - 1 , R[i] = i + 1;
    L[0] = n , R[n] = 0;
    memset(s , 0 ,sizeof(s));
    for (i = 1 ; i <= n ; ++ i)
        p[i] = i;
    for (i = 1 ; i <= n ; ++ i) {
        int x = -1 , y = -1;
        for (j = 1 ; j <= n ; ++ j) {
            if (i != j && g[i][j] == '0')
                continue;
            if (x == -1)
                x = y = cnt;
            else {
                L[cnt] = y , R[y] = cnt;
                y = cnt;
            }
            D[p[j]] = cnt , U[cnt] = p[j] , p[j] = cnt;
            col[cnt] = j , row[cnt] = i , s[j] ++;
            ++ cnt;
        }
        L[x] = y , R[y] = x;
    }
    for (i = 1 ; i <= n ; ++ i)
        D[p[i]] = i , U[i] = p[i];
    V.clear();
    for (dep = 1 ;  ; ++ dep) {
        if (dfs(0)) {
            res = dep;
            ans = V;
            break;
        }
    }
    printf("Case %d: %d" , ++ ca , res);
    for (i = 0 ; i < ans.size() ; ++ i)
        printf(" %d" , ans[i]);
    puts("");
}

int main() {
    while (~scanf("%d",&n))
        work();
    return 0;            
}
