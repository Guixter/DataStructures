#pragma once
#include <string>
#include <iostream>
#include "BinaryTree.h"

// An eye color
enum EyeColor { BLUE, GREEN, BROWN };

/*
* A person.
*/
struct Person {
public:
	std::string firstname;
	std::string lastname;
	int age;
	EyeColor eyeColor;

	friend bool operator==(const Person& l, const Person& r)
	{
		return (l.firstname == r.firstname && l.lastname == r.lastname);
	}

	friend std::ostream& operator << (std::ostream& f, Person p) {
		f << p.firstname << " " << p.lastname;
		return f;
	}
};


class FamilyTree
{
public:
	FamilyTree();
	~FamilyTree();

	void launch();

private:

	void menu();

	void AddMember();
	void ShowSizeHeight();
	void ShowDescendants();
	void ShowEyeColor();
	void ShowDescendantsEyeColor();
	void ShowAverageAge();


	Person GetPerson();
	BTNode<Person>* SearchPerson();


	BinaryTree<Person> *tree;
};
