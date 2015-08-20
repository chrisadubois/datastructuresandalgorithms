package hw5;

public class List {
	private Node head = null;//initialize the beginning of the list as null

	public List() {//create a list with the beginning being null
		head = null;
		// nodeNum = 0; //this would decrease the big o any time size is called
	}
	
	public int searchAndDelete(Object o) {
		int search = -1;
		if (o != null) {//if it's real
			search = this.indexOf(o);//find it, or return -1 if not
			this.remove(search);//remove it at that index
		}
		return search;
	}
	
	public void clear() {
		for (int i = this.size(); i >= 1; i--) {//remove starting at the tail and work the way back (this is important because if something is unhooked at the beginning
			this.remove(i);//then the rest to the right are unhooked and the addresses are lost, however, something might still be pointing to a middle index Node
		} //this works
		
		//while (head.next != null) {
			//head.next = null;
		//}
		//head = null;//this works too
	}

	public Object remove(int index) {
		Object retVal = null;//always the object to return will start as null
		if (index <= 0) {//makes sure input is correct
			throw new LinkedListException("cannot remove from an index <= 0/empty");
		}
		if (index > 0) {//as long as the index is greater than 0
			if (this.isEmpty()) {//makes sure the list isn't empty already
				throw new LinkedListException("can't remove from empty");
				//return retVal;
			} else if (this.size() == 1) {//if the size is 1 (special case)
				retVal = head.data;//the returning object is the head
				head = null;//now the list is empty
				return retVal;
			} else {
				if (index > this.size()) {//if the index is bigger than the size of the linked list, you can't remove from it
					throw new LinkedListException("Cannot remove from a nonreal index");
					//return retVal;
				} else {//if removing from the first index (1 based list)
					if (index == 1) {
						retVal = head.data;//the returning value is simply the head
						head = head.next;//now head is equal to the link that was ahead of it. so it is the new head of the list and head.next is the third
						return retVal;
					} else { //for every other body case
						Node a = head;//start at the begininng
						for (int i = 1; i < index - 1; i++) {//end at the index just before the one to be removed
							a = a.next;//and set the one right before to be removed to point to the one skipping after the one being removed 
						}
						retVal = a.next.getObject();//sets the return to the one being orpahned
						a.next = a.next.next;//stitches by jumping over one node and tying a new link
						return retVal;
					}
				}
			}
		}
		return retVal;
	}

	public void insert(Object o, int index) {
		if (o == null) {//user input check
			throw new LinkedListException("cannot add null to the list");
		}
		if (index > 0) {//as long as it's a valid index
			if (head == null) {//if there was nothing at the head, add it and make it the head
				head = new Node(o, null);
			//} else if (head != null && head.next == null) {//might be unnecessary? yes unnecessary
				//head.next = new Node(o, null);//might be unnecessary? yes unnecessary
			} else {
				if (index == 1) {//adding to the first index (the head)
					Node u = new Node(o, head);//change the head to the new Object
					head = u;
				} else if (index > size()) {//if the index is bigger than the size of the list, add it to the tail
					Node a = new Node(o, head);//start at the head, a is a node containing the object o, pointing to the head (sort of like index 0)
					while (a.next != null) {//traverse the links
						a = a.next;//
					}
					Node j = new Node(o, null);
					a.next = j;//add at the last index 
				} else if (index <= size()) {//if adding to the middle
					Node a = new Node(o, head);//start at the one before head, data object is o and the next node is head
					for (int i = 0; i < index - 1; i++) {//get to the index just before what needs to be shifted over because head is spot 1 while a is previously spot 0
						a = a.next;
					}
					Node j = new Node(o, a.next);//set an entirely new node equal to the data of the object being passed in, and the node reference equal to the index - 1's node pointer
					a.next = j;//stitch together here the index -1 now points to a new square with object o and node that was of index, which then points to the indexes previous node thinger
					//which further points ahead in the links
				}
			}
		} else {//disallows any bad user input
			throw new LinkedListException("Must enter a number > 0 to insert, this Linked List has 1-based counting, not 0 based");
		}
		// nodeNum++;
	}
	
	public void insert(Object o) {//second insert method, simply calls the bulky insert method
		if (o == null) {
			throw new LinkedListException("cannot add null to the list");
		} else {
		insert(o, this.size()+1);
	}
	}
	
	public String toString2() {//recursive toString
		Node a = head;//start at the head
		if (a == null) {//if empty
			return "Empty List";
		} else {
		return recToString(a); 
	}
	}
	
	public int size2() {//recursive size
		return size2(head);
	}
	
	private int size2(Node start) {  //notice change in header 
	int retVal = 0;
	if (start.next!=null) {//iterate through until 1 left
		retVal = 1 + size2(start.next);//add one each time
	} else {
		retVal =+ 1;//add one for the final Node uncounted 
	}
	return retVal;
	}
	
	private String recToString(Node a) {
		String retVal = "";//empty
		Node k = a;//node passed in is the head
		if (k.next != null) {//if the next elements are not null
			retVal += k.getObject() + "-->" + recToString(k.next);//the object at the next node + the object at the next node until it's 1 away from null
		} else {
			retVal +=(String) k.getObject();//add in the last value that has not been caught
		}
		return retVal;
	}

	public String toString() {
		String retVal = "linkHead[";//pretty prints
		Node current = head;//make the node the first head node
		int i = 0;//incrementer variable
		while (current != null) {//as long as the next link isn't null
			i++;//pretty prints
			retVal += current.data + "," + "(index = " + i + ") --> ";//add the nodes information + pretty prints
			current = current.next;//move to the next link
		}
		return retVal + "]linkTail";//pretty prints
	}

	public int size() {
		int counter = 0;//variable to keep track as the links are traversed
		Node a = new Node(null, head);//set to head
		while (a.next != null) {//walk across the chains
			counter++;//increment the counter
			a = a.next; //the node a is equal to the next nodes stuff in the links
		}
		return counter;
	}

	public boolean isEmpty() {//if there's nothing in the list which will ONLY happen if the beginning of the list is null
		return head == null;
	}

	public int indexOf(Object target) {//take the object to look for
		Node location = head;//set the beginning to start from as the head
		Object lookingFor;
		for (int i = 1; i <= size(); i++) {//for the length of the list
			lookingFor = location.getObject();//the object to compare is equal to the data at each node
			if (lookingFor.equals(target)) {//for free equals method
				return i;//if something has been found as equal, return the i index
			}
			location = location.next;//step to the next link for further comparisons
		}
		return -1;//returns the negative index if nothing was found
	}
	
	public Object get(int index) {
		int size = this.size();//so it doesn't run size twice and take a lot of time
		if (index > size) {
			throw new LinkedListException("Cannot get an object outside of the size of the list, the size of the list is " + size);
		} 
		Object retVal = null;//basic Object return for the worst case
		Node finder = head;//start as the head node
		int i = 1;//counter for 1 based LL
		while (finder != null) {//at each spot
			if (i == index) {//checks the counter against the search argument
				return finder.data;//return the object at that spot
			} else {
				finder = finder.next;//otherwise move to the next spot
				i++;//and increment count
			}
		}
		return retVal;//if it's never returned from finder.data (
	}
	

	private class Node {//never make a class like this ever again according to Professor Nash
		Object data;//stores the object in the node
		private Node next;//possible recursive class?

		public Node(Object o, Node n) {//initialize the variables
			data = o;
			next = n;
		}

		private Object getObject() {//semi-useful method to pull strictly the data out of the node
			return data;
		}
	}
}
