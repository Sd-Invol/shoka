#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m , K , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 2];
int dep[N] , f[17][N];
int go[N] , cnt , bel[N] , length[N];

int getKth(int x , int K) {
    for (int i = 16 ; i >= 0 ; -- i)
        if (K >> i & 1)
            x = f[i][x];
    return x;
}

void addloop(int x , int y) {
    if (bel[x]) return;
    int u = x , v = y;
    ++ cnt;
    while (x != y) {
        if (dep[x] > dep[y]) {
            go[x] = v;
            bel[x] = cnt;
            x = f[0][x];
        } else {
            go[y] = u;
            bel[y] = cnt;
            y = f[0][y];
        }
        length[cnt] ++;
    }
    length[cnt] ++;
    bel[x] = cnt;
}

int LCA(int x , int y) {
    if (dep[x] < dep[y])
        swap(x , y);
    x = getKth(x , dep[x] - dep[y]);
    if (x == y) return y;
    for (int i = 16 ; i >= 0 ; -- i)
        if (f[i][x] != f[i][y])
            x = f[i][x] , y = f[i][y];
    return f[0][x];
}

int gotoloop(int x , int z) {
    if (!bel[z])
        return z;
    if (bel[z] == bel[x])
        return x;
    for (int i = 16 ; i >= 0 ; -- i)
        if (dep[f[i][x]] >= dep[z] && bel[f[i][x]] != bel[z])
            x = f[i][x];
    return f[0][x];
}

int midpoint(int x , int y) {
    int z = LCA(x , y);
    int u = gotoloop(x , z) , v = gotoloop(y , z);
    int len1 = dep[u] + dep[v] - dep[z] - dep[z];
    int len2 = !bel[z] ? 1 << 30 : length[bel[z]] - len1;

    if (len1 <= len2) {
        int mid = (dep[x] + dep[y] - dep[z] - dep[z]) / 2;
        if (dep[x] - dep[z] >= mid)
            return getKth(x , mid);
        else
            return getKth(y , mid);
    } else {
        int mid = (dep[x] + dep[y] - dep[u] - dep[v] + len2) / 2;
        int p = go[v] , q = go[u];
        if (dep[x] + dep[p] - dep[u] - dep[u] >= mid) {
            if (dep[x] - dep[u] >= mid)
                return getKth(x , mid);
            else {
                mid = dep[x] + dep[p] - dep[u] - dep[u] - mid;
                return getKth(p , mid);
            }
        } else {
            if (dep[y] - dep[v] >= mid)
                return getKth(y , mid);
            else {
                mid = dep[y] + dep[q] - dep[v] - dep[v] - mid;
                return getKth(q , mid);
            }
        }
    }
}

void work() {
    int i , j , x , y , z;
    scanf("%d%d",&n,&m);
    memset(pre , -1 , sizeof(pre));
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d" , &x , &y);
        ++ x , ++ y;
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    queue<int> Q;
    memset(dep , -1 , sizeof(dep));
    Q.push(1) , dep[1] = 1;
    while (!Q.empty()) {
        x = Q.front() , Q.pop();
        for (j = 1 ; j <= 16 ; ++ j)
            f[j][x] = f[j - 1][f[j - 1][x]];
        for (i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (!~dep[y]) {
                dep[y] = dep[x] + 1;
                f[0][y] = x;
                Q.push(y);
            } else if (y != f[0][x]) {
                addloop(x , y);
            }
        }
    }

    scanf("%d" , &K);
    int cur = 1 , nxt;
    for (j = 0 ; j < K ; ++ j) {
        scanf("%d" , &nxt);
        printf("%d" , midpoint(cur , ++ nxt) - 1);
        putchar(" \n"[j + 1 == K]);
        cur = nxt;
    }
}

int main() {
    work();
    return 0;
}
