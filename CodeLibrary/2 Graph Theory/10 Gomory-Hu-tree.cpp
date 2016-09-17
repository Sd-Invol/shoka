void divide(int l , int r) {
    if (l == r) return;
    random_shuffle(a + l , a + r + 1);
    for (int i = 0 ; i < mcnt ; i += 2)
        e[i].f = e[i ^ 1].f = (e[i].f + e[i ^ 1].f) / 2;
    s = a[l] , t = a[r];
    E[m ++] = (edge) {s , t , -dinic()};
    int ns = 0 , nt = 0;
    for (int i = l ; i <= r ; ++ i)
        if (!~d[a[i]])
            T[nt ++] = a[i];
        else
            S[ns ++] = a[i];
    for (int i = 0 ; i < ns ; ++ i)
        a[l + i] = S[i];
    for (int i = 0 ; i < nt ; ++ i)
        a[l + ns + i] = T[i];
    divide(l , l + ns - 1);
    divide(l + ns , r);
}
