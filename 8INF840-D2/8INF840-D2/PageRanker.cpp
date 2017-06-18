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

	ifstream myReadFile("Content/testNodes.txt");
	//ifstream myReadFile("Content/eu-2005.nodes.txt");
	string outputLine;
	string content;

	map<int, NodeSetNode*> nodes;
	std::cout << "Ajout des nodes en cours..." << std::endl;

	//creation des noeuds
	if (myReadFile.is_open()) {

		//lignes de config
		std::getline(myReadFile, outputLine);
		std::getline(myReadFile, outputLine);


		while (std::getline(myReadFile, outputLine)) {
			std::stringstream Line(outputLine);

			std::getline(Line, content, ' ');
			int id = stoi(content);
			std::getline(Line, content, ' ');
			int outdegree = stoi(content);
			std::getline(Line, content, ' ');
			NodeSet* nodeSet = new NodeSet();
			nodeSet->insert(new H_Node(Page(id, outdegree, content)));
			nodes.insert(std::pair<int, NodeSetNode*>(id, new NodeSetNode(*nodeSet)));
						//std::cout << content << std::endl;
		}
		myReadFile.close();
		std::cout << "Fin de l'ajout des nodes" << std::endl;


		//A
		ifstream myReadFile2("Content/testEdges.txt");
		//ifstream myReadFile2("Content/eu-2005.edges.txt");
		std::cout << "Ajout des edges en cours..." << std::endl;
		std::vector<EdgeSetNode*> edges;
		if (myReadFile2.is_open()) {
			std::getline(myReadFile2, outputLine);
			std::getline(myReadFile2, outputLine);
			while (std::getline(myReadFile2, outputLine)) {
				std::stringstream Line(outputLine);

				std::getline(Line, content, ' ');
				int innode = stoi(content);
				std::getline(Line, content, ' ');
				int outnode = stoi(content);

				if (nodes.find(innode) != nodes.end() && nodes.find(outnode) != nodes.end()) {
					edges.push_back(new EdgeSetNode(nodes[innode], nodes[outnode]));
					nodes[innode]->addEdge(nodes[outnode]);
				}
			}

			contentA = new HyperGraph<NodeSet>(nodes[1]);
			contentA->setContent(mapToVector(nodes));
			std::cout << "Fin de l'ajout des edges" << std::endl;
			myReadFile2.close();
		}

		//Host
		std::vector<NodeSetNode*> tempMap = mapToVector(NodesToBloc(nodes, true));
		contentB->setContent(tempMap);

		//Domain
		tempMap = mapToVector(NodesToBloc(nodes, false));
		contentC->setContent(tempMap);
	}
	//system("PAUSE");
}

H_Node* PageRanker::getNodeFromSet(NodeSetNode* set) {
	H_Node* element = *(set->getContent()->begin());
	/*for (NodeSet::iterator i = set->getContent().begin(); i != set->getContent().end(); i++) {
		element = *i;
	}*/
	return element;
}

std::vector<NodeSetNode*> PageRanker::mapToVector(std::map<std::string, NodeSetNode*> mapNodes) {
	std::vector<NodeSetNode*> nodes;
	for (std::map<std::string, NodeSetNode*>::iterator it = mapNodes.begin(); it != mapNodes.end(); ++it) {
		nodes.push_back(it->second);
	}
	return nodes;
}
std::vector<NodeSetNode*> PageRanker::mapToVector(std::map<int, NodeSetNode*> mapNodes) {
	std::vector<NodeSetNode*> nodes;
	for (std::map<int, NodeSetNode*>::iterator it = mapNodes.begin(); it != mapNodes.end(); ++it) {
		nodes.push_back(it->second);
	}
	return nodes;
}

HyperGraph<NodeSet>* PageRanker::createTestHG() {

	std::vector<NodeSetNode*> nodes;


	//noeud 1
	NodeSet* nodeSet1 = new NodeSet();
	nodeSet1->insert(new H_Node(Page(1, 2, "http://de.osha.eu.int/de/print/")));
	NodeSetNode* node1 = new NodeSetNode(*nodeSet1);
	nodes.push_back(node1);


	//noeud 2
	NodeSet* nodeSet2 = new NodeSet();
	nodeSet2->insert(new H_Node(Page(1, 2, "http://de.osha.eu.int/de/print/statistics/EW2002_IBM_Massnahmen_gegen_Stress_am_Arbeitsplatz.php")));
	NodeSetNode* node2 = new NodeSetNode(*nodeSet2);
	nodes.push_back(node2);


	//noeud 3
	NodeSet* nodeSet3 = new NodeSet();
	nodeSet3->insert(new H_Node(Page(1, 2, "http://euro.eu.int/")));
	NodeSetNode* node3 = new NodeSetNode(*nodeSet3);
	nodes.push_back(node3);


	//noeud 4
	NodeSet* nodeSet4 = new NodeSet();
	nodeSet4->insert(new H_Node(Page(1, 2, "http://biodiversity.eionet.eu.int/")));
	NodeSetNode* node4 = new NodeSetNode(*nodeSet4);
	nodes.push_back(node4);

	// 12
	EdgeSetNode* edge12 = new EdgeSetNode(node1, node2);
	node1->addEdge(edge12);
	// 13
	EdgeSetNode* edge13 = new EdgeSetNode(node1, node3);
	node1->addEdge(edge13);
	// 23
	EdgeSetNode* edge23 = new EdgeSetNode(node2, node3);
	node2->addEdge(edge23);
	// 31
	EdgeSetNode* edge31 = new EdgeSetNode(node3, node1);
	node3->addEdge(edge31);
	// 43
	EdgeSetNode* edge43 = new EdgeSetNode(node4, node3);
	node4->addEdge(edge43);
	
	HyperGraph<NodeSet>* hg = new HyperGraph<NodeSet>(node1);
	hg->setContent(nodes);

	return hg;

};

map<string, NodeSetNode*> PageRanker::NodesToBloc(map<int, NodeSetNode*> nodes, bool isHost) {
	map<string, NodeSetNode*> setsHost;
	string host;
	for (map<int, NodeSetNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		//Bloc
		if (!it->second) {
//			In this case one node from the map is null
			continue;
		} else if (it->second) {
			//			std::cout << ((H_Node*)*(it->second->getContent().begin()))->getContent().url << std::endl;
			//std::cout << "ok " << getNodeFromSet(it->second)->getContent().url << std::endl;
		}

		H_Node* nodeSet = getNodeFromSet(it->second);
		host = isHost ? nodeSet->getContent()->getHost() : nodeSet->getContent()->getDomain();
		if (setsHost.find(host) == setsHost.end()) {
			setsHost.insert(std::pair<string, NodeSetNode*>(host, new NodeSetNode(NodeSet())));
		}
		setsHost[host]->getContent()->insert(nodeSet); // Insert currrent Node Page in the right set
		for (HyperGraph<Page>::Edge* edgeNode : nodeSet->getEdges())
		{
			if (edgeNode->getOut()->getContent()->getHost() != host) {
				bool already = false;
				//verifier si setsHost[host]->getEdges() ne contient pas deja celui vers lequel on pointe
				for (EdgeSetNode* edgeNode2 : setsHost[host]->getEdges())
				{
					if (edgeNode2->getOut()->getContent()->find(edgeNode->getOut()) != edgeNode2->getOut()->getContent()->end()) {
						already = true;
						break;
					}
				}
				if (!already) {
					EdgeSetNode* ed = new EdgeSetNode(setsHost[host], new NodeSetNode(NodeSet()));
					ed->getOut()->getContent()->insert(edgeNode->getOut());
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

void PageRanker::Indegree(HyperGraph<NodeSet>* hg) {
	//!!!!mettre le poids de toutes les pages a 0!!!!

	std::vector<HyperGraph<NodeSet>::Node*> blocs = hg->getNodes();
	for (vector<HyperGraph<NodeSet>::Node*>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
	{
		NodeSet* set = (*curBloc)->getContent();
		for (NodeSet::iterator curNode = set->begin(); curNode != set->end(); curNode++)
		{
			//Page* p = 
				(*curNode)->getContent()->weight = 0.0;
			/*Page newPage = Page(p.id, 0.0, p.url);
			(*curNode)->setContent(newPage);*/
			//p.weight = 0.0;
		}
	}

	//pour chaque bloc
	//pour chaque arrete sortante
	//ajouter 1 a la cible
	for (vector<HyperGraph<NodeSet>::Node*>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
	{
		std::vector<HyperGraph<NodeSet>::Edge*> edges = (*curBloc)->getEdges();
		for (vector<HyperGraph<NodeSet>::Edge*>::iterator curEdge = edges.begin(); curEdge != edges.end(); ++curEdge)
		{
			NodeSet* targettedSet = (*curEdge)->getOut()->getContent();
			H_Node *const node = *(targettedSet->begin());

			//Page p = 
				node->getContent()->weight += 1.0;
				/*
			Page newPage = Page(p.id, p.weight + 1.0, p.url);
			node->setContent(newPage);*/
			//p.weight += 1.0;
		}
	}
}
void PageRanker::PageRank(HyperGraph<NodeSet>* hg, int maxIter) {

	//Mettre le poids des pages a 1
	std::vector<HyperGraph<NodeSet>::Node*> blocs = hg->getNodes();
	for (vector<HyperGraph<NodeSet>::Node*>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
	{
		NodeSet* set = (*curBloc)->getContent();
		for (NodeSet::iterator curNode = set->begin(); curNode != set->end(); curNode++)
		{
			
			(*curNode)->getContent()->weight = 1.0;

		}
	}

	int nbIter = 0;
	while (nbIter < maxIter)
	{
		nbIter++;

		//pour chaque bloc
		//calculer note du bloc, somme des notes des pages
		//mettre les notes des pages a 1 - df

		for (vector<HyperGraph<NodeSet>::Node*>::iterator curBloc = blocs.begin(); curBloc != blocs.end(); ++curBloc)
		{
			NodeSet* set = (*curBloc)->getContent();
			(*curBloc)->setWeight(0.0);
			for (NodeSet::iterator curNode = set->begin(); curNode != set->end(); curNode++)
			{
				Page* p = (*curNode)->getContent();
				(*curBloc)->setWeight((*curBloc)->getWeight() + p->weight);
				p->weight = 1.0 - df;
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
				NodeSet* targettedSet = (*curEdge)->getOut()->getContent();
				H_Node *const node = *(targettedSet->begin());
				node->getContent()->weight += df * blocWeight / outDegree;
			}
		}
	}
}

PageRanker::~PageRanker()
{
}
