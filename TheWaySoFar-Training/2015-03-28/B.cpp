#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const double eps = 5e-7;
int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
bool cmp(const double& x , const double& y) {
    return dcmp(x - y) == 0;
}
double s[N << 2] , V[N << 2] , A[N << 2];

int n , m;
double alpha , a , b;
pair<int , int> p[N];
void work() {
    int i , j;
    m = 0;
    scanf("%lf%lf%lf" , &a , &b , &alpha);
    for (i = 0 ; i <= n ; ++ i) {
        scanf("%d%d" , &p[i].first , &p[i].second);
        V[m ++] = p[i].first;
    }
    for (i = 0 ; i < n ; ++ i) {
        if (p[i].second != p[i + 1].second) {
            double k = (double)(p[i + 1].second - p[i].second) / (p[i + 1].first - p[i].first);
            double dx = (a - p[i].second) / k;
            // printf("k = %f\n" , k);
            if (dcmp(dx) >= 0 && dcmp(dx - p[i + 1].first + p[i].first) <= 0)
                V[m ++] = (p[i].first + dx);
            dx = (b - p[i].second) / k;            
            if (dcmp(dx) >= 0 && dcmp(dx - p[i + 1].first + p[i].first) <= 0)
                V[m ++] = (p[i].first + dx);            
        }        
    }
    sort(V , V + m);
    m = unique(V , V + m , cmp) - V;
    //for (i = 0 ; i < m ; ++ i) printf("%f\n" , V[i]);
    for (i = 0 , j = 0 ; i < n ; ++ i) {
        double k = (double)(p[i + 1].second - p[i].second) / (p[i + 1].first - p[i].first);
        // printf("%f\n" , k);
        while (j < m && V[j] <= p[i + 1].first) {
            double y = p[i].second + (V[j] - p[i].first) * k;
            A[j] = y;
            ++ j;
        }
    }
    //for (i = 0 ; i < m ; ++ i) printf("%f\n" , A[i]);
    for (i = 1 ; i < m ; ++ i) {
        s[i] = s[i - 1];
        if (dcmp(a - A[i]) <= 0 && dcmp(A[i] - b) <= 0 && dcmp(a - A[i - 1]) <= 0 && dcmp(A[i - 1] - b) <= 0)
            s[i] += V[i] - V[i - 1];
        //printf("s = %f\n" , s[i] - s[i - 1]);
    }
    double S = alpha * s[m - 1];
    double res = 1e10 , L , R;
    for (i = 0 , j = 0 ; i < m ; ++ i) {
        while (j < m && s[j] - s[i] < S)
            ++ j;
        if (j < m) {
            double X = S - (s[j - 1] - s[i]);
            //printf("X = %f\n" , X);
            if (X >= 0 && X <= V[j] - V[j - 1]) {
                double len = X + V[j - 1] - V[i];
                if (X + V[j - 1] - V[i] < res) {
                    res = X + V[j - 1] - V[i];
                    L = V[i];
                    R = V[j - 1] + X;
                }     
            }
        }
    }
    printf("%.10f %.10f\n" , L , R);
    
    
}

int main() {
    freopen("bayes.in" , "r" , stdin);
    freopen("bayes.out" , "w" , stdout);
    
    while (scanf("%d",&n) , n)
        work();
    return 0;    
}
