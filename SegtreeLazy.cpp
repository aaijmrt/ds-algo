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
const int lmt = 1000005;

struct node {
    int num4, num7, num47, num74, lazy;
    node(){
        num4 = num7 = num47 = num74 = lazy = 0;
    }
    node(int a, int b, int c, int d) {
        num4 = a;
        num7 = b;
        num47 = c;
        num74 = d;
        lazy = 0;
    }
};

node tree[4*lmt];
char s[lmt];

node merge(node a, node b) {
    int ans = max(a.num47 + b.num7, a.num4 + b.num47);
    int ans1 = max(a.num74 + b.num4, a.num7 + b.num74);
    node ret = node(a.num4 + b.num4, a.num7 + b.num7, ans, ans1);
    return ret;
}

void build(int idx, int A, int B) {
    if(A == B) {
        if(s[A] == '4')
            tree[idx].num4 = 1;
        else
            tree[idx].num7 = 1;
        tree[idx].num47 = 1;
        tree[idx].num74 = 1;
        return ;
    }
    int M = (A + B)/2;
    build(2*idx+1, A, M);
    build(2*idx+2, M+1, B);
    tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
}

void lazyUpdate(int idx, int A, int B) {
    if(tree[idx].lazy > 0) {
        swap(tree[idx].num47, tree[idx].num74);
        swap(tree[idx].num4, tree[idx].num7);
        if(A != B) {
            tree[2*idx+1].lazy = 1 - tree[2*idx+1].lazy;
            tree[2*idx+2].lazy = 1 - tree[2*idx+2].lazy;
        }
        tree[idx].lazy = 0;
    }
}

node query(int idx, int l, int r, int A, int B) {
    lazyUpdate(idx, A, B);
    int M = (A + B)/2;
    if((l == A) && (r == B))
        return tree[idx];
    if(r <= M)
        return query(2*idx+1, l, r, A, M);
    else if(l >  M)
        return query(2*idx+2, l, r, M+1, B);
    else
        return merge(query(2*idx+1, l, M, A, M), query(2*idx+2, M+1, r, M+1, B));
}

void update(int idx, int l, int r, int A, int B) {
    lazyUpdate(idx, A, B);
    if((l == A) && (r == B)) {
        swap(tree[idx].num47, tree[idx].num74);
        swap(tree[idx].num4, tree[idx].num7);
        if(A != B) {
            tree[2*idx+1].lazy = 1 - tree[2*idx+1].lazy;
            tree[2*idx+2].lazy = 1 - tree[2*idx+2].lazy;
        }
        return ;
    }
    int M = (A + B)/2;
    if(r <= M)
        update(2*idx+1, l, r, A, M);
    else if(l > M)
        update(2*idx+2, l, r, M+1, B);
    else {
        update(2*idx+1, l, M, A, M);
        update(2*idx+2, M+1, r, M+1, B);
    }
    lazyUpdate(2*idx+1, A, M);
    lazyUpdate(2*idx+2, M+1, B);
    tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
}

int main(){
    int n, m;
    S2(n, m);
    scanf("%s",s);
    build(0, 0, n-1);
    while(m--) {
        char ty[10];
        scanf("%s",ty);
        if(strcmp(ty, "count") == 0) {
            printf("%d\n", query(0, 0, n-1, 0, n-1).num47);
        }
        else {
            int l, r;
            S2(l, r);
            update(0, l-1, r-1, 0, n-1);
        }
    }
    return 0;
}