#pragma once
#include <iostream>
#include <string>


using namespace std;

class Character {
public:
	void flip() { cout << "I know how to flip and I will flipping do it" << endl; }
	virtual void walk() { cout << "just in case they are too young to walk yet" << endl; }
	virtual void fly() = 0; //pure virtual function

	const int MAX_HEALTH = 50;
	int m_health = MAX_HEALTH;
	static const int MAX_INVENTORY = 10;
	string m_inventory[MAX_INVENTORY];
	string m_name;
	int m_attackVal;
	int m_spellVal;
	bool m_turn = false;
};

class Troll : public Character {
public:
	void fly() { cout << "Average Dooper is flapping and flying" << endl; }
	void attack(Character * t_enemy)
	{
		t_enemy->m_health -= m_attackVal;
	}

};

class Orc : public Character {
public:
	void barrelRoll() { cout << "rooooooolllllllllllinggggggg" << endl; }
	void walk() { cout << "Doopers have a really cool walk!" << endl; }
	void fly() { cout << "Dooper is flapping and flying" << endl; }

	void attack(Character  * t_enemy)
	{ 
		t_enemy->m_health -= m_attackVal;
	}
};