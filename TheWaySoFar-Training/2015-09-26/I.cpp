#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
typedef long long LL;
using namespace std;
const int N = 100005;
const int Q = 1e9 + 7;

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
    void output() {
        printf("(%f,%f)", x + eps , y + eps);
    }
    bool operator < (const Point& R) const{
        if (dcmp(x - R.x) == 0)
            return dcmp(y - R.y) < 0;
        return dcmp(x - R.x) < 0;
    }
    bool operator == (const Point& R) const{
        return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
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
int ca;
// 向量的极角, [-pi,pi)
double Angle(Point V) {
    return atan2(V.y , V.x);
}
Point Rotate(Point A , double rad) {
    double Sin = sin(rad) , Cos = cos(rad);
    return Point(A.x * Cos - A.y * Sin , A.x * Sin + A.y * Cos);
}
Point GetLineIntersection(Point P , Point v , Point Q , Point w) {
    Point u = P - Q;
    double t1 = (w ^ u) / (v ^ w);
    return P + v * t1;
}
void work() {
    printf("Case #%d: " , ++ ca);
    Point A , B , C;
    A.input();
    B.input();
    C.input();
    Point M = (C + B) / 2;
    double res = (A - M).len();
    Point P = GetLineIntersection(B , Rotate(B - A , pi / 2) , C , Rotate(C - A , -pi / 2));
    double R = (B - P).len();
    double arc = abs(Angle(B - P) - Angle(C - P));
    res += R * min(arc , pi + pi - arc);
    printf("%.4f\n" , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}