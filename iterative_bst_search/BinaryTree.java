package fib;//a package that once only contained the fibonacci iterative implementation but now includes 
//classes made to study

import java.util.ArrayList;
import java.util.Stack;
/*@Author: Christopher DuBois
 * Generic Binary Tree
 * built to understand wumpusMountain CSS 162 Rob Nash
 * as well as to study for the final
 */
public class BinaryTree<T extends Comparable> {
	TreeNode root = null;

	public class TreeNode<T extends Comparable> {
		private TreeNode<T> left;
		private TreeNode<T> right;
		private T data;

		public TreeNode(T d, TreeNode<T> r, TreeNode<T> l) {
			left = l;
			right = r;
			data = d;
		}
		
		public T getData() {
			return this.data;
		}
		
		public String toString() {
			String retVal = "";
			retVal += this.data;
			return retVal;
		}
	}

	public int size() {
		return recSize(root);
	}

	private int recSize(TreeNode<T> current) {
		if (current == null) return 0;
		return 1 + recSize(current.left) + recSize(current.right);
	}
	
	public void printSideways() {
		recPrintSideways(root, "");
	}
	
	private void recPrintSideways(TreeNode<T> current, String s) {
		String retVal = "";
		if (current == null) retVal += "";
		else {
			recPrintSideways(current.right, s + "    ");
			System.out.println(s + current.data);
			recPrintSideways(current.left, s + "     ");
		}
	}

	public void insertNonRecursive(T data) {
		if (root == null) {
			root = new TreeNode<T>(data, null, null);
		} else {
			TreeNode<T> cur = root;
			while (cur != null) {   // should never happen
				if (data.compareTo(cur.data) < 0) {
					if (cur.left == null) {
						cur.left = new TreeNode<T>(data, null, null);
						return;
					} else {
						cur = cur.left;
					}
				} else {
					if (cur.right == null) {
						cur.right = new TreeNode<T>(data, null, null);
						return;
					} else {
						cur = cur.right;
					}
				}
			}
		}
	}

	public void insert(T o) {
		if (o == null)
			throw new IllegalArgumentException("Cannot add null");
		root = recInsert(o, root);
	}

	private TreeNode<T> recInsert(T o, TreeNode current) {
		if (current == null) current = new TreeNode(o, null, null);
		else if(current.data.compareTo(o) > 0) {
			current.left = recInsert(o, current.left);
		} else { //if the data at current is less than the data at o
			current.right = recInsert(o, current.right);
		}
		return current;
	}

	public String outOfOrderToString() {
		return recOut(root);
	}

	private String recOut(TreeNode<T> current) {
		String retVal = "";
		if (current == null) retVal += "";
		else {
			retVal += current.data + ", ";
			retVal += recOut(current.left);
			retVal += recOut(current.right);
		}
		return retVal;
	}
	
	public TreeNode<T> getParent2(TreeNode<T> target) {
		TreeNode<T> retVal = null;
		if (target.equals(root.data)) return root;
		retVal = recGetParent2(root, target);
		return retVal;
	}
	
	public T getParent(T target) {
		TreeNode<T> retVal = null;
		if (target.equals(root.data)) throw new RuntimeException("Root has no parent");
		retVal = recGetParent(root, target);
		return retVal.data;
	}
	
	
	private TreeNode<T> recGetParent(TreeNode<T> current, T target) {
		TreeNode<T> retVal = null; 
		if(current != null) {
			if(current.left != null) {
				if(current.left.data.equals(target)) {
					return current;
				}
				retVal = recGetParent(current.left, target);
				if(retVal != null) return retVal;
			}
			if (current.right != null) {
				if (current.right.data.equals(target)) {
					return current;
				}
				retVal = recGetParent(current.right, target);
				if(retVal != null) return retVal;
			}
		}
		return retVal;
	}
	
	private TreeNode<T> recGetParent2(TreeNode<T> current, TreeNode<T> target) {
		TreeNode<T> retVal = null; 
		if(current != null) {
			if(current.left != null) {
				if(current.left.equals(target)) {
					return current;
				}
				retVal = recGetParent2(current.left, target);
				if(retVal != null) return retVal;
			}
			if (current.right != null) {
				if (current.right.equals(target)) {
					return current;
				}
				retVal = recGetParent2(current.right, target);
				if(retVal != null) return retVal;
			}
		}
	return retVal;
	}
	
	public String itSearch(T target) {
		return itSearcher(target, root);
	}
	
	public String itSearcher(T target, TreeNode<T> ruut) {
		String retVal = "";
		if (ruut == null) throw new IllegalArgumentException("null root");
		TreeNode<T> current = ruut;
		Stack<TreeNode<T>> path = new Stack<TreeNode<T>>();
		path.push(current);
		boolean found = false;
		while (!path.isEmpty()) {
			current = path.pop();
			if (current.data.equals(target)) {
				found = true;
				//retVal+= " we found it, you were looking for: " + target + " and we found: " + current.data + "\n"; 
				break;
			} else {
				retVal += " passing through..." + current.data + "\n";
			}
			if (current.left != null && current.right != null) {
				path.push(current.left);
				path.push(current.right);
			}
			if (current.left != null && current.right == null) {
				path.push(current.left);
			}
			if (current.left == null && current.right != null) {
				path.push(current.right);
			}
			if (current.left == null && current.left == null) {
				continue;
			}
		}
			if (found) {
				retVal+= " we found it, you were looking for: " + target + " and we found: " + current.data + "\n"; 
				retVal += "the quickest path to the target is... \n";
				path.clear();
				path.push(current);
				while ( (getParent2(current) != null) ) {
					path.push(current);
					current = getParent2(current);
				}
				path.push(current);
				for (int i = 0; i < path.size(); i++) {
					retVal += path.pop().data + "\n";
				}
			} else {
				retVal += "we didnt find: " + target + "\n";
			}
			return retVal;
		}
	
	public String search(T target) {
	String retVal = "";
	Stack<TreeNode> route = new Stack<TreeNode>();
	if (root.data.equals(target)) retVal += "The target is at the top " + root.data;
	else {
		TreeNode<T> nodeRef = recSearch(target, root);
		if (nodeRef != null) retVal += "found! ";
		retVal += "the data is at " + nodeRef.data;
		retVal += " the quickest path to the data is...\n";
		route.push(nodeRef);
		while (nodeRef != null) {
			route.push(this.getParent2(nodeRef));
			nodeRef = getParent2(nodeRef);
		}
		while ( !(route.isEmpty())) {
			Object add = route.pop();
			if (add == null) add = "";
			retVal += add + " ";
		}
	}
		return retVal;
	}
	
	private TreeNode<T> recSearch(T target, TreeNode<T> current) {
		if (current == null) return null;
		if(current.data.equals(target)) return current;
		else {
			TreeNode<T> leftNode = recSearch(target, current.left);
			TreeNode<T> rightNode = recSearch(target, current.right);
			if (leftNode != null) return leftNode;
			if (rightNode != null) return rightNode;
		}
		return null;
	}
	
	public int getDepth() {
		return recGetDepth(root);
	}
	
	public int recGetDepth(TreeNode<T> current) {
		if (current == null) return 0;
		return 1 + Math.max(recGetDepth(current.left), recGetDepth(current.right));
	}

	public String toString() {
		return recToString(root);
	}

	private String recToString(TreeNode<T> current) {
		String retVal = "";
		if (current == null) retVal += "";
		else {
			retVal += recToString(current.left);
			retVal += current.data + ", ";
			retVal += recToString(current.right);
		}
		return retVal;
	}
}

