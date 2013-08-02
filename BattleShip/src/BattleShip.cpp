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

	state->carrierInfo.hits = 0;
	state->carrierInfo.destroyed = false;
	state->carrierInfo.placed = false;
	state->battleshipInfo.hits = 0;
	state->battleshipInfo.destroyed = false;
	state->battleshipInfo.placed = false;
	state->cruiserInfo.hits = 0;
	state->cruiserInfo.destroyed = false;
	state->cruiserInfo.placed = false;
	state->destroyer1Info.hits = 0;
	state->destroyer1Info.destroyed = false;
	state->destroyer1Info.placed = false;
	state->destroyer2Info.hits = 0;
	state->destroyer2Info.destroyed = false;
	state->destroyer2Info.placed = false;

	state->misslesTaken = 0;
	state->hits = 0;
	state->misses = 0;
}
bool ValidGame(BATTLESHIP_STATE* state)
{
	return 
		state->size == sizeof(BATTLESHIP_STATE) && 
		state->playerID != 0 && 
		state->misslesTaken == (state->hits + state->misses) && 
		state->carrierInfo.i0 < 100 && 
		state->carrierInfo.i1 < 100 && 
		state->carrierInfo.i2 < 100 && 
		state->carrierInfo.i3 < 100 && 
		state->carrierInfo.i4 < 100 && 
		state->battleshipInfo.i0 < 100 && 
		state->battleshipInfo.i1 < 100 && 
		state->battleshipInfo.i2 < 100 && 
		state->battleshipInfo.i3 < 100 && 
		state->cruiserInfo.i0 < 100 && 
		state->cruiserInfo.i1 < 100 && 
		state->cruiserInfo.i2 < 100 && 
		state->destroyer1Info.i0 < 100 && 
		state->destroyer1Info.i1 < 100 && 
		state->destroyer2Info.i0 < 100 && 
		state->destroyer2Info.i1 < 100 && 
		state->carrierInfo.placed && 
		state->battleshipInfo.placed && 
		state->cruiserInfo.placed && 
		state->destroyer1Info.placed && 
		state->destroyer2Info.placed;
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
	state->carrierInfo.i0 = i0;
	state->carrierInfo.i1 = i1;
	state->carrierInfo.i2 = i2;
	state->carrierInfo.i3 = i3;
	state->carrierInfo.i4 = i4;
	state->carrierInfo.placed = true;
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
	state->battleshipInfo.i0 = i0;
	state->battleshipInfo.i1 = i1;
	state->battleshipInfo.i2 = i2;
	state->battleshipInfo.i3 = i3;
	state->battleshipInfo.placed = true;
}
void PlaceCruiser(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1, i2;
	GetCruiserIndices(state, x, y, flip, i0, i1, i2);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	grid0[i2] = BATTLESHIP_SHIP;
	state->cruiserInfo.i0 = i0;
	state->cruiserInfo.i1 = i1;
	state->cruiserInfo.i2 = i2;
	state->cruiserInfo.placed = true;
}
void PlaceDestroyer1(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1;
	GetDestroyerIndices(state, x, y, flip, i0, i1);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	state->destroyer1Info.i0 = i0;
	state->destroyer1Info.i1 = i1;
	state->destroyer1Info.placed = true;
}
void PlaceDestroyer2(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip)
{
	char* grid0 = (char*)&state->grid;
	uchar i0, i1;
	GetDestroyerIndices(state, x, y, flip, i0, i1);
	grid0[i0] = BATTLESHIP_SHIP;
	grid0[i1] = BATTLESHIP_SHIP;
	state->destroyer2Info.i0 = i0;
	state->destroyer2Info.i1 = i1;
	state->destroyer2Info.placed = true;
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
	GetBattleshipIndices(state, x, y, flip, i0, i1, i2, i3);
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
	GetCruiserIndices(state, x, y, flip, i0, i1, i2);
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
		state->carrierInfo.i0 == index || 
		state->carrierInfo.i1 == index || 
		state->carrierInfo.i2 == index || 
		state->carrierInfo.i3 == index || 
		state->carrierInfo.i4 == index;
}
bool IsBattleshipHere(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->battleshipInfo.i0 == index || 
		state->battleshipInfo.i1 == index || 
		state->battleshipInfo.i2 == index || 
		state->battleshipInfo.i3 == index;
}
bool IsCruiserHere(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->cruiserInfo.i0 == index || 
		state->cruiserInfo.i1 == index || 
		state->cruiserInfo.i2 == index;
}
bool IsDestroyer1Here(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->destroyer1Info.i0 == index || 
		state->destroyer1Info.i1 == index;
}
bool IsDestroyer21Here(BATTLESHIP_STATE* state, uchar x, uchar y)
{
	uchar index = (y * 10) + x;
	return 
		state->destroyer2Info.i0 == index || 
		state->destroyer2Info.i1 == index;
}

void RegisterCarrierHit(BATTLESHIP_STATE* state)
{
	if (state->carrierInfo.destroyed) return;
	state->carrierInfo.hits++;
	if (state->carrierInfo.hits >= 5)
	{
		state->carrierInfo.destroyed = true;
	}
}
void RegisterBattleshipHit(BATTLESHIP_STATE* state)
{
	if (state->battleshipInfo.destroyed) return;
	state->battleshipInfo.hits++;
	if (state->battleshipInfo.hits >= 4)
	{
		state->battleshipInfo.destroyed = true;
	}
}
void RegisterCruiserHit(BATTLESHIP_STATE* state)
{
	if (state->cruiserInfo.destroyed) return;
	state->cruiserInfo.hits++;
	if (state->cruiserInfo.hits >= 3)
	{
		state->cruiserInfo.destroyed = true;
	}
}
void RegisterDestroyer1Hit(BATTLESHIP_STATE* state)
{
	if (state->destroyer1Info.destroyed) return;
	state->destroyer1Info.hits++;
	if (state->destroyer1Info.hits >= 2)
	{
		state->destroyer1Info.destroyed = true;
	}
}
void RegisterDestroyer2Hit(BATTLESHIP_STATE* state)
{
	if (state->destroyer2Info.destroyed) return;
	state->destroyer2Info.hits++;
	if (state->destroyer2Info.hits >= 2)
	{
		state->destroyer2Info.destroyed = true;
	}
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

bool ParseCoordinate(char* buffer, uint size, uchar& x, uchar& y)
{
	if (buffer == 0 || size < 1) return false;

	bool readX = false;
	bool readY = false;
	uint l = 0;
	for (uint i = 0; i < size; i++)
	{
		char ch = buffer[i];
		if (ch == '\0') break;
		if (l > 2) break;

		if (ch >= '0' && ch <= '9')
		{
			if (!readY) break;
			x = ch - 48;
			readX = true;
		}
		else if (ch >= 'a' && ch <= 'j')
		{
			//if (!readX) break;
			y = ch - 97;
			readY = true;
		}
		else if (ch >= 'A' && ch <= 'J')
		{
			//if (!readX) break;
			y = ch - 65;
			readY = true;
		}
		else return false;
	}
	return readX && readY;
}
void PrintGame(BATTLESHIP_STATE* state1, BATTLESHIP_STATE* state2)
{
	printf(" .0123456789  .0123456789\n");
	printf(" A%c%c%c%c%c%c%c%c%c%c  A%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.a01, state1->grid.a02, state1->grid.a03, state1->grid.a04, state1->grid.a05, 
		state1->grid.a06, state1->grid.a07, state1->grid.a08, state1->grid.a09, state1->grid.a10, 
		state2->grid.a01, state2->grid.a02, state2->grid.a03, state2->grid.a04, state2->grid.a05, 
		state2->grid.a06, state2->grid.a07, state2->grid.a08, state2->grid.a09, state2->grid.a10);
	printf(" B%c%c%c%c%c%c%c%c%c%c  B%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.b01, state1->grid.b02, state1->grid.b03, state1->grid.b04, state1->grid.b05, 
		state1->grid.b06, state1->grid.b07, state1->grid.b08, state1->grid.b09, state1->grid.b10, 
		state2->grid.b01, state2->grid.b02, state2->grid.b03, state2->grid.b04, state2->grid.b05, 
		state2->grid.b06, state2->grid.b07, state2->grid.b08, state2->grid.b09, state2->grid.b10);
	printf(" C%c%c%c%c%c%c%c%c%c%c  C%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.c01, state1->grid.c02, state1->grid.c03, state1->grid.c04, state1->grid.c05, 
		state1->grid.c06, state1->grid.c07, state1->grid.c08, state1->grid.c09, state1->grid.c10, 
		state2->grid.c01, state2->grid.c02, state2->grid.c03, state2->grid.c04, state2->grid.c05, 
		state2->grid.c06, state2->grid.c07, state2->grid.c08, state2->grid.c09, state2->grid.c10);
	printf(" D%c%c%c%c%c%c%c%c%c%c  D%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.d01, state1->grid.d02, state1->grid.d03, state1->grid.d04, state1->grid.d05, 
		state1->grid.d06, state1->grid.d07, state1->grid.d08, state1->grid.d09, state1->grid.d10, 
		state2->grid.d01, state2->grid.d02, state2->grid.d03, state2->grid.d04, state2->grid.d05, 
		state2->grid.d06, state2->grid.d07, state2->grid.d08, state2->grid.d09, state2->grid.d10);
	printf(" E%c%c%c%c%c%c%c%c%c%c  E%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.e01, state1->grid.e02, state1->grid.e03, state1->grid.e04, state1->grid.e05, 
		state1->grid.e06, state1->grid.e07, state1->grid.e08, state1->grid.e09, state1->grid.e10, 
		state2->grid.e01, state2->grid.e02, state2->grid.e03, state2->grid.e04, state2->grid.e05, 
		state2->grid.e06, state2->grid.e07, state2->grid.e08, state2->grid.e09, state2->grid.e10);
	printf(" F%c%c%c%c%c%c%c%c%c%c  F%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.f01, state1->grid.f02, state1->grid.f03, state1->grid.f04, state1->grid.f05, 
		state1->grid.f06, state1->grid.f07, state1->grid.f08, state1->grid.f09, state1->grid.f10, 
		state2->grid.f01, state2->grid.f02, state2->grid.f03, state2->grid.f04, state2->grid.f05, 
		state2->grid.f06, state2->grid.f07, state2->grid.f08, state2->grid.f09, state2->grid.f10);
	printf(" G%c%c%c%c%c%c%c%c%c%c  G%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.g01, state1->grid.g02, state1->grid.g03, state1->grid.g04, state1->grid.g05, 
		state1->grid.g06, state1->grid.g07, state1->grid.g08, state1->grid.g09, state1->grid.g10, 
		state2->grid.g01, state2->grid.g02, state2->grid.g03, state2->grid.g04, state2->grid.g05, 
		state2->grid.g06, state2->grid.g07, state2->grid.g08, state2->grid.g09, state2->grid.g10);
	printf(" H%c%c%c%c%c%c%c%c%c%c  H%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.h01, state1->grid.h02, state1->grid.h03, state1->grid.h04, state1->grid.h05, 
		state1->grid.h06, state1->grid.h07, state1->grid.h08, state1->grid.h09, state1->grid.h10, 
		state2->grid.h01, state2->grid.h02, state2->grid.h03, state2->grid.h04, state2->grid.h05, 
		state2->grid.h06, state2->grid.h07, state2->grid.h08, state2->grid.h09, state2->grid.h10);
	printf(" I%c%c%c%c%c%c%c%c%c%c  I%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.i01, state1->grid.i02, state1->grid.i03, state1->grid.i04, state1->grid.i05, 
		state1->grid.i06, state1->grid.i07, state1->grid.i08, state1->grid.i09, state1->grid.i10, 
		state2->grid.i01, state2->grid.i02, state2->grid.i03, state2->grid.i04, state2->grid.i05, 
		state2->grid.i06, state2->grid.i07, state2->grid.i08, state2->grid.i09, state2->grid.i10);
	printf(" J%c%c%c%c%c%c%c%c%c%c  J%c%c%c%c%c%c%c%c%c%c\n", 
		state1->grid.j01, state1->grid.j02, state1->grid.j03, state1->grid.j04, state1->grid.j05, 
		state1->grid.j06, state1->grid.j07, state1->grid.j08, state1->grid.j09, state1->grid.j10, 
		state2->grid.j01, state2->grid.j02, state2->grid.j03, state2->grid.j04, state2->grid.j05, 
		state2->grid.j06, state2->grid.j07, state2->grid.j08, state2->grid.j09, state2->grid.j10);
}
void PrintState(BATTLESHIP_STATE* state)
{
	printf(" .0123456789\n");
	printf(" A%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.a01, state->grid.a02, state->grid.a03, state->grid.a04, state->grid.a05, 
		state->grid.a06, state->grid.a07, state->grid.a08, state->grid.a09, state->grid.a10);
	printf(" B%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.b01, state->grid.b02, state->grid.b03, state->grid.b04, state->grid.b05, 
		state->grid.b06, state->grid.b07, state->grid.b08, state->grid.b09, state->grid.b10);
	printf(" C%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.c01, state->grid.c02, state->grid.c03, state->grid.c04, state->grid.c05, 
		state->grid.c06, state->grid.c07, state->grid.c08, state->grid.c09, state->grid.c10);
	printf(" D%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.d01, state->grid.d02, state->grid.d03, state->grid.d04, state->grid.d05, 
		state->grid.d06, state->grid.d07, state->grid.d08, state->grid.d09, state->grid.d10);
	printf(" E%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.e01, state->grid.e02, state->grid.e03, state->grid.e04, state->grid.e05, 
		state->grid.e06, state->grid.e07, state->grid.e08, state->grid.e09, state->grid.e10);
	printf(" F%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.f01, state->grid.f02, state->grid.f03, state->grid.f04, state->grid.f05, 
		state->grid.f06, state->grid.f07, state->grid.f08, state->grid.f09, state->grid.f10);
	printf(" G%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.g01, state->grid.g02, state->grid.g03, state->grid.g04, state->grid.g05, 
		state->grid.g06, state->grid.g07, state->grid.g08, state->grid.g09, state->grid.g10);
	printf(" H%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.h01, state->grid.h02, state->grid.h03, state->grid.h04, state->grid.h05, 
		state->grid.h06, state->grid.h07, state->grid.h08, state->grid.h09, state->grid.h10);
	printf(" I%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.i01, state->grid.i02, state->grid.i03, state->grid.i04, state->grid.i05, 
		state->grid.i06, state->grid.i07, state->grid.i08, state->grid.i09, state->grid.i10);
	printf(" J%c%c%c%c%c%c%c%c%c%c\n", 
		state->grid.j01, state->grid.j02, state->grid.j03, state->grid.j04, state->grid.j05, 
		state->grid.j06, state->grid.j07, state->grid.j08, state->grid.j09, state->grid.j10);
}