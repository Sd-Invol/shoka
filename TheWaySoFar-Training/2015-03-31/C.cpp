#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 10005;

const double pi = acos(-1);
#define x first
#define y second
typedef pair<double , double> Point;

Point Rotate(Point A , double rad) {
    double SIN = sin(rad) , COS = cos(rad);
    return Point(A.x * COS - A.y * SIN , A.x * SIN + A.y * COS);
}

int T;
int main() {
    scanf("%d" , &T);
    for (int t = 1 ; t <= T ; ++ t) {
        double W , H;
        Point p , w , u , v;
        double arc , s;
        scanf("%lf%lf",&W,&H);
        scanf("%lf%lf",&p.x,&p.y);
        scanf("%lf%lf",&w.x,&w.y);
        scanf("%lf%lf" , &arc , &s);
        u.x = W - p.x , u.y = H - p.y;
        v.x = -p.x , v.y = -p.y;
        v = Rotate(v , arc / 180 * pi);       
        u = Rotate(u , arc / 180 * pi);               
        v.x *= s , v.y *= s;
        u.x *= s , u.y *= s;        
        v.x += w.x , v.y += w.y;
        u.x += w.x , u.y += w.y;
        p = Point(0.5 * (u.x + v.x) , 0.5 * (u.y + v.y));
        v.x -= p.x , v.y -= p.y;
        v = Rotate(v , -arc / 180 * pi);
        v.x += p.x , v.y += p.y;
        W *= s , H *= s;
        printf(".item%d { width: %.1fpx; height: %.1fpx; left: %.1fpx; top: %.1fpx; transform: rotate(%.1fdeg); }\n" , t , W , H , v.x , v.y , arc);
    }
    return 0;    
}
/*
.item1 { width: 100.0px; height: 50.0px; left: 376.5px; top: 183.8px; transform: rotate(45.0deg); }
.item2 { width: 400.0px; height: 200.0px; left: 250.0px; top: 200.0px; transform: rotate(90.0deg); }
.item1 { width: 100.0px; height: 50.0px; left: 376.5px; top: 183.8px; transform: rotate(45.0deg); }
.item2 { width: 400.0px; height: 200.0px; left: 250.0px; top: 200.0px; transform: rotate(90.0deg); }
 */
