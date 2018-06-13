#include <iostream>
#include <string>

using namespace std;

struct Map
{
	string key;
	string value;
	Map* left;
	Map* right;
};

//Defining root as a global variable, later You will understand why I did it
Map* root = NULL;
//Allowing overwriting e-mail addresses
Map* overwrite(Map*&, string);
//Finding if the user with the same e-mail already exists in the tree
Map* findEqual(Map*&, string);
//Function that checks if the current e-mail that user is inputting exists in the tree
bool findEqualValue(Map*&, string);
//Function that shows the number of users with the same name in the tree
int nofEqaulNames(Map*&, string);

//Add node to the tree function
Map* add(Map*& build, string name, string email)
{
	if (build == NULL)
	{
		Map* create = new Map;
		create->key = name;
		create->value = email;
		create->left = NULL;
		create->right = NULL;

		build = create;

		return create;
	}
	else
	{
		/*If the tree is not empty, I'm checking if the curent e-mail that user is typing already exists in the tree.
		I'm doing this in order to prevent the situation when there are users with the same emails. 
		Though I'm giving the opportunity to have same e-mails, this is just another case.
		(the usernames can be the same, but the e-mail addresses must be different)
		*/
		findEqual(build, email);
		if (name > build->key)
		{
			add(build->right, name, email);
		}
		else
		{
			add(build->left, name, email);
		}
	}
	return build;
}

/*Here I'm overwriting existing e-mail with the e-mail that doesn't exist in the tree. 
In other words with the unique e-mail address.*/
Map* overwrite(Map*& person, string email)
{
	person->value = email;
	return person;
}

//Here I'm finding e-mail that already exists in the tree, of course, if it exists at all.
Map* findEqual(Map*& equal, string searchingEmail)
{
	if (equal != NULL)
	{
		if (searchingEmail == equal->value)
		{
			int choice = 0;
			cout << "E-mail " << searchingEmail << " is already exists in the address book\n";
			cout << "Do you want to overwrite existing email? (1 for yes 0 for no)" << endl;
			cout << endl;
			cin >> choice;
			if (choice == 1)
			{
				cout << endl;
				cin.ignore();
				do
				{
					cout << "Enter person's e-mail: ";
					getline(cin, searchingEmail);
					//If the user typing the same e-mail that he's just typed
					if (searchingEmail == equal->value)
					{
						cout << "E-mail " << searchingEmail << " is already exists in the address book!\n";
					}
					/*If an e-mail already exists in the tree.
					In this function "findEqualValue(root, searchingEmail)" as a first parameter, I'm passing the root, 
					because only this way I can search through the whole tree, starting with the root.*/
					else if (findEqualValue(root, searchingEmail) == false)
					{
						cout << "E-mail " << searchingEmail << " is already exists in the address book!\n";
					}
				} while (searchingEmail == equal->value || findEqualValue(root, searchingEmail) == false);

				//Overwriting existing e-mail
				overwrite(equal, searchingEmail);
				cout << endl;
				cout << "The data has been overwritten\n";

				return equal;
			}
		}
		if (equal->left != NULL)
		{
			findEqual(equal->left, searchingEmail);
		}
		if (equal->right != NULL)
		{
			findEqual(equal->right, searchingEmail);
		}
	}
	else
	{
		return NULL;
	}
	return equal;
}

//Here I go through the whole tree to find out if there is a user with the same e-mail
bool findEqualValue(Map*& subTreeRoot, string searchingValue) 
{
	if (subTreeRoot != NULL) 
	{
		if (subTreeRoot->value == searchingValue)
		{
			return false;
		}
		bool leftResult = findEqualValue(subTreeRoot->left, searchingValue);
		bool rightResult = findEqualValue(subTreeRoot->right, searchingValue);

		/*If there is the same user with the same e-mail then I'm returning false.
		For example, first, we walked through the left subtree and didn't find the same e-mail.
		But then we walked through the right subtree and find our e-mail, we returning false as a result.
		In the end, we compare what our leftResult returned and our rightResult returned.
		If leftResult returned true, but the rightResult returned false, then we return false as a function result.
		Because true && false = false.
		The same as false && true = false.*/
		return leftResult && rightResult;
	}
	else
	{
		return true;
	}
}

//Counting number of the users with the same names
int nofEqaulNames(Map*& equalNames, string name)
{
	if (equalNames != NULL)
	{
		if (equalNames->left != NULL)
		{
			nofEqaulNames(equalNames->left, name);
		}
		if (name == equalNames->key)
		{
			if (equalNames->left)
			{
				return 1 + nofEqaulNames(equalNames->left, name);
			}
			else
			{
				return 1 + nofEqaulNames(equalNames->right, name);
			}
		}
		if (equalNames->right != NULL)
		{
			nofEqaulNames(equalNames->right, name);
		}
		return nofEqaulNames(equalNames->left, name) + nofEqaulNames(equalNames->right, name);
	}
	else
	{
		return 0;
	}
}

//Displaying all users with the same names
void showEqualNames(Map*& showEqual, string name)
{
	if (showEqual != NULL)
	{
		if (showEqual->left != NULL)
		{
			showEqualNames(showEqual->left, name);
		}
		if (name == showEqual->key)
		{
			cout << endl;
			cout << "Name: " << showEqual->key << endl;
			cout << "E-mail: " << showEqual->value << endl;
		}
		if (showEqual->right != NULL)
		{
			showEqualNames(showEqual->right, name);
		}
	}
	else
	{
		//cout << "Something\n";
	}
}

//Displaying all users that are in the tree
void showMap(Map* show)
{
	if (show != NULL)
	{
		if (show->left != NULL)
		{
			showMap(show->left);
		}
		cout << endl;
		cout << "Name: " << show->key << endl;
		cout << "E-mail: " << show->value << endl;
		if (show->right != NULL)
		{
			showMap(show->right);
		}
	}
	else
	{
		cout << "My address book is empty\n";
	}
}

//Counting all users in the tree
int totalCount(Map* count)
{
	if (count != NULL)
	{
		return 1 + totalCount(count->left) + totalCount(count->right);
	}
	else
	{
		return 0;
	}
}

//Searching users in the tree
bool search(Map*& find, string lookup)
{
	if (find != NULL)
	{
		if (find->key == lookup)
		{
			//If there are more than 1 person in the tree with the same name, then I'm displaying them all
			if (nofEqaulNames(find, lookup) > 1)
			{
				cout << endl;
				//Showing the number of these users
				cout << "There are " << nofEqaulNames(find, lookup) << " persons with this name:\n";
				//Displaying them all
				showEqualNames(find, lookup);

				return true;
			}
				cout << endl;
				cout << "Person is found\n";
				cout << "Name: " << find->key << endl;
				cout << "E-mail: " << find->value << endl;

				return true;
			
		}
		if (lookup < find->key)
		{
			return search(find->left, lookup);
		}
		else
		{
			return search(find->right, lookup);
		}
	}
	else
	{
		cout << lookup << " not found\n";
		return false;
	}
}

Map* findGreatest(Map* greatest)
{
	if (greatest == NULL)
	{
		//cout << "The tree is empty\n";
		return NULL;
	}
	else
	{
		if (greatest->right != NULL)
		{
			return findGreatest(greatest->right);
		}
	}
	//cout << "The greatest key in the tree is " << greatest->key << endl;
	return greatest;
}

//Removing user from the tree
Map* remove(Map*& delPerson, string lookupPerson, string lookupEmail)
{
	if (delPerson == NULL)
	{
		cout << "Person " << '*' << lookupPerson << '*' << " with e-mail " << '*' << lookupEmail << '*' << " not found\n";
		return delPerson;
	}
	else
	{
		if (delPerson->left != NULL)
		{
			remove(delPerson->left, lookupPerson, lookupEmail);
		}
		/*This is very important. We can have users with the same names, but their e-mail addresses
		will differ, so we can't just search only by name, we have to search specific user with unique e-mail.*/
		if (delPerson->value == lookupEmail && delPerson->key == lookupPerson)
		{
			Map* temp = delPerson;
			//case 0: Node has no children
			if (delPerson->left == NULL && delPerson->right == NULL)
			{
				delPerson = NULL;

				delete temp;

				temp = NULL;
				cout << endl;
				cout << "Person " << '*' << lookupPerson << '*' << " with e-mail " << '*' << lookupEmail << '*'
					<< " was deleted\n";

				return delPerson;
			}
			// case 1: Node has one children
			//Node has left child, but no right child
			else if (delPerson->left != NULL && delPerson->right == NULL)
			{
				delPerson = delPerson->left;

				delete temp;

				temp = delPerson;
				cout << endl;
				cout << "Person " << '*' << lookupPerson << '*' << " with e-mail " << '*' << lookupEmail << '*'
					<< " was deleted\n";

				return temp;
			}
			//Node has right child, but no left child
			else if (delPerson->right != NULL && delPerson->left == NULL)
			{
				delPerson = delPerson->right;

				delete temp;

				temp = delPerson;
				cout << endl;
				cout << "Person " << '*' << lookupPerson << '*' << " with e-mail " << '*' << lookupEmail << '*'
					<< " was deleted\n";

				return temp;
			}
			// case 2: Node has two children
			else
			{
				/*This is the case where I choose the path where I'm picking the greatest value in the left subtree. 
				Similarly, I could pick the smallest value in the right subtree.*/
				temp = findGreatest(delPerson->left);
				delPerson->key = temp->key;
				delPerson->value = temp->value;
				cout << endl;
				cout << "Person " << '*' << lookupPerson << '*' << " with e-mail " << '*' << lookupEmail << '*'
					<< " was overwritten by " << '*' << temp->key << '*' << " with e-mail "
					<< '*' << temp->value << '*';
				delPerson->left = remove(delPerson->left, temp->key, temp->value);
			}
		}
		if (delPerson->right != NULL)
		{
			remove(delPerson->right, lookupPerson, lookupEmail);
		}
	}
	return delPerson;
}

//Destroying the whole tree to free all the memory that I allocated
void destroyMap(Map* destroy)
{
	if (destroy != NULL)
	{
		destroyMap(destroy->left);
		destroyMap(destroy->right);
		delete destroy;
	}
}

int main()
{
	string name;
	string email;
	int choice = 0;

	cout << "=========================== My Address Book ===========================\n\n";
	cout << "1. Add the person to the book\n";
	cout << "2. Show my address book\n";
	cout << "3. Search to person\n";
	cout << "4. Delete person\n";
	cout << "5. Exit\n";

	while (true)
	{
		cout << endl;
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1: cin.ignore();
			system("cls");
			cout << endl;
			cout << "Enter person's name: ";
			getline(cin, name);
			cout << "Enter person's e-mail: ";
			getline(cin, email);
			add(root, name, email);
			system("cls");
			break;
		case 2: system("cls");
			cout << endl;
			showMap(root);
			cout << endl;
			if (totalCount(root) > 1)
			{
				cout << "There are " << totalCount(root) << " persons in my address book\n";
			}
			if (totalCount(root) == 1)
			{
				cout << "There is only " << totalCount(root) << " person in my address book\n";
			}
			break;
		case 3: cin.ignore();
			system("cls");
			cout << endl;
			cout << "Enter person's name: ";
			getline(cin, name);
			//nofEqaulNames(root, name);
			search(root, name);
			break;
		case 4: cin.ignore();
			system("cls");
			cout << endl;
			cout << "Enter person's name: ";
			getline(cin, name);
			cout << "Enter person's e-mail: ";
			getline(cin, email);
			//findGreatest(root);
			remove(root, name, email);
			break;
		case 5: system("cls");
			cout << endl;
			cout << "Goodbye!\n";
			cin.get();
			cin.ignore();
			return 0;
		default: return 0;
		}
		cout << endl;
		cout << "=========================== My Address Book ===========================\n\n";
		cout << "1. Add the person to the book\n";
		cout << "2. Show my address book\n";
		cout << "3. Search to person\n";
		cout << "4. Delete person\n";
		cout << "5. Exit\n";
	}

	destroyMap(root);

	cin.get();
	cin.ignore();
	return 0;
}
