package algo;
import algo.Chapter6.*;
import java.util.ArrayList;

public class Chapter14 {
	
	public static class Hash 
	{
		private int capacity;
		private ArrayList< ArrayList<String> > table;
		
		Hash(int cap) 
		{
			if (cap <= 0)
			{
				cap = 10;
			}
			
			capacity = cap;
			table = new ArrayList< ArrayList<String>  >();
			
			for (int i = 0; i < cap; i++)
			{
				table.add(null);
			}
		}
		
		private int hashCoder (String key) 
		{
			int hash = 0;
			
			for (int i = 0; i < key.length(); i++ )
			{
				hash += key.codePointAt(i);
			}
			return hash;
		}
		
		public void add (String key, int value)
		{
			int code = hashCoder(key);
			int index = code % capacity;
			int i = 0;
			
			if ( table.get(index) == null) 
			{
				table.set(index, new ArrayList<String>() );
			}
			
			// check for value
			for (i = 0; i <  table.get(index).size(); i+=2)
			{
				if (table.get(index).get(i).compareTo(key) == 0 && table.get(index).get(i + 1).compareTo(String.valueOf(value)) == 0)
				{
					return;
				}
			}
			
			// add new elements to array 
			 table.get(index).add(key);
			 table.get(index).add(String.valueOf(value));

			
		}
		
		public boolean isEmpty() 
		{
			boolean empty = true;
			for (ArrayList<String> retArr: table)
			{
				if (retArr != null) // skip nulled array elements 
				{
					empty &= retArr.size() == 0;
				}
			}
			return empty;
		}

		public ArrayList<Integer> find(String key)
		{
			int code = hashCoder(key);
			int index = code % capacity;
			ArrayList<Integer> buffer = new ArrayList<Integer>();
			int[] result = {};
			
			if (table.get(index) == null) 
			{
				return buffer;
			}
			
			
			for (int i = 0; i < table.get(index).size(); i+=2)
			{
				if (table.get(index).get(i).compareTo(key) == 0)
				{
					buffer.add( Integer.valueOf(table.get(index).get(i + 1) ));
				}
			}
			
			return buffer;
		}
		
		public void displayHashTree () // DEBUG
		{
			for (ArrayList<String > retStringArr: table )
			{
				if (retStringArr != null) 
				{
					System.out.print("\t[");
					for (int i = 0 ; i < retStringArr.size(); i++) 
					{
						System.out.print(retStringArr.get(i) + ",");
					}
					System.out.print("]");
					System.out.println();
				}
				else 
				{
					System.out.println("\t" + retStringArr);					
				}
			}
		}
		
		public ArrayList<Integer> remove (String key) 
		{
			int index = hashCoder(key) % capacity;
			ArrayList<Integer> buffer = new ArrayList<Integer>();
			int i = 0;
			
			if (table.get(index) != null) 
			{
				while (i < table.get(index).size())
				{
					if ( table.get(index).get(i).compareTo(key) == 0   )
					{
						// add value
						buffer.add( Integer.valueOf( table.get(index).get(i + 1) ));
						
						// delete 
						table.get(index).remove(i);
						table.get(index).remove(i);
					}
					else 
					{
						i+=2;
					}
				}
			}
			
			return buffer;
		}
		
		public double loadFactor () 
		{
			int elementCount = 0;
			int bucketCount = 0;
			
			for (ArrayList<String> arr : table) 
			{
				if (arr != null) 
				{
					bucketCount += 1;
					elementCount += arr.size() / 2;
				}
			}
			
			if (bucketCount == 0) 
			{
				return -1;
			}
			
			return elementCount / (double) bucketCount;
		}
		
		public void setSize (int newCap)
		{
			ArrayList< ArrayList<String> > newTable = new ArrayList<ArrayList<String>>();
			String value; 
			String key;
			int index;
			
			capacity = newCap; 
			
			for (int i = 0; i < capacity; i ++)
			{
				newTable.add(null);
			}
			
			// get keyValue pairs 
			for (ArrayList<String> arr : table) 
			{
				if (arr != null) 
				{
					for (int i = 0; i < arr.size(); i+=2) 
					{
						key = arr.get(i);
						value = arr.get(i + 1);
						index = hashCoder(key) % capacity;
						
						if (newTable.get(index) == null) 
						{
							newTable.set(index, new ArrayList<String>());
						}
						
						newTable.get(index).add(key);
						newTable.get(index).add(value);
					}
				}
			}
			
			// update class instance variable table 
			table = newTable;
		}
		
		public void grow ()
		{
			setSize(capacity + capacity / 2);
		}
		
		public void addMap (Hash hashmap)
		{
			String value; 
			String key;
			int index;
			boolean foundKeyValuePair;
			
			// get keyValue pairs from hashmap argument 
			for (ArrayList<String> arr : hashmap.table) 
			{
				if (arr != null) 
				{
					for (int i = 0; i < arr.size(); i+=2) 
					{
						key = arr.get(i);
						value = arr.get(i + 1);
						index = hashCoder(key) % capacity;
						
						// search for key/value pair in 'this' table
						foundKeyValuePair = false;
						for (int k = 0 ; k < table.get(index).size() ; k+=2 )
						{
							foundKeyValuePair |= table.get(index).get(i).compareTo(key) == 0 && table.get(index).get(i + 1).compareTo(value) == 0;
						}
						
						// add to table (if necessary)
						if (!foundKeyValuePair)
						{
							table.get(index).add(key);
							table.get(index).add(value);
						}
						
					}
				}
			}
		}
		
		public void selectKeys (String[] keys) 
		{
			ArrayList<String> replacementBucket;
	
			for (int i = 0; i < table.size(); i++) 
			{
				if (table.get(i) != null)
				{
					
					replacementBucket = new ArrayList<String>();
					
					for (int k = 0; k < table.get(i).size(); k += 2)
					{
						//  compare to keys list 
						for (String selectedKey: keys)
						{
							if ( selectedKey.compareTo(table.get(i).get(k)) == 0)
							{
								// selection (add to new bucket) 
								replacementBucket.add(table.get(i).get(k));
								replacementBucket.add(table.get(i).get(k + 1));
							}
						}
					}
					
					// replace bucket 
					table.set(i, replacementBucket);
				}
			}
		}
		
	}
}
