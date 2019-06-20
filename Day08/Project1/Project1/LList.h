#pragma once

class Node
{
public:
	int Value;

	Node* Next;
};

class LList
{
public:
	LList();
	virtual ~LList();

	void Insert(int NewValue);
	void Remove(int RemoveValue);

	Node* Tail;
	Node* Head;
};
