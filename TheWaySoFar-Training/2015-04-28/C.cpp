#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
const double eps = 1e-8;
struct Point {
    LL x , y;
    Point () {}
    Point (LL _x , LL _y) {
        x = _x , y = _y;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    LL operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
};
Point a[N] , res , P , V , Border[4];
int n;
LL S;

bool side(Point P , Point A , Point B) {
    return ((B - A) ^ (P - A)) > 0;
}

Point get(LL t) {
    return Point(P.x + V.x * t , P.y + V.y * t);
}

void check(Point A , Point B , LL& L , LL& R) {
    if (L > R) return;
    int fl = side(get(L) , A , B);
    int fr = side(get(R) , A , B);
    if (fl && fr)
        return;
    if (!fl && !fr) {
        L = 1 , R = 0;
        return;
    }
    LL l = L , r = R , m;
    if (fl) {
        while (l < r) {
            m = l + r + 1 >> 1;
            if (side(get(m) , A , B))
                l = m;
            else
                r = m - 1;
        }
        R = l;
    } else {
        while (l < r) {
            m = l + r >> 1;
            if (side(get(m) , A , B))
                r = m;
            else
                l = m + 1;
        }
        L = l;
    }
}

void gcd(LL a , LL b , LL &x, LL &y) {
    if (!b) {
        x = 1 , y = 0;
    } else {
        gcd(b , a % b , y , x);
        y -= (a / b) * x;
    }    
}

bool work(int i) {
    LL A = 0 , B = 0 , C = 0 , D , L , R , x , y;
    C -= (a[i] ^ a[i + 1]) + S;
    B += a[i].x , A -= a[i].y;
    B -= a[i + 1].x , A += a[i + 1].y;
    gcd(A , B , x , y);
    D = A * x + B * y;
    if (C % D) return 0;
    A /= D , B /= D , C /= -D;
    x *= C , y *= C;
    P = Point(x , y) , V = Point(-B , A);
    
    L = -1e9 , R = 1e9;
    check(a[(i + n - 1) % n] , a[i] , L , R);
    check(a[i + 1] , a[(i + 2) % n] , L , R);
    for (int i = 0 ; i < 4 ; ++ i)
        check(Border[i] , Border[(i + 1) % 4] , L , R);
    if (L <= R) {
        res = get(L);
        return 1;
    }
    return 0;
}
    
int main() {
    
    int i , j ;
        
    scanf("%d %lld.%d" , &n , &S , &j);
    S <<= 1 , S |= !!j;
    Border[0] = Point(-1000001 , -1000001);
    Border[1] = Point(1000001 , -1000001);
    Border[2] = Point(1000001 , 1000001);
    Border[3] = Point(-1000001 , 1000001);
    
    -- n;
    for (i = 0 ; i < n ; ++ i)
        scanf("%lld%lld" , &a[i].x , &a[i].y);
    a[n] = a[0];
    for (i = 0 ; i < n ; ++ i)
        S -= (a[i] ^ a[i + 1]);
    for (i = 0 ; i < n ; ++ i) {
        if (work(i)) {
            printf("%lld %lld\n" , res.x , res.y);
            break;
        }
    }
    return 0;
}
