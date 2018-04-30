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

vector<pair<double, int>> StabPolygonLength(Point P, Point V, const Point *p, int np) {
    auto arg = [&P, &V](Point Q, Point W) {
        return (W ^ (P - Q)) / (V ^ W);
    };
    vector<pair<double, int>> events;
    for (int i = 0 ; i < np ; ++ i) {
        int d0 = dcmp((p[i] - P) ^ V), d1 = dcmp((p[(i + 1) % np] - P) ^ V);
        if (d0 == d1) continue;
        double t = arg(p[i] , p[(i + 1) % np] - p[i]);
        int sign = d0 < d1 ? 1 : -1;
        events.emplace_back(t , sign * (d0 && d1 ? 2 : 1));
    }
    sort(events.begin() , events.end());
    return events;
}
