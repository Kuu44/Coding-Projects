import java.awt.Container;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.geom.Area;
import java.util.ArrayList;
import javax.swing.ImageIcon;
import javax.swing.JLabel;

/**
 * The abstract class Actor is the parent class for all the objects that will be added in the World and interact.
 * It contains functions of common use for every Actor. <br><br>
 * <br><br><br>
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: Actor.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */

@SuppressWarnings("serial")
public abstract class Actor extends JLabel{
	
	
	public Actor(ImageIcon icon)
	{
		setIcon(icon);
	}
	
	private World actorWorld;
	
	private int angle = 0;
	
	/*
	 * Act method is inherited and used as the main method of every instance that extends Actor. 
	 * */
	public abstract void act();
	
	//http://gamedev.stackexchange.com/questions/36046/how-do-i-make-an-entity-move-in-a-direction
	
	/**
	 * Used to move an actor in the world that exists in, based on the rotation of the actor.
	 * @param speed - Number of pixels an actor will move every time this function is invoked
	 */
	public void move(int speed)
	{
		
		 int newX = getX();
		 int newY = getY();
		 newY += speed * Math.sin(Math.toRadians(getRotation()));
		 newX += speed * Math.cos(Math.toRadians(getRotation()));
		 this.setLocation(newX, newY);
	}
	
	/**
	 * Rotates the Actor as many degrees as given in the parameter plus the current rotation
	 * @param degrees - Add degrees to the current rotation value
	 */
	protected void turn(int degrees)
	{
		int temp = getRotation() + degrees;
		
		setRotation(temp);
		rotateIcon(degrees);
	}

	
	 /**
	  * Checks if this actor is intersecting with the actor given as parameter
	  * This is accomplished by checking if the Area of each Actor is in the bounds 
	  * of the other.
	  * 
	 * @param actor - The actor to compare with
	 * @return True if the Areas are intersecting. False otherwise.
	 */
	private boolean intersectsWith(Actor actor)
	{
		//http://stackoverflow.com/questions/12325553/how-do-i-detect-the-collison-of-components
		Area area1 = new Area(this.getBounds());
		Area area2 = new Area(actor.getBounds());

		return area1.intersects(area2.getBounds2D());
	}
	 
	 

	 
	 /**
	  * Gets all the actors that exist in the World (except than this) and checks if
	  * this Actor intersects with any of them. If true, it returns the intersecting Actor
	  * otherwise, returns <code>null</code>.
	 * @return The Actor that this Actor intersects with. Null if it intersects with no one.
	 */
	protected <T extends Actor> Actor getIntersectionActor(Class<T> classToCheck)
	 {
		//get the two lists that contain Baby and Ball type instances placed in World
		 ArrayList<Baby> tempBabyList = actorWorld.getBabyList();
		 ArrayList<Ball> tempBallList = actorWorld.getBallList();
		 
		 //if the type passed as parameter is the Baby class
		 if(classToCheck.equals(Baby.class))
		 {
			 //go through the list that contains babies
			 for(int i = 0; i < tempBabyList.size();i++)
			 {
				 /*and check if a baby contained in this list (except the one performing the check) 
				  * intersects with the Actor performing this check*/
				 if(intersectsWith(tempBabyList.get(i)) && tempBabyList.get(i) != this)
				 {
					 return tempBabyList.get(i); //return the intersecting Actor if true
				 }
			 }
			 //otherwise if the type passed as parameter is the Ball class
		 }else if(classToCheck.equals(Ball.class))
		 {
			 //go through the list that contains balls
			 for(int i = 0; i < tempBallList.size();i++)
			 {
				 /*and check if a ball contained in this list (except the one performing the check) 
				  * intersects with the Actor performing this check*/
				 if(intersectsWith(tempBallList.get(i)) && tempBallList.get(i) != this)
				 {
					 return tempBallList.get(i); //return the intersecting Actor if true
				 }
			 }
		 }
		 return null; //in any other case return null
	 }
	 
	 
	 /**
	  * Checks if this <code>Actor</code> is at a world's edge.
	 * @return <code>True</code> if it touches and <code>false</code> if not
	 */
	protected boolean isAtEdge()
	 {
		 Container world = getParent();
		 Dimension worldSize = world.getSize();
		 Point actorLocation = getLocation();
		 Dimension actorSize =  getSize();
		 
		 /*Check if:
		  * 	Actor's location on X axis is bigger than World's width - the actor's Width or
		  * 	Actor's location on X axis is smaller than World's width - the actor's Width or
		  * 	Actor's  location on Y axis is bigger than World's height - the Actor's height or
		  * 	Actor's location on Y axis is smaller than World's height */
		 if(actorLocation.getX() > (worldSize.getWidth() - actorSize.getWidth())
				 || actorLocation.getY() > (worldSize.getHeight() - actorSize.getHeight()) 
				 ||actorLocation.getX() < (worldSize.getWidth() - worldSize.getWidth()) 
				 || actorLocation.getY() < (worldSize.getHeight() - worldSize.getHeight()))
		 {
			 return true;
		 }else
		 {
			 return false;
		 }
	 }
	 
	 /**
	  * Rotates the icon that is set to this actor, as many degrees as the number given
	  * as parameter.
	 * @param degrees - Rotation in degrees
	 */
	protected void rotateIcon(int degrees)
	 {
		 boolean isCircular = true; // the icon is circular by default
		 
		 /*Check if the icon's width is not equal with the icon's height
		  * If true, it means that the icon is not circular*/
		 if(getIcon().getIconWidth() != getIcon().getIconHeight()) 
		 {
			 isCircular = false; // the icon is not circular
		 }
		 /*create the newly rotated icon*/
		RotatedIcon rotIcon = new RotatedIcon(getIcon(), degrees, isCircular);
		/*set the newly rotated icon as the current Actor's icon */
		setIcon(rotIcon);
	 }
	 
	 
	/**
	 * Gives a random number from the specified range.
	 * @param min - The minimum value that the returned random number can have
	 * @param max - The maximum value that the returned random number can have
	 * @return - The random number generated
	 */
	protected int getRandomNumFromRange(int min,int max)
	{
		int randomNum = (int)  Math.round(Math.random() * (max - min));
        randomNum = (min + randomNum); 
        return randomNum; 
	}
	
	/**
	 * From the range 0 to 100, it gets a random number, returns 1
	 * if the number is bigger than 50 and returns 0 if the number
	 * is smaller than 50. That way it provides 50-50 chance to tasks
	 * that have two outcomes. 
	 * 
	 * @return 1 or 0. 
	 */
	protected int flipAcoin()
	{
		int chance = getRandomNumFromRange(0, 100);
		if(chance < 50)
		{
			return 0;
		}else
		{
			return 1;
		}
		
	}
	 
	 
	 
	 public int getRotation()
	 {
		return angle; 
	 }
	 
	 public void setRotation(int rot)
	 {
		 if(rot < 0)
		 {
			 rot = 360 - rot;
		 }
		 if(rot >= 360)
		 {
			 rot = rot - 360;
		 }
		 angle = rot;
	 }
	 
	 public void setWorld(World world)
	 {
		 actorWorld = world;
	 }
	 
	 public World getWorld()
	 {
		 return actorWorld;
	 }
}





