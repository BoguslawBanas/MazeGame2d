#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "../header_files/labirynth.h"

unsigned long long hash(char s[]){
    int i=0;
    unsigned long long result=1;
    while(s[i]!='\0'){
        result*=(5*s[i])+37;
        ++i;
    }
    return result;
}

int main(){
    system("cls");
    char seed[64];
    unsigned size;
    unsigned long long hashed_value;
    printf("Podaj ziarno do generatora: ");
    scanf("%s", seed);
    hashed_value=hash(seed);
    printf("Podaj rozmiar labiryntu: ");
    scanf("%u", &size);
    size|=1;
    srand(hashed_value);

    system("cls");

    Labirynth *labirynth=createLabirynth(size);

    printLabirynth(labirynth);

    COORD coord;
    bool is_win=false;
    coord.X=labirynth->start_point_x;
    coord.Y=labirynth->start_point_y;
    printf("%d %d", coord.X, coord.Y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    int c=getch();
    while(c!=27){ //27==ESC
        switch(c){
            case 'a':{
                if(labirynth->labirynth[coord.Y][coord.X-1]!='#'){
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    printf(" ");
                    --coord.X;
                }
            }break;
            case 'w':{
                if(labirynth->labirynth[coord.Y-1][coord.X]!='#'){
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    printf(" ");
                    --coord.Y;
                }
            }break;
            case 's':{
                if(labirynth->labirynth[coord.Y+1][coord.X]!='#'){
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    printf(" ");
                    ++coord.Y;
                }
            }break;
            case 'd':{
                if(labirynth->labirynth[coord.Y][coord.X+1]!='#'){
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    printf(" ");
                    ++coord.X;
                }
            }break;
        }
        if(labirynth->labirynth[coord.Y][coord.X]=='E'){
            is_win=true;
            break;
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("P");
        c=getch();
    }

    system("cls");
    deleteLabirynth(labirynth);
    if(is_win){
        printf("YOU WIN\n");
    }
    return 0;
}