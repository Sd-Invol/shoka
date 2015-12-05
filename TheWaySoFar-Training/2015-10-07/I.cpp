#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <queue>
using namespace std;
const int N = 505;

const double eps = 1e-8 , pi = acos(-1);
int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point {
    double x , y;
    Point (double _x = 0 , double _y = 0) {
        x = _x;
        y = _y;
    }
    Point operator + (const Point &R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    double operator ^ (const Point &R) const {
        return x * R.y - y * R.x;
    }
    double operator % (const Point &R) const {
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
    Point operator * (const double& R) const{
        return Point(x * R , y * R);
    }
    void input() {
        scanf("%lf%lf" , &x , &y);
    }
};


struct Circle {
    Point O;
    double R;
    Circle (Point _O = Point() , double _R = 0) {
        O = _O;
        R = _R;
    }
    bool in(Point P) {
        return dcmp((P - O).len() - R) <= 0;
    }
};
double L;
int n , m , K , ca;
Point P[N][N] , Q;
int s[N];
Circle C[N];


double getLineCircleIntersection(Point p , Point v , Circle C) {
    double a = v.x , b = p.x - C.O.x , c = v.y , d = p.y - C.O.y;
    double e = a * a + c * c , f = 2 * (a * b + c * d) , g = b * b + d * d - C.R * C.R;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) <= 0) return 0;
    double t1 = (-f - sqrt(delta)) / (e + e);
    double t2 = (-f + sqrt(delta)) / (e + e);
    vector<double> V; V.push_back(t1); V.push_back(t2);
    V.push_back(0);  V.push_back(1);
    sort(V.begin() , V.end()); double res = 0;
    for (int i = 0 ; i + 1 < V.size() ; ++ i) {
        double w = (V[i] + V[i + 1]) * 0.5;
        if (dcmp(w) >= 0 && dcmp(w - 1) <= 0 && C.in(p + v * w))
            res += (v * (V[i + 1] - V[i])).len();
    }
    return res;
}
double Angle(Point V) {
    return atan2(V.y , V.x);
}
double getCircleCircleIntersection(Circle C1 , Circle C2) {
    double d = (C1.O - C2.O).len();
    if (dcmp(d) == 0) {
        if (dcmp(C1.R - C2.R) >= 0)
            return 2 * pi * C2.R;
        return 0;
    }
    if (dcmp(C1.R - C2.R) >= 0 && dcmp(C1.R - C2.R - d) >= 0) return 2 * pi * C2.R;
    if (dcmp(C1.R + C2.R - d) < 0) return 0;
    if (dcmp(fabs(C1.R - C2.R) - d) > 0) return 0;
    double a = Angle(C1.O - C2.O); // acos 内可能越界
    double w = (C2.R * C2.R + d * d - C1.R * C1.R) / (2 * C2.R * d);
    double da = acos(max(-1.0 , min(1.0 , w)));
    return C2.R * da * 2;
}
double cal(double R) {
    Circle A(Q , R);
    double res = 0;
    for (int i = 0 ; i < n ; ++ i) {
        res += getCircleCircleIntersection(A , C[i]);
    }
    for (int i = 0 ; i < m ; ++ i) {
        for (int j = 0 ; j < s[i] ; ++ j) {
            Point p = P[i][j] , v = P[i][(j + 1) % s[i]];
            res += getLineCircleIntersection(p , v - p , A);
            //cout << getLineCircleIntersection(p , v - p , A) << endl;
        }
    }
    return res;
}

void work() {
    printf("Case #%d: " , ++ ca);
    scanf("%d%lf" , &K , &L);
    n = m = 0;
    for (int i = 0 ; i < K ; ++ i) {
        char type[5];
        scanf("%s" , type);
        if (*type == 'C') {
            C[n].O.input();
            scanf("%lf" , &C[n].R);
            ++ n;
        } else {
            scanf("%d" , &s[m]);
            for (int j = 0 ; j < s[m] ; ++ j)
                P[m][j].input();
            ++ m;
        }
    }
    Q.input();
    double l = 0 , r = 1e5 , mid;
    for (int i = 0 ; i < 100 ; ++ i) {
        mid = 0.5 * (l + r);
        //printf("%f : %f\n" , mid , cal(mid));
        if (dcmp(cal(mid) - L) <= 0)
            l = mid;
        else
            r = mid;
    }
    mid = l;
    double W = cal(mid);
    //printf("%.10f\n" , W);
    // cout << mid << endl;
    //cout << W << endl;
    if (dcmp(cal(1e5) - L) == 0) {
        puts("inestimable");
    } else if (fabs(W - L) < 1e-6)
        printf("%.2f\n" , r);
    else {
        puts("impossible");
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}