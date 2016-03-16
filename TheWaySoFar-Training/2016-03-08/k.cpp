#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
typedef long long LL;
const int N = 2005;

struct Point {
    int x , y;
    Point (int _x = 0 , int _y = 0) {
        x = _x , y = _y;
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    int operator ^ (const Point &R) const {
        return x * R.y - y * R.x;
    }
    int sign() const {
        if (y != 0)
            return y < 0;
        return x < 0;
    }
    bool operator < (const Point &R) const {
        if (x != R.x)
            return x < R.x;
        return y < R.y;
    }
    bool operator == (const Point &R) const {
        return x == R.x && y == R.y;
    }
    int len() const {
        return x * x + y * y;
    }
};

bool cmp(const pair<Point , int> &AA , const pair<Point , int> &BB) {
    const Point &A = AA.first;
    const Point &B = BB.first;
    if (A.sign() != B.sign())
        return A.sign() < B.sign();
    return (A ^ B) > 0;
}

int n , D , id[N][2];
Point a[N][2] , d[N];
vector< pair<int , pair<int , int> > > E;
int f[N];
vector<int> add[N] , del[N];

int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}

Point P , V;
double len;
inline double distance(int i) {
    Point u = P - a[i][0] , w = a[i][1] - a[i][0];
    return len * (w ^ u) / (V ^ w);
}

struct segment {
    bool operator () (const int &x , const int &y) {
        double dx = distance(x);
        double dy = distance(y);
        return dx < dy;
        /*if (fabs(dx - dy) > 1e-6)
            return dx < dy;
            return x < y;*/
    }
};

int main() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < 2 ; ++ j) {
            scanf("%d%d" , &a[i][j].x , &a[i][j].y);
            d[D ++] = a[i][j];
        }
    }
    sort(d , d + D);
    D = unique(d , d + D) - d;

    for (int i = 0 ; i < n ; ++ i) {
        int x = lower_bound(d , d + D , a[i][0]) - d;
        int y = lower_bound(d , d + D , a[i][1]) - d;
        id[i][0] = x , id[i][1] = y;
        E.push_back(make_pair(0 , make_pair(x , y)));
    }

    for (int i = 0 ; i < D ; ++ i) {
        vector< pair<Point , int> > Vec;
        for (int j = 0 ; j < D ; ++ j) {
            if (i != j)
                Vec.push_back(make_pair(d[j] - d[i] , j));
        }
        for (int j = 0 ; j < D ; ++ j) {
            add[j].clear();
            del[j].clear();
        }
        set<int , segment> Hash;
        sort(Vec.begin() , Vec.end() , cmp);
        
        P = d[i];
        V = Point(1 , 0);
        len = 1;
        for (int j = 0 ; j < n ; ++ j) {
            int &x = id[j][0] , &y = id[j][1];
            if (x == i || y == i)
                continue;
            if (((d[x] - d[i]) ^ (d[y] - d[i])) < 0) {
                swap(x , y);
                swap(a[j][0] , a[j][1]);
            }
            if (d[y].y >= d[i].y && d[x].y < d[i].y) {
                Hash.insert(j);
                add[x].push_back(j);
                del[y].push_back(j);
            } else {
                add[x].push_back(j);
                del[y].push_back(j);
            }
        }

        for (int j = 0 ; j < (int)Vec.size() ; ++ j) {
            V = Vec[j].first;
            len = sqrt(V.len());
            int x = Vec[j].second;
            for (auto &k : del[x])
                Hash.erase(k);
            bool flag = 0;
            if (!Hash.empty()) {
                int k = *Hash.begin();
                if (((a[k][1] - a[k][0]) ^ (d[x] - a[k][0])) >= 0)
                    flag = 1;
            } else {
                flag = 1;
            }
            if (flag) {
                E.push_back(make_pair((d[i] - d[x]).len() , make_pair(i , x)));
            }
            for (auto &k : add[x])
                Hash.insert(k);
        }

    }

    for (int i = 0 ; i < D ; ++ i) {
        f[i] = i;
    }
    double res = 0;
    sort(E.begin() , E.end());
    for (int i = 0 ; i < (int)E.size() ; ++ i) {
        int x = getf(E[i].second.first);
        int y = getf(E[i].second.second);
        //printf("%d %d : %d\n" , E[i].second.first , E[i].second.second , E[i].first);
        if (x != y) {
            f[x] = y;
            res += sqrt(E[i].first);
        }
    }
    printf("%.10f\n" , res);
    return 0;
}
