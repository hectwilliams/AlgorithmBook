package algo;
import algo.Chapter16.*;
import algo.Chapter15.*;
import algo.Chapter11.*;
import java.util.ArrayList;


public class Test 
{
	public static void TrieInsertionTest ()
	{
		TrieSet trie = new TrieSet();
	
		System.out.println("add as " + trie.insert("as"));
		System.out.println("add as " + trie.insert("as"));
		System.out.println("contains as " + trie.contains("as"));
		System.out.println("contains ducks " + trie.contains("ducks"));
		System.out.println("contains facts " + trie.contains("facts"));
		
		System.out.println("add sampson " + trie.insert("sampson"));
		System.out.println("add todd " + trie.insert("todd"));
		System.out.println("add todd " + trie.insert("apple"));
		System.out.println("add todd " + trie.insert("apple"));
		System.out.println("add todd " + trie.insert("aae"));

		System.out.println("first " + trie.first() );
		System.out.println("last " + trie.last() );

	}
	
	public static void TrieRemovalTest ()
