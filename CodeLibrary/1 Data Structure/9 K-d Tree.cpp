struct Point3D {
    int x , y , z;
    bool operator < (const Point3D& R) const {
        if (x != R.x)
            return x < R.x;
        if (y != R.y)
            return y < R.y;
        return z < R.z;
    }
}P[N]; 
typedef pair<int , int> Point;
typedef pair<int , int> Value;
Point a[N];
bool cmpX(const Point& A , const Point& B) {
    return A < B;
}
bool cmpY(const Point& A , const Point& B) {
    return make_pair(A.second , A.first) < make_pair(B.second , B.first);
}
inline void add(Value& A , Value B) {
    if (B.first > A.first)
        A = B;
    else if (B.first == A.first)
        A.second += B.second;
}
int cnt , root;
struct Node {
    Point u , low , high;
    Value val , mx;
    int c[2];
    Node () {}
    Node(int K , Point p) {
        u = low = high = p;
        c[0] = c[1] = 0;
        val = mx = make_pair(-1 << 30 , 0);
    }
    void merge(const Node& R) {
        low.first = min(low.first , R.low.first);
        low.second = min(low.second , R.low.second);
        high.first = max(high.first , R.high.first);
        high.second = max(high.second , R.high.second);
        add(mx , R.mx);
    }
}t[N];
inline void update(int p) {
    t[p].mx = t[p].val;
    t[p].high = t[p].low = t[p].u;
    if (t[p].c[0])
        t[p].merge(t[t[p].c[0]]);
    if (t[p].c[1])
        t[p].merge(t[t[p].c[1]]);
}
void build(int& p , int k , int l , int r) {
    p = cnt ++;
    int mid = l + r >> 1;
    nth_element(a + l , a + mid , a + r , k ? cmpY : cmpX);
    t[p] = Node(k , a[mid]);
    if (l < mid)
        build(t[p].c[0] , k ^ 1 , l , mid);
    if (mid + 1 < r)
        build(t[p].c[1] , k ^ 1 , mid + 1 , r);
    update(p);
}
LL cnt1 , cnt2;
void query(int p , int k , const Point& P , Value& res) {
    if (!p) return;
    ++ cnt1;
    if (t[p].high.first <= P.first && t[p].high.second <= P.second)
        return add(res , t[p].mx);
    if (t[p].u.first <= P.first && t[p].u.second <= P.second)
        add(res , t[p].val);
    if (k) {
        query(t[p].c[0] , k ^ 1 , P , res);
        if (t[p].u.second <= P.second)
            query(t[p].c[1] , k ^ 1 , P , res);
    } else {
        query(t[p].c[0] , k ^ 1 , P , res);
        if (t[p].u.first <= P.first)
            query(t[p].c[1] , k ^ 1 , P , res);
    }
} 
void modify(int p , int k , const Point& P , const Value& val) {
    if (!p) return;
    ++ cnt2;
    if (t[p].u == P) {
        t[p].val = val;
    } else {
        if (k) {
            if (P.second <= t[p].u.second)
                modify(t[p].c[0] , k ^ 1 , P , val);
            if (P.second >= t[p].u.second)
                modify(t[p].c[1] , k ^ 1 , P , val);
        } else {
            if (P.first <= t[p].u.first)
                modify(t[p].c[0] , k ^ 1 , P , val);
            if (P.first >= t[p].u.first)
                modify(t[p].c[1] , k ^ 1 , P , val);
        }
    }
    update(p);
}
 
void work() {
    int i , n;
    scanf("%d",&n);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%d%d%d",&P[i].x , &P[i].y , &P[i].z);
        a[i] = make_pair(P[i].y , P[i].z);
    }
    sort(P , P + n) , sort(a , a + n);
    int m = unique(a , a + n) - a;
    cnt = 1 , root = 0;
    build(root , 0 , 0 , m);
 
    Value ans(-1 << 30 , 0);
    for (i = 0 ; i < n ; ++ i) {
        Point p = make_pair(P[i].y , P[i].z);
        Value w = make_pair(0 , 1);
        query(root , 0 , p , w);
        ++ w.first , add(ans , w);
        modify(root , 0 , p , w);
    }
    printf("%d %d\n" , ans.first , ans.second & ((1 << 30) - 1));
}
void getNearest(int p , int k) {
	if (!p) return;
	if (t[p].vis) {
        LL dis = dist(P , t[p].u);
        if (dis < res || (dis == res && t[p].o < t[ret].o))
            res = dis , ret = p;
	}
    if (k) {
        if (cmpY(P , t[p].u)) {
            getNearest(t[p].c[0] , k ^ 1);
            if (sqr(P.second - t[p].u.second) <= res)
                getNearest(t[p].c[1] , k ^ 1);
        } else {
            getNearest(t[p].c[1] , k ^ 1);
            if (sqr(P.second - t[p].u.second) <= res)
                getNearest(t[p].c[0] , k ^ 1);
        }
    } else {
        if (cmpX(P , t[p].u)) {
            getNearest(t[p].c[0] , k ^ 1);
            if (sqr(P.first - t[p].u.first) <= res)
                getNearest(t[p].c[1] , k ^ 1);
        } else {
            getNearest(t[p].c[1] , k ^ 1);
            if (sqr(P.first - t[p].u.first) <= res)
                getNearest(t[p].c[0] , k ^ 1);
        }
    }
}
