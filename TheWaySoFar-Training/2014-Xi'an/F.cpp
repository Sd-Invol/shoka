#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1000005;
const int Q = 1e9 + 7;
int ca;

LL inv[N] , p[N] , inp[N];

LL power(LL A , LL B) {
    LL res = 1;
    while (B) {
        if (B & 1)
            (res *= A) %= Q;
        (A *= A) %= Q , B >>= 1;
    }
    return res;
}
int n , m , K;
void work() {
    scanf("%d%d%d",&n,&m,&K);
    LL res1 = 1;
    for (int i = 1 ; i <= K ; ++ i) {
        (res1 *= (m - i + 1)) %= Q;
        (res1 *= inv[i]) %= Q;
    }
    LL res2 = power(K - 1 , n - 1) * K % Q;
    for (int i = 1 ; i <= K - 1 ; ++ i) {
        int x = K - i;
        LL delta = power(x - 1 , n - 1) * x % Q;
        delta = delta * p[K] % Q * inp[i] % Q * inp[x] % Q;
        if (i & 1)
            res2 = (res2 + Q - delta) % Q;
        else
            res2 = (res2 + delta) % Q;
    }
    printf("Case #%d: %I64d\n" , ++ ca , res1 * res2 % Q);
}

int main() {
    inv[1] = 1;
    for (int i = 2 ; i < N ; ++ i)
        inv[i] = (Q - Q / i) * inv[Q % i] % Q;
    p[0] = inp[0] = 1;
    for (int i = 1 ; i < N ; ++ i) {
        p[i] = p[i - 1] * i % Q;
        inp[i] = inp[i - 1] * inv[i] % Q;
    }
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
