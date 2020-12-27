package algo;
import java.util.ArrayList;

import algo.Chapter11.*;

public class Test {
	
	public static void binaryTreeTest()
	{
		BST tree = new BST();
		
		tree.add(10);
		tree.add(20);
		tree.add(1);
		tree.add(0);
		tree.add(50);
		tree.add(25);
		tree.add(15);
		tree.add(200);
		tree.add(900);
		tree.add(23);
		tree.add(0);
		tree.add(10);

		System.out.println("contains(100) " + tree.contains(100));
		System.out.println("contains(-1) " + tree.contains(-1));
		System.out.println("contains(10) " + tree.contains(10));
		System.out.println("contains(20) " + tree.contains(20));
		System.out.println("contains(0) " + tree.contains(0));

		try {
			System.out.println("min() " + tree.min());
		} catch (BSTException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			System.out.println("max() " + tree.max());
		} catch (BSTException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("size() " + tree.size());
		System.out.println("isEmpty() " + tree.isEmpty());
		
		System.out.println("height() " + tree.height());

		System.out.println("isBalanced() " + tree.isBalanced());
		
		int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		BST testBST = Chapter11.arrayToBST(arr);
		
		System.out.println(  "root = " + testBST.root.getValue() + " "  + "arrayToBST( {1, 2, 3, 4, 5, 6, 7, 8, 9})  -- is balanced " + testBST.isBalanced() ) ;
		System.out.println(   "" + Chapter11.closestCommonAncestor(tree, 23, 900 ) ) ;
		
		Chapter11.preOrder(tree);
		Chapter11.postOrder(tree);
		
		ArrayList<Integer> rcvdArr = Chapter11.bst2Arr(tree);
		for (Integer retVal: rcvdArr)
		{
			System.out.print("[" + retVal +  "]");
		}
		
		System.out.println("");
		
		System.out.println("minheight() " + tree.minheight());
		
		Chapter11.bstPreOrderNoRecursion(tree);
		
		System.out.println("remove(10) " + tree.remove(10));
		System.out.println("remove(0) " + tree.remove(0));
//		System.out.println("remove(20) " + tree.remove(20));
//		System.out.println("remove(20) " + tree.remove(20));
		Chapter11.displayInOrder(tree.root); 		System.out.println("");

		System.out.println("isValid() " + tree.isValid());
		rcvdArr = Chapter11.traverseBSTReverseOrder(tree);
		for (Integer retVal: rcvdArr)
		{
			System.out.print("[" + retVal +  "]");
		}
		System.out.println("");
		System.out.println(" valBefore " + tree.valBefore(-1));
		System.out.println(" valAfter " + tree.valAfter(201)); 
		System.out.println(" closestValue " + tree.closestValue(12)); 
		System.out.println(" traverseBSTReverseOrder(tree, 11) " + Chapter11.traverseBSTReverseOrder(tree) ); 
		System.out.println(" traverseBSTReverseOrder(tree, 11) " + Chapter11.treePathContainsSum(tree, 11) ); 
		
		ArrayList<ArrayList<Integer>>  collectionOfArrays = Chapter11.treePathContainsSum2nd(tree, 11);
		for (ArrayList<Integer> collection: collectionOfArrays)
		{
			for (Integer retVal: collection) 
			{
				System.out.print("[" + retVal +  "]");
			}
			System.out.println("");
		}
		
		rcvdArr = Chapter11.sumOfBSTRootLeafNumbers(tree);
		for (Integer retVal: rcvdArr)
		{
			System.out.print("[" + retVal +  "]");
		}
		System.out.println("");

		rcvdArr = Chapter11.leftSideBinaryTree(tree);
		for (Integer retVal: rcvdArr)
		{
			System.out.print("[" + retVal +  "]");
		}
	}
	
	public static void main(String args[])
	{
		binaryTreeTest();
	}
	
}  
