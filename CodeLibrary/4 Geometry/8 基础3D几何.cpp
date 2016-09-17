const double eps = 1e-8 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point {
    double x , y , z;
    Point () {x = y = z = 0;}
    Point (double _x , double _y , double _z) {
        x = _x , y = _y , z = _z;
    }
    void input() {
        scanf("%lf%lf%lf" , &x , &y , &z);
    }
    bool operator < (const Point &R) const {
        if (dcmp(x - R.x) != 0)
            return x < R.x;
        if (dcmp(y - R.y) != 0)
            return y < R.y;
        return z < R.z;
    }
    bool operator == (const Point &R) const {
        return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0 && dcmp(z - R.z) == 0;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y , z + R.z);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y , z - R.z);
    }
    Point operator * (const double& R) const {
        return Point(x * R , y * R , z * R);
    }
    Point operator / (const double& R) const {
        return Point(x / R , y / R , z / R);
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y + z * R.z;
    }
    Point operator ^ (const Point& R) const {
        return Point(y * R.z - z * R.y , z * R.x - x * R.z , x * R.y - y * R.x);
    }
    inline double len() {
        return sqrt(*this % *this);
    }
}; 
Point GetLinePlaneProjection(Point A , Point P , Point n) {
    double t = (n % (P - A)) / (n % n);
    return A + n * t; // t * n.len() 是距离
} // 直线平面投影
Point GetLinePlaneIntersection(Point A , Point V , Point P , Point n) {
    double t = (n % (P - A)) / (n % V);
    return A + V * t;
} // 直线平面交点
inline double area(Point A , Point B , Point C) {
    return ((B - A) ^ (C - A)).len();
}
bool PointinTri(Point P) {
    double area1 = area(P , a[0] , a[1]);
    double area2 = area(P , a[1] , a[2]);
    double area3 = area(P , a[2] , a[0]);
    return dcmp(area1 + area2 + area3 - area(a[0] , a[1] , a[2])) == 0;
}
double GetLineIntersection(Point P , Point v , Point Q , Point w) {
    //共面时使用 
    Point u = P - Q;
    Point delta = v ^ w , cross = w ^ u;     
    if (dcmp(delta.z) != 0)
        return cross.z / delta.z;
    else if (dcmp(delta.y) != 0)
        return cross.y / delta.y;
    else if (dcmp(delta.x) != 0)
        return cross.x / delta.x;
    else {
        return 1e60;
    }
}

//a点绕Ob向量逆时针旋转弧度angle. cossin可预先计算
Point Rotate(Point a, Point b, double angle) {
    static Point e1 ,e2 , e3;
    b = b / b.len() , e3 = b;
    double lens = a % e3;
    e1 = a - e3 * lens;
    if (dcmp(e1.len()) > 0)
        e1 = e1 / e1.len();
    else
        return a;
    e2 = e1 ^ e3;
    double x1 = a % e2 , y1 = a % e1 , x2 , y2;
    x2 = x1 * cos(angle) - y1 * sin(angle);
    y2 = x1 * sin(angle) + y1 * cos(angle);
    return e3 * lens + e1 * y2 + e2 * x2;
}
/**
   绕任意轴（过原点）逆时针旋转（注意要把轴向量归一化，不然会在“点在轴上”这个情况下出问题）
   rotate x y z d 
   | (1-cos(d))*x*x+cos(d)     (1-cos(d))*x*y+sin(d)*z   (1-cos(d))*x*z-sin(d)*y   0 |
   | (1-cos(d))*y*x-sin(d)*z   (1-cos(d))*y*y+cos(d)     (1-cos(d))*y*z+sin(d)*x   0 |
   | (1-cos(d))*z*x+sin(d)*y   (1-cos(d))*z*y-sin(d)*x   (1-cos(d))*z*z+cos(d)     0 |
   |           0                          0                           0            1 |
**/
