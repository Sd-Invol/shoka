#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;
const int N = 2000005;

LL a , b , c;

LL check(LL i) {
    LL num = 0;
    for (LL x = a + b ; x > 0; x /= i)
        num += x / i;
    for (LL x = a; x > 0; x /= i)
        num -= x / i;
    for (LL x = b; x > 0; x /= i)
        num -= x / i;
    return num;
}

bool f[N];
int p[N] , t;
LL A[N];
int main() {

    cin >> a >> b >> c;
    if (c >= a + b) {
        puts("YES");
        return 0;
    }
    if (c <= a + b - 1000000) {
        puts("NO");
        return 0;
    }                
    for (int i = 2 ; i < N ; ++ i) {
        if (f[i])
            continue;
        p[t ++] = i;
        if ((LL)i * i >= N)
            continue;
        for (int j = i * i ; j < N ; j += i)
            f[j] = 1;
    }
    memset(f , 0 , sizeof(f));
    LL L = c + 1 , R = a + b , m = R - L + 1;
    for (int i = 0 ; i < m ; ++ i)
        A[i] = L + i;
    for (int i = 0 ; i < t ; ++ i) {
        int x = p[i] , cnt = check(x);
        LL l = (L + x - 1) / x * x;
        while (l <= R) {
            while (A[l - L] % x == 0) {
                A[l - L] /= x;
                -- cnt;
            }
            l += x;
        }
        if (cnt < 0) {
            puts("NO");
            return 0;
        }
    }
    map<LL , int> Hash;
    for (int i = 0 ; i < m ; ++ i)
        if (A[i] > 1)
            ++ Hash[A[i]];
    for (auto &it : Hash) {
        if (check(it.first) < it.second) {
            puts("NO");
            return 0;
        }
    }        
    puts("YES");
    return 0;
}
