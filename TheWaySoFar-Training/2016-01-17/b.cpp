#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>
using namespace std;
const int N = 1 << 18;
int n;
map<string , int> Hash;
char str[N];

int a[N] , b[N] , f[N];

int main() {
    scanf("%d" , &n);
    for (int i = 0 ; i < 1 << n ; ++ i) {
        scanf("%s" , str);
        Hash[str] = i;
        a[i] = i;
    }
    scanf("%s" , str);
    int m = 0;

    for (int k = 0 ; k < n ; ++ k) {        
        for (int i = 0 ; i < 1 << n - k - 1 ; ++ i) {
            if (str[m] == 'W') {
                f[a[i << 1 | 1]] = a[i << 1];
                b[i] = a[i << 1];
            } else {                
                f[a[i << 1]] = a[i << 1 | 1];
                b[i] = a[i << 1 | 1]; 
            }
            //printf("%d " , b[i]);
            m ++;
        }
        //puts("");
        memcpy(a , b , sizeof(a));
    }
    f[a[0]] = -1;
    scanf("%d" , &m);
    for (int i = 0 ; i < m ; ++ i) {
        scanf("%s" , str);
        int x = Hash[str];
        scanf("%s" , str);
        int y = Hash[str];

        int z = y;
        while (z != -1 && z != x)
            z = f[z];
        if (z == x) {
            puts("Win");
            continue;
        }
        z = x;
        while (z != -1 && z != y)
            z = f[z];
        if (z == y) {
            puts("Lose");
            continue;
        }
        puts("Unknown");
    }
    return 0;
}
