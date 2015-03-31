#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
int n;
pair<int , int> a[N];

struct Point {
    int x , y;
    Point () {}
    Point (int _x , int _y) {
        x = _x , y = _y;
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    LL operator ^ (const Point& R) const {
        return (LL) x * R.y - (LL) y * R.x;
    }
}P , s[N];
int top;

void work() {
    int i;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i)
        scanf("%d%d",&a[i].first , &a[i].second);
    sort(a , a + n);
    pair<LL , LL> res;
    for (i = 0 ; i < n ; ++ i) {
        P = Point(i , a[i].first);

        while (top > 1 && ((s[top - 1] - s[top - 2]) ^ (P - s[top - 2])) >= 0)
            -- top;
        s[top ++] = P;

        P = Point(i + 1 , a[i].second);

        int l = 0 , r = top - 1 , m;
        while (l < r) {
            m = l + r + 1 >> 1;
            if (((P - s[m - 1]) ^ (s[m] - s[m - 1])) >= 0)
                l = m;
            else
                r = m - 1;
        }
        int x = P.x - s[l].x;
        int y = P.y - s[l].y;
        if (y * res.first <= res.second * x)
            res = make_pair(x , y);
    }
    LL z = __gcd(res.first , res.second);
    res.first /= z , res.second /= z;
    cout << res.second << '/' << res.first << endl;
}

int main() {
    freopen("caravan.in" , "r" , stdin);
    freopen("caravan.out" , "w" , stdout);

    work();
    return 0;
}
