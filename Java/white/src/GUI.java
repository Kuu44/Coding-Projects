import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.KeyboardFocusManager;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.Timer;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;


/**
 * {@link GUI} class contains everything that has to do with the Graphical User Interface, from 
 * declarations to listening to events. <br>
 *	<br>
 * Program file : Assignment 2: GUI JAVA Application – Baby Ball Bounce
 * Filename: GUI.java
 * @author: © Joyal Joshi UoN (20416225)
 * Course: BSc(hons)Computing Year 1
 * Module:Problem Solving & Programming (PSP) | CSY1020 
 * Module Tutor from UoN:: Scott Turner
 * Module Tutor from NAMI: Kumar Lamichhane
 * Date: 22nd September 2020
 */

@SuppressWarnings("serial")
public class GUI extends JFrame implements ActionListener, KeyListener, ChangeListener {
	
	
	////DECLARATION AREA/////
    private JPanel panel;
    private JPanel gameHostingPanel;
    private JMenuBar menuBar;
    private JMenuItem exit;
    private JMenuItem hTopicItem;
    private JMenuItem aboutItem;
    private JMenuItem disableDefaultMode;
    private JSlider slider;
    
    private World myWorld;
    private KeyDispatcher localKeyDispatcher;
   
    Border lowEtchBorder = BorderFactory.createEtchedBorder(EtchedBorder.LOWERED);
    Timer timerDisplay = new Timer(1000,this);
    Timer timerFunctionality = new Timer(200,this);
    private int ticks = 1;
    
    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\   BUTTONS START
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
    ///////////////////BUTTON IMAGES
    ImageIcon actIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/step.png"));
    ImageIcon runIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/run.png"));
    ImageIcon pauseIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/pause.png"));
    ImageIcon resetIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/reset.png"));
    ImageIcon BallIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/ball.png"));

    ImageIcon compassNorthIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/north.jpg"));
    ImageIcon compassSouthIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/south.jpg"));
    ImageIcon compassEastIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/east.jpg"));
    ImageIcon compassWestIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/west.jpg"));
    
    /////////////////////GAME OPTION BUTTONS
    private myRoundedButton button2Players = new myRoundedButton("2 Players",15,5,7,3); 
    private myRoundedButton button4Players = new myRoundedButton("4 Players",15,5,7,3);
    private myRoundedButton buttonMultiPlayer = new myRoundedButton("Multi",15,5,7,3);
    private myRoundedButton buttonExit = new myRoundedButton("Exit",15,5,7,3);
    /////////////////////3-BUTTON BAR BUTTONS
    private myRoundedButton buttonAct = new myRoundedButton("Act",actIcon,15,5,7,3);
    private myRoundedButton buttonRun = new myRoundedButton("Run",runIcon,15,5,7,3);
    private myRoundedButton buttonPause = new myRoundedButton("Pause",pauseIcon,15,5,7,3); // visible when run is pressed
    private myRoundedButton buttonReset = new myRoundedButton("Reset",resetIcon,15,5,7,3);
    //////////////////////MOVEMENT BUTTONS
    private myRoundedButton movementForward = new myRoundedButton(">",18,10,8,4);
    private myRoundedButton movementBackward = new myRoundedButton("<",18,10,9,4);
    private myRoundedButton movementUp = new myRoundedButton("^",10,8,5,2);
    private myRoundedButton movementDown = new myRoundedButton(" v",10,8,5,3);
    /////////////////////////DISABLED BUTTONS
    private myRoundedButton staticBallButton = new myRoundedButton(BallIcon, false,6,13,3,6);
    private myRoundedButton compass = new myRoundedButton(compassNorthIcon,false,15,5,7,3);

    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\   BUTTONS END
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
    
    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\   TEXT AND LABEL FIELDS START 
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
    /////////////////LABELS
    private JLabel optionLabel = new JLabel("Option:");
    private JLabel squareLabel = new JLabel("Square:");
    private JLabel directionLabel = new JLabel("Direction:");
    
    private JLabel timerLabel = new JLabel("DIGITAL TIMER",JLabel.CENTER);
    private JLabel dotsLabel = new JLabel(" : ");
    private JLabel dotsLabel2 = new JLabel(" : ");
    
    private JLabel scoreLabel = new JLabel("SCORE");
    private JLabel symbolsLabel = new JLabel(" < L : R > ");
    
    ////////////////TEXT FIELDS
    private JTextField optionTextField = new JTextField(5);
    private JTextField squareTextField = new JTextField(5);
    private JTextField directionTextField = new JTextField(5);
    
    private JTextField timerSeconds = new JTextField(2);
    private JTextField timerMinutes = new JTextField(2);
    private JTextField timerHours = new JTextField(2);
    
    private JTextField scoreLeftSide = new JTextField(2);
    private JTextField scoreRightSide = new JTextField(2);
    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\   TEXT AND LABEL FIELDS END
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
    
    
    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\   IMAGES AND BABY INSTANCES USED FOR DIFFERENT MODES
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
    ImageIcon baby1Image = new ImageIcon(CBabyBallBounce.class.getResource("images/baby1.png"));
	ImageIcon baby2Image = new ImageIcon(CBabyBallBounce.class.getResource("images/baby2.png"));
	
	Baby extraBaby1 = new Baby(baby2Image);
	Baby extraBaby2 = new Baby(baby2Image);
	Baby extraBaby3 = new Baby(baby1Image);
	Baby extraBaby4 = new Baby(baby1Image);
    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\    IMAGES AND BABY INSTANCES USED FOR DIFFERENT MODES
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
	
    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\   GETTERS AREA START
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
    public JTextField getScoreLeft()
    {
    	return scoreLeftSide;
    }
    
    public JTextField getScoreRight()
    {
    	return scoreRightSide;
    }
    
    public JTextField getSquareBox()
    {
    	return squareTextField;
    }
    
    public JTextField getDirectionBox()
    {
    	return directionTextField;
    }
    public myRoundedButton getCompass()
    {
    	return compass;
    }
    /*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * \\\\\\\   GETTERS AREA END
     *\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
     * */
    
    /////END OF DECLARATION AREA/////
    
    
    /**
     * Constructor of GUI class
     */
    public GUI()
    {
    	 addKeyListener(this);
    	 setFocusable(true);
    }

    
    /**
     * Creates the frame, configures it, adds a new KeyEventDispatcher to the KeyBoardFocusManager
     * and invokes the createGUI function that builds all panels and components in this frame.
     */
    void createFrame()
    {
    	ImageIcon frameIcon = new ImageIcon(CBabyBallBounce.class.getResource("images/greenfoot.jpg"));
    	this.createGUI(); 
        this.setSize(825, 585); 
        this.setVisible(true); 
        this.setResizable(false); 
        this.setTitle("CBabyBallBounce  – Baby Ball Bounce Application");
        this.setIconImage(frameIcon.getImage()); 
        /*The next two lines will get the size of the screen, and will set 
         *the location of the frame to the center of the screen,
         *by calculating the center of the screen that the program currently. 
         *Then it will calculate the center of the frame and subtract the values from the screen's.
         **/
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dim.width/2-this.getSize().width/2, dim.height/2-this.getSize().height/2);
        
        /*gets the current KeyBoardFocusManager*/
        KeyboardFocusManager manager = KeyboardFocusManager.getCurrentKeyboardFocusManager();
        /*creates a new KeyEventDispatcher*/
        localKeyDispatcher = new KeyDispatcher();
        /*adds the new KeyEventDispatcher to the KeyBoardFocusManager*/
        manager.addKeyEventDispatcher(localKeyDispatcher); 
    }
    
    /**
     * Builds every bar and menu in the frame by invoking each individual function.
     */
    private void createGUI() 
    {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(new FlowLayout(FlowLayout.LEADING,0,0)); 
        
        createMenuBar();
        createGameArea();
        createOptionBar();
        createControlBar();
    }
    
    
    /**
     * Creates the Menu Bar
     */
    private void createMenuBar()
    {
    	//creating Menu Bar
    	menuBar = new JMenuBar();
    	
    	//creating Scenario menu
    	JMenu scenarioMenu = new JMenu("Scenario");
    	exit = new JMenuItem("Exit"); //And the submenu
    	exit.addActionListener(this);
    	scenarioMenu.add(exit); //adding the submenu into Scenario menu
    	
    	//creating Edit menu
    	JMenu editMenu = new JMenu("Edit");
    	disableDefaultMode = new JMenuItem("Make babies move!");
    	disableDefaultMode.addActionListener(this);
    	editMenu.add(disableDefaultMode);
    	
    	    	
    	//creating Help menu
    	JMenu helpMenu = new JMenu("Help");
    	hTopicItem = new JMenuItem("Help Topic"); //first help submenu
    	hTopicItem.addActionListener(this);
    	aboutItem = new JMenuItem("About"); //second help submenu
    	aboutItem.addActionListener(this);
    	helpMenu.add(hTopicItem);//adding first help submenu
    	helpMenu.addSeparator(); // adding a separator between the two submenus
    	helpMenu.add(aboutItem); //adding second help submenu
    	menuBar.add(scenarioMenu);
    	menuBar.add(editMenu);
    	menuBar.add(helpMenu);
    	
    	this.setJMenuBar(menuBar);
    }


    /**
     * Creates the Game area. A JPanel that will later host the panel that the World will exist in.
     */
    private void createGameArea()
    {
        gameHostingPanel = new JPanel(new FlowLayout(FlowLayout.CENTER,0,28));
        gameHostingPanel.setPreferredSize(new Dimension(638,480));
        gameHostingPanel.setBorder(lowEtchBorder);
        this.add(gameHostingPanel);   
    }
    /**
     * Function that will reset the World if there is one, and will create one if not. 
     * This method is accessed by the main class(CBabyBallBounce) where the instance of 
     * the world is being made.
     * @param world - The world to construct.
     * @param frame - The frame to construct the world in.
     */
    public void createWorld(World world,GUI frame)
    {
    	localKeyDispatcher.setWorld(world);
    	localKeyDispatcher.setGUI(frame);
    	myWorld = world;
    	myWorld.giveGUI(frame);
    	frame.gameHostingPanel.removeAll();
    	frame.gameHostingPanel.revalidate();
    	frame.gameHostingPanel.repaint();
    	frame.gameHostingPanel.add(world);
    }
    
    
    /**
     * The option bar contains buttons that move the ball, direction of the ball, square the ball
     * is in currently, game Modes and other fields. 
     * This function creates the option bar.
     */
    private void createOptionBar()
    {
    	//the options panel
    	JPanel panel = new JPanel();
        panel.setPreferredSize(new Dimension(171,480)); /*set the dimensions of the JPanel*/
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS)); /*BoxLayout will align all components included along the Y axis*/
        panel.setBorder(lowEtchBorder); /*set the border of the JPanel*/
       
        
        Container pane = new Container(); /*create the primary container*/
        Container subpane = new Container();  /*create the secondary container*/
        
        //RESETING PANE AND SUBPANE + SETTING LAYOUTS
        pane = resettingPane(pane);
        subpane = resettingSubpane(subpane);
        
        //DIGITAL TIMER TEXT
        subpane.add(timerLabel); /*add label to the subpane*/
        pane.add(subpane); //add subpane to pane
        
        //RESETING SUBPANE
        subpane = resettingSubpane(subpane);
        
        //HOURS MINUTES SECONDS
        subpane.add(timerHours);
        timerHours.setEditable(false); /*make it so the contents of this text field cannot be altered by the user*/
        timerHours.setBackground(Color.black); /*change its background color to black*/
        timerHours.setForeground(Color.white); /*change the text's color to white*/
        timerHours.setText("00"); /*add text*/
        subpane.add(dotsLabel); /*add : label to the subpane*/
        
        subpane.add(timerMinutes); /*add text field for minutes to the subpane*/
        timerMinutes.setEditable(false); /*make it so the contents of this text field cannot be altered by the user*/
        timerMinutes.setBackground(Color.black); /*change its background color to black*/
        timerMinutes.setForeground(Color.white); /*change the text's color to white*/
        timerMinutes.setText("00"); /*add text*/
        subpane.add(dotsLabel2); /*add : label to the subpane*/
        
        subpane.add(timerSeconds);
        timerSeconds.setEditable(false);
        timerSeconds.setBackground(Color.black);
        timerSeconds.setForeground(Color.white);
        timerSeconds.setText("00");
        pane.add(subpane);
        
        //ADDING PANE 1
        panel.add(pane);
        
        //RESETING PANE AND SUBPANE + SETTING LAYOUTS
        pane = resettingPane(pane);
        subpane = resettingSubpane(subpane);
       
        //SCORE TEXT
        subpane.add(scoreLabel);
        pane.add(subpane);
        
        
        //RESETING SUBPANE
        subpane = resettingSubpane(subpane);
        
        
        //TEAMS SCORE TEXTBOXES
        subpane.add(scoreLeftSide);
        scoreLeftSide.setText("0");
        scoreLeftSide.setEditable(false);
        scoreLeftSide.setBackground(Color.black);
        scoreLeftSide.setForeground(Color.white);
        subpane.add(symbolsLabel);
        subpane.add(scoreRightSide);
        scoreRightSide.setText("0");
        scoreRightSide.setEditable(false);
        scoreRightSide.setBackground(Color.black);
        scoreRightSide.setForeground(Color.white);
        pane.add(subpane);
        
        //ADDING PANE 2
        panel.add(pane);
        
        //RESETING PANE AND SUBPANE + SETTING LAYOUTS
        pane = resettingPane(pane);
        subpane = resettingSubpane(subpane);
        
        //OPTION LABEL AND TEXTBOX
        subpane.setLayout(new FlowLayout(FlowLayout.CENTER, 32, 0));
        subpane.add(optionLabel);
        subpane.add(optionTextField);
        optionTextField.setEditable(false);
        optionTextField.setBackground(Color.white);
        optionTextField.setText("Default");
        optionTextField.setHorizontalAlignment(JTextField.CENTER); /*align the text in this text field to center*/
        pane.add(subpane);
        
        
        //RESETING SUBPANE
        subpane = resettingSubpane(subpane);
        
        //SQUARE LABEL AND TEXTBOX
        subpane.setLayout(new FlowLayout(FlowLayout.CENTER, 30, 5));
        subpane.add(squareLabel);
        subpane.add(squareTextField);
        squareTextField.setEditable(false);
        squareTextField.setBackground(Color.white);
        squareTextField.setHorizontalAlignment(JTextField.CENTER);
        pane.add(subpane);
        
        //RESETING SUBPANE
        subpane = resettingSubpane(subpane);
        
        //DIRECTION LABEL AND TEXTBOX
        subpane.setLayout(new FlowLayout(FlowLayout.CENTER, 20, 0));
        subpane.add(directionLabel);
        subpane.add(directionTextField);
        directionTextField.setEditable(false);
        directionTextField.setBackground(Color.white);
        directionTextField.setHorizontalAlignment(JTextField.CENTER);
        pane.add(subpane);
        
        //ADDING PANE 3
        panel.add(pane);
        
        //RESETING PANE AND SUBPANE + SETTING LAYOUTS
        pane = resettingPane(pane);
        subpane = resettingSubpane(subpane);
        
        
        //CREATING NAVIGATION PANEL START /////////
        //USING GRIDBAG LAYOUT
        pane.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.weightx = 1;
        //EMPTY BUTTON
        c.gridx = 0;
        c.gridy = 0;
        c.fill = GridBagConstraints.CENTER;
        c.ipadx = 55;
        c.ipady = 25;
        pane.add(createEmptyButton(55, 30),c);
        
        c.fill = GridBagConstraints.CENTER;
        c.gridx = 1;
        c.gridy = 0;
        c.ipadx = 5;
        c.ipady = 3;
        movementUp.addActionListener(this);
        pane.add(movementUp,c);
        
        //EMPTY BUTTON
        c.fill = GridBagConstraints.CENTER;
        c.gridx = 2;
        c.gridy = 0;
        c.ipadx = 55;
        c.ipady = 25;
        pane.add(createEmptyButton(50, 30),c);
        
        /////////////////////
        c.fill = GridBagConstraints.CENTER;
        c.ipadx = 10;
        c.ipady = 7;
        c.gridx = 0;
        c.gridy = 1;
        c.weightx = 1;
        movementBackward.addActionListener(this);
        pane.add(movementBackward,c);
        
        c.fill = GridBagConstraints.CENTER;
        c.ipadx = 0;
        c.ipady = 0;
        c.gridx = 1;
        c.gridy = 1;
        pane.add(staticBallButton,c);
        
        c.fill = GridBagConstraints.CENTER;
        c.ipadx = 10;
        c.ipady = 7;
        c.gridx = 2;
        c.gridy = 1;
        movementForward.addActionListener(this);
        pane.add(movementForward,c);
        
        
        /////////////////////////
        c.fill = GridBagConstraints.CENTER;
        c.ipadx = 55;
        c.ipady = 25;
        c.gridx = 0;
        c.gridy = 2;
        pane.add(createEmptyButton(50, 30),c);
        
        c.fill = GridBagConstraints.CENTER;
        c.ipadx = 5;
        c.ipady = 3;
        c.gridx = 1;
        c.gridy = 2;
        movementDown.addActionListener(this);
        pane.add(movementDown,c);
      
        c.ipadx = 55;
        c.ipady = 25;
        c.gridx = 2;
        c.gridy = 2;
        c.fill = GridBagConstraints.CENTER;
        pane.add(createEmptyButton(50, 30),c);
        
        panel.add(pane);
        //CREATING NAVIGATION PANEL END /////////
        
        //RESETING PANE
        pane = resettingPane(pane);
        
        //COMPASS AREA START //////
        pane.setLayout(new FlowLayout(FlowLayout.CENTER,0,0));
        pane.add(compass);
        
        
        panel.add(pane);
        //COMPASS AREA END //////
        
        
        //RESETING PANE
        //ADDING RIGID AREA
        pane = resettingPane(pane);
        
        pane.add(Box.createRigidArea(new Dimension(this.getWidth(), this.getHeight() + 20)));
        
        panel.add(pane);
        
        //RESETING PANE
        //CREATING THE OPTION BUTTONS 
        pane = resettingPane(pane);
        
        pane.setPreferredSize(new Dimension(200, 100));
        pane.setLayout(new GridBagLayout());
        GridBagConstraints c2 = new GridBagConstraints();
        c2.fill = GridBagConstraints.BOTH;
        c2.weightx = 1;
        c2.ipadx = 50;
        c2.ipady = 8;
        c2.gridx = 0;
        c2.gridy = 0;
        button2Players.addActionListener(this);
        pane.add(button2Players,c2);
        
        c2.insets = new Insets(this.getInsets().top, this.getInsets().left -10, this.getInsets().bottom, this.getInsets().right);
        c2.gridx = 1;
        c2.gridy = 0;
        button4Players.addActionListener(this);
        pane.add(button4Players,c2);
        
        c2.gridx = 0;
        c2.gridy = 1;
        buttonMultiPlayer.addActionListener(this);
        pane.add(buttonMultiPlayer,c2);
        
        c2.gridx = 1;
        c2.gridy = 1;
        buttonExit.addActionListener(this);
        pane.add(buttonExit,c2);
        panel.add(pane);
        
        this.add(panel); 
    }

    

    /**
     * This function builds the control bar on the bottom of the frame. The control
     * bar contains the buttons that will control the flow of the game(run,pause,reset,act)
     * and also the slider that will adjust the speed of of the game.
     */
    private void createControlBar()
    {
    	panel = new JPanel();
    	panel.setLayout(new FlowLayout(FlowLayout.CENTER,150,0));
    	panel.setPreferredSize(new Dimension(850,200));
    	panel.setBorder(lowEtchBorder);
    	
    	Container subpane = new Container();
    	subpane = resettingSubpane(subpane);
    	
    	buttonRun.setPreferredSize(buttonPause.getPreferredSize());
    	subpane.add(buttonAct);
    	subpane.add(buttonRun);
    	subpane.add(buttonReset);
    	panel.add(subpane);
    	
    	subpane = resettingSubpane(subpane);
    	subpane.add(new JLabel("Speed:"));
    	slider = new JSlider(JSlider.HORIZONTAL,0,1000,200);
    	slider.setMajorTickSpacing(200);
    	slider.setPaintTicks(true);
    	slider.setEnabled(true);
    	slider.setInverted(true);
    	slider.setFocusable(false);
    	
    	subpane.add(slider);
    	subpane.repaint();
    	subpane.revalidate();


    	panel.add(subpane);
    	
    	buttonAct.addActionListener(this);
    	buttonReset.addActionListener(this);
    	buttonRun.addActionListener(this);
    	slider.addChangeListener(this);
    	this.add(panel);
    }
    

    
    /**
     * Support function used from createControlBar() and createOptionBar() to reset
     * an individual Container. Each Container from this function will contain other 
     * sub-containers.
     * @param pane - The primary Container to be reseted 
     * @return The reseted primary Container
     */
    private Container resettingPane(Container pane)
    {
    	pane = new Container();
        pane.setLayout(new BoxLayout(pane, BoxLayout.PAGE_AXIS)); 
        return pane;
    }
    
    /**
     * Support function used from createControlBar() and createOptionBar() to reset
     * an individual sub-Container. Each sub-container will be added to a bigger 
     * container before added to the panel.
     * @param subpane - The secondary Container to be reseted.
     * @return The reseted secondary Container
     */
    private Container resettingSubpane(Container subpane)
    {
    	 subpane = new Container();
         subpane.setLayout(new FlowLayout());
         return subpane;
    }
    
    /**
     * Creates an empty and pressed looking button to be used in the Option bar
     * @param width - The width of the button
     * @param height - The height of the button
     * @return The created button
     */
    private JButton createEmptyButton(int width, int height) 
	{
		JButton myButton = new JButton();
		myButton.setPreferredSize(new Dimension(width, height)); //setting button dimensions
		myButton.setContentAreaFilled(false); //removing the blue color filling that buttons have by default
		myButton.setBorderPainted(true); //allowing it to have a border
		myButton.setBorder(BorderFactory.createLoweredBevelBorder()); //picking the border that will make it look pressed
		return myButton; //return it
	}
    
    
    /**
     * Depending on the direction given, this function will change the compass icon in 
     * the option bar. Used by the ball.
     * @param direction - As a String "E","S","W","N"
     */
    public void changeCompass(String direction)
    {
    	switch (direction) {
		case "E":
			compass.setDisabledIcon(compassEastIcon);
			break;
		case "S":
			compass.setDisabledIcon(compassSouthIcon);
			break;
		case "N":
			compass.setDisabledIcon(compassNorthIcon);
			break;
		case "W":
			compass.setDisabledIcon(compassWestIcon);
			break;

		default:
			break;
		}
    }
    
    /**
     *Alters the pressed state of the buttonMultiPlayer to <code>true</code> or <code>false</code>
     *depending on the parameter given. If state is <code>true</code>, the button changes color. 
     *If <code>false</code> it returns to the original color. 
     * @param state - State to set the button
     */
    private void multiButtonPressed(boolean state)
    {
    	if(state) //if state is true
    	{
        	buttonMultiPlayer.setBackground(Color.RED); //change button background color to red
    		buttonMultiPlayer.repaint(); //repaint the button
    		buttonMultiPlayer.setPressed(state); //update its property isButtonPressed to true
    		optionTextField.setForeground(Color.red); //on the option text field, text becomes red
    	}else
    	{
    		/*get the initial background of the button and set it as current*/
    		buttonMultiPlayer.setBackground(buttonMultiPlayer.getInitBackground()); 
    		buttonMultiPlayer.repaint(); //repaint the button
    		buttonMultiPlayer.setPressed(state); //update its property isButtonPressed to false
    		optionTextField.setForeground(null); //remove foreground color (default black)
    	}
    }
    
    /**
     * Checks if the condition for game ending has been met.
     * If so, it checks which scoring text box contains the number that defines the game condition,
     * and displays a message dialog that displays the winning team.
     * Then, it programmatically clicks Reset button.
     */
    private void checkIfGameOver()
    {
    	String teamWon = null;
    	
    	if(myWorld.isTheGameOver())
    	{
    		timerFunctionality.stop();
    		timerDisplay.stop();
    		if(scoreLeftSide.getText().equals(String.valueOf(myWorld.getGameOverCondition())))
    		{
    			teamWon = "LEFT";
    		}else if(scoreRightSide.getText().equals(String.valueOf(myWorld.getGameOverCondition())))
    		{
    			teamWon = "RIGHT";
    		}
    		JOptionPane.showMessageDialog(this, "GAME OVER! \n" + teamWon + " team won the Game!");
    		buttonReset.doClick();
    	}
    }
    
    /**
     * Disables or enables the default mode in World, and the submenu.
     * This method is used almost exclusively to disable default mode, 
     * as a new instance of the World has default mode set to true.
     * After disabled, default mode cannot be enabled again unless the World
     * is reseted. 
     * 
     * @param disabled - true to disable, false to enable
     */
    private void defaultModeDisabled(boolean disabled)
    {
    	if(disabled)
    	{
        	myWorld.setDefaultMode(false);
    		disableDefaultMode.setEnabled(false);
    	}else
    	{
        	myWorld.setDefaultMode(true);
    		disableDefaultMode.setEnabled(true);
    	}

    }

    public void actionPerformed(ActionEvent event) 
    {
    	if(event.getSource().equals(timerDisplay))
    	{
    		timerHours.setText(Integer.toString(ticks / 3600));
    		timerMinutes.setText(Integer.toString(ticks / 60));
            timerSeconds.setText(Integer.toString(ticks % 60));
        	ticks = ticks + 1;
    	}
    	if(event.getSource().equals(timerFunctionality))
    	{
        	myWorld.allActorsAct();
        	checkIfGameOver();
    	}
    	if(event.getSource().equals(button2Players))
    	{
    		if(optionTextField.getText().equals("Default"))
    		{
    			defaultModeDisabled(true);
    			optionTextField.setText("2Players");
    			button2Players.setEnabled(false);
        		
        		myWorld.addActor(extraBaby1, 400, 250);
        		/*changing the ZOrder of this component to 0 will paint it on the front 
        		 * of other components*/
        		myWorld.setComponentZOrder(extraBaby1, 0);
        		
        		myWorld.addActor(extraBaby3, 80, 100);
        		/*changing the ZOrder of this component to 0 will paint it on the front 
        		 * of other components*/
        		myWorld.setComponentZOrder(extraBaby3, 0);
        		
        		myWorld.assignTeamsToBabies();
        		myWorld.repaint();
        		myWorld.revalidate();
    		}else if(optionTextField.getText().equals("4Players"))
    		{
    			optionTextField.setText("2Players");
    			button2Players.setEnabled(false);
    			button4Players.setEnabled(true);
    			
    			myWorld.removeActor(extraBaby2);
    			myWorld.removeActor(extraBaby4);
    			
    			myWorld.repaint();
        		myWorld.revalidate();
    		}
    	}
    	if(event.getSource().equals(button4Players))
    	{
    		button4Players.setEnabled(false);
    		
    		if(optionTextField.getText().equals("Default"))
    		{
    			defaultModeDisabled(true);
    			optionTextField.setText("4Players");
        		
        		myWorld.addActor(extraBaby1, 400, 250);
        		/*changing the ZOrder of this component to 0 will paint it on the front 
        		 * of other components*/
        		myWorld.setComponentZOrder(extraBaby1, 0);
        		
        		
        		myWorld.addActor(extraBaby3, 80, 100);
        		myWorld.setComponentZOrder(extraBaby3, 0);
        		
        		myWorld.addActor(extraBaby2, 440, 250);
        		myWorld.setComponentZOrder(extraBaby2, 0);
        		
        		myWorld.addActor(extraBaby4, 40, 150);
        		myWorld.setComponentZOrder(extraBaby4, 0);
        		
        		myWorld.assignTeamsToBabies();
        		myWorld.repaint();
        		myWorld.revalidate();
        		
    		}else if(optionTextField.getText().equals("2Players"))
    		{
    			optionTextField.setText("4Players");
    			button2Players.setEnabled(true);
        		
        		myWorld.addActor(extraBaby2, 440, 250);
        		myWorld.setComponentZOrder(extraBaby2, 0);
        		
        		myWorld.addActor(extraBaby4, 40, 150);
        		myWorld.setComponentZOrder(extraBaby4, 0);
        		
        		myWorld.assignTeamsToBabies();
        		myWorld.repaint();
        		myWorld.revalidate();
    		}
    	}
    	if(event.getSource().equals(buttonMultiPlayer))
    	{
    		boolean timersWereRunning = timerFunctionality.isRunning();
    		/*check if Multi button is NOT at pressed state*/
    		if(!buttonMultiPlayer.isButtonPressed())
    		{
    			//Object will hold the options available to OptionPane
    			Object[] options = { "LEFT", "RIGHT","CANCEL" };
    			//stop both timers
        		timerDisplay.stop();
        		timerFunctionality.stop();
        		//prompt the user with a dialog box to get the team he would like to play with. Pressing cancel 
        		//changes nothing
        		int answer = JOptionPane.showOptionDialog(this, "Please select your team", "Team Selection", 
        				JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[2]);
        		//check the user's input
        		switch (answer) {
    			case 0: //0 represents "LEFT"
    				myWorld.enableMultiMode("LEFT"); //enable manual mode for the World, giving the team as an argument
    				multiButtonPressed(true); //set Multi button's state to pressed
    				defaultModeDisabled(true);
    				break;
    			case 1: //1 represents "RIGHT"
    				myWorld.enableMultiMode("RIGHT"); //enable manual mode for the World, giving the team as an argument
    				multiButtonPressed(true); //set Multi button's state to pressed
    				defaultModeDisabled(true);
    				break;

    			default:
    				break;
    			}
        		if(timersWereRunning) //if the timers were running when the user pressed Multi Button
        		{
        			//start them again
            		timerDisplay.start();
            		timerFunctionality.start();
        		}
    		}else // in the case that Multi button was at pressed state 
    		{
    			myWorld.disableMultiMode(); //disable manual mode
    			multiButtonPressed(false); //set the button at NOT pressed state
    		}
    	}
    	if(event.getSource().equals(buttonExit))
    	{
    		System.exit(0);
    	}
    	if(event.getSource().equals(buttonReset))
    	{
    		/*Make all components turn to their initial state
    		 * restart and stop timers
    		 * if buttonPaused was in the Control Panel replace it with buttonRun
    		 * display 0 time in Digital Timer text boxes
    		 * create a new instance of the World*/
    		ticks=0;
    		timerDisplay.restart();
    		timerDisplay.stop();
    		timerFunctionality.restart();
    		timerFunctionality.stop();
    		
    		if(buttonReset.getParent().getComponent(1).equals(buttonPause))
    		{
    			buttonPause.removeActionListener(this);
    			buttonPause.replaceButtonWith(buttonRun);
    			buttonRun.addActionListener(this);
    		}
    		timerHours.setText(Integer.toString(ticks / 3600));
    		timerMinutes.setText(Integer.toString(ticks / 60));
            timerSeconds.setText(Integer.toString(ticks % 60));
            
            scoreLeftSide.setText("0");
            scoreRightSide.setText("0");
            optionTextField.setText("Default");
            squareTextField.setText("");
            directionTextField.setText("");
            
            button2Players.setEnabled(true);
            button4Players.setEnabled(true);
            multiButtonPressed(false);
            defaultModeDisabled(false);
            
    		createWorld(new World(13,16,32),this);	
    	}
    	if(event.getSource().equals(buttonAct))
    	{
    		myWorld.allActorsAct();
    	}
    	if(event.getSource().equals(buttonRun))
    	{
    		if(ticks == 0) //Don't waste 1 second. instantly display 1
    		{
    			ticks = 1;
    		}
    		/*start the timers*/
    		timerDisplay.start();
    		timerFunctionality.start();
    		/*replace buttonRun with buttonPause in the Control Panel*/
    		buttonRun.removeActionListener(this);
    		buttonRun.replaceButtonWith(buttonPause);
    		buttonPause.addActionListener(this);
    	}
      	if(event.getSource().equals(buttonPause))
    	{
      		/*stop the timers*/
    		timerDisplay.stop();
    		timerFunctionality.stop();
    		/*replace buttonPause with buttonRun in the Control Panel*/
    		buttonPause.removeActionListener(this);
    		buttonPause.replaceButtonWith(buttonRun);
    		buttonRun.addActionListener(this);
    	}
      	/*event handling for ball navigation buttons in Option Panel, will only be performed if 
      	 * timerFunctionality is running*/
    	if(event.getSource().equals(movementDown) && timerFunctionality.isRunning())
    	{
    		myWorld.Ball1.controlledMove(90, 32);
    	}
    	if(event.getSource().equals(movementBackward) && timerFunctionality.isRunning())
    	{
    		myWorld.Ball1.controlledMove(180, 32);
    	}
    	if(event.getSource().equals(movementForward) && timerFunctionality.isRunning())
    	{
    		myWorld.Ball1.controlledMove(0, 32);
    	}
    	if(event.getSource().equals(movementUp) && timerFunctionality.isRunning())
    	{
    		myWorld.Ball1.controlledMove(270, 32);
    	}
    	if(event.getSource().equals(aboutItem))
    	{
    		JOptionPane.showMessageDialog(this, "Developed by Joyal Joshi for the University of Northampton  ( NAMI College), \n "
    											+ "as a Project for Problem Solving and Programming (PSP) | CSY1020 module. ", "About", 
    											JOptionPane.INFORMATION_MESSAGE, null);
    	}
    	if(event.getSource().equals(hTopicItem))
    	{
    		JOptionPane.showMessageDialog(this, "Movement: \n"
    				+ "\u26AB \t\t\t\t  Navigational Key  \n\n"
    				+ "					 UP 	    \t\t\t\t\t       \u25B6    \u2B06 \n"   //for up arrow
    				+ "					 DOWN 		\t\t\t\t\t    \u25B6    \u2B07 \n"   //for down arrow
    				+ "					 LEFT 		\t\t\t\t\t       \u25B6   \u2B05 \n"	//for left arrow
    				+ "					 RIGHT 		\t\t\t\t\t     \u25B6   \u27A1 \n\n"	// for right arrow
    				+ "\u26AB  \t\t\t\t Options: \n\n"
    				+ "                  \u0032 Players    \t\t\t\t\t       \u25B6 	 Players  -     Each team has two players \n\n"
    				+ "                  \u0034 Players    \t\t\t\t\t	       \u25B6 	 Players  -     Each team has three players \n\n"
    				+ "                  Multi  Mode:              If enabled, will give the player control of one of the main \n"
    				+ "                                                      babies (either the right or the left side). The baby can move only up and down \n"
    				+ "                                                      using the UP and DOWN arrow keys. While, the player can move the ball\n"
    				+ "                                                      with the buttons in the option panel."
    				+ " If disabled, the baby returns to its original state.\n\n"
    				+ "\u26AB  \t\t\t\t Game Control \n"
    				+ "                  Act  	\t\t\t\t	            \u25B6 		       All actors take a single action. \n"
    				+ "                  Run  	\t\t\t\t	           \u25B6 		       All actors take actions until paused. \n"
    				+ "                  Pause	\t\t\t\t	        \u25B6 		       Pauses the game. Visible only when the game is running. \n"
    				+ "                  Reset	\t\t\t\t	         \u25B6 		       Starts a new game. \n\n"
    				+ "\u26AB  \t\t\t\t Slider control      \u25B6        Adjusts the game speed. \n\n"
    				+ "			\u2B1B  \t\t\t\t Edit 	        	\u27A1     Make babies move! | Submenu | enables baby movement.", "Instructions", JOptionPane.INFORMATION_MESSAGE, null);
    	}
    	if(event.getSource().equals(disableDefaultMode))
    	{
    		defaultModeDisabled(true);
    	}
    	if(event.getSource().equals(exit))
    	{
    		System.exit(0);
    	}
    }
    
	@Override
	public void stateChanged(ChangeEvent e) {
		timerFunctionality.setDelay(slider.getValue());
	}
    
    

    
	@Override
	public void keyPressed(KeyEvent arg0) 
	{
		
	}

	@Override
	public void keyReleased(KeyEvent arg0) 
	{
		
	}

	@Override
	public void keyTyped(KeyEvent arg0) 
	{
		
	}


}