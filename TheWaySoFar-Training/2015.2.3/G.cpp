#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000005;

int n , m;
bool f[N];

void work() {
    int i , x , y;
    scanf("%d%d",&n,&m);
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d",&x,&y);
        if (x > y) {
            puts("No");
            return;
        }            
        if (x + 1 == y)
            f[x] = 1;
    }
    for (i = 1 ; i < n ; ++ i)
        if (!f[i]) {
            puts("No");
            return;
        }
    puts("Yes");
}

int main() {
    work();
    return 0;
}
