package algo;
import algo.Chapter15.*;
import algo.Chapter5.Node;
import algo.Chapter11.*;


public class Test 
{
	public static void smallestDifferenceTreeTest()
	{
		BST tree = new BST();
		int[] collection = {10, 3, 200, 202, 100, 103, 111};
		for (int retVal: collection)
		{
			tree.add(retVal);
		}
		System.out.println(" smallest difference " + Chapter15.smallestDifference(tree));
	}
	
	public static void smallestDifferenceSListTest()
	{
		Node SList = null, runner = null;
		int[] collection = {10, 3, 200, 202, 100, 103, 111};
		for (int retVal: collection)
		{
			
			if (SList == null)
			{
				runner = SList = new Node(retVal);
			}
			else 
			{
				runner = runner.next = new Node(retVal);
			}
		}
		System.out.println(" smallest difference " + Chapter15.smallestDifference(SList));
	}
	
	public static void closestValueTest()
	{
		BST tree = new BST();
		int[] collection = {10, 3, 200, 202, 100, 103, 111};
		for (int retVal: collection)
		{
			tree.add(retVal);
		}
		System.out.println(" closest value to 120 " + Chapter15.closestValue(tree, 120));
	}
	
	
	public static void partitionTest()
	{
		BST tree = new BST();
		BST retTree;
		int[] collection = {10, 3, 200, 202, 100, 103, 111};
		for (int retVal: collection)
		{
			tree.add(retVal);
		}
		
		retTree = tree.partitionAroundValue(120);
		
		Chapter11.displayInOrder(retTree.root);
		System.out.println();
		Chapter11.displayInOrder(tree.root);
	}
	
	public static void partitionEvenlyTest()
	{
		BST tree = new BST();
		BST retTree;
		int[] collection = {10, 3, 200, 202, 100, 103, 111};
		for (int retVal: collection)
		{
			tree.add(retVal);
		}
		
		retTree = Chapter15.partitionEvenly(tree);
		
		Chapter11.displayInOrder(retTree.root);
		System.out.println();
		Chapter11.displayInOrder(tree.root);
	}
	
	public static void reverseTest ()
	{
		BST tree = new BST();
		int[] collection = {10, 3, 200, 202, 100, 103, 111};
		for (int retVal: collection)
		{
			tree.add(retVal);
		}
		
		Chapter15.reverse(tree);
		
		// before
		
		/*
		 * 		  	       10 
		 *      		/      \
		 *             3      200 
		 *           /  \    /    \
		 *                  100   202    
		 *                    \
		 *                    103
		 *                      \ 
		 *                      111
		 * 
		 * 
		 * */
		
		// after 
		/*
		 * 		  	       10 
		 *      		/      \
		 *            200       3
		 *           /   \   
		 *         202    100  
		 *                /   
		 *              103
		 *               / 
		 *             111
		 * 
		 * 
		 * */
		Chapter11.displayInOrder(tree.root);
	}
	
	public static void KthLargestTest ()
	{
		BST tree = new BST();
		int[] collection = {10, 3, 200, 202, 100, 103, 111};
		for (int retVal: collection)
		{
			tree.add(retVal);
		}
		
		for (int i = 1; i < 10; i++)
		{
			System.out.println( i + " largest " + Chapter15.KthBiggest(tree , i));

		}
	}

	
	public static void main(String args[])
	{
		KthLargestTest();
			}

}  
