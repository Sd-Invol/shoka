#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 10005;
const int Q = 1e9 + 7;
int ca;
LL n , m , b1 , d , a1 , q;
LL inverse(LL x) {
    x %= Q;
    return x == 1 ? x : (Q - Q / x) * inverse(Q % x) % Q;
}
LL power(LL A , LL B) {
    LL res = 1;
    while (B) {
        if (B & 1)
            res *= A , res %= Q;
        A *= A , A %= Q , B >>= 1;
    }
    return res;
}
LL C[N];
void work() {
    scanf("%lld%lld%lld%lld%lld%lld" , &b1 , &q , &a1 , &d , &n , &m);
    C[n] = 1;
    for (int i = n - 1 ; i >= 1 ; -- i) {
        C[i] = C[i + 1] * (n + m - i - 1) % Q * inverse(n - i) % Q;
    }    
    LL res = 0;
    LL inv = inverse(q - 1);
    for (int i = 1 ; i <= n ; ++ i) {
        LL x = (a1 + (i - 1) * d) % Q;
        res += x * C[i] % Q , res %= Q;
        
        LL delta = (Q - b1 * inv % Q) % Q;
        res += delta * C[i] % Q , res %= Q;
        b1 *= inv * q % Q , b1 %= Q;        
    }
    res += b1 * power(q , m - 1) % Q , res %= Q;
    printf("Case #%d: %lld\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        work();
    }
    return 0;
}