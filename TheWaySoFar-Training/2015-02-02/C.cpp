#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5000;
int n;
vector<int> a[N];
bitset<N> mask[50];

void work() {
    int i , j , k;    
    int res = 0;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d" , &j);
        while (j --) {
            scanf("%d",&k);
            -- k;
            a[i].push_back(k);
        }
        sort(a[i].begin() , a[i].end());
        bitset<N> f , g;
        for (j = 0 , k = 0; j < a[i].size() ; ++ j) {
            while (k < 50 && k <= a[i][j]) {
                f |= mask[k ++];
            }
            g ^= f;
            f.reset();
        }
        res += g.count();
        for (j = 0 ; j < a[i].size() ; ++ j)
            mask[a[i][j]].set(i);
    }
    printf("%d\n" , res);
}

int main() {
    work();    
    return 0;
}
