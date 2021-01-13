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
	
	public static String someoneOnInsider(ALGraph undirgraph, String myVertexID, String[] companyVertexIDList)
	{
		HashSet<String> visited = new HashSet<String>();
		ArrayList<GraphNode> stackLite = new ArrayList<GraphNode>();	
		GraphNode producerNode, consumerNode;
		
		if (!undirgraph.edgeMap.containsKey(myVertexID))
		{
			return "Insider: none";
		}
		
		for ( int i = 0; i < companyVertexIDList.length; i++ ) // iterate company id(vertex) list
		{
			stackLite.clear();
			
			if (!undirgraph.edgeMap.containsKey(companyVertexIDList[i])) // employee not in my social network?
			{
				continue;
			}
			
			if (myVertexID.compareTo(companyVertexIDList[i]) == 0 ) // myVertexID cannot be an employee
			{
				continue;
			}
			
			stackLite.add(undirgraph.edgeMap.get(companyVertexIDList[i]).get(0)); 	// add employee(from company list) node to stack 
			
			while (!stackLite.isEmpty()) 
			{				
				producerNode = stackLite.remove(0);
				
				if (visited.contains(producerNode.id))
				{
					continue;
				}
				
				visited.add(producerNode.id);
				
				for (int k = 1; k < undirgraph.edgeMap.get(producerNode.id).size(); k++)  //iterate node (employee's) connections
				{
					consumerNode = undirgraph.edgeMap.get(producerNode.id).get(k);
					
					// employee at company knows me!
					if ( consumerNode.id == myVertexID )  // consumer(MY node) <- producer(Employee node)
					{
						return "Insider: " + producerNode.id;
					}
					stackLite.add(0,  consumerNode );  
				}
			}
		}
		return "Insider: none";
	}
	
	public static String someoneOnInsiderSecond(ALGraph undirgraph, String myVertexID, String[] companyVertexIDList)
	{
		GraphNode producerNode, consumerNode;
		String msg = "Contact: None, Insider: None";
		HashSet<String> visited = new HashSet<String>();
		ArrayList<GraphNode> stackLite = new ArrayList<GraphNode>();	
		
		/* 
		 * optimization: Add company IDs to Set variable visited
		 */
		 
		for (String retString: companyVertexIDList)
		{
			visited.add(retString);
		}
		
		if (!undirgraph.edgeMap.containsKey(myVertexID))
		{
			return msg;
		}
		
		// search social network graph
		stackLite.add(undirgraph.edgeMap.get(myVertexID).get(0)); // start search from myVertexID		
		
		while (!stackLite.isEmpty()) 
		{				
			producerNode = stackLite.remove(0);
			
			if (visited.contains(producerNode.id))
			{
				continue;
			}
			
			visited.add(producerNode.id);

			for (int k = 1; k < undirgraph.edgeMap.get(producerNode.id).size(); k++) 
			{
				consumerNode = undirgraph.edgeMap.get(producerNode.id).get(k);
				
				// someone in my social network knows someone in the company
				if ( visited.contains(consumerNode.id))  // producer(node in my social network ) -> consumer(Employee node)
				{
					return "Contact: " + producerNode.id +  "Insider: " + consumerNode.id ;

				}
				stackLite.add(0, consumerNode ); 
			}
		}
		
		return msg;
	}
	
	public static ArrayList<String> vertexIsReachable (ALGraph ugraph, String vertexID1, String vertexID2)
	{
		GraphNode producerNode, consumerNode;
		HashSet<String> visited = new HashSet<String>();
		ArrayList<String> path = new ArrayList<String>();
		ArrayList<GraphNode> stackNodes = new ArrayList<GraphNode>();	
		
		if (!ugraph.edgeMap.containsKey(vertexID1))
		{
			return path;
		}
		
		// root data
		stackNodes.add(ugraph.edgeMap.get(vertexID1).get(0)); // add adjacent node to stack

		while (!stackNodes.isEmpty()) 
		{				
			producerNode = stackNodes.remove(0);
			
			if (visited.contains(producerNode.id))
			{
				continue;
			}
			
			visited.add(producerNode.id);
			path.add(producerNode.id);
			
			if (producerNode.id.compareTo(vertexID2) == 0 )
			{
				return path;
			}

			for (int k = 1; k < ugraph.edgeMap.get(producerNode.id).size(); k++) 
			{
				consumerNode = ugraph.edgeMap.get(producerNode.id).get(k);
				
				stackNodes.add(0, consumerNode ); 
			}
		}
		
		path.clear();
		
		return path;
	}
	
	public static ArrayList<ArrayList<String>> allPaths (ALGraph ugraph, String vertexID1, String vertexID2)
	{
		ArrayList<String> currWalk, copyWalk;
		GraphNode producerNode, consumerNode = null;	
		HashSet<String> visited = new HashSet<String>();
		ArrayList<GraphNode> stackNodes = new ArrayList<GraphNode>();	
		ArrayList<ArrayList<String>> stackPaths = new ArrayList<ArrayList<String>>();	
		ArrayList<ArrayList<String>> allPaths = new ArrayList<ArrayList<String>>();
		
		if (!ugraph.edgeMap.containsKey(vertexID1))
		{
			return allPaths;
		}
		
		// root data
		stackNodes.add( ugraph.edgeMap.get(vertexID1).get(0));
		stackPaths.add(new ArrayList<String>());
		
		// search and load paths
		while (!stackNodes.isEmpty())
		{
			producerNode = stackNodes.remove(0);
			currWalk = stackPaths.remove(0);
			
			if (!currWalk.isEmpty())
			{
				if (producerNode.id.compareTo(vertexID2) == 0) // traversed vertexID2 node 
				{
					currWalk.add(producerNode.id); // add end id to list
					allPaths.add(currWalk); // add path to list  
					continue;
				}
			} 
			
			if (visited.contains(producerNode.id))
			{
				continue;
			}
			
			visited.add(producerNode.id);
			currWalk.add(producerNode.id);
			
			for (int k = 1; k < ugraph.edgeMap.get(producerNode.id).size(); k++) 
			{
				//copy current walked(i.e. traversed) path  
				copyWalk = new ArrayList<String>();
				for (String retVal: currWalk)
				{
					copyWalk.add(retVal);
				}
				
				consumerNode = ugraph.edgeMap.get(producerNode.id).get(k);
				
				stackNodes.add(0, consumerNode);
				stackPaths.add(0, copyWalk);
			}
		}
		
		return allPaths;
	}
	
	public static ArrayList<String> shortestPath (ALGraph ugraph, String vertexID1, String vertexID2)
	{
		ArrayList<String> currWalk, copyWalk, path;
		GraphNode producerNode, consumerNode;	
		HashSet<String> visited = new HashSet<String>();
		ArrayList<GraphNode> queueNodes = new ArrayList<GraphNode>();	
		ArrayList<ArrayList<String>> queuePaths = new ArrayList<ArrayList<String>>();	

		if (!ugraph.edgeMap.containsKey(vertexID1))
		{
			return null;
		}
		
		path = null;
		currWalk = new ArrayList<String>();
		producerNode = ugraph.edgeMap.get(vertexID1).get(0);
		
		queueNodes.add(producerNode);
		queuePaths.add(currWalk);
		
		while ( !queueNodes.isEmpty() )
		{
			producerNode = queueNodes.remove(0);
			currWalk = queuePaths.remove(0);
			
			currWalk.add(producerNode.id);
			
			if (!visited.contains(producerNode.id))
			{
				visited.add(producerNode.id);
				queueNodes.add(producerNode);
				
				if (producerNode.id == vertexID2) // first(shortest) valid path!!
				{
					return currWalk;
				}
				
				for (int i = 1; i < ugraph.edgeMap.get(producerNode.id).size(); i++ ) 
				{
					copyWalk = new ArrayList<String>();
					for (String retString : currWalk)
					{
						copyWalk.add(retString);
					}
					
					consumerNode = ugraph.edgeMap.get(producerNode.id).get(i);
					
					queueNodes.add(consumerNode);
					queuePaths.add(copyWalk);
				}	
			}
			
		}
		
		return path;
	}
	
	public static ArrayList<String> gimmieThreeSteps (ALGraph ugraph, String vertexID)
	{
		GraphNode node = null;	
		HashSet<String> visited = new HashSet<String>();
		ArrayList<String> idList = new ArrayList<String>();
		ArrayList<GraphNode> queueLite = new ArrayList<GraphNode>();
		ArrayList<GraphNode> nextLayer = new ArrayList<GraphNode>();	
		int layer = 0;
		
		if (!ugraph.edgeMap.containsKey(vertexID))
		{
			return idList;
		}
		
		queueLite.add( ugraph.edgeMap.get(vertexID).get(0) );
		
		while (!queueLite.isEmpty() && layer < 3)
		{
			node = queueLite.remove(0);
			
			if (visited.contains(node.id))
			{
				continue;
			}
			
			visited.add(node.id);

			for (int i = 1; i < ugraph.edgeMap.get(node.id).size(); i++ ) 
			{
				node = ugraph.edgeMap.get(vertexID).get(i);
				nextLayer.add(node);
				idList.add(node.id);
			}
			
			if (queueLite.isEmpty()) 
			{
				queueLite  = nextLayer;
				nextLayer =  new ArrayList<GraphNode>();
				layer++;
			}
		}
		
		while (!nextLayer.isEmpty())  // nextLayer array not empty !
		{
			idList.add(nextLayer.remove(0).id);
		}
		
		return idList;
	}
	
	public static ArrayList<String> easyToGetThere (ALGraph dirgraph)
	{
		GraphNode node, consumerNode, producerNode;	
		HashSet<String> visited = new HashSet<String>();
		ArrayList<String> vertices = new ArrayList<String>();
		ArrayList<GraphNode> queueLite = new ArrayList<GraphNode>();	
		HashMap<String, int[]> table = new HashMap<String, int[]>();
		
		for (String currID: dirgraph.edgeMap.keySet())
		{
			queueLite.clear();
			
			producerNode = dirgraph.edgeMap.get(currID).get(0);
			queueLite.add(producerNode);  
			
			while (!queueLite.isEmpty())
			{
				node = queueLite.remove(0);
				
				if (visited.contains(node.id))
				{
					continue;
				}
				
				visited.add(node.id);

				for (int k = 1; k < dirgraph.edgeMap.get(node.id).size(); k++) 
				{
					consumerNode = dirgraph.edgeMap.get(node.id).get(k);
					
					if (!table.containsKey(consumerNode.id)) 
					{
						table.put(consumerNode.id, new int[2]);
					}
					
					table.get(consumerNode.id)[1]++; // increment incoming edge 
					
					queueLite.add(consumerNode);
				}
			}
		}
		
		for ( String producerID: dirgraph.edgeMap.keySet())
		{
			producerNode = dirgraph.edgeMap.get(producerID).get(0);
			
			if (!table.containsKey(producerNode.id))
			{
				table.put(producerNode.id, new int[2]);
			}
			
			table.get(producerNode.id)[0] = dirgraph.edgeMap.get(producerNode.id).size() - 1 ; // 0th placeholder is not available  ( outgoing edge size )
			
			if (table.get(producerNode.id)[1] > table.get(producerNode.id)[0])
			{
				vertices.add(producerNode.id);
			}
		}
		
		return vertices;
	}
	
	public static boolean isDAG (ALGraph graph)
	{
		boolean hasHead, hasTail;
		GraphNode consumerNode, producerNode, node;	
		HashSet <String> removedTable = new HashSet<String>();
		HashMap<String, int[]> table = new HashMap<String, int[]>();
		
		for (String vertexID: graph.edgeMap.keySet())
		{
			if (removedTable.contains(vertexID)) // vertex does not have single incoming/outgoing edges
			{
				return false;
			}
			
			producerNode = graph.edgeMap.get(vertexID).get(0);
			
			if (!table.containsKey(producerNode.id))
			{
				table.put(producerNode.id, new int[2]);
			}
			
			table.get(producerNode.id)[0]++; //outgoing count
			
			if (table.get(producerNode.id)[0] > 1) // too many outputs from producer node
			{
				return false;
			}
			
			if( table.get(producerNode.id)[0] == 1 && table.get(producerNode.id)[1] == 1)
			{
				removedTable.add(producerNode.id);
			}
			
			for (int i = 1; i < graph.edgeMap.get(producerNode.id).size(); i++)
			{
				consumerNode = graph.edgeMap.get(producerNode.id).get(i);
				
				if (!table.containsKey(consumerNode.id))
				{
					table.put(consumerNode.id, new int[2]);
				}
				
				table.get(consumerNode.id)[1]++; // incoming count
				
				if (table.get(consumerNode.id)[1] > 1) // too many inputs to consumer node
				{
					return false;
				}
				
				if( table.get(consumerNode.id)[0] == 1 && table.get(consumerNode.id)[1] == 1)
				{
					removedTable.add(consumerNode.id);
				}
			}
		}
		
		// expect two vertexID leftover in table
		
		hasHead = hasTail = false;
		
		if (table.size() == 2)
		{
			for (String vertexID: table.keySet())
			{
				node = graph.edgeMap.get(vertexID).get(0);
				
				if( table.get(node.id)[0] == 1 && table.get(node.id)[1] == 0)
				{
					producerNode = node;
					hasHead = !hasHead;
				}
				
				if( table.get(node.id)[0] == 0 && table.get(node.id)[1] == 1)
				{
					consumerNode = node;
					hasTail = !hasTail;
				}
			}
		}
		
		return hasHead && hasTail;
	}
	
	/* assumes input parameter is valid DAG*/
	public static ArrayList<String> DAGToArray (ALGraph graphDAG)  
	{
		ArrayList<String> array;	
		GraphNode consumerNode, producerNode, node;	
		ArrayList<GraphNode> stackNodes;	
		HashMap<String, int[]> table;
		
		producerNode = consumerNode = null;
		table = new HashMap<String, int[]>();
		stackNodes = new ArrayList<GraphNode>();
		
		for (String vertexID: graphDAG.edgeMap.keySet())
		{
			producerNode = graphDAG.edgeMap.get(vertexID).get(0);
			
			if (!table.containsKey(producerNode.id))
			{
				table.put(producerNode.id, new int[2]);
			}
			
			table.get(producerNode.id)[0]++; //outgoing count
			
			if( table.get(producerNode.id)[0] == 1 && table.get(producerNode.id)[1] == 1)  // single incoming/outgoing edges
			{
				table.remove(producerNode.id);
			}
			
			for (int i = 1; i < graphDAG.edgeMap.get(producerNode.id).size(); i++)
			{
				consumerNode = graphDAG.edgeMap.get(producerNode.id).get(i);
				
				if (!table.containsKey(consumerNode.id))
				{
					table.put(consumerNode.id, new int[2]);
				}
				
				table.get(consumerNode.id)[1]++; // incoming count
				
				if( table.get(consumerNode.id)[0] == 1 && table.get(consumerNode.id)[1] == 1)  // single incoming/outgoing edges
				{
					table.remove(consumerNode.id);
				}
			}
		}
		
		for (String vertexID: table.keySet())
		{
			node = graphDAG.edgeMap.get(vertexID).get(0);
			if( table.get(node.id)[0] == 1 && table.get(node.id)[1] == 0)
			{
				stackNodes.add(node);
			}
		}
		
		// load array 
		array = new ArrayList<String>();
		while (!stackNodes.isEmpty())
		{
			producerNode = stackNodes.remove(0);
			array.add(producerNode.id);
			
			if (graphDAG.edgeMap.get(producerNode.id).size() - 1 == 1)
			{
				consumerNode = graphDAG.edgeMap.get(producerNode.id).get(1);
				stackNodes.add(consumerNode);
			}
		}
		
		return array;
	}
}
