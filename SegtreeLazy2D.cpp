#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long int llu;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define mem(a, v) memset(a, v, sizeof(a))
#define PI acos(-1)
#define S(a) scanf("%d",&a)
#define SL(a) scanf("%lld",&a)
#define S2(a, b) scanf("%d%d",&a,&b)
#define nl printf("\n")
#define deb(x) cout<<#x<<" : "<<x<<endl;
#define deb2(x, y) cout<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<endl;
#define deb3(x, y, z) cout<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<" | "<<#z<<" : "<<z<<endl;
#define debv(x) {cout<<#x<<" : "<<endl; for(int ii =0; ii < x.size(); ii++) cout<<x[ii]<<" "; cout<<endl; }
#define debarr(x, xs) {cout<<#x<<" : "<<endl; for(int ii =0; ii < xs; ii++) cout<<x[ii]<<" "; cout<<endl; }
//auto T=clock(); 
//cout<<double(clock()-T)/CLOCKS_PER_SEC<<'\n';
const ll mod = 1000000007LL;
const int lmt = 100005;

struct node {
    int sum, lazy, len;
    node(){
        sum = lazy = len = 0;
    }
    node(int a, int b) {
        sum = a;
        len = b;
        lazy = 0;
    }
};

node tree[21][4*lmt];
int a[lmt];

node merge(node a, node b) {
    node ret = node(a.sum+b.sum, a.len+b.len);
    return ret;
}

void build(int idx, int bit, int A, int B) {
    if(A == B) {
        int tmp = 0;
        if((1<<bit)&a[A])
            tmp = 1;
        tree[bit][idx] = node(tmp, 1);
        return ;
    }
    int M = (A + B)/2;
    build(2*idx+1, bit, A, M);
    build(2*idx+2, bit, M+1, B);
    tree[bit][idx] = merge(tree[bit][2*idx+1], tree[bit][2*idx+2]);
}

void lazyUpdate(int idx, int bit, int A, int B) {
    if(tree[bit][idx].lazy > 0) {
        tree[bit][idx].sum = tree[bit][idx].len - tree[bit][idx].sum;
        if(A != B) {
            tree[bit][2*idx+1].lazy = 1 - tree[bit][2*idx+1].lazy;
            tree[bit][2*idx+2].lazy = 1 - tree[bit][2*idx+2].lazy;
        }
        tree[bit][idx].lazy = 0;
    }
}

node query(int idx, int bit, int l, int r, int A, int B) {
    lazyUpdate(idx, bit, A, B);
    int M = (A + B)/2;
    if((l == A) && (r == B))
        return tree[bit][idx];
    if(r <= M)
        return query(2*idx+1, bit, l, r, A, M);
    else if(l >  M)
        return query(2*idx+2, bit, l, r, M+1, B);
    else
        return merge(query(2*idx+1, bit, l, M, A, M), query(2*idx+2, bit, M+1, r, M+1, B));
}

void update(int idx, int bit, int l, int r, int A, int B) {
    lazyUpdate(idx, bit, A, B);
    if((l == A) && (r == B)) {
        tree[bit][idx].sum = tree[bit][idx].len - tree[bit][idx].sum;
        if(A != B) {
            tree[bit][2*idx+1].lazy = 1 - tree[bit][2*idx+1].lazy;
            tree[bit][2*idx+2].lazy = 1 - tree[bit][2*idx+2].lazy;
        }
        return ;
    }
    int M = (A + B)/2;
    if(r <= M)
        update(2*idx+1, bit, l, r, A, M);
    else if(l > M)
        update(2*idx+2, bit, l, r, M+1, B);
    else {
        update(2*idx+1, bit, l, M, A, M);
        update(2*idx+2, bit, M+1, r, M+1, B);
    }
    lazyUpdate(2*idx+1, bit, A, M);
    lazyUpdate(2*idx+2, bit, M+1, B);
    tree[bit][idx] = merge(tree[bit][2*idx+1], tree[bit][2*idx+2]);
}

int main(){
    int n;
    S(n);
    for(int i = 0; i < n; i++)
        S(a[i]);
    for(int i = 0; i <= 20; i++)
        build(0, i, 0, n-1);
    int m;
    S(m);
    while(m--) {
        int ty;
        S(ty);
        if(ty == 1) {
            int l, r;
            S2(l, r);
            ll ans = 0;
            for(int i = 0; i <= 20; i++)
                ans += ((ll)(1LL<<i) * (ll)query(0, i, l-1, r-1, 0, n-1).sum);
            printf("%lld\n", ans);
        }
        else {
            int l, r, val;
            S2(l, r);
            S(val);
            for(int i = 0; i <= 20; i++) {
                if((1<<i) & val)
                    update(0, i, l-1, r-1, 0, n-1);
            }
        }
    }
    return 0;
}