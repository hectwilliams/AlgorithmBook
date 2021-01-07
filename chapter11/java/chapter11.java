package algo;

import java.util.ArrayList;

public class Chapter11 
{
	public static class BTNode
	{
		public int val;
		public BTNode left;
		public BTNode right;
		private int count;
		
		BTNode(int value)
		{
			count = 1;
			val = value;
			left = right = null;
		}
		
		int getValue()
		{
			return val;
		}
		
	}
	
	public static void displayInOrder (BTNode node) // in order
	{
		
		if (node.left != null) 
		{
			displayInOrder(node.left);
		}
		
		for (int i = 0; i < node.count; i++) 
		{
			System.out.print ("[" + node.val  + " "+ "]");
		}
		
		if (node.right != null) 
		{
			displayInOrder(node.right);
		}
		
	}
	
	public static class BSTException extends Exception
	{
		BSTException()
		{
		}
		
		public static String nodeError()
		{
			return "nully node";
		}
	}
	
	public static  class BST
	{
		protected BTNode root;
		
		BST()
		{
			root = null;
		}
		
		
		public void add(int val)  // ordered multiset 
		{
			BTNode node;

			if (root != null) 
			{
				node = root;
				
				do 
				{
					if (val < node.val) 
					{
						if (node.left == null)   // new entry  
						{
							node = node.left = new BTNode(val);
						}
						else 
						{
							 if (node.left.val == val) // child multiset 
							 {
								 node.left.count++;
							 }
							node = node.left;
						}
					}
					
					else if (val >= node.val) 
					{
						
						if (node.val == val) // root multiset 
						{
							node.count++;
							return;
						}
						
						else if (node.right == null)  // new entry  
						{
							node = node.right = new BTNode(val);
						}
						else  
						{
							 if (node.right.val == val) // child multiset 
							 {
								 node.right.count++;
							 }
							node = node.right;
						}
					}
					
				}
				while (node.val != val);
			}
			
			if (root == null) 
			{
				root = new BTNode(val);
			}
		}
		
		public boolean contains (int val) 
		{
			BTNode node;
			
			if (root != null ) 
			{
				node = root;
				do 
				{
					if (val == node.val) 
					{
						return true;
					}
					
					if (val < node.val) 
					{
						node = node.left;
					}
					
					else if (val >= node.val) 
					{
						node = node.right;
					}
					
					
				}
				while (node != null);
			}
			
			return false;
		}
		
		public int min () throws BSTException
		{
			BTNode node;
			
			if (root != null) 
			{
				node = root;

				while (node.left == null && node.right == null); // stop at leaf 
				{
					node = node.left;
				}
				
				return node.val;
			}
			
			throw new BSTException();
			
		}
		
		public int max () throws BSTException
		{
			BTNode node;
			
			if (root != null) 
			{
				node = root;
				while (node.left == null && node.right == null); // stop at leaf 
				{
					node = node.right;
				}
				return node.val;
			}
			
			throw new BSTException();
		}
		
		private int sizeSolver (BTNode node) 
		{
			if (node == null)
			{
				return 0;
			}
			return 1 + sizeSolver(node.left) + sizeSolver(node.right);
		}
		
		public int size ()
		{
			return sizeSolver(root);
		}
		
		public boolean isEmpty() 
		{
			return root == null;
		}
		
		private int heightSolver (BTNode node)
		{
			int heightLeft, heightRight;
			
			heightLeft = heightRight = 0;
			
			if (node == null) 
			{
				return  0;
			}
			
			if (node.left != null)
			{
				heightLeft = 1 + heightSolver(node.left);
			}

			if (node.right != null)
			{
				heightRight = 1 + heightSolver(node.right);
			}
			
			if (heightLeft > heightRight) 
			{
				return heightLeft;
			}
			
			return heightRight;
		}

		public int height () 
		{
			return heightSolver(root);
		}
		
		private boolean isBalancedSolver (BTNode node)
		{
			if (node == null) 
			{
				return true;
			}
			
			 return Math.abs( heightSolver(node.left) - heightSolver(node.right)) <= 1;
		}

		public boolean isBalanced () 
		{
			return isBalancedSolver(root);
		}
		
		private int minheightSolver (BTNode node)
		{
			/*
			 * 
			 * use height of children to direct path of miniumum height 
			 * 
			 *  
			 * */
			
			int heightLeft, heightRight;
			
			if (node == null) 
			{
				return  0;
			}
			
			heightLeft = heightSolver(node.left);
			heightRight = heightSolver(node.right);
			
			// full subtree 
			
			if (node.left != null && node.right != null)
			{
				
				if (heightLeft < heightRight) 
				{
					return 1 + minheightSolver (node.left);
				}
				
				if ( heightRight < heightLeft)  
				{
					return 1 + minheightSolver (node.right);
				}
				
			}
			
			// sub tree with holes
			
			if (node.left == null && node.right != null)  
			{
				return 1 + minheightSolver(node.right);
			}
			
			if (node.right== null && node.left != null ) 
			{
				return 1 + minheightSolver(node.left);
			}
			
			// leaf subtree 

			return 0;

		}

		public int minheight () 
		{
			return minheightSolver(root);
		}
		
		public boolean remove (int val) 
		{
			BTNode node = root, parentOfNode = null, successor;
			
			if (root == null) 
			{
				return false;
			}
			
			do
			{

				if (val < node.val) 
				{
					if (node.left == null)
					{
						break;
					}
					parentOfNode = node;
					node = node.left;
				}
				else if (val > node.val) 
				{
					if (node.right == null)
					{
						break;
					}
					parentOfNode = node;
					node = node.right;
				}
				else if (val == node.val) 
				{
					// check dupes count 
					if (node.count > 1) 
					{
						node.count -= 1;
						return true;
					}
					
					if (node.left == null && node.right == null)  // leaf 
					{
						if (node == root) 
						{
							root = null;
						}
						else 
						{
							// replace target node with leaf
							if (parentOfNode.left == node) 
							{
								parentOfNode.left = null;
							}
							
							if (parentOfNode.right == node) 
							{
								parentOfNode.right = null;
							}
						}
					}
					
					else if (node.left == null ^ node.right == null) // single child 
					{
						// copy target's child attributes to node 
						if (node.left != null)
						{
							node.val = node.left.val;
							node.left = node.left.left;
							node.right = node.left.right;
						}
						
						else if (node.right != null) 
						{
							node.val = node.right.val;
							node.right = node.right.right;
							node.left = node.right.left; 
						}
					}
					
					else if (node.left != null && node.right != null) // full 
					{
						parentOfNode = node;
						successor = node.right;
						
						while (successor.left != null)
						{
							parentOfNode = successor;
							successor = successor.left;
						}
						
						// overwrite node's value
						node.val =  successor.val;
						
						// remove successor node 
						if (parentOfNode.left == successor) 
						{
							parentOfNode.left = null;
						}
						
						if (parentOfNode.right == successor) 
						{
							parentOfNode.right = null;
						}						
					}
					
					return true;
				}
			}
			while (node != null);
			
			return false;
		}
		
		public void removeAllSolver(BTNode node) 
		{
			if (node == null) 
			{
				return;
			}
			
			if (node.left != null)
			{
				removeAllSolver(node.left);
			}
			
			if (node.right!= null)
			{
				removeAllSolver(node.right);
			}
			
			node.left = null;
			node.right = null;
				
		}

		public void removeAll() 
		{
			// post order traversal / delete
			
			removeAllSolver(root);
			root = null;
		}
		
		public void addWithoutDupes(int val)  // ordered multiset 
		{
			BTNode node;

			if (root != null) 
			{
				node = root;
				
				do 
				{
					if (val < node.val) 
					{
						if (node.left == null)  
						{
							node = node.left = new BTNode(val);
						}
						else 
						{
							node = node.left;
						}
					}
					
					else if (val >= node.val) 
					{
						
						if (node.right == null) 
						{
							node = node.right = new BTNode(val);
						}
						else  
						{
							node = node.right;
						}
					}
					
				}
				while (node.val != val);
			}
			
			if (root == null) 
			{
				root = new BTNode(val);
			}
		}
		
		public boolean isValidSolver (BTNode node)
		{
			boolean isLeftChildValid, isRightChildValid;
			
			if (node == null) 
			{
				return true;
			}
			
			isLeftChildValid = isRightChildValid = true;
			
			if (node.left != null) 
			{
				if (node.left.val >= node.val )
				{
					return false;
				}
				isLeftChildValid = isValidSolver(node.left);
			}
			
			if (node.right != null) 
			{
				if (node.right.val < node.val) 
				{
					return false;
				}
				isRightChildValid = isValidSolver(node.right);
			}
			
			return isLeftChildValid && isLeftChildValid;
		}

		public boolean isValid ()
		{
			return isValidSolver(root);
		}
		
		public Integer valBefore(int value) 
		{
			BTNode node, parentOfNode;
			
			if (root == null) 
			{
				return null;
			}
			
			node = root;
 			parentOfNode = null;
			
			while (node != null )
			{
				if (node.val == value) 
				{
					if (parentOfNode == null)
					{
						return null;
					}
					
					if (parentOfNode != null) 
					{
						return parentOfNode.val;
					}
				}
				
				else if (value < node.val)
				{
					if (node.left != null) 
					{
						parentOfNode = node;
						
						if (value < node.val && value > node.left.val) 
						{
							return node.val;
						}
						node = node.left;
					}
					
					if (node.left == null) 
					{
						return node.val;
					}
				} 
				
				else if (value > node.val) 
				{
					if (node.right != null) 
					{
						parentOfNode = node;
						if (value > node.val && value < node.right.val)
						{
							return node.val;
						}
						node = node.right;
					}
					
					if (node.right == null) 
					{
						return node.val;
					}
				}
				
				
			}
		
			
			return null;
		}
		
		public Integer valAfter(int value) 
		{
			BTNode node, parentOfNode;
			
			if (root == null) 
			{
				return null;
			}
			
			node = root;
			parentOfNode = null;
			
			while ( node != null )
			{
				if (node.val  == value) 
				{
					if (node.left != null) 
					{
						return node.left.val;
					}
					
					if (node.right != null) 
					{
						return node.right.val;
					}
					
					return null;
				}
				
				if (value < node.val)
				{
					if (node.left != null) 
					{
						if (value < node.val && value > node.left.val) 
						{
							return node.left.val;
						}
						
						node = node.left; 
					}
				}
				
				else if (value > node.val) 
				{
					if (node.right != null) 
					{
						if (value > node.val &&  value < node.right.val) 
						{
							return node.right.val;
						}
						{
							node = node.right;
						}
					}
				}
			}
			
			if (parentOfNode == null) 
			{
				return null;
			}
			
			return parentOfNode.val;
		}
		
		public Integer closestValue(int value) 
		{
			BTNode node;
			if (root == null) 
			{
				return null;
			}
			
			node = root;
			
			while (node != null) 
			{
				if (node.val == value) 
				{
					return node.val;
				}
				
				else if (value < node.val) 
				{
					if (node.left == null) 
					{
						return node.val;
					}
					
					if (node.left != null) 
					{
						if ( Math.abs(node.val - value)  < Math.abs(value - node.left.val))  // distance compare 
						{
							return node.val;
						}
						
						node = node.left ;
					}
				}
				
				else if (value > node.val) 
				{
					if (node.right == null) 
					{
						return node.val;
					}
					
					if (node.right != null) 
					{
						if (Math.abs(node.val - value) < Math.abs(value - node.right.val) ) 
						{
							return node.val;
						}
						
						
						
						node = node.right;
					}
				}
			}
			
			return null;
			
		}
		
	}
	
	public static BST arrayToBST (int [] array) 
	{
		BST tree = new BST();
		int mid;
		
		if (array.length == 0 ) 
		{
			return tree;
		}
		
		mid = array.length / 2;
		
		for (int i = mid; i < array.length; i++) 
		{
			tree.add(array[i]);
		}
		
		for (int i = mid - 1; i >= 0; i--) 
		{
			tree.add(array[i]);
		}
		
		return tree;
	}
	
	public static int closestCommonAncestor(BST tree, int a, int b)
	{
		BTNode node = tree.root;
		
		while ( (a < node.getValue() && b < node.getValue()) || (a > node.getValue()  && b > node.getValue()) )
		{	
			if (a < node.getValue()) 
			{
				node = node.left;
			}
			else if (a > node.getValue()) 
			{
				node = node.right;
			}	
		}
		
		return node.val;
	}
	
	public static void preOrderSolver (BTNode node) 
	{
		if (node == null) 
		{
			return;
		}
		
		for (int i = 0; i < node.count; i++) 
		{
			System.out.print("[" + node.val +  "]");
		}
		
		if (node.left != null) 
		{
			preOrderSolver(node.left);
		}
		
		if (node.right != null) 
		{
			preOrderSolver(node.right);
		}
		
		
	}

	public static void preOrder (BST tree) 
	{
		preOrderSolver(tree.root);
		System.out.println("");
	}
	
	public static void postOrderSolver (BTNode node) 
	{
		if (node == null) 
		{
			return;
		}
		
		if (node.left != null) 
		{
			preOrderSolver(node.left);
		}
		
		if (node.right != null) 
		{
			preOrderSolver(node.right);
		}
		for (int i = 0; i < node.count; i++) 
		{
			System.out.print("[" + node.val +  "]");
		}
	}

	public static void postOrder (BST tree) 
	{
		postOrderSolver(tree.root);
		System.out.println("");
	}
	
	public static void bst2ArrSolver(BTNode node, int mode, ArrayList<Integer> cache)
	{
		
		if (mode == 1) 
		{
			cache.add(node.val);
		}
		if (node.left != null) 
		{
			bst2ArrSolver(node.left, mode, cache);
		}
		if (mode == 0) 
		{
			cache.add(node.val);
		}
		if (node.right != null) 
		{
			bst2ArrSolver(node.right, mode, cache);
		}
		
		if (mode == 2) 
		{
			cache.add(node.val);
		}
	}
	
	public static ArrayList<Integer> bst2Arr(BST tree)
	{
		ArrayList<Integer> mem = new ArrayList<Integer>();
		bst2ArrSolver(tree.root, 0, mem);
		return mem;
	}
	
	public static ArrayList<Integer> bst2ArrPre(BST tree)
	{
		ArrayList<Integer> mem = new ArrayList<Integer>();
		bst2ArrSolver(tree.root, 1, mem);
		return mem;
	}
	
	public static ArrayList<Integer> bst2ArrPost(BST tree)
	{
		ArrayList<Integer> mem = new ArrayList<Integer>();
		bst2ArrSolver(tree.root, 2, mem);
		return mem;
	}
	
	public static void bstPreOrderNoRecursion (BST tree) 
	{
		/*
		 * array add/removes functionality models a Stack 
		 * */
		
		BTNode node;
		ArrayList<BTNode> mem = new ArrayList<BTNode>();
		
		mem.add(tree.root);
		
		while (mem.isEmpty() == false) 
		{
			node = mem.remove(mem.size() - 1);
			
			System.out.print("[" + node.val +  "]");
			
			if (node.right != null) 
			{
				mem.add(node.right);
			}
			
			if (node.left != null) 
			{
				mem.add(node.left);
			}
		}
		System.out.println("");

	}
	
	public static void traverseBSTReverseOrderSolver(BTNode node, ArrayList<Integer>  cache ) 
	{
		if (node == null) 
		{
			return ;
		}
		
		traverseBSTReverseOrderSolver(node.right, cache);
		cache.add(node.val);
		traverseBSTReverseOrderSolver(node.left, cache);
	}
	
	public static ArrayList<Integer> traverseBSTReverseOrder (BST tree) 
	{
		ArrayList<Integer> result = new ArrayList<Integer> ();
		traverseBSTReverseOrderSolver(tree.root, result);
		return result;
	}
	
	public static boolean treePathContainsSumSolver(BTNode node, final int target, int currSum)
	{
		if (node == null) 
		{
			return (currSum == target); 
		}
		
		return treePathContainsSumSolver(node.left, target, currSum + node.val) || treePathContainsSumSolver(node.right, target, currSum + node.val);
	}
	
	private static ArrayList<Integer> copyArrayList (ArrayList<Integer> src) 
	{
		ArrayList<Integer> arr = new ArrayList<Integer>();
		for (Integer retVal: src)
		{
			arr.add(retVal);
		}
		return arr;
	}
	
	public static void treePathContainsSumSolver2nd(BTNode node, final int target, ArrayList<ArrayList<Integer>> cache, ArrayList<Integer> buffer, int sumOfBuffer)
	{
		ArrayList<Integer> bufferCopy;
		int calSum;
		
		if (buffer == null)
		{
			buffer = new ArrayList<Integer>();
		}
		
		if (node == null) 
		{
			return;
		}
		
		if (sumOfBuffer == target)
		{
			calSum = 0;
			for (Integer retVal: buffer) 
			{
				calSum += retVal;
			}
			
			if(target == calSum) 
			{
				cache.add(buffer);
			}
			return;
		}
		
		bufferCopy = copyArrayList(buffer);
		bufferCopy.add(node.val);
		treePathContainsSumSolver2nd(node.left, target, cache, bufferCopy, sumOfBuffer + node.val);
		
		bufferCopy = copyArrayList(buffer);
		bufferCopy.add(node.val);
		treePathContainsSumSolver2nd(node.right, target, cache, bufferCopy, sumOfBuffer + node.val);
	}
	
	public static boolean treePathContainsSum (BST tree, int sum)
	{
		return treePathContainsSumSolver(tree.root, sum, 0);
	}
	
	public static ArrayList<ArrayList<Integer>> treePathContainsSum2nd (BST tree, int sum)
	{
		ArrayList<ArrayList<Integer>> array = new ArrayList<ArrayList<Integer>>();
		treePathContainsSumSolver2nd(tree.root, sum, array, null,  0);
		return array;
	}
	
	public static void sumOfBSTRootLeafNumbersSolver (BTNode node, ArrayList<Integer> cache, int sum, int index)
	{
		if (node == null)
		{
			return;
		}
		
		index += 1;
		sum += node.val * (int)Math.pow(10, index);
		
		if (node.left == null && node.right == null) // leaf !
		{
			cache.add(sum);
		}
		
		sumOfBSTRootLeafNumbersSolver(node.left, cache, sum , index);
		sumOfBSTRootLeafNumbersSolver(node.right, cache, sum , index);
	}
	
	public static ArrayList<Integer> sumOfBSTRootLeafNumbers (BST tree)
	{
		ArrayList<Integer> array = new ArrayList<Integer>();
		sumOfBSTRootLeafNumbersSolver(tree.root, array, 0,  -1);
		return array;
	}
	
	public static void leftSideBinaryTreeSolver(BTNode node, ArrayList<Integer> cache)
	{
		if (node == null)
		{
			return;
		}
		
		cache.add(node.val);
		
		if (node.right != null) 
		{
			cache.add(node.right.val);
		}
		
		if (node.left != null) 
		{
			leftSideBinaryTreeSolver (node.left, cache);
		}
		
		
	}
	public static ArrayList<Integer> leftSideBinaryTree(BST tree)
	{
		ArrayList<Integer> array = new ArrayList<Integer>();
		leftSideBinaryTreeSolver(tree.root, array);
		return array;
	}

}
