#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
int n , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 1];
vector<int> leaf;

void dfs(int x , int fa) {
    if (!~e[pre[x]].next)
        leaf.push_back(x);
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa)
            dfs(y , x);
    }
}

void work() {
    int i , x , y;
    scanf("%d",&n);
    memset(pre , -1 , sizeof(pre));
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    dfs(1 , 0);
    x = leaf.size() >> 1;
    printf("%d\n" , (int)leaf.size() - x);
    for (i = 0 ; i + x < leaf.size() ; ++ i)
        printf("%d %d\n" , leaf[i] , leaf[i + x]);
}

int main() {
    freopen("kingdom.in" , "r" , stdin);
    freopen("kingdom.out" , "w" , stdout);
    work();
    return 0;
}
