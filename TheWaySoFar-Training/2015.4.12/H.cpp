#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
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
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
};

double A[] = {0 , 30 , 60 , 90 , 120 , 150};
double B[] = {180 , 210 , 240 , 270 , 300 , 330};

Point Rotate(Point P , double rad) {
    double SIN = sin(rad) , COS = cos(rad);
    return Point(P.x * COS - P.y * SIN , P.x * SIN + P.y * COS);
}

int main() {
    Point P , V;
    scanf("%lf%lf" , &P.x , &P.y);
    scanf("%lf%lf" , &V.x , &V.y);
    for (int i = 0 ; i < 6 ; ++ i) {
        printf("%.0f%c" , A[i] , " \n"[i == 5]);
        A[i] = A[i] / 180 * pi;
    }
    for (int i = 0 ; i < 6 ; ++ i) {
        printf("%.0f%c" , B[i] , " \n"[i == 5]);
        B[i] = B[i] / 180 * pi;
    }
    fflush(stdout);

    while (1) {
        double a = 0 , b = 0 , x;
        char str[10];
        for (int i = 0 ; i < 6 ; ++ i) {
            Point W = Rotate(V , A[i]);
            a += (P + W).len();
        }
        for (int i = 0 ; i < 6 ; ++ i) {
            Point W = Rotate(V , B[i]);
            b += (P + W).len();
        }
        if (a < b)
            printf("1\n");
        else
            printf("2\n");
        fflush(stdout);
        scanf("%lf" , &x);
        x = x / 180 * pi;
        V = Rotate(V , x);
        scanf("%s" , str);
        if (*str == 'Y')
            break;
        else {
            scanf("%lf%lf" , &P.x , &P.y);
            scanf("%lf%lf" , &V.x , &V.y);    
        }
    }
    return 0;
}
