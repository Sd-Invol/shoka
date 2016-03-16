#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 1505;

struct Point {
    int x , y;
    Point (int _x = 0 , int _y = 0) {
        x = _x , y = _y;
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    LL operator ^ (const Point &R) const {
        return (LL)x * R.y - (LL)y * R.x;
    }
    int sign() const {
        if (y != 0)
            return y < 0;
        return x < 0;
    }
    bool operator < (const Point &R) const {
        if (this -> sign() != R.sign())
            return this -> sign() < R.sign();
        return (*this ^ R) > 0;
    }
};

int n , m , t;
Point A[N] , B[N] , C[N];
int s[N << 2];

int main() {
    freopen("ambitious.in" , "r" , stdin);
    freopen("ambitious.out" , "w" , stdout);
    
    while (scanf("%d" , &n) , n) {
        for (int i = 0 ; i < n ; ++ i)
            scanf("%d%d" , &A[i].x , &A[i].y);
        scanf("%d" , &m);
        for (int i = 0 ; i < m ; ++ i)
            scanf("%d%d" , &B[i].x , &B[i].y);
        scanf("%d" , &t);
        for (int i = 0 ; i < t ; ++ i)
            scanf("%d%d" , &C[i].x , &C[i].y);
    
        LL res = 0;
        for (int i = 0 ; i < m ; ++ i) {
            vector< pair<Point , bool> > V;
            for (int j = 0 ; j < n ; ++ j)
                V.push_back(make_pair(A[j] - B[i] , 1));
            for (int j = 0 ; j < t ; ++ j)
                V.push_back(make_pair(C[j] - B[i] , 0));

            sort(V.begin() , V.end());
            V.insert(V.end() , V.begin() , V.end());

            for (int j = 0 ; j < V.size() ; ++ j) {
                s[j + 1] = s[j] + V[j].second;
            }
            int cnt = 0 , S = 0;
            for (int l = 0 , r = 0 ; l < n + t ; ++ l) {

                while (l == r || (V[l].first ^ V[r].first) > 0) {               
                    if (!V[r].second) {
                        ++ cnt;
                        S += s[r + 1];
                    }
                    ++ r;
                }
                if (!V[l].second) {
                    res += S - cnt * s[l];
                    -- cnt;
                    S -= s[l + 1];
                }
            }
        
        }
        cout << res << endl;
    }
    return 0;
}
