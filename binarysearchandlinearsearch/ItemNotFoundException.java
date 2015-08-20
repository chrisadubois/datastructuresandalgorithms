package hw6;
//@Author: Christopher DuBois
//Boilerplate exception subclass
public class ItemNotFoundException extends RuntimeException {//extends the parent class runtime exception which ends the program at run time if thrown

	public ItemNotFoundException(){
		super("Item was unable to be located");//generic if called without an argument
	}
	
	public ItemNotFoundException(String msg) {//called with a message
		super(msg);//uses the parents constructor passing in the argument 
	}
}
