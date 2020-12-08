package algo;

import algo.Chapter6.*;

public class Test {
	public static void main(String[] args)
	{
		Queue listQueue1 = new Queue();
		listQueue1.enqueue(1);
		listQueue1.enqueue(2);
		Queue listQueue2 = new Queue();
		listQueue2.enqueue(1);
		listQueue2.enqueue(2);
		listQueue2.enqueue(2);

		listQueue1.debugDisplay();
		listQueue2.debugDisplay();
		
		System.out.print( Chapter6.compareQueues ( listQueue1, listQueue2) ); //  is it equal 
		System.out.println("");

		listQueue1.enqueue(89);
		listQueue1.enqueue(1);
		listQueue1.enqueue(6);
		listQueue1.enqueue(1212);
		listQueue1.enqueue(1);
		listQueue1.enqueue(3);
		listQueue1.enqueue(4);
		listQueue1.enqueue(5);
		listQueue1.debugDisplay(); // 1,2,89,1,6,1212,1,3,4,5,
		System.out.println("");
		Chapter6.removeMinimums (listQueue1);
		listQueue1.debugDisplay(); // 1,2,89,6,1212,3,4,5,
		
		Chapter6.interleaveQueue(listQueue1);
		listQueue1.debugDisplay(); //  1,1212,2,3,89,4,6,
		System.out.println("");
		System.out.println("");

		Stack  stack1 = new Stack();
		stack1.push(1);
		stack1.push(2);
		Stack  stack2 = new Stack();
		stack2.push(1);
		stack2.push(2);
		System.out.println( Chapter6.compareStacks ( stack1, stack2) ); //  is it equal 
		
		stack1.push(3);
		stack1.push(4);

		stack1.debugDisplay(); // 4, 3, 2, 1
		Stack  copyStack = Chapter6.copyStack(stack1);
		copyStack.debugDisplay(); //   4, 3, 2, 1
		
		TwoStackQueue stack0 = new TwoStackQueue();
		stack0.enqueue(1); 
		stack0.enqueue(2); 
		stack0.enqueue(4); 
		stack0.enqueue(5);
		System.out.println(stack0.dequeue()); // 1
		stack0.enqueue(10);
		stack0.enqueue(12);
		System.out.println(stack0.dequeue()); // 2
		System.out.println(stack0.dequeue()); // 4
		System.out.println(stack0.dequeue()); //  5
		System.out.println(stack0.dequeue()); // 10
		System.out.println(stack0.dequeue()); // 12
		System.out.println("");
		Queue listQueue3 = new Queue();
		listQueue3.enqueue(2);
		listQueue3.enqueue(4);
		listQueue3.enqueue(200);
		listQueue3.enqueue(4);
		listQueue3.enqueue(2);
		
		Stack  stackx = new Stack();
		stackx.push(2);
		stackx.push(20);
		stackx.push(33);
		stackx.push(4);
		stackx.push(10);
		stackx.push(11);
		stackx.push(2);
		stackx.push(6);

		Chapter6.removeOldestStackMin(stackx);
		System.out.println ( stackx.pop() ) ; // 6
		System.out.println ( stackx.pop() ) ; // 2
		System.out.println ( stackx.pop() ) ; // 11
		System.out.println ( stackx.pop() ) ; // 10
		System.out.println ( stackx.pop() ) ; // 4
		System.out.println ( stackx.pop() ) ; // 33
		System.out.println ( stackx.pop() ) ; // 20
		System.out.println("");
		System.out.println("");

		
		Queue reorderThisQueue = new Queue();

		reorderThisQueue.enqueue(10);
		reorderThisQueue.enqueue(-20);
		reorderThisQueue.enqueue(30);
		reorderThisQueue.enqueue(-40);
		reorderThisQueue.enqueue(50);
		
		Chapter6.reorderAbsoluteQueue(reorderThisQueue);
		System.out.println(reorderThisQueue.dequeue()); //  -40
		System.out.println(reorderThisQueue.dequeue()); //  -20 
		System.out.println(reorderThisQueue.dequeue()); //  10 
		System.out.println(reorderThisQueue.dequeue()); //  30 
		System.out.println(reorderThisQueue.dequeue()); //  50
		System.out.println("");

		
//		System.out.println ( Chapter6.isPalindrome(listQueue3) ) ;
		Stack  stackparition = new Stack();
		stackparition.push(0);
		stackparition.push(-1);
		stackparition.push(2);
		stackparition.push(3);
		stackparition.push(99);
		stackparition.push(7);
		stackparition.push(-2);
		stackparition.push(3);
		Chapter6.partition(stackparition);

		System.out.println ( stackparition.pop() ) ; // 6
		System.out.println ( stackparition.pop() ) ; // 2
		System.out.println ( stackparition.pop() ) ; // 11
		System.out.println ( stackparition.pop() ) ; // 10
		System.out.println ( stackparition.pop() ) ; // 4
		System.out.println ( stackparition.pop() ) ; // 33
		System.out.println ( stackparition.pop() ) ; // 20
		System.out.println("");
		System.out.println("");

		Stack  stack_switchpairs = new Stack();
		stack_switchpairs.push(7);
		stack_switchpairs.push(6);
		stack_switchpairs.push(5);
		stack_switchpairs.push(4);
		stack_switchpairs.push(3);
		stack_switchpairs.push(2);
		stack_switchpairs.push(1);
		Chapter6.switchPairs(stack_switchpairs);

		System.out.println ( stack_switchpairs.pop() ) ; // 6
		System.out.println ( stack_switchpairs.pop() ) ; // 7
		System.out.println ( stack_switchpairs.pop() ) ; // 4
		System.out.println ( stack_switchpairs.pop() ) ; // 5
		System.out.println ( stack_switchpairs.pop() ) ; // 2
		System.out.println ( stack_switchpairs.pop() ) ; // 3
		System.out.println ( stack_switchpairs.pop() ) ; // 1
		System.out.println("");
		System.out.println("");
		
		Stack  stack_issorted = new Stack();
		stack_issorted.push(7);
		stack_issorted.push(6);
		stack_issorted.push(5);
		stack_issorted.push(4);
		stack_issorted.push(5);
		System.out.print( Chapter6.isSorted(stack_issorted) ) ;

		Stack stack_mirror= new Stack();
		stack_mirror.push(7);
		stack_mirror.push(5);
		stack_mirror.push(3);
		stack_mirror.push(1);
		Chapter6.mirror(stack_mirror);
		System.out.println("");

		System.out.println ( stack_mirror.pop() ) ; // 1
		System.out.println ( stack_mirror.pop() ) ; // 3
		System.out.println ( stack_mirror.pop() ) ; // 5
		System.out.println ( stack_mirror.pop() ) ; // 7
		System.out.println ( stack_mirror.pop() ) ; // 7
		System.out.println ( stack_mirror.pop() ) ; // 5
		System.out.println ( stack_mirror.pop() ) ; // 3
		System.out.println ( stack_mirror.pop() ) ; // 1
		System.out.println("");
		
		System.out.println(Chapter6.weakFinger(2,1));


	}

	
}

