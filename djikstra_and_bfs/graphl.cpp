#include "graphl.h"

// ---------------------------------------------------------------------------
//Constructor
//1
//
//Default constructor for class GraphL
//initializes the graph by sizing it
//to allow for indexing 1-100
//and sets each graphnodes head to null
//for the adjacency list
GraphL::GraphL()
{
	for (int i = 0; i < MAXNODESPART2; i++)
	{
		adjList[i].edgeHead = NULL;
	}
	size = 0;
	built = false;
}

// ---------------------------------------------------------------------------
//Destructor for class GraphL
//2
//
//Calls makeEmpty to dellocate the dynamic memory
//stored in the adjacency list
GraphL::~GraphL()
{
	makeEmpty();
}

// ---------------------------------------------------------------------------
//makeEmpty
//2,3
//
//Helper function for destructor
//Also used by buildGraph
//this method deallocates memory stored in the adjacency list for graphL
//by looping through the entire array, stepping into each list stored
//at an index in the array
//pre: the graph has been built
//post: the graph, and all of it's data has been destroyed and removed
//from memory
void GraphL::makeEmpty()
{
	//if there is nothing to delete don't try
	if (size == 0)
	{
		return;
	}
	//Loop through the entire array
	//start at 1 because 0 is padded and never added to
	for (int i = 1; i <= size; i++)
	{
		//While the edgeHead of the current index is not NULL
		while (adjList[i].edgeHead != NULL)
		{
			EdgeNode* cur = adjList[i].edgeHead;
			//If cur is not null, set temp pointer to cur and cur to nextEdge
			//Delete temp and set temp to null, and make the edgeHead cur
			if (cur != NULL)
			{
				EdgeNode* temp = cur;
				cur = cur->nextEdge;
				delete temp;
				temp = NULL;
				adjList[i].edgeHead = cur;
			}
		}
		adjList[i].data = NodeData("");
	}
	size = 0;
	return;
}

// ---------------------------------------------------------------------------
//buildGraph
//3
//
//Builds GraphL by reading from a txt file
//if the graph has already been built, it will call make empty to 
//rebuild the graph
//pre: a graph was "constructed"
//post: the graph has been "built" in that
//stuff is actually stored according to the data entered from the txt
//file into the adjacency list
//data is always entered in the format
//------------------------------
//int size
//Nodedata string
//...
//Nodedata string N
//int fromNode int toNode
//...
//int fromNode N int toNode N
void GraphL::buildGraph(istream& infile) 
{
	int fromNode, toNode;        // from and to node ends of edge
	if (size > 0)
	{
		makeEmpty();		 // clear the graph of memory 
	}
	                     
	built = true;
	infile >> size;                    // read the number of nodes
	if (infile.eof()) return;          // stop if no more data

	string s;                     // used to read through to end of line
	getline(infile, s);

	// read graph node information
	for (int i = 1; i <= size; i++) {
		adjList[i].data.setData(infile);
	}

	// read the edge data and add to the adjacency list
	for (;;) {
		infile >> fromNode >> toNode;
		//Signals end of input data
		if (fromNode == 0 && toNode == 0)
		{
			return;
		}
		//Insert the edge if not the end of input data
		if (fromNode > 0 && fromNode <= size && toNode > 0 && toNode <= size)
		{
			insertEdge(fromNode, toNode);
		}
	}
}

// ---------------------------------------------------------------------------
//insertEdge
//3
//
//private helper method for build graph
//Inserts and edge into the graph, given edge From and edge To (eF and eT)
//pre: a graph has been constructed
//post: a new edge has been added if within the valid sizes of the adj list
//this method will always insert new edges at the beginning of the adj list
//duplicates are allowed as they will be added to the front of the list
//at the array index
bool GraphL::insertEdge(const int eF, const int eT)
{
	//If there is no edgeHead, create one
	if (adjList[eF].edgeHead == NULL)
	{
		adjList[eF].edgeHead = new EdgeNode;
		adjList[eF].edgeHead->adjGraphNode = eT;
		adjList[eF].edgeHead->nextEdge = NULL;
		return true;
	}
	//Otherwise insert edge into the beginning of the list
	//the edge is always inserted at the beginning following
	//program specifications and simplicity
	else
	{
		EdgeNode* ins = adjList[eF].edgeHead;
		adjList[eF].edgeHead = new EdgeNode;
		adjList[eF].edgeHead->adjGraphNode = eT;
		adjList[eF].edgeHead->nextEdge = ins;
		ins = NULL;
		return true;
	}
	return false;
}

// ---------------------------------------------------------------------------
//displayGraph
//4
//
//Displays information related to all aspects of graph
//Includes existing edges and names of Nodes
//will print out the Node and it's related edges that it has links to
void GraphL::displayGraph() const
{
	cout << "Graph:\n";
	//Loop through every Node 
	for (int src = 1; src <= size; src++)
	{
		cout << "Node " << src << "        " << adjList[src].data << "\n";
		EdgeNode* cur = adjList[src].edgeHead;
		//While there is an existing edge, print out its information
		//Increment cur to nextEdge after printing 
		while (cur != NULL)
		{
			cout << "    " << "edge " << src << setw(2) << 
				cur->adjGraphNode << "\n";

			cur = cur->nextEdge;
		}
		cur = NULL;
	}
}

// ---------------------------------------------------------------------------
//depthFirstSearch
//5
//
//Prints out depth-first search ordering of the graph
//Calls helper function dfs
//Also calls helper function markAllAsUnvisited
void GraphL::depthFirstSearch()
{
	//Mark every node as unvisited for the function to work properly
	markAllAsUnvisited();
	cout << "\nDepth-first ordering:";
	//Loop through every node
	//Call dfs is the current node has not been visited
	for (int v = 1; v <= size; v++)
	{
		if (adjList[v].visited == false)
		{
			dfs(v);
		}
	}
	//print a new line to end the depth first ordering display
	cout << "\n";
}

// ---------------------------------------------------------------------------
//dfs
//helper function for depthFirstSearch
//5
//
//Takes an index of a node as an argument
void GraphL::dfs(const int v)
{
	//Mark the node at current index as visited
	adjList[v].visited = true;
	//print the node entered
	cout << " " << v;
	EdgeNode* cur = adjList[v].edgeHead;
	int w;
	//While there are edges to check
	while (cur != NULL)
	{
		w = cur->adjGraphNode;
		//Call dfs, passing in w, if the node at index w has not been visited
		if (adjList[w].visited == false)
		{
			dfs(w);
		}
		cur = cur->nextEdge;
	}
}

// ---------------------------------------------------------------------------
//markAllAsUnvisited
//5
//
//helper function for depthFirstSearch
void GraphL::markAllAsUnvisited()
{
	//Loops through all nodes, marking each as visited
	//starts at 1 because index 0 is padded
	for (int v = 1; v <= size; v++)
	{
		adjList[v].visited = false;
	}
}

