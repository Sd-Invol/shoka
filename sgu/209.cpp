#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;
typedef long long LL;

const double eps = 1e-10 , pi = acos(-1.0);
int dcmp(double x) {
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
    void output() {
        printf("(%f,%f)", x + eps , y + eps);
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
    double len()
    {
        return sqrt(*this % *this);
    }
};
// 向量的极角，[0,2pi)
double Angle(Point V) {
    return atan2(V.y , V.x);
}
// 两个向量的夹角，不分正负
double Angle(Point A , Point B) {
    return acos((A % B) / A.len() / B.len());
}
// 逆时针旋转
Point Rotate(Point A , double rad) {
    double Sin = sin(rad) , Cos = cos(rad);
    return Point(A.x * Cos - A.y * Sin , A.x * Sin + A.y * Cos);
}
// 向量的单位法向量，利用旋转得到
Point Normal(Point A) {
    double L = A.len();
    return Point(-A.y / L , A.x / L);
}
// 直线交点，v和w为两个直线的方向向量，
// 设交点的参数为P+vt,Q+wt,连立方程解t
// 线段，射线对这个t的参数有限制，很好理解。
Point GetLineIntersection(Point P , Point v , Point Q , Point w) {
    Point u = P - Q;
    double t1 = (w ^ u) / (v ^ w);
    return P + v * t1;
}
// 点到直线距离，这里直线是用两个点表示的
double DistancePointToLine(Point P , Point A , Point B) {
    Point v = B - A;
    return (v ^ (P - A)) / v.len();
}
// 点到线段距离，就是上面的代码判断一下P在AB上投影的位置。
double DistancePointToSegment(Point P , Point A , Point B) {
    if (A == B) return (P - A).len();
    Point v1 = B - A , v2 = P - A , v3 = P - B;
    if (dcmp(v1 % v2) < 0) return v2.len();
    if (dcmp(v1 % v3) > 0) return v3.len();
    return fabs(v1 ^ v2) / v1.len();
}
// 返回点在直线上的投影
Point GetLineProjection(Point P , Point A , Point B) {
    Point v = B - A;
    return A + v * (v % (P - A) / (v % v));
}
// 判断线段是否相交，没有考虑共线的情况。
bool SegmentProperIntersection(Point a1 , Point a2 , Point b1 , Point b2) {
    double c1 = (a2 - a1) ^ (b1 - a1);
    double c2 = (a2 - a1) ^ (b2 - a1);
    double c3 = (b2 - b1) ^ (a1 - b1);
    double c4 = (b2 - b1) ^ (a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
// 点是否在线段上,判定方式为到两个端点的方向是否不一致。
bool OnSegment(Point P , Point a1 , Point a2) {
    return dcmp((a1 - P) ^ (a2 - P)) == 0 && dcmp((a1 - P) % (a2 - P)) < 0;
}

#define N 80 * 80 * 2
int n , m;
Point A[N] , V[N] , P[N];
vector<Point> B[N];
vector<int> e[N];
vector<int> f[N];
int Var;
bool cmp(int i , int j) {
    return Angle(P[i] - P[Var]) < Angle(P[j] - P[Var]);
}
set< pair<int , int> > hash;
vector<double> res;

void dfs(int x , int y , int S , double area) {
    hash.insert(make_pair(x , y));
    if (y == S) {
        if (dcmp(area) > 0)
            res.push_back(area / 2);
        return;
    }
    for (int i = 0 ; i < e[y].size() ; ++ i) {
        if (e[y][i] == x) {
            if (!i) {
                int z = e[y][e[y].size() - 1];
                dfs(y , z , S , area + (P[y] ^ P[z]));
            } else {
                int z = e[y][i - 1];
                dfs(y , z , S , area + (P[y] ^ P[z]));
            }
            return;
        }
    }
}

void work()
{
    int i , j , x , y;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i)
        A[i].input() , V[i].input() , V[i] = V[i] - A[i];

    m = 0;
    for (i = 0 ; i < n ; ++ i) {
        for (j = i + 1 ; j < n ; ++ j) {
            if (dcmp(V[i] ^ V[j]) == 0)
                continue;
            Point tmp = GetLineIntersection(A[i] , V[i] , A[j] , V[j]);
            P[m ++] = tmp , B[i].push_back(tmp) , B[j].push_back(tmp);
        }
    }
    sort(P , P + m) , m = unique(P , P + m) - P;
    for (i = 0 ; i < n ; ++ i) {
        sort(B[i].begin() , B[i].end());
        B[i].erase(unique(B[i].begin() , B[i].end()) , B[i].end());
        for (j = 1 ; j < (int)B[i].size() ; ++ j) {
            x = lower_bound(P , P + m , B[i][j - 1]) - P;
            y = lower_bound(P , P + m , B[i][j]) - P;
            e[x].push_back(y) , e[y].push_back(x);
        }
    }
    for (i = 0 ; i < m ; ++ i) {
        Var = i;
        sort(e[i].begin() , e[i].end() , cmp);
        f[i].resize(e[i].size());
    }

    for (i = 0 ; i < m ; ++ i) {
        for (j = 0 ; j < e[i].size() ; ++ j) {
            if (hash.count(make_pair(i , e[i][j])))
                continue;
            dfs(i , e[i][j] , i , P[i] ^ P[e[i][j]]);
        }
    }
    sort(res.begin() , res.end());
    printf("%d\n" , res.size());
    for (i = 0 ; i < res.size() ; ++ i) {
        printf("%.4f\n" , res[i]);
    }
}

int main()
{
    work();
    return 0;
}
