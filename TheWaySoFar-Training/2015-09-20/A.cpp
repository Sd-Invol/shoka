#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 105;
int n , m;

const double eps = 1e-8 , pi = acos(-1.0);
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
Point P[N];
void work() {
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i) {
        P[i].input();
    }
    if (m > n) {
        puts("-1");
        return;
    }
    int res = 1 << 30;
    for (int i = 0 ; i < n ; ++ i) {
        vector<double> V;
        for (int j = 0 ; j < n ; ++ j) {
            Point v = P[j] - P[i];
            V.push_back(v.len());
        }
        sort(V.begin() , V.end());
        double Q = V[m - 1];
        int R = (int) ceil(Q + eps);
        int p = 0;
        for (int j = 0 ; j < n ; ++ j) {
            if (dcmp(V[j] - R) < 0)
                ++ p;
            else if (dcmp(V[j] - R) == 0)
                p = -1 << 30;
        }
        if (p == m)
            res = min(res , R);
    }
    if (res == 1 << 30)
        puts("-1");
    else
        printf("%d\n" , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}

