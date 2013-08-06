
#include "../include/main.h"

int main()
{
	MALib::InitializeSock();
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

	MALib::UninitializeSock();
	return 0;
}