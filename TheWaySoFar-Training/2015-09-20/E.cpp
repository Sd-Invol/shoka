#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <ctime>
using namespace std;
typedef long long LL;
const int N = 1005;

const double eps = 1e-10 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point {
    double x , y;
    Point () {x = y = 0;}
    Point (double _x , double _y) {x = _x , y = _y;}
    void input() {
        scanf("%lf%lf",&x,&y);
    }
    bool operator < (const Point& R) const{
        return atan2(y , x) < atan2(R.y , R.x);
    }
    Point operator + (const Point& R) const{
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const{
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const double& R) const{
        return Point(x * R , y * R);
    }
    Point operator / (const double& R) const{
        return Point(x / R , y / R);
    }// Cross Product
    double operator ^ (const Point& R) const{
        return x * R.y - y * R.x;
    }// dot
    double operator % (const Point& R) const{
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
};
struct Circle {
    Point O;
    double r;
    Circle () {}
    Circle (Point _O , double _r) {
        O = _O , r = _r;
    }
    void input() {
        O.input() , scanf("%lf",&r);
    }
    bool in(Point P) {
        return (P - O).len() < r;
    }
};


int getLineCircleIntersection(Point P , Point V , Circle C , double& t1 , double& t2) {
    double a = V.x , b = P.x - C.O.x , c = V.y , d = P.y - C.O.y;
    double e = a * a + c * c , f = 2 * (a * b + c * d) , g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) <= 0) return 0;
    t1 = (-f - sqrt(delta)) / (e + e);
    t2 = (-f + sqrt(delta)) / (e + e);
    return 2;
}

int n;
Point P[N];
Circle C;

bool check(Point Q) {
    int res = 0;
    for (int i = 0 ; i < n ; ++ i) {
        Point a = P[i] , b = P[i + 1];
        if (a.y > b.y) swap(a , b);
        if (dcmp((a - Q) ^ (b - Q)) < 0 && dcmp(a.y - Q.y) < 0 && dcmp(b.y - Q.y) >= 0)
            res ^= 1;
    }
    return res;
}
double Angle(Point V) {
    return atan2(V.y , V.x);
}
void work() {
    for (int i = 0 ; i < n ; ++ i)
        P[i].input();
    C.input();
    for (int i = 0 ; i < n ; ++ i)
        P[i] = P[i] - C.O;
    P[n] = P[0];
    C.O = Point(0 , 0);
    vector<Point> Vec;
    double res = 0;
    for (int i = 0 ; i < n ; ++ i) {
        Point W = P[i] , V = P[i + 1] - P[i];
        double t1 = -1 , t2 = -1;
        int p = getLineCircleIntersection(W , V , C , t1 , t2);
        vector<double> w;
        w.push_back(0);
        w.push_back(1);
        if (dcmp(t1) >= 0 && dcmp(t1 - 1) <= 0) {
            w.push_back(t1);
            Vec.push_back(W + V * t1);
        }
        if (dcmp(t2) >= 0 && dcmp(t2 - 1) <= 0) {
            w.push_back(t2);
            Vec.push_back(W + V * t2);
        }
        sort(w.begin() , w.end());
        for (int k = 0 ; k + 1 < w.size() ; ++ k) {
            Point p = W + V * ((w[k] + w[k + 1]) / 2);
            if (C.in(p))
                res += (V * (w[k + 1] - w[k])).len();
        }
    }
    sort(Vec.begin() , Vec.end());
    int m = Vec.size();
    if (m == 0) {
        if (res < eps) 
            res = 2 * pi * C.r;
    }
    for (int i = 0 ; i < m ; ++ i) {
        double w = Angle(Vec[(i + 1) % m]) + Angle(Vec[i]);
        w *= 0.5;
        if (i == m - 1)
            w += pi;
        Point p(cos(w) , sin(w));
        if (check(p * C.r)) {
            double arc = Angle(Vec[(i + 1) % m]) - Angle(Vec[i]);
            if (arc < 0) arc += pi + pi;
            res += arc * C.r;
        }
    }
    cout << lround(res) << endl;
}

int main() {
    while (scanf("%d" , &n) , n)
        work();
    return 0;
}
