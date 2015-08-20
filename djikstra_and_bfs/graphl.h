
/*
@Authors: Christopher DuBois && Brody Schulke
//CSS 343 Professor Zander Lab 3 Spring Qtr 2015
//Depth-first serch using adjacency list
*/

//-------------------------------------------------------------------------//
//GraphL class: implemenation of Depth-first search using an adjacency list
// to store all nodes and their edges. 

/*
Picture of adjacency list data structure used throughout GraphL
Note not all indices have adjacent nodes, picture is for representation
The ~ represents a graphNode
Note that the 0-index is not used, this is using 1-based index

 -
|0|
 -	     -	       -
|1| --->|~|--->...|N|
 -	     -	       -
|2| --->|~|--->...|N|
 -
|.|
 -
|.|
 -
|.|
 -	     -	       - 
|N| --->|~|--->...|N|
*/

//-----------------------------------------------------------------//
//Implementation and Assumptions
//Implementation---------------------------------------------------//
//Features listed below and lebeled with numbers
//in each method in the h and cpp files
//1 Default Constructor
// -Loops through adjacency list intializing indices' edgeHeads
// -sets size to 0
//2 Destructor
// -Deallocates all the memory in the adjacency list
// -Loops through each index of the adjacency list and deletes
//  everything store within the list
//3 buildGraph
// -Constructs the adjacency list for the graph using the text file
//4 displayGraph
// -Displays graph information including nodedata, edge from, and
//  edge to, if the graph has not been built or is empty, the graph
//  will still always just print Graph:
//  and Depth-first ordering: (with nothing after the colons)
//5 depthFirstSearch
// -uses Depth-first search algorithm on the adjacency list and prints
//  out results as the algorithm traverses deeper into the list
//
//Assumptions---------------------------------------------------//
//1 Assumes size is never greater than 100 nodes
//2 Assumes that user wants everything, including dynamic memory, 
//  to be deleted from the graph
//3 Assumes that the text file is properly formatted like so:
//
//int size
//Nodedata string
//...
//Nodedata string N
//int fromNode int toNode
//...
//int fromNode N int toNode N
//
// Assumes file contains no more than 100 elements
// Assumes text file terminates with '0 0'
//4 Assumes graph has already been built and has a size
//  greater than 0
//5 Assumes the graph has been constructed using an adjacency list which
// contains no more than 100 elements
#ifndef GRAPHL_H
#define GRAPHL_H

#include <iomanip>
#include "nodedata.h"

//Program specification for maximum nodes
//1-100 indexing
static const int MAXNODESPART2 = 101;

class GraphL
{
public:
	//1 Default Constructor
	GraphL();
	//2 Destructor
	~GraphL();
	//3 buildGraph from input file
	void buildGraph(istream&);
	//4 displayGraph using adjacency list
	void displayGraph() const;
	//5 depthFirstSearch using algorithm
	void depthFirstSearch();
private:

	//structures--------------------------------//
	struct EdgeNode; // forward reference for the compiler 
	//GraphNode containing an EdgeNode pointer to edgeHead, NodeData
	// for prints and node information, along with a bool for visited testing
	struct GraphNode { // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead; // head of the list of edges
		NodeData data;
		bool visited;
	};
	//EdgeNode containing index of adjacent node and
	// a pointer to another adjacent node
	struct EdgeNode {
		int adjGraphNode; // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};
	//structures--------------------------------//


	//Adjacency list for graph
	GraphNode adjList[MAXNODESPART2];

	//graph size 
	int size;

	//a bool to ensure that the graph has actually been built before
	bool built;

	//private methods below------------------------//
	//each method is a helper method
	//and has the public method's number 
	//corresponding to it

	//3 insertEdge
	//helper method for buildGraph
	bool insertEdge(const int, const int);
	//2,3 makeEmpty
	//helper method for destructor and buildGraph
	void makeEmpty();
	//5 markAllUnvisited
	//helper method for depthFirstSearch
	void markAllAsUnvisited();
	//5 dfs
	//helper method for depthFirstSearch
	void dfs(const int);
	
};
#endif

