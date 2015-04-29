#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

int n , K;
pair<LL , int> a[N];

void work() {
    int i , j , x;
    scanf("%d%d",&n,&K);
    a[1].second = 1;
    for (i = 2 ; i <= n ; ++ i) {
        scanf("%d" , &x);
        a[i] = make_pair(a[i - 1].first + x , i);
    }
    sort(a + 1 , a + n + 1);
    LL res = 1LL << 60;
    for (i = K ; i <= n ; ++ i)
        if (a[i].first - a[i - K + 1].first < res)
            res = a[i].first - a[i - K + 1].first , j = i;
    printf("%lld\n" , res);
    for (i = j - K + 1 ; i <= j ; ++ i)
        printf("%d%c" , a[i].second , " \n"[i == j]);    
}

int main() {
    work();
    return 0;
}
