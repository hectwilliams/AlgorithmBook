package algo;
import algo.Chapter5.*;

public class Chapter8 {
	
	public static class SList
	{
		Node head;
		
		SList() 
		{
			head = null;
		}
		
		public void pushFront (int value) 
		{
			head = Chapter5.addFront(head, value);
		}
		
		public Integer popFront () 
		{
			Integer result = null;
			if (head != null)
			{
				result = head.value;
				head = head.next;
			}
			return result;
		}
		
		public boolean contains (int value) 
		{
			return Chapter5.contains(head, value);
		}
		
		public void removeVal (int value) 
		{
			head = Chapter5.removeVal(head, value);
		}
		
		public Integer back (int value) 
		{
			return Chapter5.back(head);
		}
		
		public void pushBack (int value) 
		{
			 Chapter5.addBack(head, value);
		}
		
		public Integer popBack () 
		{
			Integer result = null;
			Node runner = head, runnerPrev = null;
			
			while (runner.next != null) 
			{
				runnerPrev = runner;
				runner = runner.next;
			}
			
			if (runner != null) 
			{
				result = runner.value;
				runnerPrev.next = null;
			}
						
			return result;
		}
		
		public void display()
		{
			Chapter5.display(head);
		}
		
	}
}
