#include <iostream>
#include <cstdlib>

using namespace std;

struct Tree
{
	int key;
	Tree* left;
	Tree* right;
};

Tree* createTree(Tree*& grow, int value)
{
	if (grow == NULL)
	{
		Tree* create = new Tree;
		create->key = value;
		create->left = NULL;
		create->right = NULL;

		grow = create;

		return create;
	}
	if (value > grow->key)
	{
		createTree(grow->right, value);
	}
	else if (value == grow->key)
	{
		cout << "The number " << value << " has already been added to the tree\n";
	}
	else
	{
		createTree(grow->left, value);
	}
	return grow;
}

void reverseOrderTree(Tree* show)
{
	if (show != NULL)
	{
		if (show->right != NULL)
		{
			reverseOrderTree(show->right);
		}
		cout << show->key << ' ';
		if (show->left != NULL)
		{
			reverseOrderTree(show->left);
		}
	}
	else
	{
		cout << "Tree is empty\n";
	}
}

void inOrder(Tree* show)
{
	if (show != NULL)
	{
		if (show->left != NULL)
		{
			inOrder(show->left);
		}
		cout << show->key << ' ';
		if (show->right != NULL)
		{
			inOrder(show->right);
		}
	}
	else
	{
		cout << "Tree is empty\n";
	}
}

int nodesCount(Tree* count)
{
	if (count != NULL)
	{
		return 1 + nodesCount(count->left) + nodesCount(count->right);
	}
	else
	{
		return NULL;
	}
}

int heightofTree(Tree* height)
{
	if (height != NULL)
	{
		int leftHeight = heightofTree(height->left);
		int rightHeight = heightofTree(height->right);
		if (leftHeight > rightHeight)
		{
			return 1 + leftHeight;
		}
		else
		{
			return 1 + rightHeight;
		}
	}
	else
	{
		return -1;
	}
}

bool isBalanced(Tree* balance)
{
	if (balance != NULL)
	{
		if (heightofTree(balance->left) - heightofTree(balance->right) <= 1 &&
			heightofTree(balance->right) - heightofTree(balance->left) <= 1)
		{
			cout << "The tree is balanced\n";
			return true;
		}
		else
		{
			cout << "The tree is not balanced\n";
			return false;
		}
	}
	else
	{
		cout << "The tree is empty, but balanced\n";
		return true;
	}
}

bool isSorted(Tree* sort)
{
	if (sort == NULL)
	{
		return true;
	}
	else
	{
		if (sort->left != NULL)
		{
			isSorted(sort->left);
		}
		if (sort->right != NULL)
		{
			isSorted(sort->right);
		}
		if (sort->right == NULL && sort->left == NULL)
		{
			return true;
		}
		if ((sort->left != NULL && sort->key > sort->left->key) || 
			(sort->right != NULL && sort->key < sort->right->key))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void destroyTree(Tree* destroy)
{
	if (destroy != NULL)
	{
		destroyTree(destroy->left);
		destroyTree(destroy->right);
		delete destroy;
	}
}

int main()
{
	
	int choice = 0;
	int number = 0;
	Tree* root = NULL;

	cout << "================ TREE ================\n\n";
	cout << "1. Create tree\n";
	cout << "2. Show tree (in sorted order)\n";
	cout << "3. Show tree (in reverse sorted order)\n";
	cout << "4. Number of nodes in a tree\n";
	cout << "5. Check if the tree is balanced\n";
	cout << "6. Check if the tree is properly sorted\n";
	cout << "7. Exit\n";

	while (true)
	{
		cout << endl;
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1: cout << "Enter the number: ";
			cin >> number;
			createTree(root, number);
			break;
		case 2: inOrder(root);
			break;
		case 3: reverseOrderTree(root);
			break;
		case 4: cout << "There are " << nodesCount(root) << " nodes in the tree\n";
			break;
		case 5: cout << "Height of the tree is " << heightofTree(root) << "\n";
			isBalanced(root);
			break;
		case 6: if (isSorted(root) == false)
			{
				cout << "The tree is not properly sorted\n";
			}
			else
			{
				cout << "The tree is properly sorted\n";
			}
			break;
		case 7: cout << "Goodbye! =)\n";
			cin.get();
			cin.ignore();
			return 0;
		default: return 0;
		}
		cout << endl;
		cout << "================ TREE ================\n\n";
		cout << "1. Create tree\n";
		cout << "2. Show tree (in sorted order)\n";
		cout << "3. Show tree (in reverse sorted order)\n";
		cout << "4. Number of nodes in a tree\n";
		cout << "5. Check if the tree is balanced\n";
		cout << "6. Check if the tree is properly sorted\n";
		cout << "7. Exit\n";
	}
	
	destroyTree(root);

	cin.get();
	cin.ignore();
	return 0;
}
