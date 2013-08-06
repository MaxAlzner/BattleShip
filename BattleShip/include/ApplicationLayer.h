#ifndef APPLICATIONLAYER_H_
#define APPLICATIONLAYER_H_

enum GAME_STATE
{
	STATE_NONE                 = 0x00000000, 
	STATE_PLACE_SHIPS          = 0x00000001, 
	STATE_CHOOSE_PLAYMODE      = 0x00000002, 
	STATE_CREATE_SERVER        = 0x00000010, 
	STATE_WAIT_FOR_CLIENT      = 0x00000020, 
	STATE_FIND_SERVER          = 0x00000100, 
	STATE_WAIT_FOR_SERVER      = 0x00000200, 
	STATE_SENDING_MOVE         = 0x00001000, 
	STATE_WAITING_FOR_MOVE     = 0x00002000, 
	STATE_WIN_SCREEN           = 0x00010000, 
	STATE_LOSE_SCREEN          = 0x00020000, 
	STATE_INVALID_GAME         = 0x00030000, 
};

#define InputBufferSize 64

extern BATTLESHIP_STATE local;
extern BATTLESHIP_STATE other;
extern GAME_STATE CurrentState;
extern bool StillRunning;
extern bool IsServer;

extern char InputBuffer[InputBufferSize];

void PlaceShips();
void ChoosePlayMode();

void CreateServer();
void WaitForClient();

void FindServer();
void WaitForServer();

void SendMove();
void WaitingForMove();

void WinScreen();
void LoseScreen();
void InvalidGame();

#endif