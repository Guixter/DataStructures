#include <iostream>
#include <string>
#include "PageRanker.h"
using namespace std;

void KdTree() {
	SpacePartitioning p;
	p.launch();
}

void PageRank() {
	PageRanker* pr = new PageRanker();

	int choice = -1;

	while (choice != 0) {
		cout << "------------------------" << endl;
		cout << "Que voulez vous faire :" << endl << endl;
		cout << "1 - Construire l'hypergraphe depuis les fichiers :" << endl;
		cout << "2 - Indegree" << endl;
		cout << "3 - Page Rank" << endl;
		cout << "4 - Afficher les notes" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			pr->readNodes();
			break;
		case 2:
			PageRanker::Indegree(pr->getA());
			PageRanker::Indegree(pr->getB());
			PageRanker::Indegree(pr->getC());
			break;
		case 3:
			PageRanker::PageRank(pr->getA(), 20);
			PageRanker::PageRank(pr->getB(), 20);
			PageRanker::PageRank(pr->getC(), 20);
			break;
		case 4:
			std::cout << endl << " Granularité au noeud" << endl;
			PageRanker::afficherNotes(pr->getA());
			std::cout << endl << " Granularité à l'hôte" << endl;
			PageRanker::afficherNotes(pr->getB());
			std::cout << endl << " Granularité au domaine" << endl;
			PageRanker::afficherNotes(pr->getC());
			break;
		default:
			break;
		}
	}
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