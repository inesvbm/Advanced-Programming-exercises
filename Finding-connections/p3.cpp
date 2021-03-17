#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h> 
#include <algorithm> 
#include <iomanip> 
#include <iterator>
using namespace std;

//---------------------------------------------------------- adjacency matrix
vector<vector<int>> matrix;
int numberVertex;
//---------------------------------------------------------- AP algorithm
vector<int> dfs;
vector<int> low;
vector<int> parent;
vector<int> visited;
vector<int> articPoints;
vector<int> auxArticPoints;
static int countDFS = -1;

void AP(int index) {
    int children = 0;
    visited[index] = 1;
    dfs[index] = low[index] = ++countDFS;
    for (int i = 0; i < numberVertex; i++) {
        if (matrix[index][i] != 10000000) { // if there is a connection to that vertex
            if (visited[i] == 0) {
                children++;
                parent[i] = index;
                AP(i);
                low[index] = min(low[index], low[i]);
                if (parent[index] == -1 && children > 1) {
                    articPoints[index] = 1;
                }
                if (parent[index] != -1 && low[i] >= dfs[index]) {
                    articPoints[index] = 1;
                }
            }
            else if (i != parent[index]) {
                low[index] = min(low[index], dfs[i]);
            }
        }
    }
}

//---------------------------------------------------------- Floyd-Warshall
class Edge {
public:
    int v1, v2, cost;
};

vector<Edge> totalEdges;

int floyd_warshall() {
    int sum = 0;
    for (int i = 0; i < numberVertex; i++) {
        matrix[i][i] = 0;
    }    
    for (int k = 0; k < numberVertex; k++) {
        for (int i = 0; i < numberVertex; i++) {
            for (int j = 0; j < numberVertex; j++) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
    int countServers = 0;
    for (int i = 0; i < numberVertex; i++) { // rename servers to match index
        if (articPoints[i] != 0) {
            auxArticPoints[i] = countServers;
            countServers++;
        }
    }
    for (int i = 0; i < numberVertex; i++) { 
        if (articPoints[i] != 0) {
            for (int j = i + 1; j < numberVertex; j++) {
                if (articPoints[j] != 0 && matrix[i][j] != 10000000) {
                    sum += matrix[i][j];
                    Edge e;
                    e.v1 = auxArticPoints[i];
                    e.v2 = auxArticPoints[j];
                    e.cost = matrix[i][j];
                    totalEdges.push_back(e);
                }
            }
        }
    }
    return sum;
}

//---------------------------------------------------------- Kruskal
bool operator < (Edge e1, Edge e2) {
    return (e1.cost < e2.cost);
}

int find_set(vector<int> parent, int index) {
    if (parent[index] != index) {
        parent[index] = find_set(parent, parent[index]);
    }
    return parent[index];
}

void union_set(vector<int> parent, vector<int> rank, int ind1, int ind2) {
    if (rank[ind1] > rank[ind2]) {
        parent[ind2] = ind1;
    }
    else {
        parent[ind1] = ind2;
    }
    if (rank[ind1] == rank[ind2]) {
        rank[ind2]++;
    }
}

int kruskal() {
    int count = 0;
    int sum = 0;
    vector<Edge> finalTree;
    vector<int> parent;
    vector<int> rank;
    for (int i = 0; i < numberVertex; i++) {
        if (articPoints[i] != 0) {
            parent.push_back(count);
            rank.push_back(0);
            count++;
        }
    }
    sort(totalEdges.begin(), totalEdges.end());
    for (size_t i = 0; i < totalEdges.size(); i++) {
        int src = find_set(parent, totalEdges[i].v1);
        int dest = find_set(parent, totalEdges[i].v2);
        if (src != dest) {
            finalTree.push_back(totalEdges[i]);
            parent[src] = dest;
            union_set(parent, rank, src, dest);
        }
    }
    for (size_t i = 0; i < finalTree.size(); i++) {
        sum += finalTree[i].cost;
    }
    return sum;
}

//---------------------------------------------------------- solve problem
void solve() {
    int count = 0;
    for (int i = 0; i < numberVertex; i++) {
        if (articPoints[i] != 0) {
            count++;
        }
    }
    if (count == 0) {
        cout << "no server" << endl;
    }
    else if (count == 1) {
        cout << "1 0 0" << endl;
    }
    else {
        int floyd = floyd_warshall();
        string res = to_string(count) + " " + to_string(floyd) + " ";
        if (totalEdges.size() > 1) {            
            int krus = kruskal();
            res += to_string(krus);
        }
        else {
            res += to_string(floyd);            
        }
        cout << res << endl;
    }
}

void readLines() {
    int v, u, cost;
    while (scanf("%d", &numberVertex) > 0) {
        matrix.clear();
        dfs.clear();
        low.clear();
        parent.clear();
        visited.clear();
        articPoints.clear();
        totalEdges.clear();
        auxArticPoints.clear();

        for (int i = 0; i < numberVertex; i++) {
            vector<int> vec;

            dfs.push_back(0);
            low.push_back(0);
            parent.push_back(-1);
            visited.push_back(0);
            articPoints.push_back(0);
            auxArticPoints.push_back(0);

            for (int j = 0; j < numberVertex; j++) {
                vec.push_back(10000000);
            }
            matrix.push_back(vec);
        }

        scanf("%d", &v);
        while (v != 0) {
            scanf("%d %d", &u, &cost);

            matrix[v - 1][u - 1] = cost;
            matrix[u - 1][v - 1] = cost;

            scanf("%d", &v);
        }
        for (int i = 0; i < numberVertex; i++) {
            if (visited[i] == 0) {
                AP(i);
            }
        }
        solve();
    }
}

int main() {
    readLines();
    return 0;
}