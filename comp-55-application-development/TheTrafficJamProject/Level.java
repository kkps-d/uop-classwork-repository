import java.util.*;


public class Level {	
	private Board board;
	private int numRows, numCols;
	private Vehicle currentVehicle;
	private Space goalSpace;
	
	public Level(int nRows, int nCols) {
		numRows = nRows;
		numCols = nCols;
		setupLevel();
	}
	
	public void setupLevel() {
		board = new Board(numRows, numCols);
		board.addVehicle(VehicleType.TRUCK, 0, 2, 3, true);
		board.addVehicle(VehicleType.MYCAR, 2, 0, 2, false);
		board.addVehicle(VehicleType.AUTO, 0, 4, 2, false);
		board.addVehicle(VehicleType.AUTO, 1, 4, 2, true);
		board.addVehicle(VehicleType.AUTO, 1, 5, 2, true);
		board.addVehicle(VehicleType.AUTO, 3, 3, 2, true);
		board.addVehicle(VehicleType.AUTO, 4, 4, 2, false);
		setGoalSpace(new Space(2,5));
	}
	
	
	/**
	 * @return the number of columns on the board
	 */
	public int getColumns() {
		//TODO: have this return the number of columns in the level
		return numCols;
	}
	
	public int getRows() {
		//TODO: have this return the number of columns in the level
		return numRows;
	}
	
	//Methods already defined for you
	/**
	 * generates the string representation of the level, including the row and column headers to make it look like
	 * a table
	 * 
	 * @return the string representation
	 */
	public String toString() {
		String result = generateColHeader(getColumns());
		result+=addRowHeader(board.toString());
		return result;
	}
	
	/**
	 * This method will add the row information
	 * needed to the board and is used by the toString method
	 * 
	 * @param origBoard the original board without the header information
	 * @return the board with the header information
	 */
	private String addRowHeader(String origBoard) {
		String result = "";
		String[] elems = origBoard.split("\n");
		for(int i = 0; i < elems.length; i++) {
			result += (char)('A' + i) + "|" + elems[i] + "\n"; 
		}
		return result;
	}
	
	/**
	 * This one is responsible for making the row of column numbers at the top and is used by the toString method
	 * 
	 * @param cols the number of columns in the board
	 * @return if the # of columns is five then it would return "12345\n-----\n"
	 */
	private String generateColHeader(int cols) {
		String result = "  ";
		for(int i = 1; i <= cols; i++) {
			result+=i;
		}
		result+="\n  ";
		for(int i = 0; i < cols; i++) {
			result+="-";
		}
		result+="\n";
		return result;
	}
	
	private void setGoalSpace(Space space) {
		goalSpace = space;
	}
	
	public Space getGoalSpace() {
		return goalSpace;
	}
	
	public boolean getVehicle(Space space) {
		currentVehicle = board.getVehicle(space);
		if (currentVehicle != null) {
			return true;
		} else {
			return false;
		}
	}
	
	public Vehicle getVehicleObject(Space space) {
		currentVehicle = board.getVehicle(space);
		if (currentVehicle != null) {
			return currentVehicle;
		} else {
			return null;
		}
	}
	
	public boolean canMoveNumSpaces(Space start, int numSpaces) {
		return board.canMoveNumSpaces(start, numSpaces);
	}
	
	public void moveNumSpaces(Space start, int numSpaces) {
		board.moveNumSpaces(start, numSpaces);
	}
	
	public boolean passedLevel() {
		if (board.getVehicle(goalSpace) == null) return false;
		if (board.getVehicle(goalSpace).getVehicleType() == VehicleType.MYCAR) {
			return true;
		} else {
			return false;
		}
	}
	
	public ArrayList<Vehicle> getVehiclesonBoard() {
		return board.getVehiclesonBoard();
	}
}
