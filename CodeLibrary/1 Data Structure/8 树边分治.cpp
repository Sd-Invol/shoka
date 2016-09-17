/*QTREE4,里面自带rebuild过程重建树为适合边分治的结构。
还自带手写的二叉堆。*/
const int N = 200005;
int n , m , Q , pre[N] , mcnt;
struct edge {
    int x , w , next;
}e[N << 2];
int tmp[N];
bool color[N];
void build(vector<int>& child , int x , int l , int r) {
    if (l == r) {
        int y = e[child[l]].x;
        e[mcnt] = (edge) {y , e[child[l]].w , tmp[x]} , tmp[x] = mcnt ++;
        e[mcnt] = (edge) {x , e[child[l]].w , tmp[y]} , tmp[y] = mcnt ++;
    } else {
        int mid = l + r >> 1;
        int rt = ++ n ; color[rt] = 1;
        e[mcnt] = (edge) {x , 0 , tmp[n]} , tmp[n] = mcnt ++;
        e[mcnt] = (edge) {n , 0 , tmp[x]} , tmp[x] = mcnt ++;
        if (l <= mid) build(child , rt , l , mid);
        if (mid < r) build(child , rt , mid + 1 , r);
    }
}
void rebuild(int x , int fa) {
    vector<int> child;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            rebuild(y , x);
            child.push_back(i);
        }
    }
    if (!child.empty())
        build(child , x , 0 , child.size() - 1);
}
int s[N] , size;
bool f[N];
pair<int , int> Find(int x , int fa , int cnt) {
    s[x] = 1;
    pair<int , int> res = make_pair(1 << 30 , -1);
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[i >> 1] && y != fa) {
            res = min(res , Find(y , x , cnt));
            s[x] += s[y];
            res = min(res , make_pair(max(s[y] , cnt - s[y]) , i));
        }
    }
    return res;
}
pair<int , int> res[N];
int flag[N];
vector< pair<int , int> > b[N];
priority_queue< pair<int , int> > PQ[N << 1];
void Getdis(int x , int fa , int d , int id) {
    b[x].push_back(make_pair(id , d));
    if (!color[x])
        PQ[id].push(make_pair(d , x));
    ++ size;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        if (!f[i >> 1]) {
            int y = e[i].x;
            if (y != fa)
                Getdis(y , x , d + e[i].w , id);
        }
    }
}
void divide(int x , int cnt) {
    if (cnt <= 1) return;
    int k = Find(x , 0 , cnt).second;
    f[k >> 1] = 1;

    size = 0 , PQ[k].push(make_pair(-1 << 29 , -1));
    Getdis(e[k].x , 0 , 0 , k);
    s[e[k].x] = size;

    size = 0 , PQ[k ^ 1].push(make_pair(-1 << 29 , -1));
    Getdis(e[k ^ 1].x , 0 , 0 , k ^ 1);
    s[e[k ^ 1].x] = size;

    res[k >> 1] = make_pair(PQ[k].top().first + PQ[k ^ 1].top().first + e[k].w , k >> 1);

    divide(e[k].x , s[e[k].x]);
    divide(e[k ^ 1].x , s[e[k ^ 1].x]);
}
void down(int x) {
    int i = x , j = i << 1 | 1;
    pair<int , int> t = res[i];
    if (j + 1 < m && res[j + 1] > res[j])
        ++ j;
    while (j < m && t < res[j]) {
        flag[res[j].second] = i , res[i] = res[j];
        i = j , j = i << 1 | 1;
        if (j + 1 < m && res[j + 1] > res[j])
            ++ j;
    }
    res[i] = t , flag[t.second] = i;
}
void up(int x) {
    int i = x , j = (i + 1 >> 1) - 1;
    pair<int , int> t = res[i];
    while (j >= 0 && res[j] < t) {
        flag[res[j].second] = i , res[i] = res[j];
        i = j , j = (i + 1 >> 1) - 1;
    }
    res[i] = t , flag[t.second] = i;
}

void work() {
    int i , j , x , y , z;
    char str[10];
    scanf("%d",&n);
    memset(pre , -1 , sizeof(pre)) , mcnt = n * 6;
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d%d",&x,&y,&z);
        e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , z , pre[y]} , pre[y] = mcnt ++;
    }
    int cnt = n;
    mcnt = 0;
    memset(tmp , -1 , sizeof(tmp));
    rebuild(1 , 0);
    memcpy(pre , tmp , sizeof(tmp));
    divide(1 , n);
    m = mcnt >> 1;

    make_heap(res , res + m);
    for (i = 0 ; i < m ; ++ i)
        flag[res[i].second] = i;

    scanf("%d",&Q);
    while (Q --) {
        scanf("%s" , str);
        if (*str == 'A') {
            if (!cnt)
                puts("They have disappeared.");
            else if (cnt == 1)
                puts("0");
            else
                printf("%d\n" , max(0 , res[0].first));
        } else {
            scanf("%d",&x);
            if (color[x])
                ++ cnt;
            else
                -- cnt;
            color[x] ^= 1;
            for (i = 0 ; i < b[x].size() ; ++ i) {
                j = b[x][i].first , z = b[x][i].second;
                if (!color[x])
                    PQ[j].push(make_pair(z , x));
                while (~PQ[j].top().second && color[PQ[j].top().second])
                    PQ[j].pop();
                res[flag[j >> 1]].first = PQ[j].top().first + PQ[j ^ 1].top().first + e[j].w;
                down(flag[j >> 1]) , up(flag[j >> 1]);
            }
        }
    }
}

int main() {
    work();
    return 0;
}
