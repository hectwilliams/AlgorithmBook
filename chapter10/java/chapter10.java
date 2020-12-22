package algo;

import java.util.ArrayList;
import java.util.HashMap;

public class Chapter10 {

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
	
	public static void  optimalSequenceSolver (String[] strings, ArrayList<String[]> solCache, String [] buffer , int row, int col) // GEEZ THIS WAS TOUGH TO WRAP AROUND !
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
		optimalSequenceSolver(array, sols,null, 0, 0);
		return sols;
	}
	
}
