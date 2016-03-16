#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 105;

const double eps = 1e-10 , pi = acos(-1.0);
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

Point A , B , C;
double R , g[N][N];

double cal(double X , double Y) {
    Point P(X , Y);
    return (P - A).len() + (P - B).len() + (P - C).len();
}
pair<double , double> check(double X) {
    double l = -5e5 , r = 5e5;
    for (int i = 0 ; i < 150 ; ++ i) {
        double m1 = (l + l + r) / 3;
        double m2 = (l + r + r) / 3;
        if (cal(X , m1) >= cal(X , m2))
            l = m1;
        else
            r = m2;
    }
    return make_pair(cal(X , (l + r) / 2) , (l + r) / 2);
}
double DistancePointToSegment(Point P , Point A , Point B) {
    if (A == B) return (P - A).len();
    Point v1 = B - A , v2 = P - A , v3 = P - B;
    if (dcmp(v1 % v2) < 0) return v2.len();
    if (dcmp(v1 % v3) > 0) return v3.len();
    return fabs(v1 ^ v2) / v1.len();
}
int getTangents(int x , Point P ,  vector< pair<double , int> >& sol) {
    Point u = P - C;
    double dist = u.len();
    if(dist < R) return 0;
    double arc = atan2(u.y , u.x);
    if(dcmp(dist - R) == 0) {
        g[x][2 + sol.size()] = g[sol.size() + 2][x] = 0;
        sol.push_back(make_pair(arc , 2 + sol.size()));
        return 1;
    } else {
        double ang = acos(R / dist);
        Point k2 = Point(C.x + R * cos(arc - ang) , C.y + R * sin(arc - ang));
        g[x][2 + sol.size()] = g[sol.size() + 2][x] = (P - k2).len();
        sol.push_back(make_pair(arc - ang , 2 + sol.size()));
        Point k1 = Point(C.x + R * cos(arc + ang) , C.y + R * sin(arc + ang));
        g[x][2 + sol.size()] = g[sol.size() + 2][x] = (P - k1).len();
        sol.push_back(make_pair(arc + ang , 2 + sol.size()));
        return 2;
    }
}

double cal(double a) {
    Point P = Point(C.x + R * cos(a) , C.y + R * sin(a));
    return (P - A).len() + (P - B).len();
}

int main() {
    A.input();
    B.input();
    C.input();

    double l = -5e5 , r = 5e5;
    for (int i = 0 ; i < 150 ; ++ i) {
        double m1 = (l + l + r) / 3;
        double m2 = (l + r + r) / 3;
        if (check(m1).first >= check(m2).first)
            l = m1;
        else
            r = m2;
    }
    double x = (l + r) / 2 , y = check(x).second;
    double res = cal(x , y);

    Point P = Point(x , y);
    scanf("%lf" , &R);

    if (dcmp((P - C).len() - R) >= 0) {
        printf("%.10f\n" , res - R);
        return 0;
    }

    for (int i = 0 ; i < 10 ; ++ i)
        for (int j = 0 ; j < 10 ; ++ j)
            g[i][j] = 1e30;
    vector< pair<double , int> > arc;
    getTangents(0 , A , arc);
    getTangents(1 , B , arc);
    for (int i = 0 ; i < arc.size() ; ++ i) {
        double &a = arc[i].first;
        while (a >= pi + pi) a -= pi + pi;
        while (a < 0) a += pi + pi;
    }
    if (dcmp(DistancePointToSegment(C , A , B) - R) > 0) {
        assert(arc.size() == 4);
        vector< pair<double , double> > a , b;
        if (arc[0].first < arc[1].first) {
            a.push_back(make_pair(arc[0].first , arc[1].first));
        } else {
            a.push_back(make_pair(0 , arc[1].first));
            a.push_back(make_pair(arc[0].first , pi + pi));
        }
        if (arc[2].first < arc[3].first) {
            b.push_back(make_pair(arc[2].first , arc[3].first));
        } else {
            b.push_back(make_pair(0 , arc[3].first));
            b.push_back(make_pair(arc[2].first , pi + pi));
        }
        res = 1e60;
        for (int i = 0 ; i < a.size() ; ++ i) {
            for (int j = 0 ; j < b.size() ; ++ j) {
                double l = max(a[i].first , b[j].first);
                double r = min(a[i].second , b[j].second);
                for (int k = 0 ; k < 100 && l < r ; ++ k) {
                    double m1 = (l + l + r) / 3;
                    double m2 = (l + r + r) / 3;
                    if (cal(m1) <= cal(m2))
                        r = m2;
                    else
                        l = m1;
                }
                if (l < r) {
                    res = min(res , cal((l + r) / 2));
                }
            }
        }
        printf("%.10f\n" , res);
    } else {

        sort(arc.begin() , arc.end());
        for (int i = 0 ; i < arc.size() ; ++ i) {
            //printf("%f\n" , arc[i].first);
            int j = (i + 1) % arc.size();
            double delta = abs(arc[i].first - arc[j].first);
            g[arc[i].second][arc[j].second] = min(delta , pi + pi - delta) * R;
            g[arc[j].second][arc[i].second] = min(delta , pi + pi - delta) * R;
        }
        for (int k = 0 ; k < 10 ; ++ k)
            for (int i = 0 ; i < 10 ; ++ i)
                for (int j = 0 ; j < 10 ; ++ j)
                    g[i][j] = min(g[i][j] , g[i][k] + g[k][j]);
        printf("%.10f\n" , g[0][1]);
    }
    return 0;
}
