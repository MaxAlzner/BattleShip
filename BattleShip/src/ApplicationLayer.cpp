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
	fflush(stdin);
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
	
	if (!MALib::SOCK_ConnectTo(ServerPort, InputBuffer))
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
	printf("\n");
	printf("  Waiting for opponent...\n");
	printf("\n");

	CurrentState = STATE_EXCHANGE_MOVES;

	_getch();
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
	if (!ParseCoordinate(InputBuffer, InputBufferSize, x, y))
	{
		printf("  Incorrect Coordinate\n");
		_getch();
		return;
	}

	CurrentState = STATE_LEAVING_GAME;
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