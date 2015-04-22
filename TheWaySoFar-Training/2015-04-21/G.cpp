#include <bits/stdc++.h>
using namespace std;
const int N = 50005;
int n , M ,  m , f[N];
struct Point {
    int x , y;
}a[N];
struct edge {
    int x , y , w;
    bool operator < (const edge& R) const {
        return w < R.w;
    }
}e[N * 100];
set< int > Hash;
vector< pair<int , int> > V[30005];
int getf(int x) {return f[x] == x ? x : f[x] = getf(f[x]);}
int main() {
    freopen("randommst.in", "r", stdin);
    freopen("randommst.out", "w", stdout);
    //srand(time(0));
    int i , j , x , y;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        //x = rand() % 30001;
        //y = rand() % 30001;        
        Hash.insert(x);
        V[x].push_back(make_pair(y , i));
        a[i] = (Point) {x , y};
    }
    for (i = 0 ; i <= 30000 ; ++ i)
        sort(V[i].begin() , V[i].end());
    if (n <= 1000) {
        for (i = 0 ; i < n ; ++ i) {
            for (j = i + 1 ; j < n ; ++ j) {
                int dx = a[j].x - a[i].x;
                int dy = a[j].y - a[i].y;
                e[m ++] = (edge) {i + 1 , j + 1 , dx * dx + dy * dy};
            }            
        }
    } else {
        M = 70000 / sqrt(n);
        for (i = 0 ; i < n ; ++ i) {
            x = a[i].x , y = a[i].y;
            auto itl = Hash.lower_bound(x - M);
            auto itr = Hash.upper_bound(x);
            for (auto it = itl ; it != itr ; ++ it) {
                vector< pair<int , int> >& Vec = V[*it];
                auto ti = lower_bound(Vec.begin() , Vec.end() , make_pair(y , -1));
                if (ti != Vec.end()) {
                    j = ti -> second;
                    int dx = a[j].x - a[i].x;
                    int dy = a[j].y - a[i].y;
                    if (abs(dy) < M)
                        e[m ++] = (edge) {i + 1 , j + 1 , dx * dx + dy * dy};
                }
                if (ti != Vec.begin()) {
                    -- ti;
                    j = ti -> second;
                    int dx = a[j].x - a[i].x;
                    int dy = a[j].y - a[i].y;
                    if (abs(dy) < M)
                        e[m ++] = (edge) {i + 1 , j + 1 , dx * dx + dy * dy};
                }
            }
        }
    }
    sort(e , e + m);
    double res = 0;
    for (i = 1 ; i <= n ; ++ i)
        f[i] = i;
    int cnt = 0;
    for (i = 0 ; i < m ; ++ i) {
        x = getf(e[i].x) , y = getf(e[i].y);
        if (x != y) {
            f[x] = y;
            res += sqrt(e[i].w);
            ++ cnt;
        }
    }
    assert(cnt + 1 == n);
    printf("%.15f\n" , res);
    for (i = 1 ; i <= n ; ++ i)
        f[i] = i;  
    for (i = 0 ; i < m ; ++ i) {
        x = getf(e[i].x) , y = getf(e[i].y);
        if (x != y) {
            f[x] = y;
            printf("%d %d\n" , e[i].x , e[i].y);
        }
    }    
    return 0;
}
