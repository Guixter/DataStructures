#pragma once
#include <stdexcept>

template<typename T>
class File
{
public:
	// constructeurs et destructeurs
	File(int max = 100) throw (std::bad_alloc);
	File(const File &);
	~File();

	// modificateurs
	void enfiler(const T&);
	T defiler() throw (std::logic_error);

	// s�lecteurs
	int taille() const;
	bool estVide() const;
	bool estPleine() const;
	const T& premier() const; // t�te de la file
	const T& dernier() const; // queue de la file

	// surcharge d'op�rateurs
	const File<T>& operator = (const File<T>&) throw (std::bad_alloc);
	template <typename U> friend std::ostream& operator << (std::ostream& f, const File<U>& q);

private:
	T* tab;
	int tete;
	int queue;
	int tailleMax;
	int cpt;

	void _copier(T* tabS);
	void _redimensionner()  throw (std::bad_alloc);
};




// Constructeur
template<typename T>
File<T>::File(int max) {
	tab = new T[max];
	tete = 0;
	queue = 0;
	cpt = 0;
	tailleMax = max;
}

// Destructeur
template <typename T>
File<T>::~File() {
	delete[] tab;
}

// Constructeur de copie
template<typename T>
File<T>::File(const File & f) {
	tete = f.tete;
	queue = f.queue;
	tailleMax = f.tailleMax;
	cpt = f.cpt;
	_copier(f.tab);
}

// Enfiler
template <typename T>
void File<T>::enfiler(const T& e) {
	if (cpt == tailleMax) {
		_redimensionner();
	}
	tab[queue] = e;
	queue = (queue + 1) % tailleMax;
	cpt++;
}

template <typename T>
T File<T>::defiler() {
	if (cpt != 0) {
		T element = tab[tete];
		tete = (tete + 1) % tailleMax;
		cpt--;
		return element;
	} else {
		throw std::logic_error("Defiler : la file est vide !");
	}
}

template <typename T>
int File<T>::taille() const {
	return cpt;
}

template <typename T>
bool File<T>::estVide() const {
	return (cpt == 0);
}

template <typename T>
bool File<T>::estPleine() const {
	return (cpt == tailleMax);
}

template <typename T>
const T& File<T>::premier() const {
	return tab[tete];
}

template <typename T>
const T& File<T>::dernier() const {
	return tab[queue];
}

template <typename T>
const File<T>& File<T>::operator = (const File<T>& f) {

	if (this != &f) {

		if (tab != 0) {
			delete[] tab;
		}

		tete = f.tete;
		queue = f.queue;
		tailleMax = f.tailleMax;
		cpt = f.cpt;
		_copier(f.tab);
	}

	return *this;
}

template <typename T>
void File<T>::_copier(T* tabS) {
	tab = new T[tailleMax];
	for (int i = 0; i < tailleMax; i++) {
		tab[i] = tabS[i];
	}
}

template <typename T>
void File<T>::_redimensionner() {
	// Allocate a bigger table
	int nouvelleTaille = tailleMax * 2;
	T* newTab = new T[nouvelleTaille];

	// Copy the values in the new table
	int current = 0;
	while (current < cpt) {
		int index = (tete + current) % tailleMax;
		newTab[current] = tab[index];
		current++;
	}

	// Delete the old tab
	delete[] tab;

	// Update the attributes
	tab = newTab;
	tailleMax = nouvelleTaille;
	queue = cpt;
	tete = 0;
}

template <typename T>
std::ostream& operator << (std::ostream& f, const File<T>& file) {

	int current = 0;
	while (current < file.cpt) {
		int index = ((file.queue - 1) - current) % file.tailleMax;

		if (index < 0) {
			index += file.tailleMax;
		}
		f << file.tab[index] << " ";
		current ++;
	}

	return f;
}