int MinR(char *str) {
    int i = 0 , j = 1 , k = 0 , len = strlen(str);
    while (i < len && j < len && k < len) {
        int cmp = str[(j + k) % len] - str[(i + k) % len];
        if (!cmp)
            ++ k;
        else {
            if (cmp > 0)
                j += k + 1;
            else i += k + 1;
            if (i == j) ++ j;
            k = 0;
        }
    }
    return min(i , j);
}
