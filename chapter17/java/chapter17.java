package algo;

import java.util.HashMap;
import java.util.HashSet;


import java.util.ArrayList;

public class Chapter17 
{
	/*
	 * 
	 * 
	 * Graph notes:
	 * 
	 * order - number of vertices 
	 * size - number of edges 
	 * 
	 * 
	 * 
	 * */
	
	private static class GraphNode 
	{
		String val;
		String id;
		Integer edgeVal;
		
		GraphNode(String val, String id)
		{
			this.val = val;
			this.id = id;
			this.edgeVal = null;
		}
	}
	
	public static  class ALGraph 
	{
		private int id;
		HashMap<String, ArrayList<GraphNode> > edgeMap;
		
		ALGraph()
		{
			edgeMap = new HashMap<String, ArrayList<GraphNode>>();
			id = 0;
		}
		
		public String addVertex(String value) 
		{
			String currentID = String.valueOf(id++);
			GraphNode node = new GraphNode(value, currentID);
			edgeMap.put(currentID, new ArrayList<GraphNode>());
			
			edgeMap.get(currentID).add(node); // vertex node located at 0th index of array list 
			return currentID;
		}
		
		public boolean removeVertex (String vertexID)
		{
			if (!edgeMap.containsKey(vertexID))
			{
				return false;
			}
			edgeMap.remove(vertexID);
			return true;
		}
		
		public String getVertexValue (String vertexID)
		{
			if (!edgeMap.containsKey(vertexID))
			{
				return null;
			}
			return edgeMap.get(vertexID).get(0).val;
		}
		
		public boolean setVertexValue (String vertexID, String value)
		{
			if (!edgeMap.containsKey(vertexID))
			{
				return false;
			}
			edgeMap.get(vertexID).get(0).val = value;

			return true;
		}
		
		public boolean addEdge (String vertexID1, String vertexID2, int value )
		{
			ArrayList<GraphNode> listID1;
			GraphNode newNode = new GraphNode(null, vertexID2);
			
			if (!edgeMap.containsKey(vertexID1))
			{
				return false;
			}
			if (!edgeMap.containsKey(vertexID2))
			{
				return false;
			}
			
			// does edge exist ?
			listID1 = edgeMap.get(vertexID1);
			for (int i = 1; i < listID1.size(); i++)
			{
				if (listID1.get(i).id == vertexID2 )  // vertID1 -> vertID2 exists
				{
					// return set edge 
				}
			}
			
			newNode.edgeVal = value;
			newNode.id = vertexID2;
			newNode.val = null;  // N/A
			
			listID1.add(newNode); // add vertID2 graph edge
			
			return true;
		}
		
		public void removeEdges (String vertexID)
		{
			ArrayList<GraphNode> list;
			int i;
			
			if (!edgeMap.containsKey(vertexID))
			{
				return ;
			}
			
			
			for (String retKey: edgeMap.keySet())
			{
				list = edgeMap.get(retKey);
				
				if (retKey == vertexID) // from target vertexID ( simply clear list, excluding 0th element) 
				{
					while (list.size() > 1)
					{
						list.remove(1);
					}
				}
				else
				{
					i = 0;
					while (i < list.size())
					{
						if (list.get(i).id == vertexID)  // curr vertex node points to target vertexID
						{
							list.remove(i);
						}
						else 
						{
							i++;
						}
					}
				}
			}
		}
		
		public boolean removeEdge (String vertexID1, String vertexID2)
		{
			ArrayList<GraphNode> listID1;

			if ( !edgeMap.containsKey(vertexID1) )
			{
				return false;
			}
			
			if ( !edgeMap.containsKey(vertexID2) )
			{
				return false;
			}
			
			// search vertexID1 edgeMap list 
			listID1 = edgeMap.get(vertexID1);
			
			for (int i = 1; i < listID1.size(); i++)
			{
				if (listID1.get(i).id == vertexID2)
				{
					listID1.remove(i);
					break;
				}
			}
			
			return true;
		}
		
		public Integer getEdgeValue (String vertexID1, String vertexID2)
		{
			ArrayList<GraphNode> listID1 = null;

			if ( !edgeMap.containsKey(vertexID1) )
			{
				return null;
			}
			
			if ( !edgeMap.containsKey(vertexID2) )
			{
				return null;
			}
			
			// search vertexID1 edgeMap list 
			listID1 = edgeMap.get(vertexID1);
			
			for (int i = 1; i < listID1.size(); i++)
			{
				if (listID1.get(i).id == vertexID2)
				{
					return listID1.get(i).edgeVal;
				}
			}
			
			return null;
		}
		
		public boolean setEdgeValue (String vertexID1, String vertexID2, int value)
		{
			ArrayList<GraphNode> listID1 = null;

			if ( !edgeMap.containsKey(vertexID1) )
			{
				return false;
			}
			
			if ( !edgeMap.containsKey(vertexID2) )
			{
				return false;
			}
			
			// search vertexID1 edgeMap list 
			listID1 = edgeMap.get(vertexID1);
			
			for (int i = 1; i < listID1.size(); i++)
			{
				if (listID1.get(i).id == vertexID2)
				{
					listID1.get(i).edgeVal = value;
					break;
				}
			}
			
			return true;
		}
		
		public boolean adjacent (String vertexID1, String vertexID2) 
		{
			ArrayList<GraphNode> listID1 = null;

			if ( !edgeMap.containsKey(vertexID1) )
			{
				return false;
			}
			
			if ( !edgeMap.containsKey(vertexID2) )
			{
				return false;
			}
			
			listID1 = edgeMap.get(vertexID1);
			
			for (int i = 1; i < listID1.size(); i++)
			{
				if (listID1.get(i).id == vertexID2)
				{
					return true;
				}
			}
			
			return false;
		}
		
		public String[] neighbors (String vertexID) 
		{
			String[] arr = {};
			ArrayList<GraphNode> listID1;
			int i = 0;
			
			if ( !edgeMap.containsKey(vertexID) )
			{
				return arr;
			}
			
			listID1 = edgeMap.get(vertexID);
	
			arr = new String[listID1.size() - 1];
			for (int k = 1; k < listID1.size(); k++)
			{
				arr[i++] = listID1.get(k).id;
			}
			return arr;
		}

	}
	
	public static  class AMGraph 
	{
		private int id;
		int[][] map;	
		HashMap<String /*vertex id*/, String /*vertex value*/ > vertexMap;	

		AMGraph ()
		{
			map = null;
			vertexMap = new HashMap<String , String >();
			id = 0;
		}
		
		public String addVertex (String value)
		{
			String currID;
			currID = String.valueOf(id++);

			int[][] newMap  = new int [id][id];
			
			if (map != null) 
			{
				for (int r = 0; r < newMap.length; r++)
				{
					for (int c = 0; c < newMap.length; c++)
					{
						if (r < map.length && c < map.length)
						{
							newMap[r][c] = map[r][c];
						}
						else 
						{
							newMap[r][c] = -1;
						}
					}
				}
				map = newMap;
			}
			
			if (map == null)
			{
				map  = newMap;
			}
			
			
			vertexMap.put(currID, value);

			return currID;
		}
		
		public boolean removeVertex(String vertexID)
		{
			if ( !vertexMap.containsKey(vertexID) )
			{
				return false;
			}
			vertexMap.remove(vertexID);
			return true;
		}
		
		public String getVertexValue (String vertexID)
		{
			if (!vertexMap.containsKey(vertexID) )
			{
				return null;
			}
			return vertexMap.get(vertexID);
		}
		
		public boolean setVertexValue (String vertexID, String value)
		{
			if (!vertexMap.containsKey(vertexID) )
			{
				return false;
			}
			vertexMap.replace(vertexID, value);
			return true;
		}
		
		public boolean addEdge (String vertexID1, String vertexID2, int value)
		{
			int id1, id2;
			if (!vertexMap.containsKey(vertexID1) || !vertexMap.containsKey(vertexID2) )
			{
				return false;
			}
			
			id1 = Integer.valueOf( vertexID1) ;
			id2 = Integer.valueOf( vertexID2 );
			
			map[id1][id2] = value;
			
			return true;
		}
		
		public void removeEdges(String vertexID)
		{
			int currID;
			
			if ( !vertexMap.containsKey(vertexID) )
			{
				return ;
			}
			
			currID = Integer.valueOf( vertexID );
			
			// columns  (to)
			for (int r = 0; r < map.length; r++)
			{
				map[r][currID] = -1;
			}
			
			// row
			
			for (int c = 0; c < map.length; c++)
			{
				map[currID][c] = -1;
			}
			
		}
		
		public boolean removeEdge(String vertexID1, String vertexID2)
		{
			int id1, id2;

			if ( !vertexMap.containsKey(vertexID1)  || !vertexMap.containsKey(vertexID1))
			{
				return false;
			}
			
			id1 = Integer.valueOf( vertexID1) ;
			id2 = Integer.valueOf( vertexID2 );
			
			map[id1][id2] = -1;

			return true;
		}
		
		public Integer getEdgeValue (String vertexID1, String vertexID2)
		{
			int id1, id2;

			if ( !vertexMap.containsKey(vertexID1)  || !vertexMap.containsKey(vertexID1))
			{
				return null;
			}
			
			id1 = Integer.valueOf( vertexID1) ;
			id2 = Integer.valueOf( vertexID2 );
			
			return map[id1][id2];
		}

		public boolean setEdgeValue (String vertexID1, String vertexID2, int value)
		{
			int id1, id2;

			if ( !vertexMap.containsKey(vertexID1)  || !vertexMap.containsKey(vertexID1))
			{
				return false;
			}
			
			id1 = Integer.valueOf( vertexID1) ;
			id2 = Integer.valueOf( vertexID2 );
			
			map[id1][id2] = value;
			return true;
		}
		
		public boolean adjacent (String vertexID1, String vertexID2)
		{
			int id1, id2;
			if ( !vertexMap.containsKey(vertexID1)  || !vertexMap.containsKey(vertexID1))
			{
				return false;
			}
			id1 = Integer.valueOf( vertexID1) ;
			id2 = Integer.valueOf( vertexID2 );
			return (map[id1][id2] > 0);
		}
		
		public String[] neighbors (String vertexID)
		{
			String[] result = {};
			
			if ( !vertexMap.containsKey(vertexID) )
			{
				return result;
			}
			
			result = new String[ map[Integer.valueOf( vertexID)].length ];
			
			for (int i = 0; i < map[Integer.valueOf( vertexID)].length; i++)
			{
				result[i] = String.valueOf(map[Integer.valueOf( vertexID)][i]);
			}
			
			return result;
		}
		
		public void displayMap ()
		{
			System.out.println("MAP");
			
			if (map != null)
			{
				for (int r = 0; r < map.length; r++)
				{
					for (int c = 0; c < map.length; c++)
					{
						System.out.print(" [" + map[r][c] + "] ");
					}
					System.out.println();
				}
			}
		}
		
		
	}
	
	public static  class ELGraph 
	{
		ArrayList<String[/* fromID , toID, edgeVal*/]> edgeList; 
		HashMap<String /*vertex id*/, String /*vertex value*/ > vertexMap;	
		private int id;
		ELGraph()
		{
			id = 0;
			edgeList = new ArrayList<String[]>();
			vertexMap = new HashMap<String , String> ();
		}
		
		public String addVertex(String value)
		{
			String  currID = String.valueOf(id++);
			
			vertexMap.put(currID, value);
			return currID;
		}
		
		public boolean removeVertex (String vertexID)
		{
			if (vertexMap.containsKey(vertexID) == false)
			{
				return false;
			}
			
			vertexMap.remove(vertexID);
			return true;
		}
		
		public String getVertexValue (String vertexID)
		{
			if (vertexMap.containsKey(vertexID) == false)
			{
				return null;
			}
			
			return vertexMap.get(vertexID);
		}
		
		public boolean getVertexValue (String vertexID, String value)
		{
			if (vertexMap.containsKey(vertexID) == false)
			{
				return false;
			}
			
			vertexMap.replace(vertexID, value);
			return true;
		}
		
		public boolean addEdge (String vertexID1, String vertexID2, int value)
		{
			String[] data = {vertexID1, vertexID2, String.valueOf(value)};
			
			if (vertexMap.containsKey(vertexID1) == false || vertexMap.containsKey(vertexID2) == false)
			{
				return false;
			}
			
			// check list for edge 
			for (String[] retArr: edgeList)
			{
				if (retArr[0] == vertexID1 && retArr[1] == vertexID2)
				{
					retArr[2] = String.valueOf(value);
					return true;
				}
			}
			
			edgeList.add(data);

			return true;
		}
		
		public void removeEdges (String vertexID)
		{
			int i = 0;
			String edgeEntry[];
			
			while (i < edgeList.size())
			{
				edgeEntry = edgeList.get(i);
				if ( vertexID == edgeEntry[0] || vertexID == edgeEntry[1] )
				{
					edgeList.remove(i);
				}
				else
				{
					i++;
				}
			}
		}
		
		public boolean removeEdge (String vertexID1, String vertexID2)
		{
			if (vertexMap.containsKey(vertexID1)  && vertexMap.containsKey(vertexID2))
			{
				for (int i = 0; i < edgeList.size(); i++)
				{
					if ( vertexID1 == edgeList.get(i)[0] || vertexID2 == edgeList.get(i)[1] )
					{
						edgeList.remove(i);
						return true;
					}
				}			
			}
			return false;
		}
		
		public Integer getEdgeValue (String vertexID1, String vertexID2)
		{
			if (vertexMap.containsKey(vertexID1)  &&vertexMap.containsKey(vertexID2))
			{
				for (int i = 0; i < edgeList.size(); i++)
				{
					
					if ( vertexID1 == edgeList.get(i)[0] || vertexID2 == edgeList.get(i)[1] )
					{
						return  Integer.valueOf( edgeList.get(i)[2] )  ;
					}
					
				}			
			}
			return null;
		}
		
		public boolean setEdgeValue (String vertexID1, String vertexID2, int value)
		{
			if (vertexMap.containsKey(vertexID1)  && vertexMap.containsKey(vertexID2))
			{
				for (int i = 0; i < edgeList.size(); i++)
				{
					if ( vertexID1 == edgeList.get(i)[0] || vertexID2 == edgeList.get(i)[1] )
					{
						edgeList.get(i)[2]  = String.valueOf(value);
						return true;
					}
					
				}			
			}
			return false;
		}
		
		public boolean adjacent (String vertexID1, String vertexID2)
		{
			for (int i = 0; i < edgeList.size(); i++)
			{
				if ( vertexID1 == edgeList.get(i)[0] || vertexID2 == edgeList.get(i)[1] )
				{
					return true;
				}
			}	
			return false;
		}
		
		public ArrayList<String> neighbors (String vertexID)
		{
			ArrayList<String> result = new ArrayList<String>();
			
			if (!vertexMap.containsKey(vertexID ))
			{
				return result;
			}
			
			for (int i = 0; i < edgeList.size(); i++)
			{
				if ( vertexID == edgeList.get(i)[0] || vertexID == edgeList.get(i)[1] )
				{
					result.add(String.valueOf( edgeList.get(i)[2] ) );
				}
			}	
			
			return result;
		}
	}
	
	public static boolean someoneOnInsider(ALGraph undirgraph, String myVertexID, String[] vertexIDs)
	{
		HashSet<String> visited = new HashSet<String>();
		ArrayList<GraphNode> stackLite = new ArrayList<GraphNode>();	
		GraphNode node;
		
		if (undirgraph.edgeMap.containsKey(myVertexID) == false)
		{
			return false;
		}
		
		// search my connections
		for ( int i = 1; i < undirgraph.edgeMap.get( myVertexID ).size(); i++ )
		{
			stackLite.clear();
			stackLite.add(undirgraph.edgeMap.get( myVertexID ).get(i));
			
			while (!stackLite.isEmpty()) 
			{
				node = stackLite.remove(0);
				
				// add node's edges to list
				// add
			}
			
			
		}
		return false;
	}
	
	public static String someoneOnInsiderV2(ALGraph undirgraph, String myVertexID, String[] vertexIDs)
	{
		String contactINfo = "";
		
		return contactINfo;
	}
	
	public static boolean vertexIsReachable (ALGraph ugraph, String vertexID1, String vertexID2)
	{
		
		return false;
	}
	
}
