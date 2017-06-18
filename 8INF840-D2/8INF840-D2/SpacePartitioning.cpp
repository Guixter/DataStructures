#include "SpacePartitioning.h"
#include "KDTree.h"
#include <iostream>

using namespace std;

SpacePartitioning::SpacePartitioning() {
	// Ask for the dimension of the points
	int dim = 0;
	while (dim <= 0) {
		cout << "Dimension ? ";

		cin >> dim;
		cin.clear();
		cin.ignore(1000, '\n');
	}

	tree = new KDTree(dim);
}

SpacePartitioning::~SpacePartitioning()
{
	delete tree;
}

void SpacePartitioning::launch() {
	// Call the menu
	menu();
}

Point SpacePartitioning::GetPoint() {
	Point p(tree->getDimension());

	cout << "Chose a point :" << endl;
	for (int i = 0; i < tree->getDimension(); i++) {
		cout << "Dimension " << i + 1 << " : ";
		cin >> p.coords[i];

		cin.clear();
		cin.ignore(1000, '\n');
	}

	return p;
}

void SpacePartitioning::menu() {
	int choice = -1;
	while (choice != 0) {
		cout << endl;
		cout << "------------------------" << endl;
		cout << "1 - Add a point :" << endl;
		cout << "2 - Show the tree (in order traversal)" << endl;
		cout << "3 - Search for the nearest neighbour" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			addPoint();
			break;
		case 2:
			showTree();
			break;
		case 3:
			searchNeighbour();
			break;
		default:
			break;
		}
	}
}

void SpacePartitioning::addPoint() {
	Point p = GetPoint();
	tree->insert(p);
}

void SpacePartitioning::showTree() {
	tree->print();
}

void SpacePartitioning::searchNeighbour() {
	Point p = GetPoint();
	Point *neighbour = tree->searchNearestNeighbour(p);

	if (neighbour == NULL) {
		cout << "There is no nearest neighbour..." << endl;
	} else {
		cout << "The nearest neighbour is : ";
		neighbour->print();
		cout << endl;
		delete neighbour;
	}
	
}