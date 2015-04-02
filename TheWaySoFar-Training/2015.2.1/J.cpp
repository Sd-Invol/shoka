#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , q;
char *pos[N];
int u[N][26] , f[N] , nodecnt;
char STR[N + N] , str[N];
pair<int , int> R[N];
vector<int> obj[N] , e[N];

const int M = 8000005;
int cnt , res[N];
struct node {
    node *l , *r;
    int sum;
}t[M] , *root[N];

void insert(node* &p , int l , int r , int x) {
    if (p == NULL)
        p = &t[++ cnt];
    if (l == r) {
        p -> sum = 1;
    } else {
        int mid = l + r >> 1;
        if (x <= mid)
            insert(p -> l , l , mid , x);
        else
            insert(p -> r , mid + 1 , r , x);
        p -> sum = p -> l ? p -> l -> sum : 0;
        p -> sum += p -> r ? p -> r -> sum : 0; 
    }
}
void merge(node* &p , node *x , node *y , int l , int r) {
    if (y == NULL)
        p = x;
    else if (x == NULL)
        p = y;
    else if (l == r){
        p = &t[++ cnt];
        p -> sum = (x -> sum | y -> sum);
    } else {
        int mid = l + r >> 1;
        p = &t[++ cnt];
        merge(p -> l , x -> l , y -> l , l , mid);
        merge(p -> r , x -> r , y -> r , mid + 1 , r);
        p -> sum = p -> l ? p -> l -> sum : 0;
        p -> sum += p -> r ? p -> r -> sum : 0;     
    }
}

int query(node* p , int l , int r , int top , int bot) {
    if (p == NULL)
        return 0;
    if (top <= l && r <= bot)
        return p -> sum;
    int mid = l + r >> 1 , ret = 0;
    if (top <= mid) ret += query(p -> l , l , mid , top , bot);
    if (bot > mid) ret += query(p -> r , mid + 1 , r , top , bot);
    return ret;
}

void dfs(int x) {
    for (auto y : e[x]) {
        dfs(y);
        merge(root[x] , root[x] , root[y] , 1 , n);
    }
    for (auto i : obj[x]) {
        res[i] = query(root[x] , 1 , n , R[i].first , R[i].second);
    }
}

void work() {
    int i , j , x , y;
    scanf("%d%d",&n,&q);
    int len = 0;
    for (i = 1 ; i <= n ; ++ i) {
        pos[i] = STR + len;
        scanf("%s" , pos[i]);
        len += strlen(pos[i]) + 1;
    }
    nodecnt = 1;
    for (i = 1 ; i <= q ; ++ i) {
        scanf("%d%d",&R[i].first , &R[i].second);
        scanf("%s" , str);
        x = 0;
        for (j = 0 ; str[j] ; ++ j) {
            int c = str[j] - 'a';
            if (!u[x][c])
                u[x][c] = nodecnt ++;
            x = u[x][c];
        }
        obj[x].push_back(i); 
    }
    queue<int> Q;
    for (i = 0 ; i < 26 ; ++ i)
        if (u[0][i])
            f[u[0][i]] = 0 , Q.push(u[0][i]);
    while (!Q.empty()) {
        x = Q.front() ; Q.pop();
        for (i = 0 ; i < 26 ; ++ i) {
            y = u[x][i];
            if (y) {
                Q.push(y);
                int j = f[x];
                while (j && !u[j][i])
                    j = f[j];
                f[y] = u[j][i];
            }
        }
    }
    for (i = 1 ; i < nodecnt ; ++ i) {
        e[f[i]].push_back(i);
    }
    for (i = 1 ; i <= n ; ++ i) {
        x = 0;
        for (j = 0 ; pos[i][j] ; ++ j) {
            int c = pos[i][j] - 'a';
            while (x && !u[x][c])
                x = f[x];
            x = u[x][c];
            //printf("%d : %d\n" , i , x);
            insert(root[x] , 1 , n , i);
        }
    }
    dfs(0);
    for (i = 1 ; i <= q ; ++ i)
        printf("%d\n" , res[i]);
}

int main() {
    work();
    return 0;
}
