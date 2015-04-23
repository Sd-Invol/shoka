#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 60000;

char str[N];
int pre[N] , mcnt , len , res[N];
struct edge {
    int x , next;
}e[N];

void dfs(int x) {
    for (int& i = pre[x] ; ~i ; ) {
        int y = e[i].x;
        int c = i;
        i = e[i].next;
        dfs(y);
        res[len ++] = c;
    }
}

void work() {
    int n , m , i , j;
    cin >> n >> m;
    memset(pre , -1 , sizeof(pre));
    for (i = 0 ; i < 19683 ; ++ i) {
        for (j = 0 ; j < 3 ; ++ j) {
            int x = (i * 3 + j) % 19683;
            e[mcnt] = (edge) {x , pre[i]} , pre[i] = mcnt ++;
        }
    }
    dfs(0);
    reverse(res , res + len);
    for (i = 0 ; i < len ; ++ i) {
        str[res[i]] = "flr"[res[(i + 1) % len] % 3];
    }
    puts(str);
}

int main() {
    freopen("cleaning-robot.in" , "r" , stdin);
    freopen("cleaning-robot.out" , "w" , stdout);

    work();
    return 0;
}
