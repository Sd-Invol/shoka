double mix(const Point &a, const Point &b, const Point &c) {
    return a % (b ^ c);
}
const int N = 305;
int mark[N][N];
Point info[N];
int n , cnt;
 
double area(int a, int b, int c) {
    return ((info[b] - info[a]) ^ (info[c] - info[a])).len();
}
double volume(int a, int b, int c, int d) {
    return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]);
}
struct Face {
    int v[3];
    Face() {}
    Face(int a, int b, int c) {
        v[0] = a , v[1] = b , v[2] = c;
    }
    int& operator [] (int k) {
        return v[k];
    }
};
vector <Face> face;
inline void insert(int a, int b, int c) {
    face.push_back(Face(a, b, c));
}
void add(int v) {
    vector <Face> tmp;
    int a, b, c;
    cnt ++;
    for (int i = 0; i < face.size() ; ++ i) {
        a = face[i][0] , b = face[i][1] , c = face[i][2];
        if (dcmp(volume(v, a, b, c)) < 0)
            mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
        else
            tmp.push_back(face[i]);
    }
    face = tmp;
    for (int i = 0; i < tmp.size() ; ++ i) {
        a = face[i][0] , b = face[i][1] , c = face[i][2];
        if (mark[a][b] == cnt) insert(b, a, v);
        if (mark[b][c] == cnt) insert(c, b, v);
        if (mark[c][a] == cnt) insert(a, c, v);
    }
}
int Find() {
    for (int i = 2; i < n; ++ i) {
        Point ndir = (info[0] - info[i]) ^ (info[1] - info[i]);
        if (ndir == Point())
            continue;
        swap(info[i], info[2]);
        for (int j = i + 1; j < n; j++)
            if (dcmp(volume(0, 1, 2, j)) != 0) {
                swap(info[j], info[3]);
                insert(0, 1, 2);
                insert(0, 2, 1);
                return 1;
            }
    }
    return 0;
}
void work() {
    for (int i = 0; i < n; ++ i)
        info[i].input();
    sort(info, info + n);
    n = unique(info, info + n) - info;
    face.clear();
    random_shuffle(info, info + n);
    if (Find()) {
        memset(mark, 0, sizeof(mark));
        cnt = 0;
        for (int i = 3; i < n; ++ i) add(i);
        vector<Point> Ndir;
        for (int i = 0; i < face.size() ; ++i) {
            Point p = (info[face[i][0]] - info[face[i][1]]) ^ (info[face[i][2]] - info[face[i][1]]);
            p = p / p.len();
            Ndir.push_back(p);
        }
        sort(Ndir.begin(), Ndir.end());
        int ans = unique(Ndir.begin(), Ndir.end()) - Ndir.begin();
        printf("%d\n", ans);
    } else {
        printf("1\n");
    }
}
