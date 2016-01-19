#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>
using namespace std;
const int N = 100005;

struct Point {
    double x , y;
    Point (double _x = 0 , double _y = 0) {
        x = _x;
        y = _y;
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator + (const Point &R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator * (const double &R) const {
        return Point(x * R , y * R);
    }
    double operator % (const Point &R) const {
        return x * R.x + y * R.y;
    }
    double operator ^ (const Point &R) const {
        return x * R.y - y * R.x;
    }
    
};

int n , m;
Point a[N];

int main() {
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%lf%lf" , &a[i].x, &a[i].y);
    for (int j = 0 ; j < m ; ++ j) {
        Point P , V;
        scanf("%lf%lf%lf%lf" , &P.x , &P.y , &V.x , &V.y);
        V = V - P;
        for (int i = 0 ; i < n ; ++ i) {
            if (((a[i] - P) ^ V) < 0)
                continue;
            Point W = P + V * (V % (a[i] - P) / (V % V));
            a[i] = W + W - a[i]; 
        }        
    }
    for (int i = 0 ; i < n ; ++ i)
        printf("%.10f %.10f\n" , a[i].x , a[i].y);
    return 0;
}
