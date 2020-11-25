package algo;

import java.util.*;

public class Chapter1 
{
	static void biggieSize (int numList[]) 
	{
		for (int i = 0; i < numList.length; i++) 
		{
			if (numList[i] > 0) 
			{
				System.out.println(Integer.toString(numList[i]));
			}
		}
	}
	static void biggieSize_test ()
	{
		int [] collection = {-1, 3, 5, -5};
		biggieSize(collection);
	}
	
	static ArrayList<Integer> previousLengths (String collection[])
	{
		ArrayList<Integer> result = new ArrayList<Integer>() ; // undefined at result[0]
		for (int i = 0; i < collection.length; i++) 
		{
			if (i == 0) 
			{
				result.add(-1);
			}
			else 
			{
				result.add(collection[i - 1].length());
			}
			
		}
		return result;
	}
	static void previousLengths_test ()
	{
		String [] words = {"hello", "shawn", "rodger"};
		ArrayList<Integer> list = previousLengths(words);
		for (int i = 0; i < list.size(); i++) {
			System.out.print(list.get(i) + ",");
		}
	}
	
	static int printLowReturnHigh (int[] collection) 
	{
		int low, high;
		
		low = high = 0;
		if (collection.length == 0) 
		{
			System.err.println("empty array");
			return -1;
		}
		else 
		{
			low = high = collection[0];
			for (int i = 0; i < collection.length; i++) 
			{
				if (collection[i] < low)
				{
					low = collection[i];
				}
				
				if (collection[i] > high) 
				{
					high = collection[i];
				}
			}
		}
		
		System.out.println(low);
		return high;
	}
	
	static void printLowReturnHigh_test ()
	{
		int [] data = {1,5,3,3,9,19,-5};
		System.out.println(printLowReturnHigh(data));
	}


	public static void main (String args[]) 
	{
		printLowReturnHigh_test();
	}
	
}

