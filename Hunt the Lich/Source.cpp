#include <iostream>
#include <cstring>
#include <conio.h>
#include "String.h"
using namespace std;

#define KEY_FORWARD 72
#define KEY_BACKWARD 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE ' '
#define KEY_UP1 'u'
#define KEY_UP2 'U'
#define KEY_DOWN1 'd'
#define KEY_DOWN2 'D'
#define KEY_YES1 'y'
#define KEY_YES2 'Y'
#define KEY_NO1 'n'
#define KEY_NO2 'N'

bool Win = false;
bool Loose = false;
int Round = 0;

class roomData
{
public:
	int x, y, z;		// X-axis coordinate, Y-axis coordinate, Z-axis coordinate
	bool Forward;		// 0 = Wall, 1 = Hall
	bool Right;		// 0 = Wall, 1 = Hall
	bool Backward;		// 0 = Wall, 1 = Hall
	bool Left;		// 0 = Wall, 1 = Hall
	bool Up;		// 0 = no ladder, 1 = Ladder Up
	bool Down;		// 0 = no ladder, 1 = Ladder Down
	int getHalls()	// Function for how many directions the room has
	{
		int i = 0;
		if (Forward == 1) { ++i; };
		if (Right == 1) { ++i; };
		if (Backward == 1) { ++i; };
		if (Left == 1) { ++i; };
		if (Up == 1) { ++i; };
		if (Down == 1) { ++i; };
		return i;
	}
};
roomData Room[3][25] =
{
	{ //floor 0
		{ 0, 0, 0,	 1, 1, 0, 0,	 0, 0 },	//room 0 (0,0)
		{ 1, 0, 0,	 0, 1, 0, 1,	 0, 0 },	//room 1 (0,1)
		{ 2, 0, 0,	 1, 1, 0, 1,	 0, 0 },	//room 2 (0,2)
		{ 3, 0, 0,	 1, 1, 0, 1,	 0, 0 },	//room 3 (0,3)
		{ 4, 0, 0,	 1, 0, 0, 1,	 0, 0 },	//room 4 (0,4)
		{ 0, 1, 0,	 1, 1, 1, 0,	 0, 0 },	//room 5 (1,0)
		{ 1, 1, 0,	 1, 1, 0, 1,	 0, 0 },	//room 6 (1,1)
		{ 2, 1, 0,	 1, 1, 1, 1,	 0, 0 },	//room 7 (1,2)
		{ 3, 1, 0,	 1, 0, 1, 1,	 0, 0 },	//room 8 (1,3)
		{ 4, 1, 0,	 0, 0, 1, 0,	 1, 0 },	//room 9 (1,4)
		{ 0, 2, 0,	 1, 1, 1, 0,	 0, 0 },	//room 10 (2,0)
		{ 1, 2, 0,	 1, 1, 1, 1,	 0, 0 },	//room 11 (2,1)
		{ 2, 2, 0,	 1, 1, 1, 1,	 1, 0 },	//room 12 (2,2)
		{ 3, 2, 0,	 1, 1, 1, 1,	 0, 0 },	//room 13 (2,3)
		{ 4, 2, 0,	 1, 0, 0, 1,	 0, 0 },	//room 14 (2,4)
		{ 0, 3, 0,	 0, 1, 1, 0,	 0, 0 },	//room 15 (3,0)
		{ 1, 3, 0,	 0, 1, 1, 1,	 0, 0 },	//room 16 (3,1)
		{ 2, 3, 0,	 1, 1, 1, 1,	 0, 0 },	//room 17 (3,2)
		{ 3, 3, 0,	 1, 1, 1, 1,	 0, 0 },	//room 18 (3,3)
		{ 4, 3, 0,	 1, 0, 1, 1,	 0, 0 },	//room 19 (3,4)
		{ 0, 4, 0,	 0, 1, 0, 0,	 0, 0 },	//room 20 (4,0)
		{ 1, 4, 0,	 0, 0, 0, 1,	 1, 0 },	//room 21 (4,1)
		{ 2, 4, 0,	 0, 1, 1, 0,	 0, 0 },	//room 22 (4,2)
		{ 3, 4, 0,	 0, 0, 1, 1,	 0, 0 },	//room 23 (4,3)
		{ 4, 4, 0,	 0, 0, 1, 0,	 0, 0 }		//room 24 (4,4)
	},{ //floor 1
		{ 0, 0, 1,	 1, 1, 0, 0,	 0, 0 },	//room 0 (0,0)
		{ 1, 0, 1,	 0, 0, 0, 1,	 1, 0 },	//room 1 (0,1)
		{ 2, 0, 1,	 1, 1, 0, 0,	 0, 0 },	//room 2 (0,2)
		{ 3, 0, 1,	 0, 1, 0, 1,	 1, 0 },	//room 3 (0,3)
		{ 4, 0, 1,	 1, 0, 0, 1,	 0, 0 },	//room 4 (0,4)
		{ 0, 1, 1,	 1, 1, 1, 0,	 0, 0 },	//room 5 (1,0)
		{ 1, 1, 1,	 1, 1, 0, 1,	 0, 0 },	//room 6 (1,1)
		{ 2, 1, 1,	 1, 1, 1, 1,	 0, 0 },	//room 7 (1,2)
		{ 3, 1, 1,	 1, 0, 0, 1,	 0, 0 },	//room 8 (1,3)
		{ 4, 1, 1,	 1, 0, 1, 0,	 0, 1 },	//room 9 (1,4)
		{ 0, 2, 1,	 0, 0, 1, 0,	 1, 0 },	//room 10 (2,0)
		{ 1, 2, 1,	 1, 1, 1, 0,	 0, 0 },	//room 11 (2,1)
		{ 2, 2, 1,	 1, 1, 1, 1,	 1, 1 },	//room 12 (2,2)
		{ 3, 2, 1,	 1, 0, 1, 1,	 0, 0 },	//room 13 (2,3)
		{ 4, 2, 1,	 1, 0, 1, 0,	 0, 0 },	//room 14 (2,4)
		{ 0, 3, 1,	 1, 1, 0, 0,	 0, 0 },	//room 15 (3,0)
		{ 1, 3, 1,	 0, 1, 1, 1,	 0, 0 },	//room 16 (3,1)
		{ 2, 3, 1,	 1, 1, 1, 1,	 0, 0 },	//room 17 (3,2)
		{ 3, 3, 1,	 1, 1, 1, 1,	 0, 0 },	//room 18 (3,3)
		{ 4, 3, 1,	 0, 0, 1, 1,	 0, 0 },	//room 19 (3,4)
		{ 0, 4, 1,	 0, 1, 1, 0,	 0, 0 },	//room 20 (4,0)
		{ 1, 4, 1,	 0, 1, 0, 1,	 0, 1 },	//room 21 (4,1)
		{ 2, 4, 1,	 0, 1, 1, 1,	 0, 0 },	//room 22 (4,2)
		{ 3, 4, 1,	 0, 1, 1, 1,	 0, 0 },	//room 23 (4,3)
		{ 4, 4, 1,	 0, 0, 0, 1,	 1, 0 }		//room 24 (4,4)
	},{ //floor 2
		{ 0, 0, 2,	 1, 1, 0, 0,	 0, 0 },	//room 0 (0,0)
		{ 1, 0, 2,	 0, 1, 0, 1,	 0, 1 },	//room 1 (0,1)
		{ 2, 0, 2,	 0, 0, 0, 1,	 0, 0 },	//room 2 (0,2)
		{ 3, 0, 2,	 0, 1, 0, 0,	 0, 1 },	//room 3 (0,3)
		{ 4, 0, 2,	 1, 0, 0, 1,	 0, 0 },	//room 4 (0,4)
		{ 0, 1, 2,	 0, 0, 1, 0,	 0, 0 },	//room 5 (1,0)
		{ 1, 1, 2,	 1, 1, 0, 0,	 0, 0 },	//room 6 (1,1)
		{ 2, 1, 2,	 1, 1, 0, 1,	 0, 0 },	//room 7 (1,2)
		{ 3, 1, 2,	 1, 0, 0, 1,	 0, 0 },	//room 8 (1,3)
		{ 4, 1, 2,	 1, 0, 1, 0,	 0, 0 },	//room 9 (1,4)
		{ 0, 2, 2,	 1, 0, 0, 0,	 0, 1 },	//room 10 (2,0)
		{ 1, 2, 2,	 1, 1, 1, 0,	 0, 0 },	//room 11 (2,1)
		{ 2, 2, 2,	 1, 1, 1, 1,	 0, 1 },	//room 12 (2,2)
		{ 3, 2, 2,	 1, 0, 1, 1,	 0, 0 },	//room 13 (2,3)
		{ 4, 2, 2,	 0, 0, 1, 0,	 0, 0 },	//room 14 (2,4)
		{ 0, 3, 2,	 1, 0, 1, 0,	 0, 0 },	//room 15 (3,0)
		{ 1, 3, 2,	 0, 1, 1, 0,	 0, 0 },	//room 16 (3,1)
		{ 2, 3, 2,	 1, 1, 1, 1,	 0, 0 },	//room 17 (3,2)
		{ 3, 3, 2,	 0, 0, 1, 1,	 0, 0 },	//room 18 (3,3)
		{ 4, 3, 2,	 1, 0, 0, 0,	 0, 0 },	//room 19 (3,4)
		{ 0, 4, 2,	 0, 1, 1, 0,	 0, 0 },	//room 20 (4,0)
		{ 1, 4, 2,	 0, 0, 0, 1,	 0, 0 },	//room 21 (4,1)
		{ 2, 4, 2,	 0, 0, 1, 0,	 0, 0 },	//room 22 (4,2)
		{ 3, 4, 2,	 0, 1, 0, 0,	 0, 0 },	//room 23 (4,3)
		{ 4, 4, 2,	 0, 0, 1, 1,	 0, 1 }		//room 24 (4,4)
	}
};

class playerData
{
public:
	int x, y, z;		// X, Y = Room / Z = Floor
	int Direction;		// Saves the direction the player is facing (0 = North, 1 = East, 2 = South, 3 = West)
	bool Key;			// true if the player has the key
	bool Hammer;		// true if the player has the hammer
	bool Stance;		// true makes diretional keys = attack direction / false makes diretional keys = movement direction
	int getRoom()		// finds the players specific room number
	{
		for (int R = 0; R < 25; ++R)
		{
			if ((x == Room[z][R].x) && (y == Room[z][R].y)) { return R; }
		}
		return 0;
	}
	int changeD(int D)	// changes the players direction
	{
		return Direction = ((Direction + D) % 4);
	}
	void Move()
	{
		switch (Direction)
		{
		case 0: ++y; break;	// North
		case 2:	--y; break;	// South
		case 1: ++x; break;	// East
		case 3: --x; break;	// West
		}
	}
};
playerData Player = { 2, 0, 0, 0, 0, 0, 0 };

class pitData
{
public:
	int x, y, z;
	int getRoom()
	{
		for (int R = 0; R < 25; ++R)
		{
			if ((x == Room[z][R].x) && (y == Room[z][R].y))
			{
				return R;
			}
		}
		return 0;
	}
};
pitData Pit[6] = { { 0, 1, 0 },{ 4, 2, 0 },{ 3, 4, 0 },{ 2, 0, 1 },{ 2, 4, 1 },{ 4, 3, 1 }, };

class lichData
{
public:
	int x, y, z;
	int Direction; 	// Saves the direction the Wraith is facing (0=Up, 1=Right, 2=Down, 3=Left)
	bool Undead;
	bool Phylactery1, Phylactery2;
	bool Assembled;
	int getRoom()
	{
		for (int R = 0; R < 25; ++R)
		{
			if ((x == Room[z][R].x) && (y == Room[z][R].y))
			{
				return R;
			}
		}
		return 0;
	}
	int changeD(int D) // Wraiths change in direction
	{
		return Direction = ((Direction + D) % 4);
	}
	void Move() // Moves the Player in their current direction.
	{
		switch (Direction)
		{
		case 0: ++y; break;	// Up
		case 2:	--y; break;	// Down
		case 1: ++x; break;	// Right
		case 3: --x; break;	// Left
		}
	}
};
lichData Lich = { 2, 4, 2, 2, 1, 1, 1, 0 };

// checks for walls/halls for the selected room (a = related key direction, b = ?.Direction, c = ?.z, d = ?.getRoom())
int wallCheck(int a, int b, int c, int d)
{
	switch (a)
	{
	case 0:
		if ((b == 0) && (Room[c][d].Forward == 0)) { return 1; }
		if ((b == 1) && (Room[c][d].Right == 0)) { return 1; }
		if ((b == 2) && (Room[c][d].Backward == 0)) { return 1; }
		if ((b == 3) && (Room[c][d].Left == 0)) { return 1; }
		else return 0;
	case 1:
		if ((b == 2) && (Room[c][d].Forward == 0)) { return 1; }
		if ((b == 3) && (Room[c][d].Right == 0)) { return 1; }
		if ((b == 0) && (Room[c][d].Backward == 0)) { return 1; }
		if ((b == 1) && (Room[c][d].Left == 0)) { return 1; }
		else return 0;
	case 2:
		if ((b == 1) && (Room[c][d].Forward == 0)) { return 1; }
		if ((b == 2) && (Room[c][d].Right == 0)) { return 1; }
		if ((b == 3) && (Room[c][d].Backward == 0)) { return 1; }
		if ((b == 0) && (Room[c][d].Left == 0)) { return 1; }
		else return 0;
	case 3:
		if ((b == 3) && (Room[c][d].Forward == 0)) { return 1; }
		if ((b == 0) && (Room[c][d].Right == 0)) { return 1; }
		if ((b == 1) && (Room[c][d].Backward == 0)) { return 1; }
		if ((b == 2) && (Room[c][d].Left == 0)) { return 1; }
		else return 0;
	}
	return 0;
}

// The Players attack and check for Win condition.
class attackData
{
public:
	bool Fire;
	int x, y, z;
	int D;
	int getRoom()
	{
		for (int R = 0; R < 25; ++R)
		{
			if ((x == Room[z][R].x) && (y == Room[z][R].y)) { return R; }
		}
		return 0;
	}
	void Atk(int A)
	{
		Fire = 1;
		x = Player.x;
		y = Player.y;
		z = Player.z;
		D = Player.Direction;
		D = ((D + A) % 4);
		if (D < 0) { D = 3; }
		while (Fire == true)
		{
			switch (D)
			{
			case 0: ++y; break;	// North
			case 2:	--y; break;	// South
			case 1: ++x; break;	// East
			case 3: --x; break;	// West
			}
			if ((z == Lich.z) && (x == Lich.x) && (y == Lich.y))
			{
				Lich.Assembled = false; Lich.Undead = false;
				if ((Lich.Phylactery1 == true) || (Lich.Phylactery2 == true))
				{
					cout << "The Lich is struck by your lightning bolt and falls to pieces." << endl << endl; Lich.Undead = true; Round = 15;
				}
				if ((Lich.Phylactery1 == false) && (Lich.Phylactery2 == false))
				{
					cout << "The Lich is struck by your lightning bolt, spontainiously combusts, then crumbles to dust." << endl << endl; Win = true;
				}
			}
			switch (D)
			{
			case 0: if ((Room[z][getRoom()].Forward) == 0) { Fire = 0; } break; 	// Up
			case 2:	if ((Room[z][getRoom()].Backward) == 0) { Fire = 0; } break;	// Down
			case 1: if ((Room[z][getRoom()].Right) == 0) { Fire = 0; } break;	// Right
			case 3: if ((Room[z][getRoom()].Left) == 0) { Fire = 0; } break;	// Left
			}
		}
	}
};
attackData Attack;

// Player directional input, attack toggle, and display wall collision.
void Direction()
{
	int Q = 0;
	while (Q == 0)
	{
		int c = 0;
		switch (c = _getch())
		{
		case KEY_FORWARD: //key up
			if (wallCheck(0, Player.Direction, Player.z, Player.getRoom()) == 1) { cout << "I can't go that way." << endl; continue; }
			if (Player.Stance == 0) { Player.changeD(0); Player.Move(); }
			if (Player.Stance == 1) { cout << "You fire a holy bolt of lightning down the hall ahead of you." << endl << endl; Attack.Atk(0); }
			else cout << "You go straight." << endl << endl;
			++Q;
			break;
		case KEY_BACKWARD: // key down
			if (wallCheck(1, Player.Direction, Player.z, Player.getRoom()) == 1) { cout << "I can't go that way." << endl; continue; }
			if (Player.Stance == 0) { Player.changeD(2); Player.Move(); }
			if (Player.Stance == 1) { cout << "You fire a holy bolt of lightning down the hall behind you." << endl << endl; Attack.Atk(2); }
			else cout << "You go back." << endl << endl;
			++Q;
			break;
		case KEY_LEFT: // key left
			if (wallCheck(2, Player.Direction, Player.z, Player.getRoom()) == 1) { cout << "I can't go that way." << endl; continue; }
			if (Player.Stance == 0)
			{
				if (Player.Direction == 0) { Player.changeD(3); }		// if the player is facing 0=forward and goes left, change D to 3=Left
				else Player.changeD(-1);
				Player.Move();
			}
			if (Player.Stance == 1) { cout << "You fire a holy bolt of lightning down the hall to your left." << endl << endl; Attack.Atk(-1); }
			else cout << "You go left." << endl << endl;
			++Q;
			break;
		case KEY_RIGHT: // key right
			if (wallCheck(3, Player.Direction, Player.z, Player.getRoom()) == 1) { cout << "I can't go that way." << endl; continue; }
			if (Player.Stance == 0) { Player.changeD(1); Player.Move(); }
			if (Player.Stance == 1) { cout << "You fire a holy bolt of lightning down the hall to your right." << endl << endl; Attack.Atk(1); }
			else cout << "You go right." << endl << endl;
			++Q;
			break;
		case KEY_UP1: // key u
		case KEY_UP2: // key U
			if (Room[Player.z][Player.getRoom()].Up == 0) { cout << "I can't go that way." << endl; continue; }
			if (Player.Stance == 0) { ++Player.z; }
			if (Player.Stance == 1) { cout << "You fire a holy bolt of lightning up the ladder to the floor above." << endl << endl; Attack.Atk(1); }
			else cout << "You go up a ladder." << endl << endl;
			++Q;
			break;
		case KEY_DOWN1: // key d
		case KEY_DOWN2: // key D
			if (Room[Player.z][Player.getRoom()].Down == 0) { cout << "I can't go that way." << endl; continue; }
			if (Player.Stance == 0) { --Player.z; }
			if (Player.Stance == 1) { cout << "You fire a holy bolt of lightning down the ladder to the floor below." << endl << endl; Attack.Atk(1); }
			else cout << "You go down a ladder." << endl << endl;
			++Q;
			break;
		case KEY_SPACE:
			Player.Stance = !Player.Stance;
			if (Player.Stance == 0) { cout << "Move" << endl << endl; }
			if (Player.Stance == 1) { cout << "Attack" << endl << endl; }
			break;
		default:
			break;
		}
	}
}

// Displays the rooms directional options for the Player.
void roomOptions()
{
	if (Room[Player.z][Player.getRoom()].getHalls() == 1)
	{
		cout << "There is 1 way to go." << endl;
	}
	if (Room[Player.z][Player.getRoom()].getHalls() != 1)
		if (Room[Player.z][Player.getRoom()].getHalls() != 1)
		{
			cout << "There are " << Room[Player.z][Player.getRoom()].getHalls() << " ways to go." << endl;
		}
	if (Player.Direction == 0)
	{
		if (Room[Player.z][Player.getRoom()].Forward == 1) { cout << "- Forward" << endl; }
		if (Room[Player.z][Player.getRoom()].Right == 1) { cout << "- Right" << endl; }
		if (Room[Player.z][Player.getRoom()].Left == 1) { cout << "- Left" << endl; }
		if (Room[Player.z][Player.getRoom()].Backward == 1) { cout << "- Backward" << endl; }
		if (Room[Player.z][Player.getRoom()].Up == 1) { cout << "- Up" << endl; }
		if (Room[Player.z][Player.getRoom()].Down == 1) { cout << "- Down" << endl; }
	}
	if (Player.Direction == 1)
	{
		if (Room[Player.z][Player.getRoom()].Right == 1) { cout << "- Forward" << endl; }
		if (Room[Player.z][Player.getRoom()].Backward == 1) { cout << "- Right" << endl; }
		if (Room[Player.z][Player.getRoom()].Forward == 1) { cout << "- Left" << endl; }
		if (Room[Player.z][Player.getRoom()].Left == 1) { cout << "- Backward" << endl; }
		if (Room[Player.z][Player.getRoom()].Up == 1) { cout << "- Up" << endl; }
		if (Room[Player.z][Player.getRoom()].Down == 1) { cout << "- Down" << endl; }
	}
	if (Player.Direction == 2)
	{
		if (Room[Player.z][Player.getRoom()].Backward == 1) { cout << "- Forward" << endl; }
		if (Room[Player.z][Player.getRoom()].Left == 1) { cout << "- Right" << endl; }
		if (Room[Player.z][Player.getRoom()].Right == 1) { cout << "- Left" << endl; }
		if (Room[Player.z][Player.getRoom()].Forward == 1) { cout << "- Backward" << endl; }
		if (Room[Player.z][Player.getRoom()].Up == 1) { cout << "- Up" << endl; }
		if (Room[Player.z][Player.getRoom()].Down == 1) { cout << "- Down" << endl; }
	}
	if (Player.Direction == 3)
	{
		if (Room[Player.z][Player.getRoom()].Left == 1) { cout << "- Forward" << endl; }
		if (Room[Player.z][Player.getRoom()].Forward == 1) { cout << "- Right" << endl; }
		if (Room[Player.z][Player.getRoom()].Backward == 1) { cout << "- Left" << endl; }
		if (Room[Player.z][Player.getRoom()].Right == 1) { cout << "- Backward" << endl; }
		if (Room[Player.z][Player.getRoom()].Up == 1) { cout << "- Up" << endl; }
		if (Room[Player.z][Player.getRoom()].Down == 1) { cout << "- Down" << endl; }
	}
	cout << endl;
}

// Displays Wraith warnings and check for Loose condition.
void wraithHazard(int M)
{
	if ((wallCheck(2, Lich.Direction, Lich.z, Lich.getRoom()) == 0) && ((Player.x == Lich.x - 1) && (Player.y == Lich.y))) { cout << "You feel a chill run down your spine." << endl << endl; }
	if ((wallCheck(3, Lich.Direction, Lich.z, Lich.getRoom()) == 0) && ((Player.x == Lich.x + 1) && (Player.y == Lich.y))) { cout << "You feel a chill run down your spine." << endl << endl; }
	if ((wallCheck(1, Lich.Direction, Lich.z, Lich.getRoom()) == 0) && ((Player.x == Lich.x) && (Player.y == Lich.y - 1))) { cout << "You feel a chill run down your spine." << endl << endl; }
	if ((wallCheck(0, Lich.Direction, Lich.z, Lich.getRoom()) == 0) && ((Player.x == Lich.x) && (Player.y == Lich.y + 1))) { cout << "You feel a chill run down your spine." << endl << endl; }
	if ((Room[Lich.z][Lich.getRoom()].Down == 1) && (Player.z == Lich.z - 1)) { cout << "You feel a chill run down your spine." << endl << endl; }
	if ((Room[Lich.z][Lich.getRoom()].Up == 1) && (Player.z == Lich.z + 1)) { cout << "You feel a chill run down your spine." << endl << endl; }
	if (M < 30 && ((Player.z == Lich.z) && (Player.getRoom() == Lich.getRoom())))
	{
		cout << "Dark energy permeates the room and skeletal remains are scattered about." << endl << endl;
		if (Round < 20) { Round = 20; }
	}
	if (M == 30) { cout << "The Lich has reformed himself and begins to cast an apocalypse spell" << endl << endl; Lich.Assembled = true; }
	if (M >= 30 && ((Player.z == Lich.z) && (Player.getRoom() == Lich.getRoom())))
	{
		cout << "The Lich reaches out to you and touches your arm, you rapidly age to dust." << endl; Loose = true;
	}
	if (M == 40)
	{
		cout << "The Lich finishes castiong it's apocalypse spell." << endl << "Your soul was ripped from your body." << endl; Loose = true;
	}
}

// Displays Pit warnings and check for Loose condition.
void pitHazard(int x)
{
	if ((wallCheck(2, 0, Pit[x].z, Pit[x].getRoom()) == 0) && ((Player.z == Pit[x].z) && (Player.x == Pit[x].x - 1) && (Player.y == Pit[x].y))) { cout << "You feel a slight draft." << endl << endl; }
	if ((wallCheck(3, 0, Pit[x].z, Pit[x].getRoom()) == 0) && ((Player.z == Pit[x].z) && (Player.x == Pit[x].x + 1) && (Player.y == Pit[x].y))) { cout << "You feel a slight draft." << endl << endl; }
	if ((wallCheck(1, 0, Pit[x].z, Pit[x].getRoom()) == 0) && ((Player.z == Pit[x].z) && (Player.x == Pit[x].x) && (Player.y == Pit[x].y - 1))) { cout << "You feel a slight draft." << endl << endl; }
	if ((wallCheck(0, 0, Pit[x].z, Pit[x].getRoom()) == 0) && ((Player.z == Pit[x].z) && (Player.x == Pit[x].x) && (Player.y == Pit[x].y + 1))) { cout << "You feel a slight draft." << endl << endl; }
	if ((Player.getRoom() == Pit[x].getRoom()) && (Player.z == Pit[x].z)) { cout << "You fell down a pit and died." << endl; Loose = true; }
}

int main()
{
	cout << "                   You are a Mage of a holy order," << endl;
	cout << "           able to hurl lightning bolts using your magic." << endl << endl;
	cout << "                   The holy order you are part of" << endl;
	cout << "                is most known for dealing with undead." << endl;
	cout << "             You have been asked by a high ranking priest" << endl;
	cout << "         to clear out the undead that have invaded his castle." << endl;
	cout << "   It is believed that the remains of a Lich is somewhere in the castle." << endl << endl;
	cout << "                      In order to kill a Lich," << endl;
	cout << "         one must destroy their Phylactery(s) and their body." << endl;
	cout << "            Destroying a Phylactery requiers holy weapons" << endl;
	cout << "                      which you do not possess." << endl;
	cout << "              Thankfully the priest has one such weapon," << endl;
	cout << "                but its in a locked room in the castle." << endl;
	cout << "         He also lost the key somewhere in the castle as he fled." << endl << endl;
	cout << "             You must find a key to get to the holy weapon," << endl;
	cout << "               find and destroy the Lich's Phylactery(s)," << endl;
	cout << "                          and kill the Lich." << endl << endl;
	system("pause");
	system("CLS");

	cout << "			      Player Controlls" << endl << endl << endl;
	cout << "			      Directional Keys" << endl;
	cout << "			          [Forward]" << endl;
	cout << "			  [Left] [Backward] [Right]" << endl << endl << endl;
	cout << "			Up/Down		     Yes/No" << endl;
	cout << "			[u]/[d]		     [y]/[n]" << endl << endl << endl;
	cout << "			     Toggle Attack/Move" << endl;
	cout << "			        [Space Bar]" << endl << endl << endl;
	system("pause");
	system("CLS");

	for (; (Win == false) && (Loose == false); ++Round)
	{



		// Door to Hammer Room
		if ((Player.Hammer == false) && (Player.z == 0) && (Player.getRoom() == 21))
		{
			cout << "There's a door here, perhaps a key could open it " << endl << endl;
			if (Player.Key == false)
			{
				Room[0][21] = { 1, 4, 0, 0, 0, 0, 0, 1, 0 };
			}
			if (Player.Key == true)
			{
				cout << "Use your Key? [Y/N]" << endl;
				int c = 0;
				switch (c = _getch())
				{
				case KEY_YES1:
				case KEY_YES2:
					cout << "The door opened." << endl << endl;
					Room[0][21] = { 1, 4, 0, 0, 0, 0, 1, 1, 0 };
					break;
				case KEY_NO1:
				case KEY_NO2:
					break;
				}
			}
		}

		// Key Room
		if ((Player.Key == false) && (Player.z == 2) && (Player.getRoom() == 14)) { cout << "You found a key." << endl << endl; Player.Key = true; }

		// Hammer Room
		if ((Player.Hammer == false) && (Player.z == 0) && (Player.getRoom() == 20)) { cout << "You found a Holy Hammer." << endl << endl; Player.Hammer = true; }

		// Phylactery2 Room
		if ((Player.z == 2) && (Player.getRoom() == 23))
		{
			if (Lich.Phylactery2 == false)
			{
				cout << "Shards of a broken Lich Phylactery are scattered about this room." << endl << endl;
			}
			if (Lich.Phylactery2 == true)
			{
				cout << "You found a Lich Phylactery." << endl;
				if (Player.Hammer == true)
				{
					cout << "Smash it? [Y/N]" << endl;
					int c = 0;
					switch (c = _getch())
					{
					case KEY_YES1:
					case KEY_YES2:
						cout << "You smash the Phylactery to pieces" << endl; Lich.Phylactery2 = false;
						if ((Lich.Phylactery1 == false) && (Lich.Assembled == true))
						{
							cout << "A wail of pain can be heard throughout the Castle, The Lich is Vulnerable" << endl;
						}
						break;
					case KEY_NO1:
					case KEY_NO2:
						break;
					}
				}
				cout << endl;
			}
		}

		// Phylactery1 Room
		if ((Player.z == 2) && (Player.getRoom() == 21))
		{
			if (Lich.Phylactery1 == false)
			{
				cout << "Shards of a broken Lich Phylactery are scattered about this room." << endl << endl;
			}
			if (Lich.Phylactery1 == true)
			{
				cout << "You found a Lich Phylactery." << endl;
				if (Player.Hammer == true)
				{
					cout << "Smash it? [Y/N]" << endl;
					int c = 0;
					switch (c = _getch())
					{
					case KEY_YES1:
					case KEY_YES2:
						cout << "You smash the Phylactery to pieces" << endl; Lich.Phylactery1 = false;
						if ((Lich.Phylactery2 == false) && (Lich.Assembled == true))
						{
							cout << "A wail of pain can be heard throughout the Castle, The Lich is Vulnerable" << endl;
						}
						break;
					case KEY_NO1:
					case KEY_NO2:
						break;
					}
				}
				cout << endl;
			}
		}

		// if the Lich hasn't reassembled when both phylacterys are destroyed you win
		if ((Lich.Assembled == false) && (Lich.Phylactery1 == false) && (Lich.Phylactery2 == false))
		{
			cout << "Without the Phylacterys that preserve the Lich's Soul, the Lich's remains crumble to dust." << endl << endl; Win = true;
		}
		if (Win == true) { break; }
		wraithHazard(Round); if (Loose == true) { break; }
		pitHazard(0); if (Loose == true) { break; }
		pitHazard(1); if (Loose == true) { break; }
		pitHazard(2); if (Loose == true) { break; }
		pitHazard(3); if (Loose == true) { break; }
		pitHazard(4); if (Loose == true) { break; }
		pitHazard(5); if (Loose == true) { break; }
		roomOptions();
		Direction();
	}
	if (Loose == true) { cout << endl << "GAME OVER" << endl << "You Are Die!" << endl << endl; }
	if (Win == true) { cout << endl << "CONGRATULATIONS!" << endl << "You Win!" << endl << endl; }
	system("pause");
	return 0;
}
