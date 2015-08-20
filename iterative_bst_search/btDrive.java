package fib;

public class btDrive {
	
	public static void main(String[] args) {
		BinaryTree<Integer> a = new BinaryTree<Integer>();
		a.insert(50);
		a.insertNonRecursive(37);
		a.insert(25);
		a.insert(75);
		a.insert(35);
		a.insert(65);
		a.insert(95);
		a.insert(15);
		a.insert(7);
		a.insert(20);
		a.insert(30);
		a.insert(47);
		a.insert(60);
		a.insert(68);
		a.insert(90);
		a.insert(100);
		a.insertNonRecursive(110);
		System.out.println(a);
		
		System.out.println(a.outOfOrderToString());
		
		System.out.println(a.size() + " should print out 17");
		
		System.out.println(a.getParent(95) + " should be 75");
		System.out.println(a.getParent(7) + " should be 15");
		
		System.out.println(a.search(30));
		System.out.println(a.itSearch(100));
		
		System.out.println(a.getDepth() + " should print out 5");
		
		//practice final below
		
		BinaryTree<Integer> b = new BinaryTree<Integer>();
		
		b.insert(18);
		b.insert(12);
		b.insert(35);
		b.insert(4);
		b.insert(15);
		b.insert(22);
		b.insert(58);
		b.insert(-2);
		b.insert(7);
		b.insert(13);
		b.insert(16);
		b.insert(19);
		b.insert(31);
		b.insert(40);
		b.insert(87);
		System.out.println();
		System.out.println(b);
		System.out.println(b.outOfOrderToString());
		b.printSideways();
	}

}
