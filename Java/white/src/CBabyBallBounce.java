

/**
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: CBabyBallBounce.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */
public class CBabyBallBounce
{

public static void main(String[] args) {
		GUI gui = new GUI();
		World myWorld = new World(13,16,32);
		
    	gui.createFrame();
    	gui.createWorld(myWorld, gui);
    }
}

