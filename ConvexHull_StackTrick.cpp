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
#define PI acos(-1)

const int N = 200005;
int n;
struct point{
  long long x , y;
  point(long long _x = 0 , long long _y = 0){
    x = _x;
    y = _y;
  }
  point operator - (const point &o) const {
    return point(x - o.x , y - o.y);
  }
};
long long cross(point a , point b){
  return a.x * b.y - a.y * b.x;
}
bool convex(point a , point b , point c){
  return cross(b - a , c - a) <= 0;
}

point arr[N], brr[N];
int stk[N];
int sz;
point lft[N], rgt[N];

int main(){
  scanf("%d" , &n);
  for(int i = 1 ; i <= n ; ++i){
    scanf("%lld %lld" , &arr[i].x , &arr[i].y);
  }
  for(int i = n ; i > 0 ; --i){
    brr[i] = arr[n-i+1];
  }
  stk[sz = 1] = n;
  for(int i = n - 1 ; i >= 1 ; --i){
    while(sz >= 2 && !convex(arr[i] , arr[stk[sz]] , arr[stk[sz - 1]])){
      --sz;
    }
    rgt[i] = arr[stk[sz]];
    stk[++sz] = i;
  }
  memset(stk, 0, sizeof(stk));
  stk[sz = 1] = n;
  for(int i = n - 1 ; i >= 1 ; --i){
    while(sz >= 2 && convex(brr[i] , brr[stk[sz]] , brr[stk[sz - 1]])){
      --sz;
    }
    lft[n-i+1] = brr[stk[sz]];
    stk[++sz] = i;
  }
}