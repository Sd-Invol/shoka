#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 300005;

int n , m , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 1];
int f[19][N] , dep[N] , L[N] , R[N] , ncnt;
int Lev; 
void dfs(int x , int fa) {
    L[x] = ++ ncnt;
    dep[x] = dep[fa] + 1;
    f[0][x] = fa;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            dfs(y , x);
        }
    }
    R[x] = ncnt;
}
int LCA(int x , int y) {
    if (dep[x] < dep[y]) swap(x , y);
    for (int i = Lev ; i >= 0 ; -- i)
        if (dep[x] - dep[y] >> i & 1)
            x = f[i][x];
    if (x == y) return x;
    for (int i = Lev ; i >= 0 ; -- i)
        if (f[i][x] != f[i][y])
            x = f[i][x] , y = f[i][y];
    return f[0][x];
}
inline int dist(int x , int y) {
    int z = LCA(x , y);
    return dep[x] + dep[y] - dep[z] - dep[z];
}
vector< pair<int , int> > V[N] , W[N];
bool vis[N];
int c[N] , lim;
inline void add(int x , int w) {
    x = L[x];
    while (x <= n) {
        c[x] += w;
        x += x & -x;
    }
}
inline int get(int x) {
    int i = R[x] , res = 0;
    while (i > 0) {
        res += c[i];
        i -= i & -i;
    }
    i = L[x] - 1;
    while (i > 0) {
        res -= c[i];
        i -= i & -i;
    }
    return res;
}

void DFS(int x ,int root , int ban) {
    if (vis[x] || x == ban) return;
    vis[x] = 1;
    for (auto it : V[x]) {
        int y = it.first;
        if (!vis[y]) continue;
        int Dist = dist(x , root) + dist(y , root);
        lim = min(lim , it.second - Dist >> 1);
    }
    for (int i = pre[x] ; ~i ; i = e[i].next)
        DFS(e[i].x , root , ban);
}

void work() {
    int i , j , k , x , y , z;
    scanf("%d%d",&n,&m);
    memset(pre , -1 , n + 1 << 2);
    mcnt = 0;
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d" , &x , &y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    ncnt = 0;
    dep[0] = -1;
    dfs(1 , 0);
    for (j = 1 ; 1 << j < n ; ++ j)
        for (i = 1 ; i <= n ; ++ i)
            f[j][i] = f[j - 1][f[j - 1][i]];
    Lev = j - 1;
    for (i = 1 ; i <= n ; ++ i) {
        V[i].clear() , W[i].clear();
        vis[i] = c[i] = 0;
    }
    int root = 1 , Dep = 0;
    lim = 1 << 30;
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d%d",&x,&y,&z);
        V[x].push_back(make_pair(y , z));
        V[y].push_back(make_pair(x , z));     
        int Dist = dep[x] + dep[y];
        if (Dist > z) {        
            add(x , 1) , add(y , 1);
            W[Dist - z + 1 >> 1].push_back(make_pair(x , y));
        }
    }

    while (1) {
        x = root;
        int cnt = 0 , node = -1;
        for (i = pre[x] ; ~i ; i = e[i].next) {
            y = e[i].x;
            if (y != f[0][x]) {
                if (get(y)) {
                    ++ cnt;
                    node = y;
                }
            }
        }
        y = node;
        if (!cnt) {
            printf("TAK %d\n" , x);
            return;
        }
        if (cnt > 1) {
            puts("NIE");
            return;
        }
        ++ Dep;
        for (auto it : W[Dep]) {
            add(it.first , -1);
            add(it.second , -1);
        }
        DFS(x , x , y);
        
        if (lim <= 0) {
            puts("NIE");
            return;
        }
        -- lim;
        root = y;
        
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
