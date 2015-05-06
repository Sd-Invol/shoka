#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
const int M = 1000005;
int n , m , A , B , ca;
map< pair<int , int> , int > Hash; 
pair<int , int> a[N] , b[N];
vector<int> X[M] , Y[M];
void init() {
    int i ;
    Hash.clear();
    for (i = 1 ; i <= n ; ++ i) {
        X[i].clear();
    }
    for (i = 1 ; i <= m ; ++ i) {
        Y[i].clear();
    }
    for (i = 0 ; i < A ; ++ i) {
        scanf("%d%d" , &a[i].first , &a[i].second);
        Hash[a[i]] = 3;
        X[a[i].first].push_back(a[i].second);
        Y[a[i].second].push_back(a[i].first);      
    }
    for (i = 0 ; i < B ; ++ i) {
        scanf("%d%d" , &b[i].first , &b[i].second);
        Hash[b[i]] = 1;
        X[b[i].first].push_back(b[i].second);
        Y[b[i].second].push_back(b[i].first);      
    }
    for (i = 1 ; i <= n ; ++ i) {
        sort(X[i].begin() , X[i].end());
        X[i].resize(unique(X[i].begin() , X[i].end()) - X[i].begin());
    }
    for (i = 1 ; i <= m ; ++ i) {
        sort(Y[i].begin() , Y[i].end());        
        Y[i].resize(unique(Y[i].begin() , Y[i].end()) - Y[i].begin());
    }
}
int dx[] = {0 , 1 , 0 , -1};
int dy[] = {1 , 0 , -1 , 0};

pair<int , int> getnext(int x , int y , int d) {
    if (d == 0) {
        auto it = upper_bound(X[x].begin() , X[x].end() , y);
        if (it == X[x].end())
            return make_pair(x , m + 1);
        return make_pair(x , *it);
    }
    if (d == 1) {
        auto it = upper_bound(Y[y].begin() , Y[y].end() , x);
        if (it == Y[y].end())
            return make_pair(n + 1 , y);
        return make_pair(*it , y);
    }
    if (d == 2) {
        auto it = lower_bound(X[x].begin() , X[x].end() , y);
        if (it == X[x].begin())
            return make_pair(x , 0);        
        return make_pair(x , *(-- it));
    }
    if (d == 3) {
        auto it = lower_bound(Y[y].begin() , Y[y].end() , x);
        if (it == Y[y].begin())
            return make_pair(0 , y);
        return make_pair(*(-- it) , y);
    }   
}
vector< pair<int , int> > RouteS , RouteT;
vector< pair<int , int> > Up;
vector< pair<int , pair<int , int> > > Qry;
int c[M];
LL res;
void work() {
    init();
    res = 0;
    printf("Case %d: " , ++ ca);
    int i , j , k , x , y , d;
    x = 1 , y = 0 , d = 0;
    RouteS.clear();
    RouteS.push_back(make_pair(x , y));
    while (1) {
        pair<int , int> nxt = getnext(x , y , d);
        RouteS.push_back(nxt);
        x = nxt.first , y = nxt.second;
        if (!Hash.count(nxt))
            break;
        d ^= Hash[nxt];
    }
    if (x == n && y == m + 1) {
        puts("0");
        return;
    }
    x = n , y = m + 1 , d = 2;
    RouteT.clear();
    RouteT.push_back(make_pair(x , y));
    while (1) {
        pair<int , int> nxt = getnext(x , y , d);
        RouteT.push_back(nxt);
        x = nxt.first , y = nxt.second;
        if (!Hash.count(nxt))
            break;
        d ^= Hash[nxt];
    }
    set< int > P;
    Up.clear(); Qry.clear();
    for (i = 1 ; i < RouteS.size() ; ++ i) {
        if (RouteS[i].first == RouteS[i - 1].first) {
            int L = min(RouteS[i].second , RouteS[i - 1].second);
            int R = max(RouteS[i].second , RouteS[i - 1].second);
            Qry.push_back(make_pair(RouteS[i].first , make_pair(L , R - 1)));
        }
    }
    for (i = 1 ; i < RouteT.size() ; ++ i) {
        if (RouteT[i].second == RouteT[i - 1].second) {
            int L = min(RouteT[i].first , RouteT[i - 1].first);
            int R = max(RouteT[i].first , RouteT[i - 1].first);
            Up.push_back(make_pair(L + 1 , -RouteT[i].second));
            Up.push_back(make_pair(R , RouteT[i].second));
        }
    }
    sort(Up.begin() , Up.end());
    sort(Qry.begin() , Qry.end());
    memset(c , 0 , sizeof(c));
    pair<int , int> mn(1 << 30 , 1 << 30);
    for (i = j = 0 ; i < Qry.size() ; ++ i) {
        while (j < Up.size() && Up[j].first <= Qry[i].first) {
            if (Up[j].second < 0) {
                for (k = -Up[j].second ; k <= m ; k += k & -k)
                    ++ c[k];
                P.insert(-Up[j].second);
            } else {
                for (k = Up[j].second ; k <= m ; k += k & -k)
                    -- c[k];
                P.erase(Up[j].second);
            }
            ++ j;
        }
        for (k = Qry[i].second.second ; k > 0 ; k -= k & -k)
            res += c[k];
        for (k = Qry[i].second.first ; k > 0 ; k -= k & -k)
            res -= c[k];
        auto it = P.upper_bound(Qry[i].second.first);
        if (it != P.end() && *it <= Qry[i].second.second) {
            mn = min(mn , make_pair(Qry[i].first , *it));            
        }
    }

    Up.clear(); Qry.clear();
    for (i = 1 ; i < RouteT.size() ; ++ i) {
        if (RouteT[i].first == RouteT[i - 1].first) {
            int L = min(RouteT[i].second , RouteT[i - 1].second);
            int R = max(RouteT[i].second , RouteT[i - 1].second);
            Qry.push_back(make_pair(RouteT[i].first , make_pair(L , R - 1)));
        }
    }
    for (i = 1 ; i < RouteS.size() ; ++ i) {
        if (RouteS[i].second == RouteS[i - 1].second) {
            int L = min(RouteS[i].first , RouteS[i - 1].first);
            int R = max(RouteS[i].first , RouteS[i - 1].first);
            Up.push_back(make_pair(L + 1 , -RouteS[i].second));
            Up.push_back(make_pair(R , RouteS[i].second));
        }
    }
    sort(Up.begin() , Up.end());
    sort(Qry.begin() , Qry.end());
    memset(c , 0 , sizeof(c)) , P.clear();
    for (i = j = 0 ; i < Qry.size() ; ++ i) {
        while (j < Up.size() && Up[j].first <= Qry[i].first) {
            if (Up[j].second < 0) {
                for (k = -Up[j].second ; k <= m ; k += k & -k)
                    ++ c[k];
                P.insert(-Up[j].second);
            } else {
                for (k = Up[j].second ; k <= m ; k += k & -k)
                    -- c[k];
                P.erase(Up[j].second);
            }
            ++ j;
        }
        for (k = Qry[i].second.second ; k > 0 ; k -= k & -k)
            res += c[k];
        for (k = Qry[i].second.first ; k > 0 ; k -= k & -k)
            res -= c[k];
        auto it = P.upper_bound(Qry[i].second.first);
        if (it != P.end() && *it <= Qry[i].second.second) {
            mn = min(mn , make_pair(Qry[i].first , *it));            
        }
    }
    if (!res)
        puts("impossible");
    else {
        printf("%lld %d %d\n" , res , mn.first , mn.second);
    }
}

int main() {
    while (~scanf("%d%d%d%d",&n,&m,&A,&B))
        work();
    return 0;
}
