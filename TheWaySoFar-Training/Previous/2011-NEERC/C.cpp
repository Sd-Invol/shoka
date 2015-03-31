#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 35;
const int M = 2005;
int n , m , K , sn , sx;
bool g[N][M];
char id[N];
bool w[N][N][N];
int cnt , S[N] , T[N] , o[M][N] , s[M];
int f[N][M] , p[N][M];
void work() {
    int i , j , k , l , x , y;
    char str[N] , c;
    scanf("%d%d%d%d%d",&m,&n,&K,&sn,&sx);
    id[cnt ++] = ' ';
    while (1) {
        scanf("%s%c" , str , &c);
        id[cnt] = *str;
        scanf("%s%c" , str , &c);
        for (k = 0 ; k < K ; ++ k)
            w[cnt][0][k] = (str[k] == '*');
        cnt ++;
        if (c == '\n')
            break;
    }
    for (i = 1 ; i < m ; ++ i) {
        for (j = 1 ; j < cnt ; ++ j) {
            scanf("%s" , str);
            for (k = 0 ; k < K ; ++ k)
                w[j][i][k] = (str[k] == '*');
        }
    }
    getchar();
    gets(str);
    y = strlen(str);
    for (i = 0 , j = 0 ; i < y ; ++ i) {
        scanf("%d" , &x);
        j += x;
        for (k = 0 ; k < cnt ; ++ k)
            if (id[k] == str[i])
                break;
        assert(k < cnt);
        x = S[i] = k;
        for (k = 0 ; k < m ; ++ k)
            for (l = 0 ; l < K ; ++ l)
                g[k][j + l] = w[x][k][l];
        j += K;
    }
    for (i = 0 ; i + K - 1 < n ; ++ i)
        for (k = 0 ; k < m ; ++ k)
            for (l = 0 ; l < K ; ++ l)
                for (j = 0 ; j < cnt ; ++ j)
                    o[i][j] += (g[k][i + l] != w[j][k][l]);
    for (i = 0 ; i < n ; ++ i) {
        s[i] = i ? s[i - 1] : 0;
        for (j = 0 ; j < m ; ++ j)
            s[i] += g[j][i];
    }
    getchar();
    gets(str);
    y = strlen(str);
    memset(f , 0x3f , sizeof(f));
    for (i = 0 ; i < y ; ++ i) {
        for (k = 0 ; k < cnt ; ++ k)
            if (id[k] == str[i])
                break;
        T[i] = k;
    }
    for (i = K ; i <= n ; ++ i)
        f[1][i] = o[i - K][T[0]] + (i ? s[i - K - 1] : 0);
    for (i = 1 ; i < y ; ++ i) {
        x = T[i];
        for (j = 0 ; j < n ; ++ j) {
            if (f[i][j] == 0x3f3f3f3f)
                continue;
            for (k = K + sn ; k <= K + sx && j + k <= n; ++ k) {
                int val = f[i][j] + o[j + k - K][x];
                val += s[j + k - K - 1] - s[j - 1];
                if (val < f[i + 1][j + k]) {
                    f[i + 1][j + k] = val;
                    p[i + 1][j + k] = k;
                }
            }
        }
    }
    pair<int , int> res(1 << 30 , -1);
    for (i = 1 ; i <= n ; ++ i)
        res = min(res , make_pair(f[y][i] + s[n - 1] - s[i - 1] , i));
    vector<int> ans;
    x = res.second;
    while (y) {
        ans.push_back(x);
        x -= p[y][x];
        y --;
    }
    reverse(ans.begin() , ans.end());
    x = 0;
    for (auto it : ans) {
        printf("%d " , it - K - x);
        x = it;
    }
}

int main() {
    freopen("caption.in" , "r" , stdin);
    freopen("caption.out" , "w" , stdout);
    work();
    return 0;
}
