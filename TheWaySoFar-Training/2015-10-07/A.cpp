#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
const int N = 100005;
const int Q = 1e9 + 7;
typedef long long LL;
using namespace std;
const int n = 3;
int ca;
int a[3];

void work() {
    printf("Case #%d:\n" , ++ ca);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%d" , &a[i]);
    sort(a , a + n);
    do {
        for (int i = 0 ; i < n ; ++ i)
            printf("%d%c" , a[i] , " \n"[i + 1 == n]);
    } while (next_permutation(a , a + n));
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}