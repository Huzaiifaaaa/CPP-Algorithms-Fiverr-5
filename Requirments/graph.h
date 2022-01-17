#include <limits>
#include <list>
#include <map>
#include <utility> // pair

#include "prioqueue.h"

// Unsigned integer.
using uint = unsigned int;

/*
 * Graphs
 */

// Directed graph with nodes of type V.
// (An undirected graph can be represented as a directed graph
// be where every edge exists in both directions.)
template <typename V>
struct graph {
    // adjacency list representation of the graph as a table (map),
    // which contains the list of its descendants for each node.
    map<V, list<V>> adj;

    // initialize with adjacency list representation a.
    // This is also an initialization with a suitable
    // (nested) list of initializers in curly brackets
    // possible, for example:
    // { { "A", { "B", "C" } }, { "B", { } }, { "C", { "C" } } }
    Graph (map<V, list<V>> a) : adj(a) {}

    // Return container with all nodes of the graph.
    list<V> vertices () {
		// Loop through all pairs p of table adj
		// and their first component p.first
		// add vs to the end of the list.
		list<V> vs;
		for (pair<V, list<V>> p : adj) vs.push_back(p.first);
		return vs;
    }

    // Return container with all descendants of node v.
    list<V> successors (V v) {
		// The one stored for node v in table adj
		// Return list of successors.
		return adj[v];
    }

    // Return the transposed graph as a new, independent object.
    Graph<V> transpose () {
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
    }
};

// Directed weighted graph as a subclass of Graph<V>.
// (An undirected weighted graph can be called a directed weighted
// Graph where each edge is represented in both directions
// exists with the same weight.)
template <typename V>
struct WeightedGraph : Graph<V> {
    // Table of edge weights.
    map<pair<V, V>, double> wt;

    // initialization with edge weights extended
    // adjacency list representation a.
    // This is also an initialization with a suitable
    // (nested) list of initializers in curly brackets
    // possible, for example:
    // { { "A", { { "B", 2 }, { "C", 3 } } }, { "B", { } },
    // { "C", { { "C", 4 } } } }
    WeightedGraph (map<V, list<pair<V, double>>> a) : Graph<V>({}) {
		// loop through the expanded adjacency list representation a and
		// with the information it contains, the (from Graph<V>
		// inherited) simple adjacency list representation adj and die
		// Fill weight table wt appropriately.
		for (auto p : a) {
			V u = p.first;
			Graph<V>::adj[u];
			for (auto q : p.second) {
			V v = q.first;
			double w = q.second;
			Graph<V>::adj[u].push_back(v);
			wt[{ u, v }] = w;
		}
	}
}

    // Return weight of edge (u, v).
    double weight (Vu, Vv) {
		return wt[{ u, v }];
    }
};

/*
 * Data structures for storing the results of the algorithms
 */

// result of prim plus part of result of breadth-first search,
// Bellman-Ford and Dijkstra.
template <typename V>
struct Pred {
    // table for storing the ancestor pred[v] of a node v.
    map<V, V> pred;

    // substitute value NIL, which is stored in pred[v] if it is to
    // a node v has no predecessor.
    // Defaults to the value given by the parameterless constructor of V
    // returns. If necessary, before running an algorithm
    // but another value can also be assigned to NIL that isn't
    // occurs as a real node value.
    V NIL = V();
};

// part of the result of breadth-first search (with N equal to uint)
// as well as Bellman-Ford and Dijkstra (with N equal to double).
template <typename V, typename N>
struct Dist {
    // Table for storing the distance dist[v] with numeric type N
    // between the starting node s and the node v.
    map<V,N> dist;

    // Substitute value INF stored in dist[v] if distance
    // between s and v is infinity.
    // The INF value is either "infinity" (if available) or der
    // largest possible finite value of type N.
    // (Floating point types are commonly implemented according to IEEE 754
    // and then have "infinity" as a value, but integer types do
    // not.)
    static constexpr N INF = numeric_limits<N>::has_infinity ?
		numeric_limits<N>::infinity() : numeric_limits<N>::max();
};

// Result of a breadth-first search:
// Combination of Pred<V> formed by multiple processing
// and Dist<V, uint>.
template <typename V>
struct BFS : Pred<V>, Dist<V, uint> {};

// Result of a depth-first search.
template <typename V>
struct DFS {
    // Tables for storing detection time det[v] and der
    // completion time fin[v] of a node v.
    // Both time values ??are between 1 and twice the number of nodes
    // of the graph.
    map<V, uint> det, fin;

    // List to store all nodes of the graph in ascending order
    // Completion times that are the same as the result of a
    // is a successful topological sort.
    list<V> seq;
};

// Result of the Bellman-Ford and Dijkstra shortest-path algorithms:
// Combination of Pred<V> formed by multiple processing
// and Dist<V, double>.
template <typename V>
struct SP : Pred<V>, Dist<V, double> {};

/*
 * Algorithms
 */

// Perform breadth-first search on graph g with start node s
// and store the result in res.
template <typename V, typename G>
void bfs (G g, V s, BFS<V>& res)

// Perform depth-first search on the graph g and store the result in res.
// In the main loop of the algorithm, the nodes in the
// Iterate over the order of the container g.vertices().
template <typename V, typename G>
void dfs (G g, DFS<V>& res)

// Perform depth-first search on the graph g and store the result in res.
// In the main loop of the algorithm, the nodes in the
// traverse order of list vs.
template <typename V, typename G>
void dfs (G g, list<V> vs, DFS<V>& res)

// Perform a topological sort on the graph g and the result
// store as a list of nodes in seq.
// Result value true if this is possible
// false if the graph contains a cycle.
// (In the second case, the content of seq may be undefined afterwards.)
template <typename V, typename G>
bool topsort (G g, list<V>& seq)

// Find the strongly connected components of the graph g
// and store the result as a list of lists of nodes in res.
// (Each element of res corresponds to a strongly connected component.)
template <typename V, typename G>
void scc (G g, list<list<V>>& res)

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
template <typename V, typename G>
void prime (G g, V s, Pred<V>& res)

// Shortest paths from the start node s to all nodes of the graph g with
// determine the Bellman-Ford algorithm and store the result in res
// to save.
// Result value true if there is no starting node in the graph
// returns achievable cycle with negative weight, false otherwise.
// (In the second case, the content of res may be undefined afterwards.)
template <typename V, typename G>
bool bellmanFord (G g, V s, SP<V>& res)

// Shortest paths from the start node s to all nodes of the graph g with
// determine Dijkstra's algorithm and save the result in res
// to save.
// The edges of the graph must not have negative weights.
// (This does not need to be checked.)
template <typename V, typename G>
void dijkstra (G g, V s, SP<V>& res)
