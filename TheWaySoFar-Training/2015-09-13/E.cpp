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
const int N = 100005;
int n , m , Q;
struct edge {
    int x , y , w;
    bool operator < (const edge& R) const {
        return w < R.w;
    }
}e[N] , q[N] ;
LL res[N] , ans;

int f[N] , s[N];
int getf(int x) {
    return x == f[x] ? x : f[x] = getf(f[x]);
}
void merge(int x , int y) {
    x = getf(x) , y = getf(y);
    if (x == y) return;
    ans -= (LL)s[x] * (s[x] - 1);
    ans -= (LL)s[y] * (s[y] - 1);
    f[y] = x , s[x] += s[y];
    ans += (LL)s[x] * (s[x] - 1);
}

void work() {
    scanf("%d%d%d" , &n , &m , &Q);
    for (int i = 0 ; i < m ; ++ i) {
        int x , y , z;
        scanf("%d%d%d" , &x , &y , &z);
        e[i] = (edge){x , y , z};
    }
    for (int i = 0 ; i < Q ; ++ i) {
        scanf("%d" , &q[i].w);
        q[i].x = i;
    }
    sort(e , e + m);
    sort(q , q + Q);
    for (int i = 1 ; i <= n ; ++ i)
        f[i] = i , s[i] = 1;
    ans = 0;
    for (int i = 0 , j = 0; i < Q ; ++ i) {
        while (j < m && e[j].w <= q[i].w) {
            merge(e[j].x , e[j].y);
            ++ j;
        }
        res[q[i].x] = ans;
    }
    for (int i = 0 ; i < Q ; ++ i)
        printf("%lld\n" , res[i]);
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
