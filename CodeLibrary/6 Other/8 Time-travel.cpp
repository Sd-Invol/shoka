int del[N];
void divide(const vector<int> &A) {
    if (A.size() <= 1)
        return;
    // 负数询问，否则偶数插入奇数删除
    vector<int> P , Q;
    int r = A.size() , mid = r / 2;
    for (int i = 0 ; i < mid ; ++ i)
        P.push_back(A[i]);
    divide(P);
    P.clear();
    for (int i = 0 ; i < r ; ++ i)
        if (A[i] > 0 && (A[i] & 1))
            del[A[i] >> 1] = 1;
    for (int i = 0 ; i < mid ; ++ i)
        if (A[i] > 0 && (~A[i] & 1)) {
            if (!del[A[i] >> 1])
                P.push_back(A[i] >> 1);
            else
                del[A[i] >> 1] = 2;
        }
    for (int i = mid ; i < r ; ++ i)
        if (A[i] < 0)
            Q.push_back(-A[i]);
    update(P , Q);
    Q.clear();
    int c1 = 0 , c2 = 0;
    for (int i = r - 1 ; i >= mid ; -- i) {
        if (A[i] > 0 && (A[i] & 1) && del[A[i] >> 1] == 2) {
            Q.push_back(A[i] ^ 1);
            ++ c1;
        } else if (A[i] < 0) {
            Q.push_back(A[i]);
            ++ c2;
        }
    }
    for (int i = 0 ; i < r ; ++ i)
        if (A[i] > 0 && (A[i] & 1))
            del[A[i] >> 1] = 0;
    if (c1 && c2)
        divide(Q);
    P.clear();
    for (int i = mid ; i < r ; ++ i)
        P.push_back(A[i]);
    divide(P);
}
