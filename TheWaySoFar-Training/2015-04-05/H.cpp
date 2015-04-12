#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1005;

struct Point {
    double x , y;
    Point () {}
    Point (double _x , double _y) {
        x = _x , y = _y;
    }
    Point operator * (const double& R) const {
        return Point(x * R , y * R);
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;        
    }
    double operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
};
struct Line {
    Point P , V;
    Line () {}    
    Line (Point p , Point v) {
        P = p , V = v;
    }  
};
Line operator * (const Point& A , const Point& B) {
    return Line(A , B - A);
}
Point operator * (const Line& A , const Line& B) {
    double t = (B.V ^ (A.P - B.P)) / (A.V ^ B.V);
    return A.P + A.V * t;
}
Point operator * (const Line& A , const Point& B) {
    Point C = A.P + A.V * ((A.V % (B - A.P)) / (A.V % A.V));
    return C + C - B;
}
Point operator * (const Point& B , const Line& A) {
    Point C = A.P + A.V * ((A.V % (B - A.P)) / (A.V % A.V));
    return C + C - B;
}

char str[N];
int n , m;
Point p[N];
Line l[N];
int type[N];
int get(int L , int R) {
    //printf("%d %d\n" , L , R);
    int i , j , k , x = 0 , y = -1;
    for (i = L ; i <= R ; ++ i) {
        if (str[i] == '(')
            ++ x;
        else if (str[i] == ')')
            -- x;
        else if (str[i] == '@') {
            if (x == 0)
                y = i;
        }
    }
    if (!~y) {
        if (str[L] == '(') {
            assert(str[R] == ')');
            return get(L + 1 , R - 1);
        } else {
            assert(str[L] == '[');
            assert(str[R] == ']');
            i = L + 1;
            x = y = 0;
            k = 1;
            if (str[i] == '-')
                k = -1 , ++ i;
            while (isdigit(str[i]))
                x = x * 10 + str[i ++] - '0';
            x *= k;
            assert(str[i] == ',');
            ++ i;
            y = 0;
            k = 1;
            if (str[i] == '-')
                k = -1 , ++ i;
            while (isdigit(str[i]))
                y = y * 10 + str[i ++] - '0';
            y *= k;
            assert(str[i] == ']');
            ++ m;
            type[m] = 1;
            p[m] = Point(x , y);
            //printf("*%d %d\n" , x , y);
            return m;
        }
    } else {
        x = get(L , y - 1);
        y = get(y + 1 , R);
        ++ m;
        if (type[x] == 1 && type[y] == 1) {
            type[m] = 2;
            l[m] = p[x] * p[y];
        }
        if (type[x] == 1 && type[y] == 2) {
            type[m] = 1;
            p[m] = p[x] * l[y];
        }
        if (type[x] == 2 && type[y] == 1) {
            type[m] = 1;
            p[m] = l[x] * p[y];
        }
        if (type[x] == 2 && type[y] == 2) {
            type[m] = 1;
            p[m] = l[x] * l[y];
        }        
        return m;
    }
}

void work() {    
    int i , j , k , x , y;
    n = strlen(str);

    for (i = 0 ; i < n ; ++ i) {
        if (isdigit(str[i]) || str[i] == '-') {
            if (i > 0 && str[i - 1] == '(')
                str[i - 1] = '[';
            if (i + 1 < n && str[i + 1] == ')')
                str[i + 1] = ']';            
        }
    }
    //puts(str);
    m = 0;
    k = get(0 , n - 1);
    printf("%.10f %.10f\n" , p[k].x , p[k].y);
}

int main() {
    while (scanf("%s" , str) , *str != '#')
        work();
    return 0;
}
/*
((0,0)@(1,1))@((4,1)@(2,5))
3.00000000 3.00000000
((0,0)@(3,1))@((1,-3)@(2,-1))
3.00000000 1.00000000
(0,0)@(1,1)@(4,1)
1.00000000 4.00000000
(0,0)@((1,1)@(4,1))
0.00000000 2.00000000
(((0,0)@((10,20)@(((30,40))))))
-10.00000000 10.00000000
((0,0)@(3,1))@((1,-3)@(2,-1))@(100,-100)@(100,100)
-99.83681795 -91.92248853
#
 */
