
#include <stdio.h>
#include <conio.h>

#include "..\include\MALib_sock.h"

int main()
{
	char* ip = 0;

	MALib::InitializeSock();

	MALib::HostConnection(20533, &ip);
	printf("HOST IP : %s\n", ip);
	printf("PORT NUM : %d\n", 20533);

	MALib::UninitializeSock();

	_getch();
	return 0;
}