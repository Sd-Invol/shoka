#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

typedef pair<double , double> Point;
#define x first
#define y second
const double pi = acos(-1);

double dis(Point A , Point B) {
    double dx = A.x - B.x;
    double dy = A.y - B.y;
    return dx * dx + dy * dy;
}
Point operator - (const Point& A , const Point& B) {
    return Point(A.x - B.x , A.y - B.y);
}
double len(const Point& A) {
    return sqrt(A.x * A.x + A.y * A.y);
}

int main() {
    Point A , B , P;
    scanf("%lf%lf" , &A.x , &A.y);
    scanf("%lf%lf" , &B.x , &B.y);
    scanf("%lf%lf" , &P.x , &P.y);
    double Ra = dis(A , P) , Rb = dis(B , P);
    Point da = A - P;
    Point db = B - P;
    double a = acos((da.x * db.x + da.y * db.y) / len(da) / len(db));
    if (a < 0) a += pi;

    Ra = sqrt(Ra) , Rb = sqrt(Rb);
    if (fabs(Ra - Rb) < 1e-10) {
        printf("%.10f\n" , a * len(A - P));
        return 0;
    }
    if (Ra < Rb) swap(A , B) , swap(Ra , Rb);

    double l = 0 , r = pi / 2;
    int T = 100;
    while (T --) {
        double m = (l + r) / 2;
        double AA = cos(m);
        double BB = sin(m);
        double R = Ra;
        double t = (Ra - Rb) / BB;
        double b = AA / BB * log(R / (R - BB * t));
        if (b > a)
            l = m;
        else
            r = m;
    }
        double m = (l + r) / 2;
        double AA = cos(m);
        double BB = sin(m);
        double R = Ra;
        double t = (Ra - Rb) / BB;
        double b = AA / BB * log(R / (R - BB * t));
    printf("%.10f\n" , t);
}
