package algo;
import java.util.ArrayList;

import algo.Chapter11.*;
import algo.Chapter6.*;
import algo.Chapter5.*;

public class Chapter15 
{
	public static boolean isFull (BST tree)
	{
		ArrayList<BTNode> stackModel = new ArrayList<BTNode>();   // first depth 
		BTNode node;
		if (tree.root == null) 
		{
			return false;
		}
		
		stackModel.add(tree.root);
		
		while (!stackModel.isEmpty())
		{
			node = stackModel.remove(0);
			
			if (node.right != null) 
			{
				stackModel.add(0, node.right);
			}
			
			if (node.left!= null) 
			{
				stackModel.add(0, node.left);
			}
			
			if ( node.right != null ^ node.left != null ) 
			{
				return false;
			}
		}
		return true;
	}
	
	public static boolean isComplete (BST tree)
	{
		ArrayList<BTNode> stackModel = new ArrayList<BTNode>();   // first depth 
		BTNode node;
		if (tree.root == null) 
		{
			return false;
		}
		
		stackModel.add(tree.root);
		
		while (!stackModel.isEmpty())
		{
			node = stackModel.remove(0);
			
			if (node.right != null) 
			{
				stackModel.add(0, node.right);
			}
			
			if (node.left!= null) 
			{
				stackModel.add(0, node.left);
			}
			
			if ( node.right != null  && node.left == null) 
			{
				return false;
			}
		}
		return true;
	}
	
	public static void repairHelperReinsertion (BST tree, ArrayList<BTNode> collectionOfInvalidNodes)
	{
		BTNode node;
		ArrayList<BTNode> stackModel = new ArrayList<BTNode>();   

		for (BTNode retNode: collectionOfInvalidNodes)
		{
			stackModel.add(retNode);
			while (!stackModel.isEmpty())
			{
				node = stackModel.remove(0);
				
				if (node.right != null) 
				{
					stackModel.add(0, node.right);
				}
				
				if (node.left!= null) 
				{
					stackModel.add(0, node.left);
				}
				
				tree.add(node.val); // reinsert to tree 
			}
		}
	}

	public static boolean repair (BST tree) 
	{
		ArrayList<BTNode> stackModel = new ArrayList<BTNode>();   
		ArrayList<BTNode> collectionOfInvalidNodes = new ArrayList<BTNode>();   
		BTNode node;

		if (tree.root == null)
		{
			return false;
		}
		
		// root evaluation
		if (tree.root.left != null) 
		{
			if (tree.root.left.val >= tree.root.val) 
			{
				collectionOfInvalidNodes.add(tree.root.left);
				tree.root.left = null;
			}
		}
		
		if (tree.root.right != null )  // check if root already includes 
		{
			if (tree.root.right.val < tree.root.val)  
			{
				collectionOfInvalidNodes.add(tree.root.right);
				tree.root.right= null;		
			}
		}
		
		if ( collectionOfInvalidNodes.isEmpty() ) //  root children are value, continue analysis 
		{
			stackModel.add(tree.root);
			
			while (!stackModel.isEmpty())  
			{
				node = stackModel.remove(0);
				
				if (node.right != null) 
				{
					if (node.right.val < node.val)  // insertion error 
					{
						collectionOfInvalidNodes.add(node.right);
						node.right = null;
					}
					else 
					{
						stackModel.add(0, node.right);
					}
				}
				
				if (node.left!= null) 
				{ 
					if (node.left.val >= node.val)  // insertion error 
					{
						collectionOfInvalidNodes.add(node.left);
						node.left = null;
					}
					else 
					{
						stackModel.add(0, node.left);
					}
				}
				
			}	
		}
		
		repairHelperReinsertion (tree, collectionOfInvalidNodes); 
		return collectionOfInvalidNodes.size() != 0; 
	}
	
	
	public static Integer smallestDifference(BST tree) 
	{
		ArrayList<BTNode> stackModel = new ArrayList<BTNode>();   
		Integer currDiff, smallDiff = null;
		BTNode node;
		
		if (tree.root == null) 
		{
			return null;
		}
		
		stackModel.add(tree.root);
		smallDiff = tree.root.val;
		
		while (!stackModel.isEmpty())
		{
			node = stackModel.remove(0);
			
			if (node.right != null) 
			{
				currDiff = Math.abs(node.val - node.right.val);
				if (currDiff < smallDiff )
				{
					smallDiff = currDiff;
				}
				stackModel.add(0, node.right);
			}
			
			if (node.left!= null) 
			{
				currDiff = Math.abs(node.val - node.left.val);
				if (currDiff < smallDiff )
				{
					smallDiff = currDiff;
				}
				stackModel.add(0, node.left);
			}
			
		}
		
		return smallDiff;
	}

	
	public static Integer smallestDifference(Node node) 
	{
		Integer currDiff, smallDiff = null;
		Node runner;
		
		while (node.next != null)
		{
			runner = node.next;
			while (runner.next != null)
			{
				currDiff = Math.abs(node.value - runner.value);
				if (smallDiff == null || currDiff < smallDiff)
				{
					smallDiff = currDiff;
				}
				runner = runner.next;
			}
			node = node.next;
		}
		return smallDiff;
	}
	
	public static Integer closestValue (BST tree, int value)
	{
		BTNode node;
		
		if (tree.root == null) 
		{
			return null;
		}
		
		node = tree.root;
		
		do 
		{
			if (node.left!= null)
			{
				if (value < node.val)
				{
					node = node.left;
					continue;
				}
			}
			
			if (node.right != null) 
			{
				if (value >= node.val) 
				{
					node = node.right;
					continue;
				}
			}
			
			break; // break here
		}
		while (node.val != value);

		
		return node.val;
	}
	
	// partition  (see chapter 11.java BST class)
	
	public static BST partitionEvenly (BST tree)
	{
		ArrayList<BTNode> queueModel = new ArrayList<BTNode>();   // first breadth 
		BTNode node, retNode;		
		BST subtree = null;
		int index = 0;
		int tail = 0;
		
		if (tree.root == null) 
		{
			return subtree;
		}
		
		queueModel.add(tree.root);
		while ( index <= tail)  // break when queueModel length does not change (tree iteration complete) 
		{
			node = queueModel.get(index);
			
			if (node.right != null) 
			{
				queueModel.add(node.right);
				tail++;
			}
			
			if (node.left!= null) 
			{
				queueModel.add(node.left);
				tail++;
			}
			index++;
		}
		

		// remaining nodes build subtree
		subtree = new BST();
		for (int i = queueModel.size() / 2 + 1; i < queueModel.size(); i++)
		{
			retNode = queueModel.get(i);
			if (subtree.root == null)
			{
				subtree.root = retNode;
			}
			else 
			{
				node = subtree.root;
				do
				{
					if (retNode.val < node.val) 
					{
						if (node.left == null)
						{
							node.left = retNode;
						}
						else 
						{
							node = node.left;
						}
					}
					
					else if (retNode.val >=  node.val) 
					{
						if (node.right == null)
						{
							node.right = retNode;
						}
						else 
						{
							node = node.right;
						}		
					}
					
				}
				while (node != retNode);
			}
		}
		
		// rebuild tree
		tree.root = null;
		for (int i = 0; i < queueModel.size() / 2; i++)
		{
			retNode = queueModel.get(i);
			retNode.left = retNode.right = null;
			
			if (tree.root == null)
			{
				tree.root = retNode;
			}
			else 
			{
				node = tree.root;
				do
				{
					if (retNode.val < node.val) 
					{
						if (node.left == null)
						{
							node.left = retNode;
						}
						else 
						{
							node = node.left;
						}
					}
					
					else if (retNode.val >=  node.val) 
					{
						if (node.right == null)
						{
							node.right = retNode;
						}
						else 
						{
							node = node.right;
						}		
					}
					
				}
				while (node != retNode);
			}
		}
		
		return subtree; 
		
	}
	
	public static void reverse(BST tree)
	{
		ArrayList<BTNode> cache = new ArrayList<BTNode>();
		BTNode left, right, node;
		
		if (tree.root == null)
		{
			return;
		}
		
		cache.add(tree.root);
		
		while (!cache.isEmpty())
		{
			node = cache.remove(0);
			left = right = null;
			
			if (node.left != null)
			{
				left = node.left;
				cache.add(node.left);
			}
			
			if (node.right != null)
			{
				right = node.right;
				cache.add(node.right);
			}
			
			node.right = left;
			node.left = right;
		}
		
	}
	
	public static Integer KthBiggest (BST tree, int k)  // geez lawwwwwweeeeez
	{
		BTNode node, prevNode,  predecessor = null, maxNode = null;
		Integer numResult = null;
		
		if (tree.root == null || k <= 0)
		{
			return null;
		}
		
		maxNode = tree.root;
		while (maxNode.right != null)
		{
			predecessor = maxNode;
			maxNode = maxNode.right;
			numResult = maxNode.val;
		}

		for (int i = 1; i < k ; i++)
		{
			//System.out.println( "  \t   " + maxNode.val   +  "  " + predecessor.val);  search for kth largest value when maxNode value larger than predecessor 
			 if (maxNode.val < predecessor.val)
			 {
				 return null;
			 }
			 
			maxNode = predecessor;
			numResult = maxNode.val;

			if (maxNode.left != null)
			{
				predecessor = maxNode.left;
				while (predecessor.right != null)
				{
					predecessor = predecessor.right;
				}
			}
			else 
			{
				prevNode = node = tree.root;
				while ( (node.left != maxNode && node.right != maxNode))
				{
					if (maxNode.val > node.val)
					{
						if (node.right != null)
						{
							prevNode = node;
							node = node.right;
						}
					}
					else if (maxNode.val  < node.val)
					{
						if (node.left != null)
						{
							prevNode = node;
							node = node.left;
						}
					}
				}
				
				// calculate predecessor 
				if (node.val >  maxNode.val)
				{
					predecessor = prevNode;
				}
				else 
				{
					predecessor = node;
				}
			}
			
		}
		
		return numResult;
	}
}
