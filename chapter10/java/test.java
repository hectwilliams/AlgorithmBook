package algo;
import java.util.ArrayList;

import algo.Chapter10.*;


public class Test {
	
	private static void stringToWordTest()
	{
		String str = "Life is  c    --into a drill!";
		String[] collection = Chapter10.stringToArray(str);
		System.out.print("[");
		for (String retStr: collection) 
		{
			System.out.print(retStr + ",");
		}
		System.out.print("]");
	}
	
	private static void longestWordTest()
	{
		String str = "Life is  c    --into a drill!";
		String rcvd = Chapter10.longestWord(str);
		System.out.println("longest world " + rcvd );
	}
	
	private static void reverseWordOrderTest()
	{
		String str = "Life is  c    into a drill!";
		String rcvd = Chapter10.reverseWordOrder(str);
		System.out.println("original message " + str );
		System.out.println("reversed message " + rcvd );
	}
	
	private static void uniqueWordsTest()
	{
		String str = "Sing! Sing a song; sing out loud; sing out string.";
		ArrayList<String> rcvd = Chapter10.uniqueWordsTest(str);
		System.out.print("[");

		for (String retStr: rcvd) 
		{
			System.out.print(retStr + ",");
		}
		System.out.print("]");
	}
	
	private static void rotateStringTest()
	{
		String str = "Boris Godunov";
		int shiftBy = 5;
		String result = Chapter10.rotateString(str, shiftBy);
		System.out.println(str + " shifted" +  " by " + shiftBy + "  =   " + result);
	}
	
	public static void censorTest() 
	{
		String test = "Snap crackle pop nincompoop!";
		String list[] = {
			"crack",
			"poop"
		};
		String result = Chapter10.censor(test, list);
		System.out.print(result);
	}
	
	public static void isRotationTest() 
	{
		String s1, s2;
		
		s1 = "hello";
		s2 = "lohel";
		System.out.println("valid "  + Chapter10.ionlsRotat(s1,s2)); // true
		s2 = "lohhl";
		System.out.println("valid "  + Chapter10.ionlsRotat(s1,s2)); // false
	}
	
	public static void badCharactersTest ()
	{
		String s1, bad;
		s1 = "hello";
		bad = "aoe";
		System.out.println("valid "  + Chapter10.badCharacters(s1,bad));
	}
	
	public static void geneticMarkerTest ()
	{
		String[] array = { "??wn", "lawn", "dawn"};
		String s = "dodo";
		System.out.println("valid "  + Chapter10.geneticMarker(s, array));
	}
	
	public static void optimalSequenceTest()
	{
		String[] array = {"EA?K", "?RX?", "GAG?"};
//		String[] array = {"?F??", "W??S", "??X?"};
//		String[] array = {"?UD", "FI?", "A?E"};

		ArrayList<String[]> collection = Chapter10.optimalSequence(array);
		boolean state = true;
		
		if (collection != null) 
		{
			for (String[] s: collection) 
			{
				System.out.print("[ ");

				for (String retStr: s) 
				{
					System.out.print(retStr + ",");
				}		
				System.out.println("] ");
				
				if (state) 
				{
					return;
				}
			}
		}
		
		if (collection.size() == 0) 
		{
			System.out.println("no valid sequence");

		}
	}
	
	public static void main(String args[])
	{
		optimalSequenceTest();
	}
}
