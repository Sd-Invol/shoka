#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
typedef long long LL;
using namespace std;
const int N = 100005;
const int M = 505;
struct Point {
    int x , y;
    Point (int _x = 0 , int _y = 0) {
        x = _x , y = _y;
    }
    void input() {
        scanf("%d%d" , &x , &y);
    }
    bool operator < (const Point& R) const{
        if (x != R.x)
            return x < R.x;
        return y < R.y;
    }
    bool operator == (const Point& R) const {
        return x == R.x && y == R.y;
    }
    Point operator + (const Point& R) const{
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const{
        return Point(x - R.x , y - R.y);
    }
    LL operator ^ (const Point& R) const{
        return (LL)x * R.y - (LL)y * R.x;
    }
    LL operator % (const Point& R) const {
        return (LL)x * R.x + (LL)y * R.y;
    }
};
int Convex(Point *s , Point *p , int n) {    
    sort(p , p + n);
    int m = 0;
    for (int i = 0 ; i < n ; ++ i) {
        while (m > 1 && ((s[m - 1] - s[m - 2]) ^ (p[i] - s[m - 2])) <= 0)
            m --;
        s[m ++] = p[i];
    }
    int tmp = m;
    for (int i = n - 2 ; i >= 0 ; -- i) {
        while (m > tmp && ((s[m - 1] - s[m - 2]) ^ (p[i] - s[m - 2])) <= 0)
            m --;
        s[m ++] = p[i];
    }
    if (n > 1) -- m;
    s[m] = s[0];
    return m;
}
int n , m;
Point a[N] , b[N] , s[N] , t[N];
pair<double , int> angle[N];
int g[M][M];
int work() {
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i)
        a[i].input();
    for (int i = 0 ; i < m ; ++ i)
        b[i].input();
    int nn = Convex(s , a , n);
    int mm = Convex(t , b , m);
    for (int i = 0 ; i < nn ; ++ i) {
        for (int j = 0 ; j < mm ; ++ j) {
            if (((t[j + 1] - t[j]) ^ (s[i] - t[j])) < 0)
                return -1;
        }
    }
    if (mm == 1) {
        if (nn == 1 && s[0] == t[0])
            return 1;
        return -1;
    }
    for (int i = 0 ; i < nn ; ++ i) {
        Point V = s[i + 1] - s[i];
        angle[i] = make_pair(atan2(V.y , V.x) , i);
    }
    sort(angle , angle + nn);
    memset(g , 0x3f , sizeof(g));
    for (int i = 0 ; i < m ; ++ i) {
        for (int j = 0 ; j < m ; ++ j) {
            if (i == j) continue;
            Point V = b[j] - b[i];
            double arc = atan2(V.y , V.x);
            int k = lower_bound(angle , angle + nn , make_pair(arc , -1)) - angle;
            if (k == nn) k = 0; k = angle[k].second;
            if ((V ^ (s[k] - b[i])) >= 0) {
                g[i][j] = 1;
                //  cout << i << " -> " << j << endl;
            }
        }
    }
    for (int k = 0 ; k < m ; ++ k)
        for (int i = 0 ; i < m ; ++ i)
            for (int j = 0 ; j < m ; ++ j)
                g[i][j] = min(g[i][j] , g[i][k] + g[k][j]);
    int res = 1 << 30;
    for (int k = 0 ; k < m ; ++ k)
        res = min(res , g[k][k]);
    return res;
}

int main() {
    int T , ca = 0;
    scanf("%d" , &T);    
    while (T --)
        printf("Case #%d: %d\n" , ++ ca , work());    
    return 0;
}