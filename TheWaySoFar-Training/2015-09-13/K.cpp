#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const int N = 1e6+5;
typedef __int128 LL;

int p[N] , tot;
bool f[N];
void RD(LL& x) {
    x = 0; char c;
    for (c = getchar() ;!isdigit(c) ; c = getchar()); x = c - '0';
    for (c = getchar() ; isdigit(c) ; c = getchar()) x = x * 10 + c - '0';
}

void init() {
    for (int i = 2 ; i * i < N ; ++ i) {
        if (f[i]) continue;
        for (int j = i * i ; j < N ; j += i)
            f[j] = 1;
    }
    for (int i = 2 ; i < N ; ++ i)
        if (!f[i])
            p[tot ++] = i;
}

LL SQRT(LL n) {
    LL l = 1 , r = 1e12 , m;
    while (l < r) {
        m = l + r + 1 >> 1;
        if (m * m <= n)
            l = m;
        else
            r = m - 1;
    }
    return l;
}
LL TRI(LL n) {
    LL l = 1 , r = 1e8 , m;
    while (l < r) {
        m = l + r + 1 >> 1;
        if (m * m * m <= n)
            l = m;
        else
            r = m - 1;
    }
    return l;
}


bool Rabin_Miller(LL n) {
    long long m = n;
    for (int i = 0 ; i < tot && (long long)p[i] * p[i] <= m ; ++ i)
        if (m % p[i] == 0)
            return 0;
    return 1;
}

int check(LL Z) {
    if (Z == 1)
        return 1;
    int flag = 1;
    LL p = SQRT(Z);
    if (Rabin_Miller(p) && p * p == Z)
        flag = 2;
    p = TRI(Z);
    if (Rabin_Miller(p) && p * p * p == Z)
        flag = 3;
    return flag;
}
void work() {
    LL X , Y;
    long long res1 = 1 , res2 = 1;
    RD(X) , RD(Y);

    for (int i = 0 ; i < tot ; ++ i) {
        if (X % p[i] == 0) {
            int c = 0;
            while (X % p[i] == 0)
                X /= p[i] , ++ c;
            res1 *= c;
        }
    }
    for (int i = 0 ; i < tot ; ++ i) {
        if (Y % p[i] == 0) {
            int c = 0;
            while (Y % p[i] == 0)
                Y /= p[i] , ++ c;
            res2 *= c;
        }
    }
    LL Z = __gcd(X , Y);
    if (Z > 1) {

        int flag = check(Z);
        if (flag == 2)
            Z = SQRT(Z);
        if (flag == 3)
            Z = TRI(Z);
        int cnt = 0;
        while (X % Z == 0) {
            X /= Z;
            ++ cnt;
        }
        res1 *= cnt;
        cnt = 0;
        while (Y % Z == 0) {
            Y /= Z;
            ++ cnt;
        }
        res2 *= cnt;
        res1 *= check(X);
        res2 *= check(Y);
    }

    printf("%lld %lld\n" , res1 , res2);
}

int main() {
    init();
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
