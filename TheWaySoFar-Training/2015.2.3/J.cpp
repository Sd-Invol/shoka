#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 30005;
const int M = 4000005;

int n , m , w[N];
vector<int> E[N];
struct arc {
    int x , f , next;
}e[M];
int pre[N] , mcnt , s , t;
void addarc(int x ,int y ,int z) {
    e[mcnt] = (arc) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
int d[N] , cur[N] , q[N] , T;
bool BFS() {
    memset(d , -1 , sizeof(d));
    int top = 0 , bot = -1;
    q[++ bot] = s , d[s] = 1;
    while (top != bot + 1) {
        int x = q[top ++];
        for (int i = pre[x] ; ~i ;i = e[i].next) {
            int y = e[i].x;
            if (!~d[y] && e[i].f) {
                d[y] = d[x] + 1 , q[++ bot] = y;
                if (y == t) return 1;
            }
        }
    }
    return 0;
}
int DFS(int x , int flow = 1 << 30) {
    if (x == t || !flow) return flow;
    int sum = 0 , u;
    for (int& i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[y] == d[x] + 1 && (u = DFS(y , min(flow , e[i].f)))) {
            e[i].f -= u ,  e[i ^ 1].f += u;
            sum += u , flow -= u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}
 
int dinic() {
    int ans = 0;
    while (BFS()) {
        memcpy(cur , pre , sizeof(cur));
        ans += DFS(s);
    }
    return ans;
}

inline int id(int l , int r) {
    return l + r | l != r;
}
void build(int l , int r) {
    if (l == r) return;
    int p = id(l , r) , mid = l + r >> 1;
    addarc(p , id(l , mid) , 1 << 30) , build(l , mid);
    addarc(p , id(mid + 1 , r) , 1 << 30) , build(mid + 1 , r);
}
void query(int l , int r , int top , int bot) {
    int p = id(l , r);
    if (top <= l && r <= bot) {
        addarc(T , p , 1 << 30);
    } else {
        int mid = l + r >> 1;
        if (top <= mid) query(l , mid , top , bot);
        if (bot > mid) query(mid + 1 , r , top , bot);
    }
}

int size[N] , heavy[N] , tid[N] , Top[N] , ncnt , dep[N] , Fa[N];
void FindHE(int x , int fa , int Dep) {
    heavy[x] = 0 , size[x] = 1 , dep[x] = Dep , Fa[x] = fa;
    for (auto y : E[x])
        if (y != fa) {
            FindHE(y , x , Dep + 1);
            size[x] += size[y];
            if (!heavy[x] || size[y] > size[heavy[x]])
                heavy[x] = y;
        }	
}
void ConnectHE(int x , int anc) {
    tid[x] = ++ ncnt , Top[x] = anc;
    addarc(ncnt << 1 , t , w[x]);
    if (heavy[x])
        ConnectHE(heavy[x] , anc);
    for (auto y : E[x])
        if (y != Fa[x] && y != heavy[x])
            ConnectHE(y , y);
}
void Query(int x , int y) {
    while (Top[x] != Top[y]) {
        if (dep[Top[x]] < dep[Top[y]])
            swap(x , y);
        query(1 , n , tid[Top[x]] , tid[x]);
        x = Fa[Top[x]];
    }
    if (dep[x] > dep[y])
        swap(x , y);    
    query(1 , n , tid[x] , tid[y]);
}


void work() {
    int i , x , y , z;
    scanf("%d%d",&n,&m);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d" , &w[i]);
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        E[x].push_back(y);
        E[y].push_back(x);
    }
    memset(pre , -1 , sizeof(pre));
    s = n + n + 1 , t = s + 1;
    FindHE(1 , 0 , 0);
    ConnectHE(1 , 1);
    build(1 , n);
    for (i = 1 ; i <= m ; ++ i) {
        T = t + i;
        scanf("%d%d%d",&x,&y,&z);
        addarc(s , T , z);
        Query(x , y);
    }
    cout << dinic() << endl;
}
int main() {
    work();
    return 0;
}
