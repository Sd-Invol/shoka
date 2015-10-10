#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;
const int Q = 105225319;
int n , m;
int C[N][N] , a[N] , b[N] , c[N] , power[N * N];
int inv = (Q + 1) / 2;
void work() {
    scanf("%d%d" , &n , &m);
    if (n == 1) {
        puts("0");
        return;
    }
    ++ m;
    power[0] = 1;
    for (int i = 1 ; i <= n * n ; ++ i)
        power[i] = (LL)power[i - 1] * m % Q;

    for (int i = 0 ; i <= n ; ++ i) {
        a[i] = 0;
        for (int j = 0 ; j <= i ; ++ j) {
            a[i] += (LL)C[i][j] * power[j * (i - j)] % Q;
            a[i] %= Q;
        }
       
    }
    for (int i = 0 ; i <= n ; ++ i) {
        b[i] = a[i];
        for (int j = 1 ; j < i ; ++ j) {
            b[i] += Q - (LL)C[i - 1][j - 1] * b[j] % Q * a[i - j] % Q;
            b[i] %= Q;
        }
        
    }
    c[0] = 1;
    for (int i = 1 ; i <= n ; ++ i) {
        c[i] = 0;
        for (int j = 1 ; j <= i ; ++ j) {
            c[i] += (LL)C[i - 1][j - 1] * b[j] % Q * inv % Q * c[i - j] % Q;
            c[i] %= Q;
        }
    }
    printf("%d\n" , c[n]);
}

int main() {
    for (int i = 0 ; i < N ; ++ i) {
        C[i][0] = 1;
        for (int j = 1 ; j <= i ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Q;
        }
    }
    
    int T;
    scanf("%d" , &T);
    for (int ca = 1 ; ca <= T ; ++ ca) {
        printf("Case #%d: " , ca);
        work();
    }
    return 0;
}