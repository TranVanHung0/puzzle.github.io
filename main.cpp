#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include<Windows.h>
using namespace std;
const int row = 3;
const int column = 3;
const int white_char = 0;
const char blank_char = ' ';

int board[row][column];
void print_puzzle(){

cout <<      "\t\t\t\t  ____    _   _  ______  _____  _      _____ \n"
             "\t\t\t\t |  _  | | | | | |__  / |__  / | |    |  ___|\n"
             "\t\t\t\t | |_) | | | | |   / /    / /  | |    | |___ \n"
             "\t\t\t\t |  __/  | | | |  / /    / /   | |    |  ___|\n"
             "\t\t\t\t\ | |     | | | | / /_   / /_   | |__  | |___ \n"
             "\t\t\t\t |_|    \   \___/ /____| /____|  |____| |_____|";
}
void TextColor(int x){
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
void HideCursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

}
void gotoxy(int x,int y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(h, a);
}
void TargetBoard() {
    int value = 1;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            board[i][j] = value++;
        }
    }
    board[row - 1][column - 1] = white_char;
}
void MixTable() {
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            int randomRow = rand() % row;
            int randomCol = rand() % column;

            swap(board[i][j], board[randomRow][randomCol]);
        }
    }
}
void printBoard() {
    // Ke bang hang dau
    for (int i = 0; i < column; ++i) {
        cout << "+-----";
    }
    cout << "+\n";

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            cout << "|  ";
            if (board[i][j] != white_char) {
                cout << board[i][j];
            } else {
                cout << blank_char;
            }
            cout << "  ";
        }

        cout << "|\n";

        // Duong xen ke giua hai hang
        for (int j = 0; j < column; ++j) {
            cout << "+-----";
        }
        cout << "+\n";
    }
}
bool isSolved() {
    int value = 1;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (board[i][j] != value++ && !(i == row - 1 && j == column - 1)) {
                return false;
            }
        }
    }
    return true;
}
bool isValidMove(int emptyRow, int emptyCol, int tileRow, int tileCol) {
    return ((abs(emptyRow - tileRow) == 1 && emptyCol == tileCol) ||
            (abs(emptyCol - tileCol) == 1 && emptyRow == tileRow));
}
void moveTile(int& emptyRow, int& emptyCol, int tileRow, int tileCol) {
    swap(board[emptyRow][emptyCol], board[tileRow][tileCol]);
    emptyRow = tileRow;
    emptyCol = tileCol;
}
void Introduct(){
    HideCursor();
    while(true){
        for(int x=14;x>0;x--)
        {
            TextColor(x);
            print_puzzle();
            Sleep(500);
            system("cls");
        }
        TextColor(14);
        print_puzzle();
        cout<<endl;
        TextColor(2);
        gotoxy(50,8);
        cout<<"BT92\n";
        Sleep(500);
        gotoxy(47,9);
        cout<<"Lu Van Chuan\n";
        Sleep(500);
        gotoxy(47,10);
        cout<<"Tran Van Hung\n";
        Sleep(500);
        gotoxy(47,11);
        cout<<"Tran Dinh Thien Nhan\n\n\n";
        Sleep(500);
        TextColor(14);
        gotoxy(43,14);
        cout<<"Press SPACEBAR to continue...";
        if(_getch()==32)
            break;
        }
        system("cls");
}
void ActiveGame(){
    HideCursor();
    TargetBoard();
    MixTable();
    int emptyRow, emptyCol;

    // Tim vi tri o trong
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (board[i][j] == white_char) {
                emptyRow = i;
                emptyCol = j;
            }
        }
    }

    while (true) {
        system("cls");
        printBoard();
        if (isSolved()) {
            system("cls");
            TextColor(12);
            cout << "\nCONGRATULATIONS\n";
            Sleep(2000);
            break;
        }
        int key = _getch();
        int selectedRow = emptyRow;
        int selectedCol = emptyCol;

        // Phim dieu khien
        switch (key) {
            case 72: // mui ten len
                selectedRow = emptyRow + 1;
                break;
            case 80: // mui ten xuong
                selectedRow = emptyRow - 1;
                break;
            case 75: // mui ten trai
                selectedCol = emptyCol + 1;
                break;
            case 77: //mui ten phai
                selectedCol = emptyCol - 1;
                break;
            case 32: // Phím spacebar
                system("cls");
                TextColor(12);
                cout << "\nTHANKS FOR FOLLOWING OUR PROJECT <3\n";
                Sleep(5000);
                break;
            case 8:
                system("cls");
                TextColor(12);
                cout << "\nTHANKS FOR FOLLOWING OUR PROJECT <3\n";
                Sleep(5000);
                break;
        }
        if (selectedRow >= 0 && selectedRow < row && selectedCol >= 0 && selectedCol < column &&
            isValidMove(emptyRow, emptyCol, selectedRow, selectedCol)) {
            moveTile(emptyRow, emptyCol, selectedRow, selectedCol);
        }
        if(key==8 || key==32)
            break;
    }
}
void Menu(){
    HideCursor();
    Introduct();
    bool return_menu =true;
    while(return_menu==true){
    system("cls");
    TextColor(14);
    cout<<"Press 1:     START GAMES\n";
    cout<<"Press 2:        HELP\n";
    cout<<"Press SPACEBAR: EXIT";
    int menu_key = _getch();
    switch(menu_key){
    case 49://phim so 1
        system("cls");
        ActiveGame();
       break;
    case 50: //phim so 2
        system("cls");
        cout<<"Su dung nhung phim mui ten de di chuyen\n";
        cout<<"Muon thoat khoi tro choi an phim SAPCEBAR hoac BACKSPACE\n";
        cout<<"\n\tPress any key...";
        _getch();
        break;
    case 32: //phim SAPCEBAR
        system("cls");
        return_menu = false;
        break;
    }
    }
}
int main() {
Menu();
}
