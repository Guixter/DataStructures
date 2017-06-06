#include "HyperGraph.h"
#include<fstream>
using namespace std;

HyperGraph::HyperGraph()
{
}

void HyperGraph::readNodes() {
	ifstream myReadFile;
	string filename = "Content/eu-2005.nodes.txt";
	myReadFile.open(filename);
	char output[500];
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> output;
			//ajouterNoeud(output);
		}
	}
	myReadFile.close();
}


HyperGraph::~HyperGraph()
{
}
