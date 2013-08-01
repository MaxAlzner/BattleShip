#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#define BATTLESHIP_GRID_WIDTH 10

typedef struct BATTLESHIP_STATE
{
	uint size;
	uint playerID;
	char grid[BATTLESHIP_GRID_WIDTH * BATTLESHIP_GRID_WIDTH];
	uchar misslesTaken;
	uchar misslesIndices[BATTLESHIP_GRID_WIDTH * BATTLESHIP_GRID_WIDTH];
	uchar hits;
	uchar misses;

	bool allShipsPlaced;
	uchar carrierIndices[5];
	uchar battleshipIndices[4];
	uchar cruiserIndices[3];
	uchar destroyer1Indices[2];
	uchar destroyer2Indices[2];
	bool carrierDestroyed;
	bool battleshipDestroyed;
	bool cruiserDestroyed;
	bool destroyer1Destroyed;
	bool destroyer2Destroyed;
} BATTLESHIP_STATE;

extern void ClearGame(BATTLESHIP_STATE* state);
extern bool ValidGame(BATTLESHIP_STATE* state);

extern void PlaceCarrier(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
extern void PlaceBattleship(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
extern void PlaceCruiser(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
extern void PlaceDestroyer1(BATTLESHIP_STATE* state, uint x, uint y, bool flip);
extern void PlaceDestroyer2(BATTLESHIP_STATE* state, uint x, uint y, bool flip);

extern bool IsHit(BATTLESHIP_STATE* state, uint x, uint y);

extern bool AddMissle(BATTLESHIP_STATE* state, uint x, uint y);

#endif