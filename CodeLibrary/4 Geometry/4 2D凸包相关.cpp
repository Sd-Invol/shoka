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
bool InConvex(Point q, const Point *p , int np) {
    if (OnLeft(q , p[0] , p[1]) < 0 || OnLeft(q , p[0] , p[np - 1]) > 0)
        return 0;
    int l = 2 , r = np - 1;
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
int GetExtremeVertex(const Point *p, int np, std::function<Point(Point)> direction) {
    int left = 0, leftSgn;
    auto vertexCmp = [&p, direction](int i, int j) {
        return dcmp((p[j] - p[i]) ^ (direction(p[j])));
    };
    auto isExtreme = [np, vertexCmp](int i, int& iSgn) {
        iSgn = vertexCmp((i + 1) % np, i);
        return iSgn >= 0 && vertexCmp(i, (i + np - 1) % np) < 0;
    };
    for (int right = isExtreme(0, leftSgn) ? 1 : np; left + 1 < right;) {
        int middle = (left + right) / 2, middleSgn;
        if (isExtreme(middle, middleSgn)) return middle;
        if (leftSgn != middleSgn ? leftSgn < middleSgn
            : leftSgn == vertexCmp(left, middle)) right = middle;
        else left = middle, leftSgn = middleSgn;
    }
    return left;
}
pair<int, int> TangentsConvex(const Point& P, const Point *p , int np) {
    int l = GetExtremeVertex(p, np, [&P](const Point& q) {
            return q - P;
        });
    int r = GetExtremeVertex(p, np, [&P](const Point& q) {
            return P - q;
        });
    return make_pair(l , r);
}
// Binary lifting, should be equivalent with TangentsConvex.
pair<int, int> tangentsConvex(const Point& P, const Point *p , int np) {
  int left = 0, right = 0;
  for (int k = 20 ; k >= 0 ; -- k) {
    int delta = (1 << k) % np;
    if (OnLeft(P, p[left], p[(left + delta) % np]) <= 0) {
      left += delta;
      left %= np;
    }
    if (OnLeft(P, p[left], p[(left + np - delta) % np]) <= 0) {
      left += np - delta;
      left %= np;
    }
    if (OnLeft(P, p[right], p[(right + delta) % np]) >= 0) {
      right += delta;
      right %= np;
    }
    if (OnLeft(P, p[right], p[(right + np - delta) % np]) >= 0) {
      right += np - delta;
      right %= np;
    }
  }
  return make_pair(left , right);
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
