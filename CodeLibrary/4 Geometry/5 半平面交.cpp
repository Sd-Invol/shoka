typedef vector<Point> Polygon;

//用有向直线AB的左半平面切割 O(n)
Polygon CutPolygon(const Polygon& poly , Point A , Point B) {
    Polygon newpoly;
    int n = poly.size();
    for (int i = 0 ; i < n ; ++ i) {
        const Point &C = poly[i] , &D = poly[(i + 1) % n];
        if (dcmp((B - A) ^ (C - A)) >= 0)
            newpoly.push_back(C);
        if (dcmp((B - A) ^ (C - D)) != 0) {
            double t = ((B - A) ^ (C - A)) / ((D - C) ^ (B - A));
            if (dcmp(t) > 0 && dcmp(t - 1) < 0)
                newpoly.push_back(C + (D - C) * t);
        }
    }
    return newpoly;
}
/****************************************************/
inline bool Onleft(Line L , Point P) {
    return (L.V ^ (P - L.P)) > 0;
}
Point GetLineIntersection(Line A , Line B) {
    Point u = A.P - B.P;
    double t = (B.V ^ u) / (A.V ^ B.V);
    return A.point(t);
}
Point p[N];
Line q[N];
int HalfPlaneIntersection(Line* L , int n , Point* Poly) {
    sort(L , L + n);
    int top = 0 , bot = 0;
    q[0] = L[0];
    for (int i = 1 ; i < n ; ++ i) {
        while (top < bot && !Onleft(L[i] , p[bot - 1])) -- bot;
        while (top < bot && !Onleft(L[i] , p[top])) ++ top;
        q[++ bot] = L[i];
        if (dcmp(L[i].V ^ q[bot - 1].V) == 0) {
            -- bot;
            if (Onleft(q[bot] , L[i].P))
                q[bot] = L[i];
        }
        if (top < bot)
            p[bot - 1] = GetLineIntersection(q[bot - 1] , q[bot]);
    }
    while (top < bot && !Onleft(q[top] , p[bot - 1])) -- bot;
    if (bot - top <= 1) return 0;
    p[bot] = GetLineIntersection(q[bot] , q[top]);
    int m = 0;
    for (int i = top ; i <= bot ; ++ i) Poly[m ++] = p[i];
    return m;
}
