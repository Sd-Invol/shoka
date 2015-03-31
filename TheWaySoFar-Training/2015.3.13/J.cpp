#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
typedef long long LL;

int n , m , s , c[2];
pair<int , int> a[N];

void work() {
    int i , j , x , y;
    char str[10];
    scanf("%d",&n) , s = 0 , m = 0;
    c[0] = c[1] = 0;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%s" , &x , str) , s += x;
        y = (*str == 'B');
        if (m && a[m - 1].second == y)
            a[m - 1].first += x;
        else
            a[m ++] = make_pair(x , y);
    }
    if (m == 1) {
        printf("%d\n" , s);
        return;
    }
    for (i = 0 ; i < m ; ++ i) {
        c[a[i].second] += a[i].first;
        // cout << a[i].first << ' ' << a[i].second << endl;
    }
    int A = c[0] , B = c[1];
    //cout << A << ' ' << B << endl;
    int res = 0;
    x = 0 , y = 0;
    for (i = 0 ; i < m ; ++ i) {
        //cout << i << ' ' << x << ' ' << y << endl;
        if (!a[i].second) {
            if (!y) {
                x += a[i].first;
            } else {
                LL tmp = (LL) A * y;
                if (tmp % B == 0) {
                    LL K = tmp / B - x;
                    //  cout << K << endl;
                    if (K <= a[i].first && K > 0) {
                        ++ res;
                        y = 0 , x = a[i].first - K;
                    } else {
                        x += a[i].first;
                    }
                } else {
                    x += a[i].first;
                }
            }
        } else {
            if (!x) {
                y += a[i].first;
            } else {
                LL tmp = (LL) B * x;
                if (tmp % A == 0) {
                    LL K = tmp / A - y;
                    //   cout << K << endl;
                    if (K <= a[i].first && K > 0) {
                        ++ res;
                        x = 0 , y = a[i].first - K;
                    } else {
                        y += a[i].first;
                    }
                } else
                    y += a[i].first;
            }
        }       
    }
    cout << res << endl;

    

}

int main() {
    int _;
    scanf("%d",&_);
    while (_ --)
        work();
    return 0;
}
