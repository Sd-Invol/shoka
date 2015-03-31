#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1005;
int ca;

const double eps = 1e-8 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point
{
    double x , y;
    Point () {x = y = 0;}
    Point (double _x , double _y) {x = _x , y = _y;}
    void input() {
        scanf("%lf%lf",&x,&y);
    }
    void output() {
        printf("(%f,%f)\n", x , y);
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
    }
    double operator ^ (const Point& R) const{
        return x * R.y - y * R.x;
    }
    double operator % (const Point& R) const{
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
};
int m , n;
double theta , R;
Point P , V , D;
Point a[N];
bool res[N];

Point Rotate(Point A , double rad) {
    double Sin = sin(rad) , Cos = cos(rad);
    return Point(A.x * Cos - A.y * Sin , A.x * Sin + A.y * Cos);
}
bool OnSegment(Point P , Point a1 , Point a2) {
    return dcmp((a1 - P) ^ (a2 - P)) == 0 && dcmp((a1 - P) % (a2 - P)) <= 0;
}
void checksector(Point P , Point V  , double delta = 0) {
    double arc = atan2(V.y , V.x);
    double l = arc - theta / 2 - delta , r = arc + theta / 2;
    for (int i = 0 ; i < m ; ++ i) {
        if (!res[i]) continue;
        Point W = a[i] - P;
        if (dcmp(W.len() - R) > 0) continue;
        double beta = atan2(W.y , W.x);
        if (dcmp(beta - l) >= 0 && dcmp(beta - r) <= 0)
            res[i] = 0;
        beta -= pi + pi;
        if (dcmp(beta - l) >= 0 && dcmp(beta - r) <= 0)
            res[i] = 0;
    }
}

void checkrect(Point P0 , Point P1 , Point P2 , Point P3) {
    double area = fabs((P0 ^ P1) + (P1 ^ P2) + (P2 ^ P3) + (P3 ^ P0));
    if (dcmp(area) <= 0) {
        for (int i = 0 ; i < m ; ++ i) {
            if (!res[i]) continue;
            if (OnSegment(a[i] , P0 , P1) || OnSegment(a[i] , P0 , P2))
                res[i] = 0;
        }
    } else {
        for (int i = 0 ; i < m ; ++ i) {
            if (!res[i]) continue;
            double sum = 0;
            sum += fabs((P0 - a[i]) ^ (P1 - a[i]));
            sum += fabs((P1 - a[i]) ^ (P2 - a[i]));
            sum += fabs((P2 - a[i]) ^ (P3 - a[i]));
            sum += fabs((P3 - a[i]) ^ (P0 - a[i]));
            if (dcmp(fabs(sum - area)) <= 0)
                res[i] = 0;
        }
    }
}

void work() {
    int i , j;
    scanf("%d%d%lf%lf",&m,&n,&theta,&R);
    P.input() , V.input() , D.input();
    V = V / V.len() * R , D = D / D.len() , theta *= pi / 180;
    double COS = cos(theta / 2);
    for (i = 0 ; i < m ; ++ i) {
        a[i].input();
        res[i] = 1;
    }
    checksector(P , V);
    double t = 0 , T , da;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%lf%lf" , &j , &T , &da);
        T -= t , da *= pi / 180;
        Point Q = P + D * T;
        checksector(Q , V);
        Point Lv = Rotate(V , -theta / 2);
        Point Rv = Rotate(V , theta / 2);
        checkrect(P , P + Lv , Q + Lv , Q);
        checkrect(P , P + Rv , Q + Rv , Q);
        Lv = Rotate(D , -pi / 2);
        double dot = (Lv % V) / R;
        if (dcmp(dot - COS) > 0) {
            Lv = Lv * R;
            checkrect(P , P + Lv , Q + Lv , Q);
        }
        Rv = Rotate(D , pi / 2);
        dot = (Rv % V) / R;
        if (dcmp(dot - COS) > 0) {
            Rv = Rv * R;
            checkrect(P , P + Rv , Q + Rv , Q);
        }
        if (j == 1) {
            checksector(Q , V , da);
            V = Rotate(V , -da);
        } else {
            D = Rotate(D , -da);
        }
        P = Q;
        t += T;
    }
    printf("Case #%d: " , ++ ca);
    for (i = 0 ; i < m ; ++ i)
        printf("%d" , res[i]);
    puts("");
}
int main() {
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
