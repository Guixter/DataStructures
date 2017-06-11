#pragma once
#include <functional>
#include <stdexcept>
#include <vector>
#include <stack>
#include <queue>
#include <limits>

template <typename T>
class Graph {
public:
	static float MAX_FLOAT;

	class Node;

	// The edge class
	class Edge {
	public:
		Node* source;
		Node* target;
		float weight;

		Edge(Node* source, Node* target, float weight) : source(source), target(target), weight(weight) { }

		friend class Graph<T>;
	};

	// The node class, containing the data
	class Node {
	public:
		~Node() {
			for (int i = 0; i < edges.size(); i++) {
				delete edges[edges.size() - i - 1];
				edges.erase(edges.begin() + (edges.size() - 1));
			}
		}

		T getData() const {
			return this->data;
		}

		int getNbEdges() const {
			return edges.size();
		}

		Edge* getEdge(int index) const throw (std::logic_error) {
			if (index >= edges.size()) {
				throw std::logic_error("Bad index.");
			}

			return edges[index];
		}

		void setData(T elt) {
			this->data = elt;
		}

		void addEdge(Edge* edge) {
			edges.push_back(edge);
		}

		float getDistance() const {
			return distance;
		}

		Edge* getLastEdge() const {
			return lastEdge;
		}

		Node(T data) : data(data), edges(), tag(false), distance(MAX_FLOAT), lastEdge(NULL) { }

		friend class Graph<T>;

	private:
		T data;
		std::vector<Edge*> edges;
		bool tag;

		// Some shortest path data
		float distance;
		Edge* lastEdge;
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
	Edge* addEdge(Node* source, Node* target, float weight = 1);

	// Apply a function in each node, with the BFS traversal
	void applyBreadthFirst(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the DFS traversal
	void applyDepthFirst(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node
	void applyNodes(std::function<void(Node* n)> f);

	// Apply the Dijkstra algorithm
	void dijkstra(Node* source);

private:
	std::vector<Node*> nodes;

	void _resetTags();
};

template <typename T>
using GNode = typename Graph<T>::Node;

template <typename T>
using GEdge = typename Graph<T>::Edge;

template <typename T>
float Graph<T>::MAX_FLOAT = std::numeric_limits<float>::max();

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
	nodes.push_back(n);
	return n;
}

// Add an edge between two nodes
template <typename T>
GEdge<T>* Graph<T>::addEdge(Node* source, Node* target, float weight) {
	Edge* e = new Edge(source, target, weight);
	source->addEdge(e);
	return e;
}

/////////////////////////////////

// Apply a function in each node, with the depth-first traversal
template <typename T>
void Graph<T>::applyDepthFirst(std::function<void(Node* n)> f, Node* source) {
	_resetTags();

	std::stack<Node*> *stack = new std::stack<Node*>();
	stack->push(source);
	while (!stack->empty()) {
		Node *n = stack->top();
		stack->pop();
		if (n != NULL && !(n->tag)) {
			n->tag = true;
			f(n);
			for (int i = 0; i < n->getNbEdges(); i++) {
				stack->push(n->getEdge(i)->target);
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
		Node *n = queue->front();
		queue->pop();
		if (n != NULL && !(n->tag)) {
			n->tag = true;
			f(n);
			for (int i = 0; i < n->getNbEdges(); i++) {
				queue->push(n->getEdge(i)->target);
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

// Apply a function in each node
template <typename T>
void Graph<T>::applyNodes(std::function<void(Node* n)> f) {
	for (int i = 0; i < nodes.size(); i++) {
		f(nodes[i]);
	}
}

/////////////////////////////////

// Apply Dijkstra
template <typename T>
void Graph<T>::dijkstra(Node* source) {
	// Initialization
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->distance = MAX_FLOAT;
	}
	source->distance = 0;

	std::vector<Node*> v(nodes);
	while (v.size() > 0) {
		// Find the minimum
		int index = 0;
		Node* n = v[index];
		for (int i = 1; i < v.size(); i++) {
			if (v[i]->distance < n->distance) {
				index = i;
				n = v[index];
			}
		}

		// Remove it from the list
		v.erase(v.begin() + index);

		// For all the neighbours
		for (int i = 0; i < n->getNbEdges(); i++) {
			// Update the distance of the neighbour
			Edge* e = n->getEdge(i);
			Node* neighbour = e->target;
			if (neighbour->distance > (n->distance + e->weight)) {
				neighbour->distance = (n->distance + e->weight);
				neighbour->lastEdge = e;
			}
		}
	}
}