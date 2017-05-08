#pragma once
#include "File.h"

/*
 * A machine, which can work on inputs to make an output.
 */
struct Machine {
	int nbInputs;
	File<int>** inputs;
	File<int>* output;
	bool isWorking;
	bool isBroken;
	int nbBroken;

	int workTime;

	int workingCountdown;
	int brokenCountdown;

	Machine(int countdown, int inputs) :
											isWorking(false), isBroken(false), nbBroken(0),
											workTime(countdown), workingCountdown(0), brokenCountdown(0),
											nbInputs(inputs), output(NULL)
	{
		this->inputs = new File<int>*[inputs];
	}

	~Machine() {
		delete[] inputs;
	}
};

/*
 * A factory, which contains some queues and some machines to make a product.
 */
class Fabrique
{
public:
	Fabrique();
	~Fabrique();

	void launch();

private:

	// méthodes
	void updateCartons();
	void updateMachine(Machine* machine);

	// Les machines
	Machine *mt, *mj, *ma, *mp;

	// Files d'usinage
	File<int> *usinageTetes, *usinageJupes, *usinageAxes;
	// Files d'assemblage
	File<int> *assemblageTetes, *assemblageJupes, *assemblageAxes;
	// File des pistons usinés et assemblés
	File<int> *pistons;
};

