#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m;
pair<int , int> a[N] , b[N];
int s[N];

int main() {
    int i , j , k;
    int sumn = 0 , summ = 0;
    scanf("%d%d",&n,&m);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d%d",&a[i].first , &a[i].second);
        sumn += a[i].second;
    }
    sort(a + 1 , a + n + 1);
    for (i = 1 ; i <= m ; ++ i)
        scanf("%d%d",&b[i].first , &b[i].second);
    sort(b + 1 , b + m + 1);
    for (i = 1 ; i <= m ; ++ i)
        s[i] = s[i - 1] + b[i].second;
    summ = s[m];
    LL res[3] = {};
    for (i = 1 ; i <= n ; ++ i) {
        j = lower_bound(b + 1 , b + m + 1 , make_pair(a[i].first , 0)) - b - 1;
        k = lower_bound(b + 1 , b + m + 1 , make_pair(a[i].first , 1 << 30)) - b - 1;
        res[0] += (LL)a[i].second * s[j];
        res[1] += (LL)a[i].second * (s[k] - s[j]);
    }
    res[2] = (LL)sumn * summ - res[0] - res[1];
    cout << res[0] << ' ' << res[1] << ' ' << res[2] << endl;
    return 0;      
}
