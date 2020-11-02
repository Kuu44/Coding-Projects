import java.util.Scanner;

public class Project2Main {

	public static void main (String[] args) {
		int gridSize = 8;

		//valid moves
		int[][] moves
		= {
				{-2,-1},
				{-2,1},
				{-1,2},
				{1,2},
				{2,1},
				{2,-1},
				{1,-2},
				{-1,-2}
		};

		//Getting input
		int[] input=getInput(gridSize, true);
		Node start=new Node(input[0],input[1]);
		input=getInput(gridSize, false);
		Node end=new Node(input[0],input[1]);

		//Calculating path
		Queue finalPath=new Queue();
		finalPath.enqueue(start);

		Node current=start;
		while(!end.isEqual(current)) {
			current=getNextMove(current.getPossibleMoveNodes(finalPath,moves,gridSize),end);					
			finalPath.enqueue(current);
		}		

		//Printing answer
		System.out.println("\nFound Path");
		finalPath.print();
	}
	static boolean isInside (int x, int y, int N) 
	{
		if(x>=0 && x<N) { 			
			if(y>=0 && y<N) {
				return true;
			}
			else {
				System.out.println("\nThe row must be between 0 and 7. Try again.");
				return false;
			}
		}
		else {
			System.out.println("\nThe column must be between 0 and 7. Try again.");
			return false;
		}
	}
	static int[] getInput(int N, boolean start) {
		//start tells if this is the first input or not

		int x = 0;
		int y = 0;
		Scanner in = new Scanner(System.in);

		boolean ValidInput = false;
		while(!ValidInput) 	{
			if(start)
				System.out.println("\nInput the starting row and column separated by a space:");
			else
				System.out.println("\nInput the final row and column separated by a space:");
			String input = in.nextLine();
			String[] inputArray = input.split(" "); 
			if (inputArray.length !=2) { 
				System.out.println("\nInvalid input, try again");	
				continue;
			}				
			x=Integer.parseInt(inputArray[0]);
			y=Integer.parseInt(inputArray[1]);	
			//System.out.println("\nU typed:"+x+" n "+y);
			if(isInside(x,y,N)) 
				ValidInput=true; 
		}
		//System.out.println("\nAccepted!");
		int[] result= {x,y};
		return result;
	}
	static Node getNextMove(Queue validNodes, Node end) {

		//checks all valid nodes and returns one with shortest distance to final

		Node validNode=validNodes.dequeue();

		while(!validNodes.isEmpty()) {
			Node nodeToCheck=validNodes.dequeue();

			if(nodeToCheck.distanceFrom(end)<validNode.distanceFrom(end)) 
				validNode=nodeToCheck;						
		}

		return validNode;
	}	
}

