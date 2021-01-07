package algo;

import java.util.ArrayList;
import java.util.HashMap;
import algo.Chapter6.Stack;

import java.lang.Thread;

public class Chapter13 
{
	public static int[] interleaveArrays(int[] a, int[] b)
	{
		int aIdx, bIdx, idx;
		int result[] = new int[a.length + b.length];
		
		if (a.length == 0) 
		{
			return b;
		}
		
		if (b.length == 0)
		{
			return a;
		}
		
		idx = aIdx = bIdx= 0;
		
		do
		{
			
			if (aIdx < a.length)
			{
				result[idx++] = a[aIdx++];
			}
			
			if (bIdx < b.length)
			{
				result[idx++] = b[bIdx++];
			}
			
		}
		while (aIdx+ bIdx < a.length + b.length);
	
		return result;
	}
	
	public static int[] mergeSortedArray(int[] a, int[] b)
	{
		int aIdx, bIdx, idx;
		int result[] = new int[a.length + b.length];
		
		if (a.length == 0) 
		{
			return b;
		}
		
		if (b.length == 0)
		{
			return a;
		}
		
		idx = aIdx = bIdx= 0;
		
		do
		{
			if (aIdx >= a.length)   // a limit!
			{
				result[idx++] = b[bIdx++];
			}
			
			else if (bIdx >= b.length)    // b limit!
			{
				result[idx++] = a[aIdx++];
			}
			
			else if (a[aIdx] <= b[bIdx]) 
			{
				result[idx++] = a[aIdx++];
			}
			
			else if (b[bIdx] <= a[aIdx]) 
			{
				result[idx++] = b[bIdx++];
			}
		
			
		}
		while (aIdx+ bIdx < a.length + b.length);
		

		return result;
	}
	
	public static void minimalThreeRangeSolver(int[] a, int[] b, int[] c, Integer minMeta[] ,ArrayList<Integer> buffer)
	{
		int arraySelect[];
		ArrayList<Integer> copyBuffer;
		int min, max;
		if (buffer == null) 
		{
			buffer = new ArrayList<Integer>();
		}
		
		if (buffer.size() == 3) 
		{
			min = max = buffer.get(0);
			for (int retVal: buffer)
			{
				if (retVal < min) 
				{
					min = retVal;
				}
				
				if (retVal > max)
				{
					max = retVal;
				}
			}
			
			if ( (minMeta [0] == null)  || ( max - min < minMeta[1] - minMeta[0] ) )
			{
				minMeta[0] = min;
				minMeta[1] = max;
			}
			
		}
		
		switch (buffer.size())
		{
		case 0:
			arraySelect = a;
			break;
		case 1: 
			arraySelect = b;
			break;
		case 2:
			arraySelect = c;
			break;
		default:
			arraySelect = new int[0];
		}
		
		for (int retVal: arraySelect) 
		{
			copyBuffer = new ArrayList<Integer>();
			
			for (int i = 0; i < buffer.size(); i++)
			{
				copyBuffer.add(buffer.get(i));
			}
			
			copyBuffer.add(retVal);
			minimalThreeRangeSolver(a, b, c, minMeta, copyBuffer);
		}
	}
	
	public static Integer[] minimalThreeRange(int[] a, int[] b, int[] c)
	{
		Integer[] minRange = {null,null};
		minimalThreeRangeSolver(a, b, c, minRange, null);
		return minRange;
	}
	
	public static ArrayList<Integer> intersectSortedArray(int []a, int[] b) 
	{
		 ArrayList<Integer> res = new  ArrayList<Integer>();
		 int aIdx, bIdx;
		 
		 if (a.length == 0) 
		 {
			 for (int retVal: b) 
			 {
				 res.add(retVal);
			 }
		 }
		 
		 if (b.length == 0) 
		 {
			 for (int retVal: a) 
			 {
				 res.add(retVal);
			 }
		 }
		 aIdx = bIdx = 0;
		 do
			{
				if (aIdx >= a.length )   
				{
					bIdx++;
				}
				
				else if (bIdx >= b.length)    
				{
					aIdx++;
				}
				else if (a[aIdx] < b[bIdx]) 
				{
					aIdx++;
				}
				else if (a[aIdx] > b[bIdx]) 
				{
					bIdx++;
				}
				else if (a[aIdx] == b[bIdx]) 
				{
					res.add(a[aIdx]  ) ;
					aIdx++;
					bIdx++;
				}
				
			}
			while (aIdx+ bIdx < a.length + b.length);
		 
		 return res;
	}
	
	public static ArrayList<Integer> intersectSortedArrayDedupe(int []a, int[] b) 
	{
		 ArrayList<Integer> res = new  ArrayList<Integer>();
		 int aIdx, bIdx;
		 Integer currMin = null;
		 
		 if (a.length == 0) 
		 {
			 for (int retVal: b) 
			 {
				 res.add(retVal);
			 }
		 }
		 
		 if (b.length == 0) 
		 {
			 for (int retVal: a) 
			 {
				 res.add(retVal);
			 }
		 }
		 aIdx = bIdx = 0;
		 do
			{
				if (aIdx >= a.length )   
				{
					bIdx++;
				}
				
				else if (bIdx >= b.length)    
				{
					aIdx++;
				}
				else if (a[aIdx] < b[bIdx]) 
				{
					aIdx++;
				}
				else if (a[aIdx] > b[bIdx]) 
				{
					bIdx++;
				}
				else if (a[aIdx] == b[bIdx]) 
				{
					if (currMin == null || currMin != a[aIdx])
					{
						res.add(currMin = a[aIdx]);
					}
					aIdx++;
					bIdx++;
				}
			}
			while (aIdx+ bIdx < a.length + b.length);
		 
		 return res;
	}
	
	public static ArrayList<Integer> unionSortedArray (int [] a, int [] b)
	{
		 ArrayList<Integer> res = new  ArrayList<Integer>();
		 int aIdx, bIdx;
		 
		 if (a.length == 0) 
		 {
			 for (int retVal: b) 
			 {
				 res.add(retVal);
			 }
		 }
		 
		 if (b.length == 0) 
		 {
			 for (int retVal: a) 
			 {
				 res.add(retVal);
			 }
		 }
		 aIdx = bIdx = 0;
		 
		 // a list has priority
		 do 
		 {
			 if (aIdx == a.length )   
			 {	
				 if (b[bIdx]  == a[aIdx - 1]) // already included 
				 {
					 bIdx++;
				 }
				 else 
				 {
					 res.add(b[bIdx++]);
				 }
			 }
			 else if (bIdx >= b.length)    
			 {
				 res.add(a[aIdx++]);
			 }
			 
			 else if (b[bIdx] == a[aIdx]) 
			 {
				 bIdx++;
			 }
			 else if (b[bIdx] < a[aIdx]) 
			 {
				 res.add(b[bIdx++]);
			 }
			 else if (a[aIdx] < b[bIdx]) 
			 {
				 res.add(a[aIdx++]);
			 }
			
		 }
		 while (aIdx+ bIdx < a.length + b.length);
		 
		 return res;
	}
			
	public static ArrayList<Integer> unionSortedArrayDedupe (int [] a, int [] b)
	{
		ArrayList<Integer> sortedUnion =  unionSortedArray(a, b);
		int index = 1;
		while (index < sortedUnion.size())
		{
			if (sortedUnion.get(index - 1)   == sortedUnion.get(index ) )
			{
				sortedUnion.remove(index - 1);
			}
			else 
			{
				index++;
			}
		}
		return sortedUnion;
		
	}
	
	public static ArrayList<Integer> intersectionUnsortedArraysInPlace(ArrayList<Integer> a, ArrayList<Integer> b )
	{
		int intersectionCount = 0;
		
		for (int i = 0; i < b.size(); i++)
		{
			for (int k = intersectionCount; k < a.size(); k++) 
			{
				if (b.get(i) == a.get(k))
				{
					a.add(0, a.remove(k));
					intersectionCount++;
					break;
				}
			}
		}
		
		while (a.size() > intersectionCount) 
		{
			a.remove(intersectionCount);
		}
		
		return a;
	}
	
	public static ArrayList<Integer> intersectionUnsortedArrays(ArrayList<Integer> a, ArrayList<Integer> b )
	{
		int intersectionCount = 0;
		
		for (int i = 0; i < b.size(); i++)
		{
			for (int k = intersectionCount; k < a.size(); k++) 
			{
				if (b.get(i) == a.get(k))
				{
					a.add(0, a.remove(k));
					intersectionCount++;
					break;
				}
			}
		}
		
		while (a.size() > intersectionCount) 
		{
			a.remove(intersectionCount);
		}
		
		return a;
	}
	
	public static ArrayList<Integer> intersectionUnsortedArrays (int a[], int b[]) 
	{
		ArrayList<Integer> res = new ArrayList<Integer>();
		boolean isWritable = false;
		
		for (int i = 0; i < a.length; i++) 
		{
			for (int k = 0; k < b.length; k++) 
			{
				if (a[i] == b[k])
				{
					isWritable = true;
					
					for (int ret: res)
					{
						if (ret == k) 
						{
							isWritable = false;
						}
					}
					
					if (isWritable) 
					{
						res.add(k);
						break;
					}
				}
			}
		}
		
		// map index 
		for (int i = 0; i < res.size(); i++) 
		{
			res.set(i, b[res.get(i) ]);
		}
		
		return res;
	}
	
	public static ArrayList<Integer> unionUnsortedArray (int[] a, int[] b)
	{
		ArrayList<Integer> res = new ArrayList<Integer>();
		int t0, t1;
		
		if (a.length == 0) 
		 {
			 for (int retVal: b) 
			 {
				 res.add(retVal);
			 }
			 return res;
		 }
		 
		 if (b.length == 0) 
		 {
			 for (int retVal: a) 
			 {
				 res.add(retVal);
			 }
			 return res;
		 }
		 
		 for (int retVal: a) 
		 {
			 res.add(retVal);
		 }
		 
		 for (int val: b) 
		 {
			 t0 = t1 = 0;
			 for (int retValSub: b)
			 {
				 if (retValSub == val)
				 {
					 t0++;
				 }
			 }
			 
			 for (int retValSub: res)
			 {
				 if (retValSub == val)
				 {
					 t1++;
				 }
			 }
			 
			 if (t0 > t1) 
			 {
				 for (int i = 0 ; i < t0- t1; i++)
				 {
					 res.add(val);
				 }
			 }
		 }
		 
		 return res;
	}
	
	public static void unionUnsortedArrayInPlace(ArrayList<Integer> a, ArrayList<Integer> b)
	{
		int pos = a.size();
		int tmp;
		int left, right;
		int removeCount;
		
		for (int retVal: b)
		{
			a.add(retVal);
		}
		
		for (int i = 0; i < pos; i++)
		{
			tmp = a.get(i);
			left = right = 0;
			
			for (int k = 0; k < a.size(); k++)
			{
				if (k < pos) 
				{
					if (a.get(k) == tmp)
					{
						left++;
					}
				}
				
				if (k >= pos ) 
				{
					if (a.get(k) == tmp) 
					{
						right++;
					}
				}
			}
			
			// remove intersection/ left side twins from right side 
			removeCount = left - right;
			for (int k = pos; k < a.size() && removeCount >=0; k++) 
			{
				if (a.get(k) == tmp)
				{
					a.remove(k);
					removeCount--;
				}
			}
		}
		
	}
	
	private static void swap (ArrayList<Integer> collection, int i, int j)
	{
		int tmp;
		if (i ==j)
		{
			return;
		}
		tmp = collection.get(i);
		collection.set(i, collection.get(j));
		collection.set(j, tmp);
	}
	
	private static void swap (int[] collection, int i, int j)
	{
		int tmp;
		if (i ==j)
		{
			return;
		}
		tmp = collection[i];
		collection[i] = collection[j];
		collection[j] = tmp;
	}
	
	public static ArrayList<Integer> unionUnsortedArrayInPlaceDedupe(ArrayList<Integer> a, ArrayList<Integer> b)
	{
		ArrayList<Integer> res = new ArrayList<Integer>();
		int index = 0;

		for (int retVal: a) 
		 {
			 res.add(retVal);
		 }
		 
		 for (int retVal: b) 
		 {
			 res.add(retVal);
		 }
		 
		 // partition (s) 
		 for (int retVal: a) 
		 {
			 index = 0;
			 for (int i = 0; i < res.size(); i++) 
			 {
				 if (res.get(i) <= retVal) 
				 {
					 swap(res, index, i);
					 index++;
				 }
			 }
		 }
		 
		 for (int retVal: b) 
		 {
			 index = 0;
			 for (int i = 0; i < res.size(); i++) 
			 {
				 if (res.get(i) <= retVal) 
				 {
					 swap(res, index, i);
					 index++;
				 }
			 }
		 }
		 
		 
		 // remove adjacents clones 
		 index = 1; 
		 while (index < res.size()) 
		 {
			 if (res.get(index - 1) != res.get(index)) 
			 {
				 index++;
			 }
			 else 
			 {
				 res.remove(index);
			 }
		 }
		 
		 return res;
	}
	
	public static boolean subsetSortedArray (int[] a, int[] b) 
	{
		int count;
		
		for (int i = 0; i < a.length; i++) 
		{
			count = 0;
			for (int k = 0; k < b.length; k++)
			{
				if ( (i + k) < a.length) 
				{
					if (a[i + k] == b[k])  
					{
						count++;
					}
					
					if (count == b.length)
					{
						return true;
					}		
				}
			}
		}
		return false;
	}
	

	public static boolean subsetUnSortedArray (int[] a, int[] b) 
	{
		HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
		
		for (int i = 0; i < a.length / 2; i++) 
		{
			if (!map.containsKey(a[i]))
			{
				map.put(a[i], 1);
			}
			
			if (!map.containsKey(a[a.length - 1- i]))
			{
				map.put(a[a.length - 1 - i], 1);
			}
		}
		
		for (int i = 0; i < b.length / 2; i++) 
		{
			if (!map.containsKey(b[i])  || !map.containsKey(b[b.length - 1- i]))
			{
				return false;
			}
		}
		
		
		return true;
	}
	
	
	public static class PriQNode 
	{
		long pri;
		int value;
		PriQNode next;
		
		public PriQNode(int value, long pri) 
		{
			this.pri = pri;
			this.value = value;
		}
	}
	
	public static class PriQueue
	{
		private PriQNode head, tail;
		
		PriQueue() 
		{
			head = tail = null;
		}
		
		public PriQNode getHead ()
		{
			return head;
		}
		
		public PriQNode getTail ()
		{
			return tail;
		}
		
		public synchronized Integer pop()
		{
			Integer result = null;
			if (head != null) 
			{
				if (head == tail) 
				{
					tail = head.next;
				}
				result = head.value;
				head = head.next;
			}
			return result;
		}
		
		public synchronized void  push (int value, long pri) 
		{
			PriQNode buffer, runner, newNode = new PriQNode(value, pri);
			
			if (head == null) 
			{
				head = tail = newNode;
			}
			else 
			{
				if ((pri < head.pri) || (pri == head.pri && value < head.value))  // insert new head 
				{
					newNode.next = head;
					head = newNode;
				}
				else 
				{
					runner = head;
					while (runner.next != null)   // search for prio in list  
					{
						if ( (pri < runner.next.pri) || (pri == runner.next.pri && value < runner.next.value) )  // insert between two nodes 
						{
							buffer = runner.next; 
							runner.next = newNode;
							newNode.next = buffer;
							return;
						}
						runner = runner.next; 
					}
					
					tail = runner.next = newNode; // insert  new tail
				}
			}
		}
		
		public synchronized void remove (int value, int pri)
		{
			PriQNode  runner = head;
			
			if (runner == null) 
			{
				return;
			}
			
			// remove head
			while (runner.value == value && runner.pri == pri)
			{
				head = runner = runner.next; 
			}
			
			while (runner.next != null) 
			{
				if (runner.next.value == value && runner.next.pri == pri) 
				{
					runner.next = runner.next.next;
					break;
				}
				runner = runner.next;
			}
		}
		
		public boolean isEmpty ()
		{
			return (head == null);
		}
		
		public synchronized int size ()
		{
			int count = 0;
			PriQNode node = this.head;
			while (node != null) 
			{
				node = node.next;
				count++;
			}
			return count;
		}
		
	}
	
	public static void PriQueueDisplay(PriQNode node)
	{
		while (node != null) 
		{
			System.out.print("{ pri:" + node.pri + "," + "value: " + node.value + "} ");
			node = node.next;
		}
		System.out.println();
	}
	

	
	
	public static class Sequencer
	{
		private Thread play_t;
		private boolean playEnabled = false;
		private PriQueue queue;
		
		Sequencer()
		{
			queue = new PriQueue();
			play_t = new Thread(new playMessagesRunnable());
		}
		
		public  class playMessagesRunnable implements Runnable
		{
			public void run() 
			{
				int watchdog = 0;
				
				while (watchdog < 2) 
				{
					try
					{
						// delay 5 seconds 
						Thread.sleep(5000);  
						
						// conditional blocks checks queue and increments watchdog alarm
						if (queue.isEmpty()) 
						{
							watchdog++;
						}
						else  if (!queue.isEmpty())
						{
							watchdog = 0;
							while (queue.getHead() != null)  
							{
								if (queue.head.pri >= System.currentTimeMillis())
								{
									System.out.println("playing timestamp: " + queue.getHead().pri+ " value: " + queue.getHead().value );
									queue.pop();
								}
							}
						}
					}
					catch(InterruptedException exception) 
					{
						System.out.println(exception.getStackTrace());
					}
				}
			}
		}
		
		public void sequenceMessage(long timestamp, int value)
		{
			System.out.println("loaded " + timestamp);
			queue.push(value, timestamp);
		}
		
		public void playMessages()
		{
			if (!playEnabled)
			{
				playEnabled = true;
			}
			
			if (!play_t.isAlive())
			{
				play_t.start();	
			}
			else 
			{
				System.out.println("playback enabled ");
			}
		}
		
	}
	
	public static class MinHeap
	{
		ArrayList<Integer> array;
		
		MinHeap() 
		{
			array = new ArrayList<Integer>();
			array.add(null);
		}
		
		public int size()
		{
			return array.size();
		}
		
		public boolean isEmpty()
		{
			return array.size() == 1;
		}
		
		public Integer top () 
		{
			if (array.size() > 1)
			{
				return array.get(1);
			}
			return null;
		}
		
		public boolean contains(int value) 
		{
			for (int i = 1; i < array.size(); i++) 
			{
				if (value == array.get(i))
				{
					return true;
				}
			}
			return false;
		}
		
		public void insert(int val)
		{
			int parentPos;
			int currMinIndex;
			int size;
			
			array.add(val);

			if (array.size() <= 2) 
			{
				return;
			}
			
			size = array.size() - 1;
			parentPos = size / 2;
			
			do 
			{
				currMinIndex = parentPos;

				if (parentPos*2  < array.size())
				{
					if (array.get(parentPos*2) < array.get(currMinIndex) )
					{
						currMinIndex = parentPos*2;
					}		
				}
				
				if ( parentPos*2 + 1 < array.size())
				{
					if (  array.get(parentPos*2  + 1) < array.get(currMinIndex) )
					{
						currMinIndex = parentPos*2 + 1;
					}		
				}

				if (currMinIndex == parentPos)
				{
					break;
				}
				
				swap(array, currMinIndex, parentPos);
				
				parentPos /= 2;  // move position up tree
			}
			while (parentPos >= 1);
		}
		
		public void display()
		{
			for (int i = 1; i < array.size(); i++) 
			{
				System.out.print(array.get(i) + ",");
			}
			System.out.println();
		}
		
		public Integer extract ()
		{
			int parentPos;
			int currentMaxIndex;
			Integer result;
			
			if (array.isEmpty())
			{
				return null;
			}
			
			// swap top with lowest leaf
			swap(array, 1, array.size() - 1);
		
			// move new top if needed (demote)
			parentPos = 1;
			do
			{
				currentMaxIndex = parentPos;
				if (parentPos*2 < array.size() - 1)
				{
					if (array.get(currentMaxIndex) > array.get(parentPos*2))
					{
						currentMaxIndex = parentPos*2;
					}
				}
				
				if (parentPos*2 + 1 < array.size() - 1)
				{
					if ( array.get(currentMaxIndex) > array.get(parentPos*2 + 1))
					{
						currentMaxIndex = parentPos*2 + 1;
					}
				}
				
				if (currentMaxIndex == parentPos) 
				{
					break;
				}
				
				swap(array, currentMaxIndex, parentPos);
				
				parentPos = currentMaxIndex;  // move position down tree
			}
			while(parentPos < array.size());
			
			
			// pluck
			result = array.remove(array.size() - 1);
			
			return result;
		}
		
		public void heapify (int [] array) // minheap 
		{
			int parentPos;
			int currMinIndex;
			
			if (array.length == 0) 
			{
				return;
			}
			
			for (int i = array.length - 1; i > 0; i--)  
			{
				parentPos = i / 2;  // next parent position 
				
				do 
				{
					currMinIndex = parentPos;
					
					if ( parentPos*2 + 1 < array.length)
					{
						if (  array[parentPos*2 + 1] < array[currMinIndex] )
						{
							currMinIndex = parentPos*2 + 1;
						}
					}
					
					if (parentPos*2 + 2 < array.length)
					{
						if (  array[parentPos*2 + 2] < array[currMinIndex] )
						{
							currMinIndex = parentPos*2 + 2;
						}	
					}

					if (currMinIndex == parentPos)
					{
						break;
					}
					
					swap(array, currMinIndex, parentPos);
				
					parentPos /=2;

				}
				while(parentPos >= 0);
			}
		}

	}
	
	public static class MaxHeap extends MinHeap
	{
		public void insert(int val)
		{
			int parentPos;
			int currMinIndex;
			int size;
			
			array.add(val);

			if (array.size() <= 2) 
			{
				return;
			}
			
			size = array.size() - 1;
			parentPos = size / 2;
			
			do 
			{
				currMinIndex = parentPos;
				if (parentPos*2  < array.size())
				{
					if (array.get(parentPos*2) > array.get(currMinIndex) )
					{
						currMinIndex = parentPos*2;
					}		
				}
				
				if ( parentPos*2 + 1 < array.size())
				{
					if (  array.get(parentPos*2  + 1) > array.get(currMinIndex) )
					{
						currMinIndex = parentPos*2 + 1;
					}		
				}

				if (currMinIndex == parentPos)
				{
					break;
				}
				
				swap(array, currMinIndex, parentPos);
				
				parentPos /= 2;  // move position up tree
			}
			while (parentPos >= 1);
		}
		
		public Integer extract ()
		{
			int parentPos;
			int currentMaxIndex;
			Integer result;
			
			if (array.isEmpty())
			{
				return null;
			}
			
			// swap top with lowest leaf
			swap(array, 1, array.size() - 1);
		
			// move new top if needed (demote)
			parentPos = 1;
			do
			{
				currentMaxIndex = parentPos;
				if (parentPos*2 < array.size() - 1)
				{
					if (array.get(currentMaxIndex) < array.get(parentPos*2))
					{
						currentMaxIndex = parentPos*2;
					}
				}
				
				if (parentPos*2 + 1 < array.size() - 1)
				{
					if ( array.get(currentMaxIndex) < array.get(parentPos*2 + 1))
					{
						currentMaxIndex = parentPos*2 + 1;
					}
				}
				
				if (currentMaxIndex == parentPos) 
				{
					break;
				}
				
				swap(array, currentMaxIndex, parentPos);
				
				parentPos = currentMaxIndex;  // move position down tree
			}
			while(parentPos < array.size());
			
			
			// pluck
			result = array.remove(array.size() - 1);
			
			return result;
		}
		
		public void heapify (int [] array) // maxheap 
		{
			int parentPos;
			int currMinIndex;
			
			if (array.length == 0) 
			{
				return;
			}
			
			for (int i = array.length - 1; i > 0; i--)  
			{
				parentPos = i / 2;  // next parent position 
				
				do 
				{
					currMinIndex = parentPos;
					
					if ( parentPos*2 + 1 < array.length)
					{
						if (  array[parentPos*2 + 1] > array[currMinIndex] )
						{
							currMinIndex = parentPos*2 + 1;
						}
					}
					
					if (parentPos*2 + 2 < array.length)
					{
						if (  array[parentPos*2 + 2] > array[currMinIndex] )
						{
							currMinIndex = parentPos*2 + 2;
						}	
					}

					if (currMinIndex == parentPos)
					{
						break;
					}
					
					swap(array, currMinIndex, parentPos);
				
					parentPos /=2;

				}
				while(parentPos >= 0);
			}
		}
	}
	
	public static void heapSort (int [] array)
	{
		int size;
		int parentPos;
		int currMinIndex;
		
		if (array.length == 0) 
		{
			return;
		}
		
		for (int k = 0; k < array.length; k++) 
		{
			// heapify (arr.length - k) elements 
			
			size = array.length  - 1;
			parentPos = (size - k) / 2;
			
			do 
			{
				currMinIndex = parentPos;
				
				if ( parentPos*2 + 1 < array.length - k)
				{
					if (  array[parentPos*2 + 1] > array[currMinIndex] )
					{
						currMinIndex = parentPos*2 + 1;
					}
				}
				
				if (parentPos*2 + 2 < array.length - k)
				{
					if (  array[parentPos*2 + 2] > array[currMinIndex] )
					{
						currMinIndex = parentPos*2 + 2;
					}	
				}
				
				swap(array, currMinIndex, parentPos);
				
				parentPos -= 1; // evaluate each parent available node  

			}
			while(parentPos >= 0);
			
			// swap top to active tail
			swap(array, 0, array.length - 1 - k);
		}
	}
	
	public static class MedianOfDataStream  // DIFFICULT PROBLEM GEEZ! 
	{	
		double median;
		MinHeap minheap;
		MaxHeap maxheap;
		int balance;
		
		MedianOfDataStream()
		{
			minheap = new MinHeap();
			maxheap = new MaxHeap();
		}
		
		public double read (int data) 
		{
			
			balance = maxheap.size() - minheap.size();
			
			if (minheap.isEmpty() && maxheap.isEmpty()) 
			{
				maxheap.insert(data);	
			}
			
			else if (minheap.isEmpty())
			{
				if ( maxheap.top() > data )
				{
					minheap.insert(maxheap.extract());
					maxheap.insert(data);
				}
				else 
				{
					minheap.insert(data);
				}
			}
			
			else if ( ( data >  maxheap.top() ) && (data < minheap.top()  ) )
			{
				
				if (balance == 0) 
				{
					if ( Math.abs(data - maxheap.top() ) <  Math.abs(data - minheap.top() ) )
					{
						maxheap.insert(data);
					}
					else 
					{
						minheap.insert(data);
					}
				}
				
				if (balance < 0) //  minheap  larger than maxheap  
				{
					maxheap.insert(data);
				}
				
				if (balance > 0) // maxheap larger than minheap  
				{
					minheap.insert(data);
				}
				
			}
			
			else if (data <= maxheap.top() && data < minheap.top() )
			{
				
				if (balance == 0) 
				{
					Integer tmp = maxheap.extract();
					minheap.insert(tmp);
					maxheap.insert(data);
				}
				
				if (balance < 0)  //  minheap  larger than maxheap  
				{
					maxheap.insert(data);
				}
		
				if (balance > 0) // maxheap larger than minheap  
				{
					minheap.insert(maxheap.extract());
					maxheap.insert(data);			
				}
			}
			
			else if (data > maxheap.top() && data >= minheap.top())
			{
				if (balance == 0)
				{
					minheap.insert(data);
				}
				
				if (balance < 0) // minheap larger than maxheap  
				{
					maxheap.insert(minheap.extract());
					minheap.insert(data);
				}
				
				if (balance > 0) // maxheap larger than minheap
				{
					minheap.insert(data);
				} 
			}
			
			if (maxheap.size() == 0) 
			{
				median = minheap.top();
			}
			
			if (minheap.size() == 0) 
			{
				median = maxheap.top();
			}
			
			if ( maxheap.size()  == minheap.size() ) 
			{
				median = ( minheap.top()  - maxheap.top() ) / 2;
			}
			
			if (maxheap.size() > minheap.size()) 
			{
				median = (double) maxheap.top();
			}
			
			if (minheap.size() > maxheap.size()) 
			{
				median = (double) minheap.top();
			}
			
			return median;
		}
		
	}
	
	public static class QueueTwoStack 
	{
		Stack a, b;
		
		public QueueTwoStack() 
		{
			a = new Stack();
			b = new Stack();
		}
		
		public void enqueue (int value) 
		{
			if (a.isEmpty())
			{
				a.push(value);
			}
			else 
			{
				while (!a.isEmpty())
				{
					b.push(a.pop());
				}
				b.push(value);
				
				while (!b.isEmpty()) 
				{
					a.push(b.pop());
				}
			}
		}
		
		public Integer dequeue () 
		{
			Integer result = null;
			if (!a.isEmpty())
			{
				result = a.pop();
			}
			return result;
		}
		
		public Integer front () 
		{
			Integer result = null;
			if (!a.isEmpty())
			{
				result = a.top();
			}
			return result;
		}
		
		public long size () 
		{
			return a.size();
		}
		
		public void display()
		{
			a.debugDisplay();
		}
		
		public boolean isEmpty() 
		{
			return a.isEmpty();
		}
	}


}
