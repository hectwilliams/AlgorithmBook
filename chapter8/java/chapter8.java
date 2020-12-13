package algo;
import algo.Chapter5.*;

public class Chapter8 {
	
	public static class SList
	{
		Node head;
		
		SList() 
		{
			head = null;
		}
		
		public void pushFront (int value) 
		{
			head = Chapter5.addFront(head, value);
		}
		
		public Integer popFront () 
		{
			Integer result = null;
			if (head != null)
			{
				result = head.value;
				head = head.next;
			}
			return result;
		}
		
		public boolean contains (int value) 
		{
			return Chapter5.contains(head, value);
		}
		
		public void removeVal (int value) 
		{
			head = Chapter5.removeVal(head, value);
		}
		
		public Integer back (int value) 
		{
			return Chapter5.back(head);
		}
		
		public void pushBack (int value) 
		{
			 Chapter5.addBack(head, value);
		}
		
		public Integer popBack () 
		{
			Integer result = null;
			Node runner = head, runnerPrev = null;
			
			while (runner.next != null) 
			{
				runnerPrev = runner;
				runner = runner.next;
			}
			
			if (runner != null) 
			{
				result = runner.value;
				runnerPrev.next = null;
			}
						
			return result;
		}
		
		public void display()
		{
			Chapter5.display(head);
		}
		
		public  void swapPairs () 
		{
			/*
			 * 
			 *  [1] [2] [3] [4] [5] 6[]
			 * 	pop 2
			 *  [1] [3] [4] [5] 6[]
			 * 	insert front of previous node
			 *  [2]  [1] [3] [4] [5] 6[]
			 *  pop 3
			 *  [2]  [1] [4] [5] 6[]
			 *  insert after 4
			 *  [2]  [1] [4] [3] [5] 6[]
			 *  pop 5
			 *  [2]  [1] [4] [3] [6]
			 *  insert after 6
			 *  [2]  [1] [4] [3] [6] [5]
			 *  
			 *  
			 * */
			Node buffer, runner;
			
			if (head == null) 
			{
				return;
			}
			
			if (head.next == null) 
			{
				return;
			}
			runner = head;
			
			
			if (head.next != null) 
			{
				buffer = head;
				head = runner = runner.next;
				buffer.next = runner.next;
				runner = runner.next = buffer;
			}
			
			while (runner.next != null) 
			{
				if (runner.next.next == null) 
				{
					break;
				}
				// remove(pop) data
				buffer = runner.next; 
				runner = runner.next = buffer.next;
				buffer.next = runner.next;
				runner = runner.next = buffer;
			}
			
		}
	
	}
	
	public static void display(Node list)
	{
		while (list != null) 
		{
			System.out.print(list.value + ",");
			list = list.next;
		}
		System.out.println();
	}
	
	public static void setChild (Node node, int value) // set child attribute
	{
		if (node != null) 
		{
			node.child = new Node(value);			
		}
	}

	public static void setChild (Node node, Node child) // set child attribute
	{
		if (node != null) 
		{
			node.child = child;		
		}
	}

	public static void reverse (SList obj)
	{
		/*
		 * 
		 *  a(head)					-> 	b				->  c				->	d (runner)
		 * 	b(head)					-> 	c				->	d (runner)		-> 	a
		 * 	c(head)					->	d (runner)		-> 	b				->	a
		 * 	d (runner == head)		-> 	c				->	b  				-> 	a
		 *  // complete !
		 * 
		 * 
		 */
		
		Node runner, node;
		
		if (obj.head == null) 
		{
			return;
		}
		
		runner = obj.head;
		
		while (runner.next != null) 
		{
			runner = runner.next;
		}
		
		while (obj.head != runner) 
		{
			node = obj.head; // pop head node
			obj.head = obj.head.next; // move head
			node.next = runner.next;  // connect pooped head in between runner and runner.next
			runner.next = node;
		}		
		
	}
	
	public static Integer KthLastNode (Node list, int k) 
	{
		/*
		 * 
		 * [ ]	[ ]  	[1] 	null  | 1nd front end
		 * [ ] 	[2] 	[ ] 	null  | 2nd from end
		 * [3] 	[ ] 	[ ] 	null  | 3rd from end
		 * 
		 * */
		
		Node runner, tail;
		Integer result = null;
		runner = tail = null;
		
		while (k > 0 ) 
		{
			runner = list;
			k--;
			while (runner.next != tail) 
			{
				runner = runner.next;
			}
			tail = runner; 
	
			if (tail == list) // length of list reached
			{
				break;
			}
		}
		
		
		if (k == 0) 
		{
			result = runner.value;
		}
		
		
		return result;
		
	}
	
	public static Node shiftRight(Node list, int shiftby)
	{
		Node newTail, newhead, runner = list;
		
		if (runner == null)
		{
			return null;
		}
		
		if (runner.next == null) 
		{
			return null;
		}
		
		if (shiftby > 0) 
		{
			
			for (int i = 0; i < shiftby; i++) 
			{
				runner = list;
				while (runner.next.next != null) 
				{
					runner = runner.next;
				}
				newhead = runner.next;
				runner.next = null;
				newhead.next = list;
				list = newhead;
			}
		}
		
		if (shiftby < 0) 
		{
			while (shiftby++ < 0) 
			{
				newTail = list;
				list= list.next;
				runner = list;
				while (runner.next != null) 
				{
					runner = runner.next;
				}
				runner.next = newTail;
				runner.next.next = null;
			}
		}
		
		return list;
	}
	
	public static boolean isPalindrome (Node list)
	{
		/*
		 * 
		 * compare list(curr head) and tail
		 * 
		 * */
		Node tail = null, runner;
		boolean hascrossed = false;
		
		while (!hascrossed) 
		{
			runner = list;
			while (runner.next != tail) 
			{
				runner = runner.next;
			}
			
			tail = runner; // move curr tail back
		
			if (list.value != tail.value) 
			{
				return false;
			}
			
			list = list.next; // move curr head forward
			
			hascrossed = (list == tail || tail.next == list);
		}
		
		return true;
		
	}
	
	public static int  sumNumerals (Node a, Node b)
	{
		int suma, sumb, index;
		
		index = suma = sumb =0;
		long  tensfactor = 0;
		
		do 
		{
			tensfactor = (long) Math.pow(10, index++); // 1, 10, 100 ...
			
			if (a != null) 
			{
				suma += tensfactor * a.value;
				a = a.next;
			}
			
			if (b != null) 
			{
				sumb += tensfactor * b.value;
				b = b.next;
			}
		}
		while ( a != b) ; // loops end when a == b == null
		
		return suma + sumb;
		
	}
	
	public static int  sumNumeralsv2 (Node a, Node b)
	{
		int suma, sumb, index;
		Node taila, tailb, runner;
		
		index = suma = sumb = 0;
		taila = tailb = runner = null;
		
		while (a != taila)
		{
			runner = a;
			while (runner.next != taila) 
			{
				runner = runner.next;
			}
			taila = runner;
			
			suma += (long) Math.pow(10, index++) * taila.value;
		}
		
		index = 0;
		
		while (b != tailb)
		{
			runner = b;
			while (runner.next != tailb) 
			{
				runner = runner.next;
			}
			tailb = runner;
			sumb += (long) Math.pow(10, index++) * tailb.value;
		}
		
		return suma + sumb;
		
	}
	
	public static void flattenChildren(Node list) 
	{
		/*
		 * 1) set tail node (o(n))
		 * 2) find each child in list and add to tail node (o(n))
		 * 3) if child is found recursion and repeat steps (1), (2) 
		 * 
		 * */
		
		Node tail, runner, tailRunner;
		
		if (list == null) 
		{
			return;
		}
		
		runner = list;
		while (runner.next != null) 
		{
			runner = runner.next;
		}
		tailRunner = runner;
		
		runner = list;
		tail = null;
		
		while (runner.next != tail) 
		{
			if (runner.child != null) 
			{
				flattenChildren(runner.child);

				tail = tailRunner.next = runner.child; // move tail 
				
				while (tailRunner.next != null) 
				{
					tailRunner = tailRunner.next;
				}
				 
			}
			
			runner = runner.next;
		}
		
	}
	
	public static void unflattenChildren(Node list) 
	{
		/*
		 * 1) find child node using runnerFindChild
		 * 2) find and break linear connection with child(i.e. runnerFindChild). Save the child(i.e runnerToBreakLinks) for further unlinks
		 * 
		 * */
		
		Node runnerFindChild, runnerToBreakLinks , tmp;
		
		if (list == null) 
		{
			return;
		}
		
		runnerToBreakLinks = runnerFindChild = list;
		
		while (runnerFindChild.next != null) 
		{
			if (runnerFindChild.child != null)
			{
				runnerToBreakLinks = runnerFindChild;
				while (runnerToBreakLinks.next != runnerFindChild.child) 
				{
					runnerToBreakLinks = runnerToBreakLinks.next;
				}
				
				tmp = runnerToBreakLinks.next; 
				//break link
				runnerToBreakLinks.next = null;
				// set runner to remaining nodes 
				runnerToBreakLinks = tmp;
			}
			runnerFindChild = runnerFindChild.next;
		}
		
	}
	
	public static Node setUpLoop (int numNodes, int pointTo)
	{
		Node head, runner, tail;
		
		tail = runner = head = null;
		
		for (int i = 1; i <= numNodes; i++ )
		{
			if (head == null) 
			{
				runner = head = new Node(i);
			}
			else 
			{
				runner = runner.next = new Node(i);
			}
			
			if (i == pointTo)
			{
				tail = runner;
			}
		}
		
		runner.next = tail;
		
		return head;
	}
	
	public static boolean hasLoop (Node list)
	{
		Node runnera, runnerb;
		
		runnera = runnerb = list;
		int counter = 0;
		while (runnera.next != null) 
		{
			counter = (counter + 1) % 2;
			if (counter == 0) 
			{
				runnerb = runnerb.next;
			}
			runnera = runnera.next;
			
			if (runnera == runnerb) 
			{
				return true;
			}
		}
		return false;
	}
	
	public static Node loopStart (Node list)
	{
		Node runnera, runnerb, runnerloop, pointerInsideLoop  = null;
		int lengthOfLoop = 0;
		int counter = 0;
		
		runnera = runnerb = list;
		while (runnera.next != null) 
		{
			counter = (counter + 1) % 2;
			if (counter == 0) 
			{
				runnerb = runnerb.next;
			}
			runnera = runnera.next;
			
			if (runnera == runnerb) 
			{
				pointerInsideLoop =  runnera;
				break;
			}
		}
		
		
		if (pointerInsideLoop == null) 
		{
			return null;
		}
		
		// find  loop length
		runnerloop = pointerInsideLoop;
		do 
		{
			runnerloop = runnerloop.next;
			lengthOfLoop++;
		}
		while(runnerloop != pointerInsideLoop);
		
		
		// using loop length search entire list for feedback
		runnera = list;
		pointerInsideLoop = null;
		
		while(true)
		{
	
			pointerInsideLoop = runnera;
			
			for (int i = 0; i < lengthOfLoop; i++) 
			{
				runnerb = pointerInsideLoop; // stop feedback pointer 
				pointerInsideLoop = pointerInsideLoop.next;
			}
			
			if (pointerInsideLoop == runnera)  
			{
				break;
			}
			
			runnera = runnera.next;
		}
		
		return runnerb;
	}
	
	public static void breakLoop (Node list)
	{
		Node feedbackPointer = loopStart(list);
		if (feedbackPointer != null) 
		{
			feedbackPointer.next = null;
		}
	}
	
	public static int numberOfNodes (Node list)
	{
		Node feedbackPointer = loopStart(list);
		int counter = 0;
		
		if (feedbackPointer != null) 
		{
			counter++;
		}
		
		while (list != feedbackPointer) 
		{
			counter++;
			list = list.next;
		}
		
		return counter; 
	}
	
	

	
}




