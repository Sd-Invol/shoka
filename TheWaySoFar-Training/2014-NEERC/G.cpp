#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 10005;

const double eps = 1e-10;
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
double GetLineIntersection(Point P , Point v , Point Q , Point w) {
    if (dcmp(v ^ w) == 0)
        return -1;
    Point u = P - Q;
    return (w ^ u) / (v ^ w);
}


int n , m;
double a , pos[N];
pair<int , int> h[N];
Point p[N];

void work() {
    int i , j;
    scanf("%d%d%lf" , &n , &m , &a);
    a /= 180 , a *= acos(-1);
    Point V(cos(a) , -sin(a));
    for (i = 0 ; i < n ; ++ i)
        scanf("%d",&h[i].first) , h[i].second = i;
    sort(h , h + n);
    for (i = 0 ; i < m ; ++ i)
        p[i].input();

    double x = p[0].x , res = 0;

    for (i = 0 , j = 0 ; i < n ; ++ i) {
        double y = p[j].y + (p[j + 1].y - p[j].y) * (x - p[j].x) / (p[j + 1].x - p[j].x);
        Point P(x , y + h[i].first);
        res += h[i].first;
        pos[h[i].second] = x;
        int tmp = j;
        //printf("%d : %f %f\n" , h[i].first , P.x , P.y);
        while (j + 1 < m) {
            double t = GetLineIntersection(p[j] , p[j + 1] - p[j] , P , V);
            //printf("* %d %d %f\n" , i , j , t);
            if (dcmp(t) >= 0 && dcmp(t - 1) <= 0) {
                x = p[j].x + (p[j + 1].x - p[j].x) * t;
                break;
            } else
                ++ j;
        }
        if (j + 1 >= m) {
            if (i + 1 < n) {
                double delta;
                int o = -1;
                for (j = tmp + 1 ; j < m ; ++ j) {
                    double H = GetLineIntersection(p[j] , Point(0 , 1) , P , V);
                    double dh = max(0.0 , h[n - 1].first - H);
                    if (!~o || dh > delta)
                        o = j , delta = dh;
                }
                res += delta;
                pos[h[n - 1].second] = p[o].x;
            }
            break;
        }
    }
    printf("%.15f\n" , res);
    for (i = 0 ; i < n ; ++ i)
        printf("%.15f\n" , pos[i]);
}

int main() {
    freopen("green.in" , "r" , stdin);
    freopen("green.out" , "w" , stdout);
    work();
    return 0;
}
