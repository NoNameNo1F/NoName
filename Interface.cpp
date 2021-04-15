#include "Interface.h"

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
                    SetConsoleTextAttribute(hStdout,1 );
                    cout << Line[i];

                }
                else if (Line[i] == 'O') {
                    SetConsoleTextAttribute(hStdout, 4);
                    cout << Line[i];
                }
                else if (Line[i] == 'K') {
                    SetConsoleTextAttribute(hStdout, 2);
                    cout << Line[i];
                }
                else if (Line[i] == 'E') {
                    SetConsoleTextAttribute(hStdout, 6);
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
    SetConsoleTextAttribute(hStdout, 2);
    cout << "\t\t\t\t\t\t\t\t\t\t\t1.Play!!!" << endl;
    SetConsoleTextAttribute(hStdout, 4);
    cout << "\t\t\t\t\t\t\t\t\t\t\t2.Game_Play!!!" << endl;
    SetConsoleTextAttribute(hStdout, 6);
    cout << "\t\t\t\t\t\t\t\t\t\t\t3.Exit!!!" << endl;
    SetConsoleTextAttribute(hStdout, 228);
    cout << "\t\t\t\t\t\t\t\t\t\t\tYour's choice is: ";
    cin >> choose;
    SetConsoleTextAttribute(hStdout, 7);
    switch (choose) {
        int switchback;
        case 1: {
            system("cls");
            SetConsoleTextAttribute(hStdout, 1);
            
            break;
        }
        case 2: {
            system("cls");
            GamePlay();
            cout << "\t\t\t\t\t\t\t\t\t\t\tPress 1 to go back Menu!!!\n\t\t\t\t\t\t\t\n";
            cout << "\t\t\t\t\t\t\t\t\t\t\tYour's choice is: ";
            cin >> switchback;
            if (switchback == 1)
                system("cls");
                Menu();
            break;
        }
        case 3: {
            cout << "\n\t\t\t\t\t\t\t\t\t\t\t --END GAME-- \n";
            SetConsoleTextAttribute(hStdout, 0);
            exit(0);
            break;
        }
    }

 
}

void GamePlay(){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    fstream file2("C:\\Users\\Admin\\Documents\\gameplay.txt", ios::in);
    string c;
    if (file2.fail()) {
        cout << "Can't open file \n";
    }
    else {
        cout << endl;
        int i = 1;
        while (!file2.eof()) {
            getline(file2, c);
            if (i == 16)
                i -=15;
            SetConsoleTextAttribute(hStdout,i );
            cout << c;
            
            cout << endl;
            i++;
        }
        //cout << writer.str();
        file2.close();
    }
    SetConsoleTextAttribute(hStdout, 14);

}

void MoveCenter()
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    int posx, posy;
    posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
        posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,

        MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}