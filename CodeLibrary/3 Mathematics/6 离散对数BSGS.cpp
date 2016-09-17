//S * P^k = T , m = sqrt(S) , I = P ^-1
map<unsigned int , int> hash;
unsigned int E = S;
for (i = 0 ; i < m ; ++ i) {
    if (E == T) {
        printf("%u\n" , i);
        return;
    }
    if (!hash.count(E))
        hash[E] = i;
    E = E * P;
}
for (i = 1 ; i < m ; ++ i) {
    T = T * I;
    if (hash.count(T)) {
        printf("%u\n" , i * m + hash[T]);
        return;
    }
}
puts("poor sisyphus");
