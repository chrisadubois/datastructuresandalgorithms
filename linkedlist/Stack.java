package hw5;

public class Stack extends List {//inherits everything from list except adds and removes differently

	public Stack() {//creates a list 
		super();
	}
	
	public void push(Object o) {//insert every time at the very beginning of the list(the head) i.e., add "b" b goes to the top, then add "a" a is the new top then "t" and t is the new top
		super.insert(o,  1);
	}
	
	@Override 
	public void insert(Object o, int index) {
		this.push(o);
	}
	
	@Override
	public Object remove(int index) {
		return this.pop();
	}
	
	public Object pop() {//always remove from the head of the list(the head) because it operates from a LIFO fashion so the last thing added was t, so return t, then a, then b
		return super.remove(1);
	}
	
	@Override
	public String toString() {
		String retVal = "[";
		Object valler = null;;
		int count = 0;
		Stack j = new Stack();
		while (!this.isEmpty()) {
			count++;
			valler = this.pop();
			j.push(valler);
		}
		while (!j.isEmpty()) {
			Object o = j.pop();
			this.push(o);
			retVal += o + ",";
		}
		retVal = retVal.substring(0, retVal.length()-1);
		return retVal + "]";
	}
}

