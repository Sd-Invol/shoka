#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 105;

int main() {
    int n , z , x = 0 , y = 0 , k = 0;
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i)
        for (int j = 0 ; j < n;  ++ j) {
            scanf("%d" , &z);
            x += z;
            y += !z;
            k += !!z;
        }
    if (y > k)
        puts("-1");
    else
        printf("%d\n" , x);
    return 0;
}
