#include "bintree.h"
//Christopher DuBois
//BinTree Implementation
//CSS 343 Spring Qtr
//Professor Zander
//Lab 2
//Recursive helper methods are attempted to be placed next to eachother
//but the cpp file follows the "order" numbered in the .h file
//and thus operator= is not placed next to it's recursive helper


//---------------------ostream<< operator (0)---------------------------------
//console printer function
//ensures the tree is not empty before trying to print
//promises not to alter the right operand
//uses recursive inorder traversal and prinnts the endl for the tree
ostream& operator<<(ostream& os, const BinTree& print)
{
	if (print.isEmpty())
	{
		return os;
	}
	else
	{
		print.printRec(os, print.root);
		os << endl;
		return os;
	}
}

//---------------------Recursive ostream<< helper----------------------------
//console printer recursive helper function
//loops through the tree using inorder traversal to print node data 
//as long as it exists (left, print, right)
void BinTree::printRec(ostream& os, const Node* cur) const
{
	if (cur == NULL)
	{
		os << "";
	}
	if (cur->left != NULL)
	{
		printRec(os, cur->left);
	}
	if (cur != NULL)
	{
		os << *cur->data << " ";
	}
	if (cur->right != NULL)
	{
		printRec(os, cur->right);
	}
}

//---------------------Default Constructor (1)--------------------------------
//automatically sets the root to null if the tree is constructed
//the tree will return as empty if checked after just being initialized
//the line before
BinTree::BinTree()
{
	root = NULL;
}

//---------------------Copy Constructor (2)-----------------------------------
//copies another tree into a calling tree object
//promises not to alter the right operand BST object
//calls a preorder traversal copy recursive helper method
BinTree::BinTree(const BinTree& clone)
{
	root = NULL;
	copyRec(root, clone.root);
}

//---------Copy Constructor/operator= recurisve helper---------------------
//uses preorder traversal to create deep copies of a node from one tree
//to the calling tree creates parents and then the left and right children
void BinTree::copyRec(Node*& thisCurrent, const Node* cloneCurrent)
{
	if (cloneCurrent != NULL)
	{
		Node* toAdd = new Node; //deep copy
		toAdd->data = new NodeData(*cloneCurrent->data); //deep copy
		thisCurrent = toAdd;
		copyRec(thisCurrent->left, cloneCurrent->left);
		copyRec(thisCurrent->right, cloneCurrent->right);
	}
	else    // otherwise we've reached the end of the tree
	{
		thisCurrent = NULL;
		return;
	}
}

//-----------------------Destructor (3)-------------------------------------
//if the tree has already been Nulled out, then don't try deleting it
//otherwise, deletes the tree using post order traversal (left, right, parent)
BinTree::~BinTree()
{
	makeEmpty();
}

//-----------------------makeEmpty (4)---------------------------------------
//if the tree has already been nulled out, then don't try deleting it
//otherwise, this method deletes the tree with a helper post order
//traversal method
void::BinTree::makeEmpty()
{
	if (root == NULL)
	{
		return; //dont try deleting if it's already empty
	}
	DeleteTree(root);
	root = NULL;
}

//---------------------Delete Tree-----------------------------------------
//delete tree recursive helper method for makeEmpty and Destructor
//post order traversal, delete all the way down to the left, then all the way
//down to the right, then the parent node
void BinTree::DeleteTree(Node* current)
{
	if (current != NULL)
	{
		DeleteTree(current->left); 
		//delete left then right then parent because otherwise we will
		//have memory leaks because of no access to the tree links
		DeleteTree(current->right);
		//fully delete and NULL out everything
		delete current->data;
		current->data = NULL;
		current->left = NULL;
		current->right = NULL;
		delete current;
		current = NULL;
	}
}

//---------------isEmpty (5)--------------------------------------------------
//checks if the tree is empty because BinSTree will always have a root if not
//empty, const promises not to alter the tree in the process
bool BinTree::isEmpty() const
{
	return root == NULL;
}

//---------------------operator= (6)----------------------------------------
//assignment operator
//utilizes the same preorder traversal method as the copy constructor
//to deep copy nodes into the calling tree
//entry point checks for same addresses or empty right operand tree
//promises not to alter the right operand tree
BinTree& BinTree::operator=(const BinTree& clone)
{
	if (this == &clone) //if the addresses are the same == same tree
	{
		return *this;
	}
	else if (clone.root == NULL) //if the other tree is empty, simulate this
	{
		makeEmpty();
		root = NULL;
		return *this;
	}
	else
	{
		makeEmpty(); //otherwise, clear the tree of the data that exists
		//and make deep copies from the other tree
		root = NULL;
		copyRec(root, clone.root);
		return *this;
	}
}

//---------------------operator== (7)---------------------------------------
//equivalency operator
//entrypoint checks for treese both being empty, one empty one not, and 
//both not empty
//else do a recursive helper method checking each and every node
//for equivalency
bool BinTree::operator==(const BinTree& operand) const
{
	if (this == &operand) //if the addresses are the same, equvialent
	{
		return true;
	}
	if (root == NULL && operand.root == NULL)
	{
		return true;//if they are both null, empty trees are equivalent
	}
	else if (root != NULL && operand.root != NULL)
	{
		return equivRec(root, operand.root); //check each and every node
		//for equivalency
	}
	else
	{
		return false;
	}
}

//---------------------operator!= (7)-----------------------------------------
//logically return the opposite of the == operator
bool BinTree::operator!=(const BinTree& operand) const
{
	return (!(*this == operand));
}

//---------------------Recursive == Helper------------------------------------
//recurisve helper method for equivalency
//goes all the way to the left and all the way to the right, checking each node
//starting with the roots as they are passed in
//if any node is not equivalent, in null value or value, automatically return 
//false
bool BinTree::equivRec(const Node* sourceNode, const Node* operandNode) const
{
	if (sourceNode == NULL && operandNode == NULL) //wind up
	{
		return true;
	}
	else if (sourceNode != NULL && operandNode != NULL) //recurse further
	{
		if (*sourceNode->data == *operandNode->data) 
		{
			equivRec(sourceNode->left, operandNode->left);
			equivRec(sourceNode->right, operandNode->right);
		}
	}
	else //this means the structure of the tree was not the same
	{
		return false;
	}
}

//---------------------Insert NodeData (8)------------------------------------
//Insert an entirely new node into the tree
//does not allow duplicates into the tree
//uses an algorithm that falls deeper into the tree according to 
//the binary search tree property
//left is less than parent, right is greater than parent
//so it will go down until it's in the right spot then link 
//the new nodedata in
//does so utilizing a recursive insert method
//adding the root in first
//does not make a deep copy of the node data because
//we are assuming the client wants to add that exact object to the tree
bool BinTree::insert(NodeData* toAdd)
{
	if (root == NULL) //if the tree is already empty, just make the root
	{
		Node* add = new Node;
		add->data = toAdd;
		add->left = NULL;
		add->right = NULL;
		root = add;
		return true;
	}
	else
	{
		if (insertRec(toAdd, root)) //use BST Property to find data spot
		{
			return true;
		}
		return false;
	}
}

//---------------------Insert Recursive Helper---------------------------------
//does not allow duplicates
//recursive method falls down the tree to the right spot
//going left if the object being added is less than the spot in the 
//tree being looked at
//if the insert did not occur for siome reason returns false
bool BinTree::insertRec(NodeData* add, Node* current)
{
	if (*add == *current->data) // no duplicates
	{
		return false;
	}
	else if (*add < *current->data) // BST prop go to the left
	{
		if (current->left == NULL) // if we're at the right spot
		{
			Node* toAdd = new Node;
			toAdd->data = add;
			toAdd->left = NULL;
			toAdd->right = NULL;
			current->left = toAdd;
			return true;
		}
		else
		{
			return insertRec(add, current->left); // keep going
		}
	}
	else if (*add > *current->data) // bst Prop
	{
		if (current->right == NULL)
		{
			Node* toAdd = new Node;
			toAdd->data = add;
			toAdd->left = NULL;
			toAdd->right = NULL;
			current->right = toAdd;
			return true;
		}
		else
		{
			return insertRec(add, current->right); // keep going
		}
	}
	else //it won't ever hit this case
	{
		return false;
	}
}

//---------------------Retrieve NodeData (9)---------------------------------
//retrieve looks for a particular copy of the NodeData string inside
//the tree, comparing the nodedata values at each node
//uses a recurisve helper that optimizes on the binary search tree property
//to go left or right according to the value of the node Data compare
//return value, that is, if the NodeData object is > the NodeData 
//being looked at in the tree, the algorithm will go to the right
//rinse and repeat
//if nothing is found, we return false, and the NodeData object 
//passed back as the return value through the parameter 
//gets set to a NULL value
bool BinTree::retrieve(const NodeData& toFind, NodeData*& returner) const
{
	if (&toFind == NULL)
	{
		return false;//if the node data is nothing
	}
	if (isEmpty())
	{
		returner = NULL;//set return to null NOT GARBAGE
		return false;
	}
	bool ret = rRec(toFind, returner, root);
	if (ret == false)
	{
		returner = NULL;//set return to null not garbage
	}
	return ret; //true if located false if not found
}

//---------------------Recursive Retrieve Helper------------------------------
//retrieve recursive helper
//looks for the NodeData loc and returns that NodeData if found
//via a *& parameter, it will remain garbage if not found in this method
//promises not to alter the node data being searched for in the tree
//as well as any of the nodes in the tree
//uses a bool return value to determine if found as well
bool BinTree::rRec(const NodeData& loc, NodeData*& ret, const Node* cur) const
{
	if (cur == NULL) // base case 
	{
		return false;
	}
	else
	{
		if (*cur->data == loc) //located, set the parameter return val
			// and return true
		{
			ret = cur->data;
			return true;
		}
		else if (*cur->data > loc) //bst prop keep going
		{
			rRec(loc, ret, cur->left);
		}
		else //if (*cur->data < loc) //bst prop keep going
		{
			rRec(loc, ret, cur->right);
		}
	}
}

//----------------getHeight (10)---------------------------------------------
//gets the height at a particular node in a tree
//does not assume this is a binary search tree so search is for an unordered
//binary tree
//if a node is not found, height is 0
//if the tree does not exist height is 0
//if the node is located and is a leaf, height is 1
int BinTree::getHeight(const NodeData& sourcePoint) const
{
	if (isEmpty()) //the tree has nothing so no height
	{
		return 0;
	}
	else if (*root->data == sourcePoint) //start directly at the root
	{
		return getHeightRec(root);
	}
	else
	{
		//start the search at the root
		Node* cur = root;
		Node* ret = NULL;
		//ret will be NULL if the node was not found
		locBTRec(sourcePoint, cur, ret);
		if (ret == NULL)
		{
			return 0;
		}
		//the node was found, so start calculating it's height
		return getHeightRec(ret);
	}
}

//------locate in an unordered tree recursive helper for get height-----------
//this algorithn does not assume that the binary tree is a binary search
//tree, so it theoretically has to look through every node stored in the
//tree until the Node is located.  it will return the Node where the data 
//was found if located through a parameter *& value, and remains unchanged
//if not located
//go left and go right
void BinTree::locBTRec(const NodeData& k, Node*& cur, Node*& ret) const
{
	//leaf
	if (cur == NULL)
	{
		return;
	}
	//found
	if (*cur->data == k)
	{
		ret = cur;
		return;
	}
	//check all the nodes for a general binary tree
	locBTRec(k, cur->left, ret);
	locBTRec(k, cur->right, ret);
}

//----------------getHeight Recursive Helper-----------------------------
//if the node was found in the tree for get height at a particular NodeData
//then this node finds the height at both the right and left nodes, and
//returns the larger of the two
//if the nodedata was found in the tree, the height is automatically 
//set to a value of 1, and continues adding from there as the height increases
//example
//if d was searched for in the tree below, the height will return as 3
//       f
//d----<
//       b-----<
//               a
int BinTree::getHeightRec(const Node* cur) const
{
	if (cur == NULL)
	{
		return 0;
	}
	else
	{
		int lH = getHeightRec(cur->left); //get the height of the left
		int rH = getHeightRec(cur->right); //get the height of the left
		//writing a recursive function for BST we can think of every node
		//as a subtree so we loop through the tree and add 1 for the
		//source point because the recursion will wind up
		//if the height is 2 at the left and 3 at the right, from Node
		//src, which is to the left of the root, we want to return up 4 to
		//add 1 for the src
		if (lH > rH)
		{
			return lH + 1;
		}
		else
		{
			return rH + 1;
		}
	}
}

//----------------------displaySideways (11)----------------------------------
//professor supplied
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}

//-------------------display sideways recurisve helper-----------------------
//professor supplied
//hits right node first, then prints space, then
//prints the parent node then prints the left node
void BinTree::sideways(Node* current, int level) const
{
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;   // display information of object
		sideways(current->left, level);
	}
}

//----------------bstreeToArray (12)------------------------------------------
//this method will convert a binary search tree into a sorted array
//and delete the the tree structure in process, (in place)
//if the tree is already empty, the nodedata array remains the same
//otherwise, the algorithm fills the array in sorted order by traversing
//the tree with a recursive helper method
void BinTree::bstreeToArray(NodeData* toFill[])
{
	//nothing to convert
	if (isEmpty())
	{
		return;
	}
	else
	{
		int i = 0;
		//fill up the array from the tree and delete the tree stuff
		bsttaRec(toFill, root, i);
		//make sure the tree is empty
		root = NULL;
	}
}

//----------------bstreeToArray Recursive Helper------------------------------
//Loop through the tree, visiting left, then parent, then right
//and place the NodeData in the array by altering the pointer
//then delete the nodes in the order of left, right, parent, postorder
void BinTree::bsttaRec(NodeData* fill[], Node* cur, int& i)
{
	if (cur == NULL)
	{
		return;
	}
	else
	{
		//fill in sorted order, so add in all the lefts
		//then add in all the parents, then add in the rights
		//because of BST property and the structure of the BinTree
		bsttaRec(fill, cur->left, i);
		//"repoint" the data by setting poiinters equal to eachother
		//because it is inefficient to make an entirely new NodeData
		//for no reason since the BST is being deleted in the process
		fill[i++] = cur->data;
		bsttaRec(fill, cur->right, i);
		cur->left = NULL;
		cur->right = NULL;
		delete cur;
		cur = NULL;
	}
}

//---------------arrayToBSTree (13)-------------------------------------------
//this method will take a sorted array and create a height balanced
//binary search tree from that array using a recurisve helper method
//that follows similar logic to the binary search algorithm (low, mid, high)
//it first determines the size of the array then ensures that the calling
//tree data structure object is completely empty, then fills from there
//with the recursive helper, and deletes the nodes in the array in the process
void BinTree::arrayToBSTree(NodeData* fillFrom[])
{
	// the directions here said that knowing the size was not necessary
	//because the size is not necessary, however, I believe knowing the size
	//is necessary because the binary search algorithm discussed in class
	//only works by predetermining the exact size;
	int size = 0;
	while (fillFrom[size] != NULL)
	{
		size++;
	}
	//there is nothing to make a tree from
	if (size == 0)
	{
		return;
	}
	//the tree needs to be empty to convert
	if (root != NULL)
	{
		makeEmpty();
	}
	//make the tree using binary search logic of a sorted array
	else
	{
		root = atbstRec(fillFrom, 0, size -1); // size - 1 for array indexing
	}
}

//----------------Recursive arrayToBSTree Helper--------------------------
//this method follows similar logic to binary search, using a sorted array
//and indexing as parameters to fill the binary tree
//because the array is sorted, it can use the middle in each direction
//to fill the tree, that is, the root is the middle of the array
//the left is the middle from 0 to middle-1 and the right is the middle from
//middle + 1 to the size of the array, this algorithm iterates recursively
//to empty out the array in the process and fill the tree
BinTree::Node* BinTree::atbstRec(NodeData* ff[], int low, int high)
{
	//the int parameters
	//must be within the range of the array and not overlap eachother
	if (low > high)
	{
		return NULL;
	}
	//start at the middle to height balance 
	int mid = (low + high) / 2; 
	//double check incase size had to be removed
	if (ff[mid] == NULL)
	{
		return NULL;
	}
	//make an entirely new node to be added to the tree
	Node* cur = new Node;
	//inefficient to allocate an entirely new NodeData
	//just "repoint" it (not actually repointing it just setting pointers
	//equal to eachother
	cur->data = ff[mid];
	cur->left = atbstRec(ff, low, mid - 1);
	cur->right = atbstRec(ff, mid + 1, high);
	return cur;
}
