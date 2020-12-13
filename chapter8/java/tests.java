package algo;
import algo.Chapter8;
import algo.Chapter5.*;

public class Tests {
	
	
	private static void reverseTest()
	{
		Chapter8.SList llist0 = new Chapter8.SList();
		
		llist0.pushFront(4);
		llist0.pushFront(3);
		llist0.pushFront(2);
		llist0.pushFront(1);

		llist0.display();
		System.out.println("rotated");
		Chapter8.reverse(llist0);
		llist0.display();

	}	
	
	private static void KthLastNodeTest()
	{
		Chapter8.SList llist0 = new Chapter8.SList();
		
		llist0.pushFront(4);
		llist0.pushFront(3);
		llist0.pushFront(2);
		llist0.pushFront(1);

		llist0.display();
		System.out.println(Chapter8.KthLastNode(llist0.head, 4));

	}	
	
	private static void shiftRightTest()
	{
		Chapter8.SList llist0 = new Chapter8.SList();
		
		llist0.pushFront(4);
		llist0.pushFront(3);
		llist0.pushFront(2);
		llist0.pushFront(1);

		llist0.display();
		Chapter8.display(Chapter8.shiftRight(llist0.head, 2));
	}	
	
	private static void shiftLeftTest()
	{
		Chapter8.SList llist0 = new Chapter8.SList();
		
		llist0.pushFront(4);
		llist0.pushFront(3);
		llist0.pushFront(2);
		llist0.pushFront(1);

		llist0.display();
		Chapter8.display(Chapter8.shiftRight(llist0.head, -2));
	}		

	private static void isPalindromeTest()
	{
		Chapter8.SList llist0 = new Chapter8.SList();
		
		llist0.pushFront(1);
		llist0.pushFront(2);
		llist0.pushFront(2);
		llist0.pushFront(1);
		System.out.println ( Chapter8.isPalindrome(llist0.head) );


	}		

	private static void sumNumeralsTest()
	{
		Chapter8.SList llist0 = new Chapter8.SList();
		llist0.pushFront(1);
		llist0.pushFront(0);
		llist0.pushFront(2);
		
		Chapter8.SList llist1 = new Chapter8.SList();
		llist1.pushFront(4);
		llist1.pushFront(8);

		System.out.println ( Chapter8.sumNumeralsv2(llist0.head, llist1.head) );
	}	
	
	private static void flattenChildrenTest()
	{
		Chapter8.SList list0 = new Chapter8.SList();
		list0.pushFront(5);
		list0.pushFront(4);
		list0.pushFront(3);
		list0.pushFront(2);
		
		Chapter8.SList list1 = new Chapter8.SList();
		list1.pushFront(50);
		list1.pushFront(20);
		list1.pushFront(10);
		
		Chapter8.SList list2 = new Chapter8.SList();
		list2.pushFront(300);
		list2.pushFront(200);
		list2.pushFront(100);
		
		Chapter8.setChild(list0.head.next, list1.head);
		Chapter8.setChild(list1.head.next, list2.head);

		/* Unflatten:
		 *[ 2 ] [ 3 ] [ 4 ] [5 ]  list0 
		 *        |
		 *      [ 10 ] [ 20 ] [ 50 ]  list1
 		 *                |
 		 *             [ 100 ] [ 200 ] [ 300 ]  list2
		 * 
		 *  Flatten:
		 *  [ 2 ] [ 3 ] [ 4 ] [5 ] [ 10 ] [ 20 ] [ 50 ] [ 100 ] [ 200 ] [ 300 ]
		 * 
		 * 
		 * */
		list0.display();
		Chapter8.flattenChildren(list0.head);
		list0.display(); // 2,3,4,5,10,20,50,100,200,300,
		Chapter8.unflattenChildren(list0.head);
		list0.display(); // 2,3,4,5,
		list1.display(); // 10,20,50,100,200,300,
		list2.display(); // 100,200,300,


	}	

	private static void setupLoopTest()
	{
		int size = 5;
		int pointBackTo = 3;
		Node circularList = Chapter8.setUpLoop(size, pointBackTo);
		int counter = 0;
		
		while (counter++ < size*3 )
		{
			System.out.println(circularList.value);
			circularList = circularList.next;
		}
		
	}
	
	private static void hasLoopTest() 
	{
		Node circularList = Chapter8.setUpLoop(5, 3);
		System.out.println(Chapter8.hasLoop(circularList));
		
		Chapter8.SList list1 = new Chapter8.SList();
		list1.pushFront(50);
		list1.pushFront(20);
		list1.pushFront(10);
		System.out.println(Chapter8.hasLoop(list1.head));
	}
	
	private static void loopStartTest()
	{
		Node circularList = Chapter8.setUpLoop(7, 3);
		System.out.println(Chapter8.loopStart(circularList).value);  // 3
		circularList = Chapter8.setUpLoop(100, 5);
		System.out.println(Chapter8.loopStart(circularList).value);  // 3
	}

	
	private static void breakLoopTest()
	{
		Node circularList = Chapter8.setUpLoop(7, 3);
//		Chapter5.display(circularList); infinite loop
		Chapter8.breakLoop(circularList);
		Chapter5.display(circularList);
	}

	
	private static void numberOfNodesTest()
	{
		Node circularList = Chapter8.setUpLoop(7, 3);
		
		Chapter8.SList list = new Chapter8.SList();
		list.pushFront(5);
		list.pushFront(4);
		list.pushFront(3);
		list.pushFront(2);
		
		System.out.println(Chapter8.numberOfNodes(circularList));  
		System.out.println(Chapter8.numberOfNodes(list.head));  
	}

	private static void swapPairsTest()
	{
		Chapter8.SList objLL = new Chapter8.SList();
		objLL.pushFront(6);

		objLL.pushFront(5);

		objLL.pushFront(4);
		objLL.pushFront(3);
		objLL.pushFront(2);
		objLL.pushFront(1);
		
		objLL.swapPairs(); 
		objLL.display();
	}
	
	public static void main  (String [] args) 
	{
		swapPairsTest();
	}

}
