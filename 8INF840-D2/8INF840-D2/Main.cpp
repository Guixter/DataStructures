#include <iostream>
#include <string>
#include "PageRanker.h"
using namespace std;

void KdTree() {

}

void PageRank() {
	PageRanker* hyperGraph = new PageRanker();
	hyperGraph->readNodes();
/*	Page pp = Page(0, 0, "http://curia.eu.int/de/actu/communiques/cp97/cp9776de.htm");
	std::cout << pp.getHost() << std::endl;*/
	int choice = -1;

	while (choice != 0) {
		cout << "------------------------" << endl;
		cout << "? :" << endl << endl;
		cout << "1 - Faire quelque chose :" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			//
			break;
		default:
			break;
		}
	}
}

void Graph() {

}

void menu() {
	int choice = -1;

	while (choice != 0) {
		cout << "------------------------" << endl;
		cout << "Choix de l'exercice :" << endl << endl;
		cout << "1 - KdTree :" << endl;
		cout << "2 - PageRank" << endl;
		cout << "3 - Graph" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			KdTree();
			break;
		case 2:
			PageRank();
			break;
		case 3:
			Graph();
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