#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 400005;
int n;
char str[N];
int cnt1 , cnt2;
int u1[N][26] , u2[N][26];
int a1[26] , a2[26];
bool f[26];
void work() {
    int i , j , x , cnt = 0;
    scanf("%d",&n);
    cnt1 = 1 , cnt2 = 1;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%s" , str);
        x = 1;
        for (j = 0 ; str[j] ; ++ j) {
            int c = str[j] - 'a';
            if (!u1[x][c]) {
                u1[x][c] = ++ cnt1;
                memset(u1[cnt1] , 0 , sizeof(u1[cnt1]));
                if (j)
                    ++ a1[c];
            }
            x = u1[x][c];
        }
        reverse(str , str + j);
        if (j == 1 && !f[*str - 'a'])
            ++ cnt , f[*str - 'a'] = 1;
        x = 1;
        for (j = 0 ; str[j] ; ++ j) {
            int c = str[j] - 'a';
            if (!u2[x][c]) {
                u2[x][c] = ++ cnt2;
                memset(u2[cnt2] , 0 , sizeof(u2[cnt2]));
                if (j)
                    ++ a2[c];
            }
            x = u2[x][c];
        }
    }
    LL res = (LL)(cnt1 - 1) * (cnt2 - 1);
    for (i = 0 ; i < 26 ; ++ i)
        res -= (LL)a1[i] * a2[i];
    cout << res + cnt << endl;
}

int main() {
    freopen("dictionary.in" , "r" , stdin);
    freopen("dictionary.out" , "w" , stdout);
    work();
    return 0;
}
