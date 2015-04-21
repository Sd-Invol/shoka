#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 105;

const double eps = 1e-10 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point {
    double x , y;
    Point () {x = y = 0;}
    Point (double _x , double _y) {x = _x , y = _y;}
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
    void output() {
        printf("(%.10f %.10f)\n" , x , y);
    }
};
Point Rotate(Point A , double rad) {
    double Sin = sin(rad) , Cos = cos(rad);
    return Point(A.x * Cos - A.y * Sin , A.x * Sin + A.y * Cos);
}
struct Circle {
    Point O;
    double r;
    Circle () {}
    Circle (Point _O , double _r) {
        O = _O , r = _r;
    }
    Point point(double arc) {
        return Point(O.x + cos(arc) * r , O.y + sin(arc) * r);
    }
};
double Angle(Point V) {
    return atan2(V.y , V.x);
}

vector<Point> getCircleCircleIntersection(Circle C1 , Circle C2) {
    double d = (C1.O - C2.O).len();
    double a = Angle(C2.O - C1.O);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
    Point P1 = C1.point(a - da) , P2 = C1.point(a + da);
    vector<Point> sol;
    sol.push_back(P1);
    sol.push_back(P2);
    return sol;
}
int n;
Point p[N];
void work() {
    int i , j;
    double arc = (pi + pi) / n;
    double len = sin((pi - arc) / 2) / sin(arc);    
    arc = (pi + pi) / n;
    p[0] = Point(0 , len);
    for (i = 1 ; i < n ; ++ i)
        p[i] = Rotate(p[i - 1] , arc);

    while (1) {
        vector< pair<double , int> > Vec;
        for (i = 0 ; i < n ; ++ i) {
            Point V1 = p[i] - p[(i + n - 1) % n];
            Point V2 = p[(i + 1) % n] - p[i];                
            Vec.push_back(make_pair(acos(V1 % V2) , i));
        }
        sort(Vec.begin() , Vec.end());
        vector<int> invaild;
        for (i = 0 ; i < n ; ++ i) {
            if (i > 0 && Vec[i - 1].first + 1e-4 >= Vec[i].first || i + 1 < n && Vec[i].first + 1e-4 >= Vec[i + 1].first)
                invaild.push_back(Vec[i].second);
        }
        if (invaild.empty())
            break;
        i = invaild[rand() % invaild.size()];            
        arc = 1e-2 * ((1.0 * rand() / RAND_MAX) - 0.5);
        Point V = Rotate(p[(i + 1) % n] - p[i % n] , arc) + p[i % n];
        vector<Point> sol = getCircleCircleIntersection(Circle(V , 1) , Circle(p[(i + 3) % n]  , 1));
        Point W;
        if ((p[(i + 2) % n] - sol[0]).len() < (p[(i + 2) % n] - sol[1]).len())
            W = sol[0];
        else
            W = sol[1];
        Point V0 = p[i % n] - p[(i + n - 1) % n];
        Point V1 = V - p[i % n] , V2 = W - V , V3 = p[(i + 3) % n] - W;
        Point V4 = p[(i + 4) % n] - p[(i + 3) % n];

        if ((V0 ^ V1) > 1e-7 && (V1 ^ V2) > 1e-7 && (V2 ^ V3) > 1e-7 && (V3 ^ V4) > 1e-7) {
            p[(i + 2) % n] = W;
            p[(i + 1) % n] = V;
        }   
    }
    for (i = 0 ; i < n ; ++ i) {
        printf("%.20f %.20f\n" , p[i].x , p[i].y);
    }
}

int main() {
    srand(time(0));
    cin >> n;
    work();
    return 0;
}
