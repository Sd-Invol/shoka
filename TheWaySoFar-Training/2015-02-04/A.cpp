#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m , X , Y , a[N];
priority_queue< LL , vector<LL> , greater<LL> > Q;
LL mn[N];
void work() {
    scanf("%d%d%d%d",&n,&m,&X,&Y);
    for (int i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
        if (i > 1)
            Q.push(a[i]);
    }
    for (int i = 0 ; i < m ; ++ i) {
        if (Q.empty()) {
            mn[i] = 1LL << 60;
        } else {
            mn[i] = Q.top() , Q.pop();
            Q.push(mn[i] + X);
        }
    }
    LL res = a[1] + Y;
    for (int i = 1 ; i <= m ; ++ i) {
        LL x = a[1] + (LL) (i - 1) * X;
        if (x <= mn[m - i])
            res = max(res , X + min(x + Y , mn[m - i]));
    }
    cout << res << endl;
}

int main() {
    work();
    return 0;
}
