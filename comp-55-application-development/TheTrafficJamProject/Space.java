/**
 * Simple class that represents a row and a column, with simple getters and setters for both
 * @author Osvaldo
 */

public class Space {
	//TODO Put your instance variables here
	private int row, col;
	/**
	 * The constructor that will set up the object to store a row and column
	 * 
	 * @param row
	 * @param col
	 */
	public Space(int row, int col) {
		//TODO: this is the constructor, you'll need to fill this in
		this.row = row;
		this.col = col;
	}
	
	public int getRow() {
		//TODO fill in this getter
		return row;
	}

	public int getCol() {
		//TODO fill this in
		return col;
	}
	
	public void setCol(int col) {
		this.col = col;
	}
	
	public void setRow(int row) {
		this.row = row;
	}
	
	//Small test code to put in Space.java to check to see if your class works
	public static void main(String[] args) {
		Space one = new Space(3, 4);
		Space two = new Space(1, 6);
		two.setRow(two.getRow()+1);
		two.setCol(two.getCol()-1);
		System.out.println("one r: " + one.getRow() + ", c: " + one.getCol());
		System.out.println("two r: " + two.getRow() + ", c: " + two.getCol());
	}
	
	@Override
	public String toString() {
		return "r" + row + "c" + col;
	}

}

