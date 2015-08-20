/*
@Authors: Christopher DuBois && Brody Schulke
//CSS 343 Professor Zander Lab 3 Spring Qtr 2015
//Djikstras using adjacency matrix
*/

//-------------------------------------------------------------------------//
//GraphM Class: Implementation of Dijkstra's algorithm using adjacency
//matrix. Builds graph using files, and uses the algorithm to determine
//shortest paths between nodes, using every node as a source node.

/*

Picture of the adjacency matrices used in this class
where ~ will be a weight value for the directed graph between 1 and INTMAX
This is the same structure for the T[][] as well, although extra values
such as path, dist, and visited will be represented as subscripts at each
matrix array index

C[][] Adjacency Matrix
|0 1 2 3 4 5 6 ... N
|1 0 ~ ~ ~ ~ ~ ~~~ ~
|2 ~ 0 ~ ~ ~ ~ ~~~ ~
|3 ~ ~ 0 ~ ~ ~ ~~~ ~
|4 ~ ~ ~ 0 ~ ~ ~~~ ~
|5 ~ ~ ~ ~ 0 ~ ~~~ ~
|6 ~ ~ ~ ~ ~ 0 ~~~ ~
|... ~~~~~~~~~~~~~~~
|N ~~~~~~~~~~~~~~~~~

*/

//-----------------------------------------------------------------//
//Implementation and Assumptions
//Implementation---------------------------------------------------//
//Features listed below and labeled with numbers
//in each method in the h and cpp files
//1 Construct a graph
// -Loops through T table and C matrix intializing values
//  appropriately
//2 Destruct a graph
// -Automatic de-allocation
//3 Build a Graph from a txt file
// -Reads from a text file to construct the C Matrix appropriately,
//  according to the text file and its values
//4 Insert an Edge
// -Inserts and edge into the C matrix, not allowing replacements
// -Does not allow weights of zero unless row and col are the same
//5 Remove an Edge
// -Removes edge if it exists in C matrix
//6 Display a graph
// -Pretty prints, displays GraphM and all related information
//  such as nodedata, nodes from and nodes to, distances, and paths
//  if the graph has not been built and is empty, the header will still print
//  stating Description FromNode ToNode Dijkstras Path and nothing more
//7 Display one line of a graph
// -Pretty prints, displays path and distance from specified node
//  to another specified node
//8 Dijsktra's Find Shortest Path Algorithm
// -Using greedy brute force, implements Dijkstra's pre-defined
//  shortest path algorith to find the shortest path between two
//  nodes if a path exists. Uses every single node as a source node
//
//Assumptions---------------------------------------------------//
//1 Assume size is never greater than 100 Nodes
//2 Automatic de-allocation, no assumptions
//3 Assumes all values in text file are properly formatted like so:
//
//int size
//string NodeData
//...
//string NodeData N
//int index fromNode (>1) int toNode (>1) and int weight (>0)
//...
//int index fromNode N (>1) int toNode N (>1) and int weight N (>0)
//
// Assumes that file contains no more than 100 elements
// Assumes that file terminates with '0 0 0'
//4 Assumes that user is not replacing edge, because implementation
// does not allow 
// Assumes weight and nodes are valid, following formatting requirements
//5 Assumes user is not trying to remove an edge outside of parameters
// Assumes user is removing an edge that DOES exist, cannot remove
// non-existing edge
//4, 5, If you want to replace an edge, one must first remove the edge
//then insert at the same spot.  Additionally, there is no way
//to change nodedata names unless specified in the text file
// Artificially removing edge by setting C[][] to INTMAX
//6 Assumes that findShortestPath has been called before calling
// displayAll, if the graph has been altered since the last time 
// findShortestPath has been called
// Assumes that the graph is built, otherwise nothing will print
//7 See number 6, same assumptions ^^^^^^^^^^^^
//8 Assumes that program is using an Adjacency matrix and T table
// both of size no greater than [101][101], for 1-based index, not 0
//-----------------------------------------------------------------//

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <iomanip>
#include <sstream>

//Variable for "infinity"
static const int INTMAX = 2147483647;
//Program specifications for max nodes, 1-based index
static const int MAXNODESPART1 = 101;

class GraphM
{
public:

	//1 Default constructor
	GraphM();
	//2 Destructor
	~GraphM();

	//3 buildGraph from input file using istream
	void buildGraph(istream&);

	//4 insertEdge with node from, node to, and cost
	bool insertEdge(const int, const int, const int);
	//5 removeEdge based on node from and node to
	bool removeEdge(const int, const int);
	
	//6 displayAll prints GraphM info.
	//  nodes, distances, paths etc. 
	void displayAll() const;
	//7 display prints one-line path of node from and node to
	void display(const int, const int) const;

	//8 findShortestPath uses Dijkstra's to update GraphM information
	void findShortestPath();

private:

	//structures---------------------------------//
	//TableType for T table
	//Stores subscripts for paths, visited test
	// and distance between nodes
	struct TableType
	{
		bool visited;
		int dist;
		int path;
	};
	//structures--------------------------------//

	//data for graph nodes info----------------//
	NodeData data[MAXNODESPART1];

	//Cost array for adj matrix
	int C[MAXNODESPART1][MAXNODESPART1];

	//number of nodes in graph
	int size;

	//Initialized is true after buildGraph has been called or
	// findShortestPath has been called
	// Insert, remove, and makeEmpty sets initialized back to false
	bool initialized = false;

	//Built is true if buildGraph has been called, or false if
	// makeEmpty is called
	bool built = false;

	//Stores visited, dist, path
	TableType T[MAXNODESPART1][MAXNODESPART1];

	//private methods below------------------------//
	//each method is a helper method
	//and has the public method's number 
	//corresponding to it

	//3 makeEmpty restores graph to initial state
	//  helper method of buildGraph
	void makeEmpty();

	//6 getPaths gets the paths using path subscripts of the T table
	// helper method for displayAll
	void getPaths(int, int, int) const;
	//7 displayOneLine gets paths and nodedata using subscripts
	//  of the T table
	// helper method for display
	void displayOneLine(int, int, int, stringstream&) const;

	//8 initializeT sets all T table to initial values
	//helper method for findShortestPath
	void initializeT();
	//8 dijkstras is the actual Dijkstra's algorithm
	// helper method for findShortestPath
	void dijkstras();
	//8 findSmallestWeightNotVisitedV finds the closes v node not
	//  yet visited
	// helper method for findShortestPath
	int findSmallestWeightNotVisitedV(const int) const;

	
};
#endif

