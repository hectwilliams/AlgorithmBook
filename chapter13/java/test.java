package algo;
import algo.Chapter13.*;

import java.sql.Date;
import java.util.ArrayList;
import java.util.concurrent.TimeUnit;

import algo.Chapter12.*; // for sort

public class Test {
	
	public static  void interleaveArrayTest () 
	{
		int[] arr0 = {77, 22, 11, 22};
		int[] arr1 = {2, 6, 7, 2, 6, 2};
		int [] retArray = Chapter13.interleaveArrays(arr0, arr1);
		for (int retVal: retArray) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
	}
	
	public static  void mergeSortedArrayTest () 
	{
		int[] arr0 = {1,2,2,2,7};
		int[] arr1 = {2, 2, 6, 6, 7};
		int [] retArray ;
		
		Chapter12.quickSort(arr0);
		Chapter12.quickSort(arr1);

		retArray = Chapter13.mergeSortedArray(arr0, arr1);
		for (int retVal: retArray) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
	}
	
	public static void minimalThreeArrayRangeTest() 
	{
		int[][] data = 
		{
			{1, 2, 4, 15},
			{3, 10, 12},
			{5, 10, 13, 17, 23}
		};
				
		Integer result[] = Chapter13.minimalThreeRange(data[0], data[1], data[2]);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
		
	}
	
	public static void intersectSortedArraysTest() 
	{
		int[] a = {1, 2, 2, 2, 7};	
		int[] b = {2, 2, 6, 6, 7};	
		ArrayList<Integer> result = Chapter13.intersectSortedArray(a, b);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
	}
	
	public static void intersectSortedArraysDedupeTest() 
	{
		int[] a = {1, 2, 2, 2, 7};	
		int[] b = {2, 2, 6, 6, 7};	
		ArrayList<Integer> result = Chapter13.intersectSortedArrayDedupe(a, b);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
	}
	
	public static void unionSortedArraysTest() 
	{
		int[] a = {1, 2, 2, 2, 7};
		int[] b = {2, 2, 6, 6, 7};
		ArrayList<Integer> result = Chapter13.unionSortedArray(a, b);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
		
		result = Chapter13.unionSortedArrayDedupe(a, b);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
		
	}
	
	public static void intersectionUnsortedArrayInPlaceTest () 
	{
		int [] a = {2,7,2,1,2};
		int [] b = {6,7,2,7,6,2};
		ArrayList<Integer> aa, bb, result;
		
		aa = new ArrayList<Integer>();
		for (int retVal: a) 
		{
			aa.add(retVal);
		}
		
		bb = new ArrayList<Integer>();
		for (int retVal: b) 
		{
			bb.add(retVal);
		}
		result = Chapter13.intersectionUnsortedArraysInPlace(aa, bb);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
		
		result = Chapter13.intersectionUnsortedArrays(aa, bb);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
		
	}
	
	public static void unsortedArraysTest ()
	{
		int a[] = {6, 7, 2, 7, 6, 2};
		int b[] = {2, 7, 2, 1, 2};
		ArrayList<Integer> result = Chapter13.intersectionUnsortedArrays(a, b);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
	}
	
	public static void unionUnsortedArraysTest()
	{
		int[] a = {2, 7, 2, 1, 2};
		int[] b = {6, 7, 2, 7, 6, 2};
		
		ArrayList<Integer> result = Chapter13.unionUnsortedArray(a, b);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
	}
	
	public static void unionUnsortedArrayInPlaceTest() 
	{
		int[] a = {2, 7, 2, 1};
		int[] b = {6, 7, 2, 6};
		
		ArrayList<Integer> aa, bb;
		
		aa = new ArrayList<Integer>();
		for (int retVal: a) 
		{
			aa.add(retVal);
		}
		
		bb = new ArrayList<Integer>();
		for (int retVal: b) 
		{
			bb.add(retVal);
		}
		
		Chapter13.unionUnsortedArrayInPlace(aa, bb);
		for (int retVal: aa) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();	
	}
	
	public static void unionUnsortedArrayDedupeTest() 
	{
		int[] a = {2, 7, 2, 1};
		int[] b = {6, 7, 2, 6};
		
		ArrayList<Integer> aa, bb, result;
		
		aa = new ArrayList<Integer>();
		for (int retVal: a) 
		{
			aa.add(retVal);
		}
		
		bb = new ArrayList<Integer>();
		for (int retVal: b) 
		{
			bb.add(retVal);
		}
		
		result = Chapter13.unionUnsortedArrayInPlaceDedupe(aa, bb);
		for (int retVal: result) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();	
	}
	
	public static void subsetSortedArrayTest () 
	{
		int[] a = {2, 17, 22, 31};
		int[] b = {17, 22};
		
		System.out.println("subset of " + Chapter13.subsetSortedArray(a, b) );
	}
	
	public static void subsetUnSortedArrayTest () 
	{
		int[] a = {110, 31, 2, 12, 22, 0};
		int[] b = {0, 444, 22, 110};
		
		System.out.println("subset of " + Chapter13.subsetUnSortedArray(a, b) );
	}
	

	public static void priQueueTest()
	{
		PriQueue queuePrioList = new PriQueue();
		int[] data = {1, 100, 2,1, 2,100, 2,10000, 3, 10, 3, 1, 3, 0, 5, 100};
		
		// load value/priority
		for (int i = 0 ; i < data.length; i+=2) 
		{
			queuePrioList.push(data[i + 1], data[i]);
		}
		
		Chapter13.PriQueueDisplay(queuePrioList.getHead());  // { pri:1,value: 100} { pri:2,value: 1} { pri:2,value: 100} { pri:2,value: 10000} { pri:3,value: 0} { pri:3,value: 1} { pri:3,value: 10} { pri:5,value: 100} 
		System.out.println( "pooped " + queuePrioList.pop());
		Chapter13.PriQueueDisplay(queuePrioList.getHead());  //  { pri:2,value: 1} { pri:2,value: 100} { pri:2,value: 10000} { pri:3,value: 0} { pri:3,value: 1} { pri:3,value: 10} { pri:5,value: 100} 
		queuePrioList.remove(0, 3);
		Chapter13.PriQueueDisplay(queuePrioList.getHead());  //  { pri:2,value: 1} { pri:2,value: 100} { pri:2,value: 10000} { pri:3,value: 1} { pri:3,value: 10} { pri:5,value: 100} 

	}
	
	public static void sequencerTest () 
	{
		Sequencer sequencer = new Sequencer(); 
		
		try {
			sequencer.playMessages();
			TimeUnit.SECONDS.sleep(1);
			sequencer.sequenceMessage( System.currentTimeMillis() + 2000222424, 200);
			TimeUnit.SECONDS.sleep(1);
			sequencer.sequenceMessage( System.currentTimeMillis() + 1000000 , 100);
			TimeUnit.SECONDS.sleep(1);
			sequencer.sequenceMessage( System.currentTimeMillis() + 50000000, 500);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public static void minHeapTest ()
	{
		int data[] = {/*null,*/ 4, 3, 8, 9, 100, 1, 2};
		MinHeap minheap = new MinHeap();
		
		for (int retVal: data)
		{
			minheap.insert(retVal);
		}
		minheap.display();
		System.out.println("extracted " + minheap.extract());
		minheap.display();
	}
	
	public static void heapifyTest() 
	{
		int[] data = {110, 31, 2, 12, 22, 0};
		MinHeap minheap = new MinHeap();
		MaxHeap maxheap = new MaxHeap();

		minheap.heapify(data);
		
		for (int retVal: data) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
		
		/*
		 * 				 0 
		 *            /     \
		 *         12        2 
		 *       /     \    /  \
		 *      31    22   110 
		 */
		
		maxheap.heapify(data);
		
		for (int retVal: data)    							
		{                                                   
			System.out.print(retVal + ",");                 
		}                                                   
		System.out.println();   
		
		/*
		 * 				110
		 *            /     \
		 *          31         2 
		 *       /     \     /   \
		 *      12     12   0 
		 */
	}                                                       
	
	public static void heapSortTest() 
	{
		int[] arr = {110, 31, 2, 12, 22, 0};
		Chapter13.heapSort(arr);
		for (int retVal: arr) 
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
	}
	
	public static void medianOfDataStreamTest () 
	{
		int[] arr = {110, 31, 2, 12, 22, 0,200, 4, 6, 23}; 				// 0  2 4 6 12 22 23 31 110 200  
		MedianOfDataStream medStream = new MedianOfDataStream(); 
		double median;
		for (int i = 0; i < arr.length; i++)
		{
			median = medStream.read(arr[i]);
			System.out.println("current median: " +  median );
		}
		
	}
	
	public static void QueueTwoStackTest () 
	{
		int[] arr = {110, 31, 2, 12, 22, 0};
		QueueTwoStack stack = new QueueTwoStack();
		
		for (int retVal: arr)
		{
			stack.enqueue(retVal);
		}
		
		while (!stack.isEmpty())
		{
			System.out.println(stack.dequeue());
		}
	}
	
	public static void main(String args[])
	{
		QueueTwoStackTest();
	}

}  
