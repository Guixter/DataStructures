#pragma once
#include "BinaryTree.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

struct Point {
	float* coords;
	int dimension;

	Point(int dim) {
		dimension = dim;
		coords = new float[dimension];
	}

	static float distance(Point p1, Point p2) {
		float dist = 0;
		for (int i = 0; i < p1.dimension; i++) {
			dist += pow((p1.coords[i] - p2.coords[i]), 2);
		}
		return dist;
	}

	void print() {
		std::cout << "(";
		for (int i = 0; i < dimension - 1; i++) {
			std::cout << coords[i] << ", ";
		}
		std::cout << coords[dimension - 1];
		std::cout << ")";
	}
};

class KDTree {
public:
	KDTree(int dim);
	~KDTree();

	void insert(Point p) throw (std::logic_error);
	Point* searchNearestNeighbour(Point p) throw (std::logic_error);
	inline int getDimension() const { return dimension; }
	void print();

private:
	void _insert(Point p, BTNode<Point> *current, int depth) throw (std::logic_error);
	Point* _search(Point p, BTNode<Point> *current, int depth, float* dist);

	BinaryTree<Point> *tree;
	int dimension;
};

