for (int i = 0 ; i < n ; ++ i)
    if (OnSegment(P , p[i] , p[i + 1]))
        return 0;
int res = 0;
for (int i = 0 ; i < n ; ++ i) {
    Point a = p[i] , b = p[i + 1];
    if (a.y > b.y) swap(a , b);
    if (dcmp((a - P) ^ (b - P)) < 0 && dcmp(a.y - P.y) < 0 && dcmp(b.y - P.y) >= 0)
        res ^= 1;
}
return res;
