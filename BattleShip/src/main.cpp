
#include "../include/main.h"

BATTLESHIP_STATE client;
BATTLESHIP_STATE server;

int main()
{
	ClearGame(&client);
	ClearGame(&server);

	PlaceCarrier(&client, 1, 2, false);
	PlaceCarrier(&client, 9, 3, true);

	PrintGame(&client, &server);

	_getch();
	return 0;
}