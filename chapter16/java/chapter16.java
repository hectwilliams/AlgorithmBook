package algo;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;

public class Chapter16 
{
	public static class TrieNode
	{
		String val;
		ArrayList<TrieNode> array;
		Integer count;
		String key;
		
		TrieNode(String value)
		{
			val = value;
			array = new ArrayList<TrieNode>();
			count = 1;
			key = "";
		}
	}
	
	public static class TrieSet
	{
		protected TrieNode root;
		
		TrieSet()
		{
			root = new TrieNode("");
		}
		
		public  boolean insert (String word)
		{
			int i;
			TrieNode node, newNode;
			String buffer = ""; 
			char c;
			
			if (word.isBlank())
			{
				return false;
			}
			
			node = root;
			
			while (buffer.length() < word.length())
			{
				i = -1;
				
				for ( i = 0; i < node.array.size(); i++)
				{
					c = node.array.get(i).val.charAt(node.array.get(i).val.length() - 1); 

					if (c == word.charAt(buffer.length()))  // compare string tails
					{
						node = node.array.get(i); // move down in tree
						buffer += c;

						if (buffer.length() == word.length()) // value already in trie tree !!!
						{
							return false;
						}
						break;
					}
				}
				
				if (i == -1 || i == node.array.size())  // char not found 
				{
					c = word.charAt(buffer.length());
					buffer += c;
					
					newNode = new TrieNode(buffer) ;
					node.array.add(newNode);
					
					node = node.array.get(node.array.size() - 1); // move down in tree
				}
			}

			return true;
		}
	
		public int contains (String word)
		{
			TrieNode node, retNode;
			char c;
			int i;
			
			if (word.isBlank())
			{
				return 0;
			}
			
//			word = word.toLowerCase();
			node = root;
			
			while (!node.array.isEmpty())
			{
				c = word.charAt(node.val.length()); // get 'word' variable character;
				i = -1;
				
				for ( i = 0; i < node.array.size(); i++)
				{
					retNode = node.array.get(i);
					if (retNode.val.charAt(retNode.val.length() - 1) == c)
					{
						node = retNode;
						if (node.val.length() == word.length())
						{
							return 1;
						}
						break;
					}
				}
				
				if (i == -1 || i == node.array.size()) // word not found
				{
					break;
				}
			}
			return 0;
		}
		
	
		public String first ()
		{
			TrieNode node, minNode;
			int i;
			
			node = root;
	
			while (!node.array.isEmpty())
			{
				minNode = node.array.get(0);
				for ( i = 1; i < node.array.size(); i++)
				{
					if (node.array.get(i).val.charAt(node.array.get(i).val.length() - 1) <= minNode.val.charAt(minNode.val.length() - 1) )
					{
						minNode = node.array.get(i) ;
					}
				}
				node = minNode; 
			}
			
			
			return node.val;
		}
		
		public String last ()
		{
			TrieNode node, maxNode;
			int i;
			
			node = root;
	
			while (!node.array.isEmpty())
			{
				maxNode = node.array.get(0);
				for ( i = 1; i < node.array.size(); i++)
				{
					if (node.array.get(i).val.charAt(node.array.get(i).val.length() - 1) > maxNode.val.charAt(maxNode.val.length() - 1) )
					{
						maxNode = node.array.get(i) ;
					}
				}
				node = maxNode; 
			}
			
			return node.val;
		}
		
		public  int remove(String word) 
		{
			int removalSubtreeIndex = -1;
			char trieNodeChar, wordChar;
			String buffer = "";
			TrieNode node, parentOfRemovedSubtree = null;
			ArrayList<TrieNode> collection = new ArrayList<TrieNode>();
			int i = -1, bufferLenPrevious;
			
			if (root == null || word.isBlank() )
			{
				return 0;
			}
			
			node = root;
//			
			while ( !node.array.isEmpty() && buffer.length() != word.length() )
			{
				i = -1;
				wordChar = word.charAt(buffer.length());
				bufferLenPrevious = buffer.length();
				
				for (i = 0; i < node.array.size(); i++)
				{
					trieNodeChar = node.array.get(i).val.charAt(node.array.get(i).val.length() - 1);

					if ( trieNodeChar == wordChar  )  // char match found
					{
						buffer += wordChar;

						// child has no siblings (add to removal map) ?
						// child node matches target word ?
						if (node.array.get(i).array.size() == 1 || buffer.length() == word.length() )
						{
							if (parentOfRemovedSubtree == null)
							{
								parentOfRemovedSubtree = node;
								removalSubtreeIndex = i;
							}
						}
						else 
						{
							parentOfRemovedSubtree = null;
							removalSubtreeIndex = -1;
						}
						
						node = node.array.get(i) ;
						break;							
					}
				}
				
				// buffer must grow
				if (bufferLenPrevious == buffer.length())
				{
					return 0;
				}
			}
			

			/* remove subtree using first breadth*/
			collection.add(parentOfRemovedSubtree.array.remove(removalSubtreeIndex));
			while (!collection.isEmpty())
			{
				node = collection.remove(0); 
				System.out.println("DEBUG INFO: removed trie node = " + node.val);
				// clear array
				while (!node.array.isEmpty())
				{
					collection.add(node.array.remove(0));
				}
			}
			
			return 1; 
		}
		
		public int size ()
		{
			int count = 0;
			TrieNode node;
			ArrayList<TrieNode> collection = new ArrayList<TrieNode>();

			if (root == null)
			{
				return -1;
			}
			
			collection.add(root);
			
			while (!collection.isEmpty())
			{
				node = collection.remove(0); 
				
				// clear array
				for (int i = 0; i < node.array.size(); i++)
				{
					collection.add(node.array.get(i));
				}
				
				// termination?
				if (node.array.size() == 0)
				{
					System.out.println("DEBUG INFO: terminated trie node = " + node.val);
					count++;
				}
			}
			return count;
		}
		
		public String next (String word)
		{
			TrieNode node, nextNode;
			int i;
			
			if (word.isBlank())
			{
				return null;
			}
			
			nextNode = node = root;
	
			/* find input 'target' word in trie tree */ 

			while (!node.array.isEmpty() && node.val.length() < word.length())
			{
				for ( i = 0; i < node.array.size(); i++)
				{
					if (node.array.get(i).val.charAt(node.array.get(i).val.length() - 1) == word.charAt(node.val.length()) )
					{
						nextNode = node.array.get(i) ;
					}
				}
				
				if (node == nextNode) 
				{
					return null;
				}
				
				node = nextNode;
			}
			
			if (node.array.size() == 0)
			{
				return null;
			}
			
			/* find next available word in trie tree */ 
			nextNode = node.array.get(0);
			for ( i = 1; i < node.array.size(); i++)
			{
				if (node.array.get(i).val.charAt(node.array.get(i).val.length() - 1) < nextNode.val.charAt(nextNode.val.length() - 1) )
				{
					nextNode = node;
				}
			}
			
			return nextNode.val;
		}
		
		public ArrayList<String> autoComplete (String word)
		{
			ArrayList<String> possibleWords = new ArrayList<String>();
			ArrayList<TrieNode> arrayOfNodes = new ArrayList<TrieNode>();
			TrieNode node, nextNode;

			if (word.isBlank())
			{
				return null;
			}
			
			nextNode = node = root;
			
			/* find input 'target' word in trie tree */ 

			while (!node.array.isEmpty() && node.val.length() < word.length())
			{
				for ( int i = 0; i < node.array.size(); i++)
				{
					if (node.array.get(i).val.charAt(node.array.get(i).val.length() - 1) == word.charAt(node.val.length()) )
					{
						nextNode = node.array.get(i) ;
					}
				}
				
				if (node == nextNode) 
				{
					return null;
				}
				
				node = nextNode;
			}
			
			/* find descendants and add to collection*/ 

			arrayOfNodes.add(node);
			while (!arrayOfNodes.isEmpty())
			{
				node = arrayOfNodes.remove(0);
				
				for (TrieNode retNode : node.array)
				{
					arrayOfNodes.add(retNode);
				}
				
				possibleWords.add(node.val);
			}
			
			return possibleWords;
		}
		
		public ArrayList<String> autoComplete (String word, int maxResults)
		{
			ArrayList<String> possibleWords = autoComplete(word);
			int i = 0;
			while (i < possibleWords.size())
			{
				if (possibleWords.get(i).length() > maxResults)
				{
					possibleWords.remove(i);
				}
				else
				{
					i++;
				}
			}
			return possibleWords;
	
		}
	}
	
	public static class TrieMultiSet extends TrieSet
	{
		
		public  boolean insert (String word)
		{
			int i;
			TrieNode node, newNode;
			String buffer = ""; 
			char c;
			
			if (word.isBlank())
			{
				return false;
			}
			
			node = this.root;
//			word = word.toLowerCase();
			
			while (buffer.length() < word.length())
			{
				i = -1;
				
				for ( i = 0; i < node.array.size(); i++)
				{
					c = node.array.get(i).val.charAt(node.array.get(i).val.length() - 1); 

					if (c == word.charAt(buffer.length()))  // compare string tails
					{
						node = node.array.get(i); // move down in tree
						buffer += c;

						if (buffer.length() == word.length()) // value already in trie tree !!!
						{
							node.count++;
							System.out.println("node = " + node.val  + " " + node.count);
							return true;
						}
						break;
					}
				}
				
				if (i == -1 || i == node.array.size())  // char not found 
				{
					c = word.charAt(buffer.length());
					buffer += c;
					
					newNode = new TrieNode(buffer) ;
					node.array.add(newNode);
					
					node = node.array.get(node.array.size() - 1); // move down in tree
				}
			}

			return true;
		}
		
		public  int remove(String word) 
		{
			int removalSubtreeIndex = -1;
			char trieNodeChar, wordChar;
			String buffer = "";
			TrieNode node, parentOfRemovedSubtree = null;
			ArrayList<TrieNode> collection = new ArrayList<TrieNode>();
			int i = -1, bufferLenPrevious;
			
			if (root == null || word.isBlank() )
			{
				return 0;
			}
			
			node = root;

			while ( !node.array.isEmpty() && buffer.length() != word.length() )
			{
				i = -1;
				wordChar = word.charAt(buffer.length());
				bufferLenPrevious = buffer.length();
				
				for (i = 0; i < node.array.size(); i++)
				{
					trieNodeChar = node.array.get(i).val.charAt(node.array.get(i).val.length() - 1);

					if ( trieNodeChar == wordChar  )  // char match found
					{
						buffer += wordChar;

						if (node.array.get(i).array.size() == 1 && node.array.get(i).count == 1 || buffer.length() == word.length() )
						{
							if (parentOfRemovedSubtree == null)
							{
								parentOfRemovedSubtree = node;
								removalSubtreeIndex = i;
							}
						}
						else 
						{
							parentOfRemovedSubtree = null;
							removalSubtreeIndex = -1;
						}
						
						node = node.array.get(i) ;
						break;							
					}
				}
				
				// buffer must grow
				if (bufferLenPrevious == buffer.length())
				{
					return 0;
				}
			}
			
			// get count 
			i = parentOfRemovedSubtree.array.get(removalSubtreeIndex).count--;
			
			// delete if necessary 

			if (parentOfRemovedSubtree.array.get(removalSubtreeIndex).count == 0)
			{
				collection.add(parentOfRemovedSubtree.array.remove(removalSubtreeIndex));
				while (!collection.isEmpty())
				{
					node = collection.remove(0); 
					System.out.println("DEBUG INFO: removed trie node = " + node.val);
					// clear array
					while (!node.array.isEmpty())
					{
						collection.add(node.array.remove(0));
					}
				}	
			}
			return i; 
		}
		
		
		public int contains (String word) 
		{
			char trieNodeChar, wordChar;
			String buffer = "";
			TrieNode node;
			int i = -1, bufferLenPrevious;
			
			if (root == null || word.isBlank() )
			{
				return 0;
			}
			
			node = root;

			while ( !node.array.isEmpty() && buffer.length() != word.length() )
			{
				i = -1;
				wordChar = word.charAt(buffer.length());
				bufferLenPrevious = buffer.length();
				
				for (i = 0; i < node.array.size(); i++)
				{
					trieNodeChar = node.array.get(i).val.charAt(node.array.get(i).val.length() - 1);

					if ( trieNodeChar == wordChar  )  // char match found
					{
						buffer += wordChar;
						node = node.array.get(i) ;
						break;							
					}
				}
				
				// buffer must grow
				if (bufferLenPrevious == buffer.length())
				{
					return 0;
				}
			}
			
			return node.count;
		}

		public int size ()
		{
			int count = 0;
			TrieNode node;
			ArrayList<TrieNode> collection = new ArrayList<TrieNode>();

			if (root == null)
			{
				return -1;
			}
			
			collection.add(root);
			
			while (!collection.isEmpty())
			{
				node = collection.remove(0); 
				
				// clear array
				for (int i = 0; i < node.array.size(); i++)
				{
					collection.add(node.array.get(i));
				}
				
				// termination?
				if (node.array.size() == 0)
				{
					System.out.println("DEBUG INFO: terminated trie node = " + node.val);
					count += node.count;
				}
			}
			return count;
		}
		
		public ArrayList<String> autoComplete (String word)
		{
			ArrayList<String> possibleWords = new ArrayList<String>();
			ArrayList<TrieNode> arrayOfNodes = new ArrayList<TrieNode>();
			TrieNode node, nextNode;
			int start = 0, end= 0;
			
			if (word.isBlank())
			{
				return null;
			}
			
			nextNode = node = root;
			
			/* find input 'target' word in trie tree */ 

			while (!node.array.isEmpty() && node.val.length() < word.length())
			{
				for ( int i = 0; i < node.array.size(); i++)
				{
					if (node.array.get(i).val.charAt(node.array.get(i).val.length() - 1) == word.charAt(node.val.length()) )
					{
						nextNode = node.array.get(i) ;
					}
				}
				
				if (node == nextNode) 
				{
					return null;
				}
				
				node = nextNode;
			}
			
			/* find descendants and add to collection*/ 

			arrayOfNodes.add(node);
			end = 1;
			start = 0;
			
			// load array 
			while (start< end)
			{
				node = arrayOfNodes.get(start++);
				
				for (TrieNode retNode : node.array)
				{
					arrayOfNodes.add(retNode);
					end++;
				}
			}
			
			// sort array
			arrayOfNodes.sort(new SortByVal());
			
			// load returned auto complete words 
			for (TrieNode retNode : arrayOfNodes )
			{
				possibleWords.add(retNode.val + " " + retNode.count);
			}
			
			return possibleWords;
		}
		
		private  class SortByVal implements Comparator<TrieNode>
		{
			@Override
			public int compare(TrieNode a, TrieNode b) {
				return a.val.compareTo(b.val);
			}
			
		}
	}
	
	public static class TrieMap 
	{
		protected TrieNode root;
		
		TrieMap()
		{
			root = new TrieNode("");
		}
		
		public String insert(String key , String value)
		{
			int i;
			TrieNode node, newNode;
			String bufferKey = ""; 
			char c;
			
			if (key.isBlank())
			{
				return null;
			}
			
			node = root;

			while (bufferKey.length() < key.length())
			{
				i = -1;
				
				for ( i = 0; i < node.array.size(); i++)
				{
					c = node.array.get(i).key.charAt(node.array.get(i).key.length() - 1); 
					if (c == key.charAt(bufferKey.length()))  // compare string tails
					{
						node = node.array.get(i); // move down in tree
						bufferKey += c;

						if (bufferKey.length() == key.length()) // value already in trie tree !!!
						{
							return node.val;
						}
						break;
					}
				}
				
				if (i == -1 || i == node.array.size())  // char not found 
				{
					c = key.charAt(bufferKey.length());
					bufferKey += c;
					newNode = new TrieNode(value) ;
					newNode.key = bufferKey;
					node.array.add(newNode);
					node = node.array.get(node.array.size() - 1); // move down in tree
				}
			}

			return null;
		}
		
		public String contains (String key)
		{
			char trieNodeChar, wordChar;
			String bufferKey = "";
			TrieNode node;
			int bufferLenPrevious;
			
			if (root == null || key.isBlank() )
			{
				return null;
			}
			
			node = root;

			while ( !node.array.isEmpty() && bufferKey.length() != key.length() )
			{
				wordChar = key.charAt(bufferKey.length());
				bufferLenPrevious = bufferKey.length();
				
				for (int i = 0; i < node.array.size(); i++)
				{
					trieNodeChar = node.array.get(i).key.charAt(node.array.get(i).key.length() - 1);

					if ( trieNodeChar == wordChar  )  // char match found
					{
						bufferKey += wordChar;
						node = node.array.get(i) ;
						break;							
					}
				}
				
				// buffer must grow
				if (bufferLenPrevious == bufferKey.length())
				{
					return null;
				}
			}
			
			return node.val;
		}
		
		public boolean remove (String key)
		{
			int removalSubtreeIndex = -1;
			char trieNodeChar, wordChar;
			String bufferKey = "";
			TrieNode node, parentOfRemovedSubtree = null;
			ArrayList<TrieNode> collection = new ArrayList<TrieNode>();
			int bufferLenPrevious;
			
			if (root == null || key.isBlank() )
			{
				return false;
			}
			
			node = root;

			while ( !node.array.isEmpty() && bufferKey.length() != key.length() )
			{
				wordChar = key.charAt(bufferKey.length());
				bufferLenPrevious = bufferKey.length();
				
				for (int i = 0; i < node.array.size(); i++)
				{
					trieNodeChar = node.array.get(i).key.charAt(node.array.get(i).key.length() - 1);

					if ( trieNodeChar == wordChar  ) 
					{
						bufferKey += wordChar;

						if (node.array.get(i).array.size() == 1  || bufferKey.length() == key.length() )
						{
							if (parentOfRemovedSubtree == null)
							{
								parentOfRemovedSubtree = node;
								removalSubtreeIndex = i;
							}
						}
						else 
						{
							parentOfRemovedSubtree = null;
							removalSubtreeIndex = -1;
						}
						
						node = node.array.get(i) ;
						break;							
					}
				}
				
				// buffer must grow
				if (bufferLenPrevious == bufferKey.length())
				{
					return false;
				}
			}
			
			if (parentOfRemovedSubtree == null) // nothing to deleted!!
			{
				return false;
			}
			
			// delete 
			collection.add(parentOfRemovedSubtree.array.remove(removalSubtreeIndex));
			while (!collection.isEmpty())
			{
				node = collection.remove(0); 
				System.out.println("DEBUG INFO: removed trie node = " + node.val);
				while (!node.array.isEmpty())
				{
					collection.add(node.array.remove(0));
				}
			}	
			return true; 
		}
		

		public String first ()
		{
			TrieNode node, minNode;
			int i;
			
			node = root;
	
			while (!node.array.isEmpty())
			{
				minNode = node.array.get(0);
				for ( i = 1; i < node.array.size(); i++)
				{
					if (node.array.get(i).val.charAt(node.array.get(i).key.length() - 1) <= minNode.key.charAt(minNode.key.length() - 1) )
					{
						minNode = node.array.get(i) ;
					}
				}
				node = minNode; 
			}
			
			
			return node.key;
		}
		
		public String last ()
		{
			TrieNode node, maxNode;
			int i;
			
			node = root;
	
			while (!node.array.isEmpty())
			{
				maxNode = node.array.get(0);
				for ( i = 1; i < node.array.size(); i++)
				{
					if (node.array.get(i).key.charAt(node.array.get(i).key.length() - 1) > maxNode.key.charAt(maxNode.key.length() - 1) )
					{
						maxNode = node.array.get(i) ;
					}
				}
				node = maxNode; 
			}
			
			return node.key;
		}
		
		public String next (String word)
		{
			TrieNode node, nextNode;
			int i;
			
			if (word.isBlank())
			{
				return null;
			}
			
			nextNode = node = root;
	
			/* find input 'target' word in trie tree */ 

			while (!node.array.isEmpty() && node.key.length() < word.length())
			{
				for ( i = 0; i < node.array.size(); i++)
				{
					if (node.array.get(i).key.charAt(node.array.get(i).key.length() - 1) == word.charAt(node.key.length()) )
					{
						nextNode = node.array.get(i) ;
					}
				}
				
				if (node == nextNode) 
				{
					return null;
				}
				
				node = nextNode;
			}
			
			if (node.array.size() == 0)
			{
				return null;
			}
			
			/* find next available word in trie tree */ 
			nextNode = node.array.get(0);
			for ( i = 1; i < node.array.size(); i++)
			{
				if (node.array.get(i).key.charAt(node.array.get(i).key.length() - 1) < nextNode.key.charAt(nextNode.key.length() - 1) )
				{
					nextNode = node;
				}
			}
			
			return "[" + "key: " +nextNode.key + " value: " + nextNode.val + "]";
		}
		


	}


}
