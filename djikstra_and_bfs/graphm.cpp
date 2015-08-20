//@Authors: Christopher DuBois, Brody Schulke
//CSS 343 Professor Zander, Spring Qtr 2015, Lab 3
//Brute Force dijkstras algorithm for an adjacency matrix

#include "graphm.h"
using namespace std;

//-------------------------------------------------------------------------//
//Constructor for GraphM class
//1
//
//the initialization here is unneccesary, but specified in the instructions
//the constructor for a graph sets the T[][] matrix to what is essentially
//null values as well as for the C Graph. 
//all indexes of T[][] will have weights of infinity, visits of false
//and paths of "nowhere" while the C Graph will have inifinities across the
//board as weights, except for on the diagonal where distances of 0
//will be placed (because it is known that to get from one node to itself
//the weight is 0), initialized will be set to true because the graph
//has technically been initialized and does not need to be reinitialized
//at n^2 if findShortestPath is called right away
GraphM::GraphM()
{
	//row loop controls the row of the T matrix and the C graph
	for (int row = 0; row < MAXNODESPART1; row++)
	{
		//col loop controls the column of the T matrix and the C graph
		for (int col = 0; col < MAXNODESPART1; col++)
		{
			T[row][col].dist = INTMAX;
			T[row][col].visited = false;
			T[row][col].path = 0;
			if (row == col)
			{
				C[row][col] = 0;
			}
			else
			{
				C[row][col] = INTMAX;
			}
		}
	}
	size = 0;
	initialized = true;
	built = false;
}

//-------------------------------------------------------------------------//
//Destructor for GraphM Class
//2
//
GraphM::~GraphM()
{
	//nothing to deallocate
	//the stackframe takes care 
	//of everything where there is no pointer
	//and/or dynamic memory allocation
}



//-------------------------------------------------------------------------//
//buildGraph
//3
//
//buildGraph using a text file to build a graph
//partially provided by professor
//with the format of the .txt being...
//---------------------------------------------------------------
//int size
//string NodeData
//...
//string NodeData N
//int index fromNode (>1) int toNode (>1) and int weight (>0)
//...
//int index fromNode N (>1) int toNode N (>1) and int weight N (>0)
//-----------------------------------------------------------------
//theoretically, the method could also "re"-build a graph with a new .txt
//loops through line by line reading information and breaks once
//"0 0 0" is typed as the delimiting line for the data to be stored in the
//graph.  sizes cannot be greater than 101 (for indexing 1-100) in the matrix
//if the weight of the graph in the txt file is less than 0 it is automatically
//set to INFINITY.  this method will also set the bool values for
//dijkstras algorithm to be implemented such that the graph is built, and
//initialized if not altered after this method is called
void GraphM::buildGraph(istream& infile) {

	if (built == true)
	{
		makeEmpty();
	}

	built = true;         //at this point, the graph has been "built"

	int fromNode, toNode, cost;          // from and to node ends of edge

	infile >> size;                    // read the number of nodes

	//want to return because size is over 101 invalid specifications
	if (size > MAXNODESPART1 || size <= 0)
	{
		return;
	}

	if (infile.eof()) return;          // stop if no more data

	string s;                         // used to read through to end of line
	getline(infile, s);

	// read graph node information
	for (int i = 1; i <= size; i++)
	{
		data[i].setData(infile);
		// read using setData of the NodeData class,
		// something like: 
		//    adjList[i].data.setData(infile);
		// where adjList is the array of GraphNodes and
		// data is the NodeData object inside of GraphNode
	}
	//initialized required to place here 
	//incase the stuff below the continue line never gets hit
	initialized = true;
	// read the edge data and add to the adjacency list
	for (;;)
	{
		infile >> fromNode >> toNode >> cost;

		if (cost < 0)
		{
			//cost is set to Infinity if set as bad
			cost = INTMAX;
			continue;
		}
		//assumes user will type in the delimiting line
		if (fromNode == 0 && toNode == 0 && cost == 0)
		{
			return; // end of edge data
		}
		//insertEdge also assumes you cannot set a Node's weight to be
		//0 if fromNode != toNode
		if (fromNode > 0 && fromNode <= size && toNode > 0 && toNode <= size
			&& cost > 0)
		{
			insertEdge(fromNode, toNode, cost);
		}
		// insert the edge into the adjacency list for fromNode
	}
	initialized = true;
	// needed here in case it breaks at a bad spot (because insert
	//edge sets initialized to false;
}

//-------------------------------------------------------------------------//
//makeEmpty
//3
//
//artificially makes the adjacency matrix to it's initial values
//unneeeded
void GraphM::makeEmpty()
{
	for (int row = 0; row < MAXNODESPART1; row++)
	{
		for (int col = 0; col < MAXNODESPART1; col++)
		{
			C[row][col] = INTMAX;
			T[row][col].dist = INTMAX; //predefined c++ max integer
			T[row][col].visited = false;
			T[row][col].path = 0;
		}
	}
	initialized = false;
	built = false;
}

//-------------------------------------------------------------------------//
//insertEdge
//4
//
//insert an edge into the C Graph
//this cannot replace an edge
//post: initialized is set to false and an edge has been added
//following proper size specifications to the C graph
bool GraphM::insertEdge(const int eF, const int eT, const int d)
{
	//eF = edgeFrom
	//eT = edgeTo
	//d = weight
	if (d < 0 || eF < 1 || eT < 1 || eF > MAXNODESPART1 || eT > MAXNODESPART1)
	{
		return false;
	}
	//since the C graph is set, add the edge.
	if (C[eF][eT] == INTMAX)
	{
		initialized = false;
		built = true;
		C[eF][eT] = d;
		return true;
	}
	//if trying to replace an edge, don't do it
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------//
//removeEdge
//5
//
//this method removes an edge from the C Graph if it is within valid
//size specifications (1-100) by setting the values to the
//"artificial nulled out" values.
//post: initialized is set to false and an edge within the matrix has been
//set to infinity
bool GraphM::removeEdge(const int eF, const int eT)
{
	//eF = edgeFrom
	//eT = edgeTo
	if (eF > 0 && eT > 0 && eF < MAXNODESPART1 && eT < MAXNODESPART1)
	{
		C[eF][eT] = INTMAX;
		initialized = false;
		return true;
	}
	else		//not within size specification
	{
		return false;
	}
}

//-------------------------------------------------------------------------//
//displayAll
//6
//
//displays all the information of the T graph
//pre: the graph has been built, you must call find shortest path
//before calling display all, otherwise two problems may occur
//either the graph will not have updated information, or if find shortest
//paths has never been called, it will print ---- everywhere
//post: nothing has been altered; columns are printed out displaying all
//the relevant information (after findShortestPath has been called)
//prints ---- in dijkstras col if there is no way to get 
//from one node to the next; prints "" in path col if there is no way to get
//from one node to the next; only prints from one node to node if 
//fromNode != toNode (because it is known that weights from one node to the
//same node is equal to 0 and the path is itself)
//calls a helper recursive method that gets the path "subscripts"
//by jumping through the T[][] adjacency matrix
void GraphM::displayAll() const
{
	//if the graph has never been built, there is nothing
	//to display
	if (built == false)
	{
		return;
	}
	//print the top line for column lines
	cout << "Description";
	cout << setw(25) << "From Node";
	cout << setw(10) << "To Node";
	cout << setw(13) << "Djikstra's";
	cout << setw(8) << "Path";
	cout << endl;
	//row loop controls the row to get to in the T[][]
	for (int row = 1; row <= size; row++)
	{
		cout << data[row];
		cout << endl;
		//col loop controls the column to get to in the T[][]
		for (int col = 1; col <= size; col++)
		{
			//because if row == col do nothing
			if (row != col)
			{
				cout << setw(33) << row;
				cout << setw(10) << col;
				if (T[row][col].dist == INTMAX)
				{
					cout << setw(12) << "----";
					cout << endl;
				}
				else
				{
					if (T[row][col].path == 0)
					{
						cout << T[row][col].path;
					}
					//recursively get the path subscripts
					else
					{
						cout << setw(12) << T[row][col].dist << setw(10);
						getPaths(row, col, col);
						cout << endl;
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------//
//getPaths
//6
//
//recursive private helper method to get path subscripts
//pre: the graph has been built
//post: printouts have been produced printing out the path subscripts
//stored in the T[][].path
void GraphM::getPaths(int eF, int v, int eT) const
{
	if (built == false)
	{
		return;
	}
	int vtx = 0;
	//if the path is equal to the edge from, just print out that number
	if (v == eF)
	{
		cout << v;
		return;
	}
	else
	{
		//go to the next path
		vtx = T[eF][v].path;
		//recursively call with the next path
		getPaths(eF, vtx, eT);
		//print out that path
		cout << setw(2) << v;
	}
}

//-------------------------------------------------------------------------//
//display
//7
//
//pre: findShortestPath has been called, and the graph has been built, all
//edges are within valid sizes, and the graph has not been messed with
//since it was built, if it has been messed with, this method will not
//print the most updated shortest path information
//post: a line containing the fromNode toNode, weight, and path trace
//has been printed, with NodeData's entered below is printed out, each
//on a new line.
//uses a recursive method to print out the subscripts and store the paths
//as it recursively loops through the matrix
//path names, prints "----" if there is no way to get to the node
//requested in the parameters
void GraphM::display(const int eF, const int eT) const
{

	if (built == false)
	{
		return;
	}
	//invalid sizes
	if (eF <= 0 || eT <= 0 || eF > size || eT > size)
	{
		return;
	}
	else
	{
		cout << setw(5) << eF << setw(5);
		cout << eT << setw(5);
		if (T[eF][eT].dist == INTMAX)
		{
			cout << setw(10) << "----";
			cout << endl;
			return;
		}
		else
		{
			cout << T[eF][eT].dist << setw(5);
			//use a string stream to add the information
			//as it passes through the nodedatas
			//rather than having to recurse back through
			stringstream s;
			displayOneLine(eF, eT, eT, s);
			cout << s.str();
			cout << endl;
		}
	}
}

//-------------------------------------------------------------------------//
//displayOneLine
//7
//
//recursive private helper method to get path names and path subscripts
//pre: the graph has been built
//post: printouts have been produced printing out the path names
//stored in the T[][].path
//otherwise, the exact same as above getPaths.
void GraphM::displayOneLine(int eF, int v, int eT, stringstream& s) const
{
	int vtx = 0;
	if (v == eF)
	{
		cout << v << setw(2);
		s << endl;
		s << data[v];
		return;
	}
	else
	{
		vtx = T[eF][v].path;
		displayOneLine(eF, vtx, eT, s);
		cout << v << setw(2);//data[v];
		s << endl;
		s << data[v];
	}
}

//-------------------------------------------------------------------------//
//findShortestPath
//8
//
//calls the real dijkstras algorithm
//after a series of checks
//ensures with the boolean value that the graph created was actually
//built before being called
//if the graph was not built the algorithm will not execute
//if the T graph has been altered in anyway since being initialized
//it will reinitialize all the T values appropriately
//according to the algorithm
//if the graph hasn't been messed with
//the algorithm automatically jumps in, and searches skipping initialization
//inefficiency,
//however, if the graph has been searched on multiple times
//without being altered, it still goes through the inefficiency of 
//finding the shortest path
void GraphM::findShortestPath()
{
	if (built == false)
	{
		return;
	}
	if (initialized == false && built == true)
	{
		//set all to infinity
		initializeT();
		//then find the paths
		dijkstras();
	}
	if (initialized == true && built == true)
	{
		//short circuit without having to reinitialize
		//saves on time
		dijkstras();
	}
}

//-------------------------------------------------------------------------//
//dijkstras
//8
//
//this is dijkstras algorithm for finding the shortest path in an adjacency
//matrix implementation, it is the brute force, original method N^3 is clear
//Pre conditions: The graph has been built, and the T[][] has been initialized
//to infinity for all weights, all visits as false, and all paths as 0
//post conditions: the C graph has been unaltered, but the T[][] weights
//have been altered to demonstrate the shortest paths from one node
//to the next node, the paths are recursively defined such that
//the shortest path can be printed by accessing the path "subscript" instance
//variable, and 1 to v-1 nodes have been marked as visited
void GraphM::dijkstras()
{
	//the src loop allows control of all the rows
	//in the T matrix
	for (int src = 1; src <= size; src++)
	{
		T[src][src].dist = 0;
		//the col loop follows the algorithm finding shortest paths for
		//1 to numVtxs -1
		for (int col = 1; col < size; col++)
		{
			//find the next vertex that is not visited 
			//and has the smallest weight
			//greedy algorithm
			int v = findSmallestWeightNotVisitedV(src);
			//v == -1 means there was not another next, so increment the loop
			if (v != -1)
			{
			//otherwise, mark the next vertex as visited to not visit again
				T[src][v].visited = true;
				//the w loop locates the next
				//"neighbor of neighbor vertex" that is not visited
				for (int w = 1; w <= size; w++)
				{
					//checking that it is a valid value
					//in the graph's C adjacency matrix
					if (T[src][w].visited == false && C[v][w] != INTMAX)
					{
						//T[w].dist = min(T[w].dist, C[v][w]
						//if the source to its neigbor + to it's neighbors
						//neighbor is less than the current distance
						//stored in sources W spot
						//set the value, and the path subscript
						//if not, do nothing
						if (T[src][v].dist + C[v][w] < T[src][w].dist)
						{
							T[src][w].dist = T[src][v].dist + C[v][w];
							T[src][w].path = v;
						}
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------//
//findSmallestWeightNotVisited
//8
//
//return -1 if the next v was not found 
//that is, if there was not another vertex in that row unvisited
//using a min checker and index return
//otherwise return the column index for the source row provided
int GraphM::findSmallestWeightNotVisitedV(const int srcRow) const
{
	int v = -1;
	int min = INTMAX;
	//this loop controls the column values from the source row passed in
	for (int col = 1; col <= size; col++)
	{
		//is the vertex being checked visited, and less than infinity
		if (T[srcRow][col].dist < min && T[srcRow][col].visited == false)
		{
			min = T[srcRow][col].dist;
			v = col;
		}
	}
	return v;
}

//-------------------------------------------------------------------------//
//initializeT
//8
//
//private helper method for dijkstras algorithm
//this sets all to infinity, including the source
//all indexes of T[][] will have weights of infinity, visits of false
//and paths of "nowhere", this method is used for djikstra's algorithm
//in the definition.
//precondition: the T matrix has been "altered" in some way and therefore
//must be called to follow dijkstras definition
//post condition: the T matrix has been "initialized" according to
//dijkstras algorithm, and the bool stored in the GraphM class is set to true
void GraphM::initializeT()
{
	//row loop controls the row of the T matrix
	for (int row = 0; row < MAXNODESPART1; row++)
	{
		//col loop controls the column loop of the T matrix
		for (int col = 0; col < MAXNODESPART1; col++)
		{
			T[row][col].dist = INTMAX;
			T[row][col].visited = false;
			T[row][col].path = 0;
		}
	}
	initialized = true;
}



