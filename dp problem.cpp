#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#include<map>
#include<iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#define forr(i,a,b) for(int i=a;i<=b;i++)
#define F first
#define S second
#define input ios_base::sync_with_stdio(0);cin.tie(0);
 
const double PI  = acos(-1.0);
using namespace std;
typedef long long  ll;
typedef pair<ll, ll>pii;
const double EPS = 1e-9;
const int N = 100 + 9;
ll n,c,w[N],v[N],mem[N][100009];
 
ll dp(int i,int cur)
{
    if(i > n) return 0;
    ll&ret = mem[i][cur];
    if(ret != -1) return ret;
 
    ll c1=0,c2=0;
    c1 = dp(i+1, cur);
    if(w[i] <= cur) c2 = v[i] + dp(i+1, cur - w[i]);
 
    return ret = max(c1,c2);
}
 
 
 int main()
{
//freopen("calc.in","r",stdin);
//freopen("calc.out","w",stdout);
//__builtin_popcount()
input
        cin>>n>>c;
        for(int i=1;i<=n;i++)
            cin>>w[i]>>v[i];
 
        memset(mem,-1,sizeof mem);
        cout<<dp(1,c)<<endl;
 
return 0;
}
