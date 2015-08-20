//Christopher DuBois
//CSS343
//Professor Zander
//Spring qtr 2015
//Lab 2, bintree
//---------------------------------------------------------------------------//
/*
BinTree class utilizes Nodes and the binary search
tree data structure to store NodeData (strings)

Methods are numbered ABOVE with comments so that assumptions, private
methods and public methods all have a number and a feature associated
the functions in the cpp file are also listed in this order

The Binary Search Tree is an abstract data type that is implemented here using
linked chains pointing left and right to the nodes of the tree which are
implemented following the binary search tree property which states:
//----------------------------------------------------------------
Binary Search Tree Property (left < parent && right > parent)
//----------------------------------------------------------------
measured by how the data stored in each node calculates < or >
Node is defined below in the private section as a struct.  This class is 
implemented using the recursive structure of the binary search tree and thus
all functions are defined with recursive facade helper methods

Here is an abstract representation of a binary search tree, without
data stored inside to show the BST Property. the ...'s represent continuation
as the recursive structure and pattern should be visible from this img

                           rootNode
                       /<-L |obj->| R->\                   |Rootobj|
                      /                 \
           |<-L | obj-> | R->|    |<-L | obj-> | R->|    |Lobj| |Robj|
             /             \        /              \
           ...            ...     ...             ...    ... ... ... ...
//
includes features:
0. Print a tree as an inorder traversal (left, parent, right)
1. Default Constructor, creates the tree and leaves the root as null
2. Copy Constructor, creates the tree using deep copies of the 
tree passed in as a parameter
3. Destructor, deletes the tree if the tree has not already been
nulled out
4. MakeEmpty, which completely empties the tree by deleting all it's nodes
5. A method isEmpty to check & see if the tree is empty or not
6. assignment operator= which follows the same methodology as 
the copy constructor, placing deep copies into the calling tree obj
7. equivalency and not equivalent operator== && operator!= determing if 
two trees are equal or not by checking each and every node in the tree
8. Insert a new NodeData object into the tree, not allowing for duplicates
9. Retrieve a NodeData object in the tree, returns false if not found
10. Get the height of a tree at a particular Node in the tree, assuming
the tree is a general binary tree
11. displaySideways, a method which prints the tree out how a tree might
actually be visualized (with left and right children spaced from the parent)
12. Turn a binary search tree into a sorted array
13. Turn a sorted array into a height balanced binary search tree
==============================================================================
Implementation and Assumptions
//----------------------------
Assumptions
//
// (3) destructor assume you cannot call the destructor and then 
//       operate on that same obj
// (8) does not make a deep copy of the nodedata being passed in
//       because it is assumed that the client wants to add
//       that specific node data object to the tree
//       not a copy
// (9) retrieve will return the NodeData object as NULL
//       not garbage if it was not found
// (9) retrieve returns a *& nodedata which could theoretically be altered
//       by the client if located in the tree because it hands the object
//       directly by parameter return
// (10) get height assumes that the tree is a general binary tree and so has a 
//       larger big O than a normal retrieve when searching for the node
//       to find the height of
// (10) get height assumes that a node that is found has an automatic 
//       height of 1 and each level below that node adds 1 to that height
// (13) turn a sorted array into a height balanced binary search tree
//      assumes that the array is given as sorted
//
Implementation
//
//0. In order traversal to print a tree out in a sorted 1 line order + \n
//1. The tree exists but is empty
//2. construct a new tree from the data stored in another tree, making deep
copies of each NodeData object, uses preorder traversal
//3. Recurse down, deallocate the left, the right, then the parent, unwind
//4. Recurse down, deallocate the left, the right, then the parent, unwind
//5. if root == NULL then the tree is empty else tree is not empty
//6. check to see if the trees are the same by address (if so, short circuit)
if the other tree is empty, then make calling tree empty else, copy each node
with deep copies using preorder traversal
//7. Check each and every node for equivalency (or not), short circuit if
one node is null and the other is not or if one node is not equivalent use
the logical !opposite of this for the != check
//8. Do not allow duplicates, add one node at a time by traversing down the
tree following the binary search tree property,  thus, if
object is > ... go right then recurse, if object is < ... go left then recurse
//9. Search for a particular node data in the tree by following the binary
search tree property and recursing down, if the object was found, a node
data object is returned by *& in the parameter, and a bool is returned true
otherwise, the NodeData* gets set to NULL and bool comes back false
//10. Get the height of general binary tree searches for the NodeData 
which has the height requested by looking through the entire tree, once the
nodedata has been found, get height recurses down, finding the max of each 
depth, either left or right
//11. Display sideways prints the right, prints space then prints parent
then prints left in order to simulate the apperance of how a binary 
search tree can be visualized
//12. fill an array in sorted array from a binary search tree, deleting the
binary search tree in place as it goes postorder traversal
//13. fill a binary search tree in height balanced order, deleting the stuff
inside the array as it goes preorder traversal and binary search logic
//
*/
//---------------------------------------------------------------------------//

#ifndef BINTREE_H
#define BINTREE_H
#include "nodedata.h"
class BinTree {
	//0 outstream operator, prints the tree in one line in sorted order
	//printing a \n at the end of the line
	friend ostream& operator<<(ostream&, const BinTree&);
public:
	//1
	BinTree(); // constructor, creates the tree, sets the root to NULL
	//2 creates the tree and makes deep copies of each node to place in the
	//constructed tree from the right operand const ref BinTree
	BinTree(const BinTree &); // copy constructor, creates the tree
	//3
	~BinTree(); // destructor, calls makeEmpty
	//4 this deletes and manages memory of all 
	void makeEmpty(); // make the tree empty so isEmpty returns true
	//5
	bool isEmpty() const; // true if tree is empty, otherwise false
	//6 makes deep copies of each node to place in the calling obj tree
	//from the right operand const ref tree
	BinTree& operator=(const BinTree &); // assignment operator
	//7 returns true if call BinTree obj has same structure and data
	//as the const ref BinTree
	bool operator==(const BinTree &) const; // equivalency operator
	//7 returns false if call BinTree obj has same structure and data
	//as the const ref BinTree
	bool operator!=(const BinTree &) const; // nonequivalency operator
	//8 inserts an entirely new node into the tree if not a duplicate
	//using the NodeData* passed in following BST Property
	bool insert(NodeData*); //
	//9 searches for a nodeData in the tree by using BST property to 
	//recursively search through the tree, returns bool if found, and
	//the NodeData ptr ref will be set to that NodeData located
	//this means the NodeData passed in could be altered by the client
	//as discussed in class on Weds Apr 15 if the data was not found, the node
	//data is set to NULL
	bool retrieve(const NodeData &, NodeData*&) const;
	//10 gets the height at a particular node in the tree, if it exists
	//does not follow BST property
	int getHeight(const NodeData &) const;
	//11 Professor defined, prints the tree in it's shape :) pretty prints 
	void displaySideways() const; // provided, displays the tree sideways
	//12 turns a binary search tree into a sorted array deleting the tree
	//in place in the process
	void bstreeToArray(NodeData* []);
	//13 takes an array and turns it into a height balanced binary search
	//tree (height balanced, everything is filled up to h-1)
	void arrayToBSTree(NodeData* []);

private:
	//-----------------------------------------------------------------//
	//Professor Defined inside this box (see the closing //---//)
	//comments added by me
	
	//The Node struct is a structure that allows the tree to link together
	//its branches and leafs through left and right pointers.  the Node struct
	//thus contains a left and a right pointer built into it, and also
	//contains a pointer to an object.  That is, a node contains an object
	//and has two different ways to iterate down the tree structure
	//here is an abstract representation of the Node 
	//------------------------
	//| l   |   o    |    r  |
	//| e   |   b    |   i   |
	//| f   |   j    |   i   |
	//| t   |   e    |   g   |
	//| <-  |   c    |   h   |
	//|     |   t->  |   t-> |
	//------------------------
	//where -> is the pointer to the next "thing" (either left, right, or obj)

	struct Node 
	{
		NodeData* data; // pointer to data object
		Node* left; // left subtree pointer
		Node* right; // right subtree pointer
	};
	
	//this node is the beginning of the tree, it stores a nodedata object
	// and a left and right pointer to the next nodes added to the tree
	//according to the binary search tree property
	Node* root; // root of the tree

	//this function was provided as a prototype but unused
	//void inorderHelper(...) const;
	
	//11
	void sideways(Node*, int) const; // provided, helper for displaySideways()

	//Professor defined inside this box
	//-----------------------------------------------------------------//

	// utility functions
	//methods below are labeled with an (n) to represent which method
	//labeled above that they are an assistant/helper for 

	//Destructor && makeEmpty Helper (3, 4)
	void DeleteTree(Node*);
	//operator== && operator != helper (7)
	bool equivRec(const Node*, const Node*) const;
	//operator= && copy constructor helper (2, 7)
	void copyRec(Node*&, const Node*);
	//insert helper (8)
	bool insertRec(NodeData*, Node*);
	//retrieve helper (9)
	bool rRec(const NodeData&, NodeData*&, const Node*) const;
	//ostream << helper (0)
	void printRec(ostream&, const Node*) const;
	//getHeight helper (10)
	int getHeightRec(const Node*) const;
	//getHeight locater helper (10)
	void locBTRec(const NodeData&, Node*&, Node*&) const;
	//binary search tree to array helper (12)
	void bsttaRec(NodeData*[], Node*, int&);
	//array to binary search tree helper (13)
	Node* atbstRec(NodeData*[], int, int);
};

#endif

