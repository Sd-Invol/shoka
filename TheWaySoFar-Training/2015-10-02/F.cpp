#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <set>
using namespace std;
typedef long long LL;
const int N = 205;

const int tiles[12][4] = {
    {0 , 0 , 0 , 0} ,
    {0 , 1 , 0 , 1} ,
    {1 , 0 , 1 , 0} ,
    {0 , 1 , 1 , 0} ,
    {0 , 0 , 1 , 1} ,
    {1 , 0 , 0 , 1} ,
    {1 , 1 , 0 , 0} ,
    {0 , 1 , 1 , 1} ,
    {1 , 0 , 1 , 1} ,
    {1 , 1 , 0 , 1} ,
    {1 , 1 , 1 , 0} ,
    {1 , 1 , 1 , 1}
};
int n , m;
struct status {
    int cnt[12];
    int plug[4] , root;

    status () {
        memset(plug , 0 , sizeof(plug));
        root = 1;
    }
    void rotate() {
        swap(cnt[1] , cnt[2]);
        swap(cnt[3] , cnt[5]);
        swap(cnt[7] , cnt[8]);
        swap(cnt[9] , cnt[10]);
    }
    void change(int x , int y) {
        if (x == root)
            root = y;
        for (int i = 0 ; i <= m ; ++ i)
            if (plug[i] == x)
                plug[i] = y;
    }
    bool normalize() {
        bool flag = 0;
        for (int i = 0 ; i <= m ; ++ i)
            if (plug[i] != root) {
                plug[i] = -plug[i];
            } else {
                flag = 1;
                plug[i] = 1;
            }
        if (!flag) return 0;
        int ccnt = 1; root = 1;
        for (int i = 0 ; i <= m ; ++ i) {
            if (plug[i] < 0) {
                ++ ccnt;
                for (int j = m ; j >= i ; -- j)
                    if (plug[j] == plug[i])
                        plug[j] = ccnt;
            }
        }
        return 1;
    }
    operator unsigned () const {
        unsigned res = 0;
        for (int i = 0 ; i < 12 ; ++ i)
            res = res * 61 + cnt[i] + 1;
        for (int i = 0 ; i <= m ; ++ i)
            res = res * 61 + plug[i] + 1;
        return res;
    }
    bool operator == (const status& R) const {
        return memcmp(cnt , R.cnt , sizeof(cnt)) == 0 && memcmp(plug , R.plug , sizeof(plug)) == 0;
    }
};
template<typename T1 , typename T2> struct hashmap {
    const static int MOD = 99991;
    const static int Size = 200005;
    int pre[MOD] , mcnt;
    struct node {
        T1 key;
        T2 val ;
        int next;
    } e[Size];
    void clear() {
        memset(pre , -1 , sizeof(pre));
        mcnt = 0;
    }
    void insert(const T1 &K , const T2 &V) {
        int x = unsigned(K) % MOD;
        e[mcnt] = (node) {K , V , pre[x]};
        pre[x] = mcnt ++;
    }
    int find(const T1 &K) {
        int x = unsigned(K) % MOD;
        for (int i = pre[x] ; ~i ; i = e[i].next)
            if (e[i].key == K)
                return i;
        return -1;
    }
    T2& operator [] (const T1 &x){
        int i = find(x);
        if (!~i){
            insert(x , 0);
            return e[mcnt - 1].val;
        }
        return e[i].val;
    }
};
hashmap<status , LL> f[2];
void work() {
    scanf("%d%d" , &n , &m);
    status st;
    for (int i = 0 ; i < 12 ; ++ i)
        scanf("%d" , &st.cnt[i]);
    if (n < m) {
        swap(n , m);
        st.rotate();
    }
    int cur = 0 , nxt = 1;
    f[cur].clear();
    f[cur][st] = 1;
    LL res = 0;

    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < m ; ++ j) {
            f[nxt].clear();

            for (int it = 0 ; it < f[cur].mcnt ; ++ it) {
                status ss = f[cur].e[it].key;
                LL w = f[cur].e[it].val;
                /*printf("==============\n");
                printf("%d %d : " , i , j);
                for (int k = 0 ; k <= m ; ++ k)
                    printf("%d" , ss.plug[k]);
                printf(" ");
                for (int k = 0 ; k < 12 ; ++ k)
                    printf("%d" , ss.cnt[k]);
                printf(" %lld\n" , w);*/

                for (int k = 0 ; k < 12 ; ++ k) {
                    if (!ss.cnt[k]) continue;
                    status ns = ss;
                    -- ns.cnt[k];
                    ns.root = 1;
                    int nc = (i == 0 && j == 0) ? 1 : 233;
                    if (ns.plug[j] && tiles[k][0])
                        ns.change(ns.plug[j] , nc);
                    if (ns.plug[j + 1] && tiles[k][1])
                        ns.change(ns.plug[j + 1] , nc);
                    ns.plug[j + 1] = nc * tiles[k][2];
                    ns.plug[j] = nc * tiles[k][3];
                    if (i + 1 == n && j + 1 == m && nc == ns.root)
                        res += w;
                    if (ns.normalize())
                        f[nxt][ns] += w;
                }
            }

            swap(cur , nxt);
        }
        f[nxt].clear();
        for (int it = 0 ; it < f[cur].mcnt ; ++ it) {
            status ss = f[cur].e[it].key;
            LL w = f[cur].e[it].val;
            for (int i = m ; i > 0 ; -- i)
                ss.plug[i] = ss.plug[i - 1];
            ss.plug[0] = 0;
            if (ss.normalize())
                f[nxt][ss] += w;
        }
        swap(cur , nxt);
    }
    cout << res << endl;
}

int main() {
    work();
    return 0;
}