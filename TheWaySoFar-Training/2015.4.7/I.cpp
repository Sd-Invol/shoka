#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2000005;
int n , cnt , m;
int f[N] , s[N] , u[N][26] , pos[N];
char str[N];
vector<int> e[N];
int L[N] , R[N] , ncnt;
LL sum[N];
void dfs(int x) {
    for (int i = 0 ; i < 26 ; ++ i) {
        int y = u[x][i];
        if (!y) continue;
        dfs(y);
        s[x] += s[y];
    }
}
void DFS(int x) {
    L[x] = ++ ncnt;
    sum[ncnt] = sum[ncnt - 1] + s[x];
    for (auto y : e[x])
        DFS(y);
    R[x] = ncnt;
}

void work() {
    int i , j , x , y;
    scanf("%d",&n);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d%s%d" , &j , str , &s[i]);
        u[j][*str - 'a'] = i;
    }
    cnt = n + 1;
    scanf("%d" , &m);
    for (i = 0 ; i < m ; ++ i) {
        scanf("%s" , str);
        x = 0;
        for (j = 0 ; str[j] ; ++ j) {
            int c = str[j] - 'a';
            if (!u[x][c])
                u[x][c] = cnt ++;
            x = u[x][c];
        }
        pos[i] = x;
    }
    dfs(0);
    queue<int> Q;
    for (i = 0 ; i < 26 ; ++ i)
        if (u[0][i])
            Q.push(u[0][i]);
    while (!Q.empty()) {
        x = Q.front() , Q.pop();
        for (i = 0 ; i < 26 ; ++ i) {
            y = u[x][i];
            if (!y) {
                u[x][i] = u[f[x]][i];               
            } else {
                Q.push(y);
                j = f[x];
                while (j && !u[j][i])
                    j = f[j];
                f[y] = u[j][i];
            }
        }
    }    
    for (i = 1 ; i < cnt ; ++ i)
        e[f[i]].push_back(i);
    DFS(0);
    for (i = 0 ; i < m ; ++ i) {
        x = pos[i];
        printf("%lld\n" , sum[R[x]] - sum[L[x] - 1]);
    }
}

int main() {
    work();
    return 0;
}
