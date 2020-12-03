package algo;
import java.math.*;
import java.util.*;
import java.util.Map.Entry;

public class Chapter4 {
	
	static String removeBlank (String str) 
	{
		String s = "";
		
		for (String retVal: str.split(" "))
		{
			s += retVal;
		}
		return s;
	}
	
	static Integer getDigits (String str) 
	{
		String s = "";
		
		for (String retVal: str.split("")) 
		{
			if ( retVal.codePointAt(0) >= 48 && retVal.codePointAt(0) <= 57  )  // is number !
			{
				s += retVal;
			}
		}
		return Integer.valueOf(s);
	}
	
	static String acronyms(String str)
	{
		String s = "";
		for (String retVal: str.split(" "))
		{
			if ( Character.isLetter(retVal.codePointAt(0)))
			{
				s += Character.toUpperCase( retVal.charAt(0) );
			}
		}
		return s;
	}
	
	static int countNonSpaces (String str) 
	{
		int count = 0;
		
		for (String retVal: str.split("")) 
		{
			if (retVal.codePointAt(0) != 0x20)
			{
				count++;
			}
		}
		return count;
	}
	
	static String removeShorterString (String str, int len) 
	{
		String s = "";
		for (String retVal: str.split(" ")) 
		{
			if (retVal.length() >= len) 
			{
				s += retVal + " ";
			}
		}
		return s;
	}
	
	static String reverseString(String  str)
	{
		String s ="";
		int left, right;
		
		left =  (int )Math.ceil(str.length() / 2 ) - 1 ; 
		right = left + 1;

		while (true) 
		{				
			if (left >= 0) 
			{
				s += str.charAt( left);				
				left--;
			}

			if (right < str.length()) 
			{
				s = str.charAt(right) + s;
				right++;
			}

			if (left < 0 && right >= str.length()) 
			{
				break;
			}
		}
		return s;
	}
	
	static void removeEvenString(ArrayList<String>  collection)
	{
		for ( int i = 0; i < collection.size(); ) 
		{
			if ((collection.get(i).length() % 2) == 0) // even ! 
			{
				collection.remove(i);
			}
			else 
			{
				i++;
			}
		}
	}
	
	static String integerToRomanNumeral (int number)
	{
		String s = "";
		int[] sel = new int[2];
		Hashtable< Integer, String> table = new Hashtable<Integer,String >();
		
		//set table
		table.put( 0	,"");
		table.put( 1	,"I");
		table.put( 5	,"V");
		table.put( 10	,"X");
		table.put( 50	,"L");
		table.put( 100	,"C");
		table.put( 500	,"D");
		table.put( 1000	,"M"); 
		
		while (number > 0)
		{

			switch( number )
			// fall through 
			{

			default:

			case 1000:
				
				if (number >= 900 && number <= 1000)  // two char mode  [900 - 1000]
				{
					sel[1] = 100;
				}
				
				if (number >= 1000 || sel[1]  == 100) 
				{
					sel[0]  = 1000;
					break;
				}
				
			case 500:
				
				if (number >= 400 && number <= 500)  // two char mode [400 - 500]
				{
					sel[1] = 100;
				}
				
				if (number >= 500 || sel[1] == 100) 
				{
					sel[0]  = 500;
					break;
				}
			case 100:
				
				if (number >= 90 && number <= 100)  // two char mode  [90 - 100]
				{
					sel[1] = 10;
				}
				
				if (number >= 100 || sel[1] == 10) 
				{
					sel[0]  = 100;
					break;
				}
			case 50:
				
				if (number >= 40 && number <= 50)  // two char mode   [40 - 50]
				{
					sel[1] = 10;
				}
				
				if (number >= 50 || sel[1] == 10) 
				{
					sel[0]  = 50;
					break;
				}
				
			case 10:
				
				if (number >= 9 && number <= 10)  // two char mode  [9 - 10]
				{
					sel[1] = 1;
				}
				
				if (number >= 10 || sel[1] == 1) 
				{
					sel[0]  = 10;
					break;
				}
				
			case 5:
				
				if (number >= 4 && number <= 5)  // two char mode [4 - 5]
				{
					sel[1] = 1;
				}
				
				if (number >= 5 || sel[1] == 1) 
				{
					sel[0]  = 5;
					break;
				}
				
			case 1:
				
				if (number >= 1) 
				{
					sel[0]  = 1;
				}		
			}
		
			number -= (sel[0]  - sel[1]);
			s += table.get(sel[1]) + table.get(sel[0] );
			sel[0] = sel[1] = 0;
		}
		
		return s;
	}
	
	static int romanNumeralToInteger(String romanNumeral)
	{
		int result = 0;
		Hashtable< Character, Integer> table = new Hashtable< Character, Integer>();
		int[] sel = new int[2];
		int i = 0;
		
		//set table
		table.put( 	'I', 1		);
		table.put( 	'V', 5		);
		table.put( 	'X', 10		);
		table.put( 	'L', 50		);
		table.put( 	'C', 100	);
		table.put( 	'D', 500	);
		table.put( 	'M', 1000	); 
		
		while (i < romanNumeral.length())
		{
			sel[0] = table.get(romanNumeral.charAt(i)) ;
			
			if (i + 1 < romanNumeral.length())
			{
				sel[1] = table.get(romanNumeral.charAt(i + 1));
			}
			
			if (sel[0] < sel[1]) 
			{
				i += 2;
				result += sel[1] - sel[0];
			}
			else 
			{
				result += sel[0];
				i++;
			}
		}
		
		return result;
	}
	
	static boolean parensValid(String str) 
	{
		String s = "";
		int counter = 0;
		
		for (String retVal: str.split("") ) 
		{
			if (retVal.charAt(0) == '(') 
			{
				counter++;
			}
			
			if (retVal.charAt(0) == ')') 
			{
				if (counter == 0) 
				{
					return false;
				}
				counter--;
			}
		}
		return counter == 0;
	}
	
	static boolean bracesValid (String str) 
	{
		Hashtable<Character, Character> table = new Hashtable<Character, Character>();
		ArrayList<Character> array = new ArrayList<Character>(); // front = back of list 
		String openBraces = "([{";
		Character c;
		
		table.put(')', '(');
		table.put('}', '{');
		table.put(']', '[');
			
		for (String retVal: str.split("")) 
		{
			c = retVal.charAt(0);
			
			if ( openBraces.indexOf(c) != -1) // open brace
			{
				array.add(0, c);
			}

			if (table.containsKey(c)) // close brace
			{

				if (array.size() == 0) // array empty!
				{
					return false;
				}
				if (table.get(c) != array.get(0)) // not a match!
				{
					return false;
				}
				
				array.remove(0);
			}
		}
		return array.size() == 0; // buffer must be empty 
	}
	
	/* strict palindrome */
	static boolean isPalindrome (String str)   
	{
		int halfSize = str.length() / 2;
		
		for (int i = 0; i < halfSize; i++) 
		{
			if (str.charAt(i) != str.charAt(  str.length() - 1 - i) )
			{
				return false;
			}
		}
		return true;
	}
	
	/*  palindrome evaluates numbers and alphabets  */
	static boolean isAlphaNumericPalindrome (String str)   
	{
		Character c0, c1;
		boolean[] isAlphaNumericChar = new boolean[2];
		int[] index = {0, str.length() - 1};
		
		while ( index[0] <= index[1]) 
		{
			c0 = str.charAt(index[0]);
			c1 = str.charAt(index[1]);
			isAlphaNumericChar[0] = Character.isAlphabetic(c0) || Character.isDigit(c0);
			isAlphaNumericChar[1] = Character.isAlphabetic(c1) || Character.isDigit(c1);
			
			if (isAlphaNumericChar[1] && isAlphaNumericChar[0] ) // headptr and tailptr are alpha numeric 
			{
				if (c0 != c1) 
				{
					return false;
				}
			}
			
			if (!isAlphaNumericChar[0])
			{
				index[0]++;
				continue;
			}
			
			if (!isAlphaNumericChar[1])
			{
				index[1]--;
				continue;
			}
			
			index[0]++;
			index[1]--;
		}
		
	
		return true;
	}
	
	static String longestPalindrome(String str) 
	{
		String palindrome = "";
		String subs;
		int[] index = new int[2];
		
		for (int i = 0; i < str.length(); i++)
		{
			index[0] = i;
			index[1] = str.length() - 1;

			while ( index[0] <= index[1]) 
			{
				subs = str.substring(index[0], index[1] + 1);

				if ( subs.charAt(0) == subs.charAt(subs.length() - 1) ) // possible palindrome  x[0] = x[end]
				{
					if (subs.length() > palindrome.length()) 
					{
						if (isPalindrome(subs))  // try isAlphaNumericPalindrome() !
						{
							palindrome = str.substring(index[0], index[1] + 1);							
							break;						
						}
					}
				}
				index[1]--;					
			}
		}
		
		return palindrome;
	}
	
	static String dGetsJiggy(String name) 
	{
		String s = "";
		Character c, cend;
		String msg = "to the";
		
		if (name.length() <= 0) 
		{
			return "";
		}
		
		c = Character.toUpperCase(name.charAt(0));
		
		if (name.length() == 1) 
		{
			return  msg + " " + c + "!";
		}
		
		if (name.length() > 1) 
		{
			return Character.toUpperCase(name.charAt(1)) +  name.substring(2, name.length()) + " "  + msg + " " + c + "!";
		}
		
		return "";
	}

	static boolean isWordAlphabetical (String str) 
	{
		int index = 0;
		Character c;
		Character[] data = new Character[2];

		while (index < str.length())
		{
			c = str.charAt(index);
			
			if ( Character.isAlphabetic(c) )
			{
				data[0] = data[1];
				data[1] = c;
			}
			
			if (data[0] !=null && data[1] !=null) 
			{
				if (data[0] > data[1]) 
				{
					return false;
				}
			}
			
			index++;					
		}
		return true;
	}
	
	static String commonSuffix (ArrayList<String> words) 
	{
		
		String  curr, next, result ="";
		int lenFromEnd = 0; 
		boolean done = false;
		
		if (words.size() == 0) 
		{
			return "";
		}
		
		while (!done) 
		{
			lenFromEnd++;

			for (int i = 0; i < words.size() - 1; i++)  
			{
				curr = words.get(i);
				next = words.get(i + 1);
				
				if ( !(lenFromEnd <= curr.length() && lenFromEnd <= next.length() ) ) // window greater than word length  
				{
					done = true;
				}
				else if ( curr.charAt(curr.length()  - lenFromEnd) !=  next.charAt(next.length()  - lenFromEnd) ) // adjacent elements don't match
				{
					done = true;
				}
				
				if (done) 
				{
					lenFromEnd--; // decr 1 step from error position 
					break;
				}
			}
		}
		
		if (lenFromEnd > 0) 
		{
			curr = words.get(0);
			result = curr.substring(curr.length() - lenFromEnd, curr.length());
		}
		
		return result;
	}
	
	static String bookIndex (int[] numbers)
	{
		String s = "";
		Integer start = null, curr, end = null, prev;
		
		if (numbers.length == 0) 
		{
			return s;
		}
		
		prev = start = (numbers[0]);
				
		for (int i = 1; i < numbers.length; i++) 
		{
			curr = numbers[i];
			
			if (prev + 1 != curr)  // discontinuity
			{
				if (s.length() != 0) 
				{
					s += ", ";
				}
				
				if (start != null) 
				{
					s += String.valueOf(start);
				}
				
				if (end != null) 
				{
					s +=  '-' + String.valueOf(end) ;
				}	
				
				// replace start
				start = curr; 
				end = null;
			}
			
			else 
			{
				end = curr;
			}
			prev = curr;
		}
		
		if (start != null) 
		{
			s += ", ";
			s += String.valueOf(start);
		}
	
		if (end != null) 
		{
			s +=  '-' + String.valueOf(end) ;
		}	
		
		return s;
	}
	
	public static void main (String agrs[]) 
	{
		int[] array = {1, 13, 14, 15, 37, 38, 70};
		Object s = bookIndex(array);
		System.out.print(s);
	}
}
