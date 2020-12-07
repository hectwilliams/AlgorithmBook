package algo;

public class Chapter6 {
	
	private static class SLNode  //no outside access 
	{
		 Integer val;
		 SLNode next;
		
		SLNode(Integer value) 
		{
			val = (value);
			next = null;
		}
	}
	
	private static class SequentialList  // lowest class(base)
	{
		private SLNode head = null;
		private SLNode tail = null;

		public  void setTail  (SLNode node)
		{
			tail = node;
		}
		
		public SLNode getTail  ()
		{
			return tail;
		}
		
		public  void setHead  (SLNode node)
		{
			head = node;
		}
		
		
		public SLNode getHead  ()
		{
			return head;
		}
		
		public boolean isEmpty() 
		{
			return this.getHead() == null;
		}

		public long size() 
		{
			SLNode node = getHead();
			long count = 0;
			while (node != null) 
			{
				node = node.next;
				count++;
			}
			return count;
		}
		
		public boolean contains(int val) 
		{
			SLNode node = getHead();
			while (node != null) 
			{
				if ( node.val == val) 
				{
					return true;
				}
			}
			return false;
		}
		
		public void debugDisplay()
		{
			SLNode node = getHead();
			while (node != null) 
			{
				System.out.print( node.val + ",");
				node = node.next;
			}
			System.out.println("");
		}
	}
	
	public static boolean compareList(SequentialList a, SequentialList b)
	{
		SLNode aptr = a.getHead(), bptr = b.getHead();
		
		if (aptr == null || bptr == null ) 
		{
			return false;
		}
		
		do 
		{
			if (aptr.val != bptr.val) 
			{
				return false;
			}
			aptr = aptr.next;
			bptr = bptr.next;
		}
		while (aptr != null && bptr != null);
		
		return aptr == null && bptr == null;
		
	}
	

	public static void removeMinimumsList (SequentialList queue)
	{
		SLNode ptr = queue.getHead(), minNodeptr = null;
		minNodeptr = ptr;
		
		while (ptr != null)
		{
			if (ptr.val < minNodeptr.val) 
			{
				minNodeptr = ptr;
			}
			ptr = ptr.next;
		}
		
		// remove dups 
		ptr = minNodeptr;
		while (ptr.next != null) 
		{
			if (ptr.next.val == minNodeptr.val)
			{
				ptr.next = ptr.next.next;
			}
			else 
			{
				ptr = ptr.next;
			}
		}
	}
	
	public static void interleaveList (SequentialList queue)   
	{
		SLNode ptr, mid, secondHalf, secondHalfNext;
		int count = 0;
		
		/*
		 p - ptr
		 m - midpoint 
		 [1][2][3][4][5]
		 p
		 m
		 [1][2][3][4][5]
		     p
		 m
		 [1][2][3][4][5]
		        p
		     m  
		 [1][2][3][4][5]
		           p
		     m  
		 [1][2][3][4][5]
		              p
		        m
		 * */
		
		mid = ptr = queue.getHead();
		
		while(ptr != null) 
		{
			if ( count == 2) 
			{
				count = 0;
				mid = mid.next;
			}
			ptr = ptr.next;
			count++;
		}
		
		if (mid.next != null) 
		{
			secondHalf = mid.next; // set to second half node head 
			ptr = queue.getHead(); // set a first half node head
			mid.next = null; // split list 
			
			while (ptr.next != null && secondHalf != null) 
			{
				secondHalfNext = secondHalf.next;
				secondHalf.next = ptr.next;
				ptr.next = secondHalf;
				secondHalf = secondHalfNext; // move to next
				ptr = ptr.next.next; 
			}
		}
	}
	
	
	
	
	public static class Queue  extends SequentialList
	{
		
		Queue ()
		{
			setHead(null);
		}

		public void enqueue(Integer value) 
		{
			SLNode tail , node = new SLNode(value);
			
			tail = getTail() ;
			
			if (tail == null) 
			{
				setHead(node);		

			}
			else 
			{
				tail.next = node;
			}
			
			setTail(node);		
	
		}

		public Integer dequeue() 
		{
			SLNode head = getHead(), next = null;
			Integer result = null;
			SLNode tail = getTail();
			
			if (head == null) 
			{
				return null;
			}
			
			next  = head.next;
			
			if (head == tail)
			{
				setTail(null);
			}
			
			result = head.val;

			setHead(next);
			
			return result;
		}

		public Integer front() 
		{
			SLNode head = getHead();
			if (head != null) 
			{
				return getHead().val;				
			}
			return null;
		}

		public boolean isEmpty() 
		{
			return this.front() == null;
		}

		public long size() 
		{
			SLNode node = getHead();
			long count = 0;
			while (node != null) 
			{
				node = node.next;
				count++;
			}
			return count;
		}
	
	}

	public static boolean compareQueues (Queue a, Queue b) 
	{
		return compareList(a, b);
	}
	
	public static void removeMinimums (Queue queue)
	{
		removeMinimumsList(queue);
	}
	
	public static void interleaveQueue (Queue queue)   
	{
		interleaveList(queue);
	}
	
	public static class Stack  extends SequentialList
	{
	
		public void push(int value)
		{
			SLNode node = new SLNode(value);
			node.next = getHead();
			setHead(node);
			
		}
		public  Integer pop()
		{
			SLNode node = getHead();
	
			if (node == null) 
			{
				return null;
			}
			setHead(node.next);
			return node.val;

		}
		public Integer top()
		{
			SLNode node = getHead();
			if (node == null) 
			{
				return null;
			}
			return node.val;
		}
	}
	
	public static boolean compareStacks (Stack a, Stack b) 
	{
		return compareList(a, b);
	}
	
	public static Stack copyStack(Stack stack) 
	{
		Queue queue = new Queue();
		Stack resultStack = new Stack();
		int count = 0;
		
		/*     
		 
		 &-front of sequential list 
		      
		           &
		 stack -> [a][b][c][d][e]
		  
		  
		 */
		while(stack.isEmpty() == false) 
		{
			queue.enqueue(stack.pop());
			count++;
		}
		
		/*                     
		 
		 stack -> []
		 					   &
		 queue -> [e][d][c][b][a]
		 
		 note: rotate(dequeue to back) to move tail node to front and dequeue value to both stacks ( (N^2/2 or N^2 worst case )
		 
		 rotate 1 [d][c][b][a][e]  ... [d][c][b][a]  
		 rotate 2 [c][b][a][d]   ... [c][b][a]
	     ...continue  until empty
		 */
		
		for ( ; count > 0; count--) 
		{
			for (int rotateCount = 0; rotateCount < count -1; rotateCount++) 
			{
				queue.enqueue( queue.dequeue() );
			}
			resultStack.push(queue.dequeue())  ;
			stack.push(resultStack.top());
		}
		
		return resultStack;
	}
	
	
	public static class TwoStackQueue extends SequentialList  
	{
		private Stack A, B;
		
		/*
		 	Stack A[] B[]  
		 	
		 	enqueue(2) 	A[] 		B[2]
			enqueue(3) 	A[] 		B[3][2]
			enqueue(11)	A[] 		B[11][3][2]
			dequeue()  	A[2][3][11]	B[]     ...  
						A[3][11] 	B[]
		 	enqueue(2) 	A[] 			B[2][11][3]
			dequeue()	A[3][11][2]	B[]  ...     
						A[11][2] 	B[]
			dequeue() 	A[11][2] 	B[]    
			dequeue() 	A[2] 		B[]    

		 
		*/
		
		TwoStackQueue() 
		{
			A = new Stack();
			B = new Stack();

		}
		
		public void enqueue(int val)
		{
			while (A.isEmpty() == false) 
			{
				B.push(A.pop());
			}
			B.push(val);
		}
		
		public Integer dequeue() 
		{
			while (B.isEmpty() == false) 
			{
				A.push(B.pop());
			}
			
			if (A.isEmpty() == false) 
			{
				return A.pop();
			}
			return null;
		}
	}
	
	public static boolean isPalindrome (Queue queue) 
	{
		Stack stack = new Stack();
		boolean state = true;
		long midceil, midfloor, ps, cs, sizeq;
		
		/*
		  
			set variables:
			midceil = mid size of queue rounded to high digit 
			midfloor - mid size of queue rounded to lowest digit
			ps - pre shift . number of queue rotation needed to compare front and top of queue and stack, respectively
			cs - cancal shitft - number of queue rotations needed to cancel pre-shift
			sizeq - current q size
			
			process: 
			0) get size from queue 
			1) calculate midceil and midfloor
			2) shift queue midceil number of times 
			3) set ps = 0
			4) set  sizeq = midceil
			5) dequeue midfloor number of elements into stack 
			6) check if stack is empty. IF TRUE, MOVE TO STEP 15
			7) shift queue ps times 
			8) compare front and floor
			9) set cs = (sizeq -  ps)
			10) shift queue cs times 
			11) pop stack value into queue 
			12) incr sizeq 
			13) incr ps
			14) repeat 6
			15) dequeue midfloor number of elements to stack 
			16) empty stack to queue 
			17) empty queue to stack
			18) stack queue to queue
			x) !complete 
		
		 * */
		
		//step 0
		sizeq = queue.size();
		
		//step 1
		midfloor = sizeq / 2;
		midceil = midfloor + sizeq % 2;
		
		// step 2 
		for (int i = 0; i  < midceil; i++) 
		{
			queue.enqueue(queue.dequeue());
		}

		// step 3 4
		ps = 0;
		sizeq = midceil;
		
		// step 5 
		for (int i = 0; i < midfloor; i++) 
		{
			stack.push(queue.dequeue());
		}
		
		//step 6
		while (stack.isEmpty() == false) 
		{
			// step 7
			for (int i = 0; i  < ps; i++) 
			{
				queue.enqueue(queue.dequeue());
			}
			
			// step 8
			state &= queue.front() == stack.top();
			
			//step 9
			cs = sizeq - ps;
			
			// step 10
			for (int i = 0; i  < cs; i++) 
			{
				queue.enqueue(queue.dequeue());
			}
			
			// step 11
			queue.enqueue(stack.pop());

			// step 12
			sizeq++;
			
			// step 13 
			ps++;
			
		}
		
		// step 15 
		for (int i = 0; i < midceil; i++) 
		{
			stack.push(queue.dequeue());
		}
		
		// step 16 
		while (stack.isEmpty() == false) 
		{
			queue.enqueue(stack.pop());
		}

	
		// step 17 
		while (queue.isEmpty() == false) 
		{
			stack.push(queue.dequeue());
		}
		
		// step 18
		while (stack.isEmpty() == false) 
		{
			queue.enqueue(stack.pop());
		}

		

	return state;
	}
	
	
	public static class Dequeue  extends SequentialList
	{
		/*
		 [front] [] [] [] [] [back] 
		 */
		Dequeue() 
		{
			setHead(null);
		}
		
		public void pushFront(Integer val)
		{
			SLNode node = new SLNode(val);
			
			if (isEmpty() == false) 
			{
				node.next = getHead();
			}
			setHead(node);
		}
		
		public void pushBack(Integer val)
		{
			SLNode node = new SLNode(val), ptr= getHead();
			
			if (ptr == null) 
			{
				pushFront(val);
			}
			else 
			{
				while (ptr.next != null) 
				{
					ptr = ptr.next; 
				}
				ptr.next = node; 
			}
		}
		
		public Integer popFront()
		{
			Integer data;
			SLNode node;
			
			if (isEmpty()) 
			{
				return null;
			}
			
			node = getHead();
			data = node.val;
			setHead(node.next);
			return data;
		}
		
		public Integer popBack()
		{
			Integer data = null;
			SLNode ptr = getHead();
			
			if (ptr == null) // 0 elements 
			{
				return null;
			}
			
			if (ptr.next == null) // 1 element 
			{
				data = ptr.val;
				setHead(ptr.next);
			}
			
			while (ptr.next.next != null) // 2 or more elements 
			{
				ptr = ptr.next;
			}
			
			if (ptr.next != null ) 
			{
				data = ptr.next.val;
				ptr.next = ptr.next.next;
			}
			
			return data; 
		}
		
		public Integer front() 
		{
			if (isEmpty())
			{
				return null;
			}
			return getHead().val;
		}
		
		public Integer back () 
		{
			SLNode ptr = getHead();
			
			if (ptr == null) 
			{
				return null;
			}
			
			while (ptr.next != null)
			{
				ptr = ptr.next; 
			}
			
			return ptr.val;
		}
		
		// contains inherited
		//isEmpty() inherited
		//size() inherited

	}
	
	public static void removeStackMin (Stack stack) 
	{
		/*
		 *  [S] {find min and its count(i.e. nthEle) }  --> [Q] -->  [S] {remove  value equal to min with a nthEle < ( size - nthEleMin + 1) }  -->  [Q] -> [S] {back to order}
		 * 
		 * 
		 *
		**/
		Queue queue = new Queue();
		Integer min = null, data;
		int nthEleMin = 0;
		int size = 0;
		
		if (stack.isEmpty()) 
		{
			return;
		}
		
		min = stack.top();
		nthEleMin = 0;
		
//		process: [S] {find min and its count(i.e. nthEle) }  --> [Q]
		
		for (int nthEle = 1; stack.isEmpty() == false; nthEle++) 
		{
			data = stack.pop();
			
			if (data < min) 
			{
				min  = data;
				nthEleMin = nthEle;
			}		
			
			queue.enqueue(data);
			size++;
		}
		
		
//		 [Q] -->  [S]
		
		while (queue.isEmpty() == false) 
		{
			stack.push(queue.dequeue());
		}
		
		
//		[S] {remove  value equal to min with a nthEle < ( size - nthEleMin + 1) }  ->  [Q]
		
		for (int nthEle = 1; stack.isEmpty() == false; nthEle++) 
		{
			data = stack.pop();
			if ( nthEle <= (size - nthEleMin + 1)  ) 
			{
				if (data ==  min) // do not add to queue
				{
					continue;
				}
			}
			queue.enqueue(data);
		}
		
//		[Q] -> [S] {back to order}
		while (queue.isEmpty() == false) 
		{
			stack.push(queue.dequeue());
		}
			
	}
	
	public static void removeNewestStackMin (Stack stack) 
	{
		Queue queue = new Queue();
		Integer min = null, data;
		int nthEleMin = 0;
		int size = 0;
		
		if (stack.isEmpty()) 
		{
			return;
		}
		
		min = stack.top();
		nthEleMin = 0;
		
//		process: [S] {find min and its count(i.e. nthEle) }  --> [Q]
		
		for (int nthEle = 1; stack.isEmpty() == false; nthEle++) 
		{
			data = stack.pop();
			
			if (data < min) 
			{
				min  = data;
				nthEleMin = nthEle;
			}		
			
			queue.enqueue(data);
			size++;
		}
		
//		 [Q] -->  [S]
		
		while (queue.isEmpty() == false) 
		{
			stack.push(queue.dequeue());
		}
		
//		[S] {remove  value equal to min with at  nthEle = ( size - nthEleMin + 1) }  ->  [Q]
		
		for (int nthEle = 1; stack.isEmpty() == false; nthEle++) 
		{
			data = stack.pop();
			if ( nthEle == (size - nthEleMin + 1)  ) 
			{
				if (data ==  min) // do not add to queue
				{
					continue;
				}
			}
			queue.enqueue(data);
		}
		
//		[Q] -> [S] {back to order}
		while (queue.isEmpty() == false) 
		{
			stack.push(queue.dequeue());
		}
		
	}
	
	public static void removeOldestStackMin (Stack stack) 
	{
		Queue queue = new Queue();
		Integer min = null, data;
		int nthEleMin = 0;
		int size = 0;
		
		if (stack.isEmpty()) 
		{
			return;
		}
		
		min = stack.top();
		nthEleMin = 0;
		
//		process: [S] {find min and its count(i.e. nthEle) }  --> [Q]
		
		for (int nthEle = 1; stack.isEmpty() == false; nthEle++) 
		{
			data = stack.pop();
			
			if (data < min || data == min) 
			{
				min  = data;
				nthEleMin = nthEle;
			}		
			
			queue.enqueue(data);
			size++;
		}
		
//		 [Q] -->  [S]
		
		while (queue.isEmpty() == false) 
		{
			stack.push(queue.dequeue());
		}
		
//		[S] {remove  value equal to min with at  nthEle = ( size - nthEleMin + 1) }  ->  [Q]
		
		for (int nthEle = 1; stack.isEmpty() == false; nthEle++) 
		{
			data = stack.pop();
			if ( nthEle == (size - nthEleMin + 1)  ) 
			{
				if (data ==  min) // do not add to queue
				{
					continue;
				}
			}
			queue.enqueue(data);
		}
		
		
		
//		[Q] -> [S] {back to order}
		while (queue.isEmpty() == false) 
		{
			stack.push(queue.dequeue());
		}
		
		
	}
	
	
	public  class CirQueue 
	{	private int head;
		private int tail;
		private int cap;
		private int[] arr;
		boolean wrlock, rdlock, isfull, isempty;
		
		CirQueue (int size) 
		{
			if (size <= 0) 
			{
				cap = size = 10;
			}
			arr = new int[size];
			head = tail = 0;
			wrlock = false;
			rdlock = true;
		}
		
		Integer front()
		{
			return arr[tail];
		}
		
		boolean isEmpty()
		{
			return isempty;
		}
		
		boolean isFull () 
		{
			return isfull;
		}
		
		int size () 
		{
			int count = 0;
			
			for (int index = head; index != tail; index = (index + 1) % cap ) 
			{
				count++;
			}
			return count;
		}
		
		boolean enqueue (int val) 
		{
			if (wrlock) 
			{
				return false;
			}
			
			if (rdlock)  // rd slot available
			{
				rdlock = false;
			}
			
			if ( isempty) 
			{
				isempty = false;
			}
			
			arr[tail++] = val;
			
			if (tail == head) 
			{
				isfull = wrlock = true ;
			}
			return true;
			
		}
		
		Integer dequeue ( ) 
		{
			Integer data;
			if (rdlock) 
			{
				return null;
			}
			
			if (wrlock)  // write slot available
			{
				wrlock = false;
			}
			
			if ( isfull) 
			{
				isfull = false;
			}
			
			
			data = arr[head++];
			
			if (tail == head) 
			{
				isempty = rdlock = true ;
			}
			
			return data;
		}
		
		boolean contains (int val) 
		{
			if (isempty) 
			{
				return false;
			}
			
			if (isfull)   // search entire array 
			{
				for (int retVal: arr) 
				{
					if (val == retVal)
					{
						return true;
					}
				}
			}
			else 
			{
				for (int index = head; index != tail; index = (index + 1) % cap ) 
				{
					if (arr[index] == val) 
					{
						return true;
					}
				} 		
			}
			
		
			return false;
		}
		
		void grow (int newSize) 
		{
			int[] newArray;
			int neHead, newTail;
			
			if (newSize < cap) 
			{
				return;
			}
			
			newArray = new int[newSize];

			/*
			 new array must retain contagious nature of data 
			 [wr2] [wr3] [ ] [wr0] [wr1] 
			                   T
			                   H
			              
			 new array must translate into:
			  [wr0] [wr1] [wr2] [wr3 ] [] [ expansion ] [ expansion ]
 			   H                      
 			   T  
			 * */
			
			// copy old array to new array 
			

			if (isfull) 
			{
				for (int i = 0; i < cap;  i++) 
				{
					newArray[i] = arr[(head + i) % cap]; 
				}
				isfull = false;
				head = tail = 0;
			}
			

			if ( ! isempty )
			{
				newTail = neHead = 0;  // new head/tail positions for new array 

				for (int index = head; index != tail; index = (index + 1) % cap ) 
				{
					newArray[neHead++] = arr[index]; 
				}		
				newTail = neHead;

				
				head = neHead; 
				tail = newTail;
			}
			
			// set new array 
			arr = newArray;
			cap = newSize;
			
		}
		
	}
	
	public static void reorderAbsoluteQueue (Queue queue) 
	{
		/*
		 * process (following occurs  while Q is not empty ):
		 *  Q --> S  (find max and calculate size) 
		 *  S --> Q  ( store max locally without adding back to Queue )
		 *  push locally stored max value into stack
		 *  repeat process until Q is empty 
		 *  flush stack to Queue 
		 *  complete 
		 * */
		
		Stack stack = new Stack();
		Integer max = null, data;
		int freq; // frequency of max
		int size;
		
		do 
		{
			size = 0;
			freq = 0;
			max = null;
			
			// Q -> S
			while (queue.isEmpty()  == false) 
			{
				data = queue.dequeue();
				
				if (max == null || data > max ) 
				{
					max = data;
				}
				
				stack.push(data);

				size++;
			}
			
			freq = 0;
			
			
			// S -> Q
	
			for (int i = 0;i < size; i++) 
			{
				data = stack.pop() ;
				if (data == max) 
				{
					freq++;
				}
				else 
				{
					queue.enqueue(data);
				}
			}
			
			while (freq >  0) 
			{
				stack.push(max);
				--freq;
			}
			
			size = size - freq; // size of elements in queue 
		}
		
		while (size > 0);
		
		
		// flush stack to queue 
		while (stack.isEmpty() == false) 
		{
			queue.enqueue(stack.pop());
		}
		
		
	
	}
	
	public static void main(String agrs[]) 
	{
		
	}
	
}

