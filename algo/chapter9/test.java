package algo.chapter9;
import algo.chapter9.*;
import algo.chapter5;

import java.util.ArrayList;


import algo.chapter5.Node;

public class test {
	private  void recursiveFibTest()
	{
		for (int i = 0; i < 10; i++) 
		{
			System.out.print(i + " -> " + chapter9.rFib(i) + "; ");
		}
		System.out.println("");
	}
	private  void recursiveTribTest()

	{
		for (int i = 0; i < 10; i++) 
		{
			System.out.print(i + " -> " + chapter9.rTrib(i) + "; ");
		}
		System.out.println("");	
	}
	private  void recursiveZibTest()

	{
		for (int i = 0; i < 15; i++) 
		{
			System.out.println("" + " -> " + "[" + chapter9.zib(2464) + "]" + "; ");
		}
		
		System.out.println("");	
	}
	
	private  void bestZibNumTest()
	{
		int zibResult = 3186;
		System.out.print("Largest index for " +zibResult+  " = " + chapter9.bestZibNum(3186) + "; ");
		
		zibResult = 3183;
		System.out.print("Largest index for " +zibResult+  " = " + chapter9.bestZibNum(3183) + "; ");

	}
	
	private  void rBinarySearchTest()
	{
		int [] array0 = {1,2,5,6};	
		System.out.println(chapter9.rBinarySearch(array0, 7));
		int [] array1 = {4,5,6,8,12};	
		System.out.println(chapter9.rBinarySearch(array1, 4));
	}
	
	private  void greatestCommonFactorTest() 
	{
		int a = 123456;
		int b = 987654;
		
		System.out.println("gcf(123456, 987654): " + chapter9.gcf(a, b));
		
		a= 105;
		b = 30;
		System.out.println("gcf(105, 30): " + chapter9.gcf(a, b));

	}
	
	private  void taraiTest () 
	{
		System.out.println(chapter9.tarai(10, 2, 9));
	}
	
	private  void inOrderSubsetTest() 
	{
		String str= "abcd";
		String[] array = chapter9.inOrderSubsets(str);
		for (String s:array)
		{
			System.out.print(s + ",");
		}
		System.out.println("");
	
	}
	
	// private  void rListLengthTest() 
	// {
	// 	Node head = new Node(1);
	// 	Node node = head;
		
	// 	node.next = new Node(2);
	// 	node = node.next;
		
	// 	node.next = new Node(4);
	// 	node = node.next;
		
	// 	System.out.println("list length: " + chapter9.rListLength(head));
	// }
	
	private  void gotAnyGrapsTest() 
	{
		int [] baggies = {1, 3, 3, 2, 3, 7, 3};
		System.out.println("max baggies: " + chapter9.gotAnyGrapes(baggies));
	}
	
	private  void collatzTest() 
	{
		int rcvd = 500;
		System.out.println(rcvd);
		do
		{
			rcvd = chapter9.collatz(rcvd);
			System.out.println(rcvd);
		}
		while (rcvd != 1);
	}
	
	public  void telephoneWordsTest ()
	{
		String number = "818-2612";
		ArrayList<String> collection = chapter9.telephoneWords(number);
		int index = 0;
		for (String s: collection)
		{
			System.out.println(++index + " " + s + ",");
		}
		System.out.println("");
	}
	
	public  void risingSquareTest ()
	{
		String str = chapter9.risingSquare(5);
		System.out.println(str);
	}
	
	public  void binaryExpansionTest ()
	{
		int index = 0;
		String test = "1?0?";
		ArrayList<String> collection = chapter9.binaryExpansion(test);
		for (String s: collection)
		{
			System.out.println(++index + " " + s + ",");
		}
		System.out.println("");
	}
	
	public  void anagramTest ()
	{
		int index = 0;
		String test = "lim";
		ArrayList<String> collection = chapter9.anagram(test);
		for (String s: collection)
		{
			System.out.println(++index + " " + s + ",");
		}
		System.out.println("");	
	}
	
	public  void climbingStairsTest()
	{
		ArrayList<ArrayList<Integer>> collection = chapter9.climbingStairs(4);
		for (ArrayList<Integer> array: collection)
		{
			for (int retVal: array) 
			{
				System.out.print(retVal +",");
			}
			System.out.println("");	
		}
		System.out.println("");	
	}
	
	public  void sumOfSquaresTest () 
	{
		int test = 30;
		ArrayList<ArrayList<Integer>> collection = chapter9.sumOfSquares(test);
		for (ArrayList<Integer> array: collection)
		{
			for (Integer s: array)
			{
				System.out.print(+ s + ",");
			}		
			System.out.println("");	
		}
		
		System.out.println("");	
	}
	
	public  void allValidNPairsOfParensTest()
	{
		int test = 2;
		ArrayList<String> collection = chapter9.allValidNPairsOfParens(test);
		for (String s: collection)
		{
			System.out.println(s + ",");
		}
		
		System.out.println("");	
	}
	
	public  void towerOfHanoiTest () 
	{
		int moves = chapter9.towerOfHanoi();
		System.out.println(" number of moves to relocate disks " + moves);
	}
	
	public  void ipAddressesTest() 
	{
		String addr = "255255255";
		ArrayList<String> collection = chapter9.ipAddresses(addr);
		for (String s: collection)
		{
			System.out.println(s + ",");
		}
	}
	
	public  void generateAllPossibleCoinChangeTest () 
	{
		int cents = 5;
		ArrayList<String> collection = chapter9.generateAllPossibleCoinChange(cents);
		for (String s: collection)
		{
			System.out.println(s + ",");
		}
	}
	
	public  void isChessMoveSafeTest () 
	{
		int [] intendedMove= {7,0};
		ArrayList<int[]> queens = new ArrayList<int[]>();
		int [] queen0 = {3, 7};
		int [] queen1 = {6, 7};
		int [] queen2 = {6, 1};

		queens.add( queen0 );
		queens.add( queen1 );
		queens.add( queen2 );

		System.out.println("valid move: " + chapter9.isChessMoveSafe(intendedMove, queens));
	}
	
	public  void allSafeChessSquaresTest () 
	{
		ArrayList<int[]> queens = new ArrayList<int[]>();
		int [] queen0 = {3, 7};
		int [] queen1 = {6, 7};
		int [] queen2 = {6, 1};

		queens.add( queen0 );
		queens.add( queen1 );
		queens.add( queen2 );

		ArrayList<int[]> collection = chapter9.allSafeChessSquares( queens);
		
		System.out.print("chess squares not threatened by queen: " );
		for (int[] pos: collection)
		{
			System.out.print("[" + pos[0] + "," + pos[1] + "]");
		}
		System.out.println("");
	}
	
	public  void eightQueensTest () 
	{
		ArrayList<ArrayList<int[]>> collection = chapter9.eightQueens();
		boolean enPrint = false;
		System.out.println("numbers of chessboards allowing 8 queens: " + collection.size());
		if (enPrint) 
		{
			for (ArrayList<int[]> array: collection)
			{
				System.out.print("[");
				for (int[] pos: array)
				{
					System.out.print( "[" + pos[0] + "," + pos[1] + "]");
				}
				System.out.println("]");
				chapter9.displayQueensOnBoard(8, array);
			}
			
			System.out.println("");	
		}
	
	}
	
	public  void nQueensTest() 
	{
		/*
		 * n = 13  : 31 seconds 
		 * n = 14  : 2 min 40 sec
		 * n = 15  : N/A
		 * */
		 
		int n = 15;
		int rows = n;
		int cols=  n;
		ArrayList<ArrayList<int[]>> collection = chapter9.nQueens(n, rows, cols);
		
		System.out.println("numbers of chessboards allowing " + n+ " queens " + collection.size() );
		for (ArrayList<int[]> array: collection)
		{

			System.out.print("[");
			for (int[] pos: array)
			{
				System.out.print( "[" + pos[0] + "," + pos[1] + "]");
			}
			System.out.println("]");
		
		}
	}
	
	public  void main(String args[])
	{
		nQueensTest();
	}
}
