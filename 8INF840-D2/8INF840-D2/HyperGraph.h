#pragma once
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <string>

struct Page
{
	int id;
	int weight;
	std::string url;

	Page(int _id, int _weight, std::string _url) : id(_id), weight(_weight), url(_url) {
		
	}

	std::string getHost() {
		std::string start = url.substr(0, 7);
		std::string urlHostF = url;
		if (start.size() >= 7 && start == "http://") {
			urlHostF = urlHostF.substr(7, urlHostF.size() - 7);
		}
		start = urlHostF.substr(0, 4);
		if (start.size() >= 4 && start == "www.") {
			urlHostF = urlHostF.substr(4, urlHostF.size() - 4);
		}

		std::stringstream Line(urlHostF);
		std::getline(Line, urlHostF, '/');
		return urlHostF;
	}
};


template <typename T>
class HyperGraph
{
public:
	template <typename T> class Edge;
	template <typename T> class Node;
	HyperGraph();

	~HyperGraph();

	template <typename T>
	class Node {
	public:
		Node(T _content) : content(_content) {  };

		void addEdge(Edge<T>* edge) { edges.push_back(edge); };

		T getContent() { return content; };
		std::vector<Edge<T>*> getEdges() { return edges; };

	private:
		T content;
		std::vector<Edge<T>*> edges;
	};

	template <typename T>
	class Edge {
	public:
		Edge(Node<T>* _in, Node<T>* _out) : setOut(_out) { setIn = new std::unordered_set<Node<T>*>(); setIn->insert(_in); };
		void replaceSet(std::unordered_set<Node<T>*>* _set) { setIn->clear();  setIn = _set; };

	private:
		std::unordered_set<Node<T>*>* setIn;
		Node<T>* setOut;
		int id;
	};

private:
	Node<T>* racine;
};
