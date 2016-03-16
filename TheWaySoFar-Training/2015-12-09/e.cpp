#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100005;
const int Q = 1e9 + 7;
int n , m;

int I[N] , P[N];

void init() {
    I[0] = I[1] = P[0] = P[1] = 1;
    for (int i = 2 ; i < N ; ++ i)
        I[i] = (LL)(Q - Q / i) * I[Q % i] % Q;
    for (int i = 2 ; i < N ; ++ i) {
        I[i] = (LL)I[i - 1] * I[i] % Q;
        P[i] = (LL)P[i - 1] * i % Q; 
    }
}
int C(int x , int y) {
    return (LL)P[x] * I[y] % Q * I[x - y] % Q;
}
int power(int A , LL B) {
    int res = 1;
    while (B) {
        if (B & 1)
            res = (LL)res * A % Q;
        A = (LL)A * A % Q , B >>= 1;
    }
    return res;
}
int f[N] , g[N] , h[N];

int main() {
    init();
    f[1] = g[1] = 1;
    for (int i = 2 ; i < N ; ++ i) {
        g[i] = power(2 , (LL)i * (i - 1) / 2);
        for (int j = 1 ; j < i ; ++ j) {
            f[i] += (LL)C(i , j) * f[j] % Q * g[i - j] % Q;
            f[i] %= Q;
        }
        f[i] = (g[i] + Q - f[i]) % Q;
    }
    h[0] = 1;
    for (int i = 1 ; i < N ; ++ i) {
        for (int j = 1 ; j <= i ; ++ j) {
            h[i] += (LL)C(i , j) * (g[i - j] + h[i - j]) % Q * f[j] % Q;
            h[i] %= Q;
        }
        printf("%d," , h[i]);
    }        
    return 0;
}
