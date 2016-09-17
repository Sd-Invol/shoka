int rank = 0;
for (int i = 0 ; i < n && rank < m ; ++ i) {
    int pivot = rank;
    for (int j = rank + 1 ; j < m ; ++ j)
        if (fabs(a[j][i]) > fabs(a[pivot][i]))
            pivot = j;
    if (fabs(a[pivot][i]) < 1e-10)
        continue;
    for (int j = 0 ; j < n ; ++ j)
        swap(a[rank][j] , a[pivot][j]);
    double tmp = a[rank][i];
    for (int j = 0 ; j < n ; ++ j)
        a[rank][j] /= tmp;
    for (int k = 0 ; k < m ; ++ k) {
        if (k != rank) {
            double times = a[k][i];
            for (int j = 0 ; j < n ; ++ j) {
                a[k][j] -= a[rank][j] * times;
            }
        }
    }
    ++ rank;
}
