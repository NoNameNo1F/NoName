#include <iostream>
#include "Table.h"
#include "Player.h"
#include "Interface.h"
#include<windows.h>

using namespace std;

int main()
{
	//rectangle(20, 20, 500, 200);
	Table t1;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	//MoveCenter();
	ShowCur(0);
	Menu();
	
	t1.playGame();
	//return 0;

	system("pause");
}