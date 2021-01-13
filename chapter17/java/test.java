package algo;
import algo.Chapter17.*;

public class Test 
{
	public static void ALGraphTest ()
	{
		ALGraph graph = new ALGraph();
		String[] newVertexID  = { "A", "B", "C", "D", "E", "F"};
		
		String firstId = graph.addVertex(newVertexID[0]);
		String secondId = graph.addVertex(newVertexID[1]);
		String thirdId = graph.addVertex(newVertexID[2]);
		String fourId = graph.addVertex(newVertexID[3]);
		String fifthId = graph.addVertex(newVertexID[4]);
		String sixthId = graph.addVertex(newVertexID[5]);

		System.out.println(" removed vertex \"duck\" -> " + graph.removeVertex("duck"));
		System.out.println(" removed vertex " + sixthId + " -> " + graph.removeVertex(sixthId));
		System.out.println(" get value at vertex " + firstId + " -> " + graph.getVertexValue(firstId));
		System.out.println(" get value at vertex " + fifthId + " -> " + graph.getVertexValue(fifthId));
		System.out.println(" add edge " + firstId + " to " + secondId  + " " + graph.addEdge(firstId,secondId, 100 ));
		System.out.println(" read edge " + firstId + " to " + secondId  + " " + graph.getEdgeValue(firstId,secondId ));
		System.out.print(" adjacency list " + firstId + ": " );
		for (String retString: graph.neighbors(firstId))
		{
			System.out.print(" [ " + retString + " ] ");
		}
		System.out.println();
	}
	
	public static void AMGraphTest ()
	{
		AMGraph graph = new AMGraph();
		String[] newVertexID  = { "A", "B", "C", "D", "E", "F"};
		
		String firstId = graph.addVertex(newVertexID[0]);
		String secondId = graph.addVertex(newVertexID[1]);
		String thirdId = graph.addVertex(newVertexID[2]);
		String fourId = graph.addVertex(newVertexID[3]);
		String fifthId = graph.addVertex(newVertexID[4]);
		String sixthId = graph.addVertex(newVertexID[5]);
		System.out.println(" removed vertex \"duck\" -> " + graph.removeVertex("duck"));
		System.out.println(" removed vertex " + sixthId + " -> " + graph.removeVertex(sixthId));
		System.out.println(" get value at vertex " + firstId + " -> " + graph.getVertexValue(firstId));
		System.out.println(" add edge " + firstId + " to " + secondId  + " " + graph.addEdge(firstId,secondId, 100 ));
		System.out.println(" read edge " + firstId + " to " + secondId  + " " + graph.getEdgeValue(firstId,secondId ));
		System.out.println(" set edge " + firstId + " to " + secondId  + "  400" + graph.setEdgeValue(firstId,secondId, 400 ));
		System.out.print(" adjacency list " + firstId + ": " );
		for (String retVal: graph.neighbors(firstId))
		{
			System.out.print(" [ " + retVal + " ] ");
		}
		System.out.println();
		graph.displayMap();

	}
	
	public static void ELGraphTest ()
	{
		ELGraph graph = new ELGraph();
		String[] newVertexID  = { "A", "B", "C", "D", "E", "F"};
		String firstId = graph.addVertex(newVertexID[0]);
		String secondId = graph.addVertex(newVertexID[1]);
		String thirdId = graph.addVertex(newVertexID[2]);
		String fourId = graph.addVertex(newVertexID[3]);
		String fifthId = graph.addVertex(newVertexID[4]);
		String sixthId = graph.addVertex(newVertexID[5]);
		
		System.out.println(" removed vertex \"duck\" -> " + graph.removeVertex("duck"));
		System.out.println(" removed vertex " + sixthId + " -> " + graph.removeVertex(sixthId));
		System.out.println(" get value at vertex " + firstId + " -> " + graph.getVertexValue(firstId));
		System.out.println(" add edge " + firstId + " to " + secondId  + " " + graph.addEdge(firstId,secondId, 100 ));
		System.out.println(" read edge " + firstId + " to " + secondId  + " value = " + graph.getEdgeValue(firstId, secondId ) );
		System.out.println(" set edge " + firstId + " to " + secondId  + "  400" + graph.setEdgeValue(firstId,secondId, 400 ));
		System.out.print(" adjacency to vertexID " + firstId + ": " );
		for (String retVal: graph.neighbors(firstId))
		{
			System.out.print(" [ " + retVal + " ] ");
		}
		System.out.println();
	}
	
	public static void main(String args[])
	{
		ELGraphTest();
	}
}  
