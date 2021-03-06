#include <limits>
#include <list>
#include <map>
#include <utility> // pair
#include <iostream>
#include <stack>
#include <time.h>

#include "prioqueue.h"


// Unsigned integer.
//using uint = unsigned int;

using namespace std;//using namespace

/*
 * Graphs
 */

// Directed graph with nodes of type V.
// (An undirected graph can be represented as a directed graph
// be where every edge exists in both directions.)

class BFSGraph//graph class
{
    int Vertices;//vertice variable. stores Number of vertices
    //adjacency list representation of the graph as a table (map),
    // which contains the list of its descendants for each node.
    list<int>* adjLists;//adjacency list
    bool* visited;//pointer to mark the vertice which have been visited

    // initialize with adjacency list representation a.
    // This is also an initialization with a suitable
    // (nested) list of initializers in curly brackets
    // possible, for example:
    // { { "A", { "B", "C" } }, { "B", { } }, { "C", { "C" } } }

    public://public access type
        BFSGraph(int vertices);
        void addEdge(int src, int dest);
        void BFST(int startVertex);//function declarations
         void DFST(int startVertex);//function declarations
};//end of class


BFSGraph::BFSGraph(int vertices)//creating graph, takes 1 arg, acts as a constructor
{
    Vertices = vertices;
    adjLists = new list<int>[vertices];
}//end of constructor

// Directed weighted graph as a subclass of Graph<V>.
// (An undirected weighted graph can be called a directed weighted
// Graph where each edge is represented in both directions
// exists with the same weight.)

void BFSGraph::addEdge(int src, int dest)//Function to add edges--> Edges refer to the connectivity between vertices
{
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);//pushing
}//end of add edge method
// Perform breadth-first search on graph g with start node s
// and store the result in res.
// Result of a breadth-first search:
// Combination of Pred<V> formed by multiple processing
// and Dist<V, uint>.
void BFSGraph::BFST(int start)//function for BFS traversal, takes starting point
{
    visited = new bool[Vertices];

    for (int i = 0; i < Vertices; i++)//marking all the vertice as not visited
    {
          visited[i] = false;
    }

    list<int> queue;//list queue
    visited[start] = true;//marking starting vertex as visited
    queue.push_back(start);//pushing to queue
    list<int>::iterator i;

    while (!queue.empty())//looping till the queue is not empty
    {
        int current= queue.front();//getting front from queue as current index
        cout << current << "\n";//printing result
        queue.pop_front();//pop

        for (i = adjLists[current].begin(); i != adjLists[current].end(); ++i)
        {
            int adjVertex = *i;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
}//end of function

// Perform depth-first search on the graph g and store the result in res.
// In the main loop of the algorithm, the nodes in the
// Iterate over the order of the container g.vertices().
void BFSGraph::DFST(int vertex)//performs Depth first earch
{
    visited[vertex] = true;//marking as visited
    list<int> adjList = adjLists[vertex];//creating list

    cout << vertex << " ";//printing

    list<int>::iterator i;//itertor list-> int type

    for (i = adjList.begin(); i != adjList.end(); ++i)//looping till we get the end of list
    {
        if (!visited[*i])//if vertex not visited
        {
            DFST(*i);
        }
    }
}//end of function

class SCCGraph//graph class
{
    int vertex;//declaring variable
    list<int> *adj;//list

    void fillOrder(int s, bool visitedV[], stack<int> &Stack);
    void DFSSCC(int s, bool visitedV[]);//Depth First Search

    public://access type
        SCCGraph(int V);
        void addEdge(int s, int d);
        void printSCC();
        SCCGraph transpose();
};//end of class

SCCGraph::SCCGraph(int V)//acts as constructor
{
  this->vertex = V;
  adj = new list<int>[V];
}//end of constructor

void SCCGraph::DFSSCC(int con, bool visited[])//recursive function
{
    visited[con] = true;//marking as visited
    cout << con << " ";//printing
    list<int>::iterator i;//iterator list

    for (i = adj[con].begin(); i != adj[con].end(); ++i)
    {
        if (!visited[*i])//if not visited
        {
            DFSSCC(*i, visited);//calling itself--> recurrsion
        }
    }
}//end of function

SCCGraph SCCGraph::transpose()//takes nothing, returns graph
{
    // Idea: In an outer loop all nodes u of the graph
    // run through. In an inner loop all successors of v
    // traverse from u, each time u succeeding v
    // to a new adjacency list representation a des
    // add transposed graph.
    // Finally, pass a to the Graph<V> constructor.
    // Note: If table a does not already have an entry for the
    // contains node v, a[v] automatically creates a new one
    // Entry with an empty list of descendants to which
    // push_back can be applied directly.

    SCCGraph transposegraph(vertex);//creating object

    for (int j = 0; j < vertex; j++)//looping number of vertex times
    {
        list<int>::iterator i;//iterator

        for (i = adj[j].begin(); i != adj[j].end(); ++i)
        {
            transposegraph.adj[*i].push_back(j);
        }//end of inner for
    }//end of outer for

    return transposegraph;//returning graph
}//end of function

void SCCGraph::addEdge(int s, int d)//returns nothing, takes 2 arguments, adds edges
{
    adj[s].push_back(d);
}//end of function

void SCCGraph::fillOrder(int top, bool visited[], stack<int> &Stack)//takes 3 arguments, returns nothing
{
    visited[top] = true;//marking index "top" as visited
    list<int>::iterator i;//iterator list

    for (i = adj[top].begin(); i != adj[top].end(); ++i)
    {
           if (!visited[*i])
           {
                   fillOrder(*i, visited, Stack);
           }
    }

  Stack.push(top);//pushing to stack
}

void SCCGraph::printSCC()//takes nothing, returns nothing, prints result
{
    stack<int> Stack;//declaring stack
    bool *visited = new bool[vertex];//dynamic array

    for (int i = 0; i < vertex; i++)//looping vertex times
    {
        visited[i] = false;//marking all as non visited
    }

    for (int i = 0; i < vertex; i++)//looping vertex times
    {
        if (visited[i] == false)//if vertex not visited
        {
            fillOrder(i, visited, Stack);
        }
    }

    SCCGraph PrintGraph = transpose();//creating graph obj

    for (int i = 0; i < vertex; i++)//marking all as false
    {
        visited[i] = false;
    }

    while (Stack.empty() == false)//if stack not empty
    {
        int top = Stack.top();//getting top element
        Stack.pop();//poping

        if (visited[top] == false)
        {
            PrintGraph.DFSSCC(top, visited);//printing
            cout << endl;//new lie
        }
    }//end of while
}//end of function

#define tempvertex 10

int MinKey(int key[], bool mstSet[])//takes 2 arguments, returns Minimum Index
{
	int min = INT_MAX;
	int index;//declaring variables

	for (int v = 0; v < tempvertex; v++)//lopping number of vertex times
    {
        if (mstSet[v] == false && key[v] < min)//if minimum
        {
            min = key[v];
            index = v;//updating minimum index
        }
    }

	return index;//returning index
}//end of function

void printMST(int parent[], int graph[tempvertex][tempvertex])//takes 2 arguments, prints the result
{
	for (int i = 1; i < tempvertex; i++)//looping vertex times
    {
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
    }
}//end of function

void primMST(int graph[tempvertex][tempvertex])//Minimum Spanning tree function
{
	int parent[tempvertex];
	int key[tempvertex];
	bool visited[tempvertex];

	for (int i = 0; i < tempvertex; i++)//looping vertex times
    {
        key[i] = INT_MAX;
        visited[i] = false;//marking all as false
    }

	key[0] = 0;
	parent[0] = -1;

	for (int count = 0; count < tempvertex - 1; count++)
	{
		int u = MinKey(key, visited);
		visited[u] = true;

		for (int v = 0; v < tempvertex; v++)
        {
            if (graph[u][v] && visited[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
	}

	printMST(parent, graph);//printing
}//end of function

// Minimum skeleton of the graph g using the modified algorithm from
// Determine prim with starting node s and store the result in res.
// The graph must be undirected, i.e. H. each edge must be in both
// There must be directions with the same weight.
// (This does not need to be checked.)
// Caution: res does not contain a table dist and therefore no value
// INF, because the dist values ??only during the execution of the algorithm
// are needed, but not for the result.
// Nevertheless, the function can of course have a corresponding one internally
// Use Dist object.
void prim()
{
    srand((unsigned) time(0));//for random number generation

    int graph[tempvertex][tempvertex];

    for(int i=0; i<tempvertex; i++)
    {
        for(int j=0;j<tempvertex;j++)
        {
            graph[i][j]= 1 + (rand() % 100);//assigning random values to array
        }
    }

	primMST(graph);
}

struct Edge//user defined structure, stores edge information
{
	int source;
    int destination;
    int weight;
};

struct Graph//user defined structure, stores graph information
{
	int Vertex;
	int Edge;
	struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = new Graph;
	graph->Vertex = V;
	graph->Edge = E;
	graph->edge = new Edge[E];
	return graph;
}

void PrintBellFord(int distance[], int size)//prints result
{
	for (int i = 0; i < size; ++i)//looping size times
    {
        cout<< i <<"\t\t"<< distance[i]<<"\n";//printing
    }
}//end of function

/*
 * Data structures for storing the results of the algorithms
 */

// result of prim plus part of result of breadth-first search,
// Bellman-Ford and Dijkstra.
    // Substitute value INF stored in dist[v] if distance
    // between s and v is infinity.
    // The INF value is either "infinity" (if available) or der
    // largest possible finite value of type N.
    // (Floating point types are commonly implemented according to IEEE 754
    // and then have "infinity" as a value, but integer types do
    // not.)
void BellmanFord(struct Graph* graph, int src)//BellmanFord shortest path finder
{
    int u=0;
    int v=0;
    int weight;
	int V = graph->Vertex;
	int E = graph->Edge;
	int distance[V];//declaring & initializing variables

	for (int i = 0; i < V; i++)
    {
        distance[i] = INT_MAX;
    }

	distance[src] = 0;//setting distance at src index 0

	for (int i = 1; i <= V - 1; i++)
    {
		for (int j = 0; j < E; j++)
        {
			u = graph->edge[j].source;
			v = graph->edge[j].destination;
			weight = graph->edge[j].weight;

			if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
            }
		}//end of inner for loop
	}//end of outer for loop

	for (int i = 0; i < E; i++)
    {
		u = graph->edge[i].source;
		v = graph->edge[i].destination;
		weight = graph->edge[i].weight;

		if (distance[u] != INT_MAX&& distance[u] + weight < distance[v]) //if negative distance
        {
			return;
		}
	}//end of for

	PrintBellFord(distance, V);//printing
	return;//return
}//end of functin

// Shortest paths from the start node s to all nodes of the graph g with
// determine the Bellman-Ford algorithm and store the result in res
// to save.
// Result value true if there is no starting node in the graph
// returns achievable cycle with negative weight, false otherwise.
// (In the second case, the content of res may be undefined afterwards.)

void bellmanFord()
{
    	int V = 5;
	int E = 8;//initializing variables
	struct Graph* graph = createGraph(V, E);//creating graph

	graph->edge[0].source = 0;
	graph->edge[0].destination = 1;
	graph->edge[0].weight = -1;

	graph->edge[1].source = 0;
	graph->edge[1].destination = 2;
	graph->edge[1].weight = 4;

	graph->edge[2].source = 1;
	graph->edge[2].destination = 2;
	graph->edge[2].weight = 3;

	graph->edge[3].source = 1;
	graph->edge[3].destination = 3;
	graph->edge[3].weight = 2;

	graph->edge[4].source = 1;
	graph->edge[4].destination = 4;
	graph->edge[4].weight = 2;

	graph->edge[5].source = 3;
	graph->edge[5].destination = 2;
	graph->edge[5].weight = 5;

	graph->edge[6].source = 3;
	graph->edge[6].destination = 1;
	graph->edge[6].weight = 1;

	graph->edge[7].source = 4;
	graph->edge[7].destination = 3;
	graph->edge[7].weight = -3;

	BellmanFord(graph, 0);//calling function
}


    // Substitute value INF stored in dist[v] if distance
    // between s and v is infinity.
    // The INF value is either "infinity" (if available) or der
    // largest possible finite value of type N.
    // (Floating point types are commonly implemented according to IEEE 754
    // and then have "infinity" as a value, but integer types do
    // not.)
int MinimumDistance(int dist[], bool sptSet[],int V)//Finds the smallest distance between vertex
{

    int min = INT_MAX;
    int index;//declaring variables

    for (int v = 0; v < V; v++)//looping number of vertex times
    {
        if (sptSet[v] == false && dist[v] <= min)//getting minimum distance
        {
            min = dist[v], index = v;
        }
    }//end of for

    return index;//returning index, with minimum distance
}

void printSolution(int dist[], int V)
{
    cout <<"Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout  << i << " \t\t"<<dist[i]<< endl;
}

/*
 * Data structures for storing the results of the algorithms
 */

// result of prim plus part of result of breadth-first search,
// Bellman-Ford and Dijkstra.

// Shortest paths from the start node s to all nodes of the graph g with
// determine Dijkstra's algorithm and save the result in res
// to save.
// The edges of the graph must not have negative weights.
// (This does not need to be checked.)
void dijkstra(int graph[tempvertex][tempvertex], int src, int V)//function to get shortest path, takes graph & source
{
    int dist[V];
    bool visited[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;//marking all as non visited
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)//looping vertex-1 times
    {
        int Min = MinimumDistance(dist, visited, V);//getting minimum distance
        visited[Min] = true;//marking as visited

        for (int v = 0; v < V; v++)
        {
             if (!visited[v] && graph[Min][v] && dist[Min] != INT_MAX&& dist[Min] + graph[Min][v] < dist[v])
             {
                 dist[v] = dist[Min] + graph[Min][v];
             }
        }
    }
    printSolution(dist, V);
}

void dijk()
{
    srand((unsigned) time(0));//for random number generation

    int graph[tempvertex][tempvertex];//2d array

    for(int i=0; i<tempvertex; i++)
    {
        for(int j=0;j<tempvertex;j++)
        {
            graph[i][j]= 1 + (rand() % 100);//assigning random values to array
        }
   }

    dijkstra(graph, 0, tempvertex);//calling function
}

void BFS()
{
    BFSGraph graphBFS(4);//create graph object, passing number of vertices

    graphBFS.addEdge(0, 1);
    graphBFS.addEdge(0, 2);
    graphBFS.addEdge(1, 2);
    graphBFS.addEdge(2, 0);
    graphBFS.addEdge(2, 3);
    graphBFS.addEdge(3, 3);//adding vertex & edge

    graphBFS.BFST(1);//calling DFS Function
}

void DFS()
{
    BFSGraph graphDFS(4);//create graph object, passing number of vertices

    graphDFS.addEdge(0, 1);
    graphDFS.addEdge(0, 2);
    graphDFS.addEdge(1, 2);
    graphDFS.addEdge(2, 0);
    graphDFS.addEdge(2, 3);
    graphDFS.addEdge(3, 3);//adding vertex & edge

    graphDFS.DFST(1);//calling DFS Function
}

class TopoGraph
{
	int Vertices;//declaring variables
	list<int>* adj;//adjacency list

	void topologicalSortUtil(int v, bool visited[],stack<int>& Stack);

    public://access tpye
        TopoGraph(int Vertices);//constructor
        void addEdge(int v, int w);//adds edge
        void topologicalSort();
};

// Perform a topological sort on the graph g and the result
// store as a list of nodes in seq.
// Result value true if this is possible
// false if the graph contains a cycle.
// (In the second case, the content of seq may be undefined afterwards.)

TopoGraph::TopoGraph(int V)//constructor
{
	this->Vertices = V;
	adj = new list<int>[V];
}//end of constructor

void TopoGraph::addEdge(int v, int w)//add edge to graph
{
	adj[v].push_back(w);//pushing to graph
}//end of function

// Perform a topological sort on the graph g and the result
// store as a list of nodes in seq.
// Result value true if this is possible
// false if the graph contains a cycle.
// (In the second case, the content of seq may be undefined afterwards.)
void TopoGraph::topologicalSortUtil(int vertex, bool visited[],stack<int>& Stack)
{
	visited[vertex] = true;//marking verte as visited
	list<int>::iterator i;//iterator list

	for (i = adj[vertex].begin(); i != adj[vertex].end(); ++i)//looping
    {
        if (!visited[*i])//not visited
        {
            topologicalSortUtil(*i, visited, Stack);//recurrsion
        }
    }

	Stack.push(vertex);//pushing to stack
}

void TopoGraph::topologicalSort()
{
	stack<int> Stack;//creating stack

	bool* visited = new bool[Vertices];//array to mark visted vertex

	for (int i = 0; i < Vertices; i++)//looping Vertex times
    {
        visited[i] = false;///marking all vertex as non visited
    }

	for (int i = 0; i < Vertices; i++)//looping Vertex times
    {
        if (visited[i] == false)//if vertex not visited
        {
            topologicalSortUtil(i, visited, Stack);
        }
    }


	while (Stack.empty() == false)
    {
		cout << Stack.top() << " ";//printing result
		Stack.pop();//popping from stack
	}
}

void SCC()
{
    SCCGraph graphSCC(4);//create graph object, passing number of vertics
    graphSCC.addEdge(0, 1);
    graphSCC.addEdge(0, 2);
    graphSCC.addEdge(1, 2);
    graphSCC.addEdge(2, 0);
    graphSCC.addEdge(2, 3);
    graphSCC.addEdge(3, 3);//adding vertex & edge
    graphSCC.printSCC();
}

void sort()
{
    TopoGraph g(6);
	g.addEdge(5, 2);
	g.addEdge(5, 0);
	g.addEdge(4, 0);
	g.addEdge(4, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);
	g.topologicalSort();
}

