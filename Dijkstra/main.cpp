#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_SIZE = 100001;
int n,m,s;
vector<pair<int,int>> adj[MAX_SIZE]; //adjacency list: node -> vector of (neighbor, weight)

void input(){
    cin >> n >> m >> s;
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        //adj[v].push_back({u,w});  Assuming it's an undirected graph. Remove this line if it's directed.
    }
}


const int INF = 1e9;
void dijkstra(int start){
    //initialize distance vector
    vector<long long> d(n + 1, INF);
    d[start] = 0;
    //priority_queue<T, Container, Compare>
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int ,int>>> Q;
    //{current shortest distance, node}
    Q.push({0, start});

    while(!Q.empty()){
        //from priority queue pick the pair with the smallest distance
        pair<int,int> top = Q.top(); Q.pop();
        int u = top.second;
        int dist = top.first;
        if(dist > d[u]) continue; //if the distance is greater than the current distance, skip
        //relaxation: from adjacent list find the adjacent nodes and update their distances
        for( auto it : adj[u]){
            int v = it.first;
            int weight = it.second;
            if(d[u] + weight < d[v]){
                d[v] = d[u] + weight;
                Q.push({d[v], v});
            }
        }
    }
    for(int i=1; i<=n; i++){
        if(d[i] == INF) cout << "INF\n";
        else cout << d[i] << "\n";
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    input();
    dijkstra(s); // Assuming we want to find shortest paths from node 1
    return 0;
}