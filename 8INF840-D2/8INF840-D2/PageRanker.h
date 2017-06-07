#pragma once
#include "HyperGraph.h"

typedef std::unordered_set<H_Node*> NodeSet;
typedef HyperGraph<NodeSet>::Node NodeSetNode;
typedef HyperGraph<NodeSet>::Edge EdgeSetNode;

class PageRanker
{
public:
	PageRanker();

	void readNodes();

	~PageRanker();

private:
	HyperGraph<Page>* contentA;
	HyperGraph<NodeSet>* contentB;
	HyperGraph<Page>* contentC;
};

