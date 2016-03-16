#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
const int N = 100005;
typedef long long LL;

int n , a[4];
multiset<int> S[16];

int main() {

    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        int o;
        scanf("%d" , &o);
        for (int j = 0 ; j < 4 ; ++ j)
            scanf("%d" , &a[j]);

        int res = -1 << 30;
        for (int k = 0 ; k < 1 << 4 ; ++ k) {
            int s = 0;
            for (int l = 0 ; l < 4 ; ++ l)
                if (k >> l & 1)
                    s += a[l];
                else
                    s -= a[l];
            if (o == 1) S[k].insert(s);
            if (o == 2) S[k].erase(S[k].find(s));
            if (o == 3) {
                res = max(res , s - *S[k].begin());
            }
        }
        if (o == 3)
            printf("%d\n" , res);
    }

    return 0;
}
