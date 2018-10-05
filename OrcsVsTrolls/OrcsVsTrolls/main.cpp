#include <iostream>
#include <time.h>
#include "Character.h"


void initialiseArrays(Orc * t_pointer[], Troll * t_pointerT[], int t_max, string t_name[][10]);
void startGame(const int t_max , Orc * t_pointerO[], Troll * t_pointerT[]);
static const void printStory();
void printOptions( const int  t_max, Orc * t_pointerO[], Troll * t_pointerT[]);

int main(void)
{
	srand(static_cast<unsigned>(time(NULL)));

	static const int MAX_NPCS = 10;

	Orc * orcs[MAX_NPCS];
	Troll * trolls[MAX_NPCS];

	string names[][10]{ {"Makor","Gortwag", "Atulg", "Guarg", "Dul" ,"Urul", "Mug", "Yak", "Urim", "Olpac" },
	{"Olfin", "Bazur", "Orok", "Brag", "Bugak", "Borkul", "Lob", "Gat", "Yar", "Ghorbash" } };

	initialiseArrays(orcs, trolls, MAX_NPCS, names);

	startGame(MAX_NPCS, orcs, trolls);

	cin.get();
}

void initialiseArrays(Orc * t_pointerO[], Troll * t_pointerT[], int t_max, string t_name[][10])
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

void startGame(const int t_max, Orc * t_pointerO[], Troll * t_pointerT[])
{
	cout << "------------------Orcs vs Trolls--------------------\n" << endl;
	printStory();
	printOptions(t_max, t_pointerO, t_pointerT);
}

static void const printStory()
{
	cout << "The sun rises over the bloodstained plains of Ushtera as a battle - hardened orc named Makor\nstorms out of his tent to the sight of fallen comerades.";
	cout << "The smell of blood fills the air as you pick\nup your battle axe and prepare to defend your home from the Trolls of the Breaca Empire.\n\n";

	cout << "-------------- Battle Start! -------------------\n";
}

void printOptions(const int t_max, Orc * t_pointerO[], Troll * t_pointerT[])
{
	int choice = 0;

	for (int i = 0; i < t_max; i++)
	{
		cout << "Enemy Troll " + t_pointerT[i]->m_name + " Approaches! " << endl << endl;

		t_pointerO[0]->m_turn = true;
		t_pointerT[i]->m_turn = false;

		while (t_pointerT[i]->m_health > 0)
		{
			if (t_pointerO[0]->m_turn)
			{
				cout << "\nWhat will you do?\n\n1.Attack                          3.Defend\n2.Spells                          4.Inventory\n";
				cin >> choice;
			}
			switch (choice)
			{
			case 1: // attack
				if (t_pointerO[0]->m_turn == true) // if orc's turn
				{
					cout << "You attacked the Troll!\n" << t_pointerT[i]->m_name << " took " << t_pointerO[0]->m_attackVal  << " damage\n";
					t_pointerO[0]->attack(t_pointerT[i]);
					t_pointerO[0]->m_attackVal = rand() % 10 + 1;
					t_pointerO[0]->m_turn = false;
					t_pointerT[i]->m_turn = true;
				}
				else // if troll's turn
				{
					cout << "\nThe troll Attacked!\nYou took "<< t_pointerT[i]->m_attackVal << " damage\n";
					t_pointerT[i]->attack(t_pointerO[0]);
					t_pointerO[0]->m_turn = true;
					t_pointerT[i]->m_turn = false;
				}
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
		}
	}
}
