#include "Book_Inventory.h"
#include "BookRecord.h"

using namespace std;

int main() {

	Book_Inventory inventory;
	inventory.readInventory("BookData.txt");
	inventory.printAll();
	cout << endl;
	inventory.getNumberInStock(1234);
	cout << endl;
	inventory.getNumberInStock(121212);
	cout << endl;
	BookRecord *book = new BookRecord("Algorithms", 824618, 211, 52.32);
	inventory.addBook(book);
	cout << endl;
	inventory.printAll();
	cout << endl;
	BookRecord *new_book = new BookRecord("Project X", 4343, 222, 10.011);
	inventory.addBook(new_book);
	cout << endl;
	inventory.removeBook(1234);
	cout << endl;
	inventory.removeBook(12414);
	inventory.searchByStockNumber(1234);
	cout << endl;
	inventory.searchByStockNumber(824618);
	cout << endl;
	inventory.searchByStockNumber(281947154);
	cout << endl;
	inventory.searchByCost(20, 40);
	cout << endl;
	inventory.searchByCost(0, 100);
	cout << endl;
	inventory.searchByCost(22222, 44444);
	cout << endl;
	inventory.searchByClassification(211);
	cout << endl;
	inventory.searchByClassification(23131);
	cout << endl;
	inventory.printAll();	//Print all the books again after modifications
	cout << endl;
	cout << "The ClearList function is now being implemented. All items will be deleted permanently\n";
	inventory.ClearList();
	cout << endl;
	inventory.printAll();
}