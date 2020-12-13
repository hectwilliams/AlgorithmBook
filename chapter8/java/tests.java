package algo;
import algo.Chapter8.*;
import algo.Chapter5.*;

public class Tests {
	
	
	private static void reverseTest()
	{
		SList llist0 = new SList();
		
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
		SList llist0 = new SList();
		
		llist0.pushFront(4);
		llist0.pushFront(3);
		llist0.pushFront(2);
		llist0.pushFront(1);

		llist0.display();
		System.out.println(Chapter8.KthLastNode(llist0.head, 4));

	}	
	
	private static void shiftRightTest()
	{
		SList llist0 = new SList();
		
		llist0.pushFront(4);
		llist0.pushFront(3);
		llist0.pushFront(2);
		llist0.pushFront(1);

		llist0.display();
		Chapter8.display(Chapter8.shiftRight(llist0.head, 2));
	}	
	
	private static void shiftLeftTest()
	{
		SList llist0 = new SList();
		
		llist0.pushFront(4);
		llist0.pushFront(3);
		llist0.pushFront(2);
		llist0.pushFront(1);

		llist0.display();
		Chapter8.display(Chapter8.shiftRight(llist0.head, -2));
	}		

	private static void isPalindromeTest()
	{
		SList llist0 = new SList();
		
		llist0.pushFront(1);
		llist0.pushFront(2);
		llist0.pushFront(2);
		llist0.pushFront(1);
		System.out.println ( Chapter8.isPalindrome(llist0.head) );


	}		

	private static void sumNumeralsTest()
	{
		SList llist0 = new SList();
		llist0.pushFront(1);
		llist0.pushFront(0);
		llist0.pushFront(2);
		
		SList llist1 = new SList();
		llist1.pushFront(4);
		llist1.pushFront(8);

		System.out.println ( Chapter8.sumNumeralsv2(llist0.head, llist1.head) );
	}	
	
	private static void flattenChildrenTest()
	{
		SList list0 = new SList();
		list0.pushFront(5);
		list0.pushFront(4);
		list0.pushFront(3);
		list0.pushFront(2);
		
		SList list1 = new SList();
		list1.pushFront(50);
		list1.pushFront(20);
		list1.pushFront(10);
		
		SList list2 = new SList();
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
		
		SList list1 = new SList();
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
		
		SList list = new SList();
		list.pushFront(5);
		list.pushFront(4);
		list.pushFront(3);
		list.pushFront(2);
		
		System.out.println(Chapter8.numberOfNodes(circularList));  
		System.out.println(Chapter8.numberOfNodes(list.head));  
	}

	private static void swapPairsTest()
	{
		SList objLL = new SList();
		objLL.pushFront(6);

		objLL.pushFront(5);

		objLL.pushFront(4);
		objLL.pushFront(3);
		objLL.pushFront(2);
		objLL.pushFront(1);
		
		objLL.swapPairs(); 
		objLL.display();
	}
	
	private static void DLClassTest ()
	{
		DList dlist = new DList();
		
		dlist.push(22);
		dlist.push(21);

		dlist.push(23);
//		System.out.println(dlist.pop());
		System.out.println(dlist.back());
		System.out.println(dlist.contains(3423));
		System.out.println(dlist.size());

		dlist.display();
	}
	
	private static void prependValueTest( ) 
	{
		DList dlist = new DList();
		dlist.push(22);
		dlist.push(21);
		dlist.push(23);
		Chapter8.prependValue(dlist, 300, 23);
		dlist.display();

	}
	
	private static void appendValueValueTest( ) 
	{
		DList dlist = new DList();
		dlist.push(22);
		dlist.push(21);
		dlist.push(23);
		Chapter8.appendValue(dlist, 300, 23);
		Chapter8.appendValue(dlist, 300, 22);

		dlist.display();
	}
	
	private static void kthToLastValueTest( ) 
	{
		DList dlist = new DList();
		dlist.push(22);
		dlist.push(21);
		dlist.push(23);
		System.out.println( dlist.kthToLastValue(1));
	}
	
//	private static void deleteMiddleNodeTest ( )  // changed DLNode .next attribute to public to run function
//	{
//		DList dlist = new DList();
//		dlist.push(22);
//		dlist.push(21);
//		dlist.push(23);
//		dlist.display();
//		Chapter8.deleteMiddleNode(dlist.getHead().next);
//		dlist.display();
//	}
	
//	private static void isValidTest ( )  // changed DLNode .next attribute to public to run function
//	{
//		DList dlist = new DList();
//		dlist.push(22);
//		dlist.push(21);
//		dlist.push(23);
//		dlist.getTail().next = dlist.getHead();
//		dlist.getHead().prev = dlist.getTail();
//		System.out.println( dlist.isValid());
//	}
	
	private static void partitionTest () 
	{
		DList dlist = new DList();
		dlist.push(27);
		dlist.push(26);
		dlist.push(23);
		dlist.push(7);

		dlist.push(8);

		dlist.push(7);

		dlist.push(10);
		dlist.push(3);
		dlist.push(13);
		dlist.push(1);
		
		dlist.display();
		Chapter8.partition(dlist, 7);
		dlist.display();

	}
	
	private static void palindromeTest ()
	{
		DList dlist = new DList();
		dlist.push(7);
		dlist.push(27);
		dlist.push(27);
		dlist.push(7);
		System.out.println(dlist.palindrome()); // true
		
		DList dlist2 = new DList();
		dlist2.push(7);
		dlist2.push(27);
		dlist2.push(24);
		dlist2.push(7);
		System.out.println(dlist2.palindrome()); // false

	}
	
	private static void reverseDlistTest ()
	{
		DList dlist = new DList();
		dlist.push(7);
		dlist.push(4);
		dlist.push(2);
		dlist.push(1);
		dlist.display();
		dlist.reverse(); // true
		dlist.display();

		
	}
	
	
	public static void main  (String [] args) 
	{
		reverseDlistTest();
	}
	
	


}
