#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N * 20];
int deg[N][3] , f[N];
bool g[N];
void work() {
    int i , x , y;
    scanf("%d%d",&n,&m);
    memset(pre , -1 , sizeof(pre));
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d",&x,&y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
        ++ deg[x][0] , ++ deg[y][0];
    }
    queue<int> Q;
    for (i = 1 ; i <= n ; ++ i)
        if (deg[i][0] > 1)
            Q.push(i) , g[i] = 1;
    while (!Q.empty()) {
        x = Q.front() , Q.pop() , g[x] = 0;
        if (deg[x][f[x]] <= 1)
            continue;
        int c;
        if (deg[x][(f[x] + 1) % 3] < 2)
            c = (f[x] + 1) % 3;
        else if (deg[x][(f[x] + 2) % 3] < 2)
            c = (f[x] + 2) % 3;        
        for (i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            -- deg[y][f[x]];
            ++ deg[y][c];
            if (deg[y][f[y]] > 1 && !g[y])
                Q.push(y) , g[y] = 1;           
        }
        f[x] = c;
    }
    //for (i = 1 ; i <= n ; ++ i)
    //    printf("%d%c" , deg[i] , " \n"[i == n]);
    for (i = 1 ; i <= n ; ++ i)
        printf("%d%c" , f[i] + 1, " \n"[i == n]);
}

int main() {
    freopen("coloring.in" , "r" , stdin);
    freopen("coloring.out" , "w" , stdout);
    
    work();
    return 0;
}
