#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 100005;

int n , q;
int res[N];
int X[N] , Y[N];
int xx[N] , yy[N];    
int id[N] , d0[N] , d1[N];
vector<int> e[N];

void BFS(int x , int *d) {
    queue<int> Q;
    Q.push(x) , d[x] = 0;
    while (!Q.empty()) {
        x = Q.front() , Q.pop();
        for (auto &y : e[x]) {
            if (!~d[y]) {
                d[y] = d[x] + 1;
                Q.push(y);
            }
        }
    }
}
inline int range(int x , int &A , int &B) {
    if (x == A || x == B)
        return 0;
    if (A < x && x < B)
        return 1;
    return 2;
}

void divide(vector<int> &L , vector<int> &E , vector<int> &Q) {
    if (E.empty())
        return;
    int m = 0;
    for (int i = 0 ; i < (int)L.size() ; ++ i) {
        int x = L[i];
        id[x] = m ++;
        e[x].clear();
        d0[x] = d1[x] = -1;
    }
    for (int i = 0 ; i < m ; ++ i) {
        int x = L[i] , y = L[(i + 1) % m];
        e[x].push_back(y);
        e[y].push_back(x);        
    }
    
    int size = 1 << 30 , edge = -1;
    for (int i = 0 ; i < (int)E.size() ; ++ i) {
        int x = id[X[E[i]]] , y = id[Y[E[i]]] , d = abs(x - y);
        d = max(d , m - d);
        if (d < size) {
            size = d;
            edge = i;
        }
        e[X[E[i]]].push_back(Y[E[i]]);
        e[Y[E[i]]].push_back(X[E[i]]);        
    }
    int A = id[X[E[edge]]] , B = id[Y[E[edge]]];
    if (A > B)
        swap(A , B);
    BFS(L[A] , d0);
    BFS(L[B] , d1);

    vector<int> Ll , Lr , El , Er , Ql , Qr;
    for (auto &i : Q) {
        res[i] = min(res[i] , 1 + d0[xx[i]] + d1[yy[i]]);
        res[i] = min(res[i] , 1 + d0[yy[i]] + d1[xx[i]]);
        res[i] = min(res[i] , d0[xx[i]] + d0[yy[i]]);
        res[i] = min(res[i] , d1[xx[i]] + d1[yy[i]]);        
        int mask = range(id[xx[i]] , A , B) | range(id[yy[i]] , A , B);
        if (mask == 1)
            Ql.push_back(i);
        else if (mask == 2)
            Qr.push_back(i);
    }
    for (auto &i : E) {
        int mask = range(id[X[i]] , A , B) | range(id[Y[i]] , A , B);
        if (mask == 1)
            El.push_back(i);
        else if (mask == 2)
            Er.push_back(i);
    }
    for (int i = A ; i <= B ; ++ i)
        Ll.push_back(L[i]);
    for (int i = B ; i < m ; ++ i)
        Lr.push_back(L[i]);
    for (int i = 0 ; i <= A ; ++ i)
        Lr.push_back(L[i]);
    divide(Ll , El , Ql);
    divide(Lr , Er , Qr);    
}

int main() {
    vector<int> L , E , Q;
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i)
        L.push_back(i);
    for (int i = 0 ; i < n - 3 ; ++ i) {
        scanf("%d%d" , &X[i] , &Y[i]);
        -- X[i] , -- Y[i];
        E.push_back(i);
    }    
    scanf("%d" , &q);
    for (int i = 0 ; i < q ; ++ i) {
        scanf("%d%d" , &xx[i] , &yy[i]);
        -- xx[i] , -- yy[i];
        Q.push_back(i);
        int dis = abs(xx[i] - yy[i]);
        res[i] = min(dis , n - dis);
    }
    divide(L , E , Q);
    for (int i = 0 ; i < q ; ++ i)
        printf("%d\n" , res[i]);
    return 0;
}
