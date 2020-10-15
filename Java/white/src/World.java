import java.awt.Color;
import java.awt.Dimension;
import java.util.ArrayList;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: World.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */

@SuppressWarnings("serial")
public class World extends JPanel{

	/**
	 * Will hold a reference to the GUI
	 */
	private GUI gui; 
	/**
	 * true if the game over condition has been met and false otherwise
	 */
	private boolean gameOver = false;
	
	/**
	 * Determines the score that a team must achieve so the game is over
	 */
	private int gameOverCondition = 10;
	
	/**
	 * False if user doesn't control a baby(Multi button is not pressed) and true if 
	 * user has control of a baby (Multi button is pressed)
	 */
	private boolean manualMode = false;
	
	/**
	 * Will hold the name of the team that the user selected to play with
	 */
	private String teamChosenInMulti;
	
	/**
	 * Defines if the game is in default mode or not. Being in default mode,
	 * means that the ball will not have random rotation nor that the babies 
	 * will move. If another mode is set(e.g. 2players), this will be disabled.
	 */
	private boolean defaultMode = true;
	
	/**
	 * List that will contain ALL Baby type instances that are added in the world
	 */
	private  ArrayList<Baby> BabyCollection = new ArrayList<Baby>();
	/**
	 *  List that will contain ALL Ball type instances that are added in the world
	 */
	private  ArrayList<Ball> BallCollection = new ArrayList<Ball>();
	
	
	private ImageIcon img = new ImageIcon(CBabyBallBounce.class.getResource("images/baby1.png"));
	private ImageIcon img2 = new ImageIcon(CBabyBallBounce.class.getResource("images/baby2.png"));
	private ImageIcon img3 = new ImageIcon(CBabyBallBounce.class.getResource("images/ball.png"));
	private ImageIcon img4 = new ImageIcon(CBabyBallBounce.class.getResource("images/bricks2.jpg"));
	
	 Ball Ball1 = new Ball(img3);
	 Baby baby1 = new Baby(img);
	 Baby baby2 = new Baby(img2);
	
	/*
	 * Constructor of World
	 * The world is constructed of many rectangles that form a grid
	 * To know the width and the height of the grid, we must know how many columns and rows the grid will have and also the cellsize in pixels 
	 * */
	public World( int rows, int columns,int cellsize)
	{	
		super();
		setLayout(null);
		setPreferredSize(new Dimension((columns * cellsize)+2, (rows * cellsize)+2)); //adding 2 pixels so that it doesn't fall on the border
		setBorder(BorderFactory.createLineBorder(Color.black));
		setVisible(true);
		
		
		/*Getting the World's width and keeping it in a variable.
		 * It will be used to add the bricks in the middle of the screen.
		 * Because this will be used in a for loop, we keep the value in a 
		 * variable instead of getting it every time the loop runs.*/
		int worldWidth = (int) getPreferredSize().getWidth();
		
		
		
		/*
		 * Adding Actors in the World START
		 * */
		addActor(baby1,150,200);
		addActor(baby2,320,200);
		addActor(Ball1,200,200);
		

        for (int i=0; i<19; i++)
        {
        	//place the bricks and start from the middle of the World's X axis
            addActor(new Bricks(img4), (worldWidth / 2) - 32, 19*i);
        }

		/*
		 * Adding Actors in the World END
		 * */
        
		addTiles(rows,columns,cellsize);
		assignTeamsToBabies();
	}	
	

	/**
	 * Adds an actor to the World.
	 * @param actor - The Actor object to add
	 * @param offsetLeft - Location to be placed in the World on the X axis 
	 * @param offsetTop - Location to be placed in the World on the Y axis 
	 */
	public void addActor(Actor actor, int offsetLeft, int offsetTop)
	{
		Dimension size;
		
		size = actor.getPreferredSize();
		actor.setBounds(offsetLeft + 1, offsetTop + 1,size.width, size.height);
		
		collectActor(actor);
		actor.setWorld(this);
		add(actor);
		
		
	}
	
	/**
	 * Removes an actor from the World and from the relevant list.
	 * @param actor - Actor to remove.
	 */
	public void removeActor(Actor actor)
	{
		for(int i =0; i < BabyCollection.size(); i++)
		{
			if(actor.equals(BabyCollection.get(i)))
			{
				BabyCollection.remove(i);
			}
		}
		for(int i =0; i < BallCollection.size(); i++)
		{
			if(actor.equals(BallCollection.get(i)))
			{
				BallCollection.remove(i);
			}
		}
		
		remove(actor);
	}

	/**
	 * Creates a grid of squares that form the background of the World
	 * @param rows - Number of grid's rows
	 * @param columns - Number of grid's columns
	 * @param cellsize - The size in pixels of each block in the grid
	 */
	private void addTiles(int rows, int columns, int cellSize)
	{
		
		ImageIcon bg = new ImageIcon(CBabyBallBounce.class.getResource("images/white32x32.jpg"));
		JLabel label = new JLabel(bg);
		
		for(int i = 0; i < columns; i++)
		{		
			for(int j = 0; j < rows; j++)
			{
				
				label = new JLabel(bg);
				label.setBounds(i * cellSize + 1,j * cellSize + 1,cellSize,cellSize); // ADDING 1 SO THAT THE BORDER AROUND IT TO BE VISIBLE
				add(label);
		
			}
		}
	}
	

	/**
	 * Inserts an Actor that is added in the World, to the relevant list to keep 
	 * track of all the actors that are added to the World.
	 * This method is invoked by <code>addActor</code> method.
	 * @param actor - The actor to add to a list
	 */
	private <T extends Actor> void collectActor(T actor)
	{
		//http://stackoverflow.com/questions/6149677/comparing-class-types-in-java
		
		if(actor instanceof Baby) // if the instance passed as parameter is instance type Baby
		{
			//add it to the ArrayList made to keep references to all babies added to the World
			BabyCollection.add((Baby) actor); 
		}else if(actor instanceof Ball) //else if the instance passed as parameter is instance type Ball
		{
			//add it to the ArrayList made to keep references to all balls added to the World
			BallCollection.add((Ball) actor); 
		}else
		{
			return; //in any other case, do nothing
		}
	}
	


	/**
	 *Goes through the arrayList of babies and checks the location of a baby.
	 *Depending at which side of the World it is, the baby will be assigned to the 
	 *correct team ("LEFT" or "RIGHT")
	 */
	public void assignTeamsToBabies()
	{
		for(int i = 0; i < BabyCollection.size();i++)
		{
			if(BabyCollection.get(i).getX() < this.getPreferredSize().getWidth() /2)
			{
				BabyCollection.get(i).setTeam("LEFT"); 
			}else if(BabyCollection.get(i).getX() > this.getPreferredSize().getWidth() /2)
			{
				
				BabyCollection.get(i).setTeam("RIGHT"); 
			}
		}
		
	}
	
	/**
	 * Enables Manual mode for the specified team. 
	 * @param team - the team that the player chose to control its initial baby
	 */
	public void enableMultiMode(String team)
	{
		ManualModeEnabled(true);
		teamChosenInMulti = team;
		switch (team) {
		case "RIGHT":
			baby2.setManualMode(true);
			break;
		case "LEFT":
			baby1.setManualMode(true);
			break;

		default:
			break;
		}
	}
	
	/**
	 * Disables Manual mode
	 */
	public void disableMultiMode()
	{
		ManualModeEnabled(false);
		switch (teamChosenInMulti) {
		case "RIGHT":
			baby2.setManualMode(false);
			break;
		case "LEFT":
			baby1.setManualMode(false);
			break;

		default:
			break;
		}
	}
	
	/**
	 * This method invokes the <code>act</code> method of every actor 
	 * contained in the two lists of the World. If the World is on Default
	 * mode, babies won't move.
	 */
	public void allActorsAct()
	{
		if(!defaultMode)
		{
			for(int i =0; i < BabyCollection.size(); i++)
			{
				BabyCollection.get(i).act();
			}
		}
		for(int i =0; i < BallCollection.size(); i++)
		{
			BallCollection.get(i).act();
		}
	}
	
	public boolean isDefaultMode() {
		return defaultMode;
	}


	public void setDefaultMode(boolean defaultMode) {
		this.defaultMode = defaultMode;
	}


	public ArrayList<Baby> getBabyList()
	{
		return BabyCollection;
	}
	
	public ArrayList<Ball> getBallList()
	{
		return BallCollection;
	}
	
	public void giveGUI(GUI gui)
	{
		this.gui = gui;
	}
	
	public GUI getGui()
	{
		return gui;
	}
	
	public boolean isManualModeEnabled()
	{
		return manualMode;
	}
	
	public void ManualModeEnabled(boolean mode)
	{
		manualMode = mode;
	}
	public String getTeamChosenForMulti()
	{
		return teamChosenInMulti;
	}
	
	public void setTeamForMulti(String team)
	{
		teamChosenInMulti = team;
	}
	
	public Baby getBabyOnManual()
	{
		if(baby1.isInManualMode())
		{
			return baby1;
		}else
		{
			return baby2;
		}
	}
	
	public boolean isTheGameOver()
	{
		return gameOver;
	}
	
	public void setGameOver(boolean gameover)
	{
		this.gameOver = gameover;
	}
	
	public int getGameOverCondition()
	{
		return gameOverCondition;
	}
	
	public void setGameOverCondition(int gmver)
	{
		gameOverCondition = gmver;
	}
}

