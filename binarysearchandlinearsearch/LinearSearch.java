package hw6;
//@Author Christopher DuBois
//implements the linear search method for Strings iteratively and recursively
//the recursive method will cause stack overflow as n gets very large

public class LinearSearch extends SearchAlgorithm {//"is a" abstract class, searchalgorithm has some interface methods to fill in, and other methods to simply reuse
	public LinearSearch() {//no data necessary, the count variable is held in the parent class
	}
	
	@Override
	public int search(String[] arr, String targ) {//iterative search, takes in an array of Strings, and a target to search for
		if (arr == null || targ == null) {//if either the array passed in is null or the target string is null
			throw new NullPointerException("Cannot pass in a null array or a null target string");//throw an exception
		}
		for (int i = 0; i < arr.length; i++) {//for the entire length of the String array
			incrementCount();//increment the count for the number of comparisons each time we are checking
			if (targ.equals(arr[i])) {//using strings equals method, if target equals the array at index
				return i;//then return that index
			}
		}
		int a = -1;//else throw an exception not found
		if (a == -1) {//-1 will only happen if it's not found because above it returns i
			throw new ItemNotFoundException();//throw the exception
		}
		return a;//else return -1; this will never happen here because the exception will be thrown
	}
	@Override
	public int recSearch(String[] arr, String targ) {//facade
		if (arr == null || targ == null) throw new NullPointerException("Cannot pass in null array or target string");//null checks on the array and the target String
		int a = recSearch(0, arr, targ);//finds the index (and finds -1 if not found)
		if (a == -1) throw new ItemNotFoundException();//if not found, throw an exception
		else return recSearch(0, arr, targ);//otherwise throw the not found exception
	}
	
	private int recSearch(int index, String[] arr, String targ) {//recursive linear search
		if (index >= arr.length) {//if the index being passed in to the recursive method is larger than the arrays length (or equal to), we must break out because the item cannot be found, as the index passed in is the index to check at
			return -1;//if not found return -1
		}
		if (targ.equals(arr[index])) {//uses strings equal method
			return index;//if the item was found return the index it was found at
		} else {//otherwise...
			incrementCount();//this is where the comparison incrementation is, and it is here because the above part is the case IF the word was found, otherwise, 
			//we must move to the next spot and check, thus, increment count here
			return recSearch(index+1, arr, targ);//pass in the same array, and the same target string, but increment the index to check the target against in the array
		}
	}
}

