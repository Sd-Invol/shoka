#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
int n , m;
pair<int , int> mx[21] , mn[21];
int main() {
    int i , j , x , y;
    scanf("%d%d",&n,&m);
    for (i = 1 ; i <= m ; ++ i) {
        mx[i] = make_pair(-1 << 30 , 0);
        mn[i] = make_pair(1 << 30 , 0);
    }
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d",&x,&y,&j);
        mx[j] = max(mx[j] , make_pair(x , i));
        mn[j] = min(mn[j] , make_pair(y , i));        
    }
    for (j = 1 ; j <= m ; ++ j) {
        if (mn[j].first < mx[j].first) {
            printf("TAK %d %d\n" , mn[j].second , mx[j].second);
        } else
            puts("NIE");
    }
    return 0;
}
