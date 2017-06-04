struct Line {
    Point P , V; // P + Vt
    double angle;
    Line () {}
    Line (Point A , Point B) {
        P = A , V = B - A;
        angle = atan2(V.y , V.x);
    }
    bool operator < (const Line& R) const {
        return angle < R.angle;
    }
    Point point(double t) {
        return P + V * t;
    }
};
struct Circle {
    Point O;
    double r;
    Circle () {}
    Circle (Point _O , double _r) {
        O = _O , r = _r;
    }
    Point point(double arc) {
        return Point(O.x + cos(arc) * r , O.y + sin(arc) * r);
    }
    void input() {
        O.input() , scanf("%lf",&r);
    }
};

// 判定直线与圆相交
// 方法为连立直线的参数方程与圆的方程，很好理解
// t1,t2为两个参数，sol为点集。有了参数，射线线段什么的也很方便
int getLineCircleIntersection(Line L , Circle C , double& t1 , double& t2 , vector<Point>& sol) {
    double a = L.V.x , b = L.P.x - C.O.x , c = L.V.y , d = L.P.y - C.O.y;
    double e = a * a + c * c , f = 2 * (a * b + c * d);
    double g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
        t1 = t2 = -f / (2 * e);
        sol.push_back(L.point(t1));
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (e + e);
    t2 = (-f + sqrt(delta)) / (e + e);
    sol.push_back(L.point(t1)) , sol.push_back(L.point(t2));
    return 2;
}
// 判定圆和圆之间的关系
// 内含，内切，相交，重合，外切，相离
int getCircleCircleIntersection(Circle C1 , Circle C2 , vector<Point>& sol) {
    double d = (C1.O - C2.O).len();
    if (dcmp(d) == 0) { //同心
        if (dcmp(C1.r - C2.r) == 0)//重合
            return -1;
        return 0;//内含
    }
    if (dcmp(C1.r + C2.r - d) < 0) return 0;//相离
    if (dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;//内含
    double a = (C2.O - C1.O).angle();
    double p = (C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d);
    p = max(-1.0 , min(1.0 , p));
    double da = acos(p);
    Point P1 = C1.point(a - da) , P2 = C1.point(a + da);
    sol.push_back(P1);
    if (dcmp(da) == 0) return 1; //切
    sol.push_back(P2);
    return 2;
}
// 过点p到圆C的切线。返回切线条数，sol里为方向向量
int getTangents(Point P, Circle C, vector<Point>& sol) {
    Point u = C.O - P;
    double dist = u.len();
    if(dist < C.r) return 0;
    if(dcmp(dist - C.r) == 0) {
        sol.push_back(Rotate(u, pi / 2));
        return 1;
    } else {
        double ang = asin(C.r / dist);
        sol.push_back(Rotate(u, +ang));
        sol.push_back(Rotate(u, -ang));
        return 2;
    }
}
//两个圆的公切线，对应切点存在ab里面
int getTangents(Circle A , Circle B , Point* a , Point* b) {
    int cnt = 0;
    if (A.r < B.r) swap(A , B) , swap(a , b);
    double dist = (A.O - B.O).len() , dr = A.r - B.r , sr = A.r + B.r;
    if (dcmp(dist - dr) < 0) // 内含
        return 0;
    double base = (B.O - A.O).angle();
    if (dcmp(dist) == 0 && dcmp(A.r - B.r) == 0)
        return -1;//重合
    if (dcmp(dist - dr) == 0) {//内切
        a[cnt] = A.point(base);
        b[cnt] = B.point(base);
        return 1;
    }
    double ang = acos(dr / dist);//非上述情况，两条外公切线
    a[cnt] = A.point(base + ang) , b[cnt] = B.point(base + ang) , ++ cnt;
    a[cnt] = A.point(base - ang) , b[cnt] = B.point(base - ang) , ++ cnt;
    if (dcmp(dist - sr) == 0) {// 外切，中间一条内公切线
        a[cnt] = A.point(base) , b[cnt] = B.point(pi + base) , ++ cnt;
    } else if (dcmp(dist - sr) > 0) {
        ang = acos(sr / dist);//相离，两条内公切线
        a[cnt] = A.point(base + ang) , b[cnt] = B.point(pi + base + ang) , ++ cnt;
        a[cnt] = A.point(base - ang) , b[cnt] = B.point(pi + base - ang) , ++ cnt;
    }
    return cnt;
}
// 外接圆，三根中线交点
Circle CircumscribedCircle(Point A , Point B , Point C) {
    Point D = (B + C) / 2 , d = Normal(B - C);
    Point E = (A + C) / 2 , e = Normal(A - C);
    Point P = GetLineIntersection(D , d , E , e);
    return Circle(P , (C - P).len());
}
// 内接圆，黑科技
Circle InscribedCircle(Point A , Point B , Point C) {
    double a = (B - C).len() , b = (A - C).len() , c = (A - B).len();
    Point P = (A * a + B * b + C * c) / (a + b + c);
    return Circle(P , fabs(DistancePointToLine(P , A , B)));
}
