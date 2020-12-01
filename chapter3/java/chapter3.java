package algo;

import java.util.Random;

public class Chapter3 
{
	/* custom array structure */ 
	static class Array_ 
	{
		int maxSize, len;
		int[] collection;
		
		Array_()
		{
			len = 0;
			maxSize = 1;
			collection = new int[maxSize];
		}
		
		Array_ pushFront(int value)
		{
			int [] tmp;
			
			if (len >= maxSize) // array is full!
			{
				maxSize++;
				tmp = new int[maxSize];
				for (int i = 0; i < len; i++)
				{
					tmp[i + 1] = collection[i];
				}
				tmp[0] = value;
				collection = tmp;
			}
			else  
			{
				
				/* shift right*/
				for (int i = maxSize - 1; i > 0; i--)
				{
					collection[i] = collection[i - 1];  
				}
				
				/*add to front*/
				collection[0] = value;
			}
			
			len++;
			return this;
		}
		
		Integer popFront()
		{
			Integer result = null;
			int[] replacementArray;
			
			if (len > 0)
			{
				result = collection[0];
				/* shift left*/
				replacementArray = new int[--len];
				for (int i = 1; i < len; i++)
				{
					replacementArray[i - 1] = collection[i]; 
				}
				collection = replacementArray;
			}
			return result;
		}
		
		boolean insertAt(int index, int value) 
		{
			if (index >= 0 && index < len)
			{
				collection[index] = value;
				return true;
			}
			return false;
		}
		
		Integer removeAt(int index)
		{
			Integer result = null;
			int[] replacementArray;
			int replacementArrayIndex = 0;
			
			if ( len <= 0 || (index < 0 || index >= len) )
			{
				return null;
			}
			
			replacementArray = new int [len - 1];
			
			for (int i = 0; i < len; i++) 
			{
				if (i == index) 
				{
					result = collection[i];
				}
				else 
				{
					replacementArray[replacementArrayIndex++] = collection[i];
				}
			}
			
			len--;
			collection = replacementArray;
			return result;
		}
		
		void swapPairs()
		{
			int tmp;
			for (int i = 0; i <len; i+= 2) 
			{
				tmp = collection[i];
				collection[i] = collection[i + 1];
				collection[i + 1] = tmp;
			}
		}
		
		void minToFront()
		{
			int moveValueToFront;
			int minIndex = 0;
			
			if (len <= 1)
			{
				return;
			}
			
			for (int i = 0; i < len; i++)
			{
				if (collection[i] < collection[minIndex]) 
				{
					minIndex = i;
				}
			}
			
			if (minIndex > 0) 
			{

				moveValueToFront = collection[minIndex];
				/* shift right toString ith index*/
				for (int k = minIndex; k > 0; k--)
				{
					collection[k] = collection[k - 1];
				}
				collection[0] = moveValueToFront;
			}
		}
		
		void reverse () 
		{
			int halfLen, tmp;
			
			if (len <=0) 
			{
				return;
			}
			
			halfLen = len / 2;
			for (int i = 0; i < halfLen; i++) 
			{
				tmp = collection[i];
				collection[i] = collection[len -1 - i];
				collection[len -1 - i] = tmp;
			}
		}
		
		void display()
		{
			System.out.print("[");
			if (len > 0)
			{			
				for (int ele: collection) 
				{
					System.out.print(ele + ",");
				}
			}
			System.out.println("]");
		}
		
		void display(int [] collection)
		{
			System.out.print("[");
			if (len > 0)
			{			
				for (int ele: collection) 
				{
					System.out.print(ele + ",");
				}
			}
			System.out.println("]");
		}
		
	
		
		void rotateArr(int shiftBy) 
		{
			int front, back;
			display();
			
			if (shiftBy < 0)
			{
				shiftBy = ( -1 * shiftBy ) % len;
				
				if (shiftBy == 0) 
				{
					return;
				}
				
				while (shiftBy > 0)
				{
					back = collection[0];
					for (int  i = 1; i < len; i++)
					{
						collection[i - 1] = collection[i];
					}
					collection[len - 1] = back;
					shiftBy--;
				}
				
			}
			else if (shiftBy > 0)
			{
				while (shiftBy > 0)
				{
					front = collection[len  - 1];
					for (int  i = len - 1; i > 0; i--)
					{
						collection[i] = collection[i - 1];
					}
					collection[0] = front;
					shiftBy--;
				}
			}
			display();

		}
		
		void filter(int min, int max) 
		{
			int[] newArray;
			for (int i = 0; i < len; i++) 
			{
				if (collection[i] <= min || collection[i] >= max) 
				{
					// shift down 
					for (int k = i; k < len - 1; k++) 
					{
						collection[k] = collection[k + 1];
					}
					collection[len - 1] = 0;
					len--;
				}
			}
			
			newArray = new int[len];
			for (int i = 0; i < len; i++) 
			{
				newArray[i] = collection[i];
			}
			collection = newArray;
		}
		
		int[] concat(int [] source, int [] arr)
		{
			int[] result = new int[source.length + arr.length];
			int source_index = 0, arr_index = 0;
			boolean srcDataWritable, arrDataWritable;
			
			srcDataWritable = arrDataWritable = true;
			
			/* optimized - 2 write per cycle*/
			while (srcDataWritable || arrDataWritable) 
			{
				srcDataWritable = source_index < source.length;
				arrDataWritable = arr_index < arr.length;
				
				if (srcDataWritable)
				{
					result[source_index] = source[source_index]
							;
					source_index++;
				}
				
				if (arrDataWritable)
				{
					result[result.length - 1 - arr_index] = arr[arr_index];
					arr_index++;
				}
			}
			return result;
		}

		
	}
	
	
	
	int [] skylineHeights(int[] heights)
	{
		Array_ result = new Array_();
		int max = 0;
		for (int i = 0; i < heights.length; i++) 
		{
			if (heights[i] > max)
				
			{
				max = heights[i];
				result.pushFront(max);
			}
		}
		
		result.reverse();
		
		result.display();
		return result.collection;
	}
	
	static Integer secondToLast(int [] arr)
	{
		Integer result =  null;
		if (arr.length > 1 ) 
		{
			return arr[arr.length - 1 - 2];
		}
		return result;
	}
	
	static Integer secondLargest(int [] arr)
	{
		Integer first = null, second = null;
		
		for (int  i = 0; i < arr.length; i++) 
		{
			if (first == null || arr[i] > first )
			{
				if (second != null) 
				{
					second = first;					
				}
				first = arr[i];
			}
			
			else if (second == null || arr[i] > second)
			{
				second = arr[i];
			}
		
		}
		
		if (first != null && second != null)
		{
			return second;
		}
		
		return null;
	}
	
	static Integer nthToLast (int [] arr, int n)
	{
		if (arr.length == 0) 
		{
			return null;
		}
		
		if (n > 1 && n <= arr.length)
		{
			return arr[arr.length - 1 - n];
		}
		return null;
	}
	
	static Integer nthLargest(int[] arr, int n) 
	{
		Integer threshold , currLargest ;
		
		currLargest = threshold = null;
		
		if (arr.length == 0 || n <= 0 || n > arr.length)
		{
			return null;
		}
		
		for (; n > 0; n--)
		{
			currLargest = null;
			for (int ele: arr) 
			{
				if (threshold == null || (ele < threshold && true))  // true required!!
				{
					if (currLargest == null  ||  ele > currLargest) 
					{
						currLargest = ele;
					}
				}
			}
			threshold = currLargest;
		}

		return currLargest;
	}
	
	static boolean  isCreditCardValid(int[] digitArr)
	{
		int lastDigit;
		int sum = 0;
		
		if (digitArr.length == 0) 
		{
			return false;
		}
		
		lastDigit = digitArr[digitArr.length - 1];
		
		for (int i = digitArr.length - 2; i > 0; i-= 2) 
		{
			digitArr[i] *= 2;

			if (digitArr[i] > 9) 
			{
				digitArr[i] -= 9;
			}	
		}
		
		for (int i = 0; i < digitArr.length - 1; i++)
		{
			sum += digitArr[i];
		}
		
		
		sum += lastDigit;
		
		return sum % 10 == 0;
	}
	
	/* swap*/
	static void swap (int[] collection, int posA, int posB)
	{
		int tmp = collection[posA];
		collection[posA] = collection[posB];
		collection[posB] = tmp;
	}
	
	static void shuffle (int[] arr)
	{
		Random random = new Random();
		int walk = 0;
		int rIndex;
		
		while (walk  < arr.length ) 
		{
			rIndex = random.ints(walk , arr.length).findAny().getAsInt();
			swap(arr, walk, rIndex);
			walk++;
		}
	}
	
	static int[] zipIt (int[] a, int[] b)
	{
		int [] result = new int[a.length + b.length];
		int aIndex = 0, bIndex = 0, wrIndex = 0;
		
		while (wrIndex < result.length)
		{
			if (aIndex < a.length)
			{
				result[wrIndex++] = a[aIndex++];
			}
			
			if (bIndex < b.length) 
			{
				result[wrIndex++] = b[bIndex++];
			}
		}
		return result;
	}
	
	public static void main(String args[])
	{
		Array_ arr_ = new Array_();
		for (int i = 10; i > 0; i--)
		{		}
		
		arr_.pushFront(5);
		arr_.pushFront(4);
		arr_.pushFront(3);
		arr_.pushFront(2);
		arr_.pushFront(1);
		
		int[] m = {1, 2};
		int[] n = {10, 20, 30, 40};
		
		for (int ele: zipIt(m, n) )
		{
			System.out.print("[" +  ele + "]");
		}

		
	}
}
