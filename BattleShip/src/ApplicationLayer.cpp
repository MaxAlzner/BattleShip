#include "../include/main.h"

#ifdef APPLICATIONLAYER_H_

BATTLESHIP_STATE local;
BATTLESHIP_STATE other;
GAME_STATE CurrentState = STATE_NONE;
bool StillRunning = true;
bool IsServer = false;

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
	printf("  Connecting to server\n");
	printf("\n");

	char* ip = new char[64];

	if (!MALib::HostConnection(20533, &ip))
	{
		printf("  Failed to start server\n");
		StillRunning = false;
	}
	else
	{
		printf("  IP ADDRESS : %s\n", ip);
		printf("  PORT : %d\n", 20533);
	}

	_getch();

	delete [] ip;
}
void WaitForClient()
{
	printf("\n");
	printf("  Waiting for opponent...\n");
	printf("\n");
	_getch();
}

void FindServer()
{
	printf("\n");
	printf("  Connecting to client\n");
	printf("\n");
	
	int port = 0;
	printf("  IP ADDRESS : ");
	fflush(stdin);
	scanf("%s", InputBuffer);
	printf("  PORT : ");
	fflush(stdin);
	scanf("%d", &port);
	printf("\n");
	
	if (!MALib::ConnectTo(20533, InputBuffer))
	{
		printf("  Failed to connect to server\n");
		StillRunning = false;
	}
	else
	{
		printf("  Successfully connected to server\n");
	}

	_getch();
}
void WaitForServer()
{
	printf("\n");
	printf("  Waiting for opponent...\n");
	printf("\n");
	_getch();
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

#endif