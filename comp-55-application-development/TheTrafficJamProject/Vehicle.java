import java.util.*;

public class Vehicle {
	// TODO You'll need to fill in this entire file
	private VehicleType vehicleType;
	private int headRow, headColumn, length;
	private boolean vertical;
	
	public Vehicle(VehicleType type, int startingRow, int startingColumn, int length, boolean vertical) {
		this.vehicleType = type;
		this.headRow = startingRow;
		this.headColumn = startingColumn;
		this.length = length;
		this.vertical = vertical;
	}
	
	public VehicleType getVehicleType() {
		return vehicleType;
	}
	
	public boolean isVertical() {
		return vertical;
	}
	
	/**
	 * Calculates an array of the spaces that would be travelled if a vehicle
	 * were to move numSpaces
	 * 
	 * @param numSpaces
	 *            The number of spaces to move (can be negative or positive)
	 * @return The array of Spaces that would need to be checked for Vehicles
	 */

	/*
	 * Board
	 *   8 7 6 5 4 3 2 1 0
	 * 8 
	 * 7 
	 * 6 
	 * 5
	 * 4 t b h
	 * 3
	 * 2 h
	 * 1 b
	 * 0 t
	 */
	public void move(int numSpaces) {
		if (vertical == true) {
			headRow += numSpaces;
		} else {
			headColumn += numSpaces;
		}
	}
	
	public Space ifIWereToMove(int numSpaces) {
		int ifRow = headRow;
		int ifColumn = headColumn;
		
		if (vertical == true) {
			ifRow += numSpaces;
		} else {
			ifColumn += numSpaces;
		}	
		Space ifSpace = new Space(ifRow,ifColumn);
		return ifSpace;
	}
	
	public Space[] spacesOccupied() {
		List<Space> spacesOccupied = new ArrayList<Space>();
		spacesOccupied.add(new Space(headRow, headColumn));
		if (vertical == true) {
			if (length >= 2) {
				for (int i = 1; i < length; i++) {
					spacesOccupied.add(new Space(headRow + i, headColumn));
				}
			}
		} else {
			if (length >= 2) {
				for (int i = 1; i < length; i++) {
					spacesOccupied.add(new Space(headRow, headColumn + i));
				}
			}
		}
		Space spaceToReturn[] = spacesOccupied.toArray(new Space[spacesOccupied.size()]);
		return spaceToReturn;
	}
	
	public Space[] spacesOccupiedOnTrail(int numSpaces) {
		Vehicle temp = new Vehicle(vehicleType, headRow, headColumn, length, vertical);
		Space[] spacesOccupied = temp.spacesOccupied();
		Space tail = spacesOccupied[0];
		Space head = spacesOccupied[spacesOccupied.length - 1];
		List<Space> spaceTrail = new ArrayList<Space>();
		
		if (numSpaces >= 0) {
			if (vertical == true) {
				for (int i = 1; i <= Math.abs(numSpaces); i++) {
					spaceTrail.add(new Space(head.getRow() + i, head.getCol()));
				}
			} else {
				for (int i = 1; i <= Math.abs(numSpaces); i++) {
					spaceTrail.add(new Space(head.getRow(), head.getCol() + i));
				}
			}
		} else {
			if (vertical == true) {
				for (int i = Math.abs(numSpaces); i >=1 ; i--) {
					spaceTrail.add(new Space(tail.getRow() - i, tail.getCol()));
				}
			} else {
				for (int i = Math.abs(numSpaces); i >=1 ; i--) {
					spaceTrail.add(new Space(tail.getRow(), tail.getCol() - i));
				}
			}
		}
		Space[] spaceToReturn = spaceTrail.toArray(new Space[spaceTrail.size()]);
		return spaceToReturn;
	}

	@Override
	public String toString() {
		Space[] spacesOccupied = spacesOccupied();
		String toReturn = "";
		
		toReturn = "r" + spacesOccupied[0].getRow() + "c" + spacesOccupied[0].getCol();
		for (int i = 1; i < length; i++) {
			
			toReturn += "|r" + spacesOccupied[i].getRow() + "c" + spacesOccupied[i].getCol();
		}
		return toReturn;
	}
	
	public static void printSpaces(Space[] arr) {
		  for(int i = 0; i < arr.length; i++) {
			System.out.print("r" + arr[i].getRow() + "c" + arr[i].getCol() + "; ");	
		  }
		  System.out.println();
		}

	
	public static void main(String[] args) {
		//this snippet would go inside of a public static void main in Vehicle.java
		//Assume Vehicle constructor is type, startRow, startCol, length, isVertical
		Vehicle someTruck = new Vehicle(VehicleType.TRUCK, 1, 1, 3, true);
		Vehicle someAuto = new Vehicle(VehicleType.AUTO, 2, 2, 2, false);
		System.out.println("This next test is for spacesOccupied: ");
		System.out.println("vert truck at r1c1 should give you r1c1; r2c1; r3c1 as the spaces occupied:does it?");
		printSpaces(someTruck.spacesOccupied());
		System.out.println("horiz auto at r2c2 should give you r2c2; r2c3 as the spaces occupied:does it?");
		printSpaces(someAuto.spacesOccupied());
		System.out.println("if we were to move horiz auto -2 it should give you at least r2c0; r2c1; it may also add r2c2; r2c3 to its answer:does it?");
		printSpaces(someAuto.spacesOccupiedOnTrail(-2));
		System.out.println("If I were to move truck to 2 positions positive, it's starting position would be..");
		System.out.println(someTruck.ifIWereToMove(2));
		System.out.println("Moving truck 2 positions positive");
		someTruck.move(2);
		printSpaces(someTruck.spacesOccupied());
	}
	
}

//Kaung Khant Pyae Sone