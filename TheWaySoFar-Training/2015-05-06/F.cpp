#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
int n , C , D , ca;
struct machine {
    int d , p , r , g;
    bool operator < (const machine& R) const {
        return d < R.d;
    }
}a[N];
LL f[N];
typedef pair<LL , LL> Point;
Point operator - (const Point& A , const Point& B) {
    return Point(A.first - B.first , A.second - B.second);
}
bool operator ^ (const Point& A , const Point& B) {
    return (double)A.first * B.second >= (double)A.second * B.first;
}

Point p[N] , s[N];
void solve(int L , int R) {
    if (L >= R)
        return;
    int mid = L + R >> 1;
    solve(L , mid);

    int m = 0;
    for (int i = L ; i <= mid ; ++ i) {
        if (f[i] >= a[i].p)
            p[m ++] = Point(a[i].g , f[i] - a[i].p - (LL)a[i].g * (a[i].d + 1) + a[i].r);
    }
    sort(p , p + m);
    int top = 0;
    for (int i = 0 ; i < m ; ++ i) {
        while (top > 1 && ((s[top - 1] - s[top - 2]) ^ (p[i] - s[top - 2])))
            -- top;
        s[top ++] = p[i];
    }
    m = 0;
    for (int i = 0 ; i < top ; ++ i)
        if (i + 1 == top || s[i].second >= s[i + 1].second)
            p[m ++] = s[i];
    int q = 0;
    for (int i = mid + 1 ; i <= R ; ++ i) {
        s[q ++] = Point(a[i].d , i);
    }
    sort(s , s + q);
    for (int i = 0 , j = 0 ; i < q ; ++ i) {
        while (j + 1 < m && s[i].first * p[j].first + p[j].second <= s[i].first * p[j + 1].first + p[j + 1].second)
            ++ j;
        f[s[i].second] = max(f[s[i].second] , s[i].first * p[j].first + p[j].second);
    }
    solve(mid + 1 , R);
}

void work() {
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d%d%d%d" , &a[i].d , &a[i].p , &a[i].r , &a[i].g);
    a[++ n] = (machine) {D + 1 , 0 , 0 , 0};
    sort(a + 1 , a + n + 1);
    for (int i = 1 ; i <= n ; ++ i)
        f[i] = -1LL << 60;
    f[0] = C;
    solve(0 , n);
    printf("Case %d: %lld\n" , ++ ca , f[n]);
}

int main() {
    while (scanf("%d%d%d" , &n,&C,&D) , n)
        work();
    return 0;
}
