package algo;

import java.util.ArrayList;

public class Chapter7 {
	
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

	
}

