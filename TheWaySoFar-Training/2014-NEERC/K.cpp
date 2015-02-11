#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int N = 1000005;
int n , m , C , h , u;
int cnt[N] , a[N] , b[N];
bool res[N];
multiset<int> H;
void work() {
    int i , x ;
    memset(cnt , 0 , sizeof(cnt));
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d",&a[i]);
        ++ cnt[a[i]];
    }
    scanf("%d" , &u);
    memset(b , 0 , sizeof(b));
    for (i = 2 ; i <= m ; ++ i) {
        scanf("%d" , &x);
        ++ b[x];
    }
    if (m == 1) x = u;
    if (n == 1) {
        if (x == h)
            puts("1\n1");
        else
            puts("0\n");
        return;
    }
    H.clear();
    for (i = 1 ; i <= C ; ++ i)
        if (i != h)
            H.insert(cnt[i] + b[i]);
    memset(res , 0 , sizeof(res));
    for (i = 1 ; i <= C ; ++ i) {
        if (!cnt[i]) continue;
        if (i != u) {
            if (i != h)
                H.erase(H.find(cnt[i] + b[i]));
            if (u != h)
                H.erase(H.find(cnt[u] + b[u]));
            cnt[i] -= 1 , cnt[u] += 1;
            if (i != h)
                H.insert(cnt[i] + b[i]);
            if (u != h)
                H.insert(cnt[u] + b[u]);
        }
        if (*-- H.end() + (m - 1) < cnt[h] + b[h])
            res[i] = 1;
        if (i != u) {
            if (i != h)
                H.erase(H.find(cnt[i] + b[i]));
            if (u != h)
                H.erase(H.find(cnt[u] + b[u]));
            cnt[i] += 1 , cnt[u] -= 1;
            if (i != h)
                H.insert(cnt[i] + b[i]);
            if (u != h)
                H.insert(cnt[u] + b[u]);
        }
    }
    vector<int> ans;
    for (i = 1 ; i <= n ; ++ i)
        if (res[a[i]])
            ans.push_back(i);
    printf("%d\n" , ans.size());
    for (i = 0 ; i < ans.size() ; ++ i) {
        if (i) putchar(' ');
        printf("%d" , ans[i]);
    }
    puts("");
}

int main() {
    freopen("kabaleo.in","r",stdin);
    freopen("kabaleo.out","w",stdout);
    while (~scanf("%d%d%d%d",&n,&m,&C,&h))
        work();
    return 0;
}
