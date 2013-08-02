
#include "../include/main.h"

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

BATTLESHIP_STATE local;
BATTLESHIP_STATE other;
GAME_STATE CurrentState = STATE_NONE;
bool StillRunning = true;
bool IsServer = false;

#define InputBufferSize 64
char InputBuffer[InputBufferSize];

void PlaceShips()
{
	PrintState(&local);
	if (!local.carrierInfo.placed) printf("  Placing Aircaft Carrier (5)\n");
	else if (!local.battleshipInfo.placed) printf("  Placing Destroyer (4)\n");
	else if (!local.cruiserInfo.placed) printf("  Placing Cruiser (3)\n");
	else if (!local.destroyer1Info.placed || !local.destroyer2Info.placed) printf("  Placing Destroyer (2)\n");
	printf("  Enter Coordinate : ");

	uchar x, y = 0;
	bool flip = false;

	fflush(stdin);
	scanf("%s", InputBuffer);
	bool result = ParseCoordinate(InputBuffer, InputBufferSize, x, y);
	printf("  Flip? (y/n) : ");
	char answer;
	fflush(stdin);
	scanf("%c", &answer);
	if (answer == 'y' || answer == 'Y') flip = true;

	if (!local.carrierInfo.placed)
	{
		if (CanCarrierFit(&local, x, y, flip))
		{
			PlaceCarrier(&local, x, y, flip);
		}
		else result = false;
	}
	else if (!local.battleshipInfo.placed)
	{
		if (CanBattleshipFit(&local, x, y, flip))
		{
			PlaceBattleship(&local, x, y, flip);
		}
		else result = false;
	}
	else if (!local.cruiserInfo.placed)
	{
		if (CanCruiserFit(&local, x, y, flip))
		{
			PlaceCruiser(&local, x, y, flip);
		}
		else result = false;
	}
	else if (!local.destroyer1Info.placed)
	{
		if (CanDestroyerFit(&local, x, y, flip))
		{
			PlaceDestroyer1(&local, x, y, flip);
		}
		else result = false;
	}
	else if (!local.destroyer2Info.placed)
	{
		if (CanDestroyerFit(&local, x, y, flip))
		{
			PlaceDestroyer2(&local, x, y, flip);
		}
		else result = false;
	}
	
	if (!result)
	{
		printf("\n");
		printf("  Incorrect Coordinate\n");
		_getch();
		return;
	}

	if (local.carrierInfo.placed && local.battleshipInfo.placed && local.cruiserInfo.placed && local.destroyer1Info.placed && local.destroyer2Info.placed)
	{
		CurrentState = STATE_CHOOSE_PLAYMODE;
	}
}
void ChoosePlayMode()
{
	printf("\n");
	printf("  (1). Host Game\n");
	printf("  (2). Join Game\n");
	printf("\n");

	printf("  >> ");
	int option = -1;
	fflush(stdin);
	scanf("%d", &option);

	switch (option)
	{
	case 1:
		CurrentState = STATE_CREATE_SERVER;
		IsServer = true;
		return;
	case 2:
		CurrentState = STATE_FIND_SERVER;
		return;

	default:
		break;
	}

	printf("  Incorrect Option\n");
	_getch();
}

void CreateServer()
{
	printf("\n");
	printf("  I am the server\n");
}
void WaitForClient()
{
}

void FindServer()
{
	printf("\n");
	printf("  I am the client\n");
}
void WaitForServer()
{
}

void SendMove()
{
}
void WaitingForMove()
{
}

void WinScreen()
{
	printf("\n");
	printf("  You won the game\n");
	printf("\n");
	_getch();
}
void LoseScreen()
{
	printf("\n");
	printf("  You lost the game\n");
	printf("\n");
	_getch();
}
void InvalidGame()
{
	printf("\n");
	printf("  Invalid game\n");
	printf("\n");
	_getch();
}

int main()
{
	ClearGame(&local);
	ClearGame(&other);
	CurrentState = STATE_PLACE_SHIPS;

	while (StillRunning)
	{
		system("cls");
		switch (CurrentState)
		{
		case STATE_PLACE_SHIPS:
			PlaceShips();
			break;
		case STATE_CHOOSE_PLAYMODE:
			ChoosePlayMode();
			break;
			
		case STATE_CREATE_SERVER:
			CreateServer();
			break;
		case STATE_WAIT_FOR_CLIENT:
			WaitForClient();
			break;

		case STATE_FIND_SERVER:
			FindServer();
			break;
		case STATE_WAIT_FOR_SERVER:
			WaitForServer();
			break;

		case STATE_SENDING_MOVE:
			SendMove();
			break;
		case STATE_WAITING_FOR_MOVE:
			WaitingForMove();
			break;

		case STATE_WIN_SCREEN:
			WinScreen();
			break;
		case STATE_LOSE_SCREEN:
			LoseScreen();
			break;
		case STATE_INVALID_GAME:
			InvalidGame();
			break;

		default:
			StillRunning = false;
			break;
		}
	}

	return 0;
}