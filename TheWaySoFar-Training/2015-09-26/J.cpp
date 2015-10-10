#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <queue>
#include <set>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , L , A , B , ca;
int cnt[N];
void work() {
    scanf("%d%d%d%d", &n , &A , &B , &L);
    memset(cnt , 0 , sizeof(cnt));
    for (int i = 0 ; i < n ; ++ i) {
        int l , r;
        scanf("%d%d" , &l , &r);
        ++ cnt[l] , -- cnt[r];
    }
    for (int i = 0 ; i < L ; ++ i)
        cnt[i + 1] += cnt[i];
    int res = 0 , sum = 0;
    for (int i = 0 ; i < L ; ++ i) {
        if (cnt[i])
            sum -= A;
        else
            sum += B;
        res = max(res , -sum);
    }
    printf("Case #%d: %d\n" , ++ ca ,  res);    
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}