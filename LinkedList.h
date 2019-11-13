/*-- LinkedList.h --------------------------------------------------------------

This header file defines the data type List for processing lists.
Operations are:
Constructor
Destructor
Copy constructor
Assignment operator
insert:   Insert an item
erase:    Remove an item
getListElement: get a range of list elements

-------------------------------------------------------------------------*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class LinkedList
{
public:
typedef int ListElement;
private:
	/******** Data Members ********/
	class Node
	{
	public:
		ListElement data;

		Node * next;
	};
	Node *first;         // pointer to first element in linked list
	int getListSize() const;

public:
	/******** Error Codes ********/
	static const int ILLEGAL_LIST_POSITION = -1;
	static const int NO_ERROR = 0;

	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList & origList);
	const LinkedList & operator=(const LinkedList & rightHandSide);
	int insert(ListElement item, int pos);
	int erase(int pos);
	int getListElement(int posStart, int posEnd, ListElement rv[]) const;

}; //--- end of List class

#endif

