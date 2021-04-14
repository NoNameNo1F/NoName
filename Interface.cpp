#include "Interface.h"
#include <iostream>

using namespace std;
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}
void Menu() {
    //set colour and Menu
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    fstream file1("C:\\Users\\Admin\\Documents\\intro_poker.txt", ios::in);
    string Line;

    if (file1.fail()) {
        cout << "Can't open file \n";
    }
    else {
        while (!file1.eof()) {
            //getline(file1, writer);
            getline(file1, Line);
            for (int i = 0; i < Line.size(); i++) {

                if (Line[i] == 'P') {
                    SetConsoleTextAttribute(hStdout,1  );
                    cout << Line[i];

                }
                else if (Line[i] == 'O') {
                    SetConsoleTextAttribute(hStdout, 2);
                    cout << Line[i];
                }
                else if (Line[i] == 'K') {
                    SetConsoleTextAttribute(hStdout, 3);
                    cout << Line[i];
                }
                else if (Line[i] == 'E') {
                    SetConsoleTextAttribute(hStdout, 4);
                    cout << Line[i];
                }
                else if (Line[i] == 'R') {
                    SetConsoleTextAttribute(hStdout, 5);
                    cout << Line[i];
                }
                else {
                    SetConsoleTextAttribute(hStdout, 7);
                    cout << Line[i];
                }
            }

            //}
            cout << endl;
        }
        //cout << writer.str();
        file1.close();
    }
    // Menu and choose menu!!
    int choose;
    cout << "\t\t\t\t\t\t\t1.Play!!!" << endl;
    cout << "\t\t\t\t\t\t\t2.Game_Play!!!" << endl;
    cout << "\t\t\t\t\t\t\t3.Exit!!!" << endl;
    cin >> choose;
    switch (choose) {
        int switchback;
        case 1: {

            break;
        }
        case 2: {

            GamePlay();
            cout << "\t\t\t\t\t\tPress 1 to go to Menu!!!\n\t\t\t\t\t\t\t";
            cin >> switchback;
            if(switchback == 1)
                Menu();
            break;
        }
        case 3: {

            break;
        }
    }
 
}

/*void move(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor;
	Cursor.X = x;
	Cursor.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor); // DI CHUYEN 
}

void moveRight() {
	if (X < A[BOARDSIZE - 1][BOARDSIZE - 1].x) {
		X += 4;
		move(X, Y);
	}
}

void moveLeft() {
	if (X > A[0][0].x) {
		X -= 4;
		move(X, Y);
	}
}

void moveUp() {
	if (Y > A[0][0].y) {
		Y -= 2;
		move(X, Y);
	}
}

void moveDown() {
	if (Y < A[BOARDSIZE - 1][BOARDSIZE - 1].y) {
		Y += 2;
		move(X, Y);
	}
}*/
void GamePlay(){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    fstream file2("C:\\Users\\Admin\\Documents\\gameplay.txt", ios::in);
    string c;
    if (file2.fail()) {
        cout << "Can't open file \n";
    }
    else {
        cout << endl;
        while (!file2.eof()) {
            int i = 1;
            getline(file2, c);
            //for (i ; i < i + 1; i++) {
                SetConsoleTextAttribute(hStdout,7 );
                cout << c;
            //}
            cout << endl;
        }
        //cout << writer.str();
        file2.close();
    }
    SetConsoleTextAttribute(hStdout, 16);

}