template<typename T1 , typename T2> struct hashmap {
    const static int MOD = 99991;
    const static int Size = 500005;
    int pre[MOD] , mcnt;
    struct node {
        T1 key;
        T2 val ;
        int next;
    } e[Size];
    void clear() {
        memset(pre , -1 , sizeof(pre));
        mcnt = 0;
    }
    void insert(const T1& K , const T2& V) {
        int x = K % MOD;
        e[mcnt] = (node) {K , V , pre[x]};
        pre[x] = mcnt ++;
    }
    int find(const T1 &K) {
        int x = K % MOD;
        for (int i = pre[x] ; ~i ; i = e[i].next)
            if (e[i].key == K)
                return i;
        return -1;
    }
    T2& operator [] (const T1 &x){  
        int i = find(x);  
        if (!~i){  
            insert(x , 0);  
            return e[mcnt - 1].val;  
        }  
        return e[i].val;  
    }      
};
struct hash_func {  
    size_t operator() (const Matrix &p) const {  
        return p[0][0] * 2333333 ^ p[0][1] * (145777 ^ p[1][1]);
    }  
};
unordered_map<Matrix , int , hash_func>  
