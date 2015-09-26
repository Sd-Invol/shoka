#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <unordered_map>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 1000005;
char str[N];
int n , ca;
void work() {    
    printf("Case #%d: " , ++ ca);
    scanf("%s" , str);
    n = strlen(str);
    vector<int> v;
    for (int i = 0 ; i < n ; ++ i) {
        if (str[i] == 'c')
            v.push_back(i);
        if (str[i] != 'c' && str[i] != 'f') {
            puts("-1");
            return;
        }
    }
    if (v.empty())
        printf("%d\n" , (n + 1) / 2);
    else {
        int cnt = 0;
        for (int i = 0 ; i < v.size() ; ++ i) {
            int delta;
            if (i + 1 < v.size())
                delta = v[i + 1] - v[i];
            else
                delta = v[0] + n - v[i];
            if (delta < 3)
                ++ cnt;
        }
        if (!cnt)
            printf("%d\n" , (int)v.size());
        else
            puts("-1");
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();    
    return 0;
}
