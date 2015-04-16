#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
const int Q = 1e9 + 7;
int n , m , f[N];
int dep[N];

void work() {
    int i , j , k;
    scanf("%d%d" , &n,&m);
    LL res = m;
    for (i = 2 ; i <= n ; ++ i)
        scanf("%d" , &f[i]);
    dep[0] = 1;
    for (i = 1 ; i < n ; ++ i) {
        j = f[i];
        if (f[i + 1]) {
            dep[i] = dep[j];
        } else {
            dep[i] = dep[j] + 1;
            res *= m - dep[j];
            res %= 1000000007;            
        }
    }
    cout << res << endl;
}

int main() {
    work();
    return 0;
}
