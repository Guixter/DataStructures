#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Fabrique.h"

#define CARTONS_SIZE 10		// The number of pieces in every box
#define FILE_SIZE 1000		// The initial capacity of the queues
#define FRAME_TIME 30		// The time of every frame, in seconds

using namespace std;

// The constructor
Fabrique::Fabrique()
{
	srand(time(NULL));
	usinageTetes = new File<int>(FILE_SIZE);
	usinageJupes = new File<int>(FILE_SIZE);
	usinageAxes = new File<int>(FILE_SIZE);
	assemblageTetes = new File<int>(FILE_SIZE);
	assemblageJupes = new File<int>(FILE_SIZE);
	assemblageAxes = new File<int>(FILE_SIZE);
	pistons = new File<int>(FILE_SIZE);

	mt = new Machine(120, 1);
	mt->inputs[0] = usinageTetes;
	mt->output = assemblageTetes;
	mj = new Machine(180, 1);
	mj->inputs[0] = usinageJupes;
	mj->output = assemblageJupes;
	ma = new Machine(150, 1);
	ma->inputs[0] = usinageAxes;
	ma->output = assemblageAxes;
	mp = new Machine(60, 3);
	mp->inputs[0] = assemblageTetes;
	mp->inputs[1] = assemblageJupes;
	mp->inputs[2] = assemblageAxes;
	mp->output = pistons;
}

// The destructor
Fabrique::~Fabrique()
{
	delete usinageTetes, usinageJupes, usinageAxes;
	delete assemblageTetes, assemblageJupes, assemblageAxes;
	delete pistons;
	delete mt, mj, ma, mp;
}

// Launch the process
void Fabrique::launch() {
	int nbFrames = 0;
	while (pistons->taille() < 100) {
		updateCartons();
		updateMachine(mt);
		updateMachine(mj);
		updateMachine(ma);
		updateMachine(mp);
		nbFrames++;
	}

	int tps = nbFrames * FRAME_TIME;
	int heures = tps / 3600;
	tps -= heures * 3600;
	int minutes = tps / 60;
	tps -= minutes * 60;

	cout << "Les 100 pieces ont ete assemblees en " << heures << " heure(s) " << minutes << " minute(s) et " << tps << " seconde(s)." << endl;
	cout << "MT s'est brise " << mt->nbBroken << " fois." << endl;
	cout << "MJ s'est brise " << mj->nbBroken << " fois." << endl;
	cout << "MA s'est brise " << ma->nbBroken << " fois." << endl;
	cout << "MP s'est brise " << mp->nbBroken << " fois."<< endl;
}

// Sort the pieces of a box
void Fabrique::updateCartons() {
	for (int i = 0; i < CARTONS_SIZE; i++) {
		int random = rand() % 3;

		switch (random) {
		case 0:
			usinageTetes->enfiler(0);
			break;
		case 1:
			usinageJupes->enfiler(0);
			break;
		case 2:
			usinageAxes->enfiler(0);
			break;
		default:
			break;
		}
	}
}

// Update a machine
void Fabrique::updateMachine(Machine* machine) {
	if (machine->isBroken) {
		// The machine is broken : decrement the countdown until the machine is repaired
		machine->brokenCountdown -= FRAME_TIME;
		if (machine->brokenCountdown <= 0) {
			machine->isBroken = false;
		}
	} else {
		if (machine->isWorking) {
			// The machine is working on a piece
			machine->workingCountdown -= FRAME_TIME;
			if (machine->workingCountdown <= 0) {
				// The machine just ended its work
				machine->output->enfiler(0);
				machine->workingCountdown = machine->workTime;
				machine->isWorking = false;

				// Handle the breakdown
				int random = rand() % 100;
				if (random < 25) {
					machine->isBroken = true;
					machine->brokenCountdown = ((rand() % 6) + 5) * 60;
					machine->nbBroken++;
				}
			}
		} else {
			// If all the inputs are ready, we can start a new work
			bool start = true;
			for (int i = 0; i < machine->nbInputs; i++) {
				if (machine->inputs[i]->estVide()) {
					start = false;
					break;
				}
			}

			if (start) {
				// Remove an element in each input
				for (int i = 0; i < machine->nbInputs; i++) {
					machine->inputs[i]->defiler();
				}
				machine->isWorking = true;
			}
		}
	}
}
