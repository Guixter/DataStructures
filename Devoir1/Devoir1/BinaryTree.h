#pragma once
#include <functional>
#include <stdexcept>

template <typename T>
class BinaryTree {
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

		Node* getLeftChild() const {
			return this->leftChild;
		}

		Node* getRightChild() const {
			return this->rightChild;
		}

		void setData(T elt) {
			this->data = elt;
		}

		void setParent(Node* newParent) {
			this->parent = newParent;
		}

		void setLeftChild(Node* newChild) {
			this->leftChild = newChild;
		}

		void setRightChild(Node* newChild) {
			this->rightChild = newChild;
		}

		Node(T data) : data(data), parent(NULL), leftChild(NULL), rightChild(NULL) { }

		friend BinaryTree<T>;

	private:
		T data;
		Node* leftChild;
		Node* rightChild;
		Node* parent;
	};

	/////////////////////////////////

	enum INSERTION_TYPE { LEFT, RIGHT, ANY };

	/////////////////////////////////

	// Constructor
	BinaryTree();
	// Destructor
	~BinaryTree();


	// Know if the tree is empty
	bool empty() const;
	// Get the size of the tree
	int size() const;
	// Get the height of the tree
	int height() const;
	// Get the root of the tree
	Node* root() const;
	// Search a node in the tree
	Node* search(T elt) const;


	// Add a child to the parent node (or as the root if parent is null)
	Node* add(T childData, Node* parent, INSERTION_TYPE type = ANY) throw (std::logic_error);
	// Remove (and deallocate) a node (and all its descendants) from the tree
	void remove(Node* node);

	// Apply a function in each node, with the pre-order traversal
	void applyPreOrder(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the post-order traversal
	void applyPostOrder(std::function<void(Node* n)> f, Node* source);
	// Apply a function in each node, with the in-order traversal
	void applyInOrder(std::function<void(Node* n)> f, Node* source);


	// Apply a recursive function on the tree
	template <typename U> U recursive(std::function<U(Node const*, U, U)> f, Node* source, U terminal) const;

private:
	Node* _root;
};

template <typename T>
using BTNode = typename BinaryTree<T>::Node;

/////////////////////////////////

// Constructor
template <typename T>
BinaryTree<T>::BinaryTree() {
	_root = NULL;
}

// Destructor
template <typename T>
BinaryTree<T>::~BinaryTree() {
	remove(_root);
}

/////////////////////////////////

// Know if the tree is empty
template <typename T>
bool BinaryTree<T>::empty() const {
	return (_root == NULL);
}

// Get the size of the tree
template <typename T>
int BinaryTree<T>::size() const {
	std::function<int(Node const*, int, int)> _aux;
	_aux = [](Node const *n, int left, int right) {
		return left + right + 1;
	};

	return recursive(_aux, _root, 0);
}

// Get the height of the tree
template <typename T>
int BinaryTree<T>::height() const {
	std::function<int(Node const*, int, int)> _aux;
	_aux = [](Node const *n, int left, int right) {
		if (left >= right) {
			return left + 1;
		}
		else {
			return right + 1;
		}
	};

	return recursive(_aux, _root, 0);
}

// Get the root of the tree
template <typename T>
BTNode<T>* BinaryTree<T>::root() const {
	return _root;
}

// Search a node in the tree
template <typename T>
BTNode<T>* BinaryTree<T>::search(T elt) const {
	std::function<Node*(Node*)> _aux;
	_aux = [elt, &_aux](Node* n) {
		if (n == NULL) {
			return (Node *)NULL;
		}
		else {
			if (n->data == elt) {
				return n;
			}
			else {
				Node * child = _aux(n->leftChild);
				if (child != NULL) {
					return child;
				}
				else {
					return _aux(n->rightChild);
				}
			}
		}
	};

	return _aux(_root);

}

/////////////////////////////////

// Add a child to the parent node (or as the root if parent is null)
template <typename T>
BTNode<T>* BinaryTree<T>::add(T childData, Node* parent, INSERTION_TYPE type) {
	if (parent == NULL) {
		// Setting the root
		if (_root != NULL) {
			throw std::logic_error("The root is already set !");
		}

		_root = new Node(childData);
		return _root;
	}
	else {
		// Adding a node
		if (type == LEFT && parent->leftChild != NULL) {
			throw std::logic_error("The parent already has a left child !");
		}
		if (type == RIGHT && parent->rightChild != NULL) {
			throw std::logic_error("The parent already has a right child !");
		}
		if (type == ANY && parent->leftChild != NULL && parent->rightChild != NULL) {
			throw std::logic_error("The parent already has two children !");
		}

		Node* n = new Node(childData);
		n->parent = parent;

		if (type == LEFT || (type == ANY && parent->leftChild == NULL)) {
			parent->leftChild = n;
		}
		else {
			parent->rightChild = n;
		}

		return n;
	}
}

// Remove (and deallocate) a node (and all its descendants) from the tree
template <typename T>
void BinaryTree<T>::remove(Node* node) {
	auto _aux = [](Node* n) {
		if (n->parent != NULL) {
			if (n->parent->leftChild == n) {
				n->parent->leftChild = NULL;
			}
			else {
				n->parent->rightChild = NULL;
			}
			delete n;
		}
	};

	applyPostOrder(_aux, node);
}

/////////////////////////////////

// Apply a function in each node, with the pre-order traversal
template <typename T>
void BinaryTree<T>::applyPreOrder(std::function<void(Node* n)> f, Node* source) {
	std::function<void(Node*)> _aux;
	_aux = [&_aux, f](Node* n) {
		if (n != NULL) {
			f(n);
			_aux(n->leftChild);
			_aux(n->rightChild);
		}
	};

	_aux(source);
}

// Apply a function in each node, with the post-order traversal
template <typename T>
void BinaryTree<T>::applyPostOrder(std::function<void(Node* n)> f, Node* source) {
	std::function<void(Node*)> _aux;
	_aux = [&_aux, f](Node* n) {
		if (n != NULL) {
			_aux(n->leftChild);
			_aux(n->rightChild);
			f(n);
		}
	};

	_aux(source);
}

// Apply a function in each node, with the in-order traversal
template <typename T>
void BinaryTree<T>::applyInOrder(std::function<void(Node* n)> f, Node* source) {
	std::function<void(Node*)> _aux;
	_aux = [&_aux, f](Node* n) {
		if (n != NULL) {
			_aux(n->leftChild);
			f(n);
			_aux(n->rightChild);
		}
	};

	_aux(source);
}

/////////////////////////////////

// Apply a recursive function on the tree
template <typename T>
template <typename U>
U BinaryTree<T>::recursive(std::function<U(Node const*, U, U)> f, Node* source, U terminal) const {
	if (source == NULL) {
		return terminal;
	}

	U leftValue = recursive(f, source->leftChild, terminal);
	U rightValue = recursive(f, source->rightChild, terminal);
	return f(source, leftValue, rightValue);
}