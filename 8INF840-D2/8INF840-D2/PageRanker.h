#pragma once
#include <map>
#include "HyperGraph.h"

typedef std::unordered_set<H_Node*> NodeSet;
typedef HyperGraph<NodeSet>::Node NodeSetNode;
typedef HyperGraph<NodeSet>::Edge EdgeSetNode;

struct DomainNodeSet {
	std::unordered_set<NodeSetNode*> Element;
};

typedef HyperGraph<DomainNodeSet>::Node DomainNodeSetNode;
typedef HyperGraph<DomainNodeSet>::Edge DomainEdgeSetNode;

class PageRanker
{
public:
	PageRanker();

	void readNodes();
	std::map<std::string, NodeSetNode*> NodesToBloc(std::map<int, H_Node*> nodes, bool isHost);

	//pour le graphe de base
	static void Indegree(HyperGraph<Page> &pagesToRank);
	static void PageRank(HyperGraph<Page> &pagesToRank);

	~PageRanker();

private:
	HyperGraph<Page>* contentA;
	HyperGraph<NodeSet>* contentB;
	HyperGraph<DomainNodeSet>* contentC;
};

