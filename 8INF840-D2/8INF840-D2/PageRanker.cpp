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
	//ifstream myReadFile("Content/testNodes.txt");
	ifstream myReadFile("Content/eu-2005.nodes.txt");
	string outputLine;
	string content;

	map<int, NodeSetNode*> nodes;
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
			NodeSet nodeSet = NodeSet();
			nodeSet.insert(new H_Node(Page(id, outdegree, content)));
			nodes.insert(std::pair<int, NodeSetNode*>(id, new NodeSetNode(nodeSet)));
						std::cout << content << std::endl;
		}

		//A
		//ifstream myReadFile2("Content/testEdges.txt");
		ifstream myReadFile2("Content/eu-2005.edges.txt");
		std::vector<EdgeSetNode*> edges;
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
					edges.push_back(new EdgeSetNode(nodes[innode], nodes[outnode]));
					nodes[innode]->addEdge(edges[edges.size() - 1]);
				}
			}

			contentA = new HyperGraph<NodeSet>(nodes[0]);
			std::cout << "Fin de l'ajout des edges" << std::endl;
		}

		//Host
		contentB->setContent(mapToVector(NodesToBloc(nodes, true)));

		//Domain
		contentC->setContent(mapToVector(NodesToBloc(nodes, false)));
	}

	system("PAUSE");
	myReadFile.close();
}

H_Node* PageRanker::getNodeFromSet(NodeSetNode* set) {
	H_Node* element;
	for (NodeSet::iterator i = set->getContent().begin(); i != set->getContent().end(); i++) {
		element = *i;
	}
	return element;
}

std::vector<NodeSetNode*> PageRanker::mapToVector(std::map<std::string, NodeSetNode*> mapNodes) {
	std::vector<NodeSetNode*> nodes;
	for (std::map<std::string, NodeSetNode*>::iterator it = mapNodes.begin(); it != mapNodes.end(); ++it) {
		nodes.push_back(it->second);
	}
	return nodes;
}

map<string, NodeSetNode*> PageRanker::NodesToBloc(map<int, NodeSetNode*> nodes, bool isHost) {
	map<string, NodeSetNode*> setsHost;
	string host;
	for (map<int, NodeSetNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		//Bloc
		H_Node* nodeSet = getNodeFromSet(it->second);
		host = isHost ? nodeSet->getContent().getHost() : nodeSet->getContent().getDomain();
		if (setsHost.find(host) == setsHost.end()) {
			setsHost.insert(std::pair<string, NodeSetNode*>(host, new NodeSetNode(NodeSet())));
		}
		setsHost[host]->getContent().insert(nodeSet); // Insert currrent Node Page in the right set
		for (HyperGraph<Page>::Edge* edgeNode : nodeSet->getEdges())
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
	if (isHost) {
		contentB = new HyperGraph<NodeSet>(setsHost[host]);
	}
	else {
		contentC = new HyperGraph<NodeSet>(setsHost[host]);
	}
	return setsHost;
}

void PageRanker::Indegree(HyperGraph<NodeSet> &hg) {
	//!!!!mettre le poids de toutes les pages a 0!!!!

	//pour chaque bloc
	//pour chaque arrete sortante
	//ajouter 1 a la cible
	std::vector<HyperGraph<NodeSet>::Node*> blocs = hg.getNodes();
	for (vector<HyperGraph<NodeSet>::Node*>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
	{
		std::vector<HyperGraph<NodeSet>::Edge*> edges = (*curBloc)->getEdges();
		for (vector<HyperGraph<NodeSet>::Edge*>::iterator curEdge = edges.begin(); curEdge != edges.end(); ++curEdge)
		{
			NodeSet targettedSet = (*curEdge)->getOut()->getContent();
			H_Node *const node = *(targettedSet.begin());

			Page p = node->getContent();
			p.weight += 1.0;
		}
	}
}
void PageRanker::PageRank(HyperGraph<NodeSet> &hg) {

	//!!!!mettre le poids de toutes les pages a 1!!!!
	double df = 0.85;

	//pour chaque bloc
	//calculer note du bloc, somme des notes des pages
	//mettre les notes des pages a 1 - df

	std::vector<HyperGraph<NodeSet>::Node*> blocs = hg.getNodes();
	for (vector<HyperGraph<NodeSet>::Node*>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
	{
		NodeSet set = (*curBloc)->getContent();
		for (NodeSet::iterator curNode = set.begin(); curNode != set.end(); curNode++)
		{
			Page p = (*curNode)->getContent();
			(*curBloc)->setWeight((*curBloc)->getWeight() + p.weight);
			p.weight = 1.0 - df;
		}
	}


	//pour chaque bloc
	//pour chaque arrete sortante
	//ajouter df * note du bloc / nb arcs sortants a la note de la page cible
	for (vector<HyperGraph<NodeSet>::Node*>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
	{
		std::vector<HyperGraph<NodeSet>::Edge*> edges = (*curBloc)->getEdges();
		int outDegree = edges.size();
		double blocWeight = (*curBloc)->getWeight();
		for (vector<HyperGraph<NodeSet>::Edge*>::iterator curEdge = edges.begin(); curEdge != edges.end(); ++curEdge)
		{
			NodeSet targettedSet = (*curEdge)->getOut()->getContent();
			H_Node *const node = *(targettedSet.begin());
			Page p = node->getContent();

			p.weight += df * blocWeight / outDegree;
		}
	}
}

PageRanker::~PageRanker()
{
}
