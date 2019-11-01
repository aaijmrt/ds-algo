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
const int lmt = 100005;

ll a[lmt];

ll fun(ll start, int n, ll l) {
	ll ans = 0;

	for(int i = 0; i < n; i++) {
		ll val = start + l*(long long)i;
		ans += abs(val-a[i]);
	}

	return ans;
}

int main(){
	int t;
	S(t);
	while(t--) {
		int n;
		S(n);
		ll l, A, B;
		scanf("%lld %lld %lld", &l, &A, &B);

		for(int i = 0; i < n; i++) 
			SL(a[i]);

		sort(a, a+n);

		ll lo = A, hi = B-l*(long long)n;

		while(lo < hi) {
		    ll mid = (lo + hi) >> 1;
		    if(fun(mid, n, l) < fun(mid+1, n, l)) {
		        hi = mid;
		    }
		    else {
		        lo = mid+1;
		    }
		}
		ll ans = fun(lo, n, l);
		printf("%lld\n", ans);
	}
    return 0;
}