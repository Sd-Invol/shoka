#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;

int n , m , K;
pair<int , int> a[N] , s[N];
int f[21][N];
int main() {
    int i , j;
    scanf("%d%d",&n,&m);
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d" , &a[i].first , &a[i].second);
        if (a[i].first > a[i].second)
            a[i].second += n;
        a[i].second = -a[i].second;
    }
    sort(a , a + m);
    for (i = 0 ; i < m ; ++ i) {
        a[i].second = -a[i].second;
        if (!K || a[i].second > s[K - 1].second)
            s[K ++] = a[i];
    }
    m = K;
    for (i = 0 , j = 0 ; i < m ; ++ i) {
        while (j < m && s[j].first <= s[i].second + 1)
            ++ j;
        f[0][i] = j - 1;
    }
    //for (i = 0 ; i < m ; ++ i) {
    //    printf("%d : %d %d -> %d\n" , i , s[i].first , s[i].second , f[0][i]);
    // }
    for (j = 1 ; 1 << j < m ; ++ j)
        for (i = 0 ; i < m ; ++ i)
            f[j][i] = f[j - 1][f[j - 1][i]];
    int Lev = j - 1;
    int res = 1 << 30;
    for (i = 0 ; i < m ; ++ i) {
        int x = i , y = 1;
        for (j = Lev ; j >= 0 ; -- j) {
            if (s[f[j][x]].second < s[i].first + n - 1) {
                x = f[j][x];
                y += 1 << j;
            }
        }
        if (s[x].second >= s[i].first + n - 1)
            res = min(res , y);        
        if (s[f[0][x]].second >= s[i].first + n - 1)
            res = min(res , y + 1);
    }
    if (res == 1 << 30)
        puts("impossible");
    else
        cout << res << endl;
    return 0;
}
