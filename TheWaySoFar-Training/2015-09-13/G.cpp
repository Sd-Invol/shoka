#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <cctype>
#include <map>
using namespace std;
typedef long long LL;
const int N = 1005;
int n , m , a[N];
void work() {
    scanf("%d" , &n);
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d" , &a[i]);
    scanf("%d" , &m);
    while (m --) {
        int x , y;
        scanf("%d%d" , &x , &y);
        printf("%d\n" , *max_element(a + x , a + y + 1));
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
