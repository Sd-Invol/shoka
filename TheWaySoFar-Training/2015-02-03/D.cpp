#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5000005;
int n , m , cnt , res[N];
int pre[N] , mcnt;
struct edge {
    int x , next;
}e[N + N + N];

int get_int() {
   char ch = getchar();
   while (!isdigit(ch)) ch = getchar();
   int ret = 0;
   while (isdigit(ch)) {
      ret = ret * 10 + ch - '0';
      ch = getchar();
   }
   return ret;
}
int ncnt , first[N];
int f[N] , nxt[N] , pos[N];

void dfs(int x) {
    for (int i = first[x] ; ~i ; i = e[i].next)
        dfs(e[i].x);
    for (int i = pre[x] ; ~i ; i = e[i].next)
        res[++ cnt] = e[i].x; 
}

void work() {
    int i , j , x , y;
    scanf("%d",&n);
    memset(pre , -1 , sizeof(pre));
    for (i = 1 ; i <= n ; ++ i) {
        j = get_int();
        while (j --) {
            x = get_int();
            e[mcnt] = (edge) {i , pre[x]} , pre[x] = mcnt ++;
        }
    }
    first[0] = -1 , ncnt = 1;
    for (i = 1 ; i < N ; ++ i) {
        for (j = pre[i] ; ~j ; j = e[j].next) {
            x = e[j].x , y = pos[x];
            if (f[y] == i)
                pos[x] = nxt[y];
            else {
                f[y] = i;
                nxt[y] = ncnt , first[ncnt] = -1;
                e[mcnt] = (edge) {ncnt , first[y]} , first[y] = mcnt ++;
                pos[x] = ncnt;
                ncnt ++;
            }
        }
    }
    memset(pre , -1 , sizeof(pre));
    for (i = 1 ; i <= n ; ++ i)
        e[mcnt] = (edge) {i , pre[pos[i]]} , pre[pos[i]] = mcnt ++;
    dfs(0);
    for (i = n ; i > 0 ; -- i)
        printf("%d\n" , res[i]);
}

int main() {
    work();
    return 0;
}
