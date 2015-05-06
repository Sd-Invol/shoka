#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 55;
int n , ca;
int X[N] , Y[N] , Z[N] , Vx[N] , Vy[N] , Vz[N];
#define square(x) ((x)*(x))
struct event {
    double t;
    pair<int , int> A , B;
    event() {}
    event(double _t , int i , int j , int x , int y) {
        t = _t;
        A = make_pair(i , j);
        B = make_pair(x , y);
    }
    bool operator < (const event& R) const {
        return t < R.t;
    }
};
inline double dis(double t , int x , int y) {
    return sqrt(square(X[x] - X[y] + t * (Vx[x] - Vx[y])) + square(Y[x] - Y[y] + t * (Vy[x] - Vy[y])) + square(Z[x] - Z[y] + t * (Vz[x] - Vz[y])));
}
int f[N] , tree[N][N];
int getf(int x) {return x == f[x] ? x : f[x] = getf(f[x]);}
pair<double , int> d[N];
double T;
bool cmp(pair<int , int> A, pair<int , int> B) {
    return dis(T , A.first , A.second) < dis(T , B.first , B.second);
}
void work() {
    int i , j , k , x , y ;
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d%d%d%d%d%d",&X[i] , &Y[i] , &Z[i] , &Vx[i] , &Vy[i] , &Vz[i]);
    vector< event > E;
    for (i = 1 ; i <= n ; ++ i) {
        for (j = i + 1 ; j <= n ; ++ j) {
            for (x = i ; x <= n ; ++ x) {
                for (y = x == i ? j + 1 : x + 1 ; y <= n ; ++ y) {

                    int a = square(Vx[j] - Vx[i]) + square(Vy[j] - Vy[i]) + square(Vz[j] - Vz[i]) -
                            square(Vx[y] - Vx[x]) - square(Vy[y] - Vy[x]) - square(Vz[y] - Vz[x]);
                    int b = (((Vx[j] - Vx[i]) * (X[j] - X[i]) + (Vy[j] - Vy[i]) * (Y[j] - Y[i]) + (Vz[j] - Vz[i]) * (Z[j] - Z[i])) -
                             ((Vx[y] - Vx[x]) * (X[y] - X[x]) + (Vy[y] - Vy[x]) * (Y[y] - Y[x]) + (Vz[y] - Vz[x]) * (Z[y] - Z[x]))) << 1;
                    int c = square(X[j] - X[i]) + square(Y[j] - Y[i]) + square(Z[j] - Z[i]) -
                            square(X[y] - X[x]) - square(Y[y] - Y[x]) - square(Z[y] - Z[x]);

                    if (a == 0) {
                        if (b != 0) {
                        //    printf("%f\n" , -1.0 * c / b);
                            E.push_back(event(-1.0 * c / b , i , j , x , y));
                        }
                        continue;
                    }

                    int delta = b * b - 4 * a * c;
                    if (delta == 0) {
                        E.push_back(event(-1.0 * b / (a + a) , i , j , x , y));
                    } else if (delta > 0) {
                        double tmp = sqrt(delta);
                        E.push_back(event((-b + tmp) / (a + a) , i , j , x , y));
                        E.push_back(event((-b - tmp) / (a + a) , i , j , x , y));
                        //printf("%f\n" , (-b + sqrt(delta)) / (a + a));
                        //printf("%f\n" , (-b - sqrt(delta)) / (a + a));
                    }
                }
            }
        }
    }
    sort(E.begin() , E.end());

    memset(f , 0 , sizeof(f));
    memset(tree , 0 , sizeof(tree));
    for (i = 1 ; i <= n ; ++ i)
        d[i] = make_pair(1e30 , 0);
    d[1].first = 0;
    vector< pair<int , int> > edge;
    while (1) {
        x = -1;
        for (i = 1 ; i <= n ; ++ i)
            if (!f[i] && (!~x || d[x] > d[i]))
                x = i;
        if (!~x) break; f[x] = 1;
        tree[d[x].second][x] = tree[x][d[x].second] = 1;
        if (d[x].second) edge.push_back(make_pair(d[x].second , x));
        for (i = 1 ; i <= n ; ++ i)
            if (!f[i])
                d[i] = min(d[i] , make_pair(dis(0 , x , i) , x));
    }
    int ans = 1;

    for (int K = 0 ; K < (int)E.size() ; ++ K) {
        if (E[K].t <= 1e-7) continue;
        T = E[K].t + 1e-6;
        pair<int , int> A = E[K].A , B = E[K].B;
        if ((tree[A.first][A.second] ^ tree[B.first][B.second]) == 0)
            continue;
        if (tree[A.first][A.second])
            edge.push_back(B);
        else
            edge.push_back(A);
        sort(edge.begin() , edge.end() , cmp);
        for (i = 1 ; i <= n ; ++ i)
            f[i] = i;
        j = k = -1;
        for (i = 0 ; i < (int)edge.size() ; ++ i) {
            x = edge[i].first , y = edge[i].second;
            if (!tree[x][y]) k = i;
            if (getf(x) == getf(y)) {
                if (tree[x][y]) {
                    ++ ans;
                    j = i;
                    tree[x][y] = tree[y][x] = 0;
                }
            } else {
                f[getf(x)] = getf(y);
                if (!tree[x][y])
                    tree[x][y] = tree[y][x] = 1;
            }
        }
        //assert(edge.size() == n);

        if (~j) {
            swap(edge[j] , edge[n - 1]) , edge.pop_back();
        } else {
            swap(edge[k] , edge[n - 1]) , edge.pop_back();
        }
    }
    printf("Case %d: %d\n" , ++ ca , ans);
}

int main() {
    while (~scanf("%d",&n))
        work();
    return 0;
}
