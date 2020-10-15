import javax.swing.ImageIcon;


/**
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: Baby.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */

@SuppressWarnings("serial")
public class Baby extends Actor {

	/**
	 * Constructor of Baby. 
	 * Also, assigns an icon to the Baby.
	 * @param icon - paints an icon to the Baby object
	 */
	public Baby(ImageIcon icon) 
	{
		super(icon);
	}
	
	private final int GO_UPPER = 1;
	private final int GO_LOWER = 0;
	
	/**
	 * The team of the baby. This will take two values, either "RIGHT" or "LEFT"
	 */
	private String team;
	
	/**
	 * Determines if the user controls the movement of that baby.
	 */
	private boolean manualMode = false;
	
	/**
	 * The value of direction determines the direction that the baby will move.
	 * It might be up or down.
	 * Actor.flipAcoin() method initializes this property to give a random
	 * direction to the baby when the game begins.
	 */
	private int direction = flipAcoin();
	
	/**
	 * Speed will take a random number from 10 to 20. 
	 * This determines how many pixels the baby will move every time its act()
	 * method is invoked.
	 */
	private int speed = getRandomNumFromRange(10, 20);
	
	
	private RotatedIcon iconLookingUp = new RotatedIcon(getIcon(),0,true);
	private RotatedIcon iconLookingDown = new RotatedIcon(getIcon(),180,true);
	
	@Override
	public void act() 
	{	
		//for demonstration of the basic scenario change this condition
		//check if the baby is NOT at a world's edge AND it is NOT in manual mode
		if(!isAtEdge() && !isInManualMode())
		{
			//should the baby go up?
			if(direction == GO_UPPER)
			{
				setIcon(iconLookingUp);
				//set its rotation to 270 degrees (looks up)
				setRotation(270);
				//move it towards the direction it is facing
				move(speed);
			}
			else if(direction == GO_LOWER) //or should the baby go down?
			{
				setIcon(iconLookingDown);
				//set its rotation to 90 degrees (looks down)
				setRotation(90);
				//move it towards the direction it is facing
				move(speed);
			}
		}else if(isAtEdge() && !isInManualMode()) //in the other case that the baby is at a world's edge
												//and is not on manual mode
		{
			//check which side and set it to go to the opposite direction
			checkDirection();
		}
	}
	
	/**
	 * Checks at which side the baby is,upper or lower, changes its direction to the opposite side, 
	 * and gives it a new random speed from the range of 10-20. 
	 * Also sets the Baby's icon to be relevant with the direction that the baby is going. 
	 * Where the head of the baby is looking, that is the direction of the baby.
	 */
	private void checkDirection()
	{
		if(getY() > getParent().getHeight() / 2) //LOWER SIDE --- GO UP
		{
			direction = GO_UPPER;
			setIcon(iconLookingUp);
			move(-20);
			speed = getRandomNumFromRange(10, 20);
		}else if(getY() < getParent().getHeight() / 2) //UPPER SIDE --- GO DOWN
		{
			direction = GO_LOWER;
			setIcon(iconLookingDown);
			move(-20);
			speed = getRandomNumFromRange(10, 20);
		}
	}

	
	/**
	 * Used when a baby is in Manual mode. When the user presses a direction key,
	 * this function is called from <code>KeyDispatcher</code>
	 * 
	 * @param direction - To the direction the baby to move in degrees
	 */
	public void babyControlledMove(int direction)
	{
		setRotation(direction);
		if(!isAtEdge()) //if not at a World's edge
		{
			move(20); //move normally
			if(isAtEdge()) //check AGAIN if at a World's edge
			{
				move(-getHeight()); //if yes move back as many pixels as your height
			}
		}
	}
	
	public String getTeam()
	{
		return team;
	}
	
	public void setTeam(String team)
	{
		this.team = team;
	}
	
	public boolean isInManualMode()
	{
		return manualMode;
	}
	
	public void setManualMode(boolean mode)
	{
		manualMode = mode;
	}

}
