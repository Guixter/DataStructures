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

	std::string _trim(const std::string& str)
	{
		size_t start = str.find_first_not_of(" \n\r\t");
		size_t until = str.find_last_not_of(" \n\r\t");
		std::string::const_iterator i = start == std::string::npos ? str.begin() : str.begin() + start;
		std::string::const_iterator x = until == std::string::npos ? str.end() : str.begin() + until + 1;
		return std::string(i, x);
	}

	std::string getDomain() {
		std::string x = _trim(url);
		int offset = 0;
		offset = offset == 0 && x.compare(0, 8, "https://") == 0 ? 8 : offset;
		offset = offset == 0 && x.compare(0, 7, "http://") == 0 ? 7 : offset;
		int pos1 = x.find_first_of('/', offset + 1);

		std::string domain = std::string(x.begin() + offset, pos1 != std::string::npos ? x.begin() + pos1 : x.end());
		int pos3 = domain.find(":");
		domain = domain.substr(0, pos3 != std::string::npos ? pos3 : domain.length());
		return domain;
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

	HyperGraph(Node* _racine, std::vector<Bloc> _blocs) : blocs(_blocs) , racine(_racine) { };

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

	class Bloc {
	public:
		void addVertex(Node &node) { vertex.push_back(node); }
		void addEdge(Edge &edge) { out_edges.push_back(edge); }
		vector<Node*> getVertex() { return vertex; }
		vector<Edge*> getEdge() { return out_edges; }


	private:

		std::vector<Node*> vertex;
		std::vector<Edge*> out_edges;

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

	std::vector<Bloc> getBlocs() { return blocs; }
private:
	Node* racine;
	std::vector<Bloc> blocs;
};

typedef HyperGraph<Page>::Edge H_Edge;
typedef HyperGraph<Page>::Node H_Node;