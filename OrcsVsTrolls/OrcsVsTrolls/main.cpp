#include <iostream>
#include <time.h>
#include "Character.h"

void initialiseArrays(Character * t_pointer[], Character * t_pointerT[], int t_max, string t_name[][10]);
void startGame();
static void printStory();

int main(void)
{
	srand(static_cast<unsigned>(time(NULL)));

	static const int MAX_NPCS = 10;

	Character * orcs[MAX_NPCS];
	Character * trolls[MAX_NPCS];

	string names[][10]{ {"Makor","Gortwag", "Atulg", "Guarg", "Dul" ,"Urul", "Mug", "Yak", "Urim", "Olpac" },
	{"Olfin", "Bazur", "Orok", "Brag", "Bugak", "Borkul", "Lob", "Gat", "Yar", "Ghorbash" } };

	initialiseArrays(orcs, trolls, MAX_NPCS, names);

	startGame();

	cin.get();
}

void initialiseArrays(Character * t_pointerO[], Character * t_pointerT[], int t_max, string t_name[][10])
{
	for (int i = 0; i < t_max; i++)
	{
		t_pointerO[i] = new Orc;
		t_pointerT[i] = new Troll;
		t_pointerO[i]->m_attackVal = rand() % 10 + 1;
		t_pointerT[i]->m_attackVal = rand() % 10 + 1;
		t_pointerO[i]->m_name = t_name[0][i];
		t_pointerT[i]->m_name = t_name[1][i];
	}
}

void startGame()
{
	cout << "------------------Orcs vs Trolls--------------------" << endl;
	printStory();

}

void printStory()
{
	cout << "The sun rises over the bloodstained plains of Ushtera as a battle - hardened orc named Makor\nstorms out of his tent to the sight of fallen comerades.";
	cout << "The smell of blood fills the air as you pick\nup your battle axe and prepare to defent your home from the Trolls of the Breaca Empire.\n";
}
