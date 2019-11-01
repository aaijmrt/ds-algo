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

int P[lmt], R[lmt];

void CreateSet(int n) { 
	for(int i = 0; i <= n; i++) {
 		P[i] = i;
 		P[i] = i;
 		R[i] = 0;
 	}
}

int Find(int x) {
 	if(x != P[x]) P[x] = Find(P[x]);
	return P[x];
}

void Merge(int x, int y) {
	int px = Find(x);
 	int py = Find(y);
 	if(R[px] > R[py]) P[py] = px;
 	else P[px] = py;
	if(R[px] == R[py]) R[py] = R[py] + 1;
}

int main(){

    return 0;
}