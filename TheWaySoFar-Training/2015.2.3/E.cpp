#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , dx[N] , dy[N] , Dx , Dy;
pair<int , int> a[N];
int A[N] , B[N] , C[N] , D[N];
vector<int> nx , ny;
vector< pair<int , int > > X[N] , Y[N];
set< pair<int , int> > Hash;
int cal(int x , int y) {
    //cout << X[x].size() << ' ' << Y[y].size() << endl;
    priority_queue< pair<int , pair<int , int> > > Q;
    set< pair<int , int> > vis;
    Q.push(make_pair(X[x][0].first + Y[y][0].first , make_pair(0 , 0)));
    vis.insert(make_pair(0 , 0));
    while (!Q.empty()) {
        int i = Q.top().second.first , j = Q.top().second.second , w = Q.top().first; Q.pop();
        if (!Hash.count(make_pair(X[x][i].second , Y[y][j].second)))
            return w;
        if (i + 1 < X[x].size() && !vis.count(make_pair(i + 1 , j))) {
            Q.push(make_pair(X[x][i + 1].first + Y[y][j].first , make_pair(i + 1 , j)));
            vis.insert(make_pair(i + 1 , j));
        }
        if (j + 1 < Y[y].size() && !vis.count(make_pair(i , j + 1))) {
            Q.push(make_pair(X[x][i].first + Y[y][j + 1].first , make_pair(i , j + 1)));
            vis.insert(make_pair(i , j + 1));
        }
    }
    return -1;
}

void work() {
    int i , j , x , y;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d",&x,&y);
        a[i] = make_pair(x , y);
        dx[Dx ++] = x , dy[Dy ++] = y;
    }
    sort(dx , dx + Dx);
    Dx = unique(dx , dx + Dx) - dx;
    sort(dy , dy + Dy);
    Dy = unique(dy , dy + Dy) - dy;
    for (i = 0 ; i < n ; ++ i) {
        a[i].first = lower_bound(dx , dx + Dx , a[i].first) - dx;
        a[i].second = lower_bound(dy , dy + Dy , a[i].second) - dy;
        ++ A[a[i].first] , ++ B[a[i].second];
        Hash.insert(a[i]);
    }
    LL cnt = 0;
    for (i = 0 ; i < n ; ++ i) {
        cnt += (LL) (A[a[i].first] - 1) * (B[a[i].second] - 1);
        C[a[i].first] += B[a[i].second] - 1;
        D[a[i].second] += A[a[i].first] - 1;        
    }
    for (i = 0 ; i < Dx ; ++ i)
        X[A[i]].push_back(make_pair(C[i] , i));
    for (i = 0 ; i < Dy ; ++ i)
        Y[B[i]].push_back(make_pair(D[i] , i));
    for (i = 0 ; i <= n ; ++ i) {
        if (!X[i].empty()) {
            sort(X[i].begin() , X[i].end());
            reverse(X[i].begin() , X[i].end());            
            nx.push_back(i);
        }
        if (!Y[i].empty()) {
            sort(Y[i].begin() , Y[i].end());
            reverse(Y[i].begin() , Y[i].end());
            ny.push_back(i);
        }
    }
    // << cnt << endl;
    LL res = max(*max_element(C , C + Dx) , *max_element(D , D + Dy));
    for (i = 0 ; i < nx.size() ; ++ i)
        for (j = 0 ; j < ny.size() ; ++ j) {
            //cout << nx[i] << ' ' << ny[j] << endl;
            x = cal(nx[i] , ny[j]);
            if (~x)
                res = max(res , (LL)nx[i] * ny[j] + x);
        }
    cout << cnt + res << endl;
}

int main() {
    work();
    return 0;
}
