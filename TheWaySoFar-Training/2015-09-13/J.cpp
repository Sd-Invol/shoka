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
const int N = 1005;

LL inv(LL x , LL Q) {
    x %= Q;
    return x == 1 ? x : (Q - Q / x) * inv(Q % x , Q) % Q;
}
LL C(int x , int y , LL Q) {
    if (x < y)
        return 0;
    LL res = 1;
    for (int i = y + 1 ; i <= x ; ++ i)
        res *= i , res %= Q;
    for (int i = 1 ; i <= x - y ; ++ i)
        res *= inv(i , Q) , res %= Q;
    return res;
}
LL CC(LL x , LL y , LL Q) {
    if (!x && !y)
        return 1;
    return CC(x / Q , y / Q , Q) * C(x % Q , y % Q , Q) % Q;
}
LL n , m ; int K;
void work() {
    LL pi = 1 , res = 0;
    scanf("%lld%lld%d" , &n , &m , &K);
    for (int i = 0 ; i < K ; ++ i) {
        int x;
        scanf("%d" , &x);
        int y = CC(n , m , x);
        if (!i) {
            res = y;
        } else {
            res = ((y - res % x + x) * inv(pi , x) % x) * pi + res;
        }
        pi *= x;
        res %= pi;
    }
    printf("%lld\n" , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
