package hw5;

public class Queue extends List {//inherits everything from list, simply adds and removes differently.
	
	public Queue(){//make a list
		super();
	}
	
	public void enqueue(Object o) {//always insert at the beginning of the list(the head) "same as stack addition"
		super.insert(o, 1);
	}
	
	public Object dequeue() {//this is the difference between stack and queue, a queue always removes from the opposite order that it adds to, because it operates in a FIFO fashion
		//when removing, you remove from the very end of the list, which is the first thing added. ie., t was added last, a was added 2nd and b was added 1st, so b returned, then a, then t
		return super.remove(this.size());
	}
	
	@Override 
	public void insert(Object o, int index) {
		this.enqueue(o);
	}
	
	@Override
	public Object remove(int index) {
		return this.dequeue();
	}
	@Override
	public String toString() {
			String retVal = "[";
			Object valler = null;;
			int count = 0;
			Queue j = new Queue();
			while (!this.isEmpty()) {
				count++;
				valler = this.dequeue();
				j.enqueue(valler);
			}
			while (!j.isEmpty()) {
				Object o = j.dequeue();
				this.enqueue(o);
				retVal += o + ",";
			}
			retVal = retVal.substring(0, retVal.length()-1);
			return retVal + "]";
		}
	}
