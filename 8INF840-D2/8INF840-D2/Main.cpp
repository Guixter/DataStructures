#include <iostream>
using namespace std;

void KdTree() {
	SpacePartitioning p;
	p.launch();
}

void PageRank() {

}

void Graph() {
	Zombie z;
	z.launch();
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
	return 0;
}