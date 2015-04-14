#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 1];
int dep[N] , fa[N] , f[N];
void dfs(int x , int F , int d) {
    fa[x] = F;
    dep[x] = d;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != F) {
            dfs(y , x , d + 1);
        }
    }
}

int main() {
    int i , x , y;
    scanf("%d" , &n);
    memset(pre , -1 , sizeof(pre));
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    dfs(1 , 0 , 0);
    f[1] = 1;
    int cnt = 1;
    scanf("%d" , &m);
    for (i = 1 ; i <= m ; ++ i) {
        scanf("%d" , &x) , y = x;
        while (!f[x]) {
            f[x] = 1;
            ++ cnt;
            x = fa[x];
        }
        //cout << cnt << endl;
        printf("%d%c" , cnt + cnt - 2 - dep[y] , " \n"[i == m]);
    }
        
}
