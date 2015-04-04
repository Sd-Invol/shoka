#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
char s[N] , t[N];
LL a[N] , b[N];
int n , m , bs , bt;
int f[N];
void work() {
    int i , j , k , x , y;
    scanf("%s%s" , s , t);
    n = strlen(s) , m = strlen(t);
    for (i = 0 , j = -1 ; i < n ; ++ i) {
        if (s[i] == 'b') {
            a[bs ++] = i - j - 1;
            j = i;
        }
    }
    a[bs ++] = n - j - 1; 
    for (i = 0 , j = -1 ; i < m ; ++ i) {
        if (t[i] == 'b') {
            b[bt ++] = i - j - 1;
            j = i;
        }
    }
    b[bt ++] = m - j - 1;

    if (bt > bs) {
        puts("-1");
        return;
    }
    if (bt == 1) {
        x = b[0];
        for (k = 0 ; k < 20 ; ++ k) {
            for (i = 0 ; i < bs ; ++ i)
                if (a[i] >= x) {
                    printf("%d\n" , k);
                    return;
                }
            for (i = 0 ; i + 1 < bs ; ++ i)
                a[i] = a[i] << 1 | 1;
            a[i] <<= 1;
        }
        puts("-1");
        return;
    }
    if (bt == 2) {
        for (k = 0 ; k < 20 ; ++ k) {
            for (i = 1 ; i < bs ; ++ i)
                if (a[i - 1] >= b[0] && a[i] >= b[1]) {
                    printf("%d\n" , k);
                    return;
                }
            for (i = 0 ; i + 1 < bs ; ++ i)
                a[i] = a[i] << 1 | 1;
            a[i] <<= 1;
        }
        puts("-1");
        return;
    }
    int L = b[0] , R = b[bt - 1];
    for (i = 0 ; i + 1 < bt ; ++ i)
        b[i] = b[i + 1];
    bt -= 2 , b[bt] = -1;
    f[0] = f[1] = 0;
    for (i = 1 ; i < bt ; ++ i) {
        j = f[i];
        while (j && b[j] != b[i])
            j = f[j];
        f[i + 1] = (b[j] == b[i]) ? j + 1 : 0;
    }
        
    for (k = 0 ; k < 20 ; ++ k) {
        for (i = 1 , j = 0 ; i + 1 < bs ; ++ i) {
            while (j && b[j] != a[i])
                j = f[j];
            j += (b[j] == a[i]);
            if (j == bt) {             
                if (a[i + 1] >= R && a[i - j] >= L) {
                    printf("%d\n" , k);
                    return;
                }
            }
        }
        for (i = 0 ; i + 1 < bs ; ++ i)
            a[i] = a[i] << 1 | 1;
        a[i] <<= 1;        
    }
    puts("-1");
}

int main() {
    work();    
    return 0;
}
