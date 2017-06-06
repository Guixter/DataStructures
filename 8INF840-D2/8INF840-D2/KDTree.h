#pragma once
#include "BinaryTree.h"
#include <stdexcept>

struct Point {
	float* coords;
	int dimension;

	Point(int dim) {
		dimension = dim;
		coords = new float[dimension];
	}
};

class KDTree {
public:
	KDTree(int dim);
	~KDTree();

	void insert(Point p) throw (std::logic_error);
	Point searchNearestNeighbour(Point p);

	void print();

private:
	void _insert(Point p, BTNode<Point> *current, int depth);

	BinaryTree<Point> *tree;
	int dimension;
};

