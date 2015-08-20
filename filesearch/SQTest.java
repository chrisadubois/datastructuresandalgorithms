package hw5;

public class SQTest {

	public static void main(String[] args) {

		Stack j = new Stack();
		Queue k = new Queue();

		System.out.println(j.isEmpty() + "should print true");
		System.out.println(j.size() + "should print 0");
		j.push("b");
		j.push("a");
		j.push("t");
		System.out.println(j);
		System.out.println(j.size() + "should print 3");
		System.out.println(j.isEmpty() + "should print false");
		/*System.out.println(j.isEmpty()+ "Should print false");
		System.out.println(j.size() + "Should be 3");
		j.pop();
		System.out.println(j.size()+"should print 2");
		j.pop();
		j.pop();
		System.out.println(j);
		System.out.println(j.isEmpty()+"Should print true");
		System.out.println(j.size() + "Should print 0");*/
		
		
		System.out.println(j.pop() + "should be t");
		System.out.println(j.pop() + "should be a");
		System.out.println(j.pop() + "should be b");
		
		j.insert("r", 10);
		j.insert("u", 1);
		System.out.println(j.remove(10) + "Should be u");
		System.out.println(j);
		j.pop();
		
		//System.out.println(j.pop());//cant from empty
		
		/*Object t = j.pop();
		System.out.println(t + "should be t");
		Object a = j.pop();
		System.out.println(a + "should be a");
		System.out.println(j.pop() + "should be b");
		//System.out.println(j);
		//Object g = j.pop();
		//System.out.println(g + "should be b")*/
		
		
		k.enqueue("B");
		k.enqueue("A");
		k.enqueue("T");
		System.out.println(k);
		
		Object r = k.dequeue();
		System.out.println(r + "should be B");
		Object e = k.dequeue();
		System.out.println(e + "should be A");
		Object w = k.dequeue();
		System.out.println(w + "should be T");
		
		//System.out.println(k.dequeue());//cant from empty
		
		/*System.out.println(k.isEmpty() + "should print false");
		System.out.println(k.size()+ "should print 3");
		k.dequeue();
		System.out.println(k);
		k.dequeue();
		System.out.println(k.size() + "should print 1");
		System.out.println(k);
		k.dequeue();
		System.out.println(k);
		System.out.println(k.isEmpty() + "Should print true");
		System.out.println(k.size()+"should print 0");*/

	}
}
