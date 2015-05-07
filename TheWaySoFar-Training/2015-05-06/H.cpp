#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n , m , K , pre[N] , mcnt , ca;
struct edge {
    int x , next;
}e[N];
pair<int , int> E[N];
int dfn[N] , low[N] , ncnt , res[N];
stack<int> S;
int tmp[N] , deg[N];

void dfs(int x , int fa) {
    dfn[x] = low[x] = ++ ncnt;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!dfn[y]) {
            S.push(i);
            dfs(y , i ^ 1);
            low[x] = min(low[x] , low[y]);
            if (low[y] >= dfn[x]) {
                ++ n; int j;
                do {
                    j = S.top() , S.pop();
                    if (tmp[e[j].x] != n)
                        E[m ++] = make_pair(n , e[j].x) , tmp[e[j].x] = n;
                    if (tmp[e[j ^ 1].x] != n)
                        E[m ++] = make_pair(n , e[j ^ 1].x) , tmp[e[j ^ 1].x] = n;
                } while (j != i);
            }
        } else if (i != fa && dfn[y] < dfn[x])
            S.push(i) , low[x] = min(low[x] , dfn[y]);
    }
}

void work() {
    int i , j , x , y;
    printf("Case %d: " , ++ ca);
    n = 0;
    memset(pre , -1 , sizeof(pre)) , mcnt = 0;
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d" , &x , &y);
        n = max(n , max(x , y));
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    memset(dfn , 0 , sizeof(dfn));
    memset(tmp , 0 , sizeof(tmp));
    ncnt = m = 0 , K = n;
    for (i = 1 ; i <= K ; ++ i)
        if (!dfn[i])
            dfs(i , -1);
    if (n == K + 1) {
        printf("%d %lld\n" , 2 , (long long)K * (K - 1) / 2);
        return;
    }
    memset(deg , 0 , sizeof(deg));
    for (i = 0 ; i < m ; ++ i) {
        if (E[i].first > E[i].second)
            swap(E[i].first , E[i].second);
        ++ deg[E[i].first];
        ++ deg[E[i].second];        
    }
    memset(res , 0 , sizeof(res));
    for (i = 0 ; i < m ; ++ i) {
        if (deg[E[i].first] > 1)
            ++ res[E[i].second];
    }
    int cnt = 0;
    long long ret = 1;
    for (i = K + 1 ; i <= n ; ++ i)
        if (res[i] == 1) {
            ++ cnt;
            ret *= (deg[i] - 1);
        }
    printf("%d %lld\n" , cnt , ret);
}
int main() {
    while (scanf("%d" , &m) , m)
        work();
    return 0;
}
