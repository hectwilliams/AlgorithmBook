package algo.chapter10;
import java.util.ArrayList;
import java.util.Random;



public class test {
	
	private static void stringToWordTest()
	{
		String str = "Life is  c    --into a drill!";
		String[] collection = chapter10.stringToArray(str);
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
		String rcvd = chapter10.longestWord(str);
		System.out.println("longest world " + rcvd );
	}
	
	private static void reverseWordOrderTest()
	{
		String str = "Life is  c    into a drill!";
		String rcvd = chapter10.reverseWordOrder(str);
		System.out.println("original message " + str );
		System.out.println("reversed message " + rcvd );
	}
	
	private static void uniqueWordsTest()
	{
		String str = "Sing! Sing a song; sing out loud; sing out string.";
		ArrayList<String> rcvd = chapter10.uniqueWordsTest(str);
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
		String result = chapter10.rotateString(str, shiftBy);
		System.out.println(str + " shifted" +  " by " + shiftBy + "  =   " + result);
	}
	
	public static void censorTest() 
	{
		String test = "Snap crackle pop nincompoop!";
		String list[] = {
			"crack",
			"poop"
		};
		String result = chapter10.censor(test, list);
		System.out.print(result);
	}
	
	public static void isRotationTest() 
	{
		String s1, s2;
		
		s1 = "hello";
		s2 = "lohel";
		System.out.println("valid "  + chapter10.ionlsRotat(s1,s2)); // true
		s2 = "lohhl";
		System.out.println("valid "  + chapter10.ionlsRotat(s1,s2)); // false
	}
	
	public static void badCharactersTest ()
	{
		String s1, bad;
		s1 = "hello";
		bad = "aoe";
		System.out.println("valid "  + chapter10.badCharacters(s1,bad));
	}
	
	public static void geneticMarkerTest ()
	{
		String[] array = { "??wn", "lawn", "dawn"};
		String s = "dodo";
		System.out.println("valid "  + chapter10.geneticMarker(s, array));
	}
	
	public static void optimalSequenceTest()
	{
		String[] array = {"EA?K", "?RX?", "GAG?"};
//		String[] array = {"?F??", "W??S", "??X?"};
//		String[] array = {"?UD", "FI?", "A?E"};

		ArrayList<String[]> collection = chapter10.optimalSequence(array);
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
	
	public static void dedupeTest()
	{
		String str = "Snaps! crackles pop!";
		System.out.println( chapter10.dedupe(str));
	}
	
	public static void firstUniqueLetterTest()
	{
		String str = "empathetic monarch meets primo stinker";
		System.out.println( chapter10.firstUniqueLetter(str));
	}
	
	public static void uniqueLettersTest()
	{
		String str = "Snap! Crackle! Poop!";
		System.out.println( chapter10.uniqueLetters(str));
	}
	
	public static void numToStringTest()
	{
		double num = 11.111011;
		System.out.println( "numToStringTest( 11.111011) = " + chapter10.numToString(num));
	}
	
	public static void numToTextTest () 
	{
		double number = 11.111011;
		System.out.println( "numToStringTest(40213) = " + chapter10.numToText(number));
	}
	
	public static void isPermutationTest ()
	{
		String s1, s2;
		s1 = "mister";
		s2 = "stimer";
		System.out.println( "isPermutation(mister, stimer) = " + chapter10.isPermutation(s1, s2));
	}
	
	public static void isPangramTest ()
	{
		String s = "How quickly daft jumping zebras vex!";
		System.out.println( "isPangram(s) = " + chapter10.isPangram(s));
	}
	
	public static void isPerfectPangramTest ()
	{
		String s = "Playing jazz vibe chords quickly excites my wife.";
		System.out.println( "perfectPangram(s) = " + chapter10.perfectPangram(s));
		s = "Mr.Jock, TV quiz PhD, bags few lynx.";
		System.out.println( "perfectPangram(s) = " + chapter10.perfectPangram(s));
	}
	
	public static void allPermutationsTest() 
	{
		String s = "team";
		String[] collection = chapter10.allPermutations(s);
		for (String ret: collection)
		{
			System.out.println(ret);
		}
	}
	
	public static void bestTimeToBuySellStockTest ()
	{
		int [] array = {6, 4, 6, 5, 9, 7, 6, 12, 2, 6, 11, 2, 4};
		System.out.println( chapter10.bestTimeBuyAndSellStock(array) ) ;
	}
	
	public static void areStringLooselyInterleavedTest ()
	{
		String s1 = "dne";
		String s2 = "ail";
		String s3 = "daniel";
		System.out.println( "areStringLooselyInterleaved(dne, ail, daniel) =   " + chapter10.areStringLooselyInterleaved(s1, s2, s3));
	}
	
	public static void allLooselyInterleavedStringsTest ()
	{
		String s1 = "ab";
		String s2 = "yz";
		ArrayList<String> collection = chapter10.allLooselyInterleavedStrings(s1, s2);
		for (String ret: collection) 
		{
			System.out.println(ret);
		}
	}
	
	public static void makeStringPalindromeTest() 
	{
		String s;
		s = "bene";
		System.out.println("makeStringPalindrome(bene)  " + chapter10.makeStringPalindrome(s));
		s = "dude";
		System.out.println("makeStringPalindrome(dude)  " + chapter10.makeStringPalindrome(s));
		s = "bub";
		System.out.println("makeStringPalindrome(bub)  " + chapter10.makeStringPalindrome(s));
	}
	
	public static void makeStringPalindomeAddTest() 
	{
		String s = "tutu";
		System.out.println("makeStringPalindomeAdd(tutu)  " + chapter10.makeStringPalindomeAdd(s));	
	}
	
	public static void stringEncodeTest () 
	{
		String s = "aaaabbcddd";
		System.out.println("stringEncode(aaaabbcddd) " + chapter10.stringEncode(s));
	}
	
	public static void stringDecodeTest () 
	{
		String s = "a4b2c1d3";
		System.out.println("stringDecode(a4b2c1d3) " + chapter10.stringDecode(s));
	}
	
	public static void main(String args[])
	{
	}
}  
