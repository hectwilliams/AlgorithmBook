package algo;
import java.util.*;


import java.lang.*;

public class chapter2 {

	private void printUtil(int[] collection)
	{
		System.out.print("[");
		for (int i = 0; i < collection.length; i++) 
		{
			System.out.print(Integer.toString(collection[i]) + "," );
		}
		System.out.print("]\n");
	}
	
	static int sigma (int num)
	{
		int res = 0;
		for (int i = 1; i <= num; i++)
		{
			res += i;
		}
		return res;
	}
	
	static int factorial (int num) 
	{
		int res = 1;
		for (int i = 1; i <= num; i++)
		{
			res *= i;
		}
		return res;
	}
	
	
	static String drawLeftStars(int num)
	{
		String res = "";
		int headerBlankSize;
		int SIZE = 75;
		
		if (num > SIZE) 
		{
			num = SIZE;
		}
		
		for (int i = 1; i <= SIZE; i++) 
		{
			if (i <= num)
			{
				res += '*';
			}
			else 
			{
				res += ' ';
			}	
				
		}
		
		return res;
	}
	
	static String drawRightStars(int num) 
	{
		String res = "";
		char  c;
		int headerBlankSize;
		int SIZE = 75;
		
		if (num > SIZE) 
		{
			num = SIZE;
		}
		
		headerBlankSize = SIZE - num;
		
		for (int i = SIZE; i >= 1; i--) 
		{
			if (i > headerBlankSize) 
			{
				c = '*';
			}
			else 
			{
				c = ' ';
			}
			res = c + res; 				
		}
		
		return res; 
	}
	
	static String drawCenteredStars(int num) 
	{

		String res = "";
		char  c;
		int edgeBlank;
		int SIZE = 75;
		
		if (num > SIZE) 
		{
			num = SIZE;
		}
		
		edgeBlank = SIZE - num;
		
		for (int i = 1; i <= num; i++) 
		{
			res += '*';
		}
		
		while (res.length() != SIZE) 
		{
			if (res.length() % 2 == 1)
			{
				res += ' ';
			}
			else 
			{
				res = ' ' + res;
			}
		}
		
		return res; 
	}
	
	static void threeAndFives ()
	{
		int res = 0;
		for (int i = 100; i <= 4e6; i++)
		{
			if (i % 3 == 0 ^ i % 5 == 0) 
			{
				res += i;
			}
		}
		System.out.println(res);
	}
	
	static void generateCoinChange (int cents) 
	{
		int q,d,n,p;
		String info = "";
		
		q = d = n = p = 0;
		while (cents > 0)
		{
			if (cents > 25 )
			{
				q++;
				cents -=25;
			}
			
			else if (cents > 10 ) 
			{
				d++;
				cents -=10;
			}
			
			else if (cents % 5 == 0) 
			{
				n++;
				cents -=5;

			}
			
			else if (cents % 1 == 0)
			{
				p++;
				cents -=1;
			}
		}
		
		info += "quarters: " + Integer.toString(q) + "\n" + 
				"dime: " + Integer.toString(d) + "\n" + 
				"nickel: " + Integer.toString(n) + "\n" + 
				"pennies: " + Integer.toString(p) + "\n" ;
		
		System.out.println(info);
	}
	
	static int messyMath(int num)
	{
		int res = 0;
		for (int i = 0; i <= num; i++) 
		{
			if (i*3 == (num) && i != 0) 
			{
				return  - 1;
			}
			
			if (i %3 == 0) 
			{
				continue;
			}
			
			if (i % 7 == 0)
			{
				res += 2*i;
			}
			
			else 
			{
				res += i;
			}
		}
		
		return res; 
	}
	
	static int fibonacci (int num) 
	{
		int[] reg = new int[2];
		int tmp;
		
		reg[1] = reg[0] + 1;
		
		if (num == 0)
		{
			return reg[0];
		}
		
		if (num == 1)
		{
			return reg[1];
		}
		
		while (num - 2 > 0)
		{
			tmp = reg[1];
			reg[1] = reg[1] + reg[0];
			reg[0] = tmp;
			num--;
		}
		
		return reg[1];
	}
	
	static int sumToOneDigit (int num)
	{
		int sum;
		
		while (num > 9)
		{
			sum = 0;
			
			for ( int i = 10; num /i > 0; i*= 10 ) 
			{
				sum += num / i;
			}
			
			num = sum;
		}
		
		return num;
	}
	
	static void clockHandAngles(int s) 
	{
		/*
		 	Seconds Hand Unit = 360 / 60 / 6 deg
		 	Minute Hand Unit = 360 / 60 = 6 deg ( dependent on how far seconds is to full revolution )
		 	Hour Hand Unit =  360 / 12 = 30 deg (dependent on how far minute is to full revolution 
		*/
		
		float h, m, s_percent_revolution, m_percent_revolution, h_percent_revolution;
		float hDeg = 0, mDeg = 0, sDeg = 0;
		boolean isPM = false;
		
		m = ((float)(s / 60) % 60 );
		h = s / 3600 % 24;
		s = s % 60;
		
		isPM =  (h >= 12);
		
		s_percent_revolution = s / (float) 60;
		m_percent_revolution = m / (float) 60;
		h_percent_revolution = h / (float) 12;
		
		sDeg = (s_percent_revolution * 360);
		mDeg = (s_percent_revolution * 6) + m_percent_revolution * 360;
		m_percent_revolution = mDeg / 360; // update!
		hDeg = ( m_percent_revolution* 30) + h_percent_revolution * 360;
		
		System.out.println(
				"hour: " + Float.toString(h) + "\n"+
				"min: " + Float.toString(m) + "\n"+
				"sec: " + Float.toString(s) + "\n" +
				"iSPM: " + Boolean.toString(isPM) + "\n" + 
				"h-Deg: " + Float.toString(hDeg) + "\n" +
				"m-Deg: " + Float.toString(mDeg) + "\n" +
				"s-Deg: " + Float.toString(sDeg) + "\n" 

		);
	}
	
	
	static boolean isPrime (int num) 
	{
		/*
			possible prime number is less than or equal to square root of num
		*/
		
		for (int i = 2; i <= Math.floor( Math.sqrt(num)); i++)
		{
			if (num % i == 0) 
			{
				return false; 
			}
		}
		return true;
	}
	
	static int extractDigit(double num, int digitNum)
	{			
		if (digitNum < 0) 
		{
			return (int )  (num * (int)Math.pow(10, digitNum * -1)) % 10 ;
		}
		else 
		{
			return ( (int)num / (int)Math.pow(10, digitNum)) % 10;
		}
	}
	
	static int mostSigDigit(double num)
	{
		int i = 0;
		int[] arr = new int[2];
		boolean doneFlag = false;
		
		if (num == 0)
		{
			return 0;
		}
		
		do 
		{
			arr[1] = arr[0];

			if (num < 1)
			{
				arr[0] = (int) (Math.pow(10, i) * num)  % 10;	
				doneFlag = arr[0] > 0 && arr[1] == 0;
			}
			else
			{
				arr[0]  = (int) (num / (Math.pow(10, i))) % 10;	
				doneFlag = arr[0] == 0 && arr[1] > 0;
			}
			i++;
		}
		while ( !doneFlag );
		
		return arr[0] | arr[1] ;
	}
	
	/* gaming fun */
	static int rollOne () 
	{
		Random random = new Random();
		return random.ints(1, 7).findAny().getAsInt();
	}
	
	static void playFives(int num) 
	{
		int val;
		for (int i = 0; i < num; i++) 
		{
			val = rollOne();
			System.out.println(Integer.toString(val));
			if (val == 5) 
			{
				System.out.println (" That's good luck!");
			}
		}
	}
	
	static void playStatistics()
	{
		int low = 0, high = 0, experiment;
		for (int i = 0; i < 8; i++) 
		{
			experiment = rollOne();
			
			if (i == 0) 
			{
				low = high = experiment;
			}
			
			if (experiment < low) 
			{
				low = experiment;
			}
			
			if (experiment > high) 
			{
				high = experiment;
			}
		}
		
		System.out.println("low: " + low + " " + "high: " + high);
	}
	
	static void playStatistics2()
	{
		int low = 0, high = 0, experiment, sum = 0;
		for (int i = 0; i < 8; i++) 
		{
			experiment = rollOne();
			
			sum += experiment;
			
			if (i == 0) 
			{
				low = high = experiment;
			}
			
			if (experiment < low) 
			{
				low = experiment;
			}
			
			if (experiment > high) 
			{
				high = experiment;
			}
		}
		
		System.out.println("low: " + low + " " + "high: " + high + "sum: " + sum);
	}
	
	static void playStatistics3(int num)
	{
		int low = 0, high = 0, experiment, sum = 0;
		
		for (int i = 0; i < num; i++) 
		{
			experiment = rollOne();
			
			sum += experiment;
			
			if (i == 0) 
			{
				low = high = experiment;
			}
			
			if (experiment < low) 
			{
				low = experiment;
			}
			
			if (experiment > high) 
			{
				high = experiment;
			}
		}
		
		System.out.println("low: " + low + " " + "high: " + high + "sum: " + sum);
	}
	
	static void playStatistics4(int num)
	{
		int low = 0, high = 0, experiment, sum = 0;
		
		if (num  <= 0) 
		{
			return;
		}
		
		for (int i = 0; i < num; i++) 
		{
			experiment = rollOne();
			
			sum += experiment;
			
			if (i == 0) 
			{
				low = high = experiment;
			}
			
			if (experiment < low) 
			{
				low = experiment;
			}
			
			if (experiment > high) 
			{
				high = experiment;
			}
		}
		
		System.out.println("low: " + low + " " + "high: " + high + "avg: " + sum / num);
	}
	
	static void statisticUntilDoubles () 
	{
		Random random = new Random();
		int[] reg = new int[2];
		int low, high, sum, rolls;
		
		low = high = sum = rolls = 0;
		
		while ( (reg[0] == 0) || (reg[0] != reg[1]) ) 
		{	
			rolls++;
			reg[0] = reg[1];
			reg[1] = random.ints(1, 7).findAny().getAsInt();
			
			if (reg[0] == 0)
			{
				low = high = reg[0];
			}
			
			if (reg[1] < low) 
			{
				low = reg[1];
			}
			
			if (reg[1] > high)
			{
				high = reg[0];
			}
			
			sum += reg[0];
		}
		
		System.out.println("low: " + low + " " + "high: " +   "rolls: " + rolls   + " avg: " + sum / rolls);

	}
	
	/* claire is where */
	
	public static class ClaireIsWhere 
	{
		int x, y;
		
		ClaireIsWhere() 
		{
			x = y = 0;
		}

		ClaireIsWhere(int x, int y) 
		{
			this.x = y;
			this.y = y;
		}
		
		public void reset()
		{
			x = y = 0;
		}
		
		public int xLocation()
		{
			return x;
		}
		
		public int yLocation()
		{
			return y;
		}
		
		public void moveBy (int xOffset, int yOffset) 
		{
			x += xOffset;
			y += yOffset;
		}
		
		public int distanceFromHome() 
		{
			int steps = 0;
			while (x!=0 && y!=0) 
			{
				if (x > 0) 
				{
					x--;
				}
				
				if (x < 0) 
				{
					x++;
				}
				
				if (y > 0) 
				{
					y--;
				}
				
				if (y < 0) 
				{
					y++;
				}
				
			}
			return steps;
		}
		
	}
	
	/*Date on Deserted Island*/
	
	public static class DateonDesertedIsland
	{
		String[] DAYS = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		String[] MONTHS = {"January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "Novemeber", "December"}; 
		
		static int windowDayOfWeekIndex = 6;
		static int windowMonthStart;
		static int windowMonthEnd;
		static int windowDayNum = 1;

		static int currYear = 2017;
		
		
		void weekdayName(int num)
		{
			String d = ""; 
			int index = num - 1;
			
			if (index >= 0 && index <=6)
			{
				d = DAYS[index];
			
				switch(num)
				{
				case 1: 
					System.out.println(DAYS[0]);
					break;
				
				case 2:
					System.out.println(DAYS[1]);
					break;
	
				case 3:
					System.out.println(DAYS[2]);
					break;
	
				case 4:
					System.out.println(DAYS[3]);
					break;
	
				case 5:
					System.out.println(DAYS[4]);
					break;
	
				case 6:
					System.out.println(DAYS[5]);
					break;
	
				case 7:
					System.out.println(DAYS[6]);
					break;
	
				default	:
				
					
				}
			}

		}		
		
		String weekdayName2(int num)
		{
			int pos = 6; // start pos is Saturday Dec 31
			return (DAYS[ (pos + num) % 7]);
		}
		
	
		
		void someDays() 
		{
			Random random = new Random();
			String s;
			for (int i = 0; i < 17; i++) 
			{
				s = weekdayName2 ( random.ints(1, 7).findAny().getAsInt());
				
				System.out.println(s + " ");

				if (s.compareTo("Sunday") == 0 && s.compareTo("Saturday") == 0 )
				{
					System.out.println("Enjoy your day off!");
				}
				else 
				{
					System.out.println("Work hard!");
				}
			}
		}
		
		String monthName(int monthNum) 
		{
			if (monthNum < 0) 
			{
				return null;
			}
			
			monthNum = (monthNum % 12);

			if (monthNum == 0) 
			{
				monthNum = 12;
			}
			
			return MONTHS[monthNum - 1];
		}
		
		int monthToDays(int monthNum) 
		{
			String s = monthName(monthNum);
			int numOfDayInMonth = 0;
			
			if (s != null)
			{
				switch(monthNum)
				{
				case 1:
					numOfDayInMonth = 31;
					break;
				case 2:
					if ( (currYear % 4 == 0 && currYear % 100 != 0) || (currYear % 400) == 0) 
					{
						numOfDayInMonth = 29;
					}
					else 
					{
						numOfDayInMonth = 28; // not leap								
					}
					break;
				case 3:
					numOfDayInMonth = 31;
					break;
				case 4:
					numOfDayInMonth = 30;
					break;
				case 5:
					numOfDayInMonth = 31;
					break;
				case 6:
					numOfDayInMonth = 30;
					break;	
				case 7:
					numOfDayInMonth = 31;
					break;
				case 8:
					numOfDayInMonth = 31;  // not 30
					break;	
				case 9:
					numOfDayInMonth = 30;
					break;
				case 10:
					numOfDayInMonth = 31;
					break;
				case 11:
					numOfDayInMonth = 30;
					break;
				case 12:
					numOfDayInMonth = 31;
					break;
				}
			}
			return numOfDayInMonth;
		}
		
		String[] dayToMonth (int dayNum)  // limited to year 
		{
			String[] sArr = new String[3];
			int counter = 1;
			int currMonth = 1;
			int DaysInMonth = 0;
			
			if (dayNum < 0) 
			{
				return sArr;
			}
			
			currYear = 2017;
			windowDayNum = dayNum; 
			
			if (dayNum == 0) 
			{
				sArr[0] = "December";
				sArr[1] = Integer.toString(windowDayOfWeekIndex);
				sArr[2] = String.valueOf(currYear);
				return sArr;
			}
			
			windowDayOfWeekIndex = 0;
			
			do
			{
				windowDayOfWeekIndex = (windowDayOfWeekIndex + DaysInMonth ) % 7;  
				windowMonthStart = (counter + DaysInMonth)  ; 
				
				/*translate overflow to discrete window having values between 0 and 366 (i.e. 1 <= n <= 365) */
				if (windowMonthStart > 365)
				{
					windowMonthStart = windowMonthStart % 365;
					if ( windowMonthStart == 0) 
					{
						windowMonthStart = 365;
					}
				}
				
				if (DaysInMonth != 0) 
				{
					currMonth++;
					if (currMonth >= 13) // last of month in current year  
					{
						currMonth = 1;
						currYear++;
						windowDayNum -= 365;
					}
					counter += DaysInMonth;
				}
				
				DaysInMonth = monthToDays(currMonth); 
				windowMonthEnd = windowMonthStart + DaysInMonth - 1 ;
			}
			while (counter + DaysInMonth - 1  < dayNum);  // n-1 days left in month
			
			/*
			  [ 1 - 31 ]  Jan
 			  [ 32 - 59 ] Feb
 			  [ 60 - 90 ] Mar
 			  [ 91 - 120 ] Apr
 			  [ 121 - 150 ] May
			 	...
			 */
			
			sArr[0] =  monthName(currMonth);
			sArr[1] =  Integer.toString(windowDayOfWeekIndex);
			sArr[2] = String.valueOf(currYear);

			return sArr;
		}
		
		String fullDate(int dayNum) 
		{
			String dayName, dayNumber, year;
			String[] monthData;
			
			monthData = dayToMonth(dayNum);			

			if (monthData == null)
			{
				return null;
			}
			
			year = monthData[2];
			dayName = weekdayName2(dayNum);

			dayNumber = weekdayNum(windowMonthStart ,windowDayNum); 
			return dayName + ", " + monthData[0] + " " + dayNumber + " " + year;
		}
		
		String weekdayNum (int dayAfterStartOfMonthWeekPos,  int dayNum)
		{
			int pos = 1;
			pos += (dayNum - dayAfterStartOfMonthWeekPos );
			return Integer.toString( pos) ;
		}

	}

	
	public static void main (String args[]) 
	{
		chapter2 obj = new chapter2();
		DateonDesertedIsland date = new DateonDesertedIsland();
		System.out.print( date.fullDate(139947)  + " == " + "Tuesday, Freburary 29, 2400" );
	}
}
