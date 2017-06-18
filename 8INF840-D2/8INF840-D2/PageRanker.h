#pragma once
#include <map>
#include "HyperGraph.h"

typedef std::unordered_set<H_Node*> NodeSet;
typedef HyperGraph<NodeSet>::Node NodeSetNode;
typedef HyperGraph<NodeSet>::Edge EdgeSetNode;

class PageRanker
{
public:
	static constexpr double df = 0.85;

	PageRanker();

	void readNodes();
	std::map<std::string, NodeSetNode*> NodesToBloc(std::map<int, NodeSetNode*> nodes, bool isHost);
	H_Node* getNodeFromSet(NodeSetNode* set);
	std::vector<NodeSetNode*> mapToVector(std::map<std::string, NodeSetNode*> mapNodes);
	std::vector<NodeSetNode*> mapToVector(std::map<int, NodeSetNode*> mapNodes);

	HyperGraph<NodeSet>* createTestHG();

	static void Indegree(HyperGraph<NodeSet>* hg);
	static void PageRank(HyperGraph<NodeSet>* hg, int maxIter);
	static void afficherNotes(HyperGraph<NodeSet>* hg);

	HyperGraph<NodeSet>* getA() { return contentA; };
	HyperGraph<NodeSet>* getB() { return contentA; };
	HyperGraph<NodeSet>* getC() { return contentA; };

	~PageRanker();

private:
	HyperGraph<NodeSet>* contentA;
	HyperGraph<NodeSet>* contentB;
	HyperGraph<NodeSet>* contentC;
};

