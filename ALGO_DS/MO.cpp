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
const int lmt = 2100005;

int cnt[lmt];
int L[100005];
ll output[100005];
int k;
int buck = sqrt(100000);
struct node {
    int l, r, id;
    node(int a, int b, int c) {
        l = a;
        r = b;
        id = c;
    }
};

bool cmp(const node &a, const node &b) {
    if((a.l/buck) != (b.l/buck))
        return (a.l/buck) < (b.l/buck);
    return ((a.r/buck) < (b.r/buck));
}

vector<node> query;

ll ans = 0;

void add(int idx) {
	ans += cnt[k^L[idx]];
	cnt[L[idx]]++;
}

void remove(int idx) {
	cnt[L[idx]]--;
	ans -= cnt[k^L[idx]];
}

int main(){
	int n, m;
	S2(n, m);
	S(k);
	L[0] = 0;
	for(int i = 1; i <= n; i++) {
		int x;
		S(x);
		L[i] = x ^ L[i-1];
	}

	for(int i = 0; i < m; i++) {
		int l, r;
		S2(l, r);
		query.pb(node(l, r, i));
	}

	sort(query.begin(), query.end(), cmp);
	int _l = 0, _r = 0;
	add(0);
	for(int i = 0; i < m; i++) {
        int L = query[i].l - 1, R = query[i].r;
        while(_l < L) {
            remove(_l);
            _l++;
        }
        while(_l > L) {
            _l--;
            add(_l);
        }
        while(_r < R) {
            _r++;
            add(_r);
        }
        while(_r > R) {
            remove(_r);
            _r--;
        }
        output[query[i].id] = ans;
    }
    for(int i = 0; i < m; i++)
    	printf("%lld\n", output[i]);
    return 0;
}