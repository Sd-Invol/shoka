inline LL OnLeft(Point P , Point A , Point B) {
    return (B - A) ^ (P - A);
}
/********* Naive 凸包 2.0 O(n+m) *********/
int top = 0;
for (int i = 0 ; i < n ; ++ i) {
    while (top > 1 && OnLeft(p[i] , s[top - 2] , s[top - 1]) <= 0) {
        -- top;
    }
    s[top ++] = p[i];
}
int tmp = top;
for (int i = n - 2 ; i >= 0 ; -- i) {
    while (top > tmp && OnLeft(p[i] , s[top - 2] , s[top - 1]) <= 0) {
        -- top;
    }
    s[top ++] = p[i];
}
if (n > 1)
    -- top;
/********* Minkowski-Sum O(n+m) *********/
Vec.clear();
Point cur = a[0] + b[0];
for (int i = 0 , j = 0 ; i < n || j < m ; ) {
    if (i < n && (j == m || ((a[i + 1] - a[i]) ^ (b[j + 1] - b[j])) >= 0)) {
        cur = cur + a[i + 1] - a[i];
        ++ i;
    } else {
        cur = cur + b[j + 1] - b[j];
        ++ j;
    }
    Vec.push_back(make_pair(cur , 1));
}
/******* 点在凸多边形内判定 O(logn) *******/
bool InConvex(Point q) {
    if (OnLeft(q , p[0] , p[1]) < 0 || OnLeft(q , p[0] , p[n - 1]) > 0)
        return 0;
    int l = 2 , r = n - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (OnLeft(q , p[0] , p[mid]) <= 0) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return OnLeft(q , p[r - 1] , p[r]) >= 0;
}
/******* 点到凸多边形的切线 O(logn) *******/
#define above(b , c) (OnLeft(b , q , c) > 0)
#define below(b , c) (OnLeft(b , q , c) < 0)
int getRtangent(Point q) { // find max
    int ret = 0;
    int l = 1 , r = n - 1;
    while (l <= r) {
        int dnl = above(p[l] , p[l + 1]);
        int mid = l + r >> 1;
        int dnm = above(p[mid] , p[mid + 1]);
        if (dnm) {
            if (above(p[mid], p[ret])) {
                ret = mid;
            }
        }
        if (dnl) {
            if (above(p[l], p[ret])) {
                ret = l;
            }
            if (dnm && above(p[mid] , p[l])) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (!dnm && above(p[mid] , p[l])) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return ret;
}
int getLtangent(Point q) { // find min
    int ret = 0;
    int l = 1 , r = n - 1;
    while (l <= r) {
        int dnl = below(p[l] , p[l - 1]);
        int mid = l + r + 1 >> 1;
        int dnm = below(p[mid] , p[mid - 1]);
        if (dnm) {
            if (below(p[mid], p[ret])) {
                ret = mid;
            }
        }
        if (dnl) {
            if (below(p[l], p[ret])) {
                ret = l;
            }
            if (dnm && below(p[mid] , p[l])) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        } else {
            if (!dnm && below(p[mid] , p[l])) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    return ret;
}
/****** 直线对凸多边形的交点 O(logn) ******/
double arc[N] , sum[N];
void init() {
    for (int i = 0 ; i < n ; ++ i) {
        p[i + n] = p[i];
    } p[n + n] = p[0];
    for (int i = 0 ; i < n + n ; ++ i) {
        sum[i + 1] = sum[i] + (p[i] ^ p[i + 1]);
    }
    for (int i = 0 ; i < n ; ++ i) {
        int j = (i + 1) % n;
        arc[i] = atan2(p[j].y - p[i].y , p[j].x - p[i].x);
        if (i && arc[i] < arc[i - 1]) {
            arc[i] += pi + pi;
        }
    }
}
int getseg(Point P , Point V , int l , int r) {
    -- l;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if ((V ^ (p[mid] - P)) < 0) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}
void work(Point A , Point B) {
    if (B < A) {
        swap(A , B);
    }
    double al = atan2(B.y - A.y , B.x - A.x);
    if (al < arc[0]) al += pi + pi;
    int Left = (lower_bound(arc , arc + n , al) - arc) % n;
    double ar = atan2(A.y - B.y , A.x - B.x);
    if (ar < arc[0]) ar += pi + pi;
    int Right = lower_bound(arc , arc + n , ar) - arc;
    int down = getseg(A , B - A , Left , Right);
    int up = getseg(B , A - B , Right , Left + n);
    if (down < Left || up < Right) {
        puts("0.000000");
    } else {
        Point D = GetLineIntersection(A , B - A , p[down] , p[down + 1] - p[down]);
        Point U = GetLineIntersection(B , A - B , p[up] , p[up + 1] - p[up]);
        //printf("%f %f / %f %f\n" , D.x , D.y , U.x , U.y);
        double area = (D ^ p[down + 1]) + (sum[up] - sum[down + 1]) + (p[up] ^ U) + (U ^ D);
        printf("%.6f\n" , min(sum[n] - area , area) / 2);
    }
}
