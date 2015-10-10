#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
typedef long long LL;
using namespace std;
const int N = 100005;
const int Q = 1e9 + 7;

int p[N] , I[N];
int power(int A , int B) {
    if (!A) return 0;
    int res = 1;
    while (B) {
        if (B & 1)
            res = (LL)res * A % Q;
        A = (LL)A * A % Q , B >>= 1;
    }
    return res;
}
int n , ca , res;
void work() {
    printf("Case #%d: " , ++ ca);    
    scanf("%d" , &n);
    if (n == 1) {
        puts("0");
        return;
    }
    res = (LL)n * power(n - 1 , n) % Q;
    res += (LL)n * ((LL)(n - 1) * power(n - 1 , n - 2) % Q + power(n - 1 , n - 1)) % Q;
    res %= Q;
    for (int i = 2 ; i <= n ; ++ i) {
        int delta = (LL)p[n] * I[n - i] % Q;
        delta = (LL)delta * power(n - 1 , n - i) % Q;
        res += delta , res %= Q;
    }
    res = (power(n , n + 1) - res + Q) % Q;
    printf("%d\n" , res);
}

int main() {
    I[0] = I[1] = p[0] = p[1] = 1;
    for (int i = 2 ; i < N ; ++ i)
        I[i] = (LL)(Q - Q / i) * I[Q % i] % Q;
    for (int i = 2 ; i < N ; ++ i) {
        p[i] = (LL) i * p[i - 1] % Q;
        I[i] = (LL) I[i] * I[i - 1] % Q;        
    }
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}