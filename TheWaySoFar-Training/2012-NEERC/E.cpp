#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;

int n;
LL K;
vector< pair<LL , int> > a[20];
vector<int> res;
void work() {
    int i , x;
    LL y;
    scanf("%lld%d",&K,&n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%lld",&x,&y);
        a[x].push_back(make_pair(y , i + 1));
    }
    priority_queue< pair<LL , int> > Q;
    y = 1;
    LL sum = 0;
    for (i = 0 ; i <= 18 ; ++ i) {
        for (auto it : a[i])
            Q.push(make_pair(y * it.first , it.second));
        y *= 10;
        LL z = K % y;
        while (sum < z) {
            if (Q.empty()) {
                puts("-1");
                return;
            }
            sum += Q.top().first;
            res.push_back(Q.top().second);
            Q.pop();
        }
    }
    printf("%d\n" , (int)res.size());
    for (auto it : res)
        printf("%d " , it);
}

int main() {
    freopen("exact.in" , "r" , stdin);
    freopen("exact.out" , "w" , stdout);
    work();
    return 0;
}
