// C++ program to find the shortest
// path between any two nodes using
// Floyd Warshall Algorithm.
#include "stdc++.h"
using namespace std;

#define MAXN 100
// Infinite value for array
const int INF = 1e7;

int dis[MAXN][MAXN];
int Next[MAXN][MAXN];

int ary[10][10],completed[10],n,cost=0;

//Function to convert numbers to letters
string numberToLetter(int number){
    string letter;
    switch (number) {
        case 0:
            letter = "A";
            break;
        case 1:
            letter = "B";
            break;
        case 2:
            letter = "C";
            break;
        case 3:
            letter = "D";
            break;
        case 4:
            letter = "E";
            break;
        case 5:
            letter = "F";
            break;
        case 6:
            letter = "G";
            break;
        case 7:
            letter = "H";
            break;
        case 8:
            letter = "I";
            break;
        case 9:
            letter = "J";
            break;
        case 10:
            letter = "K";
            break;
        case 11:
            letter = "L";
            break;
        case 12:
            letter = "M";
            break;
        case 13:
            letter = "N";
            break;
        case 14:
            letter = "O";
            break;
        case 15:
            letter = "P";
            break;
        case 16:
            letter = "Q";
            break;
        case 17:
            letter = "R";
            break;
        case 18:
            letter = "S";
            break;
        case 19:
            letter = "T";
            break;
        case 20:
            letter = "U";
            break;
        case 21:
            letter = "V";
            break;
        case 22:
            letter = "W";
            break;
        case 23:
            letter = "X";
            break;
        case 24:
            letter = "Y";
            break;
        case 25:
            letter = "Z";
            break;
    }
    return letter;
}

void takeInput()
{
    int i,j;

    //cout<<"Ingresa el número de colonias: ";
    cin>>n;

    for(i=0;i < n;i++)
    {
        for( j=0;j < n;j++)
            cin>>ary[i][j];

        completed[i]=0;
    }
}

int least(int c)
{
    int i,nc=999;
    int min=999,kmin;

    for(i=0;i < n;i++)
    {
        if((ary[c][i]!=0)&&(completed[i]==0))
            if(ary[c][i]+ary[i][c] < min)
            {
                min=ary[i][c]+ary[c][i];;
                kmin=ary[c][i];
                nc=i;
            }
    }

    if(min!=999)
        cost+=kmin;

    return nc;
}

// Initializing the distance and
// Next array
void initialise(int V,
                vector<vector<int> >& graph)
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dis[i][j] = graph[i][j];

            // No edge between node
            // i and j
            if (graph[i][j] == INF)
                Next[i][j] = -1;
            else
                Next[i][j] = j;
        }
    }
}

void mincost(int city)
{
    int i,ncity;

    completed[city]=1;

    cout<<numberToLetter(city)<<"--->";
    ncity=least(city);

    if(ncity==999)
    {
        ncity=0;
        cout<<numberToLetter(ncity);
        cost+=ary[city][ncity];

        return;
    }

    mincost(ncity);
}

// Function construct the shortest
// path between u and v
vector<int> constructPath(int u,
                          int v)
{
    // If there's no path between
    // node u and v, simply return
    // an empty array
    if (Next[u][v] == -1)
        return {};

    // Storing the path in a vector
    vector<int> path = { u };
    while (u != v) {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}

// Standard Floyd Warshall Algorithm
// with little modification Now if we find
// that dis[i][j] > dis[i][k] + dis[k][j]
// then we modify next[i][j] = next[i][k]
void floydWarshall(int V)
{
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                // We cannot travel through
                // edge that doesn't exist
                if (dis[i][k] == INF
                    || dis[k][j] == INF)
                    continue;

                if (dis[i][j] > dis[i][k]
                                + dis[k][j]) {
                    dis[i][j] = dis[i][k]
                                + dis[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
}

// Print the shortest path
void printPath(vector<int>& path)
{
    int n = path.size();
    for (int i = 0; i < n - 1; i++)
        cout << numberToLetter(path[i]) << " -> ";
    cout << numberToLetter(path[n - 1]) << endl;
}

using namespace std;

int bfs(int source,int target,int n,vector<int>& parent,vector<vector<int>>& graph){
    //Update the parent vector as each node value to be -1
    fill(parent.begin(),parent.end(),-1);
    //parent of source node to be -2
    parent[source] = -2;
    //Initializing queue for storing and min capacity so far
    queue<pair<int,int>> q;
    //Source node min capacity to be 1e9
    q.push({source,1e9});

    //Looping while queue is not empty
    while(!q.empty()){
        //storing top node and min capacity so far
        int u = q.front().first;
        int cap = q.front().second;
        //Removing top node from queue
        q.pop();
        //Looping all edges from u
        for(int v=0;v<n;v++){
            //finding v node has edge from u
            if(u!=v && graph[u][v]!=0 && parent[v]==-1){
                //storing parent v to be u
                parent[v] = u;
                //Updating the minimum capacity
                int min_cap = min(cap,graph[u][v]);
                //If v is the target node then return minimum capacity
                if(v==target){
                    return min_cap;
                }
                //if we didn't find target node
                //Insert the v node and minimum capacity so far in queue
                q.push({v,min_cap});
            }
        }
    }
    //if we didn't find path between source to target return 0
    return 0;
}

int Ford_Fulkerson(int source,int target,int n,vector<vector<int>>& graph){
    //Initializing parent vector for finding the path from source to target
    //In which we add parent of the node
    vector<int> parent(n,-1);
    //Initializing maximum flow for storing ans
    int max_flow = 0;
    int min_cap = 0;   //storing minimum capacity in each path

    //looping while minimum capacity become zero
    //For finding path and minimum capacity we call function bfs()
    while(min_cap = bfs(source,target,n,parent,graph)){
        //Adding the min_cap from this path
        max_flow += min_cap;
        //storing target node in v
        int v = target;

        //while we didn't find the source node
        //Looping through path stored in parent
        while(v!=source){
            //finding parent of v node
            int u = parent[v];
            //Subtracting minimum capacity from u to v
            //And adding minimum capacity from v to u
            graph[u][v] -= min_cap;
            graph[v][u] += min_cap;
            //Update the v node to it's parent
            v=u;
        }
    }
    //Returning maximum flow in the graph
    return max_flow;
}

void addEdge(vector<vector<int>>& graph,
             int u, int v, int w)
{
    graph[u][v] = w;
}


// Driver code
int main()
{
    int aux;

    takeInput();

    int V = n;
    /*vector<vector<int> > graph
            = { { 0, 16, 45, 32 },
                { 16, 0, 18, 21 },
                { 45, 18, 0, 7 },
                { 32, 21, 7, 0 } };*/

    // Clone a vector with the info of the 2D Ary
    vector<vector<int>> graph;

    for(int i=0; i<n; i++)
    {
        graph.push_back(std::vector<int>());
        for(int j=0; j<n; j++)
        {
            graph[i].push_back(ary[i][j]);
        }
    }

    /*
    //print the vector values
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout<<graph[i][j]<< "  ";
        }
        cout<<endl;
    }
    */
    int ary_flow[V][V];

    for(int i=0;i < n;i++)
    {
        for(int j=0;j < n;j++)
            cin>>ary_flow[i][j];
    }


    // Function to initialise the
    // distance and Next array
    initialise(V, graph);

    // Calling Floyd Warshall Algorithm,
    // this will update the shortest
    // distance as well as Next array
    floydWarshall(V);
    vector<int> path;

    cout<<"1. Forma de cablear las colonias con fibra, lista de arcos de la forma (A,B)."<<endl;


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j){
                cout << "La forma más optima de cablear las colonias: ("<<numberToLetter(i)<<","<<numberToLetter(j)<<") es: ";
                path = constructPath(i, j);
                printPath(path);
            }
        }
    }


    //Travelling Salesman Problem TSP
    cout<<endl<<"2. Ruta a seguir por el personal que reparte correspondencia, empezando de la primer colonia A y terminando en A."<<endl;
    cout<<"El camino pasando por todas las colonias y de regreso es:\n";
    mincost(0); //passing 0 because starting vertex
    cout<<endl;
    cout<<"El costo minímo es: "<<cost<<"km"<<endl<<endl;

    cout <<"3. Valor del flujo máximo de la información del nodo inicial al nodo final."<<endl;

    //Ford-Fulkerson Algorithm for Maximum Flow Problem
    vector<vector<int>> graph_weights(V, vector<int> (V, 0));
    //Adding edges weight in the graph
    /*
    addEdge(graph_weights, 0, 0, 0);
    addEdge(graph_weights, 0, 1, 48);
    addEdge(graph_weights, 0, 2, 12);
    addEdge(graph_weights, 0, 3, 18);
    addEdge(graph_weights, 1, 0, 52);
    addEdge(graph_weights, 1, 1, 0);
    addEdge(graph_weights, 1, 2, 42);
    addEdge(graph_weights, 1, 3, 32);
    addEdge(graph_weights, 2, 0, 18);
    addEdge(graph_weights, 2, 1, 46);
    addEdge(graph_weights, 2, 2, 0);
    addEdge(graph_weights, 2, 3, 56);
    addEdge(graph_weights, 3, 0, 21);
    addEdge(graph_weights, 3, 1, 36);
    addEdge(graph_weights, 3, 2, 52);
    addEdge(graph_weights, 3, 3, 0);
     */
    /*
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            cout<<ary_flow[i][j]<<"  ";
        }
        cout<<endl;
    }
    */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            addEdge(graph_weights,i,j,ary_flow[i][j]);
        }
    }

    //Printing the maximum flow from the given network Using Ford Fulkerson Method
    cout << "Maximum Flow Using Ford Fulkerson Algo: " << Ford_Fulkerson(0,3,V,graph_weights) << endl;

    cout<<"4. Nodo al que conectaré una nueva ubicación de acuerdo con su distancia a las centrales."<<endl;

    return 0;
}