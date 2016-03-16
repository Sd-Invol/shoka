#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 105;

const long double eps = 1e-8 , pi = acos(-1.0);
inline int dcmp(long double x) {
    return (x > eps) - (x < -eps);
}

struct Point {
    long double x , y;
    Point (long double x = 0 , long double y = 0) : x(x) , y(y) {}
    void input() {
        double _x , _y;
        scanf("%lf%lf",&_x,&_y);
        x = _x , y = _y;
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
    Point operator * (const long double& R) const{
        return Point(x * R , y * R);
    }
    Point operator / (const long double& R) const{
        return Point(x / R , y / R);
    }
    long double operator ^ (const Point& R) const{
        return x * R.y - y * R.x;
    }
    long double operator % (const Point& R) const{
        return x * R.x + y * R.y;
    }
    long double len() {
        return sqrt(*this % *this);
    }
};

struct Circle {
    Point O;
    long double r;
    Circle () {}
    Circle (Point _O , long double _r) {O = _O , r = _r;}
    Point point(long double arc) {
        return Point(O.x + cos(arc) * r , O.y + sin(arc) * r);
    }
};

long double Angle(Point P) {
    return atan2(P.y , P.x);
}

int GCCI(Circle C1 , Circle C2 , vector<Point>& sol) {
    long double d = (C1.O - C2.O).len();
    if (dcmp(d) == 0) {
        if (dcmp(C1.r - C2.r) == 0) {
            for (int i = 0 ; i < 20 ; ++ i) {
                double arc = (pi + pi) * rand() / RAND_MAX;
                sol.push_back(C1.point(arc));
            }
            return -1;
        }
        return 0;
    }
    if (dcmp(C1.r + C2.r - d) < 0) return 0;//相离
    if (dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;//内含
    long double a = Angle(C2.O - C1.O); // acos内可能越界
    long double p = (C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d);
    p = max((long double)-1.0 , min((long double)1.0 , p));
    long double da = acos(p);
    Point P1 = C1.point(a - da) , P2 = C1.point(a + da);
    sol.push_back(P1);
    if (P1 == P2) return 1; //切
    sol.push_back(P2);
    return 2;
}

void work() {
    Point A , B , C;
    long double a1 , a2;
    A.input();
    B.input();
    C.input();
    int aa , bb;
    scanf("%d%d" , &aa , &bb);
    a1 = aa / 180.0 * pi;
    a2 = bb / 180.0 * pi;

    Point C1 = (A + B) / 2.0 , W1 = B - A;
    Point V1 = Point(-W1.y , W1.x) / 2 / tan(a1);
    Point C2 = (C + B) / 2.0 , W2 = B - C;
    Point V2 = Point(-W2.y , W2.x) / 2 / tan(a2);

    if (aa == 90) V1 = Point();
    if (bb == 90) V2 = Point();

    //cout << V1.len() << endl;

    vector<Point> V;
    for (int i = -1 ; i <= 1 ; i += 2) {
        Point O1 = C1 + V1 * i;
        for (int j = -1 ; j <= 1 ; j += 2) {
            Point O2 = C2 + V2 * j;
            GCCI(Circle(O1 , (O1 - B).len()) , Circle(O2 , (O2 - B).len()) , V);
        }
    }

    for (auto &P : V) {
        if (P == B || P == A || P == C)
            continue;
        Point va = A - P , vb = B - P , vc = C - P;
        long double A1 = acos((va % vb) / va.len() / vb.len());
        long double A2 = acos((vc % vb) / vc.len() / vb.len());
        if (dcmp(A1 - a1) == 0 && dcmp(A2 - a2) == 0) {
            printf("%.15f %.15f\n" , (double)P.x , (double)P.y);
            return;
        }
    }
    assert(0);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
