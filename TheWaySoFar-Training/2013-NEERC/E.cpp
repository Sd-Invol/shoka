#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

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
    }
    double operator ^ (const Point& R) const{
        return x * R.y - y * R.x;
    }
};

int n;
Point p[N];
Point a[N] , b[N];
int ta , tb;
double L , R;

double area(double x1 , double x2) {
    int i; // a[i - 1] --> a[i]
    double L1 , R1 , L2 , R2;
    i = lower_bound(a , a + ta , Point(x1 , 0)) - a;
    R1 = a[i - 1].y + (x1 - a[i - 1].x) * (a[i].y - a[i - 1].y) / (a[i].x - a[i - 1].x);
    i = lower_bound(b , b + tb , Point(x1 , 0)) - b;
    L1 = b[i - 1].y + (x1 - b[i - 1].x) * (b[i].y - b[i - 1].y) / (b[i].x - b[i - 1].x);
    i = lower_bound(a , a + ta , Point(x2 , 0)) - a;
    R2 = a[i - 1].y + (x2 - a[i - 1].x) * (a[i].y - a[i - 1].y) / (a[i].x - a[i - 1].x);
    i = lower_bound(b , b + tb , Point(x2 , 0)) - b;
    L2 = b[i - 1].y + (x2 - b[i - 1].x) * (b[i].y - b[i - 1].y) / (b[i].x - b[i - 1].x);
    return (x2 - x1) * max(0.0 , min(R1 , R2) - max(L1 , L2));
}

pair<double , double> cal(double x1){
    double l = x1 , r = R , m1 , m2;
    while (r - l > 1e-6) {
        m1 = (l + l + r) / 3;
        m2 = (l + r + r) / 3;
        if (area(x1 , m1) > area(x1 , m2))
            r = m2;
        else
            l = m1;
    }
    return make_pair(area(x1 , (l + r) / 2) , (l + r) / 2);
}

void work() {
    int i;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i)
        p[i].input();
    sort(p , p + n);

    for (i = 0 ; i < n ; ++ i) {
        while (ta > 1 && dcmp((a[ta - 1] - a[ta - 2]) ^ (p[i] - a[ta - 2])) >= 0)
            -- ta;
        a[ta ++] = p[i];
    }
    for (i = n - 1 ; i >= 0 ; -- i) {
        while (tb > 1 && dcmp((b[tb - 1] - b[tb - 2]) ^ (p[i] - b[tb - 2])) >= 0)
            -- tb;
        b[tb ++] = p[i];
    }
    reverse(b , b + tb);
    L = p[0].x , R = p[0].x;
    for (i = 1 ; i < n ; ++ i) {
        L = min(L , p[i].x);
        R = max(R , p[i].x);
    }
    double l = L  , r = R , m1 , m2;
    while (r - l > 1e-6) {
        m1 = (l + l + r) / 3;
        m2 = (l + r + r) / 3;
        if (cal(m1).first > cal(m2).first)
            r = m2;
        else
            l = m1;
    }

    double x1 = (l + r) / 2;
    double x2 = cal(x1).second;
    double L1 , R1 , L2 , R2;
    i = lower_bound(a , a + ta , Point(x1 , 0)) - a;
    R1 = a[i - 1].y + (x1 - a[i - 1].x) * (a[i].y - a[i - 1].y) / (a[i].x - a[i - 1].x);
    i = lower_bound(b , b + tb , Point(x1 , 0)) - b;
    L1 = b[i - 1].y + (x1 - b[i - 1].x) * (b[i].y - b[i - 1].y) / (b[i].x - b[i - 1].x);
    i = lower_bound(a , a + ta , Point(x2 , 0)) - a;
    R2 = a[i - 1].y + (x2 - a[i - 1].x) * (a[i].y - a[i - 1].y) / (a[i].x - a[i - 1].x);
    i = lower_bound(b , b + tb , Point(x2 , 0)) - b;
    L2 = b[i - 1].y + (x2 - b[i - 1].x) * (b[i].y - b[i - 1].y) / (b[i].x - b[i - 1].x);
    double y2 = min(R1 , R2) , y1 = max(L1 , L2);
    printf("%.10f %.10f %.10f %.10f\n" , x1 , y1 , x2 , y2);

}

int main() {
    freopen("easy.in" , "r" , stdin);
    freopen("easy.out" , "w" , stdout);
    work();
    return 0;
}
