#include "../include/main.h"

#ifdef APPLICATIONLAYER_H_

BATTLESHIP_STATE local;
BATTLESHIP_STATE other;
GAME_STATE CurrentState = STATE_NONE;
bool StillRunning = true;
bool IsServer = false;
bool WonGame = false;

char* ServerIP = 0;
uint ServerPort = 20533;

static char* HitMessage = "That was a hit";
static char* MissMessage = "That was a miss";
static char* LoseMessage = "All my ships have been destroyed";

char InputBuffer[InputBufferSize];

void ClearInputBuffer()
{
	memset(InputBuffer, 0, InputBufferSize * sizeof(char));
}

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
	printf("  Vertical? (y/n) : ");
	char answer;
	fflush(stdin);
	scanf("%c", &answer);
	fflush(stdin);
	if (answer == 'y' || answer == 'Y') flip = true;
	
	if (!result)
	{
		printf("\n");
		printf("  Incorrect Coordinate\n");
		_getch();
		return;
	}

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
	fflush(stdin);

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
	MALib::SOCK_Initialize(true);

	if (!MALib::SOCK_HostConnection(20533, &ServerIP))
	{
		printf("\n");
		printf("  Failed to start server\n");
		StillRunning = false;
		_getch();
	}
	else
	{
		CurrentState = STATE_WAIT_FOR_CLIENT;
	}
}
void WaitForClient()
{
	printf("\n");
	printf("  Waiting for opponent...\n");
	printf("\n");
	printf("  IP ADDRESS : %s\n", ServerIP);
	printf("  PORT : %d\n", ServerPort);
	printf("\n");
	
	if (MALib::SOCK_AcceptConnection())
	{
		printf("  Found client\n");
		CurrentState = STATE_EXCHANGE_MOVES;
		_getch();
	}
}

void FindServer()
{
	MALib::SOCK_Initialize(false);
	printf("\n");
	printf("  Connecting to server\n");
	printf("\n");
	
	int port = 0;
	printf("  IP ADDRESS : ");
	fflush(stdin);
	scanf("%s", InputBuffer);
	printf("  PORT : ");
	fflush(stdin);
	scanf("%d", &port);
	fflush(stdin);
	printf("\n");
	
	if (!MALib::SOCK_ConnectTo(port, InputBuffer))
	{
		printf("  Failed to connect to server\n");
		StillRunning = false;
		_getch();
	}
	else
	{
		CurrentState = STATE_WAIT_FOR_SERVER;
	}
}
void WaitForServer()
{
	//printf("\n");
	//printf("  Waiting for opponent...\n");
	//printf("\n");

	CurrentState = STATE_EXCHANGE_MOVES;

	//_getch();
}

void ExchangeMoves()
{
	PrintGame(&local, &other);
	printf("  Enter Coordinate : ");
	uchar x, y = 0;

	fflush(stdin);
	scanf("%s", InputBuffer);
	fflush(stdin);
	printf("\n");
	if (!ParseCoordinate(InputBuffer, InputBufferSize, x, y) || !ValidTarget(&other, x, y))
	{
		printf("  Incorrect Coordinate\n");
		_getch();
		return;
	}

	printf("  Sending Coordinate\n");
	MALib::SOCK_Send(InputBuffer, InputBufferSize);
	ClearInputBuffer();
	MALib::SOCK_Receive(InputBuffer, InputBufferSize);
	printf("  Recieved Coordinate : %s\n", InputBuffer);

	uchar ox, oy = 0;
	if (!ParseCoordinate(InputBuffer, InputBufferSize, ox, oy))
	{
		printf("  Recieved Invalid Coordinate\n");
		_getch();
		return;
	}

	bool wasHit = AddMissle(&local, ox, oy);

	char* localField = (char*)&(local.gridWithoutShips);
	char* otherField = (char*)&(other.gridWithoutShips);
	MALib::SOCK_Send(localField, local.gridLength);
	MALib::SOCK_Receive(otherField, other.gridLength);

	if (local.carrierInfo.destroyed && local.battleshipInfo.destroyed && local.cruiserInfo.destroyed && local.destroyer1Info.destroyed && local.destroyer2Info.destroyed)
	{
		MALib::SOCK_Send(LoseMessage, strlen(LoseMessage));
		CurrentState = STATE_LEAVING_GAME;
	}
	else
	{
		if (wasHit) MALib::SOCK_Send(HitMessage, strlen(HitMessage));
		else MALib::SOCK_Send(MissMessage, strlen(MissMessage));
	}
	
	ClearInputBuffer();
	MALib::SOCK_Receive(InputBuffer, InputBufferSize);
	printf("  %s\n", InputBuffer);

	if (strcmp(LoseMessage, InputBuffer) == 0)
	{
		CurrentState = STATE_WIN_SCREEN;
	}

	_getch();
}
void LeavingGame()
{
	if (IsServer) MALib::SOCK_CloseConnection();
	MALib::SOCK_Uninitialize();

	if (WonGame) CurrentState = STATE_WIN_SCREEN;
	else CurrentState = STATE_LOSE_SCREEN;
}

void WinScreen()
{
	printf("\n");
	printf("  You won the game\n");
	printf("\n");
	StillRunning = false;
	_getch();
}
void LoseScreen()
{
	printf("\n");
	printf("  You lost the game\n");
	printf("\n");
	StillRunning = false;
	_getch();
}
void InvalidGame()
{
	printf("\n");
	printf("  Invalid game\n");
	printf("\n");
	StillRunning = false;
	_getch();
}

#endif