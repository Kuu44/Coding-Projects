import java.awt.Container;
import java.awt.Dimension;
import java.awt.Point;

import javax.swing.ImageIcon;
import javax.swing.JTextField;


/**
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: Ball.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */

@SuppressWarnings("serial")
public class Ball extends Actor{

	public Ball(ImageIcon icon) {
		super(icon);
	}

	/**
	 * Speed of the ball
	 */
	private int ballSpeed = 10;

	/**
	 * Direction of the ball. Used for changing the compass icon in GUI.
	 */
	private String direction;

	/**
	 * Holds a reference to the last Actor that intersected with the ball.
	 */
	private Actor lastHitter;
	
	private final int ballRadius = 14;
	
	private final int squareSize = 32;


	private GUI myGUI;

	@Override
	public void act() 
	{
		kickBall();
	}



	/**
	 * CREATING THIS ADDITIONAL METHOD IS NOT NEEDED. IT IS ONLY ADDED TO MEET THE REQUIREMENT IN THE ASSIGNMENT BRIEF.
	 * ALL THE CONTENTS OF THIS METHOD COULD JUST BE WRITTEN IN THE SCOPE OF METHOD act()
	 */
	private void kickBall()
	{
		//if the ball is not at a World's edge
		if(!isAtEdge())
		{
			move(ballSpeed); //move it to the direction it is facing

			/*Invoke getIntersectionActor method and pass the baby class as an argument
			 * so that it checks if the ball intersects with a baby placed in the World
			 * Return the Baby type instance if it intersects or null if not */
			Baby baby = (Baby) getIntersectionActor(Baby.class);

			/*if ball indeed intersects with a baby and the current baby instance
			 * is not intersecting with the ball twice in a row
			 * */
			if(baby != null && baby != lastHitter)
			{
				move(ballSpeed * -1); //get out of the baby's area by moving to the opposite direction

				/*invoke bounceOffBaby method and pass the baby's team as an argument to successfully 
				 * rotate the ball to the appropriate direction*/
				bounceOffBaby(baby.getTeam()); //instead of that
				//turn(180); //for basic scenario

				//store the current baby's instance to lastHitter
				lastHitter = baby;

				//move the ball to the direction it is facing
				move(ballSpeed * 2);
			}
		}else //if ball is at a World's edge
		{
			//bounce the ball from the wall
			bounceOffWall();
			if(isAtEdge()) //if you are still on the edge
			{
				bounceOffWall(); //rebounce once more
			}

			/*make sure that scores cannot be updated if the ball hits
			 * a World's edge twice in a row*/
			if(lastHitter != null)
			{
				//check at which half of the world is and update the relevant score text field
				updateScore();
			}
			//make it so, anyone can hit the ball
			lastHitter = null;
		}
	}



	/**
	 * Calculates and shows the square number that the ball is currently located,
	 * by getting the position of the ball on X and Y axis plus 32,dividing both by 32 
	 * and multiplying one result with the other.
	 * This method will show proper results only if every square is 32x32 pixels.
	 */
	private void locateOnTerrain()
	{
		myGUI = getWorld().getGui();
		int location = (((getX() + ballRadius + squareSize) / squareSize )  * ((getY() + ballRadius + squareSize) / squareSize));
		myGUI.getSquareBox().setText(String.valueOf(location));
	}

	/**
	 * Displays the direction of the ball in the directionTextField,
	 * depending on the ball's rotation in degrees at any moment.
	 * It also updates the compass icon properly.
	 * 
	 * @param degrees - The rotation of the ball
	 */
	private void showDirection(int degrees)
	{
		myGUI = getWorld().getGui();
		if(degrees < 45 || (degrees >315 && degrees <359)) 
		{
			direction = "E";
			myGUI.changeCompass(direction);
		}else if(degrees > 135 && degrees < 225)
		{
			direction = "W";
			myGUI.changeCompass(direction);
		}
		else if(degrees > 225 && degrees < 315)
		{
			direction = "N";
			myGUI.changeCompass(direction);
		}
		else if(degrees > 45 && degrees < 135)
		{
			direction = "S";
			myGUI.changeCompass(direction);
		}
		myGUI.getDirectionBox().setText(direction);
	}

	/**
	 * Method used for when controlled movement of the ball is required, either with keys or buttons.
	 * This method also rotates the icon of the ball to the given direction degrees.
	 * 
	 * @param direction - The direction in degrees
	 * @param speed - Pixels that the ball will move 
	 */
	public void controlledMove(int direction,int speed)
	{
		int oldSpeed = ballSpeed;
		int rotation = direction - getRotation();
		setSpeed(speed);
		setRotation(direction);
		showDirection(direction);
		rotateIcon(rotation);
		act();
		setSpeed(oldSpeed);
	}

	/**
	 * Controls the ball's correct rebound from a baby depending from the side it is located.
	 * If the World is on defaultMode, the ball will rebounce 180 degrees from a baby.
	 * Otherwise Babies on the right side (RIGHT team), will cause the ball to rebound to a new direction 
	 * from a random range of 100-260 degrees and babies on the left side (LEFT team), will 
	 * cause the ball to rebound to a new direction from a random range of 280-80 degrees.
	 * 
	 * @param team - The team of the baby that needs to be checked
	 */
	private void bounceOffBaby(String team)
	{
		int random = 0;
		int differ;
		int addOn;

		if(!getWorld().isDefaultMode())
		{
			if(team == "RIGHT")
			{ 
				random = getRandomNumFromRange(0, 90);
				differ =  90 - random; 
				addOn = getRandomNumFromRange(10,170); 
				random = (random + differ) + addOn; // to the left
				setRotation(random);
				rotateIcon(random);
			}else if(team == "LEFT" && !getWorld().isDefaultMode())
			{ 
				random = getRandomNumFromRange(0, 360);
				differ = 270 - random; 
				addOn = getRandomNumFromRange(10,170);
				random = (random + differ) + addOn; //to the right

				setRotation(random);
				rotateIcon(random);
			}
		}else 
		{
			turn(180);
		}
	}

	/**
	 * Updates the score of either team, by calculating at which side the ball will
	 * hit a world's edge. If the ball is at the right side when reaching the world's bounds,
	 * the LEFT team gets +1 in score. Respectively, if the ball is at the 
	 * left side when reaching the world's bounds, the RIGHT team gets +1 in score.
	 * This method also checks if any team have reached 10 points in scoring. If 
	 * true, it notifies the World that the game is over
	 */
	private void updateScore()
	{
		int score;

		JTextField scoreLeft = getWorld().getGui().getScoreLeft();
		JTextField scoreRight = getWorld().getGui().getScoreRight();

		if(getX() > (getWorld().getWidth() /2) + 40)
		{
			score = Integer.parseInt(scoreLeft.getText());
			if(score == getWorld().getGameOverCondition() - 1)
			{
				getWorld().setGameOver(true);
				scoreLeft.setText(Integer.toString(score + 1));
			}else
			{
				scoreLeft.setText(Integer.toString(score + 1));
			}
		}else if(getX() < (getWorld().getWidth() /2) - 50)
		{
			score =  Integer.parseInt(scoreRight.getText());
			if(score == getWorld().getGameOverCondition() - 1)
			{
				getWorld().setGameOver(true);
				scoreLeft.setText(Integer.toString(score + 1));
			}else
			{
				scoreRight.setText(Integer.toString(score + 1));
			}
		}
	}

	/**
	 * Handles the correct re-bouncing of the ball from a world's edge, applying some basic physics
	 * Depending on the incoming angle and the side the ball is intersecting with, it will be set to 
	 * the new relevant angle.
	 */
	private void bounceOffWall(){

		Container world = getParent();
		Dimension worldSize = world.getSize();
		Point ballLocation = getLocation();
		Dimension actorSize =  getSize();

		int currentRotation = getRotation();

		if(ballLocation.getX() > (worldSize.getWidth() - actorSize.getWidth())) //right wall
		{
			if(270 <= currentRotation && currentRotation <= 360)
			{
				setRotation(360 - currentRotation);
			}else if(0 <= currentRotation && currentRotation <= 90)
			{
				setRotation(180 - currentRotation);
			}
			rotateIcon(getRotation());
		}else if(ballLocation.getY() > (worldSize.getHeight() - actorSize.getHeight())) //lower wall
		{
			if(0 <= currentRotation && currentRotation <= 90)
			{
				setRotation(360 - currentRotation);
			}else if(90 <= currentRotation && currentRotation <= 180)
			{
				setRotation(360 - currentRotation);
			}
			rotateIcon(getRotation());

		}else if(ballLocation.getX() < (worldSize.getWidth() - worldSize.getWidth())) //left wall
		{
			if(90 <= currentRotation && currentRotation <= 180)
			{
				setRotation(180 - currentRotation);
			}else if(180 <= currentRotation && currentRotation <= 270)
			{
				setRotation(540 - currentRotation);
			}
			rotateIcon(getRotation());

		}else if(ballLocation.getY() < (worldSize.getHeight() - worldSize.getHeight())) //upper wall
		{
			if(180 <= currentRotation && currentRotation <= 270)
			{
				setRotation(360 - currentRotation);
			}else if(270 <= currentRotation && currentRotation <= 360)
			{
				setRotation(360 - currentRotation);
			}
			rotateIcon(getRotation());
		}
		move(getSpeed());
	}


	public int getSpeed()
	{
		return ballSpeed;
	}

	public void setSpeed(int speedChange)
	{
		ballSpeed = speedChange;
	}

	@Override public void move(int speed)
	{
		super.move(speed);
		locateOnTerrain();
	}

	@Override
	public void setRotation(int rot) {
		super.setRotation(rot);
		showDirection(getRotation());
	}


}
