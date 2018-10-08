#include <iostream>
#include <time.h>
#include "Character.h"


void initialiseArrays(Orc * t_pointer[], Troll * t_pointerT[], int t_max, string t_name[][10]);
void startGame(const int t_max , Orc * t_pointerO[], Troll * t_pointerT[]);
static const void printStory();
void printOptions( const int  t_max, Orc * t_pointerO[], Troll * t_pointerT[]);
void const printInventory(Orc * t_orc);
void spellList(Orc * t_orc, Troll * t_troll);

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
		t_pointerO[i]->m_spellVal = rand() % 10 + 5;
		t_pointerT[i]->m_spellVal = rand() % 10 + 5;
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
	int playerChoice = 0;
	int enemyChoice = 0;
	string loot[t_pointerO[0]->MAX_INVENTORY]{ "Fire Runestone","Assassin's Blade", "Bow of the Aedra", "Briar Heart", "Water hag Tooth", "Meteorite Ingot", "Gold Ruby Ring", "Silver Amber Necklace", "Chillrend", "Ayleid Crown of Lindai" };

	for (int i = 0; i < t_max; i++)
	{
		cout << "Enemy Troll " + t_pointerT[i]->m_name + " Approaches! " << endl << endl;

		t_pointerO[0]->m_turn = true;
		t_pointerT[i]->m_turn = false;

		while (t_pointerT[i]->m_health > 0)
		{
			if (t_pointerO[0]->m_turn) // if orc's turn
			{
				cout << "----------------------------------------------------------------------" << endl;
				if (t_pointerO[0]->m_turn)
				{
					cout << "\nWhat will you do?\n\n1.Attack                          3.Defend\n2.Spells                          4.Inventory\n";
					cin >> playerChoice;
				}
				switch (playerChoice)
				{
				case 1: // attack
					cout << "You attacked the Troll!\n" << t_pointerT[i]->m_name << " took " << t_pointerO[0]->m_attackVal << " damage\n";
					t_pointerO[0]->attack(t_pointerT[i]);
					t_pointerO[0]->m_attackVal = rand() % 10 + 1;
					t_pointerO[0]->m_turn = false;
					t_pointerT[i]->m_turn = true;
					break;

				case 2:
					spellList(t_pointerO[0], t_pointerT[i]);
					break;

				case 3:
					cout << "You raise your shield and take a defensive stance" << endl;
					t_pointerT[i]->m_spellVal = t_pointerT[i]->m_spellVal / 2;
					t_pointerT[i]->m_attackVal = t_pointerT[i]->m_attackVal / 2;
					t_pointerO[0]->m_turn = false;
					t_pointerT[i]->m_turn = true;
					break;

				case 4:
					printInventory(t_pointerO[0]);
					break;

				default:
					cout << "You find yourself unable to move with fear!" << endl;
					t_pointerO[0]->m_turn = false;
					t_pointerT[i]->m_turn = true;
					break;
				}

			}

			if (t_pointerT[i]->m_turn) // if enemy's turn
			{
				cout << "----------------------------------------------------------------------" << endl;
				enemyChoice = rand() % 2 + 1;
				switch (enemyChoice)
				{
				case 1:
					cout << "The troll raises its club and attacks!\nYou took " << t_pointerT[i]->m_attackVal << "  damage" << endl;
					t_pointerT[i]->attack(t_pointerO[0]);
					t_pointerT[i]->m_attackVal = rand() % 10 + 1;
					t_pointerT[i]->m_turn = false;
					t_pointerO[0]->m_turn = true;
					break;

				case 2:
					cout << "Troll casts Thunder!\nYou took " << t_pointerT[i]->m_spellVal << " damage\n";
					t_pointerT[i]->attack(t_pointerO[0]);
					t_pointerT[i]->m_spellVal = rand() % 10 + 5;
					t_pointerO[0]->m_turn = true;
					t_pointerT[i]->m_turn = false;
					break;
				default:
					cout << "The troll flails about wildly!" << endl;
					t_pointerO[0]->m_turn = true;
					t_pointerT[i]->m_turn = false;
					break;
				}
			}
		}

		//when troll is dead
		cout << "------------------------------------------------------" << endl;
		cout << t_pointerT[i]->m_name << " falls to the ground!" << endl;
		cout << "You pick up " << loot[i] << endl;
		t_pointerO[0]->m_inventory[i] = loot[i];
		cout << "------------------------------------------------------" << endl;
	}
}

void const printInventory(Orc * t_orc)
{
	cout << "-----------------Current Inventory-------------------" << endl;
	for (int i = 0; i < t_orc->MAX_INVENTORY; i++)
	{
		cout << t_orc->m_inventory[i] << endl;
	}
}

void spellList(Orc * t_orc, Troll * t_troll)
{
	int playerChoice;
	cout << "\nWhat spell will you cast?\n\n1.Fireball                          3.Thunder\n2.Heal                          4.View Health\n";
	cin >> playerChoice;
	switch (playerChoice)
	{
	case 1:
		cout << "You threw a fireball at the Troll!\n" << t_troll->m_name << " took " << t_orc->m_spellVal << " damage\n";
		t_orc->attack(t_troll);
		t_orc->m_spellVal = rand() % 10 + 5;
		t_orc->m_turn = false;
		t_troll->m_turn = true;
		break;
	case 2:
		t_orc->m_spellVal = rand() % 30 + 20;
		cout << "A blue glow surrounds you! You heal " << t_orc->m_spellVal << " health" << endl;
		t_orc->m_health = t_orc->m_health + t_orc->m_spellVal;
		if (t_orc->m_health > 100)
		{
			t_orc->m_health = t_orc->MAX_HEALTH;
		}
		t_orc->m_spellVal = rand() % 10 + 5;
		t_orc->m_turn = false;
		t_troll->m_turn = true;
		break;
	case 3:
		cout << "You fire a bolt of lightning at the troll!\n" << t_troll->m_name << " took " << t_orc->m_spellVal << " damage\n";
		t_orc->attack(t_troll);
		t_orc->m_spellVal = rand() % 10 + 5;
		t_orc->m_turn = false;
		t_troll->m_turn = true;
		break;
	case 4:
		cout << "Current health: " << t_orc->m_health << endl;
		break;
	default:
		cout << "You find yourself unable to move with fear!" << endl;
		t_orc->m_turn = false;
		t_troll->m_turn = true;
		break;
		break;
	}
}
