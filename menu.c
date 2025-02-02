#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <regex.h>

#define HEIGHT 10
#define WIDTH 30
#define STR_Y 10
#define STR_X 84

const wchar_t *ascii[] = {
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡿⣫⣵⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣟⣹⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠓⠴⣿⣿⡿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣟⡝⣿⣛⢯⣾⣿⣿⣷⣿⣿⠟⢽⣚⣭⣶⣾⣶⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣯⣶⠝⣻⣿⣿⡟⢵⣲⣿⣿⣶⣽⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡷⢿⣾⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣷⣮⣤⣫⢿⣖⣢⣾⣿⣿⣽⣿⣿⣿⣿",
L"⣿⣿⡻⠟⢿⠛⠿⠻⢿⣿⣿⣿⡟⣟⠻⠿⢿⣿⣿⣿⣿⢻⡛⠿⠿⠿⣻⠻⠿⠿⢿⣿⡻⠿⢿⢷⠲⢶⡛⠟⠻⠿⢿⣿⣿⡿⣿⠽⢻⡿⡎⢻⣝⢿⢗⠫⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣷⢢⠀⢰⣶⣦⠀⠙⣟⡶⠋⣤⣴⣤⡀⠙⣟⣳⠊⣡⣴⣶⣤⡀⣿⣢⠀⢰⣾⣿⣷⢦⢠⣾⢦⠀⢰⣶⣶⣤⣸⣿⣿⢟⡟⠴⣺⣾⣽⢟⣋⣷⢸⣀⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣏⢿⠀⠘⠛⠊⣠⡼⡞⠀⢸⣿⣿⡿⣥⠀⢸⠃⠀⣿⣿⡻⢿⣿⠿⣼⠀⢸⣿⣿⣿⢺⢸⣿⢺⠀⢈⣁⡉⢹⣿⣿⡿⣟⣾⢻⣿⢟⠷⢭⣽⣿⢃⣫⠿⣹⣿⣿⣿⣽⣿⣿⣿",
L"⣿⣿⣟⢾⠀⢸⣷⠄⠈⢿⢦⠀⢸⣿⣿⢿⡹⠀⣸⡀⠀⣿⣿⡗⡆⠀⣶⣽⠀⢸⣿⣿⣭⡻⢸⣿⣩⠀⢰⣶⣾⣼⣿⣿⣟⣟⣿⣶⢿⣏⣿⣿⣳⡶⣰⣞⡿⡽⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣯⠞⠀⠸⢿⣿⡀⠈⢛⣆⡀⠙⠋⠚⣁⣴⣿⣧⣀⠈⠋⠙⢃⣠⣿⣿⣄⠀⠙⠙⠒⢁⣼⣷⠝⠀⠘⠫⠽⠎⢡⡿⣭⣿⣉⡕⡟⣍⣿⣿⡿⣿⢿⡛⣽⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣷⣶⣿⣿⣿⣿⣿⣿⣿⣶⣾⣿⣿⣿⣿⣿⣿⣶⡶⣿⣟⣿⣿⣿⣿⢿⡿⣿⢿⣾⣳⣧⢿⡿⣫⢎⣽⣿⣿⣿⣽⢸⢵⠸⣟⣷⣿⣿⣿⢿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣻⣿⣾⣿⣿⣿⣻⣿⣽⢯⢿⡿⢫⣿⣹⡿⣷⣯⣽⣛⣻⣷⣮⣫⣾⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣿⣿⣿⣷⣿⣿⣯⢲⣿⣿⣳⣿⣹⣿⣿⣿⣮⣭⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⢯⣿⢫⣿⣯⣿⢿⣯⣏⢣⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣯⣞⡎⣡⣯⣿⣶⣟⣿⢻⢽⣛⣿⢿⣿⣻⣿⣿⣽⣻⣿⣿⣿⣻⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣯⣿⣿⡿⣿⡿⣿⣷⣿⣟⡛⣧⣿⣼⣽⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣽⣻⣯⣷⣿⣷⣯⠿⢿⣿⣧⣿⣿⣿⣽⣿⣿⣿⣿⣯⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣽⣾⣿⣿⣿⣽⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
L"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
    };

void bazikon_menu(char* name_bazikon, int ted_bazi);

char* The_Name;

#include "map.c"

void first_page();


int add_email(char* s) {
    regex_t reegex;
    int value;
    value = regcomp(&reegex, "^[a-zA-Z][a-zA-Z0-9][a-zA-Z0-9]@[a-zA-Z].[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]$", 0);
    value = regexec(&reegex, s, 0, NULL, 0);
    if(value == REG_NOMATCH) {
        return 0;
    }
    return 1;
}

char* random_password() {
    char* res = (char*)malloc(20);
    int size = 10 + rand()%5;
    res[0] = rand()%26 + 65;
    res[1] = rand()%26 + 97;
    res[2] = rand()%10 + 48;
    for(int i = 3; i < size; i++) {
        int x = rand()%3;
        if(x == 0) {
            res[i] = rand()%26 + 65;
        }
        else if(x == 1) {
            res[i] = rand()%26 + 97;
        }
        else {
            res[i] = rand()%10 + 48;
        }
    }
    res[size] = '\0';
    return res;
}


int add_password(char* s) {
    if(strlen(s) < 7)
        return 0;
    int upper = 0;
    int lower = 0;
    int integer = 0;
    for(int i = 0; i < strlen(s); i++) {
        if(s[i] >= 65 && s[i] <= 90)
            upper = 1;
        if(s[i] >= 97 && s[i] <= 122)
            lower = 1;
        if(s[i] >= 48 && s[i] <= 57)
            integer = 1;
    }
    if((upper == 0) || (lower == 0) || (integer == 0))
        return 0;
    return 1;
}

int add_user(char* s) {
    FILE* fptr = fopen("data.txt", "r");
    char* c = (char*)malloc(1000);
    while(fscanf(fptr, "%s", c) == 1) {
        if(strcmp(c, s) == 0)
            return 0;
        fscanf(fptr, "%s", c);
        fscanf(fptr, "%s", c);
        int x;
        long int y;
        fscanf(fptr, " %d %d %d", &x, &x, &x);
        fscanf(fptr, " %ld", &y);
    }
    fclose(fptr);
    return 1;
}

void start_game(char* name_bazikon, int ted_bazi, int level, int player_x, int player_y) {
    refresh();
    clear();
    refresh();
    start_color();
    curs_set(0);
    load_map(name_bazikon, ted_bazi, level); 
    move_player(player_x, player_y, name_bazikon, ted_bazi, level);
    refresh();
    endwin();
}

void NEW_GAME(char* name_bazikon,  int ted_bazi) {
    curs_set(0);
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            visit[i][j] = 0;
            shown[i][j] = 0;
        }
    }
    make_new_game(name_bazikon, ted_bazi);
    load_map(name_bazikon, ted_bazi, 0);
    player_wealth = 0;
    player_hp = 100;
    player_hunger = 100; 
    clear();
    move_player(initial_x, initial_y, name_bazikon, ted_bazi, 0);
}

void LOAD_GAME(char* name_bazikon) {
    clear();
    FILE* fptr = fopen(The_Name, "r");
    char temp[100][100];
    int pos = 0;
    while(fscanf(fptr, "%s", temp[pos++]) == 1) {

    }
    pos--;
    for(int i = 0; i < pos; i++) {
        mvprintw(2 * i, 0, "> %s", temp[i]);
    }
    int pos_x = 0;
    while(true) {
        move(pos_x, 0);
        int ch = getch();
        if(ch == '2') {
            if(pos_x == 2 * (pos - 1)) {
                pos_x = 0;
            }
            else
                pos_x += 2;
        }
        if(ch == '8') {
            if(pos_x == 0) {
                pos_x = 2 * (pos - 1);
            }
            else
                pos_x -= 2;
        }
        if(ch == '\n') {
            FILE* mount = fopen(temp[pos_x/2], "r");
            int ted_bazi;
            int level;
            int player_x;
            int player_y;
            fscanf(mount, "%d %d %d %d %c %d %d", &player_x, &player_y, &ted_bazi, &level, &last_move, &player_color, &hardness);
            fscanf(mount, " %lf", &player_hp);
            fscanf(mount, " %lf", &player_hunger);
            fscanf(mount, " %lf", &player_wealth);
            fscanf(mount, " %d", &weapon);
            for(int i = 0; i < 3; i++)
                fscanf(mount, " %d", &food[i]);
            for(int i = 0; i < 5; i++)
                fscanf(mount, " %d", &aslahe[i]);
            for(int i = 0; i < 3; i++)
                fscanf(mount, " %d", &telesm[i]);
            fclose(mount);
            move(player_x, player_y * 2);
            start_game(temp[pos_x/2], ted_bazi, level, player_x, player_y);
            break;
        }
    }
}

void swp(int* x, int* y) {
    int z = *x;
    *x = *y;
    *y = z;
}

void setti() {
    clear();
    refresh();
    int pos_x = 2;
    while(1) {
        mvprintw(0, 0, "Color: ");
        mvprintw(2,0, "> 🔵");
        mvprintw(4, 0, "> 🔴");
        mvprintw(6, 0, "> 🟢");
        mvprintw(8, 0, "> 🟡");
        mvprintw(10, 0, "Hardness: ");
        mvprintw(12, 0, "> Easy ");
        mvprintw(14, 0, "> Normal ");
        mvprintw(16, 0, "> Hard ");
        noecho();
        move(pos_x, 0);
        int dmch = getch();
        if(dmch == '2') {
            if(pos_x == 16)
                pos_x = 2;
            else
                pos_x += 2;
            if(pos_x == 10)
                pos_x += 2;
        }
        if(dmch == '8') {
            if(pos_x == 2)
                pos_x = 16;
            else
                pos_x -= 2;
            if(pos_x == 10)
                pos_x -= 2;
        }
        move(pos_x, 0);
        if(dmch == '\n') {
            if(pos_x <= 8)
                player_color = (pos_x/2) - 1;
            if(pos_x >= 12)
                hardness = (pos_x - 12)/2;
        }
        if(dmch == 'q')
            break;
        refresh();
    }
    clear();
    refresh();
}

void scoreboard(char* name_bazikon, int page) {
    clear();
    refresh();
    FILE* fptr = fopen("data.txt", "r");
    int pos = 0;
    char name_user[100][100];
    char password[100][100];
    char email[100][100];
    int emtiaz[100];
    int tala[100];
    int ted[100];
    long int tm[100];
    while(fscanf(fptr, "%s %s %s %d %d %d %ld", name_user[pos], password[pos], email[pos], &emtiaz[pos], &tala[pos], &ted[pos], &tm[pos]) == 7) {
        pos++;
    }
    for(int j = 0; j < pos; j++) {
        for(int i = 0; i < pos - 1; i++) {
            int x = i;
            int y = i + 1;
            if(emtiaz[x] < emtiaz[y]) {
                char* tt = (char*)malloc(100);
                strcpy(tt, name_user[x]);
                strcpy(name_user[x], name_user[y]);
                strcpy(name_user[y], tt);

                strcpy(tt, password[x]);
                strcpy(password[x], password[y]);
                strcpy(password[y], tt);

                strcpy(tt, email[x]);
                strcpy(email[x], email[y]);
                strcpy(email[y], tt);

                swp(&emtiaz[x], &emtiaz[y]);
                swp(&ted[x], &ted[y]);
                swp(&tala[x], &tala[y]);

                long int z = tm[x];
                tm[x] = tm[y];
                tm[y] = z; 
            }
        }
    }
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    mvprintw(0, 0, "                     Rank           Name           Score           Gold           Num_Games           Experience");
    for(int i = page * 5; i < pos && i < page * 5 + 5; i++) {
        time_t okl = time(NULL);
        if(strcmp(name_user[i], name_bazikon) == 0 && i == 0) {
            attron(COLOR_PAIR(1));
            attron(A_BOLD);// "      The Legend       "
            mvprintw(2*(i%5 + 1), 0, "      The Legend >🥇  %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
            attroff(COLOR_PAIR(1));
            attroff(A_BOLD);
        }
        else if(strcmp(name_user[i], name_bazikon) == 0 && i == 1) {
            attron(COLOR_PAIR(2));
            attron(A_BOLD);
            mvprintw(2*(i%5 + 1), 0, "      The   Goat >🥈  %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
            attroff(COLOR_PAIR(2));
            attroff(A_BOLD);
        }
        else if(strcmp(name_user[i], name_bazikon) == 0 && i == 2) {
            attron(COLOR_PAIR(3));
            attron(A_BOLD);
            mvprintw(2*(i%5 + 1), 0, "      The Master >🥉  %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
            attroff(COLOR_PAIR(3));
            attroff(A_BOLD);
        }
        else if(i == 0) {
            attron(COLOR_PAIR(1));
            mvprintw(2*(i%5 + 1), 0, "      The Legend  🥇  %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
            attroff(COLOR_PAIR(1));
        }
        else if(i == 1) {
            attron(COLOR_PAIR(2));
            mvprintw(2*(i%5 + 1), 0, "      The   Goat  🥈  %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
            attroff(COLOR_PAIR(2));
        }
        else if(i == 2) {
            attron(COLOR_PAIR(3));
            mvprintw(2*(i%5 + 1), 0, "      The Master  🥉  %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
            attroff(COLOR_PAIR(3));
        }
        else if(strcmp(name_user[i], name_bazikon) == 0){
            attron(A_BOLD);
            mvprintw(2*(i%5 + 1), 0, "                   >  %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
            attroff(A_BOLD);
        }
        else {
            mvprintw(2*(i%5 + 1), 0, "                      %d              %s", i + 1, name_user[i]);
            mvprintw(2*(i%5 + 1), 52, "%d", emtiaz[i]);
            mvprintw(2*(i%5 + 1), 52 + 17, "%d", tala[i]);
            mvprintw(2*(i%5 + 1), 52 + 2*17, "%d", ted[i]);//okl - tm[i]
            mvprintw(2*(i%5 + 1), 52 + 3*17, "%ld s", okl - tm[i]);
        }
    }
    while(true) {
        int ch = getch();
        if(ch == 'q') {
            break;
        }
        if(ch == '6') {
            if((page + 1)*5 < pos) {
                scoreboard(name_bazikon, page + 1);
                break;
            }
        }
        if(ch == '4') {
            if(page > 0) {
                scoreboard(name_bazikon, page - 1);
                break;
            }
        }
    }
    clear();
    refresh();
    return;
}
void bazikon_menu(char* name_bazikon, int ted_bazi) {
    clear();
    curs_set(1);
    int pos_x = 0;
    while(1) {
        mvprintw(0, 0, "> New Game");
        mvprintw(2,0, "> Load Game");
        mvprintw(4, 0, "> Score Board");
        mvprintw(6, 0, "> Setting");
        mvprintw(8, 0, "> Profile");
        noecho();
        move(pos_x, 0);
        int dmch = getch();
        if(dmch == '2') {
            if(pos_x == 8)
                pos_x = 0;
            else
                pos_x += 2;
        }
        if(dmch == '8') {
            if(pos_x == 0)
                pos_x = 8;
            else
                pos_x -= 2;
        }
        move(pos_x, 0);
        if(dmch == '\n') {
            if(pos_x == 0) {
                NEW_GAME(name_bazikon, ted_bazi);
            }
            if(pos_x == 2) {
                FILE* fptr = fopen(The_Name, "r");
                if(fptr == NULL) {
                    refresh();
                    attron(COLOR_PAIR(1));
                    refresh();
                    mvprintw(8, 0, "You don't have any saved games!");
                    refresh();
                    attroff(COLOR_PAIR(1));
                    refresh();
                    napms(2000);
                    refresh();
                    clear();
                    refresh();
                    continue;
                }
                else {
                    fclose(fptr);
                    LOAD_GAME(name_bazikon);
                }
            }
            if(pos_x == 4) {
                scoreboard(name_bazikon, 0);
            }
            if(pos_x == 6) {
                setti();
            }
            if(pos_x == 8) {
                clear();
                FILE* fptr = fopen("data.txt", "r");
                char* temp = (char*)malloc(1000);
                while(fscanf(fptr, "%s", temp) == 1) {
                    if(strcmp(temp, name_bazikon) == 0) {
                        mvprintw(0, 0, "* User Name: %s", temp);
                        fscanf(fptr, "%s", temp);
                        mvprintw(2, 0, "* Password: %s", temp);
                        fscanf(fptr, "%s", temp);
                        mvprintw(4, 0, "* Password: %s", temp);
                        int x;
                        int teds;
                        long int y;
                        fscanf(fptr, "%d", &x);
                        mvprintw(6, 0, "* Score: %d", x);
                        fscanf(fptr, "%d", &x);
                        mvprintw(8, 0, "* Gold: %d", x);
                        fscanf(fptr, "%d", &x);
                        mvprintw(10, 0, "* Num_Games: %d", x);
                        fscanf(fptr, " %ld", &y);
                        time_t okl = time(NULL);
                        mvprintw(12, 0, "* Score: %ld s", okl - y);;
                    }
                    else {
                        fscanf(fptr, "%s", temp);
                        fscanf(fptr, "%s", temp);
                        int x;
                        long int y;
                        fscanf(fptr, " %d %d %d", &x, &x, &x);
                        fscanf(fptr, " %ld", &y);
                    }
                }
                fclose(fptr);
                while(1) {
                    int utd = getch();
                    if(utd == 'q') {
                        clear();
                        break;
                    }
                }
            }
        }
        refresh();
    }
}

void new_login() {
    clear();
    char* user_name = (char*)malloc(30);
    strcpy(user_name, " ");
    char* password = (char*)malloc(30);
    strcpy(password, " ");
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    int pos_x = 0;
    int ok_user = 0;
    int ok_pass = 0;
    char* ramzi = (char*)malloc(1000);
    strcpy(ramzi, " ");
    while(1) {
        mvprintw(0, 0, "> Username : %s", user_name);
        mvprintw(2,0, "> password : %s", password);
        mvprintw(4,0, "> forget password: %s", ramzi);
        mvprintw(6, 0, "> Login");
        mvprintw(8, 0, "> Login as guest");
        noecho();
        move(pos_x, 0);
        int dmch = getch();
        if(dmch == '2') {
            if(pos_x == 8)
                pos_x = 0;
            else
                pos_x += 2;
        }
        if(dmch == '8') {
            if(pos_x == 0)
                pos_x = 8;
            else
                pos_x -= 2;
        }
        move(pos_x, 0);
        if(dmch == '\n') {
            if(pos_x == 8) {
                char* temps = (char*)malloc(100);
                strcpy(temps, "guest");
                bazikon_menu(temps, 0);
            }
            if(pos_x == 0) {
                echo();
                mvprintw(0, 13, "                                        ");
                mvscanw(0, 13,"%s", user_name);
                ok_user = 1;
                move(2, 0);
            }
            if(pos_x == 2) {
                echo();
                mvprintw(2, 13, "                                        ");
                mvscanw(2, 13,"%s", password);
                ok_pass = 1;
                move(6, 0);
            }
            if(pos_x == 4) {
                if(ok_user) {
                    FILE* fptr = fopen("data.txt", "r");
                char* temp = (char*)malloc(1000);
                while(fscanf(fptr, "%s", temp) == 1) {
                    if(strcmp(temp, user_name) == 0) {
                        fscanf(fptr, "%s", temp);
                        strcpy(ramzi, temp);
                        break;
                    }
                    else {
                        fscanf(fptr, "%s", temp);
                        fscanf(fptr, "%s", temp);
                        int x;
                        long int y;
                        fscanf(fptr, " %d %d %d", &x, &x, &x);
                        fscanf(fptr, " %ld", &y);
                    }
                }
                fclose(fptr);
                }
            }
            if(pos_x == 6) {
                if(ok_pass && ok_user) {
                    FILE* fptr = fopen("data.txt", "r");
                    char* temp = (char*)malloc(1000);
                    char* temps = (char*)malloc(1000);
                    int oks = 0;
                    int teds;
                    while(fscanf(fptr, "%s", temp) == 1) {
                        if(strcmp(temp, user_name) == 0) {
                            oks = 1;
                            strcpy(temps, temp);
                            fscanf(fptr, "%s", temp);
                            if(strcmp(temp, password) == 0) {
                                oks = 2;
                            }
                            fscanf(fptr, "%s", temp);
                            int x;
                            long int y;
                            fscanf(fptr, " %d %d %d", &x, &x, &teds);
                            fscanf(fptr, " %ld", &y);
                        }
                        else {
                            fscanf(fptr, "%s", temp);
                            fscanf(fptr, "%s", temp);
                            int x;
                            long int y;
                            fscanf(fptr, " %d %d %d", &x, &x, &x);
                            fscanf(fptr, " %ld", &y);
                        }
                    }
                    if(oks == 0) {
                        refresh();
                        attron(COLOR_PAIR(1));
                        refresh();
                        mvprintw(10, 0, "Username not found!");
                        refresh();
                        attroff(COLOR_PAIR(1));
                        refresh();
                        napms(2000);
                        refresh();
                        clear();
                        refresh();
                        continue;
                        attroff(COLOR_PAIR(1));//Password is not correct!
                    }
                    if(oks == 1) {
                        refresh();
                        attron(COLOR_PAIR(1));
                        refresh();
                        mvprintw(10, 0, "Password is not correct!");
                        refresh();
                        attroff(COLOR_PAIR(1));
                        refresh();
                        napms(2000);
                        refresh();
                        clear();
                        refresh();
                        continue;
                        attroff(COLOR_PAIR(1));//Logined succesfully!
                    }
                    if(oks == 2) {
                        refresh();
                        attron(COLOR_PAIR(2));
                        refresh();
                        mvprintw(10, 0, "Logined succesfully!");
                        refresh();
                        attroff(COLOR_PAIR(2));
                        refresh();
                        napms(2000);
                        refresh();
                        clear();
                        refresh();
                        fclose(fptr);
                        strcpy(The_Name, temps);
                        bazikon_menu(temps, teds);
                    }
                    fclose(fptr);// "You haven't entered the information completely"
                }
                else {
                    refresh();
                        attron(COLOR_PAIR(1));
                        refresh();
                        mvprintw(10, 0, "You haven't entered the information completely");
                        refresh();
                        attroff(COLOR_PAIR(1));
                        refresh();
                        napms(2000);
                        refresh();
                        clear();
                        refresh();
                        continue;
                        attroff(COLOR_PAIR(1));
                }
                move(4, 0);
            }
        }
        refresh();
    }
}


void new_register() {
    clear();
    int c;
    char* user_name = (char*)malloc(30);
    strcpy(user_name, " ");
    char* password = (char*)malloc(30);
    strcpy(password, " ");
    char* email = (char*)malloc(50);
    strcpy(email, " ");
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    int ok_user = 0;
    int ok_pass = 0;
    int ok_email = 0;
    int ttp = 0;
    WINDOW *win = newwin(14, 50, 11, 6);
    int tx = 12;
    int ty = 8;
    int pos_x = tx;
    box(win, 0, 0); // ایجاد کادر دور پنجره
    refresh();
    while(1) {
        refresh();
        for(int i = 0; i < sizeof(ascii)/sizeof(ascii[0]); i++) {
            mvaddwstr(i, 65, ascii[i]);
        }
    refresh();
        werase(win);
        box(win, 0, 0);
        wrefresh(win);
        mvprintw(0 + tx, 0 + ty, "> Username : %s", user_name);
        mvprintw(2 + tx, 0 + ty, "> Suggest New Password");
        mvprintw(4 + tx,0 + ty, "> password : %s", password);
        mvprintw(6 + tx, 0 + ty, "> email : %s", email);
        mvprintw(8 + tx, 0 + ty, "> Register");
        noecho();
        move(pos_x, ty);
        int dmch = getch();
        if(dmch == '2') {
            if(pos_x == 8 + tx)
                pos_x = 0 + tx;
            else
                pos_x += (2);
        }
        if(dmch == '8') {
            if(pos_x == 0 + tx)
                pos_x = 8 + tx;
            else
                pos_x -= 2;
        }
        move(pos_x + tx, 0 + ty);
        if(dmch == '\n') {
            if(pos_x == 0 + tx) {
                echo();
                mvprintw(0 + tx, 13 + ty, "                             ");
                mvscanw(0 + tx, 13 + ty,"%s", user_name);
                if(add_user(user_name) == 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(10 + tx, 0 + ty, "username already taken");
                    attroff(COLOR_PAIR(1));
                    strcpy(user_name, " ");
                    refresh();
                    napms(1500);
                    clear();
                    continue;
                    refresh();
                }
                else {
                    ok_user = 1;
                }
                move(2 + tx, 0 + ty);
            }
            if(pos_x == 2 + tx) {
                password = random_password();
                move(4 + tx, 0 + ty);
                ok_pass = 1;
            }
            if(pos_x == 4 + tx) {
                echo();
                mvprintw(4 + tx, 13 + ty, "                            ");
                mvscanw(4 + tx, 13 + ty,"%s", password);
                if(add_password(password) == 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(9 + tx, 0 + ty, "Password must be at least 7 characters,");
                    mvprintw(10 + tx, 0 + ty, "contain a digit number,");
                    mvprintw(11 + tx, ty, "a Capital letter and a lowercase letter");
                    attroff(COLOR_PAIR(1));
                    strcpy(password, " ");
                    refresh();
                    napms(1500);
                    clear();
                    continue;
                    refresh();
                }
                else {
                    ok_pass = 1;
                }
                move(6 + tx, 0 + ty);
            }
            if(pos_x == 6 + tx) {
                echo();
                mvprintw(6 + tx, 10 + ty, "                                 ");
                mvscanw(6 + tx, 10 + ty,"%s", email);
                if(add_email(email) == 0) {
                    attron(COLOR_PAIR(1));
                    mvprintw(10 + tx, 0 + ty, "Invalid email");
                    attroff(COLOR_PAIR(1));
                    strcpy(email, " ");
                    refresh();
                    napms(1500);
                    clear();
                    continue;
                    refresh();
                }
                else {
                    ok_email = 1;
                }
                move(8 + tx, 0 + ty);
            }
            if(pos_x == 8 + tx) {
                if(ok_email && ok_pass && ok_user) {
                    attron(COLOR_PAIR(2));
                    mvprintw(10 + tx, 0 + ty, "New User added sucessfully");
                    refresh();
                    napms(2500);
                    refresh();
                    attroff(COLOR_PAIR(2));
                    FILE* fptr1 = fopen("data.txt", "a+");// emtiaz tala ted_bazi zaman
                    time_t st = time(NULL);
                    fprintf(fptr1, "%s %s %s %d %d %d %ld\n", user_name, password, email, 0, 0, 0, (long)(st));
                    fclose(fptr1);
                    first_page();
                    break;
                }
                else {
                    attron(COLOR_PAIR(1));
                    mvprintw(10 + tx, 0 + ty, "You haven't entered the information completely");
                    attroff(COLOR_PAIR(1));
                }
                move(8 + tx, 0 + ty);
            }
        }
        refresh();
    }
    delwin(win);
    endwin();
}

void first_page() {
    curs_set(0);
    noecho(); 
    clear();
    refresh();
    for(int i = 0; i < sizeof(ascii)/sizeof(ascii[0]); i++) {
        mvaddwstr(i, 0, ascii[i]);
    }
    init_pair(1, COLOR_BLACK, COLOR_WHITE); 
    init_pair(2, COLOR_WHITE, COLOR_BLACK); 
    WINDOW *win = newwin(HEIGHT, WIDTH, STR_Y, STR_X);
    box(win, 0, 0); 
    const char *text1 = "Register";
    const char *text2 = "Login";
    int current_option = 0;
    curs_set(0);
    while (1) {
        refresh();
    for(int i = 0; i < sizeof(ascii)/sizeof(ascii[0]); i++) {
        mvaddwstr(i, 0, ascii[i]);
    }
    refresh();
        werase(win);
        box(win, 0, 0);
        if (current_option == 0) {
            wattron(win, COLOR_PAIR(1)); 
            mvwprintw(win, HEIGHT / 2 - 1, (WIDTH - strlen(text1)) / 2, "%s", text1);
            wattroff(win, COLOR_PAIR(1));
            wattron(win, COLOR_PAIR(2)); 
            mvwprintw(win, HEIGHT / 2 + 1, (WIDTH - strlen(text2)) / 2, "%s", text2);
            wattroff(win, COLOR_PAIR(2));
        } else {
            wattron(win, COLOR_PAIR(2)); 
            mvwprintw(win, HEIGHT / 2 - 1, (WIDTH - strlen(text1)) / 2, "%s", text1);
            wattroff(win, COLOR_PAIR(2));
            wattron(win, COLOR_PAIR(1)); 
            mvwprintw(win, HEIGHT / 2 + 1, (WIDTH - strlen(text2)) / 2, "%s", text2);
            wattroff(win, COLOR_PAIR(1));
        }

        wrefresh(win);
        int ch = getch();
        if (ch == '8') {
            current_option = (current_option == 0) ? 1 : 0; 
        } 
        else if (ch == '2') {
            current_option = (current_option == 1) ? 0 : 1; 
        } 
        else if (ch == '\n') { 
            if(current_option == 0) {
                curs_set(1);
                echo();
                clear();
                new_register();
                break;
            }
            else {
                curs_set(1);
                echo();
                clear();
                new_login();
                break;
            }
        }
        else if(ch == 'q') {
            break;
        }
    }
    delwin(win); 
    endwin();
}



int main() {
    The_Name = (char*)malloc(1000);
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    srand(time(NULL));
    keypad(stdscr, TRUE);
    first_page();
}



