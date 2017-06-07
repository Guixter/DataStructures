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

	std::string getDomain() {
		std::string urlHostF = "";
		return urlHostF;
	}
};


template <typename T>
class HyperGraph
{
public:
	class Edge;
	class Node;

	HyperGraph();

	HyperGraph(Node* _racine) : racine(_racine) { };

	~HyperGraph();

	class Node {
	public:
		Node(T _content) : content(_content) {  };

		void addEdge(Edge* edge) { edges.push_back(edge); };
		std::vector<Edge*> getEdges() { return edges; };

		T getContent() { return content; };
		void setContent(T _content) { content = _content; };

	private:
		T content;
		std::vector<Edge*> edges;
	};

	class Edge {
	public:
		Edge(Node* _in, Node* _out) : setIn(_in), setOut(_out) { /* setIn = new std::unordered_set<Node<T>*>(); setIn->insert(_in); */};
		Node* getOut() { return setOut; };

	private:
		Node* setIn;
		Node* setOut;
		int id;
	};

private:
	Node* racine;
};

typedef HyperGraph<Page>::Edge H_Edge;
typedef HyperGraph<Page>::Node H_Node;