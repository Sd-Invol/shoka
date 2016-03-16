#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 10005;

int next(int a , int b) {
    return rand() % (b - a + 1) + a;
}
int wnext(int a, int b, int type) {
    int result = next(a, b);
    for (int i = 0; i < type; i++)
        result = max(result, next(a, b));
    for (int i = 0; i < -type; i++)
        result = min(result, next(a, b));
    return result;
}
const int n = 10000;
vector<int> e[N];
int dis[N];
void add_edge(int x , int y) {
    e[x].push_back(y);
    e[y].push_back(x);
}
LL deg(int m) {
    LL res = 0;
    for (int i = 0 ; i < n ; ++ i)
        res += (LL)e[i].size() * e[i].size();
    return res;
}
void dfs(int x , int fa , int *d) {
    for (auto &y : e[x]) {
        if (y != fa) {
            d[y] = d[x] + 1;
            dfs(y , x  , d);
        }
    }
}
int dia(int m) {
    dis[0] = 0 , dfs(0 , -1 , dis);
    int x = 0;
    for (int i = 1 ; i < m ; ++ i)
        if (dis[i] > dis[x])
            x = i;    
    dis[x] = 0 , dfs(x , -1 , dis);
    x = 0;
    for (int i = 1 ; i < m ; ++ i)
        if (dis[i] > dis[x])
            x = i;
    return dis[x];
}

LL make(int type) {
    for (int i = 0 ; i < n ; ++ i) {
        e[i].clear();
    }
    for (int i = 1; i < n; ++i) 
        add_edge(i ,wnext(0, i - 1, type));
    return deg(n);
}
double ha[] = {15.831000000000,17.514000000000,20.102000000000,
               24.737000000000,36.521000000000,53.235000000000,
               66.527000000000,77.883000000000,88.001000000000};
double de[] = {114397.57,100498.07,86850.12,73259.28,59955.16,53319.33,51978.59,51403.43,51084.23};

void work() {
    int m;
    scanf("%d" , &m);
    for (int i = 0 ; i < m ; ++ i)
        e[i].clear();
    for (int i = 1 ; i < m ; ++ i) {
        int x;
        scanf("%d" , &x);
        e[x].push_back(i);
        e[i].push_back(x);        
    }
    int D = dia(m);
    int dd = deg(m);
    pair<double , int> res(1e60 , -100);
    for (int i = 0 ; i < 9 ; ++ i)
        res = min(res , make_pair(fabs(de[i] - dd) , i - 4));
    /* if (res.second > 2) {
        double d3 = fabs(ha[7] - D);
        double d4 = fabs(ha[8] - D);
        if (d3 < d4)
            res.second = 3;
        else
            res.second = 4;
            } */
    printf("%d\n" , res.second);
}

int main() {
    /*(for (int t = -4 ; t <= 4 ; ++ t) {
        LL cnt = 0;
        LL mx = -1LL << 60 , mn = 1LL << 60;
        for (int T = 0 ; T < 200 ; ++ T) {
            LL res = make(t);
            cnt += res;
            mx = max(mx , res);
            mn = min(mn , res);
        }
        printf("%.2f," , cnt / 200.0);
        //printf("%+d : %.5f %lld %lld\n" , t , cnt / 200.0 , mn , mx);
        }*/
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
