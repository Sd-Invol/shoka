#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;
int n , m;
vector<int> Q[N] , e[N];
vector< pair<int , int> > R[N];
int f[N];
int getf(int x) { return x == f[x] ? x : f[x] = getf(f[x]);}
int F[1 << 10];
vector<int> E[11];
void dfs(int x) {
    f[x] = x;
    for (auto y : Q[x]) {
        if (~f[y])
            R[getf(y)].push_back(make_pair(x , y));
    }
    for (auto y : e[x]) {
        if (!~f[y]) {
            dfs(y);
            f[y] = x;
        }
    }
}
int bel[N];
int DFS(int x , int fa) {
    //printf("%d %d\n" , x , fa);
    int res = 0;
    for (auto y : e[x])
        if (y != fa) {
            res += DFS(y , x);
        }
    Q[x].clear(); Q[x].push_back(x);
    memset(bel , -1 , sizeof(bel));
    int id = 0; vector<int> pe;
    for (auto y : e[x])
        if (y != fa) {
            pe.push_back(y);
            for (auto z : Q[y])
                bel[z] = id;
            ++ id;            
        }
    bel[x] = id; int mask = (1 << id) - 1;
    for (int i = 0 ; i <= id ; ++ i) E[i].clear();
    for (auto it : R[x]) {
        int y = bel[it.first] , z = bel[it.second];
        if (!~y || !~z) continue;
        E[y].push_back(z);
        E[z].push_back(y);
    }
    for (int i = 0 ; i < 1 << id ; ++ i) F[i] = -1 << 30;
    F[mask] = 0; int ans = 0;
    for (int i = mask ; i > 0 ; -- i) {
        if (F[i] < 0) continue;
        ans = max(ans , F[i]);
        for (auto y : E[id])
            if (i >> y & 1)
                F[i & ~(1 << y)] = max(F[i & ~(1 << y)] , F[i] + 1);
        for (int j = i ; j ; j &= j - 1) {
            int y = __builtin_ctz(j);
            for (auto z : E[y])
                if (i >> z & 1)
                    F[i & ~(1 << y | 1 << z)] = max(F[i & ~(1 << y | 1 << z)] , F[i] + 1);
        }
    }
    ans = max(ans , F[0]);
    for (int i = 0 ; i < 1 << id ; ++ i)
        if (F[i] == ans)
            mask &= ~i;
    for (int i = 0 ; i < id ; ++ i) {
        if (mask >> i & 1) continue;
        int z = pe[i];
        Q[x].insert(Q[x].end() , Q[z].begin() , Q[z].end());
        
    }
    return res + ans;
}

int T;
void work () {
    int i , x , y;
    scanf("%d",&n);
    ++ T;
    for (i = 1 ; i <= n ; ++ i) {
        R[i].clear();
        e[i].clear();
        Q[i].clear();
    }
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    
    scanf("%d",&m);
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d",&x,&y);
        Q[x].push_back(y);
        Q[y].push_back(x);        
    }
    memset(f , -1 , sizeof(f));
    dfs(1);
    cout << DFS(1 , 1) << endl;
}

int main () {
    int _;
    scanf("%d",&_);
    while (_ --)
        work();
    return 0;
}