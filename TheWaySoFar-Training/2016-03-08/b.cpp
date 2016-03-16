#include <bits/stdc++.h>
using namespace std;
const int N = 2005;

const double eps = 1e-8;
const double pi = acos(-1);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}

struct Point {
    double x , y;
    Point (double x = 0 , double y = 0) : x(x) , y(y) {} 
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
    double operator % (const Point& R) const{
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
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
    Circle (Point _O , double _r) {O = _O , r = _r;}
    Point point(double arc) {
        return Point(O.x + cos(arc) * r , O.y + sin(arc) * r);
    }
    void input() {
        O.input();
        scanf("%lf",&r);
    }
};

int n , m , K;
Point P[N];
Circle c[N];
double sx , sy , s;

void getarea() {

    for (int i = 0 ; i < n ; ++ i) {
        vector< pair<double , int> > Vec;
        int cnt = 1;        
        Vec.push_back({0 , 0});
        Vec.push_back({2 * pi , 0});
        
        for (int j = 0 ; j < n ; ++ j) {
            double dist = (c[j].O - c[i].O).len();
            if (dcmp(dist) == 0 && dcmp(c[i].r - c[j].r) == 0) {
                if (i < j) {
                    ++ cnt;
                }
                continue;
            }
            if (dcmp(dist - c[j].r - c[i].r) >= 0) {
                continue;
            }
            if (dcmp(dist + c[j].r - c[i].r) <= 0) { // j in i
                continue;
            }
            if (dcmp(dist + c[i].r - c[j].r) <= 0) { // i in j
                ++ cnt;
                continue;
            }            
            double an = atan2(c[j].O.y - c[i].O.y , c[j].O.x - c[i].O.x);
            double p = (c[i].r * c[i].r + dist * dist - c[j].r * c[j].r) / (2 * c[i].r * dist);
            double da = acos(max(-1.0 , min(1.0 , p)));
            
            double L = an - da , R = an + da;
            //printf("%d : %f %f\n" , j , L , R);
            if (L < 0) L += 2 * pi;
            if (R < 0) R += 2 * pi;
            if (L >= 2 * pi) L -= 2 * pi;
            if (R >= 2 * pi) R -= 2 * pi;            
            if (L < R) {                              
                Vec.push_back({L , 1});
                Vec.push_back({R , -1});
            } else {
                Vec.push_back({0 , 1});
                Vec.push_back({R , -1});
                Vec.push_back({L , 1});
                Vec.push_back({2 * pi , -1});
            }
        }
        sort(Vec.begin() , Vec.end());        
        for (int j = 0 ; j + 1 < Vec.size() ; ++ j) {
            //printf("%d : %d %f\n" , j , cnt , Vec[j].first);
            cnt += Vec[j].second;
            if (cnt == 1) {
                double delta = Vec[j + 1].first - Vec[j].first;
                if (dcmp(delta) <= 0)
                    continue;
                double SIN = sin(delta / 2);
                Point W = Point(0 , 4 * c[i].r * SIN * SIN * SIN / (3 * (delta - sin(delta))));
                W = Rotate(W , (Vec[j + 1].first + Vec[j].first - pi) / 2) + c[i].O;
                double area = c[i].r * c[i].r * (delta - sin(delta));
                sx -= area * W.x;
                sy -= area * W.y;
                s -= area;
                
                Point A = c[i].point(Vec[j].first) , B = c[i].point(Vec[j + 1].first);
                area = (A ^ B);
                sx -= area * (A.x + B.x) / 3;
                sy -= area * (A.y + B.y) / 3;                
                s -= area;                
            }
        }        
    } 
}

bool f[N];
void work() {    
    for (int i = 0 ; i < m ; ++ i) {
        P[i].input();
    }
    for (int i = 0 ; i < n ; ++ i) {
        c[i].input();
        if (dcmp(c[i].r) == 0) {
            -- i;
            -- n;
        }
    }
    memset(f , 0 , sizeof(f));
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < n ; ++ j) {
            if (i != j) {                
                double dist = (c[j].O - c[i].O).len();
                if (dcmp(dist) == 0 && dcmp(c[i].r - c[j].r) == 0) {
                    if (i < j) {
                        f[i] = 1;
                        break;
                    }
                    continue;
                }
                if (dcmp(dist + c[i].r - c[j].r) <= 0) {
                    f[i] = 1;
                    break;
                }     
            }
        }
    }
    int w = 0;
    for (int i = 0 ; i < n ; ++ i) {
        if (!f[i]) 
            c[w ++] = c[i];
    }
    n = w;
    sx = sy = s = 0;
    for (int i = 0 ; i < m ; ++ i) {
        Point A = P[i] , B = P[(i + 1) % m];
        double area = (A ^ B);
        sx += area * (A.x + B.x) / 3;
        sy += area * (A.y + B.y) / 3;                
        s += area;
    }
    
    getarea();
    Point C(sx / s , sy / s) , O = P[-- K];
    double arc = -pi / 2 - atan2(C.y - O.y , C.x - O.x);
    for (int i = 0 ; i < m ; ++ i) {
        Point E = Rotate((P[i] - O) , arc) + O;
        printf("%.10f %.10f\n" , E.x , E.y);
    }
}

int main() {
    while (~scanf("%d%d%d" , &m , &n , &K))
        work();
    return 0;
}
