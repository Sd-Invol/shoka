#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
int n , cnt[N] , a[N];
int main() {
    int i , j;
    scanf("%d",&n);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
        ++ cnt[a[i]];
    }
    for (i = 1 ; i <= 2000000 ; ++ i)
        for (j = i + i ; j <= 2000000 ; j += i)
            cnt[i] += cnt[j];
    long long res = -n;
    for (i = 1 ; i <= n ; ++ i)
        res += cnt[a[i]];
    cout << res << endl;
    return 0;
}
