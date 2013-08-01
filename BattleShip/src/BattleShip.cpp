#include "../include/main.h"

#define BATTLESHIP_BLANK  ' '
#define BATTLESHIP_SHIP   '#'
#define BATTLESHIP_MISSLE 'X'

void ClearGame(BATTLESHIP_STATE* state)
{
	state->size = sizeof(BATTLESHIP_STATE);
	state->playerID = 0;

	char* grid0 = (char*)&state->grid;
	for (uint i = 0; i < 100; i++)
	{
		grid0[i] = BATTLESHIP_BLANK;
	}

	state->carrierIndices.hit0 = false;
	state->carrierIndices.hit1 = false;
	state->carrierIndices.hit2 = false;
	state->carrierIndices.hit3 = false;
	state->carrierIndices.hit4 = false;
	state->battleshipIndices.hit0 = false;
	state->battleshipIndices.hit1 = false;
	state->battleshipIndices.hit2 = false;
	state->battleshipIndices.hit3 = false;
	state->cruiserIndices.hit0 = false;
	state->cruiserIndices.hit1 = false;
	state->cruiserIndices.hit2 = false;
	state->destroyer1Indices.hit0 = false;
	state->destroyer1Indices.hit1 = false;
	state->destroyer2Indices.hit0 = false;
	state->destroyer2Indices.hit1 = false;

	state->misslesTaken = 0;
	state->hits = 0;
	state->misses = 0;
	state->allShipsPlaced = false;
	state->carrierDestroyed = false;
	state->battleshipDestroyed = false;
	state->cruiserDestroyed = false;
	state->destroyer1Destroyed = false;
	state->destroyer2Destroyed = false;
}
bool ValidGame(BATTLESHIP_STATE* state)
{
	return 
		state->size == sizeof(BATTLESHIP_STATE) && 
		state->playerID != 0 && 
		state->misslesTaken == (state->hits + state->misses) && 
		state->carrierIndices.i0 < 100 && 
		state->carrierIndices.i1 < 100 && 
		state->carrierIndices.i2 < 100 && 
		state->carrierIndices.i3 < 100 && 
		state->carrierIndices.i4 < 100 && 
		state->battleshipIndices.i0 < 100 && 
		state->battleshipIndices.i1 < 100 && 
		state->battleshipIndices.i2 < 100 && 
		state->battleshipIndices.i3 < 100 && 
		state->cruiserIndices.i0 < 100 && 
		state->cruiserIndices.i1 < 100 && 
		state->cruiserIndices.i2 < 100 && 
		state->destroyer1Indices.i0 < 100 && 
		state->destroyer1Indices.i1 < 100 && 
		state->destroyer2Indices.i0 < 100 && 
		state->destroyer2Indices.i1 < 100 && 
		state->allShipsPlaced;
}

void GetCarrierIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1, uchar& i2, uchar& i3, uchar& i4)
{
	char* grid0 = (char*)&state->grid;
	if (flip)
	{
		if (x >= 10) x = 9;
		if (y >= 5) y = 4;
		i0 = (y * 10) + x;
		i1 = i0 + 10;
		i2 = i1 + 10;
		i3 = i2 + 10;
		i4 = i3 + 10;
	}
	else
	{
		if (x >= 5) x = 4;
		if (y >= 10) y = 9;
		i0 = (y * 10) + x;
		i1 = i0 + 1;
		i2 = i0 + 2;
		i3 = i0 + 3;
		i4 = i0 + 4;
	}
}
void GetBattleshipIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1, uchar& i2, uchar& i3)
{
	char* grid0 = (char*)&state->grid;
	if (flip)
	{
		if (x >= 10) x = 9;
		if (y >= 6) y = 5;
		i0 = (y * 10) + x;
		i1 = i0 + 10;
		i2 = i1 + 10;
		i3 = i2 + 10;
	}
	else
	{
		if (x >= 6) x = 5;
		if (y >= 10) y = 9;
		i0 = (y * 10) + x;
		i1 = i0 + 1;
		i2 = i0 + 2;
		i3 = i0 + 3;
	}
}
void GetCruiserIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1, uchar& i2)
{
	char* grid0 = (char*)&state->grid;
	if (flip)
	{
		if (x >= 10) x = 9;
		if (y >= 7) y = 6;
		i0 = (y * 10) + x;
		i1 = i0 + 10;
		i2 = i1 + 10;
	}
	else
	{
		if (x >= 7) x = 6;
		if (y >= 10) y = 9;
		i0 = (y * 10) + x;
		i1 = i0 + 1;
		i2 = i0 + 2;
	}
}
void GetDestroyerIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1)
{
	char* grid0 = (char*)&state->grid;
	if (flip)
	{
		if (x >= 10) x = 9;
		if (y >= 8) y = 7;
		i0 = (y * 10) + x;
		i1 = i0 + 10;
	}
	else
	{
		if (x >= 8) x = 7;
		if (y >= 10) y = 9;
		i0 = (y * 10) + x;
		i1 = i0 + 1;
	}
}

void PlaceCarrier(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1, i2, i3, i4;
	GetCarrierIndices(state, x, y, flip, i0, i1, i2, i3, i4);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	grid0[i2] = BATTLESHIP_SHIP;
	grid0[i3] = BATTLESHIP_SHIP;
	grid0[i4] = BATTLESHIP_SHIP;
	state->carrierIndices.i0 = i0;
	state->carrierIndices.i1 = i1;
	state->carrierIndices.i2 = i2;
	state->carrierIndices.i3 = i3;
	state->carrierIndices.i4 = i4;
}
void PlaceBattleship(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1, i2, i3;
	GetBattleshipIndices(state, x, y, flip, i0, i1, i2, i3);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	grid0[i2] = BATTLESHIP_SHIP;
	grid0[i3] = BATTLESHIP_SHIP;
	state->battleshipIndices.i0 = i0;
	state->battleshipIndices.i1 = i1;
	state->battleshipIndices.i2 = i2;
	state->battleshipIndices.i3 = i3;
}
void PlaceCruiser(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1, i2;
	GetCruiserIndices(state, x, y, flip, i0, i1, i2);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	grid0[i2] = BATTLESHIP_SHIP;
	state->cruiserIndices.i0 = i0;
	state->cruiserIndices.i1 = i1;
	state->cruiserIndices.i2 = i2;
}
void PlaceDestroyer1(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1;
	GetDestroyerIndices(state, x, y, flip, i0, i1);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	state->destroyer1Indices.i0 = i0;
	state->destroyer1Indices.i1 = i1;
}
void PlaceDestroyer2(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1;
	GetDestroyerIndices(state, x, y, flip, i0, i1);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	state->destroyer2Indices.i0 = i0;
	state->destroyer2Indices.i1 = i1;
}

bool CanCarrierFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1, i2, i3, i4;
	GetCarrierIndices(state, x, y, flip, i0, i1, i2, i3, i4);
	return 
		grid0[i0] == BATTLESHIP_BLANK && 
		grid0[i1] == BATTLESHIP_BLANK && 
		grid0[i2] == BATTLESHIP_BLANK && 
		grid0[i3] == BATTLESHIP_BLANK && 
		grid0[i4] == BATTLESHIP_BLANK;
}
bool CanBattleshipFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1, i2, i3;
	GetBattleshipIndices(state, x, y, flip, i0, i1, i2, i3, i4);
	return 
		grid0[i0] == BATTLESHIP_BLANK && 
		grid0[i1] == BATTLESHIP_BLANK && 
		grid0[i2] == BATTLESHIP_BLANK && 
		grid0[i3] == BATTLESHIP_BLANK;
}
bool CanCruiserFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1, i2;
	GetCruiserIndices(state, x, y, flip, i0, i1, i2, i3, i4);
	return 
		grid0[i0] == BATTLESHIP_BLANK && 
		grid0[i1] == BATTLESHIP_BLANK && 
		grid0[i2] == BATTLESHIP_BLANK;
}
bool CanDestroyerFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1;
	GetDestroyerIndices(state, x, y, flip, i0, i1);
	return 
		grid0[i0] == BATTLESHIP_BLANK && 
		grid0[i1] == BATTLESHIP_BLANK;
}

bool IsCarrierHere(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->carrierIndices.i0 == index || 
		state->carrierIndices.i1 == index || 
		state->carrierIndices.i2 == index || 
		state->carrierIndices.i3 == index || 
		state->carrierIndices.i4 == index;
}
bool IsBattleshipHere(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->battleshipIndices.i0 == index || 
		state->battleshipIndices.i1 == index || 
		state->battleshipIndices.i2 == index || 
		state->battleshipIndices.i3 == index;
}
bool IsCruiserHere(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->cruiserIndices.i0 == index || 
		state->cruiserIndices.i1 == index || 
		state->cruiserIndices.i2 == index;
}
bool IsDestroyer1Here(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->destroyer1Indices.i0 == index || 
		state->destroyer1Indices.i1 == index;
}
bool IsDestroyer21Here(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->destroyer2Indices.i0 == index || 
		state->destroyer2Indices.i1 == index;
}

bool IsHit(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	char* grid0 = (char*)&state->grid;
	uchar index = (y * 10) + x;
	if (grid0[index] == BATTLESHIP_MISSLE) return true;
	return false;
}

bool AddMissle(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	char* grid0 = (char*)&state->grid;
	bool hit = false;
	uchar index = (y * 10) + x;
	if (grid0[index] == BATTLESHIP_SHIP)
	{
		state->hits++;
		// check which ship is hit
		hit = true;
	}
	else state->misses++;
	grid0[index] = BATTLESHIP_MISSLE;
	return hit;
}

void PrintGame(BATTLESHIP_STATE* client, BATTLESHIP_STATE* other)
{
	printf(" .12345678910 .12345678910\n");
	printf(" A%c%c%c%c%c%c%c%c%c%c  A%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.a01, client->grid.a02, client->grid.a03, client->grid.a04, client->grid.a05, 
		client->grid.a06, client->grid.a07, client->grid.a08, client->grid.a09, client->grid.a10, 
		other->grid.a01, other->grid.a02, other->grid.a03, other->grid.a04, other->grid.a05, 
		other->grid.a06, other->grid.a07, other->grid.a08, other->grid.a09, other->grid.a10);
	printf(" B%c%c%c%c%c%c%c%c%c%c  B%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.b01, client->grid.b02, client->grid.b03, client->grid.b04, client->grid.b05, 
		client->grid.b06, client->grid.b07, client->grid.b08, client->grid.b09, client->grid.b10, 
		other->grid.b01, other->grid.b02, other->grid.b03, other->grid.b04, other->grid.b05, 
		other->grid.b06, other->grid.b07, other->grid.b08, other->grid.b09, other->grid.b10);
	printf(" C%c%c%c%c%c%c%c%c%c%c  C%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.c01, client->grid.c02, client->grid.c03, client->grid.c04, client->grid.c05, 
		client->grid.c06, client->grid.c07, client->grid.c08, client->grid.c09, client->grid.c10, 
		other->grid.c01, other->grid.c02, other->grid.c03, other->grid.c04, other->grid.c05, 
		other->grid.c06, other->grid.c07, other->grid.c08, other->grid.c09, other->grid.c10);
	printf(" D%c%c%c%c%c%c%c%c%c%c  D%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.d01, client->grid.d02, client->grid.d03, client->grid.d04, client->grid.d05, 
		client->grid.d06, client->grid.d07, client->grid.d08, client->grid.d09, client->grid.d10, 
		other->grid.d01, other->grid.d02, other->grid.d03, other->grid.d04, other->grid.d05, 
		other->grid.d06, other->grid.d07, other->grid.d08, other->grid.d09, other->grid.d10);
	printf(" E%c%c%c%c%c%c%c%c%c%c  E%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.e01, client->grid.e02, client->grid.e03, client->grid.e04, client->grid.e05, 
		client->grid.e06, client->grid.e07, client->grid.e08, client->grid.e09, client->grid.e10, 
		other->grid.e01, other->grid.e02, other->grid.e03, other->grid.e04, other->grid.e05, 
		other->grid.e06, other->grid.e07, other->grid.e08, other->grid.e09, other->grid.e10);
	printf(" F%c%c%c%c%c%c%c%c%c%c  F%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.f01, client->grid.f02, client->grid.f03, client->grid.f04, client->grid.f05, 
		client->grid.f06, client->grid.f07, client->grid.f08, client->grid.f09, client->grid.f10, 
		other->grid.f01, other->grid.f02, other->grid.f03, other->grid.f04, other->grid.f05, 
		other->grid.f06, other->grid.f07, other->grid.f08, other->grid.f09, other->grid.f10);
	printf(" G%c%c%c%c%c%c%c%c%c%c  G%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.g01, client->grid.g02, client->grid.g03, client->grid.g04, client->grid.g05, 
		client->grid.g06, client->grid.g07, client->grid.g08, client->grid.g09, client->grid.g10, 
		other->grid.g01, other->grid.g02, other->grid.g03, other->grid.g04, other->grid.g05, 
		other->grid.g06, other->grid.g07, other->grid.g08, other->grid.g09, other->grid.g10);
	printf(" H%c%c%c%c%c%c%c%c%c%c  H%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.h01, client->grid.h02, client->grid.h03, client->grid.h04, client->grid.h05, 
		client->grid.h06, client->grid.h07, client->grid.h08, client->grid.h09, client->grid.h10, 
		other->grid.h01, other->grid.h02, other->grid.h03, other->grid.h04, other->grid.h05, 
		other->grid.h06, other->grid.h07, other->grid.h08, other->grid.h09, other->grid.h10);
	printf(" I%c%c%c%c%c%c%c%c%c%c  I%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.i01, client->grid.i02, client->grid.i03, client->grid.i04, client->grid.i05, 
		client->grid.i06, client->grid.i07, client->grid.i08, client->grid.i09, client->grid.i10, 
		other->grid.i01, other->grid.i02, other->grid.i03, other->grid.i04, other->grid.i05, 
		other->grid.i06, other->grid.i07, other->grid.i08, other->grid.i09, other->grid.i10);
	printf(" J%c%c%c%c%c%c%c%c%c%c  J%c%c%c%c%c%c%c%c%c%c\n", 
		client->grid.j01, client->grid.j02, client->grid.j03, client->grid.j04, client->grid.j05, 
		client->grid.j06, client->grid.j07, client->grid.j08, client->grid.j09, client->grid.j10, 
		other->grid.j01, other->grid.j02, other->grid.j03, other->grid.j04, other->grid.j05, 
		other->grid.j06, other->grid.j07, other->grid.j08, other->grid.j09, other->grid.j10);
}