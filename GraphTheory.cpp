#include <bits/stdc++.h>
using namespace std;
int dis [2000+5]; //distance array
bool vis[2000+5]; //visited array
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
vector<int> AdjList[100000+5];
vector<int> ToboSort;//topological sort vector
int n,e,u,v; //n is nodes //e is edges //u is perent //v is child
int shortestPath[100000+5];//shortest path array
bool relaxed[100000+5];//relaxed array
vector<pair<int,int>> djiAdjList[100000+5];//djikstra graph
int shortest,minDis;//shortest child,minimum distance
int CC=0;
void CreatingAdjListGraph(){
		cin>>n>>e;
		for(int i=0;i<e;++i){
			cin>>u>>v;
			AdjList[u].push_back(v);
			//AdjList[v].push_back(u); //undirected graph
		}
}
void PreGraph(int n=0){	//Graph preparation
	//memset(dis,-1,sizeof(dis));  //BFS distance array preparation
	//memset(vis,0,sizeof(vis));	//DFS visited array preparation
	// memset(relaxed, 0, sizeof(relaxed)); //djikstra relaxed array preparation
	// fill(shortestPath,shortestPath+n, 1e9);	//djikstra shortestPath array preparation
}
void djikstra_k(int root){ //O(nlogn) cuz of priority_queue
	priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	shortestPath[root]=0;
	relaxed[root]=1;
	for(auto v:djiAdjList[root]){
		shortestPath[v.first]=v.second;
		pq.push({v.second,v.first});
	}
	while(!pq.empty()){
		minDis=pq.top().first,shortest=pq.top().second;
		pq.pop();
		if(!relaxed[shortest]){
			relaxed[shortest]=1;
			for(auto v:djiAdjList[shortest]){
				if(shortestPath[v.first]>shortestPath[shortest]+v.second){
					shortestPath[v.first]=v.second;
					pq.push({v.second,v.first});
				}
			}
		}
	}
}
void dijkstra(int root){
	priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	fill(shortestPath,shortestPath+n, 1e9);
	shortestPath[root]=0;
	pq.push({0,root});
	while(!pq.empty()){
		minDis=pq.top().first,shortest=pq.top().second;
		pq.pop();
		if(minDis>shortestPath[shortest])continue;
		for(auto v:djiAdjList[shortest]){
			if(shortestPath[v.first]>shortestPath[shortest]+v.second){
				shortestPath[v.first]=shortestPath[shortest]+v.second;
				pq.push({shortestPath[v.first],v.first});
			}
		}
	}
}
void DFSRec(int root){	//Recursive
		vis[root]=1;
		for(auto v:AdjList[root]){
			if(!vis[v]) DFSRec(v);
		}
		//ToboSort.push_back(root); //topological sort
}
void DFSItr(int root){	//Iterative
		stack<int> stk;
		stk.push(root);
		vis[root]=1;
		while(!stk.empty()){
			u=stk.top();
			stk.pop();
			for(auto v:AdjList[u]){
				if(!vis[v]){
					stk.push(v);
					vis[v]=1;
				}
			}
		}
}
void DFS2D(int stx , int sty) {
	vis[stx][sty] = 1;
	for(int i = 0; i < 4; ++i) {
		int nx = stx + dx[i] , ny = sty + dy[i];
		if(!vis[nx][ny] && valid(nx , ny))
			DFS(nx , ny);
	}
}
int Connectedcomponents(){  //counting number of connectedcomponents
	for(int i=1;i<=n;++i){
    if(!vis[i]){
      DFSItr(i);
      CC++;
    }
  }
  return CC;
}
void BFS(int root){
    queue<int> qu;
    qu.push(root);
    dis[root]=0;
    while(!qu.empty()){
        u=qu.front();
        qu.pop();
        for(auto v:AdjList[u]){
            if(dis[v]==-1){
                dis[v]=dis[u]+1;
                qu.push(v);
            }
        }
    }
}
bool bipartite(int s, int c = 0){
	queue<int> q;
	int u, v;
	color[s] = c;
	q.push(s);
	while(!q.empty()){
		u = q.front();
		q.pop();
		for(int i = 0; i < adj[u].size(); i++){
			v = adj[u][i];
			if(color[v] == -1){
				color[v] = 1 - color[u];
				q.push(v);
			}
			else {
				if (color[v] != 1-color[u])return 0;
			}
		}
	}
	return 1;
 
}
int main(){
		CreatingAdjListGraph();
 		BFS(0);
}

//-------- DSU ----------

int parent[100005], height[100005], forests;
void Init(int n){
	for(int i = 0; i < n; i++){
		parent[i] = i;
		height[i] = 0;
	}
	 forests = n; 
}
int find_set(int x){
	if (parent[x] == x)return x;
	return parent[x] = find_set(parent[x]);
}
void link(int x, int y){
	if(height[x] > height[y])swap(x,y);
	parent[x] = y;
	if(height[x] == height[y])height[y]++;
}
bool union_sets(int x, int y){
	int u = find_set(x), v = find_set(y);
	if (u != y){
		link(x,y);
		forests--;
	}
	return x != y;
}
int kruskal() {
	int n, m, cost = 0, u, v, c;
	vector<pair<int, pair<int,int> > > edges;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> u >> v >> c;
		edges.push_back({c,{u,v}});
	}
	Init(n);
	sort(edges.begin(), edges.end());
	for (auto p : edges){
		if (forests == 1)break;
		if (union_sets(p.second.first,p.second.second))cost += p.first;
	}
	return cost;
}
