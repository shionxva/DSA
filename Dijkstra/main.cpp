#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100001;
map<char, vector<pair<char,int>>> adj; //adjacency list: node -> vector of (neighbor, weight)
const int INF = 1e9;

pair<map<char, char>, map<char, long long>> dijkstra(char start, map<char, vector<pair<char,int>>> adj, map<char, int> wait_times){
    map<char, char> previous;
    //initialize distance vector
    map<char, long long> d;
    for(auto& x : adj){
        d[x.first] = INF;
        previous[x.first] = ' ';
    }
    d[start] = 0;
    previous[start] = start;
    //priority_queue<T, Container, Compare>
    priority_queue<pair<long long, char>, vector<pair<long long, char>>, greater<pair<long long, char>>> Q;
    //{current shortest distance, node}
    Q.push({0, start});

    while(!Q.empty()){
        //from priority queue pick the pair with the smallest distance
        pair<long long, char> top = Q.top(); Q.pop();
        char u = top.second;
        long long dist = top.first;
        if(dist > d[u]) continue; //if the distance is greater than the current distance, skip
        //relaxation: from adjacent list find the adjacent nodes and update their distances
        for( auto it : adj[u]){
            char v = it.first;
            int weight = it.second;
            int cost = d[u] + weight; //total cost to reach v from u
            if (cost <= 30 || v == 'G') { //if the cost is less than or equal to 30, we can go to v without waiting
                if(cost < d[v]){
                d[v] = cost;
                Q.push({d[v], v});
                previous[v] = u; //update the previous node for v
                }
            }
            else {
                int i = 0;
                while((cost+i) % wait_times[v] !=0) i++;
                cost = cost + i;
                if(cost < d[v]){
                    d[v] = cost;
                    Q.push({d[v], v});
                    previous[v] = u;
                }
            }
        }
    }
    return {previous, d};
}

vector<char> shortest_path(map<char, char> previous, char start, char end){
    vector<char> path;
    while (1){
        path.push_back(end);
        end = previous[end];
        if (end == start) {
            path.push_back(start);
            break;
        }
    }

    reverse(path.begin(), path.end()); 
    return path;
}

string clean_line(string line) {
    for (char& c : line) {
        if (c == ',') {
            c = ' ';
        }
    }
    return line;
}

int main(int argc, char* argv[]) {
    //string file_name = argv[0];
    string input_file  = argv[1];
    string output_file = argv[2];

    ifstream fin(input_file);
    ofstream fout(output_file);

    vector<string> lines;
    string line;

    while(getline(fin, line)){
        if(line.empty()) continue;
        lines.push_back(clean_line(line));
    }
    fin.close();

    int index = 0;
    int graphs;
    char u,v;

    stringstream(lines[index++]) >> graphs;

    for(int i=0; i<graphs; i++){
        int vertices,wtime;
        stringstream(lines[index++]) >> vertices;
        map<char, int> wait_times; // Clear the wait times for the new graph
        adj.clear(); // Clear the adjacency list for the new graph

        for(int j=0; j<vertices; j++){
            stringstream(lines[index++]) >> u >> wtime;
            wait_times[u] = wtime;
        }

        while(index < (int)lines.size()){
            int weight;
            stringstream ss(lines[index]);
            if(ss >> u >> v >> weight) {
                ss >> u >> v >> weight;
                adj[u].push_back({v, weight});
                adj[v].push_back({u, weight});
                index++;
            }
            else {
                break;
            }
        }

        pair<map<char,char>, map<char,long long>> result = dijkstra('A', adj, wait_times);
        map<char,char> solution = result.first;
        map<char,long long> d = result.second;
        cout << d['G'] << endl;
        fout << d['G'] << endl;
        vector<char> path = shortest_path(solution, 'A', 'G');
        for (char x : path) {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    return 0;
}