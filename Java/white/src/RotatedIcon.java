import java.awt.Component;
import java.awt.Graphics2D;
import java.awt.Graphics;
import java.awt.RenderingHints;
import javax.swing.Icon;

/**
 *  The RotatedIcon allows you to change the orientation of an Icon by
 *  rotating the Icon before it is painted. This class supports the ABOUT_CENTER 
 *  orientation that allows the icon to be rotated by the specified degrees about its center.
 *  <br><br>
 * * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: RotatedIcon.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */
public class RotatedIcon implements Icon
{

	private Icon icon;

	private double degrees;
	private boolean circularIcon;


	/**
	 *  Create a RotatedIcon. The icon will rotate about its center.
	 *
	 *  @param icon	the Icon to rotate
	 *  @param degrees   the degrees of rotation
	 *  @param circularIcon treat the icon as circular so its size doesn't change
	 */
	public RotatedIcon(Icon icon, double degrees, boolean circularIcon)
	{
		this.icon = icon;
		this.degrees = degrees;
		this.circularIcon = circularIcon;
	}

	/**
	 *  Gets the Icon to be rotated
	 *
	 *  @return the Icon to be rotated
	 */
	public Icon getIcon()
	{
		return icon;
	}
	/**
	 *  Gets the degrees of rotation.
	 *
	 *  @return the degrees of rotation
	 */
	public double getDegrees()
	{
		return degrees;
	}

	/**
	 *  Is the image circular or rectangular?
	 *  When true, the icon width/height will not change as the Icon is rotated.
	 *
	 *  @return true for a circular Icon, false otherwise
	 */
	public boolean isCircularIcon()
	{
		return circularIcon;
	}

//
//  Implement the Icon Interface
//
	
	/** 
	 * Gets the height of this icon.
	 * 
	 * @return the height of the icon in pixels.
	 */
	@Override
	public int getIconHeight() {
		return icon.getIconHeight();
	}

	/** 
	 * Gets the width of this icon.
	 * 
	 * @return the width of the icon in pixels.
	 */
	@Override
	public int getIconWidth() {
		return icon.getIconWidth();
	}


   /**
	*  Paint the icons of this compound icon at the specified location
	*
	*  @param c The component on which the icon is painted
	*  @param g the graphics context
	*  @param x the X coordinate of the icon's top-left corner
	*  @param y the Y coordinate of the icon's top-left corner
	*/
	@Override
	public void paintIcon(Component c, Graphics g, int x, int y)
	{
		Graphics2D g2 = (Graphics2D)g.create();

		int cWidth = icon.getIconWidth() / 2;
		int cHeight = icon.getIconHeight() / 2;
		
		 /*Setting Anti-aliasing rendering hints is a safety measure that will make the edges
         * of the buttons smoother to the eyes of people who are using older display devices.*/
			g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			
			/*set the clip rectangle of the graphics2D to be as big as the icon*/
			g2.setClip(x, y, getIconWidth(), getIconHeight());
			
			/*set the origin of the graphics2D context to the center of the icon*/
			g2.translate((getIconWidth() - icon.getIconWidth()) / 2, (getIconHeight() - icon.getIconHeight()) / 2);
			
			/*rotate the Icon*/
			g2.rotate(Math.toRadians(degrees), x + cWidth, y + cHeight);
			
			/*then paint the icon*/
			icon.paintIcon(c, g2, x, y);
			
			/*release system resources from using the graphics2D context*/
		g2.dispose();
	}


}