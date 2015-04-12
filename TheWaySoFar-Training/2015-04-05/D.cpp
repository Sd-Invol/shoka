#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 100005;

int n , pw;
int pf[N] , vf[N] , th[N] , vw[N];
double e[N];
double cal(double W) {
    double res = W * pw;
    for (int i = 1 ; i <= n ; ++ i) {
        double H = W * vw[i];
        res += max(0.0 , th[i] - H) * e[i];
    }
    return res;
}

void work() {
    scanf("%d",&pw);
    for (int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d%d",&vw[i],&pf[i],&vf[i],&th[i]);
        e[i] = (double)pf[i] / vf[i];
    }
    vector< pair<double , int> > V;
    double K = pw , B = 0;
    for (int i = 1 ; i <= n ; ++ i) {
        if (vw[i] != 0) {
            double x = (double)th[i] / vw[i];
            if (vw[i] < 0) {
                if (x > 0) {
                    V.push_back(make_pair(x , i));
                } else {
                    K += -vw[i] * e[i];
                    B += th[i] * e[i];
                }
            } else {
                if (x > 0) {
                    V.push_back(make_pair(x , -i));
                    K += -vw[i] * e[i];
                    B += th[i] * e[i];
                }
            }
        } else {
            B += max(0 , th[i]) * e[i];
        }
    }
    sort(V.begin() , V.end());
    double res = B;
    for (int i = 0 , j = 0 ; i < V.size() ; ++ i) {
        while (j < V.size() && V[j].first <= V[i].first + 1e-8) {
            int x = V[j ++].second;
            if (x < 0) {
                x = -x;
                K -= -vw[x] * e[x];
                B -= th[x] * e[x];
            } else {
                K += -vw[x] * e[x];
                B += th[x] * e[x];     
            }
        }
        res = min(res , K * V[i].first + B);
    }
    printf("%.10f\n" , res);
}

int main() {
    while (scanf("%d",&n) , n)
        work();
    return 0;
}
