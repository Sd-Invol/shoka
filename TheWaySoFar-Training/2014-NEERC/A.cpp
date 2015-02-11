#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 25;

int K , w , h , n;
char g[N][N][N] , res[N][N];
int cnt[N][4];
int H[N][N] , V[N][N];
int a[N];
bool f[N];

bool dfs(int k) {
    if (k == K)
        return 1;
    int x = k / n , y = k % n;
    for (int i = 0 ; i < K ; ++ i) {
        if (f[i]) continue;
        if (x == 0 && cnt[i][0]) continue;
        if (x == n - 1 && cnt[i][2]) continue;
        if (y == 0 && cnt[i][1]) continue;
        if (y == n - 1 && cnt[i][3]) continue;
        if (x && !V[a[k - n]][i]) continue;
        if (y && !H[a[k - 1]][i]) continue;
        f[i] = 1;
        a[k] = i;
        if (dfs(k + 1))
            return 1;
        f[i] = 0;
    }
    return 0;
}

void work() {
    int i , j , k , l;
    scanf("%d%d%d",&K,&w,&h);
    for (n = 1 ; n * n < K ; ++ n);
    for (i = 0 ; i < K ; ++ i) {
        for (j = 0 ; j < 3 * h - 2 ; ++ j)
            scanf("%s" , g[i][j]);
        for (j = 0 ; j < h - 1 ; ++ j)
            for (k = 0 ; k < w ; ++ k) {
                cnt[i][0] += (g[i][j][k + w - 1] != '.');
                cnt[i][2] += (g[i][j + h + h - 1][k + w - 1] != '.');
            }
        for (k = 0 ; k < w ; ++ k) {
            cnt[i][0] += (g[i][h - 1][k + w - 1] == '.');
            cnt[i][2] += (g[i][h + h - 2][k + w - 1] == '.');
        }
        for (j = 0 ; j < h ; ++ j)
            for (k = 0 ; k < w - 1 ; ++ k) {
                cnt[i][1] += (g[i][j + h - 1][k] != '.');
                cnt[i][3] += (g[i][j + h - 1][k + w + w - 1] != '.');
            }
        for (j = 0 ; j < h ; ++ j) {
            cnt[i][1] += (g[i][j + h - 1][w - 1] == '.');
            cnt[i][3] += (g[i][j + h - 1][w + w - 2] == '.');
        }

        // for (j = 0 ; j < 4 ; ++ j)
        //    printf("%d%c" , cnt[i][j] , " \n"[j == 3]);
    }

    for (i = 0 ; i < K ; ++ i) {
        for (j = 0 ; j < K ; ++ j) {
            if (i == j) continue;

            for (k = 1 ; k < h + h ; ++ k) {
                for (l = 0 ; l < w ; ++ l)
                    if (isalpha(g[i][k + h - 1][l + w - 1]) && isalpha(g[j][k - 1][l + w - 1]))
                        break;
                if (l < w)
                    break;
            }
            if (k >= h + h) {
                V[i][j] = 1;
                //printf("%d %d\n" , i , j);
            }
        }
    }
    for (i = 0 ; i < K ; ++ i) {
        for (j = 0 ; j < K ; ++ j) {
            if (i == j) continue;

            for (k = 0 ; k < h ; ++ k) {
                for (l = 1 ; l < w + w; ++ l)
                    if (isalpha(g[i][k + h - 1][l + w - 1]) && isalpha(g[j][k + h - 1][l - 1]))
                        break;
                if (l < w + w)
                    break;
            }
            if (l >= w + w) {
                H[i][j] = 1;
                //printf("%d %d\n" , i , j);
            }
        }
    }
    assert(dfs(0));
    for (i = 0 ; i < K ; ++ i) {
        l = a[i];
        int x = h * (i / n) , y = w * (i % n);
        for (j = 0 ; j < 3 * h - 2 ; ++ j)
            for (k = 0 ; k < 3 * w - 2 ; ++ k)
                if (g[l][j][k] != '.') {
                    res[j - h + 1 + x][k - w + 1 + y] = g[l][j][k];
                }
    }
    printf("%d %d\n" , n * w , n * h);
    for (i = 0 ; i < n * h ; ++ i)
        puts(res[i]);
}

int main() {
    freopen("ascii.in" , "r" , stdin);
    freopen("ascii.out" , "w" , stdout);
    work();
    return 0;
}
