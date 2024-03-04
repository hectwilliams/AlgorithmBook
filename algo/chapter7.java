package algo;

import java.util.ArrayList;
import java.util.HashMap;

public class chapter7 {
	
	chapter7() 
	{
		System.out.println ( this.getClass().getName() );
	}
	public static boolean balancePoint(int [] array)
	{
		/*
		 1) set pos variable to last index array 
		 2) add value at pos to accumulator 
		 3) sum numbers between first value(inclusive and pos(exclusive)  -- leftSum var
		 4) if summed == accumulator then stop
		 5) if pos == 0 stop
		 6)  decrement pos 
		 7) repeat step 2)
		 * */
		int pos;
		int acc;
		int leftSum = 0;
		
		if (array.length == 0) 
		{
			return true;
		}
		
		pos = array.length - 1;
		acc = 0;
		
		while (pos > 0) 
		{
			acc += array[pos]; 
			for (int i = 0; i < pos; i++) 
			{
				leftSum += array[i];
			}
			
			if (leftSum == acc) 
			{
				return true;
			}
			
			leftSum = 0; // reset summing variable
			pos -= 1; // step 
		}
		
		
		return false;
	}
	
	public static int balanceIndex (int [] array) 
	{
		
		int leftSum, rightSum;
		
		for (int pos = 0; pos < array.length; pos++) 
		{
			leftSum = rightSum = 0;
			
			for (int i = 0; i < pos; i++) 
			{
				leftSum += array[i];
			}
			
			for (int i = pos + 1; i < array.length; i++) 
			{
				rightSum += array[i];
			}
			
			if (leftSum == rightSum) 
			{
				return pos;
			}
			
		}
		
		return -1;
	}
	
	public static int[] tacoTruck (ArrayList<int[]> customerPositions )  
	{
		/* 
		 using customerPositions create inspection space (min x, min y, max x, max y). Traverse entire space and return optimal position
		 * */
		int[] mindistancexy = new int[2];
		int ylow, yhigh, xhigh, xlow;
		double distanceAcc = -1;
		double mindistance = -1;
		
		ylow = yhigh = xhigh = xlow = 0;
		
		if (customerPositions.size() == 0) 
		{
			return null;
		}
		
		xhigh = xlow = customerPositions.get(0)[0]  ;
		yhigh = ylow  = customerPositions.get(0)[1]  ;

		// determine inspection space 
		for (int[] xy: customerPositions) 
		{
			if (xy[0] > xhigh) 
			{
				xhigh = xy[0];
			}
			
			if (xy[1] > yhigh)
			{
				yhigh = xy[1];
			}
			
			if (xy[0] < xlow) 
			{
				xlow = xy[0];
			}
			
			if (xy[1] < ylow ) 
			{
				ylow = xy[1];
			}
		}
		
		
		// calculate lowest distance(point to all other customer positions) to find optimal customer position  
		// start x = lowest h
		// start y = highest y
		
		for ( int x = xlow; x <=  xhigh; x++ )
		{
			for (int y = yhigh; y >= ylow ; y--) 
			{
				distanceAcc = 0;
				for (int[] xy: customerPositions) 
				{
					distanceAcc += Math.abs(x - xy[0])  + Math.abs (y - xy[1]);  // distance accumulator (lower sum = optimal)
				}
				
				if (mindistance == -1 || distanceAcc < mindistance)
				{
					mindistance = distanceAcc;
					mindistancexy[0] = x;
					mindistancexy[1] = y;
				}
			}
		} 

		return mindistancexy;
	}	
	
	public static boolean binarySearch(int[] array, int target) 
	{
		int start, end, mid, size;
		int head; // head controlled by search
		
		if (array.length == 0) 
		{
			return false;
		}
		
		start = head  = 0;
		end = array.length - 1;
		
		while (end > start) 
		{
			size = (end - start) + 1;
			mid =  head + (size / 2);

			if (size % 2 == 1) // odd 
			{
				if (array[mid] == target) 
				{
					return true;
				}
				
//				 [ m - 1 ] [ mid ] [ m + 1 ] 

				if (target > array[mid] )
				{
					start  =  mid + 1;
				}
				
				if (target < array[mid]) 
				{
					end = mid - 1;
				}
				
			}
			
			if (size % 2 == 0) // even 
			{
				if (array[mid] == target || array[mid - 1] == target) 
				{
					return true;
				}
				
//				[ (m - 2) ] [ mid - 1 ] [ mid ] [ (m + 1) ] 
				
				if ( target > array[mid] )  
				{
					start = mid + 1;
				}
				
				if (target < array[mid - 1])  
				{
					end = mid - 2;
				}
			}
			
			head = start; // update!
		}
		
		return array[0] == target;
		
	}
	
	public static String minofSortedRotated (String[] sortedRotatedCollection) 
	{
		int start, end, mid, head, size;
		boolean minOnRightHalf = false;
		
		if (sortedRotatedCollection.length == 0)
		{
			return "";
		}
		
		start = head = 0;
		end = sortedRotatedCollection.length - 1;
		
		
		while (end > start) 
		{
			size = end - start + 1;
			mid = head + (size / 2);
			
			minOnRightHalf = sortedRotatedCollection[end].compareTo(sortedRotatedCollection[start]) < 0; 

			if (size % 2 == 1) // odd 
			{
				if (minOnRightHalf) 
				{
					start = mid + 1;
				}
				
				if (!minOnRightHalf) // min located on left side 
				{
					end = mid - 1;
				}
			}
			
			if (size % 2 == 0) // even 
			{
				if (minOnRightHalf) 
				{
					start = mid + 1;
				}
				
				if (!minOnRightHalf) 
				{
					end = mid - 2;
				}
			}
			
			head = start;
		}
		
		return sortedRotatedCollection[start];
	}

	public static boolean stringBinarySearch (String str, char targetc)
	{
		int start, end, mid, head, size;
		
		if (str.length() == 0) 
		{
			return false;
		}
		
		head = start = 0;
		end = str.length() - 1;
		mid =  head + (end - start) / 2;
		
		while (end > start) 
		{
			size = end - start + 1;
			mid = head + (size / 2);	
			
			if (size % 2 == 1) // odd 
			{
				if (targetc == str.charAt(mid) ) 
				{
					return true;
				}
				if (targetc > str.charAt(mid) ) 
				{
					start = mid + 1;
				}
				
				if (targetc < str.charAt(mid) ) 
				{
					end = mid - 1;
				}
			}
			
			if (size % 2 == 0) // even 
			{
				if (targetc == str.charAt(mid) || targetc == str.charAt(mid + 1) ) 
				{
					return true;
				}
				if (targetc > str.charAt(mid) ) 
				{
					start = mid + 1;
				}
				
				if (targetc < str.charAt(mid) ) 
				{
					end = mid - 2;
				}
			}
			
			head = start;
		}
		
		return false;
	}
	
	public static void removeDups (ArrayList<Integer> collection) 
	{
		int head = -1;
		int index = 0;
		
		while (head <  collection.size() - 1)  // 	[] [head] [] valid vs. [] [] [head] invalid 
		{
			index =  index % collection.size();

			if (index == 0)  // cyclic ! 
			{
				head++;
			}
		
			if (collection.get(index) == collection.get(head) && head != index) 
			{
				collection.remove(index);
			}
			else 
			{
				++index;
			}
		}
		
	}
	
	public static int mode (int [] array)
	{
		HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
		int max = -1;
		int val = -1;

		for (int retVal: array) 
		{
			if (map.containsKey(retVal) == false) 
			{
				map.put(retVal, 1); 
			}
			else 
			{
				map.replace(retVal, map.get(retVal) + 1);
				if (map.get(retVal) > max) 
				{
					val = retVal;
					max = map.get(retVal);
				}
			}
		}
		
		return val;
	}
	
	public static void arrBufferCopy(int[] src, int[] dest, int srcIdxStart, int destIdxStart, int numVals) 
	{
		while (srcIdxStart < src.length && destIdxStart < dest.length && numVals > 0) 
		{
			dest[destIdxStart++] = src[srcIdxStart++];
			numVals--;
		}
	}
	
	public static void arrBufferCopy_second(int[] src, int[] dest, int srcIdxStart, int destIdxStart, int numVals) 
	{
		while (srcIdxStart < src.length  && destIdxStart < dest.length && numVals > 0) 
		{
			dest[destIdxStart++] = src[srcIdxStart++];
			numVals--;
			destIdxStart = destIdxStart % dest.length;
			srcIdxStart = srcIdxStart % src.length;

		}
	}
	
	public static void arrBufferCopy_third(int[] src, int[] dest, int srcIdxStart, int destIdxStart, int numVals) 
	{
		// case handled in arrBufferCopy_second
		 arrBufferCopy_second(src, dest, srcIdxStart, destIdxStart, numVals);
	}
	
	public static void arrBufferCopy_fourth (int[] src, int[] dest, int srcIdxStart, int destIdxStart, int numVals)
	{
		int [] storage;
		int i;
		
		if ( dest != src) 
		{
			 arrBufferCopy_second(src, dest, srcIdxStart, destIdxStart, numVals);
		}
	
		if (dest == src) 
		{
			storage = new int[numVals] ;
			
			// store copy data in storage
			for ( i = 0; (i < numVals) && (srcIdxStart + i < src.length); i++) 
			{
				storage[i] = src[srcIdxStart + i];
			}

			// write storage elements to destination
			for (int k = 0; (k < i) && (destIdxStart + k < dest.length); k++)  // i = len of storage elements
			{
				dest[destIdxStart + k] = storage[k];
			}
			
		}
	}
	
	private static int arrBufferCopy_fifth__wrap(int[] array, int currPos, int stepdir)
	{
		currPos += stepdir;
		if (currPos < 0) 
		{
			currPos += array.length;
		}
		return currPos;
	}
	
	public static void arrBufferCopy_fifth(int[] src, int[] dest, int srcIdxStart, int destIdxStart, int numVals) 
	{
		int dest_to_src_len = 0;
		int datax, datay, data; 
		int countToSwapRegion;
		int guard = 0;
		int start, end;
		int p0, p1;
		int origin;
		
		if (numVals <= 0) 
		{
			return;
		}
		
		if (numVals >= src.length)
		{
			numVals = src.length;
		}
		
		if (src != dest) 
		{
			arrBufferCopy_second(src, dest, srcIdxStart, destIdxStart, numVals);	
		}
		
		if (src == dest) 
		{
			if (destIdxStart == srcIdxStart) 
			{
				return;
			}
			
			dest_to_src_len = Math.abs(srcIdxStart - destIdxStart);
			countToSwapRegion = src.length - dest_to_src_len;
			
			if (srcIdxStart > dest_to_src_len) 
			{
				
				if (numVals < countToSwapRegion) 
				{
					for (int i = 0; i < countToSwapRegion; i++) 
					{
						src[(destIdxStart + i) % src.length] = src[ (srcIdxStart + i) % src.length];
					}	
				}
				else 
				{
					
					for (int rot = 0; rot < dest_to_src_len; rot++) 
					{
						data = src[0];
						for (int i = 1; i < src.length; i++) 
						{
							src[i - 1] = src[i];
						}
						src[src.length - 1] = data;
					}		
					
					for (int i = 0; i < src.length - numVals; i++ ) 
					{
						p0 = src.length - dest_to_src_len - i;
						p1 = destIdxStart - 1 - i;
						
						if (p0 < 0) 
						{
							p0+= src.length;
						}
						
						if (p1 < 0) 
						{
							p1 += src.length;
						}
						
						src[p1] = src[p0];
				
					}

				}
			}
		
			if (srcIdxStart  < destIdxStart) 
			{
				if (numVals <= dest_to_src_len) 
				{
					for (int i = 0; i < dest_to_src_len; i++) 
					{
						src[(destIdxStart + i) % src.length] = src[ (srcIdxStart + i) % src.length];
					}		
				}
				else 
				{
					for (int rot = 0; rot < dest_to_src_len; rot++) 
					{
						data = src[src.length - 1];
						for (int i = src.length - 1; i > 0 ; i--) 
						{
							src[i] = src[i - 1];
						}
						src[0] = data;
					}		
					
					for (int i = 0; i < src.length - numVals; i++ ) 
					{
						p0 = srcIdxStart - 1 + i;
						p1 = destIdxStart - 1 + i;
						
						if (p0 < 0) 
						{
							p0+= src.length;
						}
						
						if (p1 < 0) 
						{
							p1 += src.length;
						}
						
						src[p0] = src[p1];

					}
					
				}
			}
			
		}
		
	}
	
	public static int iSigma (int num) 
	{
		int start = 1;
		int end = num;
		int sum = 0;
		
		while (end > start) 
		{
			sum += start + end; 
			start++;
			end--;
		}
		
		if (num % 2 == 1) 
		{
			if (start == end)
			{
				sum += start;				
			}
		}
		
		return sum;
	}
	
	public static int factorial (int num) 
	{
		int prod = 1;
		
		for (int i = num; i > 1; i-= 2)
		{
			prod *= i * (i - 1);
		}
		
		return prod;	
	}
	
	public static int fibonacci (int num) 
	{
		/*
		 * [0] [1]    		No-Op
		 * [0] [1]		 	load = 1
		 * [1] [load(1)] 	load = 2
		 * [1] [load(2)] 	load = 3
		 * [2] [load(3)] 	load = 5
		 * [3] [load(4)] 	load = 8
		 * 
		 * */
		
		int[] reg = {0, 1};
		int load = 0;
		
		if (num == 0 || num == 1)
		{
			return reg[num];
		}	
		
		for (int i = 1; i <= num; i++) 
		{
			load = reg[0] + reg[1];
			reg[0] = reg[1];
			reg[1] = load;
		}
		
		return reg[1];
	}
	
	public static int tribonacci (int num) 
	{
		/*
		 * [0] [0] [1]    		No-Op
		 * [0] [0] [1]		 	No-Op
		 * [0] [0] [1]		 	load = 1
		 * [0] [1] [1 loaded]	load = 2
		 * [1] [1] [2 loaded]	load = 4
		 * [1] [2] [4 loaded]	load = 7
		 * [2] [4] [7 loaded]	load = 13
		 * [4] [7] [13 loaded]	load = 24
		 * 
		 * */
		
		int[] reg = {0, 0, 1};
		int load = 0;
		
		if (num == 2|| num == 0 || num == 1)
		{
			return reg[num];
		}	
		
		for (int i = 2; i <= num; i++) 
		{
			load = 0;
			for (int retVal: reg) 
			{
				load += retVal;
			}
			
			for (int k = 0; k < reg.length - 1; k++) 
			{
				reg[k] = reg[k + 1];
			}
			
			reg[2] = load;
		}
		
		return reg[2];

	}
	
	public static double medianOfSortedArrays(int[]... arrays) 
	{
		/*
		 * calculate total length of all arrays
		 * calculate mid point
		 * create location_array (position) array equal to total number of arrays
		 * search each array at index (if available, index may have reached end of array list) for min
		 * store min and id (selected array)
		 * increment id in location_array
		 * repeat.. until loop exits
		 * 
		 * */
		int [] positions = new int[arrays.length];
		Integer id, curr, prev; // currrent min and previous min
		int length = 0;
		int midpoint;
		
		if (arrays.length == 0) 
		{
			return 0;
		}
		
		id = curr = prev = null;
		
		for (int[] retArray: arrays) 
		{
			length += retArray.length;
		}
		
		midpoint = (length / 2) + 1;
		
		for (int i = 0;  i < midpoint; i++)
		{
			id = 0; 
			prev = curr; // store previous min 
			curr = null;
			
			for (int p = 0; p < positions.length; p++) 
			{
				if (positions[p] < arrays[p].length)  // end not reached!
				{
					if (curr== null || arrays[p] [positions[p]] < curr)  // find next min
					{
						curr = arrays[p] [positions[p]];
						id = p;
					} 
				}
			}
			
			positions[id]++; // incr position 			
		}
		
		if (length % 2 == 1) 
		{
			return curr;
		}
		
		else 
		{
			return (curr + prev ) * 0.5;
		}	
	}
	
	
	public static Integer missingValue ( int[] array) 
	{
		// arithmetic series formula  sigma(array) = (arr.length * 0.5 ) *(front_value + last_value)
		
		double runningsum = 0;
		double sum = 0;
		int min, max;
		
		if (array.length == 0) 
		{
			return null;
		}
		
		min = max = array[0];
		
		for (int retVal: array) 
		{
			if (retVal < min) 
			{
				min = retVal;
			}
			
			if (retVal > max) 
			{
				max = retVal;
			}
			
			sum += retVal;
		}
		
		runningsum = ( array.length + 1) * (max + min) * 0.5 ; //  array.length + 1 (missing value)
		System.out.println("sum " + sum + " running sum " + runningsum + " " + " min " + min + " max " + max );
		
		return (int) (runningsum - sum);

	}
	
	public static Integer rainTerraces (int[] heights) 
	{
		int units = 0;
		int sum = 0; // sum of units 
		int h = 0;
		
		if (heights.length == 0) 
		{
			return -1;
		}
		
		sum = h = 0;
		
		for (int i = 1; i < heights.length; i++)
		{
			if (heights[i] >= h) 
			{
				units += sum;
				h = sum = 0; // reset variables 
			}
			
			if (heights[i] < heights[i - 1]) 
			{
				h = heights[i - 1];
			}
			
			if (h != 0) 
			{
				sum += h - heights[i];
			}
		}
		
		return units; 
	}
	
	public static int lastDigitofAtoTheB (int base, int exponent)
	{
		/*
		 * cyclic nature of  squares :)
		 *  12
		 *  12 * 12 = 144
		 *  12 * 12 * 12 = 1728
		 *  12 * 12 * 12 * 12 = 20736 
		 *  12 * 12 * 12 * 12 * 12 = 248832 
		 *  12 * 12 * 12  *12  *12 *12 = 2985984
		 *  12 * 12 * 12  * 12 *12 *12 *12 = 35831808 
		 * 
		 * */
		
		int stopDigit = base % 10;
		int lastDigit = stopDigit; // returned solution
		int counter = 2;
		int currDigit;
		do 
		{
			currDigit = (int)Math.pow(base, counter++) % (10);
			if (currDigit < lastDigit)
			{
				lastDigit = currDigit;
			}
		}
		while(currDigit != stopDigit);
		
		return lastDigit;
	
	}
	
	public static boolean matrixSearch (int[][] image, int[][] target)
	{
		boolean state = false;
		
		for (int r = 0; r < image.length; r++)
		{
			for (int c = 0; c < image[r].length; c++) 
			{
				if (r + target.length - 1 < image.length && c + target[0].length - 1 < image[r].length)  
				{
					state = true;
					
					//	compare to target 
					for (int lr= 0; lr < target.length; lr++) 
					{
						for (int lc = 0; lc < target[lr].length; lc++) 
						{
							state &= target[lr][lc] == image[r + lr][c + lc];
 						}
					}
					
					if (state == true) 
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	
	public static int maxOfSubarraySum (int[] array) // THIS WAS TOUGH COOKIE :) !
	{
		Integer maxSum = 0;
		int acc = 0;
		
		for (int i = 0; i < array.length; i++)
		{

			acc += array[i];
			
			if (acc > maxSum) 
			{
				maxSum = acc;
			}

			if (acc < maxSum) // direction change  (possible reset of acc variable)
			{
				
				if (i + 1 < array.length) // check next value 
				{
					if ( (array[i + 1] + acc) >= maxSum) // continue adding to accumulator  
					{
						continue;
					}
					else 
					{
						acc = 0;
					}
				}
			}

		}
		
		return maxSum;
	}
	
}

