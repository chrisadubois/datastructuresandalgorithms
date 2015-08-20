package Hw8;
import java.util.Stack;
import java.util.ArrayList;

/*
 * @Author: Christopher DuBois
 * CSS 162
 * Professor Rob Nash
 * Wumpus Hunter
 * 
 * This class, which is a stack based wumpus hunter uses a stack in order to iterate
 * through a mountain of nodes in search for the Treasure room.  The class
 * does so by extending the WumpusHunter class and overriding the getName and startAt methods which
 * begin the iterative approach to the search.  After finding the Treasure room, the wumpus hunter will
 * use a stack to iterate back up the tree and print out the quickest path to the treasure room
 * Additionally, aside from this was an attempt at a recursive version of the same thing, although this has
 * not been as thoroughly tested and does not fully work in terms of finding the quickest path
 */

public class StackBasedWumpusHunter extends WumpusHunter {
	
	//this is the overridden getName method for the wumpus hunter
	//the name could be anything
	@Override 
	public String getName() {
		return "John III - who is an iterable, stack-based Wumpus Hunter";//John III!!!!
	}
	
	//this method is the overridden startAt method for the wumpus hunter
	//it iterates through the tree, starting at the root and finds the treasure room
	//once it finds the treasure room
	//it works its way back up the tree using a stack to fill out the path
	//because stacks pop() have the properties of reversing things
	//it will print out the quickest path to the treasure room
	@Override
	public void startAt(MountainCave current) {//it takes in a "MountainCave" which is a treeNode
		Stack<MountainCave> hero = new Stack<MountainCave>();//This is the hero stack! which will hold the values as we search down
		//loops through the tree because it adds each mountaincave as you enter it to the stack and if the 
		//stack isn't empty keep looping, OR if the current mountain node isn't null
		while (!hero.isEmpty() || current != null) {//as long as hero isn't empty because we will be 
			//popping from it, OR
			//as long as the node isn't null because this 
			//would happen if we reached a leaf
			if (current != null) {//if the current mountain node isn't null because that would happen at the bottom
				//of a branch
				actionLog += " we are now entering the cave: " + current.getCaveName() + "\n";//print out the caves name as we search down
				if (current.isAdjacentToScales()) {//a method that tells us when we get close to the treasure
					actionLog += " the scales are adjacent to our feet " + "\n";//pretty prints
				}
				//this is the case if we found the treasure room by looking at the node we are on
				if (current.hasScales()) {//if the current of the mountainCave has the scales
					hero.push(current);//add that node to the stack
					actionLog += " the scales are here!! we've got the golden scales and didn't get wumpus'd, ";//pretty prints
					while (current.hasParent()) {//this will only happen once we have found the scales
						hero.push(current);//add on the node
						current = current.getParent();//work your way back up the tree
					}
					hero.push(current);//add the top Node
					actionLog += "The quickest path to the goldenScales is " + "\n";//show the beginning by popping off the stack
					for (int i = 0; i < hero.size(); i++) {//pop off all of the pathway BACKWARDS (that is, we've already found the scales, and are now printing the backwards path, but
						//since a stack reverses stuff using pop, it actually prints the forward path
						actionLog += hero.pop().getCaveName() + "\n";//pretty prints
					}
					break;//end the while loop so no infinite
				}
				//all of this below traverses the tree
				hero.push(current);//still inside of the while keep adding to the stack
				//if it didn't have the scales, traverse the tree, it will go on to this because above it says break
				if (current.getChildren().size() == 2) {//if the branch has two leafs
					current = (MountainCave) current.getChildren().get(1);//get the child at spot one in the arraylist
				} else {//otherwise
					current = null;//the node is null and when this gets passed up to the top of the while 
					//it will enter the first if and fail and come
					//down to the else below
				}
		} else {//if the current MountainCave Node IS!!! null but my hero stack which holds the items to check is not empty
			current = (MountainCave) hero.pop();//because current is null you can't call getParent on null, but in the hero Stack, 
			//the getParent of that node is that last thing in the stack
			//this only happens if you are on a LEAF so you need to go back up the tree
			if (current.getChildren().size() >= 1) {//if the branch only has one leaf or more
				current = (MountainCave) current.getChildren().get(0);//get the other child
			} else {//if the current MountainCave Node that I am working on HAS NO children, i.e., it is a leaf
				current = null;//then the node is null
			}
		}
	}

}
	
	public void recStartAtCall(MountainCave root) {//prints it out backwards
		ArrayList<MountainCave> retVal = new ArrayList<MountainCave>();
		retVal.add(recStartAt(root));
	}
	
	public MountainCave recStartAt(MountainCave current) {
		Stack<MountainCave> list = new Stack<MountainCave>();
		if (current != null) {
		if (current.hasScales()) {
			list.push(current);
			actionLog += "were here!" + "\n";
			while (current.hasParent()) {
				actionLog += (current.getCaveName()) + "\n";
				list.push(current);
				current = current.getParent();
			}
			actionLog += (current.getCaveName()) + "\n";
			list.push(current);
			/*for (int i = 0; i < list.size(); i++) {
				actionLog += list.pop().getCaveName() + "\n";
			}*/
			return current;
			//return null;
		}  else {//end of basecase start of recursion
			if (current.getChildren().size() == 2) {
				return recStartAt((MountainCave)current.getChildren().get(1));
			} else if (current.getChildren().size() >= 1) {
				return recStartAt((MountainCave)current.getChildren().get(0));
			} else {
				return recStartAt((MountainCave)current.getParent().getChildren().get(0));
			}
		}
		}
		//return current;
		return null;
	}
}
