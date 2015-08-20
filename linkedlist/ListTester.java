package hw5;

public class ListTester {

	public static void main(String[] args) {//these tests were all done in seperate occasions using the same list and commenting/uncommenting so the "should bes" are 
		//accurate only if specific sections are activated
		List j = new List();

		String k = "test1";
		String u = "test2";
		String u2 = "test3";
		String t = "anythingIwant";
		String i = "index";
		String foo = "foo";
		
		//j.insert(foo, 1);
		//j.insert(k, 2);
		//j.remove(2);
		for (int e = 1; e <= 10; e++) {
			j.insert("i" + e, e);
		}
		System.out.println(j.toString2());
		//System.out.println(j);
		j.clear();
		System.out.println(j.toString2());
		//j.insert(i, 0);
		//System.out.println(j);
		
		j.insert(k, 1);
		j.insert(u, 2);
		j.insert(u2, 3);
		j.insert(t, 4);
		j.insert(i, 5);
		j.insert(foo, 6);
		//j.insert(foo, 1);
		System.out.println(j);
		
		System.out.println(j.get(3));
		
		j.searchAndDelete(u2);
		System.out.println(j);
		
		List y = new List();
		for (int f = 1; f <= 25; f++) {
			y.insert("test" + f, f);
		}
		System.out.println(y);
		y.clear();
		System.out.println(y);
		//j.clear();
		//System.out.println(j);
		/*
		System.out.println(j);
		System.out.println(j.indexOf(t) + "should print out 4");
		System.out.println(j.indexOf("anythingIwant") + "should print out 4");
		System.out.println(j.indexOf("test3") + "should print out 3");
		
		for (int q = 1; q < 10; q++) {
			j.insert("Test"+ q, q);
		}
		System.out.println(j);
		//j.insert(t, 5);
		//System.out.println(j.indexOf(t)+ "Should print out 5");
		System.out.println(j.indexOf("Test2") + "should print out 2");*/
		
		/*System.out.println(j.isEmpty() + "Should print true");
		j.insert(k, 1);
		System.out.println(j);
		System.out.println(j.isEmpty() + "Should print false");
		j.insert(u, 2);
		System.out.println(j);
		j.insert(u2, 3);
		System.out.println(j);
		j.insert(t, 2);
		System.out.println(j);
		System.out.println(j.indexOf(t) + "Should print 2");
		System.out.println(j.indexOf(u2) + "Should print out 4");
		System.out.println(j.indexOf(u) + "print 3");
		j.insert(foo, 100);
		System.out.println(j);
		j.insert(i, 5);
		System.out.println(j);
		j.insert(i, 0);
		System.out.println(j);
		j.insert(null, 3);//is this supposed to work?
		System.out.println(j);
		
		j.remove(10);
		j.remove(1);
		System.out.println(j);
		j.remove(5);
		System.out.println(j);
		j.remove(2);
		System.out.println(j);
		System.out.println(j.size() + "should print 4");
		System.out.println(j.isEmpty()+ "should print false");
		j.remove(3);
		j.remove(2);
		j.remove(1);
		System.out.println(j.isEmpty() + "Should print true");
		
		System.out.println(j);
		
		System.out.println(j.size() + "should be 1");
		
		//j.remove(10);
		
		/*
		System.out.println(j.isEmpty()); System.out.println(j.size());
		 j.insert(k, 1); j.insert(k, 2); j.insert(k, 3); //j.insert(u, 6);
		 j.insert(u2, 4); j.insert(u, 5); //System.out.println(j.nodeNum);
		 System.out.println(j); j.insert(t, 3); System.out.println(j);
		 
		 j.insert(u2, 67); System.out.println(j);
		 System.out.println(j.isEmpty()); System.out.println(j.size());
		  
		 j.insert(i, 6); j.insert(i, 2); 
		 System.out.println(j.indexOf(foo) + " should print -1");
		 System.out.println(j.indexOf(t) + " should print 3");

		// remove testers
		for (int r = 1; r <= 8; r++) {
			j.insert("Test" + r, r);
			
			 } System.out.println(j); j.remove(2); System.out.println(j);
			 j.remove(5); System.out.println(j); j.remove(3);
			 System.out.println(j); j.remove(1); System.out.println(j);
			 
				j.remove(4);
				System.out.println(j);
		}*/

	}
}
