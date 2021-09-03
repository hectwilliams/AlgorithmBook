package algo;

import java.util.*;
import algo.myUtil.*;

public class chapter1
{
	/* class function */
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

		/* class function */
	static void biggieSize_test ()
	{
		int [] collection = {-1, 3, 5, -5};
		biggieSize(collection);
	}

	/* class function */
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

		/* class function */
	static void previousLengths_test ()
	{
		String [] words = {"hello", "shawn", "rodger"};
		ArrayList<Integer> list = previousLengths(words);
		for (int i = 0; i < list.size(); i++) {
			System.out.print(list.get(i) + ",");
		}
	}

	/* class function */
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

		/* class function */
	static void printLowReturnHigh_test ()
	{
		int [] data = {1,5,3,3,9,19,-5};
		System.out.println(printLowReturnHigh(data));
	}

	static int[] addSevenToMost(int[] collection)
	{	int size = collection.length - 1;
		int[] result = new int[size < 0 ? 0 : size ];

		for (int i = 1; i < collection.length; i++)
		{
			result[i - 1] = collection[i] + 7;
		}
		return result;
	}

		/* class function */
	static void addSevenToMost_test ()
	{
		int[] result;
		int[] data = {1,3,5,6, 9};

		result = addSevenToMost(data);
		for (int i = 0; i < result.length; i++)
		{
			System.out.println(result[i]);
		}
	}

	/* class function */
	static int printOneReturnAnother (int[] collection)
	{
		int pos = 1;
		int odd = -1;
		boolean hit = false;

		if (collection.length == 0)
		{
			System.out.println("length of array = 0");
		}

		for (; collection.length-pos >= 0; pos++)
		{
			int currPos = collection.length-pos;

			if (collection[currPos] % 2 == 1)
			{
				hit = true;
				odd = collection[currPos];
			}

			if (pos == 2) // second to last
			{
				System.out.println("second to last value: " + Integer.toString(collection[currPos]));
			}
		}
		return odd;
	}

		/* class function */
	static void printOneReturnAnother_test()
	{
		int[] collection = {1,2,4,7,9,10,12};
		System.out.println(printOneReturnAnother(collection));
	}

	/* class function */
	static void reverseArray (int[] collection)
	{
		int halfSize = collection.length / 2;
		int tmp;
		System.out.println(Integer.toString(halfSize));

		for (int i = 0 ; i < halfSize; i++)
		{
			tmp = collection[i];
			collection[i] = collection[collection.length - (i + 1)];
			collection[collection.length - (i + 1)] = tmp;
		}
	}

	/* class function */
	static void reverseArray_test ()
	{
		int[] collection = {1,2,4,7,9,10,12};

		System.out.println("before: ");
		for (int i = 0; i < collection.length; i++)
		{
			System.out.print(Integer.toString(collection[i]) + ",");
		}
		System.out.println("");

		reverseArray(collection);

		System.out.println("after: ");
		for (int i = 0; i < collection.length; i++)
		{
			System.out.print(Integer.toString(collection[i]) + ",");
		}
	}

	/* class function */
	static int[] doubleList (int[] collection)
	{
		int [] result = new int[collection.length];
		for (int i = 0; i < collection.length; i++)
		{
			result[i] = collection[i] * 2;
		}
		return result;
	}

	/* class function */
	static void doubleList_test ()
	{
		int [] collection = {1,2,3,4};
		System.out.println("before");

		// myUtil.print(collection);
		System.out.println("after");
		// algo.myUtil.print(doubleList(collection));
	}


	/* class function */
	static int[] negate (int[] collection)
	{
		int[] result = new int[collection.length];
		for (int i = 0; i < collection.length; i++)
		{
			result[i] = collection[i] < 0 ? -1*collection[i] : collection[i];
		}
		return result;
	}

		/* class function */
	static void negate_test ()
	{
		int [] collection = {-1,2,-3,4};
		int[] result = negate(collection);
		// myUtil.print(result);
	}

		/* class function */

	static void countPositives (int[] collection)
	{
		int count = 0;

		for (int ele: collection)
		{
			count += ele >= 0 ? 1 : 0 ;
		}

		if (collection.length != 0)
		{
			collection[collection.length - 1] = count;
		}
	}

		/* class function */
	static void countPositives_test()
	{
		int[] collection = {-1, 1, 1, 1};
		countPositives(collection);
		// myUtil.print(collection);
	}

	/* class function */
	static void alwaysHungry (String[] collection)
	{
		int counter = 0;
		String[] words = {"yummy", "food", "I'm Hungry"};

		for (String ele: collection)
		{
			if (ele.compareTo(words[1]) == 0)
			{
				counter += 1;
				System.out.println(words[0]);
			}
		}
		if (counter == 0)
		{
			System.out.println(words[2]);
		}
	}

		/* class function */
	static void alwaysHungry_test ()
	{
		String[] collection = {""};
		alwaysHungry(collection);
	}

	/* class function */
	static void evenAndOdds(int[] collection)
	{
		int oddCount, evenCount;

		oddCount = evenCount = 0;

		for (int ele: collection )
		{
			if (ele % 2 == 0) // even
			{
				if (oddCount > 0)
				{
					oddCount = 0;
				}

				evenCount++;

				if (evenCount == 3)
				{
					System.out.println("That's odd");
					evenCount = 0;
				}
			}

			if (ele % 2 == 1) // odd
			{
				if (evenCount > 0)
				{
					evenCount = 0;
				}

				oddCount++;

				if(oddCount == 3)
				{
					System.out.println("Even more so!");
					oddCount = 0;
				}
			}

		}
	}

		/* class function */
	static void evenAndOdds_test()
	{
		int[] collection = {1, 1, 1, 0, 1, 0, 0, 0};
		evenAndOdds(collection);
	}

	/* class function */
	static void swapTowardTheCenter(int[] collection)
	{
		int tmp;
		int halfSize = collection.length / 2;
		for (int i = 1; i <= halfSize ; i+= 2)
		{
			tmp = collection[i - 1];
			collection[i - 1] = collection[collection.length - i];
			collection[collection.length - i] = tmp;
		}
	}

		/* class function */
	static void swapTowardTheCenter_test()
	{
		int[] collection = {1, 2, 3, 4, 5, 6, 7, 8};
		swapTowardTheCenter(collection);
		// myUtil.print(collection);
	}


	/* class function */
	static void scaleArray (int[] collection, int scaleFactor)
	{
		for (int i = 0; i < collection.length; i++)
		{
			collection[i] = scaleFactor * collection[i];
		}
	}

		/* class function */
	static void scaleArray_test()
	{
		int[] collection = {1, 2, 3, 4, 5, 6, 7, 8};
		scaleArray(collection, 4);
		// myUtil.print(collection);
	}

	/* class function */
	static int[] keepLastFew(int[] collection, int x)
	{
		int[] result;
		int [] empty = new int[0];

		if (x < 0)
		{
			return empty;
		}

		result = new int[x];

		for (int i = 0; i < x; i++)
		{
			result[x - 1 - i] = collection[collection.length - 1 - i];
		}

		return result;
	}

	/* class function */
	static void keepLastFew_test()
	{
		int[] collection = {1, 2, 3, 4, 5, 6, 7, 8};
		int[] shortenedArr = keepLastFew(collection, -1);
		// myUtil.print(shortenedArr);
	}

	/* class function */

	static float slopeEquationXIntercept(float m, float b)
	{
		float x = (b * -1) / m;
		return x;
	}

		/* class function */
	static void slopeEquationXIntercept_test ()
	{
		float xIntercept = slopeEquationXIntercept(2, 3);
		System.out.println(Float.toString(xIntercept));
	}


	/* class function */
	static String whatHappensToday()
	{
		Random randObj = new Random();
		int d = (int) (randObj.nextFloat() * 100);
		String msg = "";
		int curr = 0;

		if (d < 10)
		{
			msg = "volcanos";
		}

		curr+= 10;

		if (d >= curr && d < curr + 15 )
		{
			msg = "tsunamis";
		}
		curr+= 15;

		if (d >= curr && d < curr + 20)
		{
			msg = "earthquakes";
		}
		curr+= 20;

		if (d >= curr && d < curr + 25)
		{
			msg = "blizzards";
		}
		curr+= 25;

		if (d >= curr && d < curr + 30)
		{
			msg = "meteors";
		}
		curr+= 30;

		System.out.println("what happened today kenny? " +msg);
		return msg;
	}


	/* class function */
	static void whatHappensToday_test()
	{
		whatHappensToday();
	}


	/* class function */

	static void whatReallyHappensToday()
	{
		int volcanos, tsunamis, earthquakes, blizzards, meteors;
		String s;
		String msg = "";
		volcanos = tsunamis = earthquakes = blizzards =  meteors = 0;

		for (int i = 1; i <= 100; i++)
		{
			s = whatHappensToday();
			if (s.compareTo("volcanos") == 0)
			{
				volcanos++;
			}
			if (s.compareTo("tsunamis") == 0)
			{
				tsunamis++;
			}
			if (s.compareTo("earthquakes") == 0)
			{
				earthquakes++;
			}
			if (s.compareTo("blizzards") == 0)
			{
				blizzards++;
			}
			if (s.compareTo("meteors") == 0)
			{
				meteors++;
			}
		}


		if (volcanos >= 10)
		{
			msg += "volcanos ";
		}
		if (tsunamis >= 15)
		{
			msg += "tsunamis ";
		}
		if (earthquakes >=20)
		{
			msg += "earthquakes ";
		}
		if (blizzards >= 25)
		{
			msg += "blizzards ";
		}
		if (meteors >= 30)
		{
			msg += "meteors";
		}

		System.out.println("what REALLY happened kenny: " +msg);
	}


	/* class function */
	static void whatReallyHappensToday_test()
	{
		whatReallyHappensToday();
	}

	/* class function */
	static void soaringIQ ()
	{
		double riseby = 0.01;
		double myIQ = 101;

		for (double i = riseby; i < 0.98; i+= riseby)
		{
			myIQ += i;
		}
		System.out.println(Double.toString(myIQ));
	}
	static void soaringIQ_test ()
	{
		soaringIQ();
	}

	/* class function */
	static void letterGrade (int score)
	{
		String msg = "";
		if (score < 60)
		{
			msg = "F";
		}
		if (score >= 60 && score < 70)
		{
			msg = "D";
		}
		if (score >= 70 && score < 80)
		{
			msg = "C";
		}

		if (score >= 80 && score < 90)
		{
			msg = "B";
		}
		if (score >= 90)
		{
			msg = "A";
		}

		System.out.println(msg);
	}

	/* class function */
	static void letterGrade_test()
	{
		letterGrade(101);
		letterGrade(77);
	}

	/* class function */
	static void letterGradeMoreAccurate (int score)
	{
		String sign = "";
		String msg = "";

		if (score % 10 <= 2)
		{
			sign += "-";
		}

		if (score % 10 >= 8)
		{
			sign += "+";
		}

		if (score < 60)
		{
			msg = "F";
		}
		if (score >= 60 && score < 70)
		{
			msg = "D";
		}
		if (score >= 70 && score < 80)
		{
			msg = "C";
		}

		if (score >= 80 && score < 90)
		{
			msg = "B";
		}
		if (score >= 90)
		{
			msg = "A";
		}


		if (msg != "F" && msg!= "A")
		{
			msg = sign + msg;
		}

		System.out.println(msg);

	}

	/* class function */
	static void letterGradeMoreAccurate_test()
	{
		letterGradeMoreAccurate(101);
		letterGradeMoreAccurate(77);
	}

	/* class function */
	public static void main (String args[])
	{
		letterGradeMoreAccurate_test();
	}

}


