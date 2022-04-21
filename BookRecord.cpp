#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include "BookRecord.h"
#pragma warning(disable : 4996)

BookRecord::BookRecord() {
	m_lStockNum = 0;
	m_iClassification = 0;
	m_dCost = 0.0;
	m_iCount = 0;
	for (int i = 0; i <= 128; i++) {
		m_sName[i] = '\0';
	}
}

BookRecord::~BookRecord() {
	//destructor should be empty
}

BookRecord::BookRecord(const char *name, long sn, int cl, double cost) {
	m_iCount = 1;
	m_lStockNum = sn;
	m_iClassification = cl;
	m_dCost = cost;
	strcpy(m_sName, name);
}

void BookRecord::getName(char *name) {

	strcpy(name, m_sName);
}

void BookRecord::setName(const char *name) {

	strcpy(m_sName, name);

}

long BookRecord::getStockNum() {

	return m_lStockNum;

}

void BookRecord::setStockNum(long sn) {

	m_lStockNum = sn;

}

void BookRecord::getClassification(int &cl) {

	cl = m_iClassification;

}

void BookRecord::setClassification(int cl) {

	m_iClassification = cl;

}

double BookRecord::getCost() {

	return m_dCost;

}

void BookRecord::setCost(double c) {

	m_dCost = c;

}

int BookRecord::getNumberInStock() {

	return m_iCount;

}

void BookRecord::setNumberInStock(int count) {

	m_iCount = count;

}


void BookRecord::printRecord() {

	std::cout << m_sName << " " << m_lStockNum << " " << m_iClassification << " " << m_dCost << " " << m_iCount << std::endl << std::endl;

}

void BookRecord::setNext(BookRecord *next)
{
	//This function creates a new node
	//It also points the previous node to this node

	m_pNext = next;

	//BookRecord *new_book = new BookRecord;

	/*long stock_number = 0;
	new_book->m_lStockNum = next->m_lStockNum;
	new_book->m_iClassification = next->m_iClassification;
	new_book->m_dCost = next->m_dCost;
	new_book->m_iCount = next->m_iCount;
	strcpy(new_book->m_sName, next->m_sName);
	new_book->m_pNext = nullptr;
	*/
}

BookRecord* BookRecord::getNext()
{
	return m_pNext;
}