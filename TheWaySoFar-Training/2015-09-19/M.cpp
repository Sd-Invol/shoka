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
const int N = 2005;
int n , m , ca;
int X[105][N] , Y[105][N];
int sx[105] , sy[105];
LL ssx[105] , ssy[105];
const double eps = 1e-8 , pi = acos(-1.0);
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
};
typedef vector<Point> Polygon;
Polygon CutPolygon(const Polygon& poly , Point A , Point B) {
    Polygon newpoly;
    int n = poly.size();
    for (int i = 0 ; i < n ; ++ i) {
        const Point &C = poly[i] , &D = poly[(i + 1) % n];
        if (dcmp((B - A) ^ (C - A)) >= 0)
            newpoly.push_back(C);
        if (dcmp((B - A) ^ (C - D)) != 0) {
            double t = ((B - A) ^ (C - A)) / ((D - C) ^ (B - A));
            if (dcmp(t) > 0 && dcmp(t - 1) < 0)
                newpoly.push_back(C + (D - C) * t);
        }
    }
    return newpoly;
}
void work() {
    printf("Case #%d: " , ++ ca);
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i) {
        sx[i] = ssx[i] = sy[i] = ssy[i] = 0;
        for (int j = 0 ; j < m ; ++ j) {
            scanf("%d%d" , &X[i][j] , &Y[i][j]);
            sx[i] += X[i][j];
            ssx[i] += X[i][j] * X[i][j];
            sy[i] += Y[i][j];
            ssy[i] += Y[i][j] * Y[i][j];            
        }
    }
    for (int i = 0 ; i < n ; ++ i) {
        Polygon Poly;
        Poly.push_back(Point(0 , 0));
        Poly.push_back(Point(4095 , 0));
        Poly.push_back(Point(4095 , 4095));
        Poly.push_back(Point(0 , 4095));
        
        for (int j = 0 ; j < n ; ++ j) {
            if (i == j)
                continue;
            LL A = 0 , B = 0 , C = 0;
            /*for (int k = 0 ; k < m ; ++ k) {
                A += 2 * (X[j][k] - X[i][k]);
                B += 2 * (Y[j][k] - Y[i][k]);
                C += X[i][k] * X[i][k] + Y[i][k] * Y[i][k];
                C -= X[j][k] * X[j][k] + Y[j][k] * Y[j][k];
                }        */
            A = 2 * (sx[j] - sx[i]);
            B = 2 * (sy[j] - sy[i]);
            C += ssx[i] + ssy[i];
            C -= ssx[j] + ssy[j];            
            LL d = abs(__gcd(A , __gcd(B , C)));
            A /= d , B /= d , C /= d;
            //printf("%d %d : %lld %lld %lld\n" , i , j , A , B , C);
            if (A == 0 && B == 0) {
                if (C > 0)
                    Poly.clear();
            } else {
                Point P;
                if (A == 0) {
                    P = Point(0 , (double)-C / B);
                } else {
                    P = Point((double)-C / A , 0);
                }                
                Point V(-B , A);
                Poly = CutPolygon(Poly , P , P + V);
            }
        }
        double res = 0;
        int K = Poly.size();           
        for (int j = 0 ; j < K ; ++ j) {
            res += (Poly[j] ^ Poly[(j + 1) % K]);
        }
        double p = res / 2;
        printf("%d%c" , int(p + 0.5) , " \n"[i + 1 == n]);
    }
}



int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
