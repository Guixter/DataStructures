#include "KDTree.h"
#include <iostream>
#include <limits>

using namespace std;

KDTree::KDTree(int dim)
{
	dimension = dim;
	tree = new BinaryTree<Point>();
}

KDTree::~KDTree()
{
	delete tree;
}


void KDTree::insert(Point p) {
	if (p.dimension != dimension) {
		throw std::logic_error("The dimensions are not the same.");
	}

	if (tree->empty()) {
		tree->add(p, NULL);
	} else {
		_insert(p, tree->root(), 0);
	}
}

void KDTree::_insert(Point p, BTNode<Point> *current, int depth) {
	if (Point::distance(p, current->getData()) == 0) {
		throw std::logic_error("The point is already in the tree.");
	}

	int dim = depth % p.dimension;
	if (p.coords[dim] <= current->getData().coords[dim]) {
		if (current->getLeftChild() != NULL) {
			_insert(p, current->getLeftChild(), depth+1);
		} else {
			tree->add(p, current, BinaryTree<Point>::LEFT);
		}
	} else {
		if (current->getRightChild() != NULL) {
			_insert(p, current->getRightChild(), depth + 1);
		}
		else {
			tree->add(p, current, BinaryTree<Point>::RIGHT);
		}
	}
}

Point* KDTree::_search(Point p, BTNode<Point> *current, int depth, float* dist) {
	// Handle the NULL case
	if (current == NULL) {
		*dist = numeric_limits<float>::max();
		return NULL;
	}
	int dim = depth % p.dimension;
	Point c = current->getData();

	// Handle the leaves
	if (current->getLeftChild() == NULL && current->getRightChild() == NULL) {
		*dist = Point::distance(c, p);
		return new Point(c);
	}

	// Compute the "best branch" and the other one
	BTNode<Point> *bestBranch, *otherBranch;
	if (p.coords[dim] <= c.coords[dim]) {
		bestBranch = current->getLeftChild();
		otherBranch = current->getRightChild();
	} else {
		bestBranch = current->getRightChild();
		otherBranch = current->getLeftChild();
	}

	// Recursive call
	Point* best = _search(p, bestBranch, depth+1, dist);

	// Handle the current node
	float currentDist = Point::distance(p, c);
	if (currentDist < *dist) {
		best = new Point(c);
		*dist = currentDist;
	}

	// Check if the hypersphere collides the hyperplane
	float planeDist = pow(p.coords[dim] - c.coords[dim], 2);
	if (planeDist < *dist) {
		float otherDist;
		Point* other = _search(p, otherBranch, depth + 1, &otherDist);
		if (otherDist < *dist) {
			*dist = otherDist;
			best = other;
		}
	}

	// Return the result
	return best;
}

void KDTree::print() {
	auto _print = [](BTNode<Point>* p) {
		p->getData().print();
		cout << endl;
	};

	tree->applyInOrder(_print, tree->root());
}

Point* KDTree::searchNearestNeighbour(Point p) {
	if (p.dimension != dimension) {
		throw std::logic_error("The dimensions are not the same.");
	}

	if (tree->empty()) {
		return NULL;
	} else {
		float dist;
		return _search(p, tree->root(), 0, &dist);
	}
}