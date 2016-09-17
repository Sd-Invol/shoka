struct Treap {
    int nodecnt;
    int L[N] , R[N] , cnt[N];
    int key[N];
    int Min[N] , add[N] , rev[N];
    bool hey(int A , int B) {
        return rand() % (cnt[A] + cnt[B]) < cnt[A];
    }
    int newnode(int val) {
        ++ nodecnt , L[nodecnt] = R[nodecnt] = 0;
        cnt[nodecnt] = 1 , Min[nodecnt] = key[nodecnt] = val;
        rev[nodecnt] = add[nodecnt] = 0;
        return nodecnt;
    }
    void pushup(int x) {
        cnt[x] = 1 , Min[x] = key[x];
        if (L[x]) cnt[x] += cnt[L[x]] , Min[x] = min(Min[x] , Min[L[x]]);
        if (R[x]) cnt[x] += cnt[R[x]] , Min[x] = min(Min[x] , Min[R[x]]);
    }
    void pushdown(int x) {
        if (rev[x]) {
            if (L[x]) rev[L[x]] ^= 1 , swap(L[L[x]] , R[L[x]]);
            if (R[x]) rev[R[x]] ^= 1 , swap(L[R[x]] , R[R[x]]);
            rev[x] = 0;
        }
        if (add[x]) {
            if (L[x]) add[L[x]] += add[x] , Min[L[x]] += add[x] , key[L[x]] += add[x];
            if (R[x]) add[R[x]] += add[x] , Min[R[x]] += add[x] , key[R[x]] += add[x];;
            add[x] = 0;
        }
    }
    void merge(int& p , int x , int y) {
        if (!x || !y)
            p = x | y;
        else if ( hey(x , y) ) // key[x] < key[y]
            pushdown(x) , merge(R[x] , R[x] , y) , pushup(p = x);
        else
            pushdown(y) , merge(L[y] , x , L[y]) , pushup(p = y);
    }
    void split(int p , int& x , int& y , int size) {
        if (!size) {
            x = 0 , y = p;
            return;
        }   pushdown(p);
        if (cnt[L[p]] >= size)
            y = p , split(L[p] , x , L[y] , size) , pushup(y);
        else
            x = p , split(R[p] , R[x] , y , size - cnt[L[p]] - 1) , pushup(x);
    }
};
