#pragma once
#include "Graph.h"
#include <cmath>

struct Tower {
public:
	int number;
	float x, y;

	bool operator==(Tower t) {
		return (number == t.number);
	}

	static float distance(Tower t1, Tower t2) {
		return sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2));
	}
};

class Zombie
{
public:
	Zombie();
	~Zombie();

	void launch();

private:
	Graph<Tower> *g;

	void loadFile();
	void compute();
};

