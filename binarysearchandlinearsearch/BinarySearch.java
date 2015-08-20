package hw6;
//@Author Christopher DuBois
//implements the binary search method on Strings iteratively and recursively

public class BinarySearch extends SearchAlgorithm {//"is a" abstract class, searchalgorithm has some interface methods to fill in, and other methods to simply reuse

	public BinarySearch() {//no data to fill in
	}
	
	@Override
	public int search(String[] arr, String targ) {//iterative binary search
		if (arr == null || targ == null) throw new NullPointerException("cannot pass in a null array or null target string");//null checks
		boolean found = false;//boolean flag, that will throw an itemnotfound exception if the search could not find the target
		int below = 0;//the bottom index of the array
		int above = arr.length-1;//the top index of the array
		//thus, the word (if it is in the array) should be somewhere in between these two variables
		while ( (above - below) / 2 > 0) {// condition which states that as long as the "middle" is above 0, keep looping
			//if the middle is 0 then there is nothing left to compare to
			incrementCount();//everytime the loop happens, a comparison has been made, so increment count
			int mid = (above + below) / 2; //find the middle of the array
			if (arr[mid].equals(targ)) {//if, by chance, the middle of the array has the target string
				found = true;//then found is true
				return mid;//and we can break out and return that index
			} else if (arr[mid].compareTo(targ) > 0) {//otherwise, if we compare the array at the middle index to the target string and it returns a POSITIVE VALUE
				//if target is "lexicographically less" than the array at the middle it returns a positive value, so we look between below and middle
				above = mid;//look between below and middle (middle is now the new above)
			} else {//otherwise, the comparison with the array at the middle index to the target string returns a negative value, because the argument is greater than
				//the array at the middle index, which means it is above the middle
				//thus, we restart the below index at the middle so now we look between middle and above
				below = mid;//look between the middle and above where below is now what the middle just was
			}
			}
		if (found == false) {//boolean flag gets thrown if it was not found
			throw new ItemNotFoundException();
		}
		return -1;//will never reach this here, but if the exception was not thrown... return -1 to indicate the item was not found
	}
	@Override
	public int recSearch(String[] arr, String targ) {//facade method
		if (arr == null || targ == null) throw new NullPointerException("Cannot pass in null array or null target value");//null checks
		return recSearch(arr, targ, 0, arr.length-1);//pass in the array, the target string, the "bottom" as 0 and the top end of the array  as the length -1 for the top index
	}
	
	private int recSearch(String[] arr, String targ, int below2, int above2) {//takes the array, the target string, and the below and above indices (starting at 0 and length-1)
		int mid = (above2 + below2) / 2;//basic middle formula
		if (below2 >= above2) {//continue "recursing" until the below passes the above or "is the" above, this will happen because the below will increment up and the above will increment down in addition to the "middle" changing
			throw new ItemNotFoundException();//base case broken, item was not found, throw the exception
		} 
		if (arr[mid].equals(targ)) {//the best case scenario
			return mid;//using string equals, if the target equals the array at the middle index, return that index
		}
		else if (arr[mid].compareTo(targ) < 0){//argument is greater than the array at the middle index
			incrementCount();//increment the comparison counts because a comparison was made
			return recSearch(arr, targ, mid+1, above2);//since the argument (target) is greater than mid, we want to look again from the middle to the above
		} else {//the argument is less than the array at the middle index
			incrementCount();//so we increment count because a comparison was made
			return recSearch(arr,targ, below2, mid);//and search again from the below to the middle because the target was less than the middle index
		}
	}
}
