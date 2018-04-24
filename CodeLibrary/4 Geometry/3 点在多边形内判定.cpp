int PointInPolygon(Point P , const Point *p , int np) {
    for (int i = 0 ; i < np ; ++ i)
        if (OnSegment(P , p[i] , p[(i + 1) % np]))
            return 0;
    int res = -1;
    for (int i = 0 ; i < np ; ++ i) {
        Point a = p[i] , b = p[(i + 1) % np];
        if (a.y > b.y) swap(a , b);
        if (dcmp((a - P) ^ (b - P)) < 0 &&
            dcmp(a.y - P.y) < 0 &&
            dcmp(b.y - P.y) >= 0) {
            res = -res;
        }
    }
    return res;
}
