#include "Zombie.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Zombie::Zombie()
{
	g = new Graph<Tower>();
}

Zombie::~Zombie()
{
	delete g;
}

void Zombie::launch() {
	loadFile();
	compute();
}

void Zombie::loadFile() {
	// Load the file
	ifstream *input = new ifstream("ville.txt");
	if (input->fail()) {
		cout << "The file is not available." << endl;
		return;
	}

	// Create the nodes
	char* buffer = new char[100];
	while (!input->eof()) {
		input->getline(buffer, 100);
		string s(buffer);
		std::istringstream in(s);
		
		int num;
		float x, y;
		in >> num >> x >> y;

		Tower t;
		t.number = num;
		t.x = x;
		t.y = y;
		g->addNode(t);
	}
	delete[] buffer;

	// Add the edges
	Graph<Tower> *graph = g;
	auto _it = [graph](GNode<Tower>* n) {
		auto _it2 = [n](GNode<Tower>* n2) {
			if (!(n->getData() == n2->getData())) {
				float w = Tower::distance(n->getData(), n2->getData());
				GEdge<Tower> *e = new GEdge<Tower>(n, n2, w);
				n->addEdge(e);
			}
		};

		graph->applyNodes(_it2);
	};
	g->applyNodes(_it);


	// Close the file
	input->close();
	delete input;
}

void Zombie::compute() {
	Graph<Tower> *graph = g;
	GNode<Tower> *bestNode = NULL;
	float bestCritical = -1;
	auto _it = [graph, &bestNode, &bestCritical](GNode<Tower>* n) {
		// Apply dijkstra
		graph->dijkstra(n);

		// Compute the critical path
		float critical = -1;
		auto _it2 = [graph, &critical](GNode<Tower>* n2) {
			if (critical == -1 || n2->getDistance() > critical) {
				critical = n2->getDistance();
			}
		};
		graph->applyNodes(_it2);
		//cout << "Le noeud " << n->getData().number << " a pour chemin critique : " << critical << endl;

		// Update the best node
		if (bestNode == NULL || bestCritical > critical) {
			bestNode = n;
			bestCritical = critical;
		}
	};

	g->applyNodes(_it);

	cout << "Le meilleur point de debut est la tour no " << bestNode->getData().number << " (chemin critique : " << bestCritical << ")." << endl;
}