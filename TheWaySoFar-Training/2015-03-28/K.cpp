#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 205;

const double eps = 1e-10;
inline int dcmp(double x) {
    return (x > eps) - (x < -eps); 
}
struct Point {
    double x , y;
    Point () {}
    Point (double _x , double _y) {
        x = _x , y = _y;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const double& R) const {
        return Point(R * x , R * y);
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    double operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    double len() {
        return sqrt(*this % *this);
    }
};
Point Normal(Point A) {
    double L = A.len();
    return Point(-A.y / L , A.x / L);
}

int n;
Point p[N];

typedef vector<Point> Polygon;

Polygon Cut(const Polygon& poly , Point A , Point B) {
    Polygon newpoly;
    int n = poly.size();
    for (int i = 0 ; i < n ; ++ i) {
        const Point& C = poly[i] , &D = poly[(i + 1) % n];
        if (dcmp((B - A) ^ (C - A)) >= 0)
            newpoly.push_back(C);
        if (dcmp((B - A) ^ (C - D)) != 0) {
            double t = ((B - A) ^ (C - A)) / ((B - A) ^ (C - D));
            if (dcmp(t) > 0 && dcmp(t - 1) < 0)
                newpoly.push_back(C + (D - C) * t);
        }
    }
    return newpoly;
}
Point X , Y;
bool check(double r) {
    Polygon P;
    P.push_back(Point(-1e5 , -1e5));
    P.push_back(Point(1e5 , -1e5));
    P.push_back(Point(1e5 , 1e5));
    P.push_back(Point(-1e5 , 1e5));
    for (int i = 0 ; i < n ; ++ i) {
        Point V = Normal(p[i + 1] - p[i]) * r;
        P = Cut(P , p[i] + V , p[i + 1] + V);
    }
    if (P.empty())
        return 0;
    double dis = 0;
    int m = P.size();
    for (int i = 0 ; i < m ; ++ i)
        for (int j = i + 1 ; j < m ; ++ j) {
            double len = (P[i] - P[j]).len();
            if (len > dis) {
                dis = len;
                X = P[i] , Y = P[j];
            }
        }
    if (dis >= r + r)
        return 1;
    return 0;
}


void work() {
    int i , j ;
    for (i = 0 ; i < n ; ++ i)
        scanf("%lf%lf" , &p[i].x , &p[i].y);
    p[n] = p[0];
    double l = 0 , r = 1e5 , m;
    while (r - l > eps) {
        m = (l + r) * 0.5;
        if (check(m))
            l = m;
        else
            r = m;
    }   
    printf("%.15f\n" , l);
    printf("%.15f %.15f\n" , X.x , X.y);
    printf("%.15f %.15f\n" , Y.x , Y.y);    
}

int main() {
    freopen("kabbalah.in" , "r" , stdin);
    freopen("kabbalah.out" , "w" , stdout);
    while (scanf("%d" , &n) , n)
        work();
    return 0;
}
