import acm.program.*;

import java.awt.Color;
import java.awt.event.MouseEvent;

import acm.graphics.*;

public class GraphicsGame extends GraphicsProgram {
	/**
	 * Here are all of the constants
	 */
	public static final int PROGRAM_WIDTH = 500;
	public static final int PROGRAM_HEIGHT = 500;
	public static final String LABEL_FONT = "Arial-Bold-22";
	public static final String EXIT_SIGN = "EXIT";
	public static final String IMG_FILENAME_PATH = "images/";
	public static final String IMG_EXTENSION = ".png";
	public static final String VERTICAL_IMG_FILENAME = "_vert";

	// TODO declare your instance variables here
	private Level level;
	private double x, y;
	private Space currentSpace;
	private int steps;
	private int xOffset, yOffset;
	
	private Space mouseInitial, mouseCurrent;
	private GObject toDrag;
	
	public void init() {
		setSize(PROGRAM_WIDTH, PROGRAM_HEIGHT);
		level = new Level(6, 6);
		steps = 0;
	}

	public void run() {
		init();
		drawLevel();
		addMouseListeners();
	}

	private void drawLevel() {
		removeAll();
		drawGridLines();
		drawCars();
		drawWinningTile();
		GLabel counter = new GLabel("" + steps, 5, 75);
		counter.setFont("Arial-Bold-30");
		add(counter);
	}

	/**
	 * This should draw the label EXIT and add it to the space that represents
	 * the winning tile.
	 */
	private void drawWinningTile() {
		double x = (level.getGoalSpace().getCol()) * spaceWidth();
		double y = (level.getGoalSpace().getRow() + 1) * spaceHeight();
		GLabel label = new GLabel(EXIT_SIGN, x, y - spaceHeight()/2);
		label.setFont(LABEL_FONT);
		add(label);
	}

	/**
	 * draw the lines of the grid. Test this out and make sure you have it
	 * working first. Should draw the number of grids based on the number of
	 * rows and columns in Level
	 */
	private void drawGridLines() {
		for (int i = 1; i < level.getColumns(); i++) {
			add(new GLine(spaceWidth() * i, 0, spaceWidth() * i, PROGRAM_HEIGHT));
			add(new GLine(0, spaceHeight() * i, PROGRAM_WIDTH, spaceHeight()* i));
		}
	}

	/**
	 * Maybe given a list of all the cars, you can go through them and call
	 * drawCar on each?
	 */
	private void drawCars() {
		for (Vehicle v : level.getVehiclesonBoard()) {
			drawCar(v);
		}
	}

	/**
	 * Given a vehicle object, which we will call v, use the information from
	 * that vehicle to then create a GImage and add it to the screen. Make sure
	 * to use the constants for the image path ("/images"), the extension ".png"
	 * and the additional suffix to the filename if the object is vertical when
	 * creating your GImage. Also make sure to set the images size according to
	 * the size of your spaces
	 * 
	 * @param v
	 *            the Vehicle object to be drawn
	 */
	private void drawCar(Vehicle v) {
		GImage temp;
		String name;
		double x, y;
		
		name = v.getVehicleType().toString();
		if (v.isVertical()) {
			name += VERTICAL_IMG_FILENAME;
		}
		name += IMG_EXTENSION;
		
		x = v.spacesOccupied()[0].getCol() * spaceWidth();
		y = v.spacesOccupied()[0].getRow() * spaceHeight();
		temp = new GImage(name, x, y);

		double newWidth, newHeight;
		
		newWidth = temp.getWidth() + (spaceWidth() - temp.getWidth());
		newHeight = temp.getHeight() + (spaceHeight() - temp.getHeight());
		if(v.isVertical()) {
			newHeight *= v.spacesOccupied().length;
		} else {
			newWidth *= v.spacesOccupied().length;
		}
		temp.setSize(newWidth, newHeight);
		add(temp);
	}

	/**
	 * Given a xy coordinates, return the Vehicle that is currently at those x
	 * and y coordinates, returning null if no Vehicle currently sits at those
	 * coordinates.
	 * 
	 * @param x
	 *            the x coordinate in pixels
	 * @param y
	 *            the y coordinate in pixels
	 * @return the Vehicle object that currently sits at that xy location
	 */
	private Vehicle getVehicleFromXY(double x, double y) {
		return level.getVehicleObject(convertXYToSpace(x, y));
	}

	/**
	 * This is a useful helper function to help you calculate the number of
	 * spaces that a vehicle moved while dragging so that you can then send that
	 * information over as numSpacesMoved to that particular Vehicle object.
	 * 
	 * @return the number of spaces that were moved
	 */
	private int calculateNumSpaces() {
		int movedRow = mouseCurrent.getRow() - mouseInitial.getRow();
		int movedCol = mouseCurrent.getCol() - mouseInitial.getCol();
		
		if (movedRow == 0) {
			return movedCol;
		} else if (movedCol == 0) {
			return movedRow;
		} else {
			return 0;
		}
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		x = e.getX();
		y = e.getY();
		currentSpace = convertXYToSpace(x, y);
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		toDrag = getElementAt(e.getX(), e.getY());
		if (toDrag != null) {
			xOffset = e.getX() - (int)toDrag.getX();
			yOffset = e.getY() - (int)toDrag.getY();
		}
		x = e.getX();
		y = e.getY();
		mouseInitial = convertXYToSpace(x, y);
		currentSpace = convertXYToSpace(x, y);
		/*
		if (level.getVehicleObject(currentSpace) != null) {
			System.out.println("Current vehicle: " + getVehicleFromXY(x, y).toString());
		} else {
			System.out.println("No vehicle selected");
		}
		*/
	}
	
	double afterLimit = 0;
	double beforeLimit = 0;
	boolean imposeAfterLimit = false;
	boolean imposeBeforeLimit = false;
	Vehicle temp = null;
	
	@Override
	public void mouseDragged(MouseEvent e) {
		Vehicle currentVehicle = level.getVehicleObject(currentSpace);
		double endX, endY;

		if (!(toDrag instanceof GImage)) return;
		
		if (toDrag != null) {
			if (currentVehicle.isVertical()) {
				toDrag.setLocation(toDrag.getX(), e.getY() - yOffset);
			} 
			if (!currentVehicle.isVertical()) {
				toDrag.setLocation(e.getX() - xOffset, toDrag.getY());
			}

			// Limiters 
			if (toDrag.getX() < 0) toDrag.setLocation(0, toDrag.getY());
			if (toDrag.getY() < 0) toDrag.setLocation(toDrag.getX(), 0);
			if (toDrag.getX() + toDrag.getWidth() > PROGRAM_HEIGHT) toDrag.setLocation(PROGRAM_HEIGHT - toDrag.getWidth(), toDrag.getY());
			if (toDrag.getY() + toDrag.getHeight() > PROGRAM_WIDTH) toDrag.setLocation(toDrag.getX(), PROGRAM_WIDTH - toDrag.getHeight());
			if (currentVehicle.isVertical()) {
				endX = toDrag.getX();
				endY = toDrag.getY() + toDrag.getHeight();
				temp = getVehicleFromXY(endX, endY);
				if (imposeAfterLimit == false) {
					if (temp != null && temp != currentVehicle) {
						afterLimit = endY;
						imposeAfterLimit = true;
					}
				}
				if (endY > afterLimit && imposeAfterLimit == true) {
					toDrag.setLocation(toDrag.getX(), afterLimit - toDrag.getHeight());
				}
				
				endX = toDrag.getX();
				endY = toDrag.getY();
				temp = getVehicleFromXY(endX, endY);
				if (imposeBeforeLimit == false) {
					if (temp != null && temp != currentVehicle) {
						beforeLimit = endY;
						imposeBeforeLimit = true;
					}
				}
				if (endY < beforeLimit && imposeBeforeLimit == true) {
					toDrag.setLocation(toDrag.getX(), beforeLimit);
				}
			} else {
				endX = toDrag.getX() + toDrag.getWidth();
				endY = toDrag.getY();
				temp = getVehicleFromXY(endX, endY);
				if (imposeAfterLimit == false) {
					if (temp != null && temp != currentVehicle) {
						afterLimit = endX;
						imposeAfterLimit = true;
					}
				}
				if (endX > afterLimit && imposeAfterLimit == true) {
					toDrag.setLocation(afterLimit - toDrag.getWidth(), toDrag.getY());
				}
				
				endX = toDrag.getX();
				endY = toDrag.getY();
				temp = getVehicleFromXY(endX, endY);
				if (imposeBeforeLimit == false) {
					if (temp != null && temp != currentVehicle) {
						beforeLimit = endX;
						imposeBeforeLimit = true;
					}
				}
				if (endX < beforeLimit && imposeBeforeLimit == true) {
					toDrag.setLocation(beforeLimit, toDrag.getY());
				}
			}
			
		}
	}
	
	@Override
	public void mouseReleased(MouseEvent e) {
		imposeBeforeLimit = false;
		imposeAfterLimit = false;
		mouseCurrent = convertXYToSpace(e.getX(), e.getY());
		if (level.getVehicleObject(currentSpace) != null) {
			if (level.canMoveNumSpaces(currentSpace, calculateNumSpaces()) && calculateNumSpaces() != 0) {
				System.out.println("Spaces moved: " + calculateNumSpaces());
				level.moveNumSpaces(currentSpace, calculateNumSpaces());
				steps++;
			}
		}
		mouseInitial = mouseCurrent = currentSpace = null;
		drawLevel();
		if (level.passedLevel()) {
			passedLevel();
		}
	}
	
	private void passedLevel() {
		removeAll();
		GLabel temp;
		temp = new GLabel("Congratulations!", 10, 50);
		temp.setColor(Color.CYAN);
		temp.setFont("Arial-Bold-60");
		add(temp);
		temp = new GLabel("You have cleared this level!", 10, 100);
		temp.setColor(Color.GREEN);
		temp.setFont("Arial-Bold-35");
		add(temp);
		temp = new GLabel("Steps: " + steps, 10, 150);
		temp.setColor(Color.BLACK);
		temp.setFont("Arial-Bold-30");
		add(temp);
	}
	
	/**
	 * Another helper function/method meant to return the space given an x and y
	 * coordinate system. Use this to help you write getVehicleFromXY
	 * 
	 * @param x
	 *            x-coordinate (in pixels)
	 * @param y
	 *            y-coordinate (in pixels)
	 * @return the Space associated with that x and y
	 */
	private Space convertXYToSpace(double x, double y) {
		double row = y / spaceHeight();
		double col = x / spaceWidth();
		
		// System.out.println(new Space((int)row, (int)col));
		
		return new Space((int)row, (int)col);
	}

	/**
	 * 
	 * @return the width (in pixels) of a single space in the grid
	 */
	private double spaceWidth() {
		return PROGRAM_WIDTH / level.getColumns();
	}

	/**
	 * 
	 * @return the height in pixels of a single space in the grid
	 */
	private double spaceHeight() {
		return PROGRAM_HEIGHT / level.getRows();
	}

}
