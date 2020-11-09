#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
const int N = 1e5 + 7;
int n , m ;
int dis[N] ;
struct Edge{
    int from , to , cost ;
};
Edge edges[N] ;
// return false if there is a negative cycle
// overall O (V * E)
bool bellman(int src){
    memset(dis , '?' , (n +1) * sizeof(dis[0])) ;   // 0x3f3f3f3f
    dis[src] = 0 ;
    int nn = n ;
    while(nn--){   //  (O (V))
        for(int e = 0 ; e < m ; ++e){       // process edges    // O(E)
            const auto &p = edges[e] ;
            int newdis = dis[p.from] + p.cost ;
            if(dis[p.to] > newdis){         // relaxation
                if(!nn)
                    return 0 ;
                dis[p.to] = newdis ;
            }
        }
    }
    return  1 ;
}
int main() {
    cin >> n >> m ;
    for(int i = 0 ; i < m ; ++i){
        int u , v , cst ;
        cin >> u >> v >> cst  ;
        edges[i] = {u , v , cst};
    }
    if(!bellman(0)){
        cout << "Negative Cycle" ;
    }
    else{
        for(int i = 0 ; i < n ; ++i){
            cout << i << ' ' << dis[i] << "\n" ;
        }
    }
 
}
