f[0] = m;  
for (int i = 1 , k = 0 ; i < m ; ++ i) {
    int len = k + f[k], l = f[i - k];
    if (i > 1 && l < len - i)
        f[i] = l;
    else {
        int j = i > 1 ? max(0 , len - i) : 0;
        while(i + j < m && t[j] == t[i + j])
            ++ j;
        f[i] = j , k = i;
    }
}
for (int i = 0 , k = 0 ; i < n ; ++ i) {
    int len = k + L[k] , l = f[i - k];
    if (i > 0 && l < len - i)
        L[i] = l;
    else {
        int j = i > 0 ? max(0 , len - i) : 0;
        while (j < m && t[j] == s[(i + j) % n])
            ++ j;
        L[i] = j , k = i;
    }
}    
