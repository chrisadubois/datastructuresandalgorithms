package hw5;

public class LinkedListException extends RuntimeException {//stock class...boiler plate code
	
	public LinkedListException(String msg){
		super(msg);
	}
	
	public LinkedListException() {
		super("LinkedList Error!!");//this almost never gets used
	}
}
