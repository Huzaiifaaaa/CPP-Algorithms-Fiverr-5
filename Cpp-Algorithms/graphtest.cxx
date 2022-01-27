#include <iostream>
#include <string>
using namespace std;

#include "graph.h"

// node type.
using V = string;

// Field with test graphs.
// (Any other graphs can be added for your own tests.)
// So that graphs of type Graph<V> and WeightedGraph<V> in the same field
// can be stored as pointers to the base type Graph<V>
// stored if needed in pointer to WeightedGraph<V>
// being transformed.
//Graph<V>* graphs[] = {
    // Example of an unweighted graph.
    /*new Graph<string>({
		{ "A", { "B", "C" } },	// node A has children B and C.
		{ "B", { } },		// Node B has no children.
		{ "C", { "C" } }	// Node C has itself as its successor.
    }),

    // Example of a weighted graph.
    new WeightedGraph<string>({
		{ "A", { { "B", 2 }, { "C", 3 } } },
			// Edges A -> B with weight 2 and A -> C with weight 3.
		{ "B", { } }, 		// No edges B -> ...
		{ "C", { { "C", 4 } } } // Edge C -> C with weight 4.
    }),
};*/

// Path from start node s to node v using ancestor information
// output to res.
/*void path (V s, V v, Pred<V>& res) {
    if (s != v && res.pred[v] != res.NIL) {
		path(s, res.pred[v], res);
		cout << " -> ";
    }
    cout << v;
}
*/
// main program.
// Algorithm selection by first command line argument:
// bfs -> breadth first search
// dfs -> depth first search
// sort -> topological sort
// scc -> strongly connected components
// prime -> prime
// bell -> Bellman Ford
// dijk -> Dijkstra
// Selection of the test graph by the second command line argument.
// (For the prim, bell and dijk algorithms, a weighted
// graph can be selected.)
// Selection of the starting node by the optional third
// Command line argument (default is "A").
int main (int argc, char* argv[]) {
    // Command line arguments.
    string a = argv[1]; // Algorithm.
//    Graph<V>* g = graphs[stoi(argv[2])]; // graph.
    //V s = argc > 3 ? argv[3] : "A"; // start node.

    // Run the desired algorithm and print its result.
    /*if (a == "bfs") {
		BFS<V> res;
		bfs(*g, s, res);
		for (V v : g->vertices()) {
			path(s, v, res);
			uint d = res.dist[v];
			if (d == res.INF) cout << " inf" << endl;
			else cout << " " << d << endl;
		}
    }
    else if (a == "dfs") {
		DFS<V> res;
		dfs(*g, res);
		for (V v : res.seq) {
			cout << v << " " << res.det[v] << " " << res.fin[v] << endl;
		}
    }
    else*/ if (a == "sort") {
		//list<V> res;
		sort();
		/*if (topsort(*g, res)) {
			for (V v : res) cout << v << endl;
		}
		else {
			cout << "cycle" << endl;
		}
    */}
    else if (a == "scc") {
		//list<list<V>> res;
		SCC();
		/*scc(*g, res);
		for (list<V> c : res) {
			c.sort();
			for (V v : c) cout << v << " ";
			cout << endl;
		}
	*/}
    else if (a == "prime") {
//		Pred<V> res;
		prim();
		/*prim(*(WeightedGraph<V>*)g, s, res);
		for (V v : g->vertices()) {
			path(s, v, res);
			cout << endl;
		}
    */}
    else if (a == "bell") {
		//SP<V> res;
		bellmanFord();
		/*if (bellmanFord(*(WeightedGraph<V>*)g, s, res)) {
			for (V v : g->vertices()) {
				path(s, v, res);
				cout << " " << res.dist[v] << endl;
			}
		}
		else {
			cout << "negative cycle" << endl;
		}
    */}
    else if (a == "dijk") {
//		SP<V> res;
		dijk();
		/*dijkstra(*(WeightedGraph<V>*)g, s, res);
		for (V v : g->vertices()) {
			path(s, v, res);
			cout << " " << res.dist[v] << endl;
		}
    */}
    else {
		cout << "unknown algorithm: " << a << endl;
    }
}
