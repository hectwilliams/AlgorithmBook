package algo;
import java.util.ArrayList;
import algo.Chapter5.*;
import algo.Chapter12.Name;

public class Test {
	
	public static void bubbleSortTest()
	{
		int arr[] = {22 ,1 , 0, 93, 34, 22, 17};
		Chapter12.bubbleSort(arr);
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
	}
	
	public static void selectionSortTest()
	{
		int arr[] = {22 ,1 , 0, 93, 34, 22, 17};
		Chapter12.selectionSort(arr);
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
	}
	
	public static void selectionSortSListTest()
	{
		Node runner;
		Node node, head;
		
		node = head = new Node(22);
		
		node.next = new Node(1);
		node.next.next = new Node(0);
		node.next.next.next = new Node(93);
		node.next.next.next.next = new Node(34);
		node.next.next.next.next.next = new Node(25);
		node.next.next.next.next.next.next = new 
		(17);
		
		node = Chapter12.selectionSortSList(head);
		runner = node;
		while (runner != null) 
		{
			System.out.print("[" + runner.value + "]");
			runner = runner.next;
		}
		System.out.println("");
	}
	
	public static void bubbleSortSListTest()
	{
		Node runner;
		Node node, head;
		
		node = head = new Node(22);
		
		node.next = new Node(1);
		node.next.next = new Node(0);
		node.next.next.next = new Node(93);
		node.next.next.next.next = new Node(34);
		node.next.next.next.next.next = new Node(25);
		node.next.next.next.next.next.next = new Node(17);
		
		node = Chapter12.bubbleSortSList(head);
		runner = node;
		while (runner != null) 
		{
			System.out.print("[" + runner.value + "]");
			runner = runner.next;
		}
		System.out.println("");
	}
	
	public static void multiKeySortTest() 
	{
		Name[] nameCollection = {
			new  Name("Giorgio", "Carnevale"),
			new  Name("Lee", "Abbey"),
			new  Name("Aaron", "Carnevale"),
		};
		Chapter12.multiKeySort(nameCollection);
		
		for (Name RetObj :nameCollection )
		{
			System.out.println( RetObj.getFirstName() + "  " + RetObj.getLastName());
		}
	}
	
	public static void insertionSortTArrayTest() 
	{
		int arr[] = {22 ,1 , 0, 93, 34, 22, 17};
		Chapter12.insertionSort(arr);
		
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
	}
	
	public static void insertionSortSListTest() 
	{
		Node node, head, runner;
		node = head = new Node(22);
		node.next = new Node(1);
		node.next.next = new Node(0);
		node.next.next.next = new Node(93);
		node.next.next.next.next = new Node(34);
		node.next.next.next.next.next = new Node(25);
		node.next.next.next.next.next.next = new Node(17);
		
		runner = Chapter12.insertionSort(head);
		while (runner != null) 
		{
			System.out.print("[" + runner.value + "]");
			runner = runner.next;
		}
	}
	
	public static void arrayCombineTest() 
	{
		ArrayList<Integer> arr1 = new ArrayList<Integer>();
		ArrayList<Integer> arr2 = new ArrayList<Integer>();

		int[] a1 = {22 ,1 , 0, 93, 34, 22, 17} ;
		int[] a2 = {20 ,-1 , 0, 9, 76, 222, 1117};
		
		Chapter12.bubbleSort(a1);
		Chapter12.bubbleSort(a2);

		for (int retVal: a1)
		{
			arr1.add(retVal);
		}
		
		for (int retVal: a2)
		{
			arr2.add(retVal);
		}
		
		Chapter12.combine(arr1, arr2);
		
		for (int data: arr1)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");

	}
	
	public static void SListCombinTest() 
	{
		Node node, head, runner;
		
		node = head = new Node(3);
		node.next = new Node(9);
		node.next.next = new Node(10);
		node.next.next.next = new Node(193);
		node.next.next.next.next = new Node(334);
		node.next.next.next.next.next = new Node(525);
		node.next.next.next.next.next.next = new Node(617);
		
		Node node2, head2;
		node2 = head2 = new Node(1);
		node2.next = new Node(5);
		node2.next.next = new Node(10);
		node2.next.next.next = new Node(93);
		node2.next.next.next.next = new Node(2334);
		
		runner = Chapter12.combine(head, head2);
		while (runner != null) 
		{
			System.out.print("[" + runner.value + "]");
			runner = runner.next;
		}
		System.out.println("");
	}
	
	public static void SListMergeSortTest ()
	{
		Node node, head, runner;

		node = head = new Node(22);
		node.next = new Node(1);
		node.next.next = new Node(0);
		node.next.next.next = new Node(93);
		node.next.next.next.next = new Node(34);
		node.next.next.next.next.next = new Node(25);
		node.next.next.next.next.next.next = new Node(17);
		
		System.out.println("before");
		runner = head;
		while (runner != null) 
		{
			System.out.print("[" + runner.value + "]");
			runner = runner.next;
		}
		System.out.println("");
		
		System.out.println("after");

		runner = Chapter12.mergeSortList(head);

		while (runner != null) 
		{
			System.out.print("[" + runner.value + "]");
			runner = runner.next;
		}
		System.out.println("");
		
	}
	
	public static void SListPartitionTest ()
	{
		Node node, head, runner;

		node = head = new Node(5);
		node.next = new Node(1);
		node.next.next = new Node(8);
		node.next.next.next = new Node(4);
		node.next.next.next.next = new Node(9);
		node.next.next.next.next.next = new Node(2);
		node.next.next.next.next.next.next = new Node(5);
		node.next.next.next.next.next.next.next = new Node(3);

		runner = Chapter12.partition(head);
		
		while (runner != null) 
		{
			System.out.print("[" + runner.value + "]");
			runner = runner.next;
		}
		System.out.println("");

	}
	
	public static void arrayPartitionTest () 
	{
		int arr[] = {5, 4, 9, 2, 5, 3};
		int arr2[] = {5, 4, 9, 2, 5, 3};
		int arr3[] = {5, 4, 9, 2, 5, 3};

		System.out.println("pivot position " + Chapter12.partition(arr));
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
		System.out.println("");

		System.out.println("pivot position " + Chapter12.partitionV2MedianPivot(arr2));
		for (int data: arr2)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
		System.out.println("");

		System.out.println("pivot position " + Chapter12.partitionV2EndPivot(arr3));
		for (int data: arr3)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
	}
	
	public static void partitionSubsetTest () 
	{
		int arr[] = {5, 4, 9, 2, 5, 3};
		int start = 1;
		int end = arr.length - 1;
		
		System.out.println( "pivot position " + Chapter12.partitionV3Subset(arr, start, end) );
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
	}
	
	public static void quickSortTest() 
	{
		int arr[] = {5, 4, 9, 2, 5, 3};
		Chapter12.quickSort(arr);
		
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
	}
	
	public static void partition3Test() 
	{
		int arr[] = {5, 1, 8, 4, 9, 2, 5, 3};
		Chapter12.quickSort(arr);
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
	}
	
	public static void mergeSortArrayTest()
	{
		int arr[] = {22 ,1 , 0, 93, 34, 22, 17};
		
		Chapter12.mergeSort(arr);
		
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
		
		System.out.println("");
	}
	
	public static void masterInvoiceListTest() 
	{
		int timestampGroup0Arr[] = {5, 4, 9, 2, 5, 3};
		int timestampGroup1Arr[] = {22 ,1 , 0, 93, 34, 22, 17};
		int timestampGroup2Arr[] = {20 ,-1 , 0, 9, 76, 222, 1117};
		ArrayList< ArrayList<Integer> > collection = new ArrayList< ArrayList<Integer> >();
		ArrayList<Integer> result; 
		
		for (int i =0 ; i < 3; i++) 
		{
			collection.add(new   ArrayList<Integer>());
		}

		Chapter12.quickSort(timestampGroup0Arr);
		Chapter12.quickSort(timestampGroup1Arr);
		Chapter12.quickSort(timestampGroup2Arr);
		
		for (int data: timestampGroup0Arr)
		{
			collection.get(0).add(data);
		}

		for (int data: timestampGroup1Arr)
		{
			collection.get(1).add(data);
		}
		
		for (int data: timestampGroup2Arr)
		{
			collection.get(2).add(data);
		}
		
		result = Chapter12.masterInvoiceList(collection);

		for (int data: result)
		{
			System.out.print("[" + data + "]");
		}
	}
	
	public static void pancakeSortTest() 
	{
		int stackOfPancake[] = {22 ,1 , 0, 93, 34, 22, 17};
		Chapter12.pancakeSort(stackOfPancake);
		for (int data: stackOfPancake)
		{
			System.out.print("[" + data + "]");
		}
		
		System.out.println("");
	}	
	
	public static void radixSortTest() 
	{
		int arr[] = {20 ,1 , 0, 9, 76, 222, 1117};
		Chapter12.radixSort(arr);
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
	}
	
	public static void wiggleSortTest() 
	{
		int arr[] = {20 ,1 , 0, 9, 76, 222, 1117};
		Chapter12.wiggleSort(arr);
		for (int data: arr)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
		
		int arr2[] = {3,5,2,1,6,4};
		Chapter12.wiggleSort(arr2);
		for (int data: arr2)
		{
			System.out.print("[" + data + "]");
		}
		System.out.println("");
	}
	
	public static void medianUnsortedArrayTest () 
	{
		int arr[] = {1 ,20 , 0, 9, 76, 222, 1117};
		System.out.println( " median of unsorted array " + Chapter12.medianUnsortedArray(arr) ); 
	}
	
	public static void main(String args[])
	{
		medianUnsortedArrayTest();
	}
	
}  
