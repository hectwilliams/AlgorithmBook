package algo;
import algo.Chapter9.*;

import java.util.ArrayList;


import algo.Chapter5.Node;;

public class Test {
	private static void recursiveFibTest()
	{
		for (int i = 0; i < 10; i++) 
		{
			System.out.print(i + " -> " + Chapter9.rFib(i) + "; ");
		}
		System.out.println("");
	}
	private static void recursiveTribTest()

	{
		for (int i = 0; i < 10; i++) 
		{
			System.out.print(i + " -> " + Chapter9.rTrib(i) + "; ");
		}
		System.out.println("");	
	}
	private static void recursiveZibTest()

	{
		for (int i = 0; i < 15; i++) 
		{
			System.out.println("" + " -> " + "[" + Chapter9.zib(2464) + "]" + "; ");
		}
		
		System.out.println("");	
	}
	
	private static void bestZibNumTest()
	{
		int zibResult = 3186;
		System.out.print("Largest index for " +zibResult+  " = " + Chapter9.bestZibNum(3186) + "; ");
		
		zibResult = 3183;
		System.out.print("Largest index for " +zibResult+  " = " + Chapter9.bestZibNum(3183) + "; ");

	}
	
	private static void rBinarySearchTest()
	{
		int [] array0 = {1,2,5,6};	
		System.out.println(Chapter9.rBinarySearch(array0, 7));
		int [] array1 = {4,5,6,8,12};	
		System.out.println(Chapter9.rBinarySearch(array1, 4));
	}
	
	private static void greatestCommonFactorTest() 
	{
		int a = 123456;
		int b = 987654;
		
		System.out.println("gcf(123456, 987654): " + Chapter9.gcf(a, b));
		
		a= 105;
		b = 30;
		System.out.println("gcf(105, 30): " + Chapter9.gcf(a, b));

	}
	
	private static void taraiTest () 
	{
		System.out.println(Chapter9.tarai(10, 2, 9));
	}
	
	private static void inOrderSubsetTest() 
	{
		String str= "abcd";
		String[] array = Chapter9.inOrderSubsets(str);
		for (String s:array)
		{
			System.out.print(s + ",");
		}
		System.out.println("");
	
	}
	
	private static void rListLengthTest() 
	{
		Node head = new Node(1);
		Node node = head;
		
		node.next = new Node(2);
		node = node.next;
		
		node.next = new Node(4);
		node = node.next;
		
		System.out.println("list length: " + Chapter9.rListLength(head));
	}
	
	private static void gotAnyGrapsTest() 
	{
		int [] baggies = {1, 3, 3, 2, 3, 7, 3};
		System.out.println("max baggies: " + Chapter9.gotAnyGrapes(baggies));
	}
	
	private static void collatzTest() 
	{
		int rcvd = 500;
		System.out.println(rcvd);
		do
		{
			rcvd = Chapter9.collatz(rcvd);
			System.out.println(rcvd);
		}
		while (rcvd != 1);
	}
	
	public static void telephoneWordsTest ()
	{
		String number = "818-2612";
		ArrayList<String> collection = Chapter9.telephoneWords(number);
		int index = 0;
		for (String s: collection)
		{
			System.out.println(++index + " " + s + ",");
		}
		System.out.println("");
	}
	
	public static void risingSquareTest ()
	{
		String str = Chapter9.risingSquare(5);
		System.out.println(str);
	}
	
	public static void binaryExpansionTest ()
	{
		int index = 0;
		String test = "1?0?";
		ArrayList<String> collection = Chapter9.binaryExpansion(test);
		for (String s: collection)
		{
			System.out.println(++index + " " + s + ",");
		}
		System.out.println("");
	}
	
	public static void anagramTest ()
	{
		int index = 0;
		String test = "lim";
		ArrayList<String> collection = Chapter9.anagram(test);
		for (String s: collection)
		{
			System.out.println(++index + " " + s + ",");
		}
		System.out.println("");	
	}
	
	public static void climbingStairsTest()
	{
		ArrayList<ArrayList<Integer>> collection = Chapter9.climbingStairs(4);
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
	
	public static void sumOfSquaresTest () 
	{
		int test = 30;
		ArrayList<ArrayList<Integer>> collection = Chapter9.sumOfSquares(test);
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
	
	public static void allValidNPairsOfParensTest()
	{
		int test = 2;
		ArrayList<String> collection = Chapter9.allValidNPairsOfParens(test);
		for (String s: collection)
		{
			System.out.println(s + ",");
		}
		
		System.out.println("");	
	}
	
	public static void towerOfHanoiTest () 
	{
		int moves = Chapter9.towerOfHanoi();
		System.out.println(" number of moves to relocate disks " + moves);
	}
	
	public static void ipAddressesTest() 
	{
		String addr = "255255255";
		ArrayList<String> collection = Chapter9.ipAddresses(addr);
		for (String s: collection)
		{
			System.out.println(s + ",");
		}
	}
	
	public static void generateAllPossibleCoinChangeTest () 
	{
		int cents = 5;
		ArrayList<String> collection = Chapter9.generateAllPossibleCoinChange(cents);
		for (String s: collection)
		{
			System.out.println(s + ",");
		}
	}
	
	public static void isChessMoveSafeTest () 
	{
		int [] intendedMove= {7,0};
		ArrayList<int[]> queens = new ArrayList<int[]>();
		int [] queen0 = {3, 7};
		int [] queen1 = {6, 7};
		int [] queen2 = {6, 1};

		queens.add( queen0 );
		queens.add( queen1 );
		queens.add( queen2 );

		System.out.println("valid move: " + Chapter9.isChessMoveSafe(intendedMove, queens));
	}
	
	public static void allSafeChessSquaresTest () 
	{
		ArrayList<int[]> queens = new ArrayList<int[]>();
		int [] queen0 = {3, 7};
		int [] queen1 = {6, 7};
		int [] queen2 = {6, 1};

		queens.add( queen0 );
		queens.add( queen1 );
		queens.add( queen2 );

		ArrayList<int[]> collection = Chapter9.allSafeChessSquares( queens);
		
		System.out.print("chess squares not threatened by queen: " );
		for (int[] pos: collection)
		{
			System.out.print("[" + pos[0] + "," + pos[1] + "]");
		}
		System.out.println("");
	}
	
	public static void eightQueensTest () 
	{
		ArrayList<ArrayList<int[]>> collection = Chapter9.eightQueens();
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
				Chapter9.displayQueensOnBoard(8, array);
			}
			
			System.out.println("");	
		}
	
	}
	
	public static void main(String args[])
	{
		eightQueensTest();
	}
}
