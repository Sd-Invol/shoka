#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1005;
typedef long long LL;

int n , a[N] , f[N];
int main() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d" , &a[i]);
    sort(a , a + n);
    int res = 0;
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < i ; ++ j)
            if (a[i] <= a[j]) {
                f[i] = max(f[j] , f[i]);
            }
        res = max(res , ++ f[i]);
    }
    cout << res << endl;
    return 0;
}
