
#include "../include/main.h"

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

		case STATE_EXCHANGE_MOVES:
			ExchangeMoves();
			break;
		case STATE_LEAVING_GAME:
			LeavingGame();
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