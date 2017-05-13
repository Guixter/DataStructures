#pragma once
#include "vector"
#include <functional>

template <typename T>
class ArbreGenealogique {
public:

	ArbreGenealogique(T racine);
	~ArbreGenealogique();

	int taille() const;
	void ajouter(T parent, T elt);
	bool estVide() const;

	void appliquerPrefixe(std::function<void(T)> f);
	void appliquerSuffixe(std::function<void(T)> f);
	void appliquerInfixe(std::function<void(T)> f);

	/*
	void descendancePrefixe() const;
	void descendanceSuffixe() const;
	void descendanceInfixe() const;
	void ajouterMembre();
	void couleurYeux(int couleur);
	void couleurYeux(); ?
	int moyenneAge();
	*/

private:

	struct Noeud {
		T data;
		Noeud* filsGauche;
		Noeud* filsDroit;
		Noeud* parent;

		Noeud(T data, Noeud* parent = NULL, Noeud* filsGauche = NULL, Noeud* filsDroit = NULL) :
					data(data), parent(parent), filsGauche(filsGauche), filsDroit(filsDroit) {}
	};

	Noeud* root;


	template <typename U> U _recursif(std::function<U(Noeud*, U, U)> f, Noeud* n, U terminal) const;
	void _appliquerPrefixe(std::function<void(Noeud*)> f);
	void _appliquerSuffixe(std::function<void(Noeud*)> f);
	void _appliquerInfixe(std::function<void(Noeud*)> f);
};



template <typename T>
ArbreGenealogique<T>::ArbreGenealogique(T racine) {
	root = new Noeud(racine);
}

template <typename T>
ArbreGenealogique<T>::~ArbreGenealogique() {
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

	_appliquerSuffixe(_suppr);
}

template <typename T>
int ArbreGenealogique<T>::taille() const {
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
void ArbreGenealogique<T>::ajouter(T parent, T elt) {
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

	_appliquerSuffixe(_ajout);
}

template <typename T>
bool ArbreGenealogique<T>::estVide() const {
	return (root == NULL);
}

template <typename T>
void ArbreGenealogique<T>::appliquerPrefixe(std::function<void(T)> f) {
	auto _aux = [f](Noeud* n) {
		f(n->data);
	};

	_appliquerPrefixe(_aux);
}

template <typename T>
void ArbreGenealogique<T>::appliquerSuffixe(std::function<void(T)> f) {
	auto _aux = [](Noeud* n) {
		f(n->data);
	};

	_appliquerSuffixe(_aux);
}

template <typename T>
void ArbreGenealogique<T>::appliquerInfixe(std::function<void(T)> f) {
	auto _aux = [](Noeud* n) {
		f(n->data);
	};

	_appliquerInfixe(_aux);
}

///////////////////////////////////////

template <typename T>
void ArbreGenealogique<T>::_appliquerPrefixe(std::function<void(Noeud*)> f) {
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
	
	if (root != NULL) {
		_aux(root);
	}
}

template <typename T>
void ArbreGenealogique<T>::_appliquerSuffixe(std::function<void(Noeud*)> f) {
	
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

	
	if (root != NULL) {
		_aux(root);
	}
}

template <typename T>
void ArbreGenealogique<T>::_appliquerInfixe(std::function<void(Noeud*)> f) {
	std::function<void(Noeud*)> _aux;
	_aux = [&_aux, f](Noeud* n) {
		if (n->filsGauche != NULL) {
			_aux(n->filsGauche);
		}
		f(n);
		if (n->filsDroit != NULL) {
			_aux(n->filsDroit);
		}
	}

		if (root != NULL) {
			_aux(root);
		}
}

template<typename T>
template<typename U>
U ArbreGenealogique<T>::_recursif(std::function<U(Noeud*, U, U)> f, Noeud * n, U terminal) const {
	if (n == NULL) {
		return terminal;
	}

	U gaucheValue = _recursif(f, n->filsGauche, terminal);
	U droiteValue = _recursif(f, n->filsDroit, terminal);
	return f(n, gaucheValue, droiteValue);
}
