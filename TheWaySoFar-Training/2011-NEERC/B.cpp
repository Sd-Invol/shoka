#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;

void work() {
    int n;
    cin >> n;
    int p = 1;
    while (1 << p <= n)
        ++ p;
    -- p;
    int m = n - (1 << p);
    for (int i = 0 ; i < n - m - m ; ++ i) {
        int x = i;
        for (int j = p - 1 ; j >= 0 ; -- j)
            printf("%d" , x >> j & 1);
        puts("");
    }
    for (int i = n - m - m ; i < n - m ; ++ i) {
        int x = i;
        for (int j = p - 1 ; j >= 0 ; -- j)
            printf("%d" , x >> j & 1);
        puts("0");
        for (int j = p - 1 ; j >= 0 ; -- j)
            printf("%d" , x >> j & 1);
        puts("1");
    }

}

int main() {
    freopen("binary.in" , "r" , stdin);
    freopen("binary.out" , "w" , stdout);
    work();
    return 0;
}
