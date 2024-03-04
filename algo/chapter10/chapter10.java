package algo.chapter10;

import java.util.ArrayList;
import java.util.HashMap;

public class chapter10 {

	public static String[] stringToArray (String str)
	{
		String[] array = {};
		String [] bufferArray = new String[0];
		char c;
		int p1 = 0;
		String buffer;
		int size = 0;
		
		while (p1 < str.length()) 
		{
			
			// find next char
			while ( !(('a' <= str.charAt(p1) && 'z' >= str.charAt(p1))  || ('A' <= str.charAt(p1) && 'Z' >= str.charAt(p1)) ))
			{
				c = str.charAt(p1);
				p1++;

			}
			
			buffer = "";
			do
			{
				c = str.charAt(p1++);
				buffer +=  c;
			}
			while ( ('a' <= c && 'z' >= c)  || ('A' <= c && 'Z' >= c)  );
			
			// String wringy 
			bufferArray = new String[size + 1]; 
			for (int i = 0; i < array.length; i++) 
			{
				bufferArray[i] = array[i];
			}
			bufferArray[size++] = buffer;
			
			// point return array to bufferArray 
			array = bufferArray;
		}
		
		
		return array;
	}
	
	public static String longestWord(String str)
	{
		char c;
		int p1 = 0;
		String longestWrd,buffer;
		
		longestWrd = "";
		
		while (p1 < str.length()) 
		{
			// find next char
			while ( !(('a' <= str.charAt(p1) && 'z' >= str.charAt(p1))  || ('A' <= str.charAt(p1) && 'Z' >= str.charAt(p1)) ))
			{
				c = str.charAt(p1);
				p1++;
			}
			
			buffer = "";
			do
			{
				c = str.charAt(p1++);
				buffer +=  c;
			}
			while ( ('a' <= c && 'z' >= c)  || ('A' <= c && 'Z' >= c)  );
			
			if (buffer.length() > longestWrd.length())
			{
				longestWrd = buffer;
			}
		}
		
		return longestWrd;
	}
	
	public static String reverseWordOrder(String str)
	{
		char c;
		int p1 = str.length() -1;
		String buffer;
		String result = "";
		
		while (p1 > 0) 
		{
			
			// find next char
			while ( !(('a' <= str.charAt(p1) && 'z' >= str.charAt(p1))  || ('A' <= str.charAt(p1) && 'Z' >= str.charAt(p1)) ))
			{
				c = str.charAt(p1);
				p1--;
			}
			
			buffer = "";
			do
			{
				c = str.charAt(p1--);
				buffer =  c + buffer;
			}
			while ( p1 != -1 && (('a' <= c && 'z' >= c)  || ('A' <= c && 'Z' >= c)  ) );
			
			// append to string 
			result = result +buffer ;
		}
		
		return result;
	}
	
	public static ArrayList<String> uniqueWordsTest (String str)
	{
		ArrayList<String> array = new ArrayList<String>();
		HashMap<String, Integer> map = new HashMap<String, Integer>();
		String [] data;
		
		data = stringToArray(str);
		
		for (String s: data)
		{
			if (!map.containsKey(s))
			{
				map.put(s, 0);
			}
			
			map.replace(s, map.get(s) + 1);
		}
		
		for (String key: map.keySet())
		{
			if (map.get(key) == 1 && !key.isBlank()) 
			{
				array.add(key);
			}
		}
		
		return array;
	}
	
	public static String rotateString (String str, int shifts) 
	{
		char c;
		String s = "";
		
		for (int i = 0; i < shifts % str.length(); i++) 
		{
			c = str.charAt(str.length() - 1);
			s = "" + c;
			
			for ( int k = 1; k < str.length(); k++) 
			{
				s += str.charAt(k);
			}
			
		}
		return s;
	}
	
	public static String censor (String str, String[] naughtyList)
	{
		
		/*
		 * 
		 * 
		 * Snap crackle pop nincompoop!
		 * 1) b0 = S  b1 = S
		 * 1) b0 = Sn  b1 = Sn
		 * 1) b0 = Sna  b1 = Sna
		 * 1) b0 = Snap  b1 = Snap
		 * 1) b0 = Snap   b1 = Snap 
		 * 1) b0 = Snap c  b1 = Snap x 
		 * 1) b0 = Snap cr  b1 = Snap xx 
		 * 1) b0 = Snap cra  b1 = Snap xxx 
		 * 1) b0 = Snap crac  b1 = Snap xxxx
		 * 1) b0 = Snap crack  b1 = Snap xxxxx
		 * 1) b0 = Snap crack   b1 = Snap xxxxx 
			overwrite b0
		 * 1) b0 = Snap xxxxx   b1 = Snap xxxxx 
		 * 1) b0 = Snap xxxxxl   b1 = Snap xxxxxl
		 * 1) b0 = Snap xxxxxle   b1 = Snap xxxxxle
		 * 
		 * 
		 * */
		
		int pos = 0;
		String buffer, bufferNull = "";
		char c;
		
		for (String word: naughtyList) 
		{
			// reset buffers
			buffer = bufferNull = "";
			
			for (int index = 0; index < str.length(); index++) 
			{
				c =  str.charAt(index);
			    buffer += c;
			    
			    // non-match  (reset pos index and set bufferNully to buffer)
				if (word.charAt(pos) != c)
				{
					pos = 0;
					bufferNull =  buffer;
				}
				
			    //char found (append and possible match process)
				if (word.charAt(pos) == c)
				{
					pos++;
				    bufferNull +=  "x";
				    
				    // whole word match found !
				    if (pos == word.length()) 
					{
						buffer =  bufferNull;
						pos = 0;
					}
				}
			}
			
			str = buffer;

		}

		
		return bufferNull;
	}
	
	public static boolean ionlsRotat(String s1, String s2) 
	{
		int offset = 0;
		int count;
		int i ;
		
		if (s1.length() != s2.length()) 
		{
			return false;
		}
		
	
		for (i = 0; i < s1.length(); i++)  
		{
			if (s1.charAt(i) == s2.charAt(0)) 	// possible match 
			{
				count = offset = 0;
				while ( offset < s1.length()) // search
				{
					if (s1.charAt( (i + offset) % s1.length()) == s2.charAt(offset))
					{
						count++;
						if (count == s1.length()) 
						{
							return true;
						}
					}
					offset++;
				}
			}
		}
		
		return false;
	}
	
	public static String badCharacters (String s1, String badchars)
	{
		char c;
		String buffer = "";
		
		for (String retStr: badchars.split(""))
		{
			c = retStr.charAt(0);
			buffer = "";
			
			// remove char 
			for (int i = 0; i < s1.length(); i++) 
			{
				if (c != s1.charAt(i))
				{
					buffer += s1.charAt(i);
				}
			}
			// change s1
			s1 = buffer;
		}
		
		return buffer;
	}
	
	public static boolean geneticMarker (String s, String[] array)
	{
		int len = 0;
		
		if (array.length == 0)
		{
			return false;
		}
		
		for (String w: array) 
		{
			len = 0;
			
			if (w.length() != s.length()) 
			{
				continue;
			}
			
			// test words
			for (int i = 0; i < w.length(); i++) 
			{
				
				if (w.charAt(i) == '?' ||w.charAt(i) == s.charAt(i)) 
				{
					len++;
					if (len == s.length())
					{
						return true;
					}
				}
			}
		}
		
		return false; 
	}
	
	private static String [] copyArray (String [] src) 
	{
		String [] res = new String[src.length];
		for (int i = 0 ; i < src.length; i++) 
		{
			res[i] = src[i];
		}
		return res;
	}
	
	private static char [] copyArray (char [] src) 
	{
		char [] res = new char[src.length];
		for (int i = 0 ; i < src.length; i++) 
		{
			res[i] = src[i];
		}
		return res;
	}
	private static void swap (String[] collection, int i, int j) 
	{
		if (i == j || collection.length == 0) 
		{
			return;
		}
		String tmp = collection[i];
		collection[i] = collection[j];
		collection[j] = tmp;
	}
	
	private static void displayStrings(String[] collection) 
	{
		System.out.print("[ ");
	
		for (String retStr: collection) 
		{
			System.out.print(retStr + ",");
		}		
		System.out.println("] ");
	}
	
	private static void  optimalSequenceSolver (String[] strings, ArrayList<String[]> solCache, String [] buffer , int row, int col) // GEEZ THIS WAS TOUGH TO WRAP AROUND !
	{
		
	/* primary order controlled by first column of each array entry 
		[ E,,,] 
		[ E,A,,] 
		[ A,E,G,] 
		[ AR,E,G,] 
		[ AR,EA,G,] 
		[ AR,EA,GA,]
	 
	 	order must be retained  in remaining columns
		[ AR,EA,GA,] invalid
	    [ AA,EA,GE,] valid 
	*/
		
		String [] copyBuffer, copyStrings;
		int colSize = strings[0].length();
		int rowSize = strings.length;
		char[] cArray = {'A', 'Z'};
		
		
		if (buffer == null) 
		{
			buffer = new String[strings.length];
			for (int i = 0; i < strings.length; i++) 
			{
				buffer[i] = "";
			}
		}
		
		if (solCache.size() != 0) 
		{
			return;
		}
		if (buffer != null) 
		{
			if (row >= rowSize) 
			{
				row = 0;
				col += 1;
				if (col == colSize )
				{
					solCache.add(buffer);
					return;
				}
			}
			
			if ( strings[row].charAt(col) != '?' ) 
			{
				cArray[1] = cArray[0] = strings[row].charAt(col);
			}
			
			for (char c = cArray[0]; c <= cArray[1]; c++)  
			{	
				// copy array of string
				copyStrings = copyArray(strings);
				// copy buffered data 
				copyBuffer = copyArray(buffer);
				// append character to buffer mem location
				copyBuffer[row] += c;
				
				if (row != 0 && col == 0 && copyBuffer[row].length() == 1) 
				{
					while (copyBuffer[row].charAt(0) < copyBuffer[row - 1].charAt(0) ) 
					{
						swap(copyBuffer, row, row - 1);
						swap(copyStrings, row, row - 1);
					}
				}
				
				if ( copyBuffer[row].length() > 1  && row != 0)  
				{
					// swap due to column values 
					if (copyBuffer[row - 1].charAt(col) > copyBuffer[row].charAt(col))
					{
						// swap both buffer and array to sustain order 
						swap(copyBuffer, row, row - 1);
						swap(copyStrings, row, row - 1);					
					}
					
					// is order retained due to column swap?
					if (copyBuffer[row - 1].compareTo(copyBuffer[row]) > 0)
					{
						continue;
					}
				}
				
				optimalSequenceSolver(copyStrings, solCache, copyBuffer, row + 1, col );
			}
		}
	}

	public static ArrayList<String[]> optimalSequence (String[] array) 
	{
		ArrayList<String[]> sols = new ArrayList<String[]>();
		optimalSequenceSolver(array, sols, null, 0, 0);
		return sols;
	}
	
	public static String dedupe (String str) 
	{
		String slicedString = "";
		boolean dupFound = false;
		
		if (str.length() == 0) 
		{
			return  "";
		}
		for (int k = 1; k < str.length(); k++) 
		{
			slicedString += str.charAt(k);
			dupFound |= str.charAt(0) == str.charAt(k);
		}
		
		if (!dupFound)
		{
			return str.charAt(0) + dedupe(slicedString);
		}
		
		return dedupe(slicedString) ;
	}
	
	public static int firstUniqueLetter (String str)
	{
		int i = -1;
		int counter = 0;
		
		
		for (int p = 0; p < str.length(); p++) 
		{
			counter = 0;
			
			for (i =  0; i < str.length(); i++) 
			{
				
				if (p == i) 
				{
					continue;
				}
				
				if ( str.charAt(p) == str.charAt(i) )	
				{
					counter++;
				}	
			}
			
			if (counter == 0) 
			{
				return p;
			}
		}
		
		return -1;
	}
	
	public static String uniqueLetters (String str) 
	{
		int counter = 0;
		String buffer = "";
		
		if (str.length() == 0) 
		{
			return "";
		}
		
		for (int  i= 1; i < str.length() ; i++ ) 
		{
			if (str.charAt(0) != str.charAt(i))
			{
				buffer += str.charAt(i);
			}
			
			if (str.charAt(0) == str.charAt(i))
			{
				counter++;
			}
		}

		if (counter == 0)
		{
			return str.charAt(0) + uniqueLetters(buffer);
		}
		
		return uniqueLetters(buffer);
			
	}
	

	public static String numToString (double num) 
	{
		/*
		 * decimal precision limit of 5  0.xxxxx. 
		 * 
		 * */
		
		int whole = 0;
		int n = 10;
		int val = 0;
		double buf;
		double decOne = 0.1;
		double currDecimal = 0.0;
		String decimalStr = "";
		String wholeStr = "";
		int threshold = 0;

		// calculate whole region 
		buf = num;
		n = 0;
		while ((int) buf !=0)
		{
			val = ((int) buf) % 10;
			whole += (int) Math.pow(10, n++) * val;
			buf /= 10;
			wholeStr = val + wholeStr;
		}
		
		// calculate fractional region  

		buf = num;
		n = 10;
		while ( threshold < 15 && (num - currDecimal - whole) != 0) 
		{
			threshold++;
			val = 0;
			buf = num;
			while ( ((int) (buf*n) % 10) != 0)
			{
				buf -=  decOne ;
				val++;
			}
			currDecimal += val * decOne;
			decOne /= 10;
			n *= 10;
			decimalStr += val;
		}
		
		if (wholeStr.length() == 0) 
		{
			wholeStr = "0";
		}
		
		if (decimalStr.length() == 0) 
		{
			decimalStr = "0";
		}
		return wholeStr + "." + decimalStr;
		
	}
	
	private static String parserNumber(String s , boolean isDecimal)
	{
		String result = "";
		int realIndex;
		char c;
		
		for (int i = 0; i < s.length() && !isDecimal; i++) 
		{
			c = s.charAt(i);
			
			realIndex = 2 - i;
			
			switch(realIndex)
			{
			
			case 2:
				if (c == '1') 
				{
					result = "one";
				}
				
				if (c == '2') 
				{
					result = "two";
				}
				
				if (c == '3') 
				{
					result = "three";
				}
				
				if (c == '4') 
				{
					result = "four";
				}
				
				if (c == '5') 
				{
					result = "five";
				}
				
				if (c == '6')
				{
					result = "six";
				}
				
				if (c == '7') 
				{
					result = "seven";
				}
				
				if (c == '8') 
				{
					result = "eight";
				}
				
				if (c == '9') 
				{
					result = "nine";
				}
				
				break;
			case 1:
				
				if (c == '1')
				{
				
					
					if (result == "one") 
					{
						result = "eleven";
					}
					
					if (result == "two")
					{
						result = "twelve";
					}
					
					if (result == "three")
					{
						result = "thirteen";
					}
					
					if (result == "four")
					{
						result = "fourteen";
					}
					
					if (result == "five")
					{
						result = "fifteen";
					}
					
					if (result == "six")
					{
						result = "sixteen";
					}
					
					if (result == "seven")
					{
						result = "seventeen";
					}
				
					if (result == "eight")
					{
						result = "eighteen";
					}
					
					if (result == "nine")
					{
						result = "nineteen";
					}
				}
				
				if (c == '2')
				{
					result = "twenty " + result;
				}
				
				if (c == '3')
				{
					result = "thirty " + result;
				}
				
				if (c == '4') 
				{
					result = "fourty " + result;
				}
				
				if (c == '5') 
				{
					result = "fifty " + result;
				}
				
				if (c == '6')
				{
					result = "sixty " + result;
				}
				
				if (c == '7') 
				{
					result = "seventy " + result;
				}
				
				if (c == '8') 
				{
					result = "eighty " + result;
				}
				
				if (c == '9') 
				{
					result = "ninety " + result;
				}
				
				break;
			
			case 0:
				
				if (c ==  '1')
				{
					result = "one hundred " + result;
				}
				
				if (c == '2') 
				{
					result = "two hundred " + result;
				}
				
				if (c == '3') 
				{
					result = "three hundred " + result;
				}
				
				if (c == '4') 
				{
					result = "four hundred " + result;
				}
				
				if (c == '5') 
				{
					result = "five hundred " + result;
				}
				
				if (c == '6') 
				{
					result = "six hundred " + result;
				}
				
				if (c == '7')
				{
					result = "seven hundred " + result;
				}
				
				if (c == '8') 
				{
					result = "eight hundred " + result;
				}
				
				if (c == '9')
				{
					result = "nine hundred " + result;
				}
				
				break;
				

			}
			System.out.println("result:  " + result);

		}
		
		
		for (int i = 0 ; i < s.length() && isDecimal; i++) 
		{
			c = s.charAt(i);
			
			if (c == '0') 
			{
				result += "zero ";
			}
			
			if (c == '1') 
			{
				result += "one ";
			}
			
			if (c == '2') 
			{
				result += "two ";
			}
			
			if (c == '3') 
			{
				result += "three ";
			}
			
			if (c == '4') 
			{
				result += "four ";
			}
			
			if (c == '5') 
			{
				result += "five ";
			}
			
			if (c == '6')
			{
				result += "six ";
			}
			
			if (c == '7') 
			{
				result += "seven ";
			}
			
			if (c == '8') 
			{
				result += "eight ";
			}
			
			if (c == '9') 
			{
				result += "nine ";
			}
		}

		return result;
	}
	
	public static String numToText (double number)
	{
		final String[] metricNumbers = {"Thousand", "Million", "Billion", "Trillion", "Quadrillion"};
		String w = "";
		String d = "";
		String buffer = "";
		String tmp = "";
		int metricIndex = -1;
		int i = 0;
		String strData = numToString(number);
		
		// process whole section
		{
			while (strData.charAt(i) != '.') 
			{
				w += strData.charAt(i);
				i++;
			}
			
			for (int k = 0; k < w.length(); k++) 
			{
				buffer += w.charAt(k);
	
				if (buffer.length() == 3) 
				{
					tmp += parserNumber(buffer, false);
					metricIndex++;
					buffer = "";
					
					if (k + 1 < w.length())
					{
						tmp = metricNumbers[metricIndex] + " " +  tmp;
					}
				}
			}	
			
			if (buffer.length() != 0) 
			{
				tmp = parserNumber(buffer, false) + " " + tmp;
			}
			
		}
		
		// process decimal section
		{
			i++;
			while (i < strData.length()) 
			{
				d += strData.charAt(i);
				i++;
			}
			
			d = parserNumber(d, true);
		}
		
		return  tmp +  "and " + d;
	}
	
	public static boolean isPermutation (String s1, String s2)
	{
		int count;
		
		if (s1.length() != s2.length()) 
		{
			return false;
		}
		
		for (int i = 0; i < s1.length(); i++) 
		{
			count = 0;
			
			if (s1.charAt(i) == s2.charAt(0)) 
			{
				for (int offset = 0; offset < s1.length(); offset++) 
				{
					if (s1.charAt( (i + offset)  % s1.length()) == s2.charAt(offset ) )
					{
						count++;
					}
				}
			
				if (count == s1.length())
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	public static boolean isPangram (String s)
	{
		String buffer = "";
		int k = 0;
		char c;
		
		if (s.length() == 0) 
		{
			return false;
		}
		
		// lowercase
		s = s.toLowerCase();
		
		for (int i = 0; i < s.length(); i++) 
		{
			c = s.charAt(i);
			for (k = 0; k < buffer.length(); k++) 
			{
				if (c == buffer.charAt(k) ) 
				{
					break;
				}
			}
			
			if (buffer.length() == 0 || k == buffer.length())   // k search completed with no match!
			{
				if ( 97 <= c && 122 >= c ) 
				{
					buffer += c;
					
				}
			}
		}
		return buffer.length() == 26;
	}

	public static boolean perfectPangram (String s)
	{
		String buffer = "";
		char c;
		int index;
		int [] map = new int[26];
		int count = 0;
		
		if (s.length() == 0) 
		{
			return false;
		}
		
		// lowercase
		s = s.toLowerCase();
		
		for (int i = 0; i < s.length(); i++) 
		{
			c = s.charAt(i);
			if ( 97 <= c && c <= 122) 
			{
				index = (int)c - 97;
				if (map[index] == 0) 
				{
					count++;
					map [index]++; 
				}
				
				else 
				{
					return false;
				}	
			}
			
		}
		
		return count == 26;
	}
	
	
	private static void allPermutationsSolver (String s, ArrayList<String> cache, String buffer)
	{
		String bufferCopy;
		String sCopy;
		
		if (buffer == null) 
		{
			buffer = "";
		}
		
		if (s.length() == 0) 
		{
			cache.add(buffer);
		}
		
		for (int i = 0;  i < s.length(); i++) 
		{
			//copy string (filter)
			sCopy = "";
			for (int k = 0; k < s.length(); k++)
			{
				if (k == i) 
				{
					continue;
				}
				sCopy += s.charAt(k);
			}
			
			// copy buffer 
			bufferCopy = "";
			for (int k = 0; k< buffer.length(); k++) 
			{
				bufferCopy += buffer.charAt(k);
			}
			bufferCopy += s.charAt(i);
			
			allPermutationsSolver(sCopy, cache, bufferCopy);
		}
	}
	
	public static String[] allPermutations (String s)
	{
		String[] array;
		int size = 1;
		ArrayList<String> mem = new ArrayList<String>();	
		
		for (int i = s.length() ; i > 0; i-- ) 
		{
			size *= i; 
		}
		
		allPermutationsSolver(s, mem, null);
		array = new String[size];
		
		for (int i = 0; i < mem.size(); i++) 
		{
			array[i] = mem.get(i);
		}
		
		return array;
	}
	
	private static void printArray(int [] arr) 
	{
		System.out.print("[");
		for (int ret: arr)
		{
			System.out.print(ret + ",");
		}
		System.out.println("]");
	}
	
	private static void bestTimeBuyAndSellStockSolver (int [] arr, int buy, int sell, int max[])
	{
		
		/*
		 * {6, 4, 6, 5, 9, 7, 6, 12, 2, 6, 11, 2, 4}
		 * 
		 *  buy(6)
		 *  	sell(4)
		 *  	sell(6)
		 *  	sell(5)
		 *  	sell(9)
		 *  	sell(7)
		 *  	sell(6)
		 *  	sell(12)
		 *  	sell(2)
		 *  	sell(6)
		 *  	sell(11)
		 *  	sell(2)
		 *  	sell(4)
		 *
		 * buy(4)
		 *		sell(6)
		 *  	sell(5)
		 *  	sell(9)
		 *  	sell(7)
		 *  	sell(6)
		 *  	sell(12)
		 *  	sell(2)
		 *  	sell(6)
		 *  	sell(11)
		 *  	sell(2)
		 *  	sell(4)		  
		 * 
		 * buy(6)
 				sell(5)
		 *  	sell(9)
		 *  	sell(7)
		 *  	sell(6)
		 *  	sell(12)
		 *  	sell(2)
		 *  	sell(6)
		 *  	sell(11)
		 *  	sell(2)
		 *  	sell(4)			  
		 * 
		 * 
		 * 
		 * 
		 * 
		 * */
		
		int [] arrCopy;
		int price;
		int rcvdBuy = buy;
		int rcvdSell = sell;
		int n = 0;
		
		if (buy != 0 && sell != 0) 
		{
			price = sell - buy;
			if (price > max[0])
			{
				max[0] = price;
			}
			return;
		}
		
		if (arr.length == 0) 
		{
			return;
		}
		
		for (int i = 0; i < arr.length; i++) 
		{	
			n = 0;
			
			if (buy == 0) 
			{
				buy = arr[i];
			}
			else if (sell == 0) 
			{
				sell = arr[i];
			}
			
			arrCopy = new int[arr.length - i - 1];
			for (int k =  i + 1; k < arr.length; k++)
			{
				arrCopy[n++] = arr[k];
			}
			
			bestTimeBuyAndSellStockSolver(arrCopy, buy, sell , max);
			
			buy = rcvdBuy;
			sell = rcvdSell;
		}
		
	}
	
	
	private static void bestTimeBuyAndSellStockSolver2 (int [] arr, int max[], ArrayList<Integer> buffer)
	{
		int [] arrCopy;
		int price = 0;
		int n = 0;
		int sell = 0;
		int buy = 0;
		ArrayList<Integer> copyBuffer;
		
		if (arr.length == 0) 
		{
			if (buffer.size() % 2 == 0) 
			{
				for (int i = 0; i < buffer.size(); i++) 
				{
					if (i % 2 == 0)
					{
						buy += buffer.get(i);
					}
					
					if (i % 2 == 1)
					{
						sell += buffer.get(i);
					}
				}
				price = sell - buy;
				
				if (price > max[0])
				{
					max[0] = price;
				}
			}
			return;
		}

		if (buffer == null)  
		{
			buffer = new ArrayList<Integer>();
		}

		for (int i = 0; i < arr.length; i++) 
		{	
			n = 0;
			
			arrCopy = new int[arr.length - i - 1];
			for (int k =  i + 1; k < arr.length; k++)
			{
				arrCopy[n++] = arr[k];
			}
			
			copyBuffer = new ArrayList<Integer>();
			
			for (Integer retVal: buffer)
			{
				copyBuffer.add( retVal);
			}
			
			if (copyBuffer.size() % 2 == 0) // buy stock  
			{
				copyBuffer.add(arr[i]);
			}
			
			else if (copyBuffer.size() % 2 == 1)  // sell stock
			{
				copyBuffer.add(arr[i]);
			}
			
			bestTimeBuyAndSellStockSolver2(arrCopy, max, copyBuffer);
		}
	}
	
	private static void bestTimeBuyAndSellStockSolver3 (int [] arr, int transaction, int max[], ArrayList<Integer> buffer)
	{
		int [] arrCopy;
		int price = 0;
		int n = 0;
		int sell = 0;
		int buy = 0;
		ArrayList<Integer> copyBuffer;
		
		
		if (buffer == null)
		{
			buffer = new ArrayList<Integer>();
		}
		
		if ( (arr.length == 0) || (buffer.size() == transaction * 2) ) 
		{
			if (buffer.size() % 2 == 0) 
			{
				for (int i = 0; i < buffer.size(); i++) 
				{
					if (i % 2 == 0)
					{
						buy += buffer.get(i);
					}
					
					if (i % 2 == 1)
					{
						sell += buffer.get(i);
					}
				}
				price = sell - buy;
				
				if (price > max[0])
				{
					max[0] = price;
				}
			}
			return;
		}

		for (int i = 0; i < arr.length; i++) 
		{	
			n = 0;
			
			arrCopy = new int[arr.length - i - 1];
			for (int k =  i + 1; k < arr.length; k++)
			{
				arrCopy[n++] = arr[k];
			}
			
			
			
			copyBuffer = new ArrayList<Integer>();
			
			for (Integer retVal: buffer)
			{
				copyBuffer.add( retVal);
			}
			
			if (copyBuffer.size() % 2 == 0) // buy stock  
			{
				copyBuffer.add(arr[i]);
			}
			
			else if (copyBuffer.size() % 2 == 1)  // sell stock
			{
				copyBuffer.add(arr[i]);
			}
			
			bestTimeBuyAndSellStockSolver3(arrCopy, transaction, max, copyBuffer);
		}
	}

	public static int bestTimeBuyAndSellStock(int[] arr)
	{
		int max[] = new int[1];
		bestTimeBuyAndSellStockSolver3(arr, 2, max, null);
		return max[0];
	}
	
	public static boolean areStringLooselyInterleaved(String s1, String s2, String s3)
	{
		String buffer = "";
		
		if (s1.length() + s2.length() != s3.length()) 
		{
			return false;
		}
		
		buffer = interleaveStrings(s1, s2);
		return buffer.compareTo(s3) == 0;
	}
	
	private static String interleaveStrings(String s1, String s2) 
	{
		String buffer;
		buffer = "";
		int pos[] = new int[2];

		while (buffer.length() != s1.length()+s2.length())
		{
			if (pos[0] < s1.length())
			{
				buffer += s1.charAt(pos[0]++);
			}
			
			if (pos[1] < s2.length())
			{
				buffer += s2.charAt(pos[1]++);
			}
		}
		return buffer;
	}
	
	public static ArrayList<String>  allLooselyInterleavedStrings (String s1, String s2)
	{
		ArrayList<String> mem = new ArrayList<String>();
		
		// concat
		mem.add(s1 + s2);
		mem.add(s2 + s1);
		
		// injection
		mem.add( s1.charAt(0) + s2 + s1.charAt(s1.length() - 1) ) ;
		mem.add( s2.charAt(0) + s1 + s2.charAt(s2.length() - 1) ) ;

		// interleave
		mem.add( interleaveStrings(s1, s2));
		mem.add( interleaveStrings(s2, s1));
		
		return mem;
	}
	
	private static boolean isPalindrome (String s)
	{
		int pos[] = {0, s.length() - 1};
		
		while (pos[0] <= pos[1]) 
		{
			if (s.charAt(pos[0]++) != s.charAt(pos[1]--) )
			{
				return false;
			}
		}
		return true;
	}
	
	public static int makeStringPalindrome (String s)
	{
		String buffer;
		if (isPalindrome(s))
		{
			return -1;
		}
		
		for (int i = 0; i < s.length(); i++) 
		{
			buffer = "";
			for (int k = 0; k < s.length(); k++) 
			{
				if (k == i) 
				{
					continue;
				}
				buffer += s.charAt(k);
			}
			
			if (isPalindrome(buffer))
			{
				return i;
			}
		}
		
		return -1;
	}
	
	public static String makeStringPalindomeAdd (String s)
	{
		String buffer;

		s.toLowerCase();
		
		for (int i = 0; i < s.length(); i++) 
		{
			for (char c = 'a'; c <= 'z'; c++ ) 
			{
				buffer = "";
				for (int k = 0; k < s.length(); k++) 
				{
					if (k == i) 
					{
						buffer += c;
					}
					
					buffer += s.charAt(k);
				}

				if (isPalindrome(buffer)) 
				{
					return "" + c;
				}
			}
		}
		
		return "";
	}
	
	
	public static String stringEncode (String s) 
	{
		char c;
		int count = 0;
		String result = "";
		
		for (int i = 0; i < s.length(); i++) 
		{
			c = s.charAt(i);
			
			if ( i + 1 >= s.length() ) // discontinuity
			{
				result += c  + String.valueOf(count + 1) ;
				count= 0;
			}
			
			if (count != 0)
			{
				if (c != s.charAt(i - 1) )  // discontinuity
				{
					result += s.charAt(i - 1) + String.valueOf(count) ;
					count= 0;
				}
			}
			count++;
		}
		
		return result;
	}
	
	public static String stringDecode (String s) 
	{
		String result = "";
		char c;
		int count; 
		
		for (int i = 0; i < s.length(); i +=2 ) 
		{
			c = s.charAt(i);
			count = Integer.valueOf(   s.charAt(i  + 1) + "");
			do
			{
				result += c;
			}
			while (--count > 0);
		}
		
		return result;
	}
	
}
