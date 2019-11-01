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

ll gcd ( ll a, ll b, ll & x, ll & y ) {
	if ( a == 0 ) {
		x = 0 ; y = 1 ;
		return b ;
	}
	ll x1, y1 ;
	ll d = gcd ( b % a, a, x1, y1 ) ;
	x = y1 - ( b / a ) * x1 ;
	y = x1 ;
	return d ;
}

bool find_any_solution (ll a, ll b, ll c, ll & x0, ll & y0, ll & g) {
	g = gcd (abs(a), abs(b), x0, y0);
	if ((c % g) != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)   x0 *= -1;
	if (b < 0)   y0 *= -1;
	return true;
}

int main(){
	ll a, b;
	SL(a);
	SL(b);
	if((a == 1) || (b == 1)) {
		ll ans = max(a, b);
		ans = min(2LL, ans);
	 	printf("%lld\n", ans);
	 	return 0;
	}
	ll gcd = __gcd(a, b);
	if(gcd > 1) {
		ll ans = a*b;
		ans /= gcd;
		printf("%lld\n", ans);
		return 0;
	}
	ll x, y, g;
	find_any_solution(a, b, 1LL, x, y, g);	
	ll ans = max(abs(a*x), abs(b*y));
	ll tmp = a*b;
	tmp /= gcd;
	ans = min(ans, tmp);
	printf("%lld\n", ans);
    return 0;
}