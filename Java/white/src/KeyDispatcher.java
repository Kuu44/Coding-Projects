import java.awt.KeyEventDispatcher;
import java.awt.event.KeyEvent;

/**
 * {@link KeyDispatcher} implements KeyEventDispatcher interface. This is instantiated by the GUI class
 * and is added to the KeyboardFocusManager's dispatcher chain so that KeyEvents will be dispatched first
 * by this dispatcher. This dispatcher dispatches KeyEvents related to the arrow keys, used for the manual
 * movement of the ball or baby. <br> <br>
 * <br>
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: KeyDispatcher.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */
class KeyDispatcher implements KeyEventDispatcher
{
	World theWorld;
	GUI gui;

	@Override
	public boolean dispatchKeyEvent(KeyEvent arg0) {
		if(arg0.getID() == 402 && gui.timerFunctionality.isRunning() && !theWorld.isManualModeEnabled()) 
			//402 is the key ID for key_released state
			//timerFunctionality must be running
			//manual mode must be disabled
		{
			switch (arg0.getKeyCode()) { //check which key was pressed 
			case 37: // ID for left_arrow
				theWorld.Ball1.controlledMove(180, 32);
				break;
			case 38: // ID for up_arrow
				theWorld.Ball1.controlledMove(270, 32);
				break;
			case 39: // ID for right_arrow
				theWorld.Ball1.controlledMove(0, 32);
				break;
			case 40: // ID for down_arrow
				theWorld.Ball1.controlledMove(90, 32);
				break;
			}
		}else if(arg0.getID() == 401 && gui.timerFunctionality.isRunning() && theWorld.isManualModeEnabled())
		{
			//401 is the key ID for key_pressed state
			//timerFunctionality must be running
			//manual mode must be enabled
			switch (arg0.getKeyCode()) {
			case 38: // ID for up_arrow
				theWorld.getBabyOnManual().babyControlledMove(270); //BUG WHEN ON THE EDGE OF THE WORLD AND SUDDENLY CHANGES DIRECTION
				break;												//IT GETS OUT OF THE PANEL COMPLETELY!!
			case 40: // ID for down_arrow
				theWorld.getBabyOnManual().babyControlledMove(90);
				break;
			}
		}
		return false;
	}
	public void setWorld(World world)
	{
		theWorld = world;
	}
	public void setGUI(GUI theGui)
	{
		gui = theGui;
	}

}