#pragma once
#include "vector"
#include <functional>

template <typename T>
class Arbre {
public:

	Arbre(T racine);
	~Arbre();

	int taille() const;
	int hauteur() const;
	void ajouter(T parent, T elt);
	bool estVide() const;

	void appliquerPrefixe(std::function<void(T)> f);
	void appliquerSuffixe(std::function<void(T)> f);
	void appliquerInfixe(std::function<void(T)> f);
	void appliquerPrefixe(std::function<void(T)> f, T t);
	void appliquerSuffixe(std::function<void(T)> f, T t);
	void appliquerInfixe(std::function<void(T)> f, T t);

private:

	struct Noeud {
		T data;
		Noeud* filsGauche;
		Noeud* filsDroit;
		Noeud* parent;

		Noeud(T data, Noeud* parent = NULL, Noeud* filsGauche = NULL, Noeud* filsDroit = NULL) :
					data(data), parent(parent), filsGauche(filsGauche), filsDroit(filsDroit) { }
	};

	Noeud* root;


	template <typename U> U _recursif(std::function<U(Noeud*, U, U)> f, Noeud* n, U terminal) const;
	void _appliquerPrefixe(std::function<void(Noeud*)> f, Noeud* n);
	void _appliquerSuffixe(std::function<void(Noeud*)> f, Noeud* n);
	void _appliquerInfixe(std::function<void(Noeud*)> f, Noeud* n);
};



template <typename T>
Arbre<T>::Arbre(T racine) {
	root = new Noeud(racine);
}

template <typename T>
Arbre<T>::~Arbre() {
	auto _suppr = [](Noeud* n) {
		if (n->parent != NULL) {
			if (n->parent->filsGauche == n) {
				n->parent->filsGauche = NULL;
			} else {
				n->parent->filsDroit = NULL;
			}
		}
		delete n;
	};

	_appliquerSuffixe(_suppr, root);
}

template <typename T>
int Arbre<T>::hauteur() const {
	std::function<int(Noeud*, int, int)> _aux;
	_aux = [](Noeud* n, int gauche, int droite) {
		if (gauche >= droite) {
			return gauche + 1;
		} else {
			return droite + 1;
		}
	};

	return _recursif(_aux, root, 0);
}

template <typename T>
int Arbre<T>::taille() const {
	std::function<int(Noeud*, int, int)> _aux;
	_aux = [](Noeud* n, int gauche, int droite) {
		return gauche + droite + 1;
	};

	return _recursif(_aux, root, 0);
}

template <typename T>
void Arbre<T>::ajouter(T parent, T elt) {
	auto _ajout = [&parent, &elt](Noeud* n) {
		if (n->data == parent) {
			if (n->filsGauche == NULL) {
				Noeud* nouveau = new Noeud(elt, n);
				n->filsGauche = nouveau;
			} else if (n->filsDroit == NULL) {
				Noeud* nouveau = new Noeud(elt, n);
				n->filsDroit = nouveau;
			}
		}
	};

	_appliquerSuffixe(_ajout, root);
}

template <typename T>
bool Arbre<T>::estVide() const {
	return (root == NULL);
}

template <typename T>
void Arbre<T>::appliquerPrefixe(std::function<void(T)> f) {
	auto _aux = [f](Noeud* n) {
		f(n->data);
	};

	_appliquerPrefixe(_aux, root);
}

template <typename T>
void Arbre<T>::appliquerSuffixe(std::function<void(T)> f) {
	auto _aux = [f](Noeud* n) {
		f(n->data);
	};

	_appliquerSuffixe(_aux, root);
}

template <typename T>
void Arbre<T>::appliquerInfixe(std::function<void(T)> f) {
	auto _aux = [f](Noeud* n) {
		f(n->data);
	};

	_appliquerInfixe(_aux, root);
}

template <typename T>
void Arbre<T>::appliquerPrefixe(std::function<void(T)> f, T t) {
	// Trouver le noeud correspondant
	Noeud* node = NULL;
	auto _aux = [&node, t](Noeud* n) {
		if (n != NULL && n->data == t) {
			node = n;
		}
	};
	_appliquerPrefixe(_aux, root);

	// Appliquer à partir de ce noeud
	auto _aux2 = [f](Noeud* n) {
		f(n->data);
	};
	_appliquerPrefixe(_aux2, node);
}

template <typename T>
void Arbre<T>::appliquerSuffixe(std::function<void(T)> f, T t) {
	// Trouver le noeud correspondant
	Noeud* node = NULL;
	auto _aux = [&node, t](Noeud* n) {
		if (n != NULL && n->data == t) {
			node = n;
		}
	};
	_appliquerSuffixe(_aux, root);

	// Appliquer à partir de ce noeud
	auto _aux2 = [f](Noeud* n) {
		f(n->data);
	};
	_appliquerSuffixe(_aux2, node);
}

template <typename T>
void Arbre<T>::appliquerInfixe(std::function<void(T)> f, T t) {
	// Trouver le noeud correspondant
	Noeud* node = NULL;
	auto _aux = [&node, t](Noeud* n) {
		if (n != NULL && n->data == t) {
			node = n;
		}
	};
	_appliquerInfixe(_aux, root);

	// Appliquer à partir de ce noeud
	auto _aux2 = [f](Noeud* n) {
		f(n->data);
	};
	_appliquerInfixe(_aux2, node);
}

///////////////////////////////////////

template <typename T>
void Arbre<T>::_appliquerPrefixe(std::function<void(Noeud*)> f, Noeud* n) {
	std::function<void(Noeud*)> _aux;
	_aux = [&_aux, f](Noeud* n) {
		f(n);
		if (n->filsGauche != NULL) {
			_aux(n->filsGauche);
		}
		if (n->filsDroit != NULL) {
			_aux(n->filsDroit);
		}
	};
	
	if (n != NULL) {
		_aux(n);
	}
}

template <typename T>
void Arbre<T>::_appliquerSuffixe(std::function<void(Noeud*)> f, Noeud* n) {
	
	std::function<void(Noeud*)> _aux;
	_aux = [&_aux, f](Noeud* n) {
		if (n->filsGauche != NULL) {
			_aux(n->filsGauche);
		}
		if (n->filsDroit != NULL) {
			_aux(n->filsDroit);
		}
		f(n);
	};

	
	if (n != NULL) {
		_aux(n);
	}
}

template <typename T>
void Arbre<T>::_appliquerInfixe(std::function<void(Noeud*)> f, Noeud* n) {
	std::function<void(Noeud*)> _aux;
	_aux = [&_aux, f](Noeud* n) {
		if (n->filsGauche != NULL) {
			_aux(n->filsGauche);
		}
		f(n);
		if (n->filsDroit != NULL) {
			_aux(n->filsDroit);
		}
	};

	if (n != NULL) {
		_aux(n);
	}
}

template<typename T>
template<typename U>
U Arbre<T>::_recursif(std::function<U(Noeud*, U, U)> f, Noeud * n, U terminal) const {
	if (n == NULL) {
		return terminal;
	}

	U gaucheValue = _recursif(f, n->filsGauche, terminal);
	U droiteValue = _recursif(f, n->filsDroit, terminal);
	return f(n, gaucheValue, droiteValue);
}
