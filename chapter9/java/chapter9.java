package algo;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;

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
	
	private static boolean parenIsValid(String str)
	{
		int openBraceCount , closeBraceCount;
		
		openBraceCount = closeBraceCount = 0;
		
		for (String retVal: str.split("") )
		{
			if (retVal.charAt(0) == '{')
			{
				if (closeBraceCount > openBraceCount) 
				{
					return false;
				}
				openBraceCount++;
			}
			
			if (retVal.charAt(0) == '}')
			{
				closeBraceCount++;
			}
		}
		
		if (openBraceCount != closeBraceCount) 
		{
			return false;
		}
		
		return true;
	}
	private static void allValidNPairsOfParensSolver(final int numOfParenthesis, ArrayList<String> arrayCache, String bufferCache) 
	{
		String bufferCopy = "";
		char[] possibleValues = {'{', '}'};
		
		if (bufferCache != null) 
		{
			if (bufferCache.length() == numOfParenthesis)
			{
				if (parenIsValid(bufferCache))
				{
					arrayCache.add(bufferCache);
				}
				return;
			}
		}
		
		for (int i = 0; i < possibleValues.length; i++) 
		{
			if (bufferCache != null) 
			{
				bufferCopy = "" + bufferCache;
			}
			
			// add value 
			bufferCopy += "" + possibleValues[i];
			
			//recursion
			allValidNPairsOfParensSolver(numOfParenthesis, arrayCache, bufferCopy);
		}
	}
	
	public static ArrayList<String> allValidNPairsOfParens(int numOfPairs) 
	{
		ArrayList<String> array = new ArrayList<String>();
		allValidNPairsOfParensSolver( (int) Math.pow(numOfPairs, 2), array, null);
		return array;
	}
	
	private static boolean isEqual (Stack<Integer> a, Stack<Integer> b) 
	{
		
		Stack<Integer> tmpStack;
		boolean hasEqualStack = false;
		
		if (a.size() != b.size()) 
		{
			return hasEqualStack;
		}
		
		tmpStack =  new Stack<Integer>();
		
		
		while ( !a.isEmpty() && !b.isEmpty() ) 
		{
			tmpStack.push(a.pop()); // first push to a
			tmpStack.push(b.pop()); 
		}
		
		hasEqualStack = true;
		
		
		while ( !tmpStack.isEmpty() ) 
		{
			b.push(tmpStack.pop()); // first pop b
			a.push(tmpStack.pop());
			hasEqualStack &= (a.peek() == b.peek());
		}
		
		return hasEqualStack;
		
	}
	
	private static boolean towerOfHanoiTestMove (int srcID, int destID, ArrayList<Stack<Integer>> towers, HashMap<Integer, ArrayList<Stack<Integer>> > map )
	{
		Stack<Integer> src, dest;
		
		src = towers.get(srcID);
		dest = towers.get(destID);
		
		if (src.size() == 0 ) 
		{
			return false;  
		}
		
		if ( (src.size() != 0) && ( dest.size() != 0) ) 
		{
			if (src.peek() > dest.peek()) 
			{
				return false;
			}
		}
		
		/* If the program accessed this tower state  return caller */
		for (Stack<Integer> retStack: map.get(srcID)) 
		{
			if (isEqual (retStack, src) )  
			{
				return false;
			}
		}
		
		map.get(srcID).add(copyStack(src)); // copy stack to table
		dest.add(src.pop()); // pop src to dest tower

		return true;
		
	}
	
	private static Stack<Integer> copyStack (Stack<Integer> stack)
	{
		Stack<Integer> clone = new Stack<Integer>();
		Stack<Integer> buffer = new Stack<Integer>();
		Integer data;
		
		while (!stack.isEmpty() ) 
		{
			buffer.push(stack.pop());
		}
		
		while (!buffer.isEmpty()) 
		{
			data = buffer.pop();
			clone.push(data);
			stack.push(data);
		}
		return clone;
	}
	
	private static ArrayList<Stack<Integer>> copyStackArray ( ArrayList<Stack<Integer>>  towers)
	{
		ArrayList<Stack<Integer>> cloneStackArray = new ArrayList<Stack<Integer>>();
		Stack<Integer> copiedStack;
		for (int i = 0; i <  towers.size(); i++) 
		{
			copiedStack = copyStack ( towers.get(i) );
			cloneStackArray.add(copiedStack); 
		}
		return cloneStackArray;
	}
	
	private static HashMap<Integer, ArrayList<Stack<Integer>> >  copyMap( HashMap<Integer, ArrayList<Stack<Integer>>> map)
	{

		HashMap<Integer, ArrayList<Stack<Integer>> > clonedMap = new HashMap<Integer, ArrayList<Stack<Integer>> >();
		for (Integer key: map.keySet())
		{
			clonedMap.put(key, copyStackArray(map.get(key)));
		}
		
		return clonedMap;
	}
	
	private static class towerOfHanoiSolverMeta
	{
		boolean done;
		int numOfIterations;
		towerOfHanoiSolverMeta() 
		{
			done = false;
			numOfIterations = 10;
		}
	}
	
	private static void  towerOfHanoiSolver(ArrayList<Stack<Integer>> towers, HashMap<Integer, ArrayList<Stack<Integer>> > map, towerOfHanoiSolverMeta meta, int iteration) // point to 'sel' tower 
	{
		ArrayList<Stack<Integer>> cloneTower;
		HashMap<Integer, ArrayList<Stack<Integer>>> cloneMap;
		int destID;
		int srcID ;
		
		if (meta.done) 
		{
			return;
		}
		
		if (towers.get(2).size() == 3)
		{
			meta.done = true;
			meta.numOfIterations = iteration;
			return;
		}
	
		for (srcID = 0; srcID < 3; srcID++)  // select tower 
		{
			for (int offset = 1; offset <= 2; offset++) // possible moves 
			{
				destID = (srcID + offset) % 3; //  move src data to dest 
				cloneMap = copyMap(map); // deep copy objects 
				cloneTower = copyStackArray(towers); // deep copy objects 
				
				if (towerOfHanoiTestMove(srcID, destID, cloneTower, cloneMap )) 
				{
					towerOfHanoiSolver(cloneTower, cloneMap, meta, iteration + 1);
				}
			}
		}
	}
	
	public static int towerOfHanoi()
	{
		ArrayList<Stack<Integer>> towers = new ArrayList<Stack<Integer>>();
		HashMap<Integer, ArrayList<Stack<Integer>> > map = new HashMap<Integer, ArrayList<Stack<Integer>> >();
		towerOfHanoiSolverMeta meta = new towerOfHanoiSolverMeta();
		
		//set up map
		for (int i = 0; i < 3; i++) 
		{
			map.put(i, new ArrayList<Stack<Integer>>());
		}
		
		// set up towers
		Stack<Integer> stack0 = new Stack<Integer>();
		Stack<Integer> stack1 = new Stack<Integer>();
		Stack<Integer> stack2 = new Stack<Integer>();

		stack0.push(3);
		stack0.push(2);
		stack0.push(1);
		
		towers.add(stack0);
		towers.add(stack1);
		towers.add(stack2);
		
		towerOfHanoiSolver (towers, map, meta, 0);
		
		return meta.numOfIterations;
	}
	
	private static int sum(ArrayList<Integer> list) 
	{
		int sum = 0;
		
		if (list == null) 
		{
			return sum;
		}
		
		for (int i = 0; i < list.size(); i++) 
		{
			sum += list.get(i);
		}
		return sum;
	}
	public static void   ipAddressesSolver (final String addr, ArrayList<String>  addrList , ArrayList<Integer> arrayCache) 
	{
		String newEntry;
		int currSum;
		ArrayList<Integer> arrayCopy; 
		int pos;
		int[] possibleValues = {1, 2, 3};
		
		if (arrayCache != null) 
		{
			if (arrayCache.size() == 4)
			{
				// add decimal points (i.e. translate into valid ip address)
				
				newEntry ="";
				pos = 0;
				for (Integer numOfChars: arrayCache ) 
				{
					if (!newEntry.isEmpty()) 
					{
						newEntry += '.';
					}
					newEntry += addr.substring(pos, pos + numOfChars);
					pos += numOfChars;
				}
				addrList.add(newEntry);
			}
		}

		currSum = sum(arrayCache);
		
		for ( int retVal: possibleValues )  
		{
			if (currSum + retVal <= 9) 
			{
				arrayCopy = new ArrayList<Integer>();
				
				// copy array 
				if (arrayCache != null) 
				{
					for (int data: arrayCache) 
					{
						arrayCopy.add( data);
					}	
				}
				
				// add number
				arrayCopy.add(retVal);
				
				ipAddressesSolver(addr, addrList, arrayCopy);
			}
		}
		
	}
	
	public static ArrayList<String> ipAddresses (String addr) 
	{
		ArrayList<String> collection = new  ArrayList<String>();
		ipAddressesSolver(addr, collection, null);
		return collection;
	}
	
	private static void generateAllPossibleCoinChangeSolver (int cents, final int [] possibleCoins, ArrayList<String> coinsCache, int [] bufferCache)
	{
		int [] bufferCopy;
		String str;
		
		if (cents == 0) 
		{
			// load string data 
			str = "";
			for (int i = 0; i < bufferCache.length; i++) 
			{
				switch (i) 
				{
				case 0:
					str += "Pennies: ";
					break;
				case 1:
					str += "Nickels: " ;
					break;
				case 2:
					str += "Dimes: ";
					break;
				case 3:                
					str += "Quarters: "; 
					break;
				}
				str += bufferCache[i] + " \t";
			}
			
			// add coin change string to coinCache
			coinsCache.add(str);
			
			return;
		}
		
		for (int i = 0; i < possibleCoins.length; i++) 
		{
			if (cents - possibleCoins[i] >= 0 ) 
			{
				bufferCopy = new int[possibleCoins.length];

				if (bufferCache != null) 
				{	
					// copy buffer
					for (int k =  0; k < bufferCache.length; k++)
					{
						bufferCopy[i] = bufferCache[i];
					}
				}
				
				// add coin
				bufferCopy[i]++;
				
				generateAllPossibleCoinChangeSolver(cents -  possibleCoins[i], possibleCoins, coinsCache, bufferCopy);
			}
		}
	}
	
	public static ArrayList<String> generateAllPossibleCoinChange (int cents) 
	{
		 ArrayList<String> collection = new  ArrayList<String>();
		int [] coins = {1, 5, 10, 25};

		 generateAllPossibleCoinChangeSolver(cents,coins, collection, null);
		 return collection;
	}
	
	public static void printChessBoard (String [][] board)
	{
		if (board == null ) 
		{
			return;
		}
		System.out.println("");

		for (int r = 0; r < board.length; r++) 
		{
			for (int c = 0; c < board[r].length; c++) 
			{
				System.out.print("[" + board[r][c] +"]");
			}
			System.out.println("");

		}
		System.out.println("");

	}
	
	private static String[][] generateChessBoard (int n)
	{
		String[][] board = new String[n][n];
		
		for (int r = 0; r < board.length; r++) 
		{
			for (int c = 0; c < board[r].length; c++) 
			{
				board[r][c] = " ";
			}
		}
		return board;
	}
	
	public static boolean isChessMoveSafe (int [] intendedMove, ArrayList<int[] > queens ) // [r][c]
	{
		
		/*
		 * Chess Notes :
		 * 
		 *  [row, col]
		 * 	[0,0] [0,1] [0,2] [0,3] [0,4] [0,5] [0,6] [0,7] 
		 * 	[1,0] [1,1] [1,2] [1,3] [1,4] [1,5] [1,6] [1,7] 
		 * 	[2,0] [2,1] [2,2] [2,3] [2,4] [2,5] [2,6] [2,7] 
		 * 	[3,0] [3,1] [3,2] [3,3] [3,4] [3,5] [3,6] [3,7] 
		 * 	[4,0] [4,1] [4,2] [4,3] [4,4] [4,5] [4,6] [4,7] 
		 * 	[5,0] [5,1] [5,2] [5,3] [5,4] [5,5] [5,6] [5,7] 
		 * 	[6,0] [6,1] [6,2] [6,3] [6,4] [6,5] [6,6] [6,7] 
		 * 	[7,0] [7,1] [7,2] [7,3] [7,4] [7,5] [7,6] [7,7] 
		 *      
		 *                 
		 *   Diagonal  diff
		 *  [0]   [-1]  [-2]  [-3]  [-4]  [-5]  [-6]  [-7] 
		 * 	[1]   [0]   [-1]  [-2]  [-3]  [-4]  [-5]  [-6] 
		 * 	[2]   [1]   [0]   [-1]  [-2]  [-3]  [-4]  [-5] 
		 * 	[3]   [2]   [1]   [0]   [-1]  [-2]  [-3]  [-4] 
		 * 	[4]   [3]   [2]   [1]   [0]   [-1]  [-2]  [-3] 
		 * 	[5]   [4]   [3]   [2]   [1]   [0]   [-1]  [-2] 
		 * 	[6]   [5]   [4]   [3]   [2]   [1]   [0]   [-1] 
		 * 	[7]   [6]   [5]   [4]   [3]   [2]   [1]   [0] 
		 *  
		 *  
		 *  [0]   [1]   [2]   [3]   [4]   [5]   [6]   [7] 
		 *  [1]   [2]   [3]   [4]   [5]   [6]   [7]   [0]
		 * 	[2]   [3]   [4]   [5]   [6]   [7]   [0]   [1]
		 * 	[3]   [4]   [5]   [6]   [7]   [0]   [1]	  [2]
		 * 	[4]   [5]   [6]   [7]   [0]   [1]	[2]   [3]
		 * 	[5]   [6]   [7]   [0]   [1]	  [2]   [3]   [4]
		 * 	[6]   [7]   [0]   [1]	[2]   [3]   [4]   [5]
		 * 	[7]   [0]   [1]	  [2]   [3]   [4]   [5]   [6]
 		 *  
 		 *  
			example queens:
			[x][x][x][q][x][x][x][x]     [x][x][x][x][q][x][x][x]      [x][x][x][x][x][q][x][x]   [x][x][x][x][x][x][q][x]                        
			[ ][ ][x][x][x][ ][ ][ ]     [ ][ ][ ][x][x][x][ ][ ]      [ ][ ][ ][ ][x][x][x][ ]   [ ][ ][ ][ ][ ][x][x][x]                        
			[ ][x][ ][x][ ][x][ ][ ]     [ ][ ][x][ ][x][ ][x][ ]      [ ][ ][ ][x][ ][x][ ][x]   [ ][ ][ ][ ][x][ ][x][ ]                        
			[x][ ][ ][x][ ][ ][x][ ]     [ ][x][ ][ ][x][ ][ ][x]      [ ][ ][x][ ][ ][x][ ][ ]   [ ][ ][ ][x][ ][ ][x][ ]                        
			[ ][ ][ ][x][ ][ ][ ][x]     [x][ ][ ][ ][x][ ][ ][ ]      [ ][x][ ][ ][ ][x][ ][ ]   [ ][ ][x][ ][ ][ ][x][ ]                        
			[ ][ ][ ][x][ ][ ][ ][ ]     [ ][ ][ ][ ][x][ ][ ][ ]      [x][ ][ ][ ][ ][x][ ][ ]   [ ][x][ ][ ][ ][ ][x][ ]                        
			[ ][ ][ ][x][ ][ ][ ][ ]     [ ][ ][ ][ ][x][ ][ ][ ]      [ ][ ][ ][ ][ ][x][ ][ ]   [x][ ][ ][ ][ ][ ][x][ ]                        
			[ ][ ][ ][x][ ][ ][ ][ ]     [ ][ ][ ][ ][x][ ][ ][ ]      [ ][ ][ ][ ][ ][x][ ][ ]   [ ][ ][ ][ ][ ][ ][x][ ]                        
                                                                                                                                      
		 * */
		
		String[][] board;
		boolean isValid;
		
		if (queens.size() == 0) 
		{
			return true;
		}
		
		board = generateChessBoard(8);
		isValid = true;
//		board[intendedMove[0]][intendedMove[1]] = "i";

		for (int[] queen : queens) 
		{
			
			// queen's position 
			if (intendedMove[0] == queen[0] && intendedMove[1] == intendedMove[1])
			{
				return false;
			}
			// left diagonal test
			if (  (queen[0] - queen[1]) ==  (intendedMove[0] - intendedMove[1]) ) 
			{
				return false;
			}
			
			// right diagonal test
			if ( (queen[0] + queen[1])  ==  (intendedMove[0] + intendedMove[1]) ) 
			{
				return false;
			}
			
			// row test
			if (queen[0] == intendedMove[0])
			{
				return false;
			}
			
			// col test
			if (queen[1] == intendedMove[1])
			{
				return false;
			}	
//			board[queen[0]][queen[1]] = "x";

		}
		
//		printChessBoard(board);

		return isValid;
		
	}
	
	public static ArrayList<int[]> allSafeChessSquares(ArrayList<int[]> queens)
	{
		final int n = 8;
		String[][] board;
		ArrayList<int[]> positionList;
		int[] data;

		board = generateChessBoard(n);
		positionList = new ArrayList<int[]>();
		
		for (int[] queen : queens) 
		{
			QueenSolverPaintBoard(board, queen);
		}   
		
		// add available squares 
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < n; c++) 
			{
				if (board[r][c] == " ")
				{
					data = new int[2];
					data[0] = r;
					data[1] = c;
					positionList.add(data);
				}
			}
		}
		
//		printChessBoard(board);

		return positionList;
	}
	
	private static String[][] copy2DArray (String [][] array2D )
	{
		int rows, cols;
		
		rows = array2D.length;
		cols = array2D[0].length;
		String[][] clone = new String[rows][cols];
		
		for (int r = 0; r < rows; r++)
		{
			for (int c  = 0; c < cols; c++) 
			{
				clone[r][c] = array2D[r][c];
			}
		}
		return clone;
	}
	
	private static ArrayList<int[]> copyList ( ArrayList<int[]> list)
	{
		ArrayList<int[]> clone = new ArrayList<int[]>();
		int [] data;
		
		for (int i = 0; i < list.size(); i++) 
		{
			data = new int[2];
			data[0] = list.get(i)[0];
			data[1] = list.get(i)[1];
			clone.add(data);
		}
		
		return clone;
	}
	
	private static void QueenSolverPaintBoard (String [][] board , int [] queen)
	{
		// left diagonal top
		for (Integer[] pos = {queen[0], queen[1] };  (0 <= pos[0] && pos[0] < 8) && (0 <= pos[1] && pos[1] < 8)  ; pos[0]--, pos[1]-- )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}
		}
	
		// left diagonal bottom
		for (Integer[] pos = {queen[0], queen[1] };  (0 <= pos[0] && pos[0] < 8) && (0 <= pos[1] && pos[1] < 8) ; pos[0]++, pos[1]++ )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}		
		}	
		
		// right diagonal top
		for (Integer[] pos = {queen[0], queen[1] }; (0 <=pos[0] && pos[0] < 8) && (0  <= pos[1] && pos[1] < 8) ; pos[0]--, pos[1]++ )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}		
		}	
		
		// right diagonal bottom
		for (Integer[] pos = {queen[0], queen[1] }; (0 <= pos[0] && pos[0] < 8) && (0 <= pos[1] && pos[1] < 8) ; pos[0]++, pos[1]-- )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}			
		}
		
		// horizontal left
		for (Integer[] pos = {queen[0], queen[1] }; (0 <= pos[0] && pos[0] < 8) && (0  <= pos[1] && pos[1] < 8) ; pos[1]-- )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}			
		}
		
		// horizontal right
		for (Integer[] pos = {queen[0], queen[1] };  (0 <= pos[0] && pos[0] < 8) && (0  <= pos[1] && pos[1] < 8) ; pos[1]++ )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}			
		}
		
		// vertical top
		for (Integer[] pos = {queen[0], queen[1] };  (0 <= pos[0] && pos[0] < 8) && (0  <= pos[1] && pos[1] < 8) ; pos[0]-- )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}			
		}
		
		// vertical bottom
		for (Integer[] pos = {queen[0], queen[1] };  (0 <= pos[0] && pos[0] < 8) && (0  <= pos[1] && pos[1] < 8) ; pos[0]++ )
		{
			if (board[pos[0]][pos[1]] != "q")
			{
				board[pos[0]][pos[1]] = "x";
			}			
		}
		
		board[queen[0]][queen[1]] = "q";
	}
	
	public static void displayQueensOnBoard (int n, ArrayList<int[]> list) 
	{
		String [][] board = new String [n][n];
		
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++) 
			{
				board[i][j] =" ";
			}
		}
		
		for (int[] pos: list) 
		{
			board[pos[0]][pos[1]] = "x";
		}
		
		printChessBoard(board);
		
	}
	
	private static int[] filter (int[] src, int index) 
	{
		int[] dest = new int[src.length - 1];
		int pos = 0;
		for (int i = 0; i < src.length; i++) 
		{
			if (i == index) 
			{
				continue;
			}
			dest[pos++] = src[i];
		}
		return dest;
	}

	public static void eightQueensSolver (final int n, ArrayList<ArrayList<int[]>> arrayCache, int[] availableRows, String [][] board,  ArrayList<int[]> queensCache)
	{
		String [][] boardCopy = null;
		ArrayList<int[]> bufferCopy = null;
		int[] remainingRows = null;
		int[] newPos;
		
		if (queensCache == null) 
		{
			bufferCopy = new ArrayList<int[]>();
			board   = generateChessBoard(n);
			availableRows = new int[n];
			for (int i = 0; i < availableRows.length; i++) 
			{
				availableRows[i] = i;
			}
			queensCache = new ArrayList<int[]>();
		}
		
		if (queensCache.size() == n ) 
		{
			arrayCache.add(copyList(queensCache)); 
			return;
		}	
		
		for (int i = 0; i < availableRows.length; i++) 
		{
			for (int j = 0 ; j < n; j++) 
			{
				newPos = new int[2]; 
				
				// queen placement
				newPos[0] = i;
				newPos[1] = j;
	
				bufferCopy = copyList(queensCache);  

				// filter 
				remainingRows = filter(availableRows, i);
				
				// check board 
				if (board[newPos[0]][newPos[1]] != " ")
				{
					continue;
				}

				// set queen 
				if (isChessMoveSafe(newPos, bufferCopy))  // new position safe? 
				{
					bufferCopy.add(newPos);   // add queen to list 
					boardCopy = copy2DArray(board);
					QueenSolverPaintBoard(boardCopy, newPos);
					eightQueensSolver(n, arrayCache, remainingRows,  boardCopy, bufferCopy);	
				}
			}

		}	
	}
	
	public static ArrayList<ArrayList<int[]>> eightQueens ()
	{
		final int n = 8;
		
		ArrayList<ArrayList<int[]>> array = new ArrayList<ArrayList<int[]>>();
		eightQueensSolver(n,array, null, null, null);
		return array;
	}

}
