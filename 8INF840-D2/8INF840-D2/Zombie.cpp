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

	// Print
	/*auto _print = [](GNode<Tower>* n) {
		cout << n->getData().number << endl;
		for (int i = 0; i < n->getNbEdges(); i++) {
			cout << " - " << n->getEdge(i)->target->getData().number << " : " << n->getEdge(i)->weight << endl;
		}
	};

	g->applyNodes(_print);*/
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
	auto _it = [graph](GNode<Tower>* n) {
		auto _it2 = [n](GNode<Tower>* n2) {
			if (!(n->getData() == n2->getData())) {
				float w = Tower::distance(n->getData(), n2->getData());
				GEdge<Tower> *e = new GEdge<Tower>(n, n2, w);
				n->addEdge(e);
			}
		};

		graph->applyBreadthFirst(_it2, n);
	};

	g->applyNodes(_it);
}