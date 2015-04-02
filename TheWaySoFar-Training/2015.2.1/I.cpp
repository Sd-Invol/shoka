#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , K , a[N];
LL s , res[N];

void work() {
    int i , j , k , x , y;
    scanf("%d%d",&n,&K);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
        if (a[i] < 0) {
            s += a[i];
            a[i] = -a[i];
        }
    }
    sort(a + 1 , a + n + 1);
    priority_queue< pair<LL , int> > Q;
    Q.push(make_pair(-a[1] , 1));
    res[0] = s;
    for (int k = 1 ; k <= K && !Q.empty() ; ++ k) {
        pair<LL , int> t = Q.top(); Q.pop();
        res[k] = s - t.first , j = t.second;
        if (j != n) {
            Q.push(make_pair(-(-t.first + a[j + 1]) , j + 1));
            Q.push(make_pair(-(-t.first + a[j + 1] - a[j]) , j + 1));
        }
    }
    bool zero = 0;
    for (i = 0 , j = 0 ; j < K ; ++ i) {
        if (res[i] == 0 && !zero)
            zero = 1;
        else {
            printf("%lld\n" , res[i]);
            ++ j;
        }
    }    
}

int main() {
    work();    
    return 0;
}
