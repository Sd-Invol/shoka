LL det(LL A[][N]) {
    LL ans = 1;
    for (int i = 1 ; i <= n ; ++ i) {
        for (int j = i + 1 ; j <= n ; ++ j) {
            while (A[j][i]) {
                LL t = A[i][i] / A[j][i];
                for (int k = 1 ; k <= n ; ++ k) {
                    A[i][k] -= A[j][k] * t;
                    swap(A[i][k] , A[j][k]);
                }
                ans = -ans;
            }
        }
        if (!A[i][i])
            return 0;
        ans *= A[i][i];
    }
    return ans;
}
