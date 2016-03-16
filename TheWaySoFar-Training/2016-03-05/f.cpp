#include <cstdio>
#include <cstring>
#include <vector>
const int N = 1005;
using namespace std;

int n;
vector<int> e[N];
int cnt[N];
int f[N][5];

void print(int x , int c) {
    cnt[x] = 1 << 30;
    for (auto &y : e[x]) {
        if (!f[y][c]) {
            f[y][c] = 1;
            -- cnt[y];
        }
    }
}

int main() {
    scanf("%d" , &n);
    for (int i = 1 ; i < n ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for (int i = 1 ; i <= n ; ++ i) {
        cnt[i] = 4;
    }

    while (1) {
        int x = 1;
        for (int i = 1 ; i <= n ; ++ i) {
            if (cnt[x] > cnt[i]) {
                x = i;
            }
        }
        int c = 0;
        for (int i = 1 ; i <= 4 ; ++ i) {
            if (!f[x][i]) {
                c = i;
                break;
            }
        }
        printf("%d %d\n" , x , c);
        fflush(stdout);
        print(x , c);
        
        scanf("%d%d" , &x , &c);
        if (!~x && !~c) {
            break;
        }
        print(x , c);
    }
    return 0;
}
