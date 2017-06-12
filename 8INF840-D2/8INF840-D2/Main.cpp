#include <iostream>
#include <string>
#include "PageRanker.h"
using namespace std;

void KdTree() {

}

void PageRank() {
	PageRanker* pr = new PageRanker();
	pr->readNodes();
	//Page pp = Page(0, 0, "http://curia.eu.int/de/actu/communiques/cp97/cp9776de.htm");
	//std::cout << pp.getDomain() << std::endl;
	/*HyperGraph<NodeSet>* hga = hyperGraph->debug();
	std::cout << hga->getNodes().size() << endl;*/
	//HyperGraph<NodeSet> hg = pr->create();

	//
/*	std::vector<NodeSetNode*> nodes;


	//noeud 1
	NodeSet nodeSet1 = NodeSet();
	nodeSet1.insert(new H_Node(Page(1, 2, "http://de.osha.eu.int/de/print/")));
	NodeSetNode node1 = NodeSetNode(nodeSet1);
	nodes.push_back(&node1);


	//noeud 2
	NodeSet nodeSet2 = NodeSet();
	nodeSet2.insert(new H_Node(Page(1, 1, "http://de.osha.eu.int/de/print/statistics/EW2002_IBM_Massnahmen_gegen_Stress_am_Arbeitsplatz.php")));
	NodeSetNode node2 = NodeSetNode(nodeSet2);
	nodes.push_back(&node2);


	//noeud 3
	NodeSet nodeSet3 = NodeSet();
	nodeSet3.insert(new H_Node(Page(1, 1, "http://euro.eu.int/")));
	NodeSetNode node3 = NodeSetNode(nodeSet3);
	nodes.push_back(&node3);


	//noeud 4
	NodeSet nodeSet4 = NodeSet();
	nodeSet4.insert(new H_Node(Page(1, 1, "http://biodiversity.eionet.eu.int/")));
	NodeSetNode node4 = NodeSetNode(nodeSet4);
	nodes.push_back(&node4);

	// 12
	EdgeSetNode edge12 = EdgeSetNode(&node1, &node2);
	node1.addEdge(&edge12);
	// 13
	EdgeSetNode edge13 = EdgeSetNode(&node1, &node3);
	node1.addEdge(&edge13);
	// 23
	EdgeSetNode edge23 = EdgeSetNode(&node2, &node3);
	node2.addEdge(&edge23);
	// 31
	EdgeSetNode edge31 = EdgeSetNode(&node3, &node1);
	node3.addEdge(&edge31);
	// 43
	EdgeSetNode edge43 = EdgeSetNode(&node4, &node3);
	node4.addEdge(&edge43);

	HyperGraph<NodeSet>* hg = new HyperGraph<NodeSet>(&node1);
	hg->setContent(nodes);
	//

	PageRanker::Indegree(hg);

	PageRanker::PageRank(hg, 20);
	*/

	int choice = -1;

	while (choice != 0) {
		cout << "------------------------" << endl;
		cout << "Que voulez vous faire :" << endl << endl;
		cout << "1 - Construire l'hypergraphe depuis les fichiers :" << endl;
		cout << "2 - Indegree" << endl;
		cout << "3 - Page Rank" << endl;
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