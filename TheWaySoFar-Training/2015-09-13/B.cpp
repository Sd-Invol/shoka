#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <cctype>
#include <map>
using namespace std;
typedef long long LL;
const int N = 10005;
int n , m , pre[N] , mcnt , v[N];
int deg[N];

struct edge {
    int x , next;
}e[N * 20];
bool del[N];
LL sum; int cnt;

void dfs(int x) {
    if (del[x]) return;
    del[x] = 1; sum += v[x] , ++ cnt;
    for (int i = pre[x] ; ~i ; i = e[i].next)
        dfs(e[i].x);
}

void work() {
    scanf("%d%d" , &n , &m);
    memset(pre , -1 , sizeof(pre));
    memset(deg , 0 , sizeof(deg));
    mcnt = 0;
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d" , &v[i]);
    for (int i = 0 ; i < m ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        e[mcnt] = (edge){y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge){x , pre[y]} , pre[y] = mcnt ++;
        ++ deg[x] , ++ deg[y];
    }
    queue<int> Q;
    memset(del , 0 , sizeof(del));
    for (int i = 1 ; i <= n ; ++ i) {
        if (deg[i] == 1) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        del[x] = 1;
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (deg[y] > 1) {
                -- deg[x];
                -- deg[y];
                if (deg[y] == 1) {
                    Q.push(y);
                }
            }
        }
    }
    LL res = 0;
    for (int i = 1 ; i <= n ; ++ i) {
        if (!del[i]) {
            cnt = sum = 0;
            dfs(i);
            if (cnt > 1 && (cnt & 1))
                res += sum;
        }
    }
    printf("%lld\n" , res);
}

extern int main2(void) __asm__ ("main2");
int main() {
    int __size__ = 256 << 20;  // 256Mb
    char *p = (char *)malloc(__size__) + __size__;
    __asm__ __volatile__(
        "movq  %0, %%rsp\n"
        "pushq $exit\n"
        "jmp main2\n"
        :: "r"(p));
    return 0;
}
int main2() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
