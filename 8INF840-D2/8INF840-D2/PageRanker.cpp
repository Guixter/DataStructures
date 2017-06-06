#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

#include "PageRanker.h"
using namespace std;

PageRanker::PageRanker()
{
}

void PageRanker::readNodes() {
	ifstream myReadFile("Content/eu-2005.nodes.txt");
	string outputLine;
	string content;

	map<int, HyperGraph<Page>::Node<Page>*> nodes;
	if (myReadFile.is_open()) {
		std::getline(myReadFile, outputLine);
		std::getline(myReadFile, outputLine);
		while (std::getline(myReadFile, outputLine)) {
			std::stringstream Line(outputLine);

			std::getline(Line, content, ' ');
			int id = stoi(content);
			std::getline(Line, content, ' ');
			int outdegree = stoi(content);
			std::getline(Line, content, ' ');
			nodes.insert(std::pair<int, HyperGraph<Page>::Node<Page>*>(id, new HyperGraph<Page>::Node<Page>(Page(id, outdegree, content))));
			//			std::cout << content << std::endl;
		}

		ifstream myReadFile2("Content/eu-2005.edges.txt");
		std::vector<HyperGraph<Page>::Edge<Page>*> edges;
		map<HyperGraph<Page>::Node<Page>*, vector<std::unordered_set<HyperGraph<Page>::Edge<Page>*>>> nodeEdges;
		if (myReadFile2.is_open()) {
			std::getline(myReadFile, outputLine);
			std::getline(myReadFile, outputLine);
			while (std::getline(myReadFile, outputLine)) {
				std::stringstream Line(outputLine);

				std::getline(Line, content, ' ');
				int innode = stoi(content);
				std::getline(Line, content, ' ');
				int outnode = stoi(content);

				if (nodes.at(innode) && nodes.at(outnode)) {
					edges.push_back(new HyperGraph<Page>::Edge<Page>(nodes[innode], nodes[outnode]));
					nodes[innode]->addEdge(edges[edges.size() - 1]);
				}
			}

			std::cout << "Fin de l'ajout des edges" << std::endl;
		}

		map<string, std::unordered_set<HyperGraph<Page>::Node<Page>*>*> setsHost;

		for (map<int, HyperGraph<Page>::Node<Page>*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			//Bloc
			string host = it->second->getContent().getHost();
			if (setsHost.find(host) == setsHost.end()) {
				setsHost.insert(std::pair<string, std::unordered_set<HyperGraph<Page>::Node<Page>*>*>(host, new std::unordered_set<HyperGraph<Page>::Node<Page>*>() ));
			}


		}

	}

	myReadFile.close();
}


PageRanker::~PageRanker()
{
}
