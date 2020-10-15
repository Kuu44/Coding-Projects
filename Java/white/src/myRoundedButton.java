
import java.awt.Color;
import java.awt.Container;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.geom.RoundRectangle2D;
import javax.swing.ImageIcon;
import javax.swing.JButton;

 /**
  * Custom class used for creating rounded-corner buttons <br><br>
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: myRoundedButton.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */
 
@SuppressWarnings("serial")
class myRoundedButton extends JButton {

	//DECLARATION AREA START //
	private boolean isButtonPressed = false;
	private int width; //will hold the height when the object will be created
	private int height; //will hold the weight when the object will be created
	private double x;
	private double y;
	
	private static final double ARC_WIDTH  = 11; //the width of the Arc
    private static final double ARC_HEIGHT = 11; //the height of the Arc
    protected final Color fc = new Color(100, 150, 255, 200); //inner border color 
    protected final Color ac = Color.lightGray; //pressed button's color
    protected final Color bg = new Color(250,250,250);
    
    protected Shape shape;
    protected Shape base;
    //DECLARATION AREA END //
    
    
    //CONSTRUCTOR AREA START//
    protected myRoundedButton(ImageIcon icon, boolean isClickable,int width,int height,double d,double y) 
    {
    	super(icon);
    	this.width = width;
    	this.height = height;
    	
    	this.x = d;
    	this.y = y;
    	
    	 if(!isClickable)
         {
         	this.setDisabledIcon(icon);
         	this.setEnabled(false);
         }
        
    }
    protected myRoundedButton(String text,int width,int height,int x,int y) 
    {
        super(text);
        this.width = width;
    	this.height = height;
    	
    	this.x = x;
    	this.y = y;
    }
    
    protected myRoundedButton(String text, ImageIcon icon,int width,int height,int x,int y) {
        super(text, icon);
        this.width = width;
    	this.height = height;
    	
    	this.x = x;
    	this.y = y;
    }
    //CONSTRUCTOR AREA END //
    
    
    
    @Override public void updateUI() {
    	super.updateUI();
    	setContentAreaFilled(false);
    	setFocusPainted(false);
    	setBackground(new Color(250,250,250)); //button's color
    	initShape();
    }
    

    /*initShape() ensures that if the button changed location, a new shape will be created to the size that it is set and to the 
     * new coordinates
     * */
    protected void initShape() {
        if (!getBounds().equals(base)) {
            base = getBounds();
            shape = new RoundRectangle2D.Double(x,y, getWidth() - width, getHeight() - height, ARC_WIDTH, ARC_HEIGHT);
        }
    }
 /*paintComponent is overridden so that whenever it is called, to take in account our custom configurations for the 
  * button and not the default ones. This method might get invoked from a number of places and whenever Java deems 
  * appropriate to do so. 
  * Whenever this happens though for whatever reason that is none of our concern, we need to ensure that its background
  * will get painted to our custom color, and that whenever the button is pressed to change to another custom color that 
  * we defined. 
  * 
  *  */
    @Override protected void paintComponent(Graphics g) {
        initShape();
        Graphics2D g2 = (Graphics2D) g.create();
        /*Setting Anti-aliasing rendering hints is a safety measure that will make the edges
         * of the buttons smoother to the eyes of people who are using older display devices.*/
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        if (getModel().isArmed()) {
            g2.setPaint(ac);
            g2.fill(shape);
        }  else {
            g2.setPaint(getBackground());
            g2.fill(shape);
        }
        g2.dispose();
        super.paintComponent(g);
    }
    
    /*paintBorder method, paints the border around the roundButton. The way that this method gets invoked is similar
     * to the way paintComponent gets invoked*/
    @Override protected void paintBorder(Graphics g) {
        initShape();
        Graphics2D g2 = (Graphics2D) g.create();
        g2.setPaint(Color.gray);
        g2.draw(shape);
        g2.dispose();
    }
    
    /*This method will ensure that only the painted area of the button can be clicked. This is accomplished 
     * by checking if the specified point on the given x and y is inside the area of the component's shape 
     * (roundRectangle2D) Returns true if the shape exists and the point is inside the shape and false if 
     * either of these two conditions is false.
     * It is automatically invoked by Java on mouse Events.
     */
    @Override public boolean contains(int x, int y) {
        initShape();
        return shape != null && shape.contains(x, y);
    }
    
    
    
    /**
     * Replaces <code>this</code> button with the button given in the parameter. 
     * This method dynamically gets the index of <code>this</code> button
     * and then places the specified button to that index.
     * @param buttonToPlace - The button to add in the position of <code>this</code>
     */
    void replaceButtonWith(myRoundedButton buttonToPlace)
    {
    	Container c = this.getParent(); /*Get the container that contains this button*/
    	
    	for (int i = 0; i < c.getComponentCount(); i++) { /*get the number of components in this container*/
    		if (c.getComponent(i) == this) /*when you find this button in the container*/
    		{
    			c.remove(this); //remove the button
    			c.add(buttonToPlace,i);	//add the new button to the index that the removed was
    			c.revalidate(); //recalculate the layout
    			c.repaint(); //repaint the container and components it contains
    		}
    	}
    }
     
     public boolean isButtonPressed()
     {
    	 return isButtonPressed;
     }
     
     public void setPressed(boolean pressed)
     {
    	 isButtonPressed = pressed;
     }
     
     public Color getInitBackground()
     {
    	 return bg;
     }

   
}