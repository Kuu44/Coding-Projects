/* Name: Prathana Thapa
 * Project 2
 */

import java.util.Scanner;

public class ConnectFour
{
	//i = row, j = column
	public static void main (String[] args)
	{	
		Scanner input = new Scanner(System.in);
		boolean playAgain=true;
		
		while(playAgain) 
		{
			char[][] board = new char[6][7];
			int noOfDisk = 0;
			char color;
			String player=" ";
		    int disk;
		    fillBoard(board);
		    int column=0;
		    
			while (isWinner(board) == false && noOfDisk != 6 * 7) 
			{	
				printBoard(board);
								
				boolean incorrectInput=true;
			    while(incorrectInput) {
			    	
			    	column = input.nextInt();
			    	
			    	for(int i=0;i<7;i++) 
			    	{
			    		if(column==i) 
			    		{
			    			incorrectInput=false;
			    			break;
			    		}
				    }
			    	if(incorrectInput) 
			    	{
			    		System.out.println("YOU ENTERED AN INVALID INTEGER OR" + 
			    				" THE COLUMN IS FULL.");
			    	}
			    }
				
				if ( noOfDisk % 2 == 0)
				{
					color = 'Y';
					 player = "Y";
				}
				else 
				{
					color = 'R';
					player = "R";
				}
				noOfDisk++;
				
				System.out.print("");				
			   	
				dropDisk(board,column,color);		
			}
			
		    if(isWinner(board)) 
		    {
		    	printBoard(board);
		     System.out.println(player + " has WON the game!");	      
		    }
		    else 
		    {
		     System.out.println("I declare a draw");
		    }
		    
		    System.out.println( "DO YOU WANT TO PLAY A NEW GAME? (type 1 for yes)");
		    
		   
		    
		    boolean incorrectInput=true;
		    
		    while(incorrectInput) {
		    	int answer=input.nextInt();
			    if(answer) 
			    {
			    	playAgain=true;
			    	incorrectInput=false;
			    }
			    else if(answer) 
			    {
			    	playAgain=false;
			    	incorrectInput=false;
			    }
			    else 
			    {
			    	System.out.println("YOU ENTERED AN INVALID INTEGER OR" + 
			    			" THE COLUMN IS FULL.");
			    	incorrectInput=true;		    	
			    }
		    }
		}
    }
	
	// fill the board
	public static char[][] fillBoard(char[][] board)
	{
		for (int i = 0; i < board.length; i++ )
		{
			for (i=0;i<6;i++) 
			{
				for(int j=0;j<7;j++) 
				{
					board[i][j] = ' ';
				}
			}
		}
	return board;
	}
	
	// displayBoard(char[][] board) 
	private static void printBoard(char[][] board)
	{
		for(int i = board.length - 1; i >= 0; i--)
		{
			System.out.print("| ");
			for(int j = 0; j <board[i].length; j++)
			{
				System.out.print(board[i][j] + " | ");
			}
			System.out.println();//new line
		}
	}
	 // drop disk method
	public static void dropDisk(char[][] board, int column, char color)
	{ 
		while(columnIsFull(board,column)) 
		{
			System.out.println("YOU ENTERED AN INVALID INTEGER OR" + 
					"THE COLUMN IS FULL.");
			boolean incorrectInput=true;
		    while(incorrectInput) {
		    	Scanner newColumn = new Scanner(System.in);
		    	column = newColumn.nextInt();
		    	
		    	for(int i=0;i<7;i++) 
		    	{
		    		if(column==i) 
		    		{
		    			incorrectInput=false;
		    			break;
		    		}
			    }
		    	if(incorrectInput) 
		    	{
		    		System.out.println("YOU ENTERED AN INVALID INTEGER OR" + 
		    				" THE COLUMN IS FULL.");
		    	}
		    }
		}
		for(int i=0; i<6; i++) 
		{
			if(board[i][column]==' ')
			{
				board[i][column]=color;
				return;
			}
		}
	}
	// check if column is full
	public static boolean columnIsFull(char[][] board,int col) 
	{
		for(int i=5; i>=0; i--) 
		{
			if(board[i][col]==' ')
			{
				return false;
			}
		}
		return true;
	}
	// search for winner
	public static boolean isWinner(char[][] board)
	{	
	// checking for horizontal win
		for (int i=0; i<board.length; i++)
		{
			for(int j=0; j<board[i].length -3; j++)
			{
				if(board[i][j] !=' '
				&& board[i][j] == board[i][j+1]
				&& board[i][j] == board[i][j+2]
				&& board[i][j] == board[i][j+3])
				{
				return true;					
				}					
			}								
		}
	//	checking for vertical win
		for (int j=0; j<board[0].length; j++)
		{
			for (int i=0; i<board[0].length-3; i++)
			{
				if(board[i][j] !=' '
				    && board[i][j] == board[i+1][j]
				    && board[i][j] == board[i+2][j]
				    && board[i][j] == board[i+3][j])
				{
					return true;
				}
			}
		}
	// checking for diagonal win, from top left to bottom right
		for (int i=0; i<board.length-3; i++)
		{
			for (int j=0; j<board[i].length - 3; j++)
			{
				if(board[i][j] != ' '
					&& board[i][j] == board[i+1][j+1]
                    && board[i][j] == board[i+2][j+2]
                    && board[i][j] == board[i+3][j+3] )
				{
					return true;
				}
			}
		}
		
	// checking for diagonal win, from top right to bottom left
		for(int i=0; i<board.length-3; i++)
		{
			for(int j=3; j<board[i].length; j++)
			{
				if(board[i][j] != ' '
					&& board[i][j] == board[i+1][j-1]
					&& board[i][j] == board [i+2][j-2]
					&& board[i][j] == board[i+3][j-3])
				{
				return true;
				}
			}
		}
		boolean result=false;
		return result;
	}
}

