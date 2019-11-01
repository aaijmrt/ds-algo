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

vector<pair<ll, ll> > A, B;

ll cross(pair<ll, ll> A, pair<ll, ll> B, pair<ll, ll> C){
    pair<ll, ll> AB, AC;
    AB.X = B.X - A.X;
    AB.Y = B.Y - A.Y;
    AC.X = C.X - A.X;
    AC.Y = C.Y - A.Y;
    ll cross = AB.X * AC.Y - AB.Y * AC.X;
    return abs(cross);
}

bool check(pair<ll, ll> a1, pair<ll, ll> a2, pair<ll, ll> b){
	ll x1 = a2.X - a1.X;
	ll y1 = a2.Y - a1.Y;
	ll x2 = b.X - a1.X;
	ll y2 = b.Y - a1.Y;
	if(y2*x1 >= y1*x2)
		return true;
	return false;
}

int main(){
	// freopen("inp.txt", "r", stdin);
	int n;
	S(n);
	for(int i = 0; i < n; i++) {
		ll x, y;
		SL(x);
		SL(y);
		A.pb(mp(x, y));
	}
	int m;
	S(m);
	for(int i = 0; i < m; i++) {
		ll x, y;
		SL(x);
		SL(y);
		B.pb(mp(x, y));
	}

	for(int i = 0; i < m; i++) {
		int lo = 0, hi = n-1;
		while(lo < hi) {
			int mid = (lo + hi) / 2;
			if(check(A[0], A[mid], B[i]))
				hi = mid;
			else
				lo = mid+1;
			// deb2(hi, lo);
		}
		// deb3(B[i].X, B[i].Y, hi);
		if(hi < 2) {
			printf("NO\n");
			return 0;
		}
		ll area = cross(A[0], A[hi-1], A[hi]);
		ll area1 = cross(B[i], A[hi-1], A[hi]), area2 = cross(A[0], B[i], A[hi]), area3 = cross(A[0], A[hi-1], B[i]);
		// deb(area);
		// deb3(area1, area2, area3);
		if((area1 == 0) && ((B[i] != A[hi]) || (B[i] != A[hi-1]))) {
			printf("NO\n");
			return 0;
		}
		if((area2 == 0) && ((B[i] != A[0]) || (B[i] != A[hi])) && (hi == (n-1))) {
			printf("NO\n");
			return 0;
		}
		if((area3 == 0) && ((B[i] != A[0]) || (B[i] != A[hi-1])) && (hi == 2)) {
			printf("NO\n");
			return 0;
		}

		if(area != (area1 + area2 + area3)) {
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");

    return 0;
}