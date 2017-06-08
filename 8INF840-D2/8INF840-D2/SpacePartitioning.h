#pragma once
#include <string>
#include <iostream>
#include "KDTree.h"

class SpacePartitioning
{
public:
	SpacePartitioning();
	~SpacePartitioning();

	void launch();

private:
	void menu();
	Point GetPoint();

	void addPoint();
	void showTree();
	void searchNeighbour();

	KDTree *tree;
};
