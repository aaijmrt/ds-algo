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
//cout << fixed << setprecision(10) << f(0, 0, 0) << "\n";
const ll mod = 1000000007LL;
const int lmt = 1000005;

struct data {
	int a, b; ll h;
	data(int x, int y, ll z) {
		a = x;
		b = y;
		h = z;
	}
};

vector<data> v;
set<ll> st;
map<int, int> M;

bool cmp(data a, data b) {
	if(a.b != b.b) 
		return a.b < b.b;
	return a.a < b.a;
}

ll tree[2000005];

ll query(int idx, int l, int r, int A, int B) {
    int mid = (A + B)/2;
    if((l == A) && (r == B))
        return tree[idx];
    if(r <= mid)
        return query(2*idx+1, l, r, A, mid);
    else if(l > mid)
        return query(2*idx+2, l, r, mid+1, B);
    else
        return max(query(2*idx+1, l, mid, A, mid), query(2*idx+2, mid+1, r, mid+1, B));
}

void update(int idx, int pos, ll val, int A, int B) {
    if(B == A) {
    	tree[idx] = val;
        return ;
    }
    int mid = (A + B)/2;
    if(pos <= mid)
        update(2*idx+1, pos, val, A, mid);
    else if(pos > mid)
        update(2*idx+2, pos, val, mid+1, B);
    tree[idx] = max(tree[2*idx+1], tree[2*idx+2]);
}

int main(){
	int n;
	S(n);
	for(int i = 0; i < n; i++) {
		int a, b, h;
		S2(a, b);
		S(h);
		st.insert(a);
		st.insert(a+1);
		st.insert(b);
		v.pb(data(a, b, h));
	}

	sort(v.begin(), v.end(), cmp);
	int cnt = 0;

	for(auto it = st.begin(); it != st.end(); it++) {
		M[*it] = cnt;
		cnt++;

	}

	ll ans = 0;

	for(int i = 0; i < n; i++) {
		int a = v[i].a;
		int b = v[i].b;

		ll val = query(0, M[a+1], M[b], 0, cnt-1);

		ans = max(ans, val+v[i].h);
		
		update(0, M[b], val+v[i].h, 0, cnt-1);

	}

	printf("%lld\n", ans);

    return 0;
}