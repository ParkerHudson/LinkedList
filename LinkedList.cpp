/*-- LinkedList.cpp-----------------------------------------------------------

This file implements List member functions.
-------------------------------------------------------------------------*/

#include <new>
#include <iostream>
#include "LinkedList.h"

//--- Definition of class constructor
// Construct a List object.
// Precondition:  None.
// Postcondition : An empty List object is constructed; first == nullptr
LinkedList::LinkedList()
	: first(nullptr)  // initialize to empty list
{
}

//--- Definition of class destructor
// Destroys a List object.
// Precondition : The life of a List object is over.
// Postcondition : The memory dynamically allocated by the linked list is now deallocated
LinkedList::~LinkedList()
{
	Node *current = first;
	Node *temp;
	int k = getListSize();
	for (int i = 0; i < k; i++)
	{ // traverse through the list and deallocate nodes
		temp = current->next;  // get the next node in the linked list
		delete current;
		current = temp;
	}

	/* // alternate solution
	while (getListSize() != 0)
	{ // while there are still nodes left
		erase(0);
	}
	*/
}

//--- Definition of copy constructor
// Construct a copy of a List object.
// Precondition:  A copy of origList is needed; origList is a const
// reference parameter.
// Postcondition: A copy of origList has been constructed.
LinkedList::LinkedList(const LinkedList & origList) : first(nullptr)
{
	Node *temp;         // stores the new node pointer
	Node *prevNode = nullptr;     // store the previous node pointer
	Node *orgPrevNode = nullptr;  // stores the previous node pointer from the original list
	for (int i = 0; i < origList.getListSize(); i++)
	{
		temp = new(std::nothrow) Node();
		if (temp == nullptr)
		{ // if there was an error in the allocation then
			std::cerr << "*** Inadequate memory to allocate storage for new node ***\n";
			exit(1);
		}
		else if (i == 0)
		{ // if this is the first node then
			first = temp;  // set the pointer in the previous node
			first->data = origList.first->data;  // set the data in the node
			first->next = nullptr;  // set next pointer to null
			prevNode = temp;        // set the previous node for the next loop
			orgPrevNode = origList.first;   // set the org list previous node for the next loop
		}
		else
		{
			prevNode->next = temp;  // set the pointer in the previous node
			prevNode->next->data = orgPrevNode->next->data;  // set the data in the node
			prevNode->next->next = nullptr;  // set next pointer to null
			prevNode = temp;    // set the previous node for the next loop
			orgPrevNode = orgPrevNode->next;  // set the org list previous node for the next loop
		}
	}

	/* // alternate solution
		Node * current = origList.first;
		int count = 0;
		for( ; current != nullptr; )
		{ // traverse the origList
			insert(current->data, count);
			count++;
			current = current->next
		}
	*/
}

//--- Definition of assignment operator
// Assign a copy of a List object to the current object.
// Precondition: rightHandSide List is required.
// Postcondition : A copy of rightHandSide has been assigned to this
// object. A const reference to this list is returned.
const LinkedList & LinkedList::operator=(const LinkedList & rightHandSide)
{
	if (this != &rightHandSide)  // check that not self-assignment
	{
		// deallocate current linked list, same as the destructor code
		Node *current = first;
		Node *temp;
		int k = getListSize();
		for (int i = 0; i < k; i++)
		{
			temp = current->next;  // get the next node in the linked list
			delete current;
			current = temp;
		}
		// now start to copy from the rightHandSide
		first = nullptr;
		// similar to copy constructor
		Node *prevNode = nullptr;     // store the previous node pointer
		Node *orgPrevNode = nullptr;  // stores the previous node pointer from the original list
		for (int i = 0; i < rightHandSide.getListSize(); i++)
		{
			temp = new(std::nothrow) Node();
			if (temp == nullptr)
			{ // if there was an error in the allocation then
				std::cerr << "*** Inadequate memory to allocate storage for new node ***\n";
				exit(1);
			}
			else if (i == 0)
			{ // if this is the first node then
				first = temp;  // set the pointer in the previous node
				first->data = rightHandSide.first->data;  // set the data in the node
				first->next = nullptr;  // set next pointer to null
				prevNode = temp;        // set the previous node for the next loop
				orgPrevNode = rightHandSide.first;   // set the org list previous node for the next loop
			}
			else
			{
				prevNode->next = temp;  // set the pointer in the previous node
				prevNode->next->data = orgPrevNode->next->data;  // set the data in the node
				prevNode->next->next = nullptr;  // set next pointer to null
				prevNode = temp;    // set the previous node for the next loop
				orgPrevNode = orgPrevNode->next;  // set the org list previous node for the next loop
			}
		}
	}
	return *this;
}

//--- Definition of insert()
// Insert item at pos position.pos 0 is the first element position in the list
// Precondition : A constructed list, either empty or with elements
// Postcondition : inserted item into list at pos position
// Returns ILLEGAL_LIST_POSITION for insert that is out of range of the current list,
// Otherwise return a NO_ERROR.
int LinkedList::insert(ListElement item, int pos)
{ // note pos goes from 0 to n
	if (pos < 0 || pos > getListSize())
	{ // perform error checking on the input
		return ILLEGAL_LIST_POSITION;
	}
	// get the new node to insert
	Node *temp = new(std::nothrow) Node();
	if (temp == nullptr)
	{ // if there was an error in the allocation then
		std::cerr << "*** Inadequate memory to allocate storage for new node ***\n";
		exit(1);
	}
	temp->data = item;
	temp->next = nullptr; // if at the end of the list

	if (pos == 0)
	{ // process insertion at the beginning of the list  
		temp->next = first;
		first = temp;
	}
	else
	{ // process insertion after the beginning of the list
		// find the node before the insertion point
		Node *current = first;
		for (int i = 1; i < pos; i++)
		{
			current = current->next;
		}
		temp->next = current->next; // set the next pointer in the new node
		current->next = temp;  // set the next pointer in the previous node
	}
	return NO_ERROR;
}

//--- Definition of erase()
// Erase item at pos position.pos 0 is the first element position in the list.
// Precondition: A constructed list, either empty or with elements
// Postcondition : erased item at pos position
// Returns ILLEGAL_LIST_POSITION for erase that is out of range of the current list,
// Otherwise return a NO_ERROR.
int LinkedList::erase(int pos)
{
	if (getListSize() == 0)
	{ // perform error checking on the input
		return ILLEGAL_LIST_POSITION;
	}
	if (pos < 0 || pos >= getListSize())
	{ // perform error checking on the input
		return ILLEGAL_LIST_POSITION;
	}
	Node *temp;
	if (pos == 0)
	{ // if the deletion is the zero node then
		temp = first;   // save pointer to be deleted
		first = first->next;   // bypass node
		delete temp;  // delete node
	}
	else
	{
		// find the node before the deletion point
		Node *current = first;
		for (int i = 1; i < pos; i++)
		{
			current = current->next;
		}
		temp = current->next;  // save pointer to be deleted
		if (pos == (getListSize() - 1))
		{ // if the deleted node is at the end of the list then
			current->next = nullptr;
		}
		else
		{ // else there is another node to link with
			current->next = current->next->next;
		}
		delete temp; // delete the node
	}
	return NO_ERROR;
}
//--- Definition of getListElement()
// Returns list values
// Precondition : A constructed list, either empty or with elements.
// The rv[] array must be large enough to hold the returned contents.
// Postcondition : Fills array rv with the list elements specified
// Returns ILLEGAL_LIST_POSITION for move that is out of range of the current list,
// Otherwise return a NO_ERROR.Both posStart and posEnd must be valid positions
// and posStart <= posEnd.posStart is an index to the start of the data and
// posEnd is an index to the end of the data.To retieve one element
// posStart and posEnd will be the same value.
int LinkedList::getListElement(int posStart, int posEnd, ListElement rv[]) const
{
	if (posStart < 0 || posStart >= getListSize() || posEnd < 0 || posEnd >= getListSize() || posStart > posEnd)
	{ // check for valid paramenters
		return ILLEGAL_LIST_POSITION;
	}
	Node *current = first;   // point to zero node
	for (int i = 0; i < posStart; i++)
	{ // loop to find the node
		current = current->next;
	}
	for (int i = 0; i < ((posEnd - posStart)+1); i++)
	{ // put returned elements in the beginning of the list
		rv[i] = current->data;
		current = current->next;
	}
	return NO_ERROR;
}
//--- Definition of getSize()
// returns the size of the list. Do not change this.
int LinkedList::getListSize() const
{
	int rv = 0;
	Node *current = first;
	for (; current != nullptr;)
	{
		rv++;
		current = current->next;
	}
	return rv;
}

