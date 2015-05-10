#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 205;
const double eps = 1e-8;
const double pi = acos(-1);
int dcmp(double x) {
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
        return Point(x * R , y * R);
    }
    double operator ^ (const Point &R) const {
        return x * R.y - y * R.x;
    }
    double len() {
        return sqrt(x * x + y * y);
    }
};
int n;
double R;
Point a[N];

double Angle(Point A) {
    return atan2(A.y , A.x);
}

double sector(Point A , Point B) {
    double theta = Angle(A) - Angle(B);
    while (theta < 0) theta += pi + pi;
    while (theta >= pi + pi) theta -= pi + pi;
    theta = min(theta , pi + pi - theta);
    return R * R * theta;
}
int Get(Point P , Point V , double& t0 , double& t1) {
    double A = V.x , B = P.x , C = V.y , D = P.y;
    double E = A * A + C * C , F = 2 * (A * B + C * D) , G = B * B + D * D - R * R;
    double delta = F * F - 4 * E * G;
    if (dcmp(delta) < 0)
        return 0;
    if (dcmp(delta) == 0) {
        t0 = t1 = -F / (E + E);
        return 1;
    }
    delta = sqrt(delta);
    t0 = (-F - delta) / (E + E);
    t1 = (-F + delta) / (E + E);
    return 2;
}

void work() {
    int i , j;
    for (i = 0 ; i < n ; ++ i)
        scanf("%lf%lf" , &a[i].x , &a[i].y);
    a[n] = a[0];

    double res = 0;
    for (i = 0 ; i < n ; ++ i) {
        double t0 = 0 , t1 = 0 , delta;
        Point P = a[i] , V = a[i + 1] - a[i];
        int cnt = Get(P , V , t0 , t1);
        Point X = P + V * t0 , Y = P + V * t1;
        bool f0 = dcmp(a[i].len() - R) <= 0;
        bool f1 = dcmp(a[i + 1].len() - R) <= 0;
        if (f0 && f1) {
            delta = fabs(a[i] ^ a[i + 1]);
        } else if (!f0 && f1) {
            delta = sector(a[i] , X) + fabs(X ^ a[i + 1]);
        } else if (f0 && !f1) {
            delta = sector(Y , a[i + 1]) + fabs(a[i] ^ Y);
        } else {
            if (cnt > 1 && 0 < t1 && t1 < 1 && 0 < t0 && t0 < 1) {
                delta = sector(a[i] , X) + sector(Y , a[i + 1]) + fabs(X ^ Y);
            } else {
                delta = sector(a[i] , a[i + 1]);
            }
        }
        res += delta * dcmp(a[i] ^ a[i + 1]);
    }
    res /= 2;
    printf("%.10f\n" , res);    
}

int main() {
    while (~scanf("%d%lf" , &n , &R))
        work();
    return 0;
}
