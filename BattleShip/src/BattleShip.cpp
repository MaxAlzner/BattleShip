#include "../include/main.h"

void ClearGame(BATTLESHIP_STATE* state)
{
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
}

void PlaceCarrier(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
void PlaceBattleship(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
void PlaceCruiser(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
void PlaceDestroyer1(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
void PlaceDestroyer2(BATTLESHIP_STATE* state, uint x, uint y, bool flip);

bool IsHit(BATTLESHIP_STATE* state, uint x, uint y);

bool AddMissle(BATTLESHIP_STATE* state, uint x, uint y);