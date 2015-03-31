#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 20005;
int n , m , pre[N] , mcnt;
struct arc {
    int x , f , next;
}e[N * 200];
int s , t;
inline void addarc(int x , int y , int z) {
    //printf("%d %d\n" , x , y);
    e[mcnt] = (arc) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
int d[N] , cur[N];
bool BFS() {
    queue<int> Q;
    memset(d , -1 , sizeof(d));
    Q.push(s) , d[s] = 1;
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (e[i].f && !~d[y]) {
                d[y] = d[x] + 1;
                if (y == t)
                    return 1;
                Q.push(y);
            }
        }
    }
    return 0;
}
int DFS(int x , int flow = 1 << 30) {
    if (!flow || x == t) return flow;
    int u , sum = 0;
    for (int& i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[y] == d[x] + 1 && (u = DFS(y , min(flow , e[i].f)))) {
            sum += u , flow -= u;
            e[i].f -= u , e[i ^ 1].f += u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}
int R , C;
char str[105][105];
int bel[26];
int main() {
    int i , j , x , y , z;
    scanf("%d%d",&R , &C);
    for (i = 1 ; i <= R ; ++ i)
        scanf("%s" , str[i] + 1);
    memset(pre , -1 , sizeof(pre));
    int num = 0 , sum = 0 , cnt = R * C;
    s = R * C + 26 + 1 , t = s + 1;
    for (i = 1 ; i <= R ; ++ i)
        for (j = 1 ; j <= C ; ++ j) {
            ++ num;
            if (~(i + j) & 1)
                continue;
            if (str[i][j] == '.')
                continue;
            if (i > 1 && str[i - 1][j] != '.') addarc(num , num - C , 1);
            if (i < R && str[i + 1][j] != '.') addarc(num , num + C , 1);
            if (j > 1 && str[i][j - 1] != '.') addarc(num , num - 1 , 1);
            if (j < C && str[i][j + 1] != '.') addarc(num , num + 1 , 1);
        }
    num = 0;
    int tmp = mcnt;
    for (i = 1 ; i <= R ; ++ i) {
        for (j = 1 ; j <= C ; ++ j) {
            ++ num;
            if (str[i][j] == '*') {
                ++ sum;
                if ((i + j) & 1)
                    addarc(s , num , 1);
                else
                    addarc(num , t , 1);
            }
            if (isupper(str[i][j])) {                
                x = str[i][j] - 'A' + 1;
                str[i][j] = '@';
                if (!bel[x]) {
                    ++ sum;
                    if ((i + j) & 1) {
                        addarc(s , cnt + x , 1);
                        bel[x] = 1;
                    } else {
                        addarc(cnt + x , t , 1);
                        bel[x] = 2;
                    }
                }
                if (bel[x] == 1)
                    addarc(cnt + x , num , 1);
                else
                    addarc(num , cnt + x , 1);
            }
        }
    }
    int res = 0;
    while (BFS()) {
        memcpy(cur , pre , sizeof(pre));
        res += DFS(s);
    }
    if (res + res != sum) {
        puts("No");
        return 0;
    }
    puts("Yes");
    for (i = 0 ; i < tmp ; i += 2) {
        if (!e[i].f) {
            if ((e[i].x - 1) / C == (e[i ^ 1].x - 1) / C) {
                z = (e[i].x - 1) / C + 1;
                x = (e[i].x - 1) % C + 1;
                y = (e[i ^ 1].x - 1) % C + 1;
                if (x > y) swap(x , y);
                str[z][x] = '<';
                str[z][y] = '>';                
            } else {
                z = (e[i].x - 1) % C + 1;
                x = (e[i].x - 1) / C + 1;
                y = (e[i ^ 1].x - 1) / C + 1;
                if (x > y) swap(x , y);
                str[x][z] = '^';
                str[y][z] = 'v';                
            }
        }
    }
    for (i = 1 ; i <= R ; ++ i)
        puts(str[i] + 1);
    return 0;
}
