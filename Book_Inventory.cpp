#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Book_Inventory.h"

bool Book_Inventory::readInventory(const char *filename)
{
	char     line[128];
	int      numBooks;
	// define other variables here as needed

	m_InFile.open(filename, ifstream::in);
	if (!m_InFile.is_open())
	{
		// m_InFile.is_open() returns false if the file could not be found or
		//    if for some other reason the open failed.
		cout << "Unable to open file" << filename << "\nProgram terminating...\n";
		return false;
	}
	// Read number of books
	getNextLine(line, 128);
	numBooks = atoi(line);
	for (int i = 0; i < numBooks; i++)
	{
		// ------------------------------------------
		// Your code to read the inventory goes here
		// ------------------------------------------
		BookRecord* temp = new BookRecord;

		getNextLine(line, 128);
		int stocknumber = atoi(line);
		temp->setStockNum(stocknumber);

		getNextLine(line, 128);
		temp->setName(line);

		getNextLine(line, 128);
		int classification = atoi(line);
		temp->setClassification(classification);

		getNextLine(line, 128);
		double cost = atof(line);
		temp->setCost(cost);

		getNextLine(line, 128);
		int inven = atoi(line);
		temp->setNumberInStock(inven);
		addBook(temp);



	}
	return true;
}

//--------------------------------------------
// Function: getNextLine() 
// Purpose:  Read a line from a data file.
//   The next non-comment line read from file
//   is stored in line char array.
//   An empty string is stored if the end of
//   file is reached.
// Returns: bool - true if a valid line was
//   read, false if end of file is reached. 
//--------------------------------------------
bool Book_Inventory::getNextLine(char *line, int lineLen)
{
	int    done = false;
	while (!done)
	{
		m_InFile.getline(line, lineLen);

		if (m_InFile.good())    // If a line was successfully read
		{
			if (strlen(line) == 0)  // Skip any blank lines
				continue;
			else if (line[0] == '#')  // Skip any comment lines
				continue;
			else return true;    // Got a valid data line so return with this line
		}
		else // No valid line read, meaning we reached the end of file
		{
			strcpy(line, ""); // Copy empty string into line as sentinal value
			return false;
		}
	} // end while
	return false; // Cannot reach this point but include a return to avoid compiler warning
				  //   that not all paths return a value.
}

/*other functions listed in the header file are below*/

Book_Inventory::Book_Inventory() {
	//This constructor creates an empty linked list when an object is instantiated
	//It also assigns the head of the list to an empty node 1
	m_pHead = nullptr;
	size = 0;

}

void Book_Inventory::ClearList() {
	BookRecord* tempPtr;
	cout << "Clearing the list" << endl;
	while (m_pHead != NULL)
	{
		tempPtr = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete tempPtr;
	}
	size = 0;
}

bool Book_Inventory::addBook(BookRecord *br) {
	cout << "Adding a new book!" << endl;
	//BookRecord* newNode;  	// the new node
	BookRecord* predLoc;  	// pointer that will be directed towards the previous node
	BookRecord* location;

	bool moreToSearch;		//boolean value to check if the location of insertion is correct

	location = m_pHead;
	predLoc = NULL;
	moreToSearch = (location != NULL);

	long stock_number = br->m_lStockNum;

	while (moreToSearch) {
		if (location->m_lStockNum < stock_number)
		{
			predLoc = location;
			location = location->m_pNext;
			moreToSearch = (location != NULL);
			//break;
		}
		else
		{
			moreToSearch = false;
			//break;
		}
	}

	//Inserting the node into the linked list:::
	BookRecord *node = new BookRecord;

	node->m_lStockNum = br->m_lStockNum;
	node->m_iClassification = br->m_iClassification;
	node->m_dCost = br->m_dCost;
	node->m_iCount = br->m_iCount;
	strcpy(node->m_sName, br->m_sName);
	node->setNext(br);




	if (predLoc == NULL) {
		node->m_pNext = m_pHead;
		m_pHead = node;
	}
	else {
		node->m_pNext = location;
		predLoc->m_pNext = node;
	}
	size++;
	return NULL;
}

BookRecord*Book_Inventory::removeBook(long stockNum)
{
	cout << "Trying to remove a book" << endl;

	BookRecord *location;
	location = m_pHead;
	BookRecord* tempLocation;

	//Look for the node to be deleted:::
	bool isPresent = true;

	if (stockNum == m_pHead->getStockNum()) {
		tempLocation = location;
		m_pHead = m_pHead->m_pNext;
		isPresent = true;
	}
	else {
		while ((location->m_pNext)->getStockNum() != stockNum) {
			location = location->m_pNext;
			if (location->m_pNext == NULL) {
				break;
			}
		}

		tempLocation = location->m_pNext;
		if (location->m_pNext != NULL) {
			location->m_pNext = (location->m_pNext)->m_pNext;
		}
		isPresent = false;
	}

	if (isPresent == true) {
		cout << endl;
		cout << tempLocation->m_sName << " Removed!" << endl;
		delete tempLocation;
		cout << endl;


		size--;
	}
	else {
		cout << "The stock number you have entered does not correspond to any book\n\n";
	}
	return nullptr;
}


BookRecord*Book_Inventory::searchByStockNumber(long stockNum)
{
	cout << "Searching for a book by stock number" << endl;
	BookRecord* location;
	location = m_pHead;
	bool found = false;

	while (location != NULL) {
		if (location->m_lStockNum == stockNum) {
			cout << endl << "A book was found!\n\n";
			cout << "Name: ";
			for (int i = 0; i < 128; i++) {
				cout << location->m_sName[i];
			}
			cout << endl;
			cout << "Stock_Num: " << location->m_lStockNum << endl;
			cout << "Classification: " << location->m_iClassification << endl;
			cout << "Cost of the book: " << location->m_dCost << endl;
			cout << "Number of books in stock: " << location->m_iCount << endl;
			found = true;
			return location;
		}
		location = location->m_pNext;
	}
	if (found == false) {
		cout << "Book could not be found!\n";
	}
}

void Book_Inventory::searchByClassification(int cl)
{
	cout << "Searching for a book by classification..." << endl;
	BookRecord* location;
	location = m_pHead;


	int dummy = 0;
	bool found = false;
	while (dummy != size) {

		if (location->m_iClassification == cl) {
			cout << "Book found:\n";
			cout << "Name: ";
			for (int i = 0; i < 128; i++) {
				cout << location->m_sName[i];
			}
			cout << endl;
			cout << "Stock_Num: " << location->m_lStockNum << endl;
			cout << "Classification: " << location->m_iClassification << endl;
			cout << "Cost of the book: " << location->m_dCost << endl;
			cout << "Number of books in stock: " << location->m_iCount << endl;
			cout << endl;
			found = true;
		}

		dummy++;
		location = location->getNext();
	}

	if (found == false) {
		cout << "Book could not be found!\n";
	}
}


void Book_Inventory::searchByCost(double min, double max) {
	cout << "Searching for a book by cost" << endl;
	BookRecord* location;
	location = m_pHead;

	int dummy = 0;
	bool found = false;
	while (dummy != size) {
		if (location->m_dCost >= min && location->m_dCost <= max) {
			cout << "Name: ";
			for (int i = 0; i < 128; i++) {
				cout << location->m_sName[i];
			}
			cout << endl;
			cout << "Stock_Num: " << location->m_lStockNum << endl;
			cout << "Classification: " << location->m_iClassification << endl;
			cout << "Cost of the book: " << location->m_dCost << endl;
			cout << "Number of books in stock: " << location->m_iCount << endl << endl;
			dummy++;
			found = true;
		}
		else {
			dummy++;
		}
		location = location->getNext();
	}

	if (found == false) {
		cout << "No books were found in this price range.\n" << endl << endl;
	}
}

int Book_Inventory::getNumberInStock(long sn) {
	cout << "Getting number of books..." << endl;
	BookRecord* location;
	location = m_pHead;
	int value = 0;
	bool found = false;

	while (location != NULL) {
		if (location->m_lStockNum == sn) {
			cout << "Number of books in stock: " << location->m_iCount << endl;
			found = true;
			value = location->m_iCount;
		}
		location = location->m_pNext;
	}

	if (found == false) {
		cout << "Stock Num entered is incorrect\n\n";
	}
	return value;
}

void Book_Inventory::printAll() {
	cout << "Printing all elements in the list..." << endl;
	BookRecord* location;
	location = m_pHead;
	int count = 0;
	cout << "********************************************\n";
	while (count != size) {
		cout << "Name: ";
		for (int i = 0; i < 128; i++) {
			cout << location->m_sName[i];
		}
		cout << endl;
		cout << "Stock_Num: " << location->m_lStockNum << endl;
		cout << "Classification: " << location->m_iClassification << endl;
		cout << "Cost of the book: " << location->m_dCost << endl;
		cout << "Number of books in stock: " << location->m_iCount << endl;
		cout << endl << endl;
		location = location->m_pNext;
		count++;
	}
	cout << "********************************************\n";
}

Book_Inventory::~Book_Inventory() {
	BookRecord* tempPtr;
	while (m_pHead != NULL)
	{
		tempPtr = m_pHead;
		m_pHead = m_pHead->m_pNext;
		delete tempPtr;
	}
	size = 0;
}









