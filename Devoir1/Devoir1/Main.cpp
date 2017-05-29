#include <iostream>
#include <sstream>
#include <time.h>
#include "Player.h"
#include "Dictionary.h"
#include "Fabrique.h"
#include "FamilyTree.h"
#include "Network.h"

using namespace std;

void Factory() {
	Fabrique *f = new Fabrique();
	f->launch();
	delete f;
}

void launchFamilyTree() {
	FamilyTree *t = new FamilyTree();
	t->launch();
	delete t;
}

void DoubleLinkedList() {
	Network *n = new Network();
	n->launch();
	delete n;
}

void menu() {
	int choice = -1;

	while (choice != 0) {
		cout << "------------------------" << endl;
		cout <<  "Choix de l'exercice :" << endl << endl;
		cout << "1 - Cardgame :" << endl;
		cout << "2 - Factory" << endl;
		cout << "3 - Dictionary" << endl;
		cout << "4 - Family Tree" << endl;
		cout << "5 - Distributed List" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			launchCardGame();
			break;
		case 2:
			Factory();
			break;
		case 3:
			launchDictionnary();
			break;
		case 4:
			launchFamilyTree();
			break;
		case 5:
			DoubleLinkedList();
			break;
		default:
			break;
		}
	}
}

int main() {
	menu();

	system("PAUSE");
	return 0;
}
