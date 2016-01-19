#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
const int N = 2005;
int W , H , n , m , K;
int cx[N] , cy[N] , hp[N];
int tx[N] , ty[N] , ms[N];

set< pair<int , int> > Mountain;
map< pair<int , int> , int> Hash;
int dx[] = {1, -1 , -1 , 0 , 0 , 1};
int dy[] = {0, 0 , 1 , 1 , -1 , -1};
vector< pair<int , int> > U , V, P;
inline bool in(int x , int y) {
    return 0 <= x && x < W && 0 <= y && y < H;
}
inline bool attack(int x , int y , int p) {
    for (int i = 0 ; i < 6 ; ++ i) {
        int X = x + dx[i] , Y = y + dy[i];
        if (X == cx[p] && Y == cy[p])
            return 1;
        for (int j = 0 ; j < 6 ; ++ j)
            if (X + dx[j] == cx[p] && Y + dy[j] == cy[p])
                return 1;
    }
    return 0;
}


void BFS(int id) {
    map< pair<int , int> , int> dist;
    queue< pair<int , int> > Q;
    Q.push(make_pair(tx[id] , ty[id]));
    dist[make_pair(tx[id] , ty[id])] = 0;
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        int w = dist[make_pair(x , y)];
        //printf("%d %d : %d\n" , x , y , w);
        Q.pop();
        for (int i = 0 ; i < n ; ++ i) {
            if (attack(x , y , i)) {
                if (!Hash.count(make_pair(x , y))) {
                    Hash[make_pair(x , y)] = K ++;
                    P.push_back(make_pair(x, y));
                }
                int j = Hash[make_pair(x , y)];
                U.push_back(make_pair(id , j));
                V.push_back(make_pair(j , i));                
            }
        }
        if (w + 1 == ms[id])
            continue;
        for (int i = 0 ; i < 6 ; ++ i) {
            int X = x + dx[i] , Y = y + dy[i];
            //printf("-%d %d\n" , X , Y);
            pair<int , int> D(X , Y);
            if (!in(X , Y) || Mountain.count(D))
                continue;
            //printf("--%d %d\n" , X , Y);
            if (dist.count(D))
                continue;
            //printf("---%d %d\n" , X , Y);
            dist[D] = w + 1;
            Q.push(D);
        }
    }
}

int s , t , pre[N] , mcnt;
struct arc {
    int x , f,  next;
}e[N * N * 4];

void addarc(int x , int y, int z) {
    e[mcnt] = (arc) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 , pre[y]} , pre[y] = mcnt ++;    
}
int d[N] , cur[N];
bool bfs() {
    queue<int> Q;
    memset(d , -1 , sizeof(d));
    d[t] = 1 , Q.push(t);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            if (e[i ^ 1].f && !~d[y]) {
                d[y] = d[x] + 1;
                Q.push(y);
                if (y == s)
                    return 1;
            }
        }
    }
    return 0;
}
int DFS(int x , int flow = 1 << 30) {
    if (x == t || !flow)
        return flow;
    int sum = 0 , u;
    for (int &i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (d[y] + 1 == d[x] && (u = DFS(y , min(flow , e[i].f)))) {
            e[i].f -= u , e[i ^ 1].f += u;
            flow -= u , sum += u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}
int dinic() {
    int res = 0;
    while (bfs()) {
        memcpy(cur , pre , sizeof(pre));
        res += DFS(s);
    }
    return res;
}

int car_bo[1000];
map<pair<int, int>, int> pos_bo;

int main() {
    scanf("%d%d" , &W , &H);
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d%d" , cx + i , cy + i , hp + i);
        Mountain.insert(make_pair(cx[i] , cy[i]));
    }
    scanf("%d" , &m);
    for (int i = 0 ; i < m ; ++ i) {
        scanf("%d%d%d" , tx + i , ty + i , ms + i);        
        pos_bo[make_pair(tx[i], ty[i])] = i;
    }
    scanf("%d" , &K);
    for (int i = 0 ; i < K ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        Mountain.insert(make_pair(x , y));
    }
    K = 0;
    for (int i = 0 ; i < m ; ++ i) {
        BFS(i);
    }
    sort(U.begin() , U.end());
    U.erase(unique(U.begin() , U.end()) , U.end());
    sort(V.begin() , V.end());
    V.erase(unique(V.begin() , V.end()) , V.end());
    
    s = n + m + K + K , t = s + 1;
    for (int res = n ; res >= 0 ; -- res) {
        for (int mask = 0 ; mask < 1 << n ; ++ mask) {
            if (__builtin_popcount(mask) != res)
                continue;
            int sum = 0;
            memset(pre , -1 , sizeof(pre));
            mcnt = 0;

            for (int i = 0 ; i < m ; ++ i) {
                addarc(s , i , 1);
            }
            for (int i = 0 ; i < (int)U.size() ; ++ i) {
                addarc(U[i].first , m + U[i].second , 1);
            }
            for (int i = 0 ; i < K ; ++ i) {
                addarc(m + i , m + K + i , 1);
            }
            for (int i = 0 ; i < (int)V.size() ; ++ i) {
                addarc(m + K + V[i].first , m + K + K + V[i].second , 1);
            }
            for (int i = 0 ; i < n ; ++ i) {
                if (mask >> i & 1) {
                    addarc(m + K + K + i , t , hp[i]);
                    sum += hp[i];
                }
            }
            if (dinic() != sum) continue;            
            printf("%d\n" , res);
            vector<pair<int, int> > pr;
            for (int i = 0; i < m; ++i)
                for (int k = pre[i]; k != -1; k = e[k].next) {
                    int y = e[k].x;
                    if (e[k ^ 1].f != 1) continue;
                    if (y < m || y >= m + K) continue;
                    pr.push_back(make_pair(i, y - m));
                    //printf("!%d %d %d\n", i, P[y - m].first, P[y-m].second);
                }
            while (1) {
                for (int i = 0; i < pr.size(); ++i)
                    car_bo[pr[i].first] = 1;
                int flag = 0;
                for (int i = 0; i < pr.size(); ++i) {
                    int x = P[pr[i].second].first;
                    int y = P[pr[i].second].second;
                    if (pos_bo.count(make_pair(x, y)) == 0)
                        continue;
                    int id = pos_bo[make_pair(x, y)];
                    if (car_bo[id]) continue;
                    flag = 1;
                    car_bo[id] = 1;
                    car_bo[pr[i].first] = 0;
                    pr[i].first = id;
                    break;
                }
                if (flag == 0) break;
            }
            for (int i = 0; i < pr.size(); ++i) {
                int id = pr[i].first;
                tx[id] = i;
            }
            for (int i = 0; i < m; ++i)
                if (!car_bo[i]) {
                    printf("%d %d 0\n", tx[i], ty[i]);
                }
                else {
                    int id = tx[i];
                    id = pr[id].second;
                    printf("%d %d ", P[id].first, P[id].second);
                    int flag = -1;
                    for (int k = pre[id + m + K]; k != -1; k = e[k].next) {
                        int y = e[k].x;
                        if (e[k ^ 1].f == 1) {
                            if (y >= m + K + K && y < m + K + K + n) {
                                flag = y - m - K - K;
                                break;
                            }
                        }
                    }
                    printf("%d\n", flag + 1);
                }
            return 0;
        }
    }        
    return 0;
}
