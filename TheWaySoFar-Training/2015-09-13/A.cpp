#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <cctype>
#include <map>
using namespace std;
typedef long long LL;
const int N = 200005;

int K , m , q;
struct peo {
    int v , t;
    char str[205];
    bool operator < (const peo& R) const {
        return make_pair(-v , t) > make_pair(-R.v , R.t);
    }
}a[N];
priority_queue<peo> Q;
int res[N];
pair<int , int> b[N];
void work() {
    scanf("%d%d%d" , &K , &m , &q);
    for (int i = 0 ; i < K ; ++ i) {
        scanf("%s%d" , a[i].str , &a[i].v);
        a[i].t = i + 1;
    }
    for (int i = 0 ; i < m ; ++ i) {
        scanf("%d%d" , &b[i].first , &b[i].second);
    }
    sort(b , b + m);
    int tmp = 0;
    b[m ++] = make_pair(K + 10 , K + 10);
    for (int i = 0 , j = 0 ; i < m ; ++ i) {
        while (j < K && a[j].t <= b[i].first) {
            Q.push(a[j]);
            ++ j;
        }
        while (b[i].second && !Q.empty()) {
            res[++ tmp] = Q.top().t - 1;
            Q.pop();
            -- b[i].second;
        }
    }
    for (int i = 0 ; i < q ; ++ i) {
        int x;
        scanf("%d" , &x);
        printf("%s%c" , a[res[x]].str , " \n"[i + 1 == q]);
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
