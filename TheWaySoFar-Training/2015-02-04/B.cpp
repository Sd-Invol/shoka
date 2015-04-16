#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m , q;
int a[N] , b[N];
char str[N];
map< pair<int , int> , int > Hash;
bool cal(int x , int y) {
    if (y == 0) return a[x];
    if (x == 0) return b[y];
    if (x <= 2 || y <= 2) {
        if (Hash.count(make_pair(x , y)))
            return Hash[make_pair(x , y)];    
        return Hash[make_pair(x , y)] = !(cal(x - 1 , y) && cal(x , y - 1));
    }
    int z = min(x - 2 , y - 2);
    return cal(x - z , y - z);
}

void work() {
    int i , x , y;
    scanf("%d%d%d",&n,&m,&q);
    scanf("%s" , str);
    for (i = 1 ; i <= n ; ++ i)
        a[i] = str[i - 1] - '0';
    scanf("%s" , str);    
    for (i = 1 ; i <= m ; ++ i)
        b[i] = str[i - 1] - '0';
    while (q --) {
        scanf("%d%d",&x,&y);
        puts(cal(x , y) ? "Yes" : "No");
    }
}

int main() {
    work();
    return 0;
}
