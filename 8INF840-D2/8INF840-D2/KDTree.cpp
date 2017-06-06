#include "KDTree.h"
#include <iostream>

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

void KDTree::print() {
	auto _print = [](BTNode<Point>* p) {
		cout << "(";
		for (int i = 0; i < p->getData().dimension - 1 ; i++) {
			cout << p->getData().coords[i] << ", ";
		}
		cout << p->getData().coords[p->getData().dimension-1];
		cout << ")" << endl;
	};

	tree->applyInOrder(_print, tree->root());
}

Point KDTree::searchNearestNeighbour(Point p) {
	return p;
}