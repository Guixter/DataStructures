#include <iostream>
#include <fstream>
#include <sstream>
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

	map<int, H_Node*> nodes;
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
			nodes.insert(std::pair<int, H_Node*>(id, new H_Node(Page(id, outdegree, content))));
						std::cout << content << std::endl;
		}

		//A
		ifstream myReadFile2("Content/eu-2005.edges.txt");
		std::vector<H_Edge*> edges;
		if (myReadFile2.is_open()) {
			std::getline(myReadFile, outputLine);
			std::getline(myReadFile, outputLine);
			while (std::getline(myReadFile, outputLine)) {
				std::stringstream Line(outputLine);

				std::getline(Line, content, ' ');
				int innode = stoi(content);
				std::getline(Line, content, ' ');
				int outnode = stoi(content);

				if (nodes.find(innode) == nodes.end() && nodes.find(outnode) == nodes.end()) {
					edges.push_back(new H_Edge(nodes[innode], nodes[outnode]));
					nodes[innode]->addEdge(edges[edges.size() - 1]);
				}
			}

			contentA = new HyperGraph<Page>(nodes[0]);
			std::cout << "Fin de l'ajout des edges" << std::endl;
		}

		//Host
		NodesToBloc(nodes, true);

		//Domain
		NodesToBloc(nodes, false);
	}

	system("PAUSE");
	myReadFile.close();
}

map<string, NodeSetNode*> PageRanker::NodesToBloc(map<int, H_Node*> nodes, bool isHost) {
	map<string, NodeSetNode*> setsHost;
	string host;

	//comment faire pour qu'ils ne soient pas supprimes en sortant de la fonction?
	//vector<NodeSetNode*> blocs;

	for (map<int, H_Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		//Bloc
		host = isHost ? it->second->getContent().getHost() : it->second->getContent().getDomain();

		//if bloc doesnt already exists, create it
		if (setsHost.find(host) == setsHost.end()) {
			setsHost.insert(std::pair<string, NodeSetNode*>(host, new NodeSetNode(NodeSet())));
			
		}

		setsHost[host]->getContent().insert(it->second); // Insert currrent Node Page in the right set
		for (HyperGraph<Page>::Edge* edgeNode : it->second->getEdges())
		{
			if (edgeNode->getOut()->getContent().getHost() != host) {
				bool already = false;
				//verifier si setsHost[host]->getEdges() ne contient pas deja celui vers lequel on pointe
				for (EdgeSetNode* edgeNode2 : setsHost[host]->getEdges())
				{
					if (edgeNode2->getOut()->getContent().find(edgeNode->getOut()) != edgeNode2->getOut()->getContent().end()) {
						already = true;
						break;
					}
				}
				if (!already) {
					EdgeSetNode* ed = new EdgeSetNode(setsHost[host], new NodeSetNode(NodeSet()));
					ed->getOut()->getContent().insert(edgeNode->getOut());
					setsHost[host]->addEdge(ed);
				}
			}
		}

	}
	contentB = new HyperGraph<NodeSet>(setsHost[host]);
	return setsHost;
}

void PageRanker::Indegree(HyperGraph<Page> &pagesToRank) {
	//pour chaque bloc
	//pour chaque arrete partant du bloc
	//ajouter 1 a la page cible
	vector<HyperGraph<Page>::Bloc> blocs = pagesToRank.getBlocs();
	for(vector<HyperGraph<Page>::Bloc>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
	{
		vector<HyperGraph<Page>::Edge*> edges = curBloc->getEdge();
		for (vector<HyperGraph<Page>::Edge*>::iterator curEdge = edges.begin(); curEdge != edges.end(); ++curEdge) 
		{
			Page pointed = (*curEdge)->getOut()->getContent();
			pointed.weight += 1;
		}
		
	}
	
}

void PageRanker::PageRank(HyperGraph<Page> &pagesToRank) {

}

PageRanker::~PageRanker()
{
}
