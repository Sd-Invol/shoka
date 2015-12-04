#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <set>
using namespace std;
typedef long long LL;
const int N = 205;

const double eps = 1e-4 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}

struct Point {
    double x , y;
    Point (double _x = 0 , double _y = 0) {
        x = _x , y = _y;
    }
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
    double arg() {
        return atan2(y , x);
    }
};

int n;
Point L[N] , P[N * N];
int pre[N * N] , mcnt;
struct edge {
    int x , next;
}e[N * N * 2];
int Next[N * N * 2];
bool vis[N * N * 2];
Point GetLineIntersection(Point P , Point v , Point Q , Point w) {
    Point u = P - Q;
    double t1 = (w ^ u) / (v ^ w);
    return P + v * t1;
}
bool OnSegment(Point P , Point a1 , Point a2) {
    return dcmp((a1 - P) ^ (a2 - P)) == 0 && dcmp((a1 - P) % (a2 - P)) <= 0;
}
void work() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        L[i].input();
        P[i] = L[i];
    }
    int m = n;
    for (int i = 0 ; i + 1 < n ; ++ i)        
        for (int j = i + 1 ; j + 1 < n ; ++ j) {
            if (dcmp((P[i + 1] - P[i]) ^ (P[j + 1] - P[j])) != 0)
                P[m ++] = GetLineIntersection(P[i] , P[i + 1] - P[i] , P[j] , P[j + 1] - P[j]);
        }
    sort(P , P + m);
    m = unique(P , P + m) - P;
    memset(pre , -1 , sizeof(pre));
    set< pair<int , int> > Hash;
    for (int i = 0 ; i + 1 < n ; ++ i) {
        vector< pair <Point , int> > V;
        for (int j = 0 ; j < m ; ++ j)
            if (OnSegment(P[j] , L[i] , L[i + 1]))
                V.push_back(make_pair(P[j] , j));
        sort(V.begin() , V.end());
        for (int j = 0 ; j + 1 < V.size() ; ++ j) {
            int x = V[j].second , y = V[j + 1].second; 
            if (!Hash.count(make_pair(x , y))) {
                Hash.insert(make_pair(x , y));
                e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
            }
            if (!Hash.count(make_pair(y , x))) {
                Hash.insert(make_pair(y , x));
                e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
            }
        }
    }
    for (int x = 0 ; x < m ; ++ x) {
        vector< pair<double , int> > V;
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            V.push_back(make_pair((P[y] - P[x]).arg() , i));
        }
        sort(V.begin() , V.end());
        for (int i = 0 ; i < V.size() ; ++ i) {
            int j = (i + 1) % V.size();
            Next[V[j].second ^ 1] = V[i].second;
        }
    }
    double res = 0;
    for (int i = 0 ; i < mcnt ; ++ i) {
        if (!vis[i]) {
            int x = i;
            double area = 0;
            while (!vis[x]) {
                vis[x] = 1;
                area += (P[e[x ^ 1].x] ^ P[e[x].x]);
                x = Next[x];
            }
            if (x == i && dcmp(area) > 0)
                res += area;
        }
    }
    printf("%.8f\n" , res / 2);
}

int main() {
    work();
    return 0;
}