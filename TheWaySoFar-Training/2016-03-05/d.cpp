#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 205;
char str[N];
int n;

void print(int x) {
    printf("%d\n%d\n%d\n" , n + 1 , 1 , n);
    int m = 0;
    for (int i = 0 ; i < n ; ++ i) {
        static int t[26];
        for (int j = 0 ; j < 26 ; ++ j)
            t[j] = n + 1;
        ++ m;
        if (i == x) {
            t[str[i] - 'a'] = m;
            ++ i;            
        }
        if (i < n) {
            t[str[i] - 'a'] = m + 1;
        }
        for (int j = 0 ; j < 26 ; ++ j)
            printf("%d%c" , t[j] , " \n"[j + 1 == 26]);
    }
    if (x + 1 < n) {
        for (int j = 0 ; j < 26 ; ++ j)
            printf("%d%c" ,  n + 1 , " \n"[j + 1 == 26]);
    }
    for (int j = 0 ; j < 26 ; ++ j)
        printf("%d%c" ,  n + 1 , " \n"[j + 1 == 26]);
}

void work() {
    n = strlen(str);
    for (int i = 0 ; i < n ; ++ i) {
        if (i + 1 < n && str[i] == str[i + 1])
            continue;        
        for (int j = i + 1 ; j < n ; ++ j) {
            if (j + 1 < n && str[j] == str[j + 1])
                continue;
            if (str[i] != str[j]) {
                puts("YES");
                print(i);
                print(j);
                return;
            }
        }
    }
    puts("NO");
}

int main() {
    freopen("decomposable.in" , "r" , stdin);
    freopen("decomposable.out" , "w" , stdout);
    
    while (~scanf("%s" , str))
        work();
    return 0;
}
