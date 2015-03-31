#include <bits/stdc++.h>
using namespace std;
const int N = 100005;

const double eps = 1e-8;
int dcmp(double x) {
    return (x > eps) - (x < -eps);
}

struct Point {
    double x , y;
    Point() {}
    Point(double _x , double _y) {
        x = _x , y = _y;
    }
    void print() {
        printf("%.10f %.10f\n", x , y);
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const double& R) const {
        return Point(x * R , y * R);
    }
    double operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    bool operator < (const Point& R) const {
        return make_pair(x , y) < make_pair(R.x , R.y);
    }
    double Len() {
        return sqrt(*this % *this);
    }    
}a[N] , s[N];
int n , m;
int main() {
    int i , j , k , l;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i)
        scanf("%lf%lf",&a[i].x , &a[i].y);
    sort(a , a + n);
    m = 0;
    for (i = 0 ; i < n ; ++ i) {
        while (m > 1 && dcmp((s[m - 1] - s[m - 2]) ^ (a[i] - s[m - 2])) <= 0)
            -- m;
        s[m ++] = a[i];
    }
    int tmp = m;
    for (i = n - 1 ; i >= 0 ; -- i) {
        while (m > tmp && dcmp((s[m - 1] - s[m - 2]) ^ (a[i] - s[m - 2])) <= 0)
            -- m;
        s[m ++] = a[i];
    }
    if (n > 1) -- m; s[m] = s[0];

    double res = 1e60;
    Point P , X , Y;
    j = k = 1 , l = m / 2;
    for (i = 0 ; i < m ; ++ i) {
        // printf("%f %f\n" , s[i].x , s[i].y);
        Point V = s[i + 1] - s[i];
        double len = V % V;
        while ((V ^ (s[j + 1] - s[i])) >= (V ^ (s[j] - s[i])))
            j = (j + 1) % m;
        while ((V % (s[k + 1] - s[i])) >= (V % (s[k] - s[i])))
            k = (k + 1) % m;
        while ((V % (s[l + 1] - s[i])) <= (V % (s[l] - s[i])))
            l = (l + 1) % m;
        Point L = s[i] + V * ((V % (s[l] - s[i])) / len);
        Point R = s[i] + V * ((V % (s[k] - s[i])) / len);
        double W = (R - L).Len();
        double H = (V ^ (s[j] - s[i])) / sqrt(len);
        // printf("* %d %d %d\n" , j , k , l);
        // printf("%.10f %.10f\n" , W , H);
        if (W * H < res) {
            res = W * H;
            double t;
            P = L;
            X = R - L;
            //V.print();
            Y = Point(-V.y , V.x);
            // printf("*%f\n" , len);
            Y = Y * (1 / sqrt(len));
            //Y.print();
            Y = Y * H;
            
        }

    }
    //printf("%.10f\n" , res);
    P.print();
    (P + X).print();
    (P + X + Y).print();
    (P + Y).print();
    
    return 0;
}
