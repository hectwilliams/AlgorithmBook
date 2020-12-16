package algo;
import java.util.ArrayList;
import java.util.HashMap;

import algo.Chapter5.Node; // node
public class Chapter9 {
	public static int rFib(int num)
	{
		/*
		 * 
		 *  0     return 1 
		 *   1    return 0
		 *     2  return f(0) + f(1)  
		 *     	 3  return f(1) + f(2)  
		 *     	  	
		 * */
		if (num <= 0)
		{
			return 0;
		}
		
		if (num == 1 ) 
		{
			return 1;
		}
		
		
		return rFib(num - 2) + rFib(num - 1);
	}
	
	public static int rTrib (int num)
	{
		/*
		 * 
		 *  0     return 0
		 *   1    return 0
		 *     2  return 1
		 *     	 3  return f(0) + f(1) + f(2)  
		 *     	   4  return f(1) + f(2) + f(3)  
		 *     
		 * */
		
		if (num <=1) 
		{
			return 0;
		}
		
		if (num == 2) 
		{
			return 1;
		}
		
		return rTrib(num - 3) + rTrib(num - 2) + rTrib(num - 1);
	}
	
	public static int ackermann (int num1, int num2)
	{
		if (num1 == 0) 
		{
			return num2 + 1;
		}
		
		if (num2 == 0) 
		{	if (num1 > 0) 
			{
				return ackermann(num1 - 1, 1);
			}
			else 
			{
				return num2 + 1;
			}
		} 
		
		return ackermann(num1 - 1, ackermann(num1, num2 - 1));
	}
	
	
	public static int zib (int num)
	{
		int n;
		
		if (num <= 1) 
		{
			return 1;
		}
		
		if (num == 2) 
		{
			return 2;
		}
		
		
		if ((num % 2) == 1) 
		{ 
			n = (num - 1) / 2;
			return zib(n) + zib(n - 1) + 1;
		}
		
		if ((num % 2) == 0) 
		{
			n = (num) / 2;
			return zib(n) + zib(n + 1) + 1;
		}
		
		return 0;
	}
	
	public static Integer bestZibNumSolver (int possibleFibResult)
	{
		
		Integer n;
		int evenResult, oddResult;
		boolean findlargestIndex = true; // set to false to find lowest index
		
		if (possibleFibResult == 1) 
		{
			return 0;
		}
		
		if (possibleFibResult <= 2) 
		{
			return 2;
		}

		n = bestZibNumSolver(possibleFibResult - 1)  / 2  ;	
		evenResult = zib(n) + zib(n + 1) + 1;
		oddResult = zib(n) + zib(n - 1) + 1;
		
		if (findlargestIndex)
		{
			if ( oddResult < possibleFibResult) 
			{
				return (n + 1) * 2;
			}	
		}
		
		if (!findlargestIndex) 
		{
			if ( oddResult < possibleFibResult) 
			{
				return (n + 1) * 2;
			}	
		}
		
		return n*2;
		
	}
	
	public static Integer bestZibNum (int possibleFibResult) // HARD PROBLEM
	{
		/*
		 * find lowest index refer to bestZibNumSolver
		 * find largest index refer to bestZibNumSolver
		 * */
		
		int n = bestZibNumSolver(possibleFibResult) / 2;
		int evenResult = zib(n) + zib(n + 1) + 1;
		int oddResult = zib(n) + zib(n - 1) + 1;

		if (evenResult == possibleFibResult) 
		{
			return n*2;
		}
		
		if ( oddResult == possibleFibResult)
		{
			return n*2  + 1;
		}
		return null;
	}
	
	public static boolean rBinarySearch(int [] array, int target)
	{
		int mid = array.length / 2;
		int[] arrayCopy = {};
		int copyLength = 0;
		
		if (array.length == 0 ) 
		{
			return false;
		}
		
		if (array.length == 1) 
		{
			return array[0] == target;
		}
		
		if (array.length % 2 == 1) 
		{
			if (array[mid] == target)
			{
				return true;
			}
			
			copyLength = array.length / 2;
			
			if (target > array[mid])
			{
				arrayCopy = new int[copyLength];

				// copy right
				for (int i = 0; i < copyLength; i++) 
				{
					arrayCopy[i] = array[mid + 1 + i];
				}
			}
			
			if (target < array[mid])
			{
				arrayCopy = new int[copyLength];
				// copy left 
				for (int i = 0; i < copyLength; i++) 
				{
					arrayCopy[copyLength - 1 - i] = array[mid - 1 - i];

				}
			}
		}
		
		if (array.length % 2 == 0)
		{   
			if (array[mid] == target || array[mid - 1] == target)
			{
				return true;
			}
			
			copyLength = (array.length - 2) / 2;
			
			if (target > array[mid]) 
			{
				arrayCopy = new int[copyLength];
				
				// copy right 
				for (int i = 0; i < copyLength; i++) 
				{
					arrayCopy[i] = array[mid + 1 + i];
				}
			}
			
			if (target < array[mid - 1]) 
			{
				arrayCopy = new int[copyLength];

				// copy left 
				for (int i = 0; i < copyLength; i++) 
				{
					arrayCopy[copyLength - 1 - i] = array[mid - 2 - i];
				}
			}
		}
		
		return rBinarySearch(arrayCopy, target);
		
	}
	
	
	public static double gcf(double num1, double num2)
	{
		int k;

		if (num2 > num1) 
		{
			return gcf (num2 , num1);
		}
		
		if (num2 % num1 == 0) 
		{
			return num1;
		}
		
		k = (int)num1 / (int) num2;
		
		return gcf(num1 - k*num2  , num2 );
	}
	
	public static int tarai(int x, int y, int z)
	{
		if ((x <= y)) 
		{
  		}
		return tarai(tarai(x - 1, y, z), tarai(y-1, z, x), tarai(z-1, x, y));
	}
	
	public static int factorial  (int num) 
	{
		if (num  <= 1)
		{
			return 1;
		}
		
		return num * factorial(num - 1);
	}
	
	private static String[] combinations(String str, int r) 
	{
		int n = str.length();
		String[] result = {};
		int start;
		int numOfElements;
		int[] keyMap;
		int tmp;
		
		if (n == 0 || r > n) 
		{
			return result;
		}
		
		numOfElements = factorial(n) / (factorial(n - r) * factorial(r));
		start = 0;
		result = new String[numOfElements];
		
		/* compute 'ordered' key map for combinations */
		do 
		{
			keyMap = new int[r];
			for (int i = 0; i < r; i++) 
			{
				keyMap[i]  = (start + i ) % n;
				if (i != 0) 
				{
					if (keyMap[i - 1] > keyMap[i]) 
					{
						// swap
						{
							tmp = keyMap[i];
							keyMap[i] = keyMap[ i - 1];
							keyMap[i - 1] = tmp;
						}
					}
				}
				
				// compute set
				result[start] = "";
				for (int m = 0; m < r; m++)
				{
					result[start] += str.charAt(keyMap[m]) ;
				}
			}
			start++;
		}
		while (start != numOfElements);
		
		return result;
	
	}
	
	private static void inOrderSubsetsSolver (String str, int num, String[] arrayCache, int[] positionCache)
	{
		String[] combinationList;
		
		if (num == 0) 
		{
			return;
		}

		inOrderSubsetsSolver(str, num - 1, arrayCache, positionCache);
		
		combinationList =  combinations(str, num);
		
		for (String s: combinationList)
		{
			arrayCache[positionCache[0]++] = s;
		}
		
	}
	
	public static String[] inOrderSubsets(String str) 
	{
		/*
		 * subset count 2^n  (n = size of string)
		 * */
		String[] result = new String[(int)Math.pow(2, str.length())];
		int [] positionCache = new int[1];
		
		if (str.length() == 0) 
		{
			return result;
		}
		
//		result[result.length - 1] = "";
		inOrderSubsetsSolver(str, str.length(), result, positionCache);
		
		return result;
	}
	
	public static int rListLength (Node node) 
	{
		if (node == null) 
		{
			return 0;
		}
		
		return 1 + rListLength(node.next);
	}
	
	public static int gotAnyGrapes(int[] baggies) 
	{
		
		int rcvd  = 0;
		int copy[];
		int maxBag = 0;

		if (baggies.length == 0) 
		{
			return 0;
		}
		
		maxBag = baggies[0];
		for (int nextBagIndex = 2; nextBagIndex < baggies.length; nextBagIndex++) 
		{
			// copy available baggies (slice array)
			copy = new int[baggies.length - nextBagIndex];
			for (int k = nextBagIndex; k < baggies.length; k++) 
			{
				copy[k - nextBagIndex] = baggies[k];	
			}
			
			rcvd = baggies[0]  + gotAnyGrapes(copy);
			
			if (rcvd > maxBag) 
			{
				maxBag = rcvd;
			}
		}
		
		return maxBag;
	} 
	
	public static int collatz (int num) 
	{
		if (num != 1) 
		{
			if (num %2 == 0) 
			{
				return num/2;
			}
			
			if (num % 2 == 1) 
			{
				return 3*num + 1;
			}
		}
		
		return 1;
	}
	
	private static void telephoneWordsSolver(String number, HashMap<Character, String> map, ArrayList<String> arrayCache, String buffer)
	{
		String bufferCopy;
		String charCodes;
		char c;

		if (number.length() == 0) 
		{
			arrayCache.add(buffer);
			return;
		}
		
		// store first char of number argument
		c = number.charAt(0);
		
		// retrieve code
		charCodes = map.get(c); 
		
		for (int i = 0; i < charCodes.length(); i++) 
		{
			// append character(code) to buffer instance
			bufferCopy = buffer + charCodes.charAt(i);
		
			telephoneWordsSolver(number.substring(1), map, arrayCache, bufferCopy);
		}
		
	}
	
	public static ArrayList<String> telephoneWords (String number)
	{
		HashMap<Character, String> map = new HashMap<Character, String>();
		ArrayList<String> possibleStrings = new ArrayList<String>();
		
		map.put('-', "");
		map.put('1', "I");
		map.put('0', "O");
		map.put('2', "ABC");
		map.put('3', "DEF");
		map.put('4', "GHI");
		map.put('5', "JKL");
		map.put('6', "MNO");
		map.put('7', "PQRS");
		map.put('8', "TUV");
		map.put('9', "WXYZ");
		
		// remove dash
		number = number.replaceAll("-", "");
		
		telephoneWordsSolver (number, map, possibleStrings, "");
		
		return possibleStrings;
	}
	
	public static String risingSquaresolver(int num)  
	{
		
		if (num <= 0) 
		{
			 return "";
		}
		
		if (num % 2 == 1) 
		{
			return risingSquaresolver(num - 2) + " " + Math.pow(num, 2)     ; 
		}
		
		if (num % 2 == 0) 
		{
			return  Math.pow(num, 2)    + " "  + risingSquaresolver(num - 2) ; 
		}
		
		return "";
	}
	
	public static String risingSquare (int num) 
	{
		return risingSquaresolver(num)  + " " + risingSquaresolver(num - 1);
	}
	
	private static void binaryExpansionSolver (String str, ArrayList<String> arrayCache, String bufferCache) 
	{
		char[] possibleValue = {'0', '1'};
		String bufferCopy;
		String strCopy;
		char c;
		
		if (str.length()== 0) 
		{
			arrayCache.add(bufferCache);
			return;
		}
		
		// first character in str
		c = str.charAt(0);
		
		// copy str arg / remove first character
		strCopy = str.substring(1);
		
		
		if (c != '?') 
		{
			bufferCopy= bufferCache + c;
			binaryExpansionSolver(strCopy, arrayCache, bufferCopy);
		}
		else 
		{
			for (int i = 0; i < possibleValue.length; i++)
			{
				bufferCopy= bufferCache + possibleValue[i];
				binaryExpansionSolver(strCopy, arrayCache, bufferCopy);
			}
		}
		
	}
	public static ArrayList<String> binaryExpansion (String str) 
	{
		ArrayList<String> array = new ArrayList<String>();
		binaryExpansionSolver(str, array, "");
		return array;
	}
	
	private static void anagramSolver (String str, ArrayList<String> arrayCache, String bufferCache) 
	{
		String bufferCopy;
		String strCopy;
		
		if (str.length() == 0) 
		{
			arrayCache.add(bufferCache);
			return;
		}
		
		for (int i = 0; i < str.length(); i++) 
		{
			bufferCopy =  str.charAt(i) + bufferCache;
			strCopy = str.substring(0, i) + str.substring(i + 1);
			anagramSolver(strCopy, arrayCache, bufferCopy);
		}
	}
	
	public static ArrayList<String> anagram (String str) 
	{
		ArrayList<String> array = new ArrayList<String>();
		anagramSolver(str, array, "");
		return array;
	}
	
	private static void climbingStairsSolver (int numOfStairs , ArrayList<ArrayList<Integer>> arrayCache, ArrayList<Integer> bufferCache) 
	{
		ArrayList<Integer> bufferCopy;
		int[] possibleValue = {1, 2};

		if (numOfStairs <= 0) 
		{
			if (numOfStairs == 0 )
			{
				arrayCache.add(bufferCache);
			}
			return;
		}
		
		
		for (int i = 0; i < possibleValue.length; i++)
		{
			// copy buffer cache 
			bufferCopy = new ArrayList<Integer>();
			if (bufferCache != null)
			{
				for (Integer retVal: bufferCache)
				{
					bufferCopy.add(retVal);
				}	
			}
			
			// add element to buffer copy
			bufferCopy.add(possibleValue[i]);
			
			climbingStairsSolver(numOfStairs - possibleValue[i], arrayCache, bufferCopy);
		}
		
	}
	
	public static ArrayList<ArrayList<Integer>> climbingStairs (int numOfStairs) 
	{
		ArrayList<ArrayList<Integer>> array = new  ArrayList<ArrayList<Integer>>();
		climbingStairsSolver(numOfStairs, array, null);
		return array;
	}
	
	private static void climbingStairsSolverSecond (int numOfStairs , ArrayList<ArrayList<Integer>> arrayCache, ArrayList<Integer> bufferCache, boolean isRight) 
	{
		ArrayList<Integer> bufferCopy;
		int[] possibleValue = {1, 2};

		if (numOfStairs <= 0) 
		{
//			System.out.println(foot + " " + bufferCache);
			if (numOfStairs == 0 && isRight == true)
			{
				arrayCache.add(bufferCache);
			}
			return;
		}
		
		
		for (int i = 0; i < possibleValue.length; i++)
		{
			// copy buffer cache 
			bufferCopy = new ArrayList<Integer>();
			if (bufferCache != null)
			{
				for (Integer retVal: bufferCache)
				{
					bufferCopy.add(retVal);
				}	
			}
			
			// add element to buffer copy
			bufferCopy.add(possibleValue[i]);
			
			climbingStairsSolverSecond(numOfStairs - possibleValue[i], arrayCache, bufferCopy, !isRight);  // first step happens at this statement
		}
		
	}
	
	public static ArrayList<ArrayList<Integer>> climbingStairsSecond (int numOfStairs) 
	{
		ArrayList<ArrayList<Integer>> array = new  ArrayList<ArrayList<Integer>>();
		climbingStairsSolverSecond(numOfStairs, array, null, true);
		return array;
	}
	
	private static void climbingStairsSolverThird (int numOfStairs , ArrayList<ArrayList<Integer>> arrayCache, ArrayList<Integer> bufferCache, boolean isRight, int leftStep, int rightStep) 
	{
		ArrayList<Integer> bufferCopy;
		int[] possibleValue = {1, 2};

		if (numOfStairs <= 0) 
		{
			if (numOfStairs == 0 && leftStep == rightStep)
			{
				arrayCache.add(bufferCache);
			}
			return;
		}
		
		for (int i = 0; i < possibleValue.length; i++)
		{
			// copy buffer cache 
			bufferCopy = new ArrayList<Integer>();
			if (bufferCache != null)
			{
				for (Integer retVal: bufferCache)
				{
					bufferCopy.add(retVal);
				}	
			}
			
			// add element to buffer copy
			bufferCopy.add(possibleValue[i]);
			
			// left or right foot moved?
			if (!isRight) 
			{
				leftStep++;
			}
			
			if (isRight) 
			{
				rightStep++;
			}
			
			climbingStairsSolverThird(numOfStairs - possibleValue[i], arrayCache, bufferCopy, !isRight, leftStep, rightStep);  // first step happens at this statement
		}
		
	}
	
	public static ArrayList<ArrayList<Integer>> climbingStairsThird (int numOfStairs) 
	{
		ArrayList<ArrayList<Integer>> array = new  ArrayList<ArrayList<Integer>>();
		climbingStairsSolverThird(numOfStairs, array, null, true, 0, 0);
		return array;
	}
	
	private static void sumOfSquaresSolver (int  num , ArrayList<ArrayList<Integer>> arrayCache, ArrayList<Integer> bufferCache, final int target) 
	{
		ArrayList<Integer> bufferCopy;
		int sqrtValue = (int) Math.sqrt(num);
		int possibleValue;
		int sum = 0;
		
		if (num == 0) 
		{
			sum = 0;
			
			if (bufferCache != null)
			{
				for (Integer retVal: bufferCache) 
				{
					sum += (int) Math.pow(retVal, 2);
				}
				
				if (sum == target)
				{
					arrayCache.add(bufferCache);
				}
			}
		}
		
		for (int i = sqrtValue - 1;  i >= 0; i-- ) // subtract 1 !
		{
			bufferCopy = new ArrayList<Integer>();
			if (bufferCache != null) 
			{
				for (Integer retVal: bufferCache ) 
				{
					bufferCopy.add(retVal);
				}
			}
			
			// add value
			bufferCopy.add(sqrtValue);
			
			// selection possible outcome (sum path)
			possibleValue = i;

			// recursion  (branching from nonempty buffer)
			sumOfSquaresSolver( (int) Math.pow(possibleValue,2) , arrayCache, bufferCopy, target);
		
			// recursion (new branch with empty buffer using possibleValue variable as root)
			sumOfSquaresSolver( (int) Math.pow(possibleValue,2) , arrayCache, null, target);

		}

	}
	
	public static ArrayList<ArrayList<Integer>> sumOfSquares(int num) 
	{
		ArrayList<ArrayList<Integer>> array = new ArrayList<ArrayList<Integer>>();
		sumOfSquaresSolver(num, array, null, num); // new branch
		return array;
	}
	
	private static void allValidNPairsOfParensSolver(int numOfPairs, ArrayList<String> arrayCache, String bufferCache) 
	{
		
	}
	
	public static ArrayList<String> allValidNPairsOfParens(int numOfPairs) 
	{
		ArrayList<String> array = new ArrayList<String>();
		allValidNPairsOfParensSolver(numOfPairs, array, null);
		return array;
	}

}
