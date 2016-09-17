void work() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        L[i].input();
        P[i] = L[i];
    }
    int m = n;
    for (int i = 0 ; i + 1 < n ; ++ i)        
        for (int j = i + 1 ; j + 1 < n ; ++ j) {
            if (dcmp((P[i + 1] - P[i]) ^ (P[j + 1] - P[j])) != 0)
                P[m ++] = GetLineIntersection(P[i] , P[i + 1] - P[i] , P[j] , P[j + 1] - P[j]);
        }
    sort(P , P + m);
    m = unique(P , P + m) - P;
    memset(pre , -1 , sizeof(pre));
    set< pair<int , int> > Hash;
    for (int i = 0 ; i + 1 < n ; ++ i) {
        vector< pair <Point , int> > V;
        for (int j = 0 ; j < m ; ++ j)
            if (OnSegment(P[j] , L[i] , L[i + 1]))
                V.push_back(make_pair(P[j] , j));
        sort(V.begin() , V.end());
        for (int j = 0 ; j + 1 < V.size() ; ++ j) {
            int x = V[j].second , y = V[j + 1].second; 
            if (!Hash.count(make_pair(x , y))) {
                Hash.insert(make_pair(x , y));
                e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
            }
            if (!Hash.count(make_pair(y , x))) {
                Hash.insert(make_pair(y , x));
                e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
            }
        }
    }
    for (int x = 0 ; x < m ; ++ x) {
        vector< pair<double , int> > V;
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x;
            V.push_back(make_pair((P[y] - P[x]).arg() , i));
        }
        sort(V.begin() , V.end());
        for (int i = 0 ; i < V.size() ; ++ i) {
            int j = (i + 1) % V.size();
            Next[V[j].second ^ 1] = V[i].second;
        }
    }
    double res = 0;
    for (int i = 0 ; i < mcnt ; ++ i) {
        if (!vis[i]) {
            int x = i;
            double area = 0;
            while (!vis[x]) {
                vis[x] = 1;
                area += (P[e[x ^ 1].x] ^ P[e[x].x]);
                x = Next[x];
            }
            if (x == i && dcmp(area) > 0)
                res += area;
        }
    }
    printf("%.8f\n" , res / 2);
}
