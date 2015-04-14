#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 20005;

struct number {
    double l , c;
    number () { l = c = 0; }
    number (double _c) {
        l = 0;
        c = _c;
    }
    number (double _l , double _c) {
        l = _l;
        c = _c;
    }
    number operator + (const number& R) const {
        return number(l + R.l , c + R.c);
    }
    number operator - (const number& R) const {
        return number(l - R.l , c - R.c);
    }
    number operator * (const number& R) const {
        return number(l * R.c + c * R.l , c * R.c);
    }        
};

struct Point {
    number x , y;
    Point () {
        x = number();
        y = number();        
    }
    Point (double _x , double _y) {
        x = number(_x);
        y = number(_y);        
    }
    Point (number _x , number _y) {
        x = _x;
        y = _y;        
    }
    
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const number& R) const {
        return Point(x * R , y * R);
    }
    number operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
};
int n;
Point a[N] , b[N];

int main() {
    double x , y;
    int i , j;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%lf%lf" , &x , &y);
        a[i] = Point(x , y);
        scanf("%lf%lf" , &x , &y);
        b[i] = Point(x , y) - a[i];
    }
    a[n] = a[0] , b[n] = b[0];
    number t(1 , 0);

    for (i = 1 ; i <= n ; ++ i) {
        Point P = a[i - 1] + b[i - 1] * t;
        Point Q = P - a[i];
        double r = (b[i] % b[i]).c;
        t = b[i] % Q;
        t.l /= r , t.c /= r;
    }
    double res = t.c / (1 - t.l);
    double X = a[0].x.c + b[0].x.c * res;
    double Y = a[0].y.c + b[0].y.c * res;    
    printf("%.10f %.10f\n" , X , Y);
    return 0;
}
