
#include <iostream>
#include <list>//including header files
#include <stack>
#include <time.h>

using namespace std;//using namespace

#include "graph.h"

int main()//main function --? Execution starts here--> DONOT INCLUDE IN GRAPH.H FILE
{

 BFSGraph graphBFS(4);//create graph object, passing number of vertices
    graphBFS.addEdge(0, 1);
    graphBFS.addEdge(0, 2);
    graphBFS.addEdge(1, 2);
    graphBFS.addEdge(2, 0);
    graphBFS.addEdge(2, 3);
    graphBFS.addEdge(3, 3);//adding vertex & edge
    graphBFS.BFST(1);//calling DFS Function

    cout<<"\n\n";

    graphBFS.DFST(1);//calling DFS Function

    cout<<"\n\n";
    sort();
    cout<<"\n\n";
    SCC();
    cout<<"\n\n";
    prim();
    cout<<"\n\n";
    bellmanFord();
    cout<<"\n\n";
    dijk();
    return 0;
}
