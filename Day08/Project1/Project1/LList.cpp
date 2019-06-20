#include "LList.h"



LList::LList()
{
	Head = new Node();
	Tail = new Node();
	Head->Next = Tail;
}

LList::~LList()
{
}

void LList::Insert(int NewValue)
{
	Node* NewNode = new Node();
	NewNode->Value = NewValue;
	
	Node* Find;
	for (Find = Head; Find->Next != Tail; Find = Find->Next);
	Find->Next = NewNode;
	NewNode->Next = Tail;
}

void LList::Remove(int RemoveValue)
{
	Node* preFind;
	Node* Find;
	for (Find = Head; Find->Value != RemoveValue; Find = Find->Next)
		preFind = Find;
	preFind->Next = Find->Next;
}
