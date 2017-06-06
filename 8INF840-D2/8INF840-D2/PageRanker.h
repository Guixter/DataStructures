#pragma once
#include "HyperGraph.h"

class PageRanker
{
public:
	PageRanker();

	void readNodes();

	~PageRanker();

private:
	HyperGraph<Page>* content;
};

