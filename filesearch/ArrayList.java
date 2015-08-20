package Hw5;

//Christopher DuBois
public class ArrayList {
	private Object[] list;
	private int numElem;

	public ArrayList(Object[] arr) {//array constructor
		int size = 0;
		for (int i = 0; i < arr.length; i++) {
			if (arr[i] != null) {//checks at every spot to determine numElem
				size++;
			}
		}
		this.numElem = size;
		this.list = new Object[size];
		for (int i = 0; i < size; i++) {
			this.list[i] = arr[i];//copies the arr into list
		}
	}

	public ArrayList(int length) {//constructor of arb length no elements less than 50k
		if (length < 50000) {
			this.numElem = 0;
			this.list = new Object[length];
		} else {
			System.out.println("QueueOverFlow");
			System.exit(-1);
		}
	}

	public ArrayList() {//no arg constructor
		int a = 100;
		this.numElem = 0;
		this.list = new Object[a];
	}
	
	public ArrayList(ArrayList o) {//copy constructor, and pulls the elements and copies them into this.list
		if (o == null) { throw new NullPointerException("My message"); }
		else {
			this.list = new Object[o.size()];
			for (int i = 0; i < o.size(); i++) {
				this.list[i] = o.get(i); 
			}
			this.numElem = o.size();
		}
	}

	public int size() {
		return this.numElem;//how many elements are in the array
	}

	public boolean isEmpty() {//if there are no elements in the array
		return numElem == 0;
	}

	private boolean isFull() {//checks to see if all the elements have something in it
		return numElem == this.list.length;
	}

	private void resize(int resizeValue) {//resizes it at a specific amount, and then copies into an array, and copies back with that new size allocation
		Object[] copyArr = new Object[resizeValue];
		for (int i = 0; i < this.numElem; i++) {
			copyArr[i] = this.list[i];
		}
		this.list = new Object[resizeValue];
		for (int i = 0; i < this.numElem; i++) {
			this.list[i] = copyArr[i];
		}
	}

	private void shiftRight(int shiftAtIndex) {//shiftright of a particular index to move elements over for an index insertion
		for (int i = shiftAtIndex; i < this.numElem; i++) {
			this.list[i + 1] = this.list[i];
		}
	}

	private void shiftLeft(int shiftAtIndex) {//same as above shiftleft index insertion
		for (int i = shiftAtIndex; i < this.list.length - 1; i++) {
			this.list[i] = this.list[i + 1];
			//this.resize(this.list.length);
		}
	}

	public void insert(Object o, int index) {//insert an object at a particular index
		if (o != null) {
			if (this.isFull()) {
				this.resize(numElem * 2);
				if (index < this.size()) {//if index in middle of the array
					this.shiftRight(index);
					this.list[index] = o;
				}
				if (index >= this.size()) {//if index is after the array
					this.resize(index + 1);
					this.list[index] = o;
				}
			} else {
				if (index < this.size()) {//if index in middle of array
					this.shiftRight(index);
					this.list[index] = o;
				}
				if (index >= this.size()) {//if index is after the array
					this.resize(index + 1);
					this.list[index] = o;
				}
			}
			numElem++;
		}
	}

	public void insert(Object o) {//calls the master insert, adds onto the end
		this.insert(o, this.numElem);
	}

	public Object remove(int index) {
		//remove something at a particular spot, return it and shift things over left to cover up the spot
		if (index >= this.numElem) { throw new NullPointerException("Cannot remove from a space that holds no data"); 
			//return "Error, cannot remove from nonexistence";
		} else {
			Object retVal = this.list[index];
			this.shiftLeft(index);
			this.list[this.list.length - 1] = null;
			numElem--;
			return retVal;
		}
	}
	
	public boolean equals(Object o) {//checks at lengths, then checks at each index
		if (o != null && o instanceof ArrayList) {
			ArrayList that = (ArrayList) o;
			if (this.list.length == that.list.length) {
				for (int i = 0; i < this.list.length; i++) {
					if (!this.list[i].equals(that.list[i])) {
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}
	
	public Object get(int index) {
		if (index < this.list.length) {//makes sure the index is inbounds
			return this.list[index];//returns that value
		}
		return "No File Path";
	}
	
	public int indexOf(Object o) {//searches for a particular object using the equals and iterating through the list
		if (o != null) {
			for (int i = 0; i < this.list.length; i++) {
				if (this.list[i].equals(o)) {
					return i;
				}
			}
		}
		return -1;
	}

	@Override
	public String toString() {//standard to string, plus also tells the index
		String retVal = "Pathname list and index [";
		for (int i = 0; i < this.list.length; i++) {
			if (this.list[i] != null) {
				retVal += this.list[i] + "(index = " + i + ")" + ",";
			}
		}
		return retVal + "]";
	}

}