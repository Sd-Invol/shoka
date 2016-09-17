s[0] = '%';  
for (int i = 0 ; str[i] ; ++ i) {
    s[len ++] = '#';
    s[len ++] = str[i];
    s[len ++] = '#';
}s[len] = 0;
int id = 0 , mx = 0;  
for (int i = 0 ; i < len ; ++ i) {  
    p[i] = mx > i ? min(p[id + id - i], mx - i) : 1;  
    while (s[i + p[i]] == s[i - p[i]]) ++ p[i];  
    if (i + p[i] > mx)
        mx = i + p[i] , id = i;  
}
