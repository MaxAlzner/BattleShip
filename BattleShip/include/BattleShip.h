#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

typedef struct BATTLESHIP_STATE
{
	uint size;
	uint playerID;

	struct
	{
		char a01, a02, a03, a04, a05, a06, a07, a08, a09, a10;
		char b01, b02, b03, b04, b05, b06, b07, b08, b09, b10;
		char c01, c02, c03, c04, c05, c06, c07, c08, c09, c10;
		char d01, d02, d03, d04, d05, d06, d07, d08, d09, d10;
		char e01, e02, e03, e04, e05, e06, e07, e08, e09, e10;
		char f01, f02, f03, f04, f05, f06, f07, f08, f09, f10;
		char g01, g02, g03, g04, g05, g06, g07, g08, g09, g10;
		char h01, h02, h03, h04, h05, h06, h07, h08, h09, h10;
		char i01, i02, i03, i04, i05, i06, i07, i08, i09, i10;
		char j01, j02, j03, j04, j05, j06, j07, j08, j09, j10;
	} grid;
	struct
	{
		uchar i0, i1, i2, i3, i4;
		uchar hits;
		bool destroyed;
		bool placed;
	} carrierInfo;
	struct
	{
		uchar i0, i1, i2, i3;
		uchar hits;
		bool destroyed;
		bool placed;
	} battleshipInfo;
	struct
	{
		uchar i0, i1, i2;
		uchar hits;
		bool destroyed;
		bool placed;
	} cruiserInfo;
	struct
	{
		uchar i0, i1;
		uchar hits;
		bool destroyed;
		bool placed;
	} destroyer1Info, destroyer2Info;
	
	uchar misslesTaken;
	uchar hits;
	uchar misses;
} BATTLESHIP_STATE;

extern void ClearGame(BATTLESHIP_STATE* state);
extern bool ValidGame(BATTLESHIP_STATE* state);

extern void GetCarrierIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1, uchar& i2, uchar& i3, uchar& i4);
extern void GetBattleshipIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1, uchar& i2, uchar& i3);
extern void GetCruiserIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1, uchar& i2);
extern void GetDestroyerIndices(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip, uchar& i0, uchar& i1);

extern void PlaceCarrier(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);
extern void PlaceBattleship(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);
extern void PlaceCruiser(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);
extern void PlaceDestroyer1(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);
extern void PlaceDestroyer2(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);

extern bool CanCarrierFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);
extern bool CanBattleshipFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);
extern bool CanCruiserFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);
extern bool CanDestroyerFit(BATTLESHIP_STATE* state, uchar x, uchar y, bool flip);

extern bool IsCarrierHere(BATTLESHIP_STATE* state, uchar x, uchar y);
extern bool IsBattleshipHere(BATTLESHIP_STATE* state, uchar x, uchar y);
extern bool IsCruiserHere(BATTLESHIP_STATE* state, uchar x, uchar y);
extern bool IsDestroyer1Here(BATTLESHIP_STATE* state, uchar x, uchar y);
extern bool IsDestroyer2Here(BATTLESHIP_STATE* state, uchar x, uchar y);

extern void RegisterCarrierHit(BATTLESHIP_STATE* state);
extern void RegisterBattleshipHit(BATTLESHIP_STATE* state);
extern void RegisterCruiserHit(BATTLESHIP_STATE* state);
extern void RegisterDestroyer1Hit(BATTLESHIP_STATE* state);
extern void RegisterDestroyer2Hit(BATTLESHIP_STATE* state);

extern bool IsHit(BATTLESHIP_STATE* state, uchar x, uchar y);

extern bool AddMissle(BATTLESHIP_STATE* state, uchar x, uchar y);

extern bool ParseCoordinate(char* buffer, uint size, uchar& x, uchar& y);
extern void PrintGame(BATTLESHIP_STATE* client, BATTLESHIP_STATE* other);
extern void PrintState(BATTLESHIP_STATE* state);

#endif