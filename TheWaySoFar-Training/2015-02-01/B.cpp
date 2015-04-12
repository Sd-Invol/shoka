#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 45;
const int Q = 1e9 + 7;
int n , m , pre[N] , mcnt;
int w[105][4];
struct edge {
    int x , next;
}e[205];

int f[N];
bool vis[N];
vector<int> a[2];
LL cnt[N][2];
void dfs(int x , int c) {
    if (~f[x]) return;
    f[x] = c; a[c].push_back(x);
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        dfs(y , !c);
    }
}
void work() {
    int i , j , k , l , x , y;
    scanf("%d%d",&n,&m);
    memset(pre , -1 , sizeof(pre));
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d" , &x , &y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
        for (j = 0 ; j < 4 ; ++ j)
            scanf("%d" , &w[i][j]);
    }
    memset(f , -1 , sizeof(f));
    vector<int> V;
    for (i = 1 ; i <= n ; ++ i) {
        if (~f[i])
            continue;
        a[0].clear();
        a[1].clear();        
        dfs(i , 0);
        if (a[0].size() <= a[1].size())
            V.insert(V.end() , a[0].begin() , a[0].end());
        else
            V.insert(V.end() , a[1].begin() , a[1].end());
    }
    memset(f , 0 , sizeof(f));    
    m = V.size();
    for (i = 0 ; i < m ; ++ i) 
        f[V[i]] = 1;        
    LL res = 0;
    for (j = 0 ; j < 1 << m ; ++ j) {
        for (i = 1 ; i <= n ; ++ i)
            cnt[i][0] = cnt[i][1] = 1;
        for (k = 0 ; k < m ; ++ k) {
            x = V[k] , l = (j >> k & 1);
            for (i = pre[x] ; ~i ; i = e[i].next) {
                y = e[i].x;
                if (~i & 1) {
                    cnt[y][0] *= w[i >> 1][l << 1 | 0];
                    cnt[y][1] *= w[i >> 1][l << 1 | 1];
                } else {
                    cnt[y][0] *= w[i >> 1][0 << 1 | l];
                    cnt[y][1] *= w[i >> 1][1 << 1 | l];
                }
                cnt[y][0] %= Q;
                cnt[y][1] %= Q;                
            }
        }
        LL delta = 1;
        for (i = 1 ; i <= n ; ++ i)
            if (!f[i]) {
                delta *= (cnt[i][0] + cnt[i][1]);
                delta %= Q;
            }
        res += delta;
        res %= Q;
    }
    cout << res << endl;        
}

int main() {
    work();    
    return 0;
}
