#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 5e5 + 5;
const int Q = 1e9 + 7;
typedef long long LL;

int f[N] , n , s[N];
int p[N];

int cal(int L , int R) {
    LL res = 0;
    res += (LL)R * (R + 1) / 2;
    res -= (LL)L * (L + 1) / 2;
    return res % Q;
}

void init() {
    f[1] = 1;
    s[1] = 1;
    f[2] = 2;
    s[2] = 3;

    for (int i = 3 , j = 1 ; i < N ; ++ i) {
        while (s[j] < i)
            ++ j;
        f[i] = j;
        s[i] = s[i - 1] + j;
    }
    for (int i = 1 ; i < N ; ++ i) {
        p[i] = p[i - 1] + (LL)cal(s[i - 1] , s[i]) * i % Q;
        p[i] %= Q;
    }
}

void work() {
    scanf("%d" , &n);
    int res = 0;
    int i = upper_bound(s , s + N , n) - s - 1;
    res = p[i];
    res += (LL)cal(s[i] , n) * (i + 1) % Q;
    res %= Q;
    printf("%d\n" , res);
}


int main() {
    int T;
    init();
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
