#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
int ca;

int n , a[N];


void work() {
    int i;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i)
        scanf("%d" , &a[i]);
    for (i = 0 ; i < n ; ++ i)
        if (a[i] % 3)
            break;
    printf("Case #%d: " , ++ ca);
    puts(i < n ? "No" : "Yes");
}

int main() {
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
