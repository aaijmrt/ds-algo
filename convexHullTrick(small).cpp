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

//solves for y = min(m[i]*x + c[i]);;

ll a[lmt], b[lmt], dp[lmt];

int pointer; 
vector<long long> M; 
vector<long long> B;

bool bad(int l1, int l2, int l3) {
	if(M[l1] == M[l3]) return false;
	if(M[l1] == M[l2]) return false;
    return (B[l3]-B[l1]) / (M[l1]-M[l3]) < (B[l2]-B[l1]) / (M[l1]-M[l2]);
}

void add(long long m, long long b) {
    M.push_back(m);
    B.push_back(b);
    while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1)) {
        M.erase(M.end()-2);
        B.erase(B.end()-2);
    }
}

long long query(long long x) {
    if (pointer>=M.size())
        pointer=M.size()-1;
    while ((pointer<M.size()-1)&&(M[pointer+1]*x+B[pointer+1])<(M[pointer]*x+B[pointer])) // change '<' to '>' for max
        pointer++;
    return M[pointer]*x+B[pointer];
}


int main(){
	int n;
	S(n);
	for(int i = 0; i < n; i++) SL(a[i]);
	for(int i = 0; i < n; i++) SL(b[i]);

	dp[0] = 0LL;
	add(b[0], 0);
	pointer=0;

	for(int i = 1; i < n; i++) {
		dp[i] = query(a[i]);
		add(b[i], dp[i]);
	}	
	printf("%lld\n", dp[n-1]);
    return 0;
}