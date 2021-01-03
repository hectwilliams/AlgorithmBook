package algo;
import java.util.ArrayList;
import java.util.HashMap;

import algo.Chapter12.Name;
import algo.Chapter5.*;

public class Chapter12 {
	
	private static void swap(int arr[], int i, int k)
	{
		if (i == k) 
		{
			return;
		}
		int tmp = arr[i];
		arr[i] = arr[k];
		arr[k] = tmp;
	}
	
	private static void swap(Name[] names, int i, int k)
	{
		Name tmp = names[i];
		names[i] = names[k];
		names[k] = tmp;
	}
	
	public static void bubbleSort(int arr[])
	{
		for (int i = 0; i < arr.length; i++)
		{
			for (int k = 1; k < arr.length; k++) 
			{
				if (arr[k - 1] > arr[ k ])
				{
					swap(arr, k, k - 1);
				}
			} 
		}
	}
	
	public static void selectionSort(int arr[])
	{
		int currMinIndex;
		int index = 0;
		
		for (int i = 0; i < arr.length; i++)
		{
			currMinIndex = i;
			for ( index = i; index < arr.length; index++)
			{
				if (arr[index] < arr[currMinIndex])
				{
					currMinIndex = index;
				}
			}
			
			if (currMinIndex != i)
			{
				swap(arr, i, currMinIndex);
			}
		}
	}
	
	public static Node selectionSortSList (Node node)
	{
		Node runner, it;
		Node minNode, minNodePrev; 
		Node head;
		
		minNodePrev = minNode = runner = head = node;
		
		// head search first 
		{
			while ( runner.next != null) 
			{
				if (runner.next.value < minNode.value) 
				{
					// store min data 
					minNodePrev = runner;
					minNode = runner.next;
				}
				runner = runner.next; 
			}
			
			minNodePrev.next = minNodePrev.next.next;
			minNode.next = head;
			head = minNode;
		}
		
		// remaining nodes (excluding head) 

		it = head;
		
		while (it.next != null) 
		{

			runner = minNode = it.next; 
			while ( runner.next != null) 
			{
				if (runner.next.value < minNode.value) 
				{
					// store min data 
					minNodePrev = runner;
					minNode = runner.next;
				}
				runner = runner.next; 
			}
			
			if (minNode != it.next) 
			{
				minNodePrev.next = minNodePrev.next.next;
				minNode.next = it.next;
				it.next = minNode;
			}
			
			it = it.next;
		}
		
		return head;
	}
	
	public static Node bubbleSortSList (Node node)
	{
		Node runner, runnerprev,  bufferNode, head;
		boolean wasReordered = false;
		
		runner = head = node;

		do
		{
			wasReordered = false;
			
			// evaluate head and adjacent node 
			if (head.next != null) 
			{
				if (head.next.value < head.value)
				{
					bufferNode = head.next;   /// buffer swapped node 
					head.next = head.next.next; 
					bufferNode.next = head;
					head = bufferNode;
					wasReordered = true;
				}
				
			// evaluate remaining nodes 
		
				runnerprev = head;
				runner = head.next;
				bufferNode = null;
				
				while (runner.next != null) 
				{
					if (runner.next.value < runner.value) 
					{
						bufferNode = runner.next;
						runner.next = runner.next.next;
						bufferNode.next = runner;
						runner = runnerprev.next = bufferNode;
						wasReordered = true;
					}
					
					runnerprev = runner;
					runner = runner.next;
				}
			}
			
		}
		while (wasReordered);
		
		return head;
	}
	
	public static class  Name
	{
		private String firstName;
		private String lastName;
		
		Name(String first, String last) 
		{
			firstName = first;
			lastName = last;
		}
		
		String getFirstName () 
		{
			return firstName;
		}
		
		String getLastName ()
		{
			return lastName;
		}
	}
	
	public static void multiKeySort(Name[] names)
	{
		for (int i = 0; i < names.length; i++) 
		{
			for (int k = 1; k < names.length; k++) 
			{
				if ( names[k - 1].getLastName().compareTo(names[k].getLastName() )  > 0 )   //  primary
				{
					swap(names, k, k - 1);
				}
				else if ( names[k - 1].getFirstName().compareTo( names[k].getFirstName() )  >  0 ) //  secondary
				{
					 if ( names[k - 1].getLastName().compareTo( names[k].getLastName() ) == 0  ) 
					 {
						 swap(names, k, k - 1);
					 }
				}
			}
		}
	}
	
	public static void insertionSort (int[] arr) 
	{
		int currIndex = 1;
		
		while (currIndex < arr.length)
		{
			for (int i = currIndex; i > 0; i--)
			{
				if (arr[i] < arr[i - 1])
				{
					swap(arr, i, i - 1);
				}
			}
			
			currIndex++;
		}
	}
	
	public static Node insertionSort (Node node)  // annoyed by this problem for some reason!
	{
		Node head, currNode, currNodePrev;
		Node runner, buffer, runnerprev;
		
		currNodePrev = null;
		currNode = head = node;
		
		while (currNode != null)
		{
			runner = head;
			runnerprev = null;
	
			while (runner != currNode)
			{
				if (  currNode.value < runner.value ) 
				{
					buffer = currNode; 
					currNodePrev.next = currNodePrev.next.next;

					if (runnerprev == null) 
					{
						currNode.next = runner;
						head = currNode;
					}
					
					else 
					{
						buffer.next = runnerprev.next;
						runnerprev.next = buffer; 
					}
					
					break;
				}
				
				runnerprev = runner;
				runner = runner.next;
			}
			
			currNodePrev = currNode;
			currNode = currNode.next;
		}
		
		return head;
	}
	
	public static  void combine ( ArrayList<Integer> arr1, ArrayList<Integer> arr2 )
	{
		int idx1, idx2;
		
		idx1 = idx2 = 0;
		
		while (idx1 < arr1.size() && idx2 < arr2.size() )
		{
			if ( arr1.get(idx1) <= arr2.get(idx2) )
			{
				idx1++;
			}
			else if ( arr1.get(idx1) > arr2.get(idx2) )
			{
				arr1.add(idx1, arr2.get(idx2));
				idx1++;
				idx2++;
			}
		}
		
		// read remaining values into arr1
		if (idx1 >= arr1.size()) 
		{
			while ( idx2 < arr2.size() ) 
			{
				arr1.add(arr2.get(idx2++));
			}
		}
	}
	
	public static  Node combine ( Node a, Node b)
	{
		Node head, ptr;
		Node aprev;
		
		if (a == null)
		{
			return b;
		}
		
		if (b == null) 
		{
			return a;
		}
		
		aprev = null;
		head = a; 
		
		while (a != null && b != null) 
		{
			if (b.value <= a.value)
			{
				ptr = b;
				b = b.next;
				ptr.next = a;
				
				if (aprev == null) 
				{
					head = ptr;
				}
				
				if (aprev != null)
				{
					aprev.next = ptr;
				}
			}
			aprev = a;
			a = a.next;
		}
		
		
		if (b != null) // nodes remaining in b list !
		{
			aprev.next = b;
		}
		
		return head;
	}
	
	public static Node mergeSortList (Node list)
	{
		Node ptr, runner, left, right;
		int count = 0;
		
		if (list.next == null) 
		{
			return list;
		}
		
		// split list in half 
		ptr = runner = list; 
		
		do 
		{
			count = ~count;
			
			if (count == 0)
			{
				ptr = ptr.next;
			}
			
			runner = runner.next;
		}
		while (runner.next != null);
		
		right = ptr.next;
		left = list;
		ptr.next = null;  // cut list in half 
		
		left = mergeSortList(left); // return ordered left 
		right = mergeSortList(right); // return ordered right 
		
		return combine(left, right);
	}
	
	public static Node partition (Node list)
	{
		Node head, pivot, ptr; 
		
		pivot = head = list;
		
		while (list.next != null)
		{
			if (list.next.value <  pivot.value)
			{
				ptr = list.next; 
				list.next = list.next.next;
				ptr.next = head;
				head = ptr;
			}
			else 
			{
				list = list.next; 
			}
		}
		
		return head;
	}
	
	public static int partition (int arr[] )
	{
		int pivotIndex, pivot;
		int idx = 0;
		int tmp;
		
		if (arr.length == 0)
		{
			return -1;
		}
		
		pivotIndex = 0;
		pivot = arr[pivotIndex];
		
		for (int i = 0 ; i < arr.length; i++) 
		{
			if (arr[i]  < pivot)
			{
				tmp = arr[i];
				arr[i]  = arr[idx];
				arr[idx] = tmp;
				idx++;
				
				if (pivotIndex + 1 == idx)  // pivot moved!
				{
					pivotIndex = idx; 
				}
			}
		}
		
		return pivotIndex;
	}
	
	public static int partitionV2MedianPivot (int arr[] )
	{
		int pivotIndex, pivot;
		int tmp;
		int idx = 0;
		
		if (arr.length == 0)
		{
			return -1;
		}
		
		pivotIndex = arr.length / 2;
		pivot = arr[pivotIndex];
		
		for (int i = 0; i < arr.length; i++) 
		{
			if (arr[i] < pivot)
			{
				tmp = arr[i];
				arr[i]  = arr[idx];
				arr[idx] = tmp;
				idx++;
				
				if (pivotIndex + 1 == idx)  // pivot moved!
				{
					pivotIndex = idx; 
				}
			}
		}
		
		return pivotIndex;
	}
	
	public static int partitionV2EndPivot (int arr[] )
	{
		int pivotIndex, pivot;
		int tmp;
		int idx = 0;
		
		if (arr.length == 0)
		{
			return -1;
		}
		
		pivotIndex = arr.length - 1;
		pivot = arr[pivotIndex];
		
		for (int i = 0; i < arr.length; i++) 
		{
			if (arr[i] < pivot)
			{
				tmp = arr[i];
				arr[i]  = arr[idx];
				arr[idx] = tmp;
				idx++;

				if (pivotIndex + 1 == idx)  // pivot moved!
				{
					pivotIndex = idx; 
				}
			}
		}
		
		return pivotIndex;
	}
	
	public static int partitionV3Subset (int arr[], int start, int end)
	{
		int pivotIndex, pivot;
		int idx;
		int tmp;
		
		if (arr.length == 0)
		{
			return -1;
		}
		
		idx = pivotIndex = start;
		pivot = arr[pivotIndex];
		
		for (int i = start; i < end + 1; i++) 
		{
			if (arr[i] < pivot) 
			{
				tmp = arr[i];
				arr[i]  = arr[idx];
				arr[idx] = tmp;
				idx++;

				if (pivotIndex + 1 == idx)  // pivot moved!
				{
					pivotIndex = idx; 
				}
			}
		}
		return pivotIndex;
	}
	
	private static void quickSortSolver (int arr[], int start, int end)
	{
		int pivot;
		
		if (start < end )
		{
			pivot = partitionV3Subset(arr, start, end);
			quickSortSolver(arr, 0, pivot - 1);
			quickSortSolver(arr, pivot + 1, end);
		}
	}
	
	public static void quickSort(int arr[]) 
	{
		if (arr.length == 0) 
		{
			return;
		}
		quickSortSolver(arr, 0, arr.length - 1);
	}
	
	public static void partition3 (int arr[]) 
	{
		int pivotIndex, pivot;
		int idx;
		int tmp;
		
		if (arr.length == 0) 
		{
			return;
		}
		
		idx = pivotIndex = 0;
		pivot = arr[pivotIndex];		
		
		for (int i = 0; i < arr.length; i++) 
		{

			if (arr[i] < pivot) 
			{
				tmp = arr[i];
				arr[i]  = arr[idx];
				arr[idx] = tmp;
				idx++;

				if (pivotIndex + 1 == idx)  // pivot moved!
				{
					pivotIndex = idx; 
				}
			}
			
			if (arr[i] == pivot)
			{
				if (i != pivotIndex)
				{
					idx++; 	//forward idx variable 
					i--; 	// rewind i variable
				}
			}
			
		}
	}
	
	public static void mergeSort ( int [] arr ) 
	{
		ArrayList<Integer> arrList = new ArrayList<Integer>();
		for (int retVal: arr)
		{
			arrList.add(retVal);
		}
		
		mergeSort(arrList);
		
		for (int i = 0; i < arr.length; i++) 
		{
			arr[i] = arrList.get(i);
		}
	}
	
	public static void mergeSort (  ArrayList<Integer> arr ) 
	{
		ArrayList<Integer> left, right;
		int mid;
		
		if (arr.size() <= 1)
		{
			return;
		}
		
		mid = arr.size() / 2; 
		
		// left 
		left = new ArrayList<Integer>();
		for (int i = 0; i < mid; i++) 
		{
			left.add(arr.get(i));
		}
		
		// right
		right = new ArrayList<Integer>();
		for (int i = mid; i < arr.size(); i++) 
		{
			right.add(arr.get(i));
		}
		
		mergeSort(left);
		mergeSort(right);
		
		combine(left, right);
		
		
		for (int i = 0; i < arr.size() ; i++) 
		{
			arr.set(i, left.get(i));
		}
	}
	
	public static ArrayList<Integer> masterInvoiceList(ArrayList< ArrayList<Integer> > collection)
	{
		// list of array of timestamp. Return combined lists in order 
		
		ArrayList<Integer> output = new ArrayList<Integer>();
		for (ArrayList<Integer> retArray: collection)
		{
			combine(output, retArray);
		}
		return output ;
	}
	
	public static void pancakeSort (int pancakes[])
	{
		int orderedCakes = 0;
		int currMaxIndex;
		int len;
		int tmp;
		
		while (orderedCakes < pancakes.length)
		{
			currMaxIndex = 0;
			
			// find largest pancake
			len = pancakes.length - orderedCakes;
			for (int i = 0; i <len ; i++)
			{
				if ( pancakes[i] > pancakes[currMaxIndex] ) 
				{
					currMaxIndex = i;
				}
			}
			
			// flip (moving largest pancake to top)
			len = currMaxIndex + 1;
			for (int i = 0; i < len / 2; i++) 
			{
				tmp = pancakes[len - 1 - i];
				pancakes[len - 1 - i] = pancakes[i];
				pancakes[i] = tmp;
			}
			
			// flip (moving curr max pancake above threshold of balanced pancakes )
			len = pancakes.length - orderedCakes;
			for (int i = 0; i < len / 2; i++) 
			{
				tmp = pancakes[len - 1 - i];
				pancakes[len - 1 - i] = pancakes[i];
				pancakes[i] = tmp;
			}
			orderedCakes++;
		}
	}
	
	public static void radixSort(int arr[])
	{
		ArrayList<ArrayList<Integer>> map = new ArrayList<ArrayList<Integer>>();
		int offset = 0;
		Integer retVal;
		boolean done = false;
		int id;
		
		// allocate mem blocks
		for (int i = 0; i < 10; i++) 
		{
			map.add(new ArrayList<Integer>());
		}
		
		//load map
		for (int ret: arr) 
		{
			id = ((int) (ret / Math.pow(10, offset)))  % 10;
			map.get(id).add(ret);
		}
		
		// solver 
		do
		{
			done = true;
			offset++;
			for (int k = 0; k < map.size(); k++)
			{
				ArrayList<Integer> retArray = map.get(k);
				
				for (int i = 0; i < retArray.size(); i++)
				{
					retVal = retArray.get(i);
					id = (int) (retVal / Math.pow(10, offset))  % 10;
					
					if (k != id ) 	// so important !
					{
						retArray.remove(i);
						map.get(id).add(retVal);
					}
					done &= (id == 0);
				}
			}
		}
		while (!done);
		
		// overwrite local argument variable arr[]
		for ( int i = 0; i < map.get(0).size(); i++) 
		{
			arr[i] = map.get(0).get(i);
		}
	}
	
	public static void wiggleSort (int arr[]) // fun!
	{
		int idx = 0;
		int minIndex, maxIndex;
		
		while (idx + 1 < arr.length) 
		{
			minIndex = maxIndex = idx;
			
			for (int i = idx; i < arr.length; i++) 
			{
				if (arr[i] < arr[minIndex] )
				{
					minIndex = i;
				}
				
				if (arr[i] > arr[maxIndex]) 
				{
					maxIndex = i;
				}
			}
			
			swap(arr, idx, minIndex);
			swap(arr, idx + 1, maxIndex);
			idx+= 2;
		}
	}
	
	public static Integer medianUnsortedArray ( int arr[] )   // GEEZ THIS TOOK A WHILE !!
	{
		HashMap<Integer, ArrayList<Integer>> map = new HashMap<Integer, ArrayList<Integer>>();
		Integer median  = null;
		int halfLength = arr.length / 2;
		int widthOfNumber;
		int counter = 0; 
		
		// n/2 --> map data by with of numbers ( 100 = width(3) , 10000 = width(5) ) 
		for (int i = 0; i < arr.length; i+=2) 
		{
			widthOfNumber =  arr[i] == 0 ? 1 : (int) Math.ceil(Math.log10(arr[i]));;
			if (map.containsKey(widthOfNumber) == false)
			{
				map.put(widthOfNumber, new ArrayList<Integer>());
			}
			
			map.get(widthOfNumber).add(arr[i]);

			
			if (i + 1 <  arr.length) 
			{
				widthOfNumber =  arr[i  + 1] == 0 ? 1 : (int) Math.ceil(Math.log10(arr[i + 1]));;
				
				if (map.containsKey(widthOfNumber) == false)
				{
					map.put(widthOfNumber, new ArrayList<Integer>());
				}
				
				map.get(widthOfNumber).add(arr[i + 1]);
			}
		}
		
		// n/2 find the max value for half of the array
		for (int retKey: map.keySet())
		{
			if (counter >= halfLength) 
			{
				break;
			}
			
			for (int i = 0 ; i < map.get(retKey).size() && counter < halfLength; i++) 
			{
				if (median == null || map.get(retKey).get(i) > median)
				{
					median =  map.get(retKey).get(i);
					counter += 1;
				}
			}
		}
		
		return median;
	}
	
}
