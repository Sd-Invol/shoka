#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
const int N = 2005;
using namespace std;
int n , a[N];
void work() {
    scanf("%d" , &n);
    int sum = 0 , res = 0;
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d" , &a[i]);
        sum += a[i];
    }
    for (int i = 0 ; i < n ; ++ i) {
        if (a[i] * n > sum)
            ++ res;
    }
    cout << res << endl;
}


int main() {
    work();
    return 0;
}