#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1605;


void work() {
    int n , i;
    scanf("%d",&n);
    n *= 2;
    for (i = 2 ; i * i <= n ; ++ i) {
        if (n % i == 0) {
            int x = i;
            int y = n / i;
            int a = x + y;
            if (~a & 1)
                continue;
            a = a - 1 >> 1;
            int b = y - x;
            if (~b & 1)
                continue;
            b = b + 1 >> 1;
            printf("%d = %d" , n >> 1 , b);
            //10 = 1 + 2 + 3 + 4
            for (int j = b + 1; j <= a ; ++ j) {
                printf(" + %d" , j);
            }
            puts("");
            return;
        }
    }
    puts("IMPOSSIBLE");
}

int main() {
    int _; scanf("%d",&_);
    while (_ --)
        work();
    return 0;
}
