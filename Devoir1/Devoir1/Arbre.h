#pragma once

template<typename E> 
class Arbre { 
public:
private: 
	class Noeud {
	public: 
		E data; 
		Noeud *gauche; 
		Noeud *droite; 
		int card;
		int hauteur;
		Noeud( const E& d ): gauche(0), data(d) ,droite(0), hauteur(0) { } 
	};
	
	Noeud * racine; 
	int cpt; 
};