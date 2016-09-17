inline LL mod_mul(LL a , LL b , LL Q){
    return (a * b - (LL)((long double)a * b / Q) * Q) % Q;
}
inline LL myrand() {
    return rand() << 30 | rand();
}
LL mod_exp(LL a , LL x , LL n) {
    LL ret = 1;
    while(x) {
        if(x & 1)
            ret = mod_mul(ret , a , n);
        a = mod_mul(a , a , n) , x >>= 1;
    }
    return ret;
}
bool Rabin_Miller(LL n) { //素性测试
    LL k = 0 , i , j , m , a;
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (~n & 1) return 0;
    m = n - 1;
    while(~m & 1)
        m >>= 1 , ++ k;
    for(i = 0 ; i < 20; ++ i) {
        a = myrand() % (n - 2) + 2;
        a = mod_exp(a , m , n);
        if (a == 1)
            continue;
        for (j = 0 ; j < k ; ++ j) {
            if (a == n - 1)
                break;
            a = mod_mul(a , a , n);
        }
        if (j < k)
            continue;
        return 0;
    }
    return 1;
}
inline LL func(LL x , LL n) {
    return (mod_mul(x , x , n) + 1) % n;
}
LL Pollard(LL n) { //启发式分解
    LL i , x , y , p;
    if (Rabin_Miller(n))
        return n;
    if(~n & 1)
        return 2;
    for(i = 1 ; i < 20 ; ++ i) {
        x = i;
        y = func(x , n);
        p = __gcd(y - x , n);
        while(p == 1) {
            x = func(x , n);
            y = func(func(y , n) , n);
            p = __gcd((y - x + n) % n , n) % n;
        }
        if(p == 0 || p == n)
            continue;
        return p;
    }
}
void factor(LL n , vector<int>& ans) {
    LL x = Pollard(n);
    if(x == n) {
        ans.push_back(x);
        return;
    }
    factor(x , ans);
    factor(n / x , ans);
}
