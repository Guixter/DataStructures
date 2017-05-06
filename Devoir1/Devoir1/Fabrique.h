#pragma once
#include "File.h"

class Fabrique
{
public:
	Fabrique();
	~Fabrique();

	void launch();

private:

	// méthodes
	void updateCartons();
	void updateUsinage(bool& active, bool& broken, int& countdown, int countdownBroken, int maxTime, File<int>* usinage, File<int>* assemblage, int& nbBroken);
	void updateAssemblage(bool& active, bool& broken, int& countdown, int countdownBroken, int maxTime, File<int>* tetes, File<int>* jupes, File<int>* axes, int& nbBroken);

	File<int> *usinageTetes, *usinageJupes, *usinageAxes;
	File<int> *assemblageTetes, *assemblageJupes, *assemblageAxes;

	int nbPistons;
	int* countdowns;

	bool mtActive, mjActive, maActive, mpActive;
	bool mtBroken, mjBroken, maBroken, mpBroken;

	int mtNbBroken, mjNbBroken, maNbBroken, mpNbBroken;
};

