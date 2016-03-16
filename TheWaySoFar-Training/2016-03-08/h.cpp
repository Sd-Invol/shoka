#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const int N = 100005;

int m , n , K;
vector<int> cnt[N];
map<int , int> D;
int H[N];
struct human {
    char name[15];
    int dep , id , bir;
    void input() {        
        int x;
        scanf("%d" , &x);
        if (!D.count(x)) {
            D[x] = ++ n;
            H[n] = x;
        }
        x = D[x];
        dep = x;
        id = cnt[x].size() + 1;
        scanf("%s" , name);
        int dd , mm , yy;
        scanf("%d:%d:%d" , &dd , &mm , &yy);
        bir = yy * 10000 + mm * 100 + dd;
    }
    bool operator < (const human &R) const {
        if (bir != R.bir)
            return bir < R.bir;
        if (dep != R.dep)
            return H[dep] < H[R.dep];
        return id < R.id;
    }
} P[N];

struct cmp {
    bool operator () (const int &x , const int &y) {
        return P[x] < P[y];
    }
};
set<int , cmp> S[N] , O;

int main() {
    scanf("%d" , &m);
    for (int i = 0 ; i < m ; ++ i) {
        int o , d;
        scanf("%d" , &o);
        if (o == 1) {
            P[++ K].input();
            cnt[P[K].dep].push_back(K);            
            S[P[K].dep].insert(K);
            O.insert(K);
            d = P[K].dep;
        } else {
            int x , y;
            scanf("%d%d" , &x , &y);
            x = D[x]; int p = cnt[x][y - 1];
            S[x].erase(p);
            O.erase(p);
            d = x;
        }
        if (!O.empty())
            printf("%s " , P[*O.begin()].name);
        else
            printf("Vacant ");
        if (!S[d].empty())
            printf("%s\n" , P[*S[d].begin()].name);
        else
            printf("Vacant\n");        
    }
}
