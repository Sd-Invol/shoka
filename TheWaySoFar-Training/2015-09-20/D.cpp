#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;
const int Q = 1e9 + 7;
const int N = 2048;
int n , m , L , R;
void FWT(int a[] , int len , int oper) {
    for (int k = 0 ; 1 << k < len ; ++ k) {
        for (int i = 0 ; i < len ; ++ i) {
            if (~i >> k & 1) {
                int j = i ^ (1 << k);
                int x = (a[i] + Q - a[j]) % Q;
                int y = (a[i] + a[j]) % Q;
                if (oper == -1) {
                    x = (Q - x) % Q;
                    swap(x , y);
                }
                a[i] = x;
                a[j] = y;
            }
        }
    }
}
int f[N] , ans[N];

int inverse(int x) {
    return x == 1 ? 1 : (LL)(Q - Q / x) * inverse(Q % x) % Q;
}
const int inv = inverse(2048);
int work() {
    int res = 0;
    n <<= 1 , n |= 1;
    for (int x = L ; x <= R ; ++ x) {
        memset(f , 0 , sizeof(f));
        for (int i = x ; i <= x + m ; ++ i)
            f[i] = 1;
        FWT(f , 2048 , 1);
        memset(ans , 0 , sizeof(ans));
        ans[0] = 1;        
        FWT(ans , 2048 , 1);
        int p = n;
        while (p) {
            if (p & 1) {
                for (int j = 0 ; j < 2048 ; ++ j) {
                    ans[j] = (LL) ans[j] * f[j] % Q;
                }
            }
            for (int j = 0 ; j < 2048 ; ++ j) 
                f[j] = (LL) f[j] * f[j] % Q;
            p >>= 1;
        }
        FWT(ans ,  2048 , -1);        
        res += (LL) ans[0] * inv % Q;
        res %= Q;
    }
    printf("%d\n" , res);    
}

int main() {
    while (~scanf("%d%d%d%d" , &n , &m , &L , &R))
        work();
    return 0;
}
