#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Fabrique.h"

#define CARTONS_SIZE 10
#define FILE_SIZE 100000
#define FRAME_TIME 30

using namespace std;


Fabrique::Fabrique()
{
	srand(time(NULL));
	usinageTetes = new File<int>(FILE_SIZE);
	usinageJupes = new File<int>(FILE_SIZE);
	usinageAxes = new File<int>(FILE_SIZE);
	assemblageTetes = new File<int>(FILE_SIZE);
	assemblageJupes = new File<int>(FILE_SIZE);
	assemblageAxes = new File<int>(FILE_SIZE);

	nbPistons = 0;
	countdowns = new int[8];
	for (int i = 0; i < 8; i++) {
		countdowns[i] = 0;
	}

	mtActive = false;
	mjActive = false;
	maActive = false;
	mpActive = false;
	mtBroken = false;
	mjBroken = false;
	maBroken = false;
	mpBroken = false;
}


Fabrique::~Fabrique()
{
	delete usinageTetes;
	delete usinageJupes;
	delete usinageAxes;
	delete assemblageTetes;
	delete assemblageJupes;
	delete assemblageAxes;
	delete[] countdowns;
}


void Fabrique::launch() {
	int nbFrames = 0;
	while (nbPistons < 100) {
		updateCartons();
		updateUsinage(mtActive, mtBroken, countdowns[0], countdowns[4], 120, usinageTetes, assemblageTetes, mtNbBroken);
		updateUsinage(mjActive, mjBroken, countdowns[1], countdowns[5], 180, usinageJupes, assemblageJupes, mjNbBroken);
		updateUsinage(maActive, maBroken, countdowns[2], countdowns[6], 150, usinageAxes, assemblageAxes, maNbBroken);
		updateAssemblage(mpActive, mpBroken, countdowns[3], countdowns[7], 60, assemblageTetes, assemblageJupes, assemblageAxes, mpNbBroken);
		nbFrames++;
	}

	int tps = nbFrames * FRAME_TIME;
	int heures = tps / 3600;
	tps -= heures * 3600;
	int minutes = tps / 60;
	tps -= minutes * 60;

	cout << "Les 100 pieces ont ete assemblees en " << heures << " heure(s) " << minutes << " minute(s) et " << tps << " seconde(s)." << endl;
	cout << "MT s'est brise " << mtNbBroken << " fois." << endl;
	cout << "MJ s'est brise " << mjNbBroken << " fois." << endl;
	cout << "MA s'est brise " << maNbBroken << " fois." << endl;
	cout << "MP s'est brise " << mpNbBroken << " fois."<< endl;
}

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

void Fabrique::updateUsinage(bool& active, bool& broken, int& countdown, int countdownBroken, int maxTime, File<int>* usinage, File<int>* assemblage, int& nbBroken) {
	if (broken) {
		// The machine is broken : decrement the countdown until the machine is repaired
		countdownBroken -= FRAME_TIME;
		if (countdownBroken <= 0) {
			broken = false;
		}
	} else {
		if (active) {
			// The machine is working on a piece
			countdown -= FRAME_TIME;
			if (countdown <= 0) {
				// The machine just ended its work
				assemblage->enfiler(0);
				countdown = maxTime;
				active = false;

				// Handle the breakdown
				int random = rand() % 100;
				if (random < 25) {
					broken = true;
					countdownBroken = ((rand() % 6) + 5) * 60;
					nbBroken++;
				}
			}
		}
		if (!active && !usinage->estVide()) {
			// Start working on a new piece
			usinage->defiler();
			active = true;
		}
	}
}

void Fabrique::updateAssemblage(bool& active, bool& broken, int& countdown, int countdownBroken, int maxTime, File<int>* tetes, File<int>* jupes, File<int>* axes, int& nbBroken) {
	if (broken) {
		// The machine is broken : decrement the countdown until the machine is repaired
		countdownBroken -= FRAME_TIME;
		if (countdownBroken <= 0) {
			broken = false;
		}
	}
	else {
		if (active) {
			// The machine is working on a piston
			countdown -= FRAME_TIME;
			if (countdown <= 0) {
				// The machine just ended its work
				nbPistons++;
				countdown = maxTime;
				active = false;

				// Handle the breakdown
				int random = rand() % 100;
				if (random < 25) {
					broken = true;
					countdownBroken = ((rand() % 6) + 5) * 60;
					nbBroken++;
				}
			}
		}
		if (!active && !tetes->estVide() && !jupes->estVide() && !axes->estVide()) {
			// Start working on a new piece
			tetes->defiler();
			jupes->defiler();
			axes->defiler();
			active = true;
		}
	}
}