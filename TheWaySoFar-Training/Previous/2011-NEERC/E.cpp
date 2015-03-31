#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 200005;
int n , m , K , t;
bool live[N];
bool sex[N];
int f[N + N];
int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}
map<int , int> h;
void work() {
    int i , j , x , y;
    char str[10];
    scanf("%d",&n);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%s" , str);
        live[i] = 1;
        if (*str == 'F')
            sex[i] = 1;
        else
            sex[i] = 0;
        f[i] = i;
    }
    scanf("%d",&m);
    for (i = 1 ; i <= m ; ++ i) {
        scanf("%d" , &x);
        if (x < 0) {
            live[-x] = 0;
        } else {
            scanf("%d%s" , &y , str);
            ++ n;
            live[n] = 1;
            if (*str == 'F')
                sex[n] = 1;
            else
                sex[n] = 0;
            f[n] = getf(y);
        }
    }
    scanf("%d" , &K) , t = n;
    for (i = 1 ; i <= K ; ++ i) {
        scanf("%d%d",&x,&y);
        if (!h.count(y)) {
            h[y] = ++ n;
            f[n] = n;
        }
        y = h[y];
        f[getf(x)] = y;
    }
    set<int> u;
    for (i = 1 ; i <= t ; ++ i)
        if (live[i])
            u.insert(getf(i));
    if (u.size() == 1) {
        puts("YES");
        return;
    }
    u.clear();
    for (i = 1 ; i <= t ; ++ i)
        if (live[i] && getf(i) > t)
            u.insert(getf(i));
    if (u.size() > 1) {
        puts("NO");
    } else
        puts("POSSIBLY");
}
int main() {
    freopen("eve.in" , "r" , stdin);
    freopen("eve.out" , "w" , stdout);
    work();
    return 0;
}
