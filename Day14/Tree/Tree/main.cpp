#include <iostream>
#include <stack>
using namespace std;

class Node
{
public:
	Node* Parent;

	Node* Left;
	Node* Right;

	int Data;
};

class BinaryTree
{
public:
	BinaryTree(int Data = 1)
	{
		Root = new Node();
		Root->Data = Data;
	}

	Node* Root;

	void Traversal()
	{
		Traversal(Root);
	}

	Node* Search(int Data)
	{
		return Search(Root, Data);
	}

	void InsertLeft(int SearchData, int Data)
	{
		Node* InsertPoint = Search(SearchData);

		if (InsertPoint)
		{
			InsertPoint->Left = new Node();
			InsertPoint->Left->Data = Data;
			InsertPoint->Left->Parent = InsertPoint;
		}
	}

	void InsertRight(int SearchData, int Data)
	{
		Node* InsertPoint = Search(SearchData);

		if (InsertPoint)
		{
			InsertPoint->Right = new Node();
			InsertPoint->Right->Data = Data;
			InsertPoint->Right->Parent = InsertPoint;
		}
	}

protected:
	Node* Search(Node* Current, int Data)
	{
		if (Current == nullptr)
		{
			return nullptr;
		}
		if (Current->Data == Data)
		{
			return Current;
		}

		Node*Temp;
		Temp = Search(Current->Left, Data);
		
		if (Temp)
		{
			return Temp;
		}

		Temp = Search(Current->Right, Data);

		if (Temp)
		{
			return Temp;
		}

		return nullptr;
	}

	void Traversal(Node* Current)
	{
		if (Current == nullptr)
		{
			return;
		}

		Traversal(Current->Left);
		Traversal(Current->Right);
	}
};

class BinarySearchTree : public BinaryTree
{
public:
	BinarySearchTree(int Data) :BinaryTree(Data) {};

	void Insert(int Data)
	{
		InsertNode(Root->Parent, Root, Data);
	}

	void InsertNode(Node* Parent, Node* Current, int Data)
	{
		if (Current == nullptr)
		{
			Current = new Node();
			Current->Data = Data;
			Current->Parent = Parent;

			return;
		}

		if (Data < Current->Data)
		{
			InsertNode(Current, Current->Left, Data);
		}
		else
		{
			InsertNode(Current, Current->Right, Data);
		}
	}

protected:
	Node* Search(Node* Current, int Data)
	{
		if (Current == nullptr)
		{
			return nullptr;
		}
		
		if (Current->Data == Data)
		{
			return Current;
		}
		else if (Current->Data > Data)
		{
			return Search(Current->Left, Data);
		}
		else
		{
			return Search(Current->Right, Data);
		}

		return nullptr;
	}
};

bool BinarySearch(Node* node, int data)
{
	if (node == nullptr)
	{
		return 0;
	}
	else if (node->Data == data)
	{
		return 1;
	}
	else
	{
		if (BinarySearch(node->Left, data))
		{
			return 1;
		}
		else if (BinarySearch(node->Right, data))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

bool BinarySearch2(Node* node, int data)
{
	stack<Node*> s;
	s.push(node);
	while (!s.empty())
	{
		node = s.top();
		s.pop();
		if (node->Data == data)
		{
			return 1;
		}

		if (node->Right != nullptr)
		{
			s.push(node->Right);
		}
		if (node->Left != nullptr)
		{
			s.push(node->Left);
		}
	}

	return 0;
}

int main()
{
	BinaryTree Number;

	Number.Root->Left = new Node();
	Number.Root->Left->Data = 2;

	Number.Root->Right = new Node();
	Number.Root->Right->Data = 3;

	Number.Root->Left->Left = new Node();
	Number.Root->Left->Left->Data = 4;

	Number.Root->Left->Right = new Node();
	Number.Root->Left->Right->Data = 5;

	Number.Root->Right->Left = new Node();
	Number.Root->Right->Left->Data = 6;

	Number.Root->Right->Right = new Node();
	Number.Root->Right->Right->Data = 7;

	//cout << BinarySearch2(Number.Root, 8) << endl;
	//Number.Traversal();
	Node* Temp = Number.Search(3);

	cout << Temp->Data << endl;

	return 0;
}