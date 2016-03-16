#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 105;
const int Q = 1e9 + 7;
int n , m , a[N];

int inverse(int x) {
    return x == 1 ? x : (LL)(Q - Q / x) * inverse(Q % x) % Q;
}
int power(int A , int B) {
    int res = 1;
    while (B) {
        if (B & 1)
            res = (LL)res * A % Q;
        A = (LL)A * A % Q , B >>= 1;
    }
    return res;
}
void work() {
    scanf("%d%d" , &n , &m);
    int sum = 0;
    for (int i = 0 ; i < m ; ++ i) {
        scanf("%d" , &a[i]);
        sum += a[i];
    }
    sum = inverse(sum);
    for (int i = 0 ; i < m ; ++ i)
        a[i] = (LL)a[i] * sum % Q;    
    int res = 0;
    for (int i = 0 ; i < m ; ++ i) {
        res += power(a[i] , n);
        res %= Q;
    }
    for (int i = 0 ; i < m ; ++ i)
        for (int j = 0 ; j < m ; ++ j) {
            if (i == j || n == 1)
                continue;
            if (a[i] == a[j]) {
                int p = power(a[i] , n);
                res += (LL)p * (n - 1) % Q;
                res %= Q;
            } else {
                int q = (LL)a[i] * inverse(a[j]) % Q;
                int p = (LL)(power(q , n - 1) + Q - 1) * inverse(q - 1) % Q;
                p = (LL)p * a[i] % Q * power(a[j] , n - 1) % Q;
                res += p , res %= Q;
            }
        }
    printf("%d\n" , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
