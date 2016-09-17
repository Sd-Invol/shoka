/******圆和多边形求交****/
double sector_area(Point A , Point B , double R) {
    double theta = Angle(A) - Angle(B);
    while (theta < 0) theta += pi + pi;
    while (theta >= pi + pi) theta -= pi + pi;
    theta = min(theta , pi + pi - theta);
    return R * R * theta;
}//a[n] = a[0]
double cal(double R) {
    double area = 0;
    for (int i = 0 ; i < n ; ++ i) {
        double t1 = 0 , t2 = 0 , delta;
        Line L = Line(a[i] , a[i + 1]);
        int cnt = getLineCircleIntersection(L , Circle(Point(0 , 0) , R) , t1 , t2);
        Point X = L.point(t1) , Y = L.point(t2);
        bool f1 = dcmp(a[i].len() - R) <= 0 , f2 = dcmp(a[i + 1].len() - R) <= 0;
        if (f1 && f2)
            delta = fabs(a[i] ^ a[i + 1]);
        else if (!f1 && f2) {
            delta = sector_area(a[i] , X , R) + fabs(X ^ a[i + 1]);
        } else if (f1 && !f2) {
            delta = fabs(a[i] ^ Y) + sector_area(Y , a[i + 1] , R);
        } else {
            if (cnt > 1 && 0 < t1 && t1 < 1 && 0 < t2 && t2 < 1) {
                delta = sector_area(a[i] , X , R) + sector_area(Y , a[i + 1] , R) + fabs(X ^ Y);
            } else {
                delta = sector_area(a[i] , a[i + 1] , R);
            }
        }
        area += delta * dcmp(a[i] ^ a[i + 1]);
    }
    return area / 2;
}
/*********圆交/并*******/
void getarea() { // 计算圆并的重心，必要的时候可以去除有包含关系的圆
    for (int i = 0 ; i < n ; ++ i) {
        vector< pair<double , int> > Vec;
        int cnt = 1;
        Vec.push_back({0 , 0});
        Vec.push_back({2 * pi , 0});
        for (int j = 0 ; j < n ; ++ j) {
            double dist = (c[j].O - c[i].O).len();
            if (dcmp(dist) == 0 && dcmp(c[i].r - c[j].r) == 0) {
                if (i < j) {
                    ++ cnt;
                }
                continue;
            }
            if (dcmp(dist - c[j].r - c[i].r) >= 0) {
                continue;
            }
            if (dcmp(dist + c[j].r - c[i].r) <= 0) { // j in i
                continue;
            }
            if (dcmp(dist + c[i].r - c[j].r) <= 0) { // i in j
                ++ cnt;
                continue;
            }
            double an = atan2(c[j].O.y - c[i].O.y , c[j].O.x - c[i].O.x);
            double p = (c[i].r * c[i].r + dist * dist - c[j].r * c[j].r) / (2 * c[i].r * dist);
            double da = acos(max(-1.0 , min(1.0 , p)));

            double L = an - da , R = an + da;
            //printf("%d : %f %f\n" , j , L , R);
            if (L < 0) L += 2 * pi;
            if (R < 0) R += 2 * pi;
            if (L >= 2 * pi) L -= 2 * pi;
            if (R >= 2 * pi) R -= 2 * pi;
            if (L < R) {
                Vec.push_back({L , 1});
                Vec.push_back({R , -1});
            } else {
                Vec.push_back({0 , 1});
                Vec.push_back({R , -1});
                Vec.push_back({L , 1});
                Vec.push_back({2 * pi , -1});
            }
        }
        sort(Vec.begin() , Vec.end());
        for (int j = 0 ; j + 1 < Vec.size() ; ++ j) {
            //printf("%d : %d %f\n" , j , cnt , Vec[j].first);
            cnt += Vec[j].second;
            if (cnt == 1) {
                double delta = Vec[j + 1].first - Vec[j].first;
                if (dcmp(delta) <= 0)
                    continue;
                double SIN = sin(delta / 2);
                Point W = Point(0 , 4 * c[i].r * SIN * SIN * SIN / (3 * (delta - sin(delta))));
                W = Rotate(W , (Vec[j + 1].first + Vec[j].first - pi) / 2) + c[i].O;
                double area = c[i].r * c[i].r * (delta - sin(delta));
                sx -= area * W.x;
                sy -= area * W.y;
                s -= area;

                Point A = c[i].point(Vec[j].first) , B = c[i].point(Vec[j + 1].first);
                area = (A ^ B);
                sx -= area * (A.x + B.x) / 3;
                sy -= area * (A.y + B.y) / 3;
                s -= area;
            }
        }
    }
}
