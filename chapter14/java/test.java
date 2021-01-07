package algo;
import java.util.ArrayList;

import algo.Chapter14.*;


public class Test {
	
	public static void HashTest()
	{
		Hash hash = new Hash(10);
		System.out.println(" is empty --> " + hash.isEmpty());
		System.out.println();

		hash.add("henry", 100);
		hash.add("shawn", 73470);
		hash.add("henry", 73470);
		hash.add("abcd", 73470);

		
		System.out.print("Find(\"henry\"): ") ;
		for (int retVal: hash.find("henry"))
		{
			System.out.print(retVal + ",");
		}
		System.out.println();
		System.out.println();
		
		System.out.println(" is empty --> " + hash.isEmpty());
		System.out.println();
		

		System.out.println("Hash Tree: ");
		hash.displayHashTree();
		System.out.println();
		
		ArrayList<Integer> valuesRemovedCollection  = hash.remove("henry");
		for (int retVal: valuesRemovedCollection)
		{
			System.out.println("removed from hash tree " + retVal );
		}
		
		System.out.println("load factor: " + hash.loadFactor());
		
		hash.grow();
		System.out.println();

		System.out.println("Hash Tree: ");
		hash.displayHashTree();
		System.out.println();
		
		
	}
	
	public static void main(String args[])
	{
		HashTest();	
	}

}  
