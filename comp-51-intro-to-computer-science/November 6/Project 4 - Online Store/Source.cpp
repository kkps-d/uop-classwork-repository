/*
Project 4 - Online Store
Kaung Khant Pyae Sone
COMP 051-01
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct shoppingItem {
	string desc{};	// Description
	float price{};	// Price
	int quantity{};	// Quantity
	float weight{};	// Weight in ounces
};

struct shippingRates {
	int zip, numOfValidEntries;	// Zip code, number of valid zip codes after loading the file
	float tax, USPS, UPS, Fedex;	// Tax, rates fir USPS, UPS and FedEx
};

// Loads the rates file into an array of structure
void loadShipping(struct shippingRates rates[]) {
	string temp, fileName; // temp used for error checking zip, fileName is the name of the rates file
	int zip;
	int i = 0;	// Used as an array pointer and for tracking valid values. This value is incremented every time the entry inside the rates file is valid.
	float tax, USPS, UPS, Fedex;	// Tax, rates fir USPS, UPS and FedEx
	bool error;	// Stores if the entry in the rates file contains an error or not.
	bool fail = 1; // Stores if file opening fails or not
	ifstream input;

	while (fail == 1)
	{
		cout << "Enter filename of rates file to load (cin): ";
		cin >> fileName;
		input.open(fileName);
		if (input.fail())
		{
			cout << "File not found! ";
		}
		else
		{
			fail = 0;
		}
	}

	while (input >> temp)	// Loops until end of file is reached
	{
		error = false;	// Resets every loop so program is ready to error check the entries in the rates file
		input >> tax >> USPS >> UPS >> Fedex;
		if (temp.length() == 5)	// Checks if zip code has only 5 characters
		{
			stringstream convert(temp);	// Converts string temp
			convert >> zip;				// to int zip
			if (zip > 90000 && zip <= 96162)	// Checks if zip codes are within this range
			{
				rates[i].zip = zip;
			}
		}
		else
		{
			cout << "Invalid zip code: " << temp << ". Entry skipped" << endl;
			error = true;	// If zip code is invalid, all other error checking is skipped and the entry is not added to the array of structure
		}
		if (error == false) // If zip code is valid, continues to error checking other entries
		{
			if (tax >= 0 && tax <= 1)
			{
				rates[i].tax = tax;
			}
			else // If tax rate is invalid, all other error checking is skipped and the entry is not added to the array of structure
			{
				cout << "Invalid tax: " << tax << ". Entry skipped" << endl;
				error = true;
			}
		}
		if (error == false)
		{
			if (USPS > 0)
			{
				rates[i].USPS = USPS;
			}
			else
			{
				cout << "Invalid USPS rates: " << USPS << ". Entry skipped" << endl;
				error = true;
			}
		}
		if (error == false)
		{
			if (UPS > 0)
			{
				rates[i].UPS = UPS;
			}
			else
			{
				cout << "Invalid UPS rates: " << UPS << ". Entry skipped" << endl;
				error = true;
			}
		}
		if (error == false)
		{
			if (Fedex > 0)
			{
				rates[i].Fedex = Fedex;
			}
			else
			{
				cout << "Invalid FedEx rates: " << Fedex << ". Entry skipped" << endl;
				error = true;
			}
		}
		if (error == false) // Increments the array pointer and number of valid entries inside the array of structure
		{
			i++;
		}
	}
	rates[0].numOfValidEntries = i; // Stores the number of valid entries inside the array of structure for other functions to use

	input.close();
}

// Checks for invalid characters in integer input and returns valid input
int intChecker() {
	int input;
	cin >> input;
	do
	{
		if (cin.fail())
		{
			cin.clear(); // Clears cin buffer
			cin.ignore(INT_MAX, '\n'); // Ignores 1 character and newline
			cout << "Invalid character. Please enter again: ";
			cin >> input;
		}
	} while (cin.fail());
	return input;
}

// Displays the menu, accepts user choice and returns 
int displayMenu() {
	int userChoice;
	bool valid = false;

	cout << "Mr. Silver's Tableware" << endl;
	cout << "1. Create Customer Account" << endl;
	cout << "2. Shop for Items" << endl;
	cout << "3. Proceed to Check out" << endl;
	cout << "4. Exit" << endl;
	cout << "Enter your choice: ";
	while (1)
	{
		userChoice = intChecker();
		switch (userChoice)
		{
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
		case 4:
			return 4;
			break;
		default:
			cout << "Invalid option. Please try again: ";
			break;
		}
	}
}

// Asks for user info and creates a new customer
void createCustomer(string &customerName, string &address, string &city, int &zip) {
	int temp;
	bool validZip = false;
	bool confirm = false;
	bool validChoice = false;
	char choice;
	
	// Solves getline reading newline from main during menu selection and skipping the first input
	// Problem caused by transitioning from cin to getline
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	// Self-explanitory
	do
	{
		system("cls");
		cout << "Creating a new user" << endl;
		do
		{
			cout << "Enter your full name: ";
			getline(cin, customerName);
			if (customerName.empty())
			{
				cout << "Name cannot be empty! " << endl;
			}
		} while (customerName.empty());
		
		do
		{
			cout << "Enter your full address (without city): ";
			getline(cin, address);
			if (address.empty())
			{
				cout << "Address cannot be empty! " << endl;
			}
		} while (address.empty());

		do
		{
			cout << "Enter your city: ";
			getline(cin, city);
			if (city.empty())
			{
				cout << "Name cannot be empty! " << endl;
			}
		} while (city.empty());

		cout << "Enter your zip code: ";
		while (validZip == false)
		{
			temp = intChecker();
			if (temp > 90000 && temp <= 96162)
			{
				zip = temp;
				validZip = true;
			}
			else
			{
				cout << "Invalid zip code: " << temp << ". Please try again: ";
			}
		}
		cout << endl;
		cout << "You have entered: " << endl;
		cout << "Name: " << customerName << endl;
		cout << "Address: " << address << endl;
		cout << "City: " << city << endl;
		cout << "Zip code: " << zip << endl;
		cout << "Is this information correct? (Y/N): ";
		while (validChoice == false)
		{
			cin >> choice;
			switch (choice)
			{
			case 'Y':
			case 'y':
				confirm = true;
				validChoice = true;
				break;
			case 'N':
			case 'n':
				confirm = false;
				validChoice = true;
				break;
			default:
				cout << "Invalid choice. Please try again: ";
				confirm = false;
				validChoice = false;
				break;
			}
		}
	} while (confirm == false);
}

// Checks for quantity, and if valid adds item to cart
void addToCart(string desc, float price, float weight, struct shoppingItem cart[], int &itemCount) {

	int quantity;
	cout << "Enter quantity: ";
	do
	{
		quantity = intChecker();
		if (quantity <= 0)
		{
			cout << "Invalid quantity. Please try again: ";
		}
	} while (quantity <= 0);
	cart[itemCount].desc = desc;
	cart[itemCount].price = price;
	cart[itemCount].weight = weight;
	cart[itemCount].quantity = quantity;
}

// Responsible for displaying available items and calling the addToCart() function to add items to the cart
void maintainCart(struct shoppingItem cart[], int &itemCount) {
	int itemChoice;
	bool validChoice = false, quit = false;

	do
	{
		system("cls");
		cout << "Catalogue" << endl;
		cout << "=========================================" << endl;
		cout << "1. Spoon - $0.79" << endl;
		cout << "2. Fork - $0.79" << endl;
		cout << "3. Knife - $0.79" << endl;
		cout << "4. Silverware set for two - $4.59" << endl;
		cout << "5. Silverware set for six - $13.99" << endl;
		cout << "6. Go back to menu" << endl;
		cout << "Number of items currently in cart: " << itemCount << endl;
		cout << "Select item to add to cart: ";
		do
		{
			itemChoice = intChecker();
			switch (itemChoice)
			{
			case 1:
				// addToCart(item description, price, weight, shopping cart array, number of items inside the cart)
				addToCart("Spoon", 0.79F, 0.85F, cart, itemCount);	// F added to solve "Warning C4305 'argument': truncation from 'double' to 'float'"
				validChoice = true;
				break;
			case 2:
				addToCart("Fork", 0.79F, 0.85F, cart, itemCount);
				validChoice = true;
				break;
			case 3:
				addToCart("Knife", 0.79F, 0.85F, cart, itemCount);
				validChoice = true;
				break;
			case 4:
				addToCart("Silverware set for two", 4.59F, 5.1F, cart, itemCount);			
				validChoice = true;
				break;
			case 5:
				addToCart("Silverware set for six", 13.99F, 15.3F, cart, itemCount);
				validChoice = true;
				break;
			case 6:
				validChoice = true;
				quit = true;
				break;
			default:
				cout << "Invalid choice. Please try again: ";
				validChoice = false;
				break;
			}
		} while (validChoice == false);
		if (quit == false)
		{
			itemCount++; // If not quitting, assuming that user added an item, increments the number of items inside the cart
		}
	} while (quit == false);
}

// Searches rates array for the zip code, and returns the location in the form of a pointer. Exits program if zip code is not found
int findPointerByZip(int zip, struct shippingRates rates[]) {
	for (int i = 0; i <= rates[0].numOfValidEntries; i++)
	{
		if (rates[i].zip == zip)
		{
			return i;
		}
	}
	system("cls");
	cout << "Error - current zip code's entry contains invalid information. Please contact vendor." << endl;
	system("pause");
	exit(0);
}

// Displays the receipt and calculates the subtotal and returns it
float displayReceipt(struct shoppingItem cart[], int itemCount) {
	float total = 0;

	system("cls");
	cout << "Mr. Silver's Silverware" << endl;
	cout << "Receipt" << endl;
	cout << setfill('=') << setw(79) << "=" << endl;
	cout << setfill(' ');
	cout << setw(30) << left << "Description";
	cout << setw(10) << left << "Price";
	cout << setw(10) << left << "Quantity";
	cout << setw(16) << left << "Weight (ounces)";
	cout << setw(15) << left << "Total for item" << endl;

	for (int i = 0; i < itemCount; i++) // Prints the information of each item and calculates total price of items
	{
		cout << setw(30) << cart[i].desc;
		cout << setw(10) << cart[i].price;
		cout << setw(10) << cart[i].quantity;
		cout << setw(16) << cart[i].weight;
		cout << left << "$" << left << cart[i].price * cart[i].quantity << endl;
		total += cart[i].price * cart[i].quantity;	// Calculates the total price
	}
	cout << "Subtotal: $" << total << endl;
	return total;
}

// Calculates and returns the shipping cost
float calculateShipping(struct shoppingItem cart[], struct shippingRates rates[], int itemCount, int zip) {
	float USPS;
	float UPS;
	float Fedex;
	float weight = 0;
	int shippingMethod;
	int shippingModifier;	// Different multipliers for different amount of weight
	int i;
	bool validMethod = false;

	i = findPointerByZip(zip, rates); // Stores the lcoaiton of the zip code in the array
	USPS = rates[i].USPS;
	UPS = rates[i].UPS;
	Fedex = rates[i].Fedex;

	for (int j = 0; j < itemCount; j++) // Loop to find total weight
	{
		weight += cart[j].weight * cart[j].quantity;
	}

	if (weight <= 10) // 0 - 10 ounces = 1
	{
		shippingModifier = 1;
	}
	else if (weight >= 11 && weight <= 50) // 11 - 50 ounces = 5
	{
		shippingModifier = 5;
	}
	else // More than 50 ounces = 10
	{
		shippingModifier = 10; 
	}
	
	USPS *= shippingModifier;  // Multiplies rates with modifier
	UPS *= shippingModifier;
	Fedex *= shippingModifier;

	cout << endl << "Shipping" << endl;
	cout << "Total weight: " << weight << " ounces" << endl;
	cout << "====================" << endl;
	cout << "1. USPS - $" << USPS << endl;
	cout << "2. UPS - $" << UPS << endl;
	cout << "3. FedEx - $" << Fedex << endl;

	while (1)
	{
		cout << "Enter shipping method: ";
		shippingMethod = intChecker();
		switch (shippingMethod)
		{
		case 1:
			return USPS;
			break;
		case 2:
			return UPS;
			break;
		case 3:
			return Fedex;
			break;
		default:
			cout << "Invalid shipping method. ";
			break;
		}
	}
}

// Calculates and returns the tax
float calculateTax(float subtotal, struct shippingRates rates[], int zip) {
	int i;
	i = findPointerByZip(zip, rates);
	return subtotal * rates[i].tax;
}

// Verifies, calculates and returns the total cost
float calculateTotal(float subtotal, float shipping, float tax) {
	if (subtotal > 0 && shipping > 0 && tax > 0)
	{
		return subtotal + shipping + tax;
	}
	else
	{
		system("cls");
		cout << "Catastrophic failure." << endl;
		exit(0);
	}
}

// Saves the invoice to text and HTML files
void saveInvoice(string customerName, string address, string city, int zip, int itemCount, struct shoppingItem cart[], float subtotal, float tax, float shipping, float total) {
	ofstream output;
	time_t result = time(0); // current time put into time_t struct
	char str[26];	// char array used to store converted time
	ctime_s(str, 26, &result); // ctime_s converts raw time to readable time and stores in str

	// Text file

	output.open("invoice.txt");
	output << "Mr. Silver's Silverware" << endl;
	output << str << endl;
	if (customerName.length() == 0)
	{
		output << "Unregistered customer" << endl;
	}
	else
	{
		output << customerName << endl;
		output << address << endl;
	}
	output << "CA " << zip << endl << endl;

	output << "Invoice" << endl;
	output << setfill('-') << setw(80) << "-" << endl << setfill(' ');
	output << setw(30) << left << "Description";
	output << setw(10) << left << "Price";
	output << setw(10) << left << "Quantity";
	output << setw(16) << left << "Weight (ounces)";
	output << setw(15) << left << "Total for item" << endl;

	for (int i = 0; i < itemCount; i++)
	{
		output << setw(30) << cart[i].desc;
		output << setw(10) << cart[i].price;
		output << setw(10) << cart[i].quantity;
		output << setw(16) << cart[i].weight;
		output << left << "$" << left << cart[i].price * cart[i].quantity << endl;
	}
	output << endl;
	output << fixed << setprecision(2);
	output << "Subtotal: $" << subtotal << endl;
	output << "Tax: $" << tax << endl;
	output << "Shipping: $" << shipping << endl;
	output << "-----------------------" << endl;
	output << "Total: $" << total << endl;
	output.close();
	cout << "Invoice has been saved to invoice.txt" << endl;

	// HTML File

	output.open("invoice.html");
	output << "<html>" << endl;
	output << "<head>" << endl;
	output << "	<title>Invoice</title>" << endl;
	output << "<style type=\"text/css\">" << endl;
	output << "body { font-family: Arial, Helvetica, sans-serif; padding-left: 50px; padding-top: 20px; }" << endl;
	output << "</style>" << endl;
	output << "</head>" << endl;
	output << "<body><h5> Mr. Silver's Silverware<br>" << str << "<br></h5>";
	output << "<h4>" << customerName << "<br>" << address << "<br>" << city << "<br>CA " << zip << "</h4>" << endl;
	output << "<h1>Invoice</h1>" << endl;
	output << "<table style=\"width: 600px; text-align: left; border: 1px solid black\">" << endl;
	output << "<tr><th>Description</th><th>Price</th><th>Quantity</th><th>Weight (ounces)</th><th>Total for item</th></tr>" << endl;

	for (int i = 0; i < itemCount; i++)
	{
		output << "<tr>" << endl;
		output << "<td>" << cart[i].desc << "</td>" << endl;
		output << "<td>$" << cart[i].price << "</td>" << endl;
		output << "<td>" << cart[i].quantity << "</td>" << endl;
		output << "<td>" << cart[i].weight << "</td>" << endl;
		output << "<td>$" << cart[i].price * cart[i].quantity << "</td>" << endl;
		output << "</tr>" << endl;
	}
	output << "</table>" << endl;
	output << "<h4>" << endl;
	output << "Subtotal: $" << subtotal << "<br>" << endl;
	output << "Tax: $" << tax << "<br>" << endl;
	output << "Shipping: $" << shipping << "<br></h4>" << endl;

	output << "<h3 style=\"border-top: 2px solid black; width: 600px; padding-top: 20px; \">" << endl;
	output << "Total: $" << total << "</h3></body></html>";

	cout << "Invoice has been saved to invoice.html" << endl;
}

// Runs displayReceipt(), calculateShipping(), calculateTax() and calculateTotal() and displays shipping, tax and total
void checkOut(struct shippingRates rates[], struct shoppingItem cart[], int zip, int itemCount, string customerName, string address, string city) {
	float subtotal;
	float shipping;
	float tax;
	float total;
	bool validZip = false;
	bool validChoice = false;
	int temp;

	if (zip == 0) // Asks for zip code if empty
	{
		system("cls");
		cout << "You haven't entered a zip code! Please enter one: ";
		while (validZip == false)
		{
			temp = intChecker();
			if (temp > 90000 && temp <= 96162)
			{
				zip = temp;
				validZip = true;
			}
			else
			{
				cout << "Invalid zip code. Please try again: ";
			}
		}
	}

	subtotal = displayReceipt(cart, itemCount);
	shipping = calculateShipping(cart, rates, itemCount, zip);
	tax = calculateTax(subtotal, rates, zip);
	total = calculateTotal(subtotal, shipping, tax);
	if (total != 0)
	{
		cout << endl;
		cout << fixed << setprecision(2);
		cout << "Subtotal: $" << subtotal << endl;
		cout << "Tax: $" << tax << endl;
		cout << "Shipping: $" << shipping << endl;
		cout << "-----------------------" << endl;
		cout << "Total: $" << total << endl;
	}
	else
	{
		system("cls");
		cout << "Error - Invalid values detected. Please contact vendor." << endl;
		system("pause");
		exit(0);
	}
	saveInvoice(customerName, address, city, zip, itemCount, cart, subtotal, tax, shipping, total);
}

int main() {
	shoppingItem cart[100]; // array used to store items you add to shopping cart
	shippingRates rates[6161]; // array used to store zip codes loaded from file
	string customerName, address, city;
	int zip = 0, userChoice, itemCount = 0;
	bool exit = false;
	
	loadShipping(rates);
	do
	{
		system("cls");
		cout << "Welcome " << customerName << "!" << endl;
		userChoice = displayMenu();
		switch (userChoice)
		{
		case 1:
			createCustomer(customerName, address, city, zip);
			break;
		case 2:
			maintainCart(cart, itemCount);
			break;
		case 3:
			if (itemCount != 0)
			{
				checkOut(rates, cart, zip, itemCount, customerName, address, city);
				exit = true;
			}
			else
			{
				system("cls");
				cout << "Cart is empty!" << endl;
				system("pause");
			}
			break;
		case 4:
			exit = true;
			break;
		}
	} while (exit == false);
}