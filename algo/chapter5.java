package algo;


public class chapter5 {
	
	public   class Node // node object 
	{
		public Integer value;
		public Node next;
		Node child;
		
		public Node(int val)
		{
			this.value = val;
			child = next = null;
		}
	}
	
	// Standalone functions 

	
	public   Node addFront(Node ptr, int value) 
	{
		Node node = new Node(value);
		
		if (ptr != null) 
		{
			node.next = ptr;
		}
		
		return node;
	}
	
	public   boolean contains (Node ptr, int val)
	{
		while (ptr != null) 
		{
			if (ptr.value == val)
			{
				return true;
			}
		}
		return false;
	}
	
	public   Node removeFront (Node ptr) 
	{
		if (ptr != null) 
		{
			ptr = ptr.next;
		}
		return ptr;
	}
	
	public   Integer front(Node ptr) 
	{
		if (ptr != null) 
		{
			return ptr.value;
		}
		return null;
	}
	
	  int length (Node ptr) 
	{
		int count = 0;
		while (ptr != null) 
		{
			count++;
			ptr = ptr.next;
		}
		return count;
	}
	
	  Integer max(Node ptr) 
	{
		Integer result = null;
		String[] v = new String[2];
		
		while (ptr != null) 
		{
			if (result == null) 
			{
				result = ptr.value;
			}
			
			else 
			{
				v[0] = String.valueOf( ptr.value);
				v[1] = String.valueOf( result);
				
				if (result instanceof Number) 
				{
					if (Integer.valueOf(v[0])  >  Integer.valueOf( v[1]) )
					{
						result = ptr.value;
					}
				}
			}
			ptr = ptr.next;
		}
			
		return result;
	}
	
	  int min(Node ptr) 
	{
		Integer result = null;
		String[] v = new String[2];
		
		while (ptr != null) 
		{
			if (result == null) 
			{
				result = ptr.value;
			}
			
			else 
			{
				v[0] = String.valueOf( ptr.value);
				v[1] = String.valueOf( result);
				
				
				
				if (result instanceof Number) 
				{
					if (Integer.valueOf(v[0])  <  Integer.valueOf( v[1]) )
					{
						result = ptr.value;
					}
				}
			}
			ptr = ptr.next;
		}
			
		return result;
	}
	
	  Number average (Node ptr) 
	{
		double sum = 0;
		int  n = 0;
		
		if (ptr == null) 
		{
			return null;
		}
		if ( ! (ptr.value instanceof Number) ) 
		{
			return null;
		}
		while (ptr != null) 
		{
			n++;
			sum += Double.valueOf( String.valueOf( ptr.value) );
			ptr = ptr.next;
		}
		if (n!=0) 
		{
			return sum / (double) n;
		}
		return null;
	}

	public   void display(Node ptr) 
	{
		while (ptr != null) 
		{
			System.out.print(String.valueOf(ptr.value) + ',');
			ptr = ptr.next; 
		}
		System.out.println("");
	}
	
	public   Integer back(Node ptr) 
	{
		if (ptr != null) 
		{
			while (ptr.next != null) 
			{
				ptr = ptr.next; 
			}
			return ptr.value;
		}
		return null;
	}
	
	public   Node removeBack (Node ptr) 
	{
		Node result = null;
		if (ptr != null) 
		{
			if (ptr.next != null) 
			{
				while (ptr.next.next != null)
				{
					ptr = ptr.next;
				}
				result= ptr.next;
				ptr.next = null;
			}
		}
		return result;
	}
	
	public   void addBack (Node ptr, int value) 
	{
		
		if (ptr == null) 
		{
			addFront(ptr, value);
		}
		
		if (ptr != null) 
		{
			while (ptr.next != null )
			{
				ptr = ptr.next;
			}
			ptr.next = new Node(value);
		}
	}

	interface compareInterface
	{
		boolean compare(Node a, Node b);	
		default void normalFunction ()
		{
			System.out.println("Thanks for using interface");
		}
	}
	
	  Node moveToFront (Node ptr, int mode) 
	{
		Node head, oldHead, prev = null;
		compareInterface interfaceSelect;
		
		if (ptr == null)
		{
			return null;
		}
		
		oldHead = head = ptr;

		while (ptr.next != null) 
		{
			switch(mode) 
			{
					
				case 0: 
					interfaceSelect = (Node  curr,  Node min) -> {
						return Double.valueOf( String.valueOf(curr.value)).compareTo(Double.valueOf( String.valueOf(min.value)) ) < 0;
					};
				break;
				
				case 1:  
					interfaceSelect = (Node  curr,  Node max) -> {
						return Double.valueOf( String.valueOf(curr.value)).compareTo(Double.valueOf( String.valueOf(max.value)) ) > 0;
					};
					break;
				
				default:
					return null;
			}
			
			if (interfaceSelect.compare(ptr.next, head))
			{
				head = ptr.next;
				prev = ptr;
			}
		
			ptr = ptr.next;
		}
		
		
		if (prev != null) 
		{
			prev.next = prev.next.next;
			head.next = oldHead;
		}
	
		return head;		
	}
	
	  Node moveMinToFront(Node ptr)
	{

		return moveToFront(ptr, 0);
	}
	
	  Node moveMaxToFront(Node ptr)
	{
		
		return moveToFront(ptr, 1);
	}
	
	  Node prependVal(Node ptr, int value, int before) 
	{
		Node oldHead = ptr, node = new Node(value);
		
		if (ptr == null) 
		{
			return node;
		}
		
		if (ptr.value  == before) 
		{
			node.next = ptr;
			return node;
		}
		
		while (ptr.next != null) 
		{
			if (ptr.next.value == before) 
			{
				node.next= ptr.next;
				ptr.next = node;
				ptr = node;
			}
			ptr = ptr.next;
		}
		
		if (node.next == null) // node not added to list
		{
			ptr.next = node;
		}
		
		return oldHead;
	}
	
	
	
	  Node appendVal(Node ptr, int value, int after) 
	{
		Node oldHead = ptr, node = new Node(value);
		
		if (ptr == null) 
		{
			return node;
		}
		
		if (ptr.value  == after) 
		{
			node.next = ptr.next;
			ptr.next = node;
			return ptr;
		}
		
		while (ptr.next != null) 
		{
			if (ptr.next.value == after) 
			{
				node.next= ptr.next.next;
				ptr.next.next = node;
				ptr = node;
			}
			ptr = ptr.next;
		}
		
		if (node.next == null) // node not added to list
		{
			ptr.next = node;
		}
		
		return oldHead;
	}
	
	  Node removeVal(Node ptr, int value)
	{
		Node newHead = ptr, marker;
		
		if (ptr == null)
		{
			return null;
		}
		
		while (ptr != null) // check front for value
		{
			if (ptr.value != value) 
			{
				break;
			}
			newHead = ptr = ptr.next;
		}
		
		if (ptr != null)
		{
			while (ptr.next != null) 
			{
				if (ptr.next.value == value) 
				{
					ptr.next = ptr.next.next;
				}
				else
				{
					ptr = ptr.next;
				}
			}
		}
		return newHead;
	}
	
	  Node splitOnValue (Node ptr, int value) 
	{
		Node newHead = null;
		
		if (ptr == null) 
		{
			return null;
		}
		
		
		if (ptr.value == value)
		{
			return ptr;
		}
		
		while (ptr.next != null) 
		{
			if (ptr.next.value == value) 
			{
				newHead = ptr.next;
				ptr.next = null;
			}
			else 
			{
				ptr = ptr.next;
			}
			
		}
		return newHead;
	}
	
	  Node concat (Node a, Node b) 
	{
		Node head = null;
		
		if (a == null) 
		{
			return b;
		}
		
		if (b == null) 
		{
			return a;
		}
		
		while (a.next != null) 
		{
			a = a.next;
		}
		
		a.next = b;
		
		return head;
	}
	
	  Node removeNegatives (Node ptr) 
	{
		Node head = null;
		
		if (ptr == null) 
		{
			return null;
		}
		
		while (ptr != null)
		{
			if (Double.valueOf(String.valueOf(ptr.value)) >= 0)
			{
				break;
			}
			head = ptr = ptr.next;
		}
		
		while (ptr.next != null) 
		{
			if (Double.valueOf(String.valueOf(ptr.next.value)) < 0) 
			{
				ptr.next = ptr.next.next;
			}
			else 
			{
				ptr = ptr.next;
			}
		}
		
		return head;
	}
	
	  Node partition (Node ptr, int value)  // partition(S) sorted 
	{
		Node head = null, part = null, partClone = null, nde;
		int ptrNextValue, ptrValue , valuePart;
		
		if (ptr == null)
		{
			return null;
		}
		
		head = ptr;
		valuePart = Integer.valueOf(String.valueOf(value));
		
		while (ptr.next != null) 
		{
			ptrNextValue = Integer.valueOf(String.valueOf(ptr.next.value));
			ptrValue = Integer.valueOf(String.valueOf(ptr.value));

					
			if (ptrNextValue < valuePart )  // less than value 
			{
				nde = ptr.next;
				ptr.next = ptr.next.next;
				
				nde.next = head; 
				head = nde;
			}
			else if (ptrNextValue == valuePart)
			{
				if (part == null)
				{

					partClone = part = ptr = ptr.next;	
				}
				else if (ptrNextValue == ptrValue) // prev.value == next.value = partition.value
				{
					partClone = ptr = ptr.next;			
				}
				else 
				{
					nde = ptr.next;
					ptr.next = ptr.next.next;
					
					// append after part(partition) node clone(s)
					nde.next = partClone.next;
					partClone = partClone.next = nde;		
				}
			}
			
			else 
			{
				ptr = ptr.next;
			}
			
		}
		
		return head;
	}
	
	  Integer secondToLastValue(Node ptr) 
	{
		
		if (ptr == null) 
		{
			return null;
		}
		
		if (ptr.next != null) 
		{
			if (ptr.next.next != null) 
			{
				while (ptr.next.next != null) 
				{
					ptr = ptr.next;
				}
				return ptr.value;
			}
		}
		return null;
	}
	
	  void removeSelf(Node ptr) 
	{
		if (ptr == null) 
		{
			return;
		}
		
		if (ptr.next == null) 
		{
			return;
		}
		
		ptr.value = ptr.next.value;
		ptr.next = ptr.next.next;
	}
	
	  Node copy (Node ptr)  // deep copy
	{
		Node head = null, tail = null;
		
		while (ptr != null)
		{
			if (head == null) 
			{
				tail = head = new Node(ptr.value);
			}
			else 
			{
				tail = tail.next =  new Node(ptr.value);
			}
			ptr = ptr.next;
		}
		
		return head;
	}
	
	  Node filter (Node ptr, int low, int high) 
	{
		int ptrValue;
		Node head; 
		
		if (ptr == null) 
		{
			return null;
		}
		
		head = ptr;
		
		while (ptr != null) 
		{
			ptrValue = Integer.valueOf(String.valueOf(ptr.value));
			if ( ptrValue >= low && ptrValue <=high ) // valid node found break loop
			{
				break;
			}
			head = ptr = ptr.next;
		}
		
		while (ptr.next != null) 
		{
			ptrValue = Integer.valueOf(String.valueOf(ptr.next.value));
			if ( ptrValue < low || ptrValue > high ) 
			{

				ptr.next = ptr.next.next;
			}
			else 
			{
				ptr = ptr.next;
			}
		}
		
		return head;
	}
	
	  Integer secondLargestValue ( Node ptr) 
	{
		Object[] maxReg = new Object[2];
		
		compareInterface cmprInterface = (Node  a,  Node b) -> {
			if (a == null || b == null) 
			{
				return false;
			}
			return Double.valueOf( String.valueOf(a.value))  >  Double.valueOf( String.valueOf(b.value)  );
		};
			
		while (ptr != null) 
		{
			if (maxReg[1] == null) 
			{
				maxReg[1] = ptr;
			}
			
			if (cmprInterface.compare(ptr, (Node) maxReg[1]))  // cast maxReg[1]!
			{
				maxReg[0] = maxReg[1];
				maxReg[1] = ptr;
			}
			else if (cmprInterface.compare(ptr, (Node) maxReg[0])) // cast maxReg[0]!
			{
				maxReg[0] = ptr;
		
			}
			ptr = ptr.next;
		}
		
		if (maxReg[1] != null)
		{
			return  ((Node)maxReg[1]).value;				
		}
		
		return null;
	}
	
	  Node zip (Node ptrA, Node ptrB) 
	{
		Node ptrAHead = null, ptrBNext = null;
		
		if (ptrA == null) 
		{
			return ptrB;
		}
		ptrAHead = ptrA;
		while (ptrA.next != null && ptrB != null) 
		{
			ptrBNext = ptrB.next;
			ptrB.next = ptrA.next;
			ptrA.next = ptrB;
			ptrB = ptrBNext; // one step forward in B list  
			ptrA = ptrA.next.next; //note* ptrA.next is inserted B element
		}
		
		while (ptrA.next != null) // move to last node in A list
		{
			ptrA = ptrA.next;
		}
		
		ptrA.next = ptrB; // append remaining 
		
		return ptrAHead;
	}
	
	  void dedupe(Node ptr) 
	{
		Node bufferHead, bufferTail, bufferptr;
		
		compareInterface cmprInterface = (Node a,  Node b) -> {
			if (a == null || b == null) 
			{
				return false;
			}
			return Double.valueOf( String.valueOf(a.value)).compareTo(Double.valueOf( String.valueOf(b.value)) ) == 0;
		};
		
		if (ptr == null) 
		{
			return;
		}
		

		bufferHead = bufferTail = new Node(ptr.value);
		
		while (ptr.next != null) 
		{
			bufferptr = bufferHead;     

			while (bufferptr != null)   // search for dup
			{
				if (cmprInterface.compare(ptr.next, bufferptr))
				{
					break;
				}
				bufferptr = bufferptr.next;
			}
			
			if (bufferptr != null)  // remove ptr.next
			{
				display(bufferptr);

				ptr.next = ptr.next.next;
			}
			else 
			{
				ptr = ptr.next;
				bufferTail = bufferTail.next = new Node(ptr.value);

			}
		}
	}
	
	  void dedupeWithOutBuffer(Node ptr)   // (N^2/2 or N^2 worst case ) runtime
	{
		Node walk;
		compareInterface cmprInterface = (Node  a,  Node b) -> {
			if (a == null || b == null) 
			{
				return false;
			}
			return Double.valueOf( String.valueOf(a.value)).compareTo(Double.valueOf( String.valueOf(b.value)) ) == 0;
		};
		
		while (ptr.next != null) 
		{
			walk  = ptr;
			while (walk.next != null)   // search for dups 
			{
				if (cmprInterface.compare(ptr, walk.next))   // dup!
				{
					walk.next  = walk.next.next;  // remove!
				}
				else 
				{
					walk = walk.next;    // walk
				}
			}
			ptr = ptr.next; // move ptr forward 
		}
		
	}



	public  void main (String[] args)
	{
//		List<Integer> w = new List<Integer>();
		Node head = null, head2;
		head = addFront(head, -1);
		head = addFront(head, 2);
		head = addFront(head, 3);
		head = addFront(head, -20);
		head = addFront(head, -9);
		head = addFront(head, 4000);
		head = addFront(head, 56);
		head = addFront(head, 2);
		head = addFront(head, 9);
		head = addFront(head, 5);
               
		head = moveMaxToFront(head);
		head = prependVal(head, 100, -100);
		
//		head = w.appendVal(head,  120, -9);
		head2 = splitOnValue(head,  -9);

//		head = w.partition(head, 2);
//		head = w.copy(head);
		
		display(head);
		display(head2);
		head = zip(head, head2);
		
		System.out.println("");
		display(head);
		
		dedupeWithOutBuffer(head);
		display(head);


	}

}
