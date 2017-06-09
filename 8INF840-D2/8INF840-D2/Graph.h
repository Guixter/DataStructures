#pragma once
#include <functional>
#include <stdexcept>
#include <vector>
#include <stack>
#include <queue>

template <typename T>
class Graph {
public:

	// The node class, containing the data
	class Node {
	public:
		T getData() const {
			return this->data;
		}

		Node* getParent() const {
			return this->parent;
		}

		int getNbChildren() const {
			return children.size();
		}

		Node* getChild(int index) const throw (std::logic_error) {
			if (index >= children.size()) {
				throw std::logic_error("Bad index.");
			}

			return children[index];
		}

		void setData(T elt) {
			this->data = elt;
		}

		void setParent(Node* newParent) {
			this->parent = newParent;
		}

		void addChild(Node* child) {
			children.insert(child);
		}

		Node(T data) : data(data), parent(NULL), children() { }

		friend Graph<T>;

	private:
		T data;
		std::vector<Node*> children;
		Node* parent;
		bool tag;
	};

	/////////////////////////////////

	// Constructor
	Graph();
	// Destructor
	~Graph();

	// Know if the graph is empty
	bool empty() const;
	// Get the size of the graph
	int nbNodes() const;
	// Search a node in the graph
	Node* search(T elt) const;

	// Add a node to the graph
	Node* addNode(T data);
	// Add an edge between two nodes of the graph
	void addEdge(Node* n1, Node* n2);

	// Apply a function in each node, with the BFS traversal
	void applyBreadthFirst(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the DFS traversal
	void applyDepthFirst(std::function<void(Node* n)> f, Node* source);

private:
	std::vector<Node*> nodes;

	void _resetTags();
};

template <typename T>
using GNode = typename Graph<T>::Node;

/////////////////////////////////

// Constructor
template <typename T>
Graph<T>::Graph() : nodes() { }

// Destructor
template <typename T>
Graph<T>::~Graph() {
	for (int i = 0; i < nodes.size(); i++) {
		delete nodes[nodes.size() - i - 1];
		nodes.erase(nodes.begin() + (nodes.size() - 1));
	}
}

/////////////////////////////////

// Know if the graph is empty
template <typename T>
bool Graph<T>::empty() const {
	return (nodes.size() == 0);
}

// Get the number of nodes in the graph
template <typename T>
int Graph<T>::nbNodes() const {
	return nodes.size();
}

// Search a node in the graph
template <typename T>
GNode<T>* Graph<T>::search(T elt) const {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->getData() == elt) {
			return nodes[i];
		}
	}

	return NULL;
}

/////////////////////////////////

// Add a node to the graph
template <typename T>
GNode<T>* Graph<T>::addNode(T data) {
	Node* n = new Node(data);
	nodes.insert(data);
	return n;
}

// Add an edge between two nodes
template <typename T>
void Graph<T>::addEdge(Node* n1, Node* n2) {
	n1->children.add(n2);
	n2->children.add(n1);
}

/////////////////////////////////

// Apply a function in each node, with the depth-first traversal
template <typename T>
void Graph<T>::applyDepthFirst(std::function<void(Node* n)> f, Node* source) {
	_resetTags();

	std::stack<Node*> *stack = new std::stack<Node*>();
	stack->push(source);
	while (!stack->empty()) {
		Node *n = stack->pop();
		if (n != NULL) {
			f(n);
			for (int i = 0; i < n->nbChildren(); i++) {
				if (!(n->tag)) {
					stack->push(n->getChild(i));
					n->tag = true;
				}
			}
		}
	}
}

// Apply a function in each node, with the breadth-first traversal
template <typename T>
void Graph<T>::applyBreadthFirst(std::function<void(Node* n)> f, Node* source) {
	_resetTags();

	std::queue<Node*> *queue = new std::queue<Node*>();
	queue->push(source);
	while (!queue->empty()) {
		Node *n = queue->pop();
		if (n != NULL) {
			f(n);
			for (int i = 0; i < n->nbChildren(); i++) {
				if (!(n->tag)) {
					queue->push(n->getChild(i));
					n->tag = true;
				}
			}
		}
	}
}

// Reset the tags of the graph
template <typename T>
void Graph<T>::_resetTags() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->tag = false;
	}
}