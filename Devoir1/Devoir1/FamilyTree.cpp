#include "FamilyTree.h"
#include <iostream>
#include <string>
#include <ctime>
#include <functional>

using namespace std;

FamilyTree::FamilyTree() {
	tree = new BinaryTree<Person>();
}

FamilyTree::~FamilyTree()
{
	delete tree;
}

void FamilyTree::launch() {
	// Add the root
	cout << "------------------------" << endl;
	cout << "* Enter the oldest person of the tree (the root) : " << endl;
	tree->add(GetPerson(), NULL);

	// Call the menu
	menu();
}

Person FamilyTree::GetPerson() {
	Person p;
	p.firstname = "";
	p.lastname = "";
	p.age = -1;

	// Firstname
	while (p.firstname.compare("") == 0) {
		cout << "First name ? ";

		getline(cin, p.firstname);
		cin.clear();
	}


	// Lastname
	while (p.lastname.compare("") == 0) {
		cout << "Last name ? ";

		getline(cin, p.lastname);
		cin.clear();
	}

	// Année de naissance
	while (p.age < 0) {
		cout << "Age ? ";

		cin >> p.age;
		cin.clear();
		cin.ignore(1000, '\n');
	}

	// Eye color
	int choice = -1;
	while (choice < 0 || choice > 2) {
		cout << "Eye color (Blue = 0, Green = 1, Brown = 2) ? ";

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	p.eyeColor = static_cast<EyeColor>(choice);

	return p;
}

BTNode<Person>* FamilyTree::SearchPerson() {
	BTNode<Person>* n = NULL;
	Person p;

	while (n == NULL) {
		p.firstname = "";
		p.lastname = "";

		// First name
		while (p.firstname.compare("") == 0) {
			cout << "First name ? ";

			getline(cin, p.firstname);
			cin.clear();
		}

		// Last name
		while (p.lastname.compare("") == 0) {
			cout << "Last name ? ";

			getline(cin, p.lastname);
			cin.clear();
		}

		n = tree->search(p);

		if (n == NULL) {
			cout << p << " is not in the tree." << endl;
		}
	}

	return n;
}

void FamilyTree::menu() {
	int choice = -1;
	while (choice != 0) {
		cout << endl;
		cout << "------------------------" << endl;
		cout << "1 - Add a member :" << endl;
		cout << "2 - Show the tree's size and height" << endl;
		cout << "3 - Show a person's descendants" << endl;
		cout << "4 - Show all the people with an eye color" << endl;
		cout << "5 - Show the same-color-eyed descendants of a person" << endl;
		cout << "6 - Show the average age" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			AddMember();
			break;
		case 2:
			ShowSizeHeight();
			break;
		case 3:
			ShowDescendants();
			break;
		case 4:
			ShowEyeColor();
			break;
		case 5:
			ShowDescendantsEyeColor();
			break;
		case 6:
			ShowAverageAge();
			break;
		default:
			break;
		}
	}
}

void FamilyTree::AddMember() {
	// Find the parent
	cout << "* Chose the parent" << endl;
	BTNode<Person>* parent = SearchPerson();

	// Create the child
	Person child;
	while (true) {
		cout << endl << "* Chose the child" << endl;
		child = GetPerson();

		if (child.age < parent->getData().age) {
			break;
		}
		else {
			cout << "The child must be younger than the parent !" << endl;
		}
	}

	// Add the child to the tree
	tree->add(child, parent);
	cout << endl << child << " has ben added as a child of " << parent->getData() << "." << endl;
	system("pause");
}

void FamilyTree::ShowSizeHeight() {
	cout << endl << "The tree has a size of " << tree->size() << " and a height of " << tree->height() << "." << endl;
	system("pause");
}

void FamilyTree::ShowDescendants() {
	// Search the person
	cout << "Whose descendants ?" << endl;
	BTNode<Person>* n = SearchPerson();

	// Traversal type
	int choice = -1;
	while (choice < 0 || choice > 2) {
		cout << "Traversal ? (Preorder = 0, Inorder = 1, Postorder = 2) ";

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
	}

	// Print
	auto _print = [](BTNode<Person>* p) {
		cout << "- " << p->getData() << endl;
	};
	cout << endl;

	switch (choice) {
	case 0:
		tree->applyPreOrder(_print, n);
		break;
	case 1:
		tree->applyInOrder(_print, n);
		break;
	case 2:
		tree->applyPostOrder(_print, n);
		break;
	default:
		break;
	}
	system("pause");
}

void FamilyTree::ShowEyeColor() {
	// Eye color
	int choice = -1;
	while (choice < 0 || choice > 2) {
		cout << "Eye color (Blue = 0, Green = 1, Brown = 2) ? ";

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	EyeColor c = static_cast<EyeColor>(choice);

	// Print
	auto _print = [c](BTNode<Person>* p) {
		if (p->getData().eyeColor == c) {
			cout << "- " << p->getData() << endl;
		}
	};
	cout << endl;
	tree->applyPreOrder(_print, tree->root());

	system("pause");
}

void FamilyTree::ShowDescendantsEyeColor() {
	// Search the person
	cout << "Whose descendants ?" << endl;
	BTNode<Person>* n = SearchPerson();

	// Print
	auto _print = [n](BTNode<Person>* p) {
		if (p->getData().eyeColor == n->getData().eyeColor) {
			cout << "- " << p->getData() << endl;
		}
	};
	cout << endl;
	tree->applyPreOrder(_print, n);

	system("pause");
}

void FamilyTree::ShowAverageAge() {
	std::function<int(BTNode<Person> const*, int, int)> _aux = [](BTNode<Person> const *n, int left, int right) {
		return left + right + n->getData().age;
	};

	cout << "Average age : " << ((float)(tree->recursive(_aux, tree->root(), 0))) / tree->size() << endl;
	system("pause");
}
