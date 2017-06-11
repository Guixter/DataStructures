#pragma once
#include <map>
#include "HyperGraph.h"

typedef std::unordered_set<H_Node*> NodeSet;
typedef HyperGraph<NodeSet>::Node NodeSetNode;
typedef HyperGraph<NodeSet>::Edge EdgeSetNode;

class PageRanker
{
public:

	PageRanker();

	void readNodes();
	std::map<std::string, NodeSetNode*> NodesToBloc(std::map<int, NodeSetNode*> nodes, bool isHost);
	H_Node* getNodeFromSet(NodeSetNode* set);
	std::vector<NodeSetNode*> mapToVector(std::map<std::string, NodeSetNode*> mapNodes);

	HyperGraph<NodeSet> create();

	static void Indegree(HyperGraph<NodeSet>* hg);
	static void PageRank(HyperGraph<NodeSet>* hg, int maxIter);

	HyperGraph<NodeSet>* debug() { return contentA; };

	~PageRanker();

private:
	HyperGraph<NodeSet>* contentA;
	HyperGraph<NodeSet>* contentB;
	HyperGraph<NodeSet>* contentC;
};

