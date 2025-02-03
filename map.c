#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

void save_map(char* name_bazicon, int ted_bazi, int level);
void load_map(char* name_bazicon, int ted_bazi, int level);

struct room {
    int x;
    int y;
    int lenth;
    int width;
    char mapc[40][40];
    int p_x[2];
    int p_y[2];
};

struct monsters {
    int x;
    int y;
    int kind;
    int alive;
    int dist;
    int damage;
    int hp;
    int active;
};

struct monsters monster[50];
int tot_monster = 0;

int food[3];
int aslahe[5];
int weapon = 0;
int telesm[3];

int tel_hp = 0;
int tel_speed = 0;
int tel_power = 0;

struct room rm[8];

time_t now, then;
time_t now_h, then_h;
double duration;

char map[50][200];
int s_rm[50][200];
int tem[10];

double player_wealth = 0;
double player_hp = 100;
double player_hunger = 100;
int player_color = 0;
int hardness = 0;

int visit[50][200];

int shown[50][100];
int initial_x;
int initial_y;
int initial_room;
int initial_stair_room;
int stair_x;
int stair_y;
char last_move = '.';
int D_X;
int D_Y;
int ancient = 0;
char ramz[10];

int last_partab;
char last_monster[50];

void load_map(char* name_bazikon, int ted_bazi, int level) {
    char* temp = (char*)malloc(200);
    char* temp1 = (char*)malloc(3);
    temp1[0] = (char)(65 + ted_bazi);
    temp1[1] = '\0';
    char* temp2 = (char*)malloc(3);
    temp2[0] = (char)(level + 48);
    temp2[1] = '\0';
    strcpy(temp, name_bazikon);
    strcat(temp, temp1);
    strcat(temp, temp2);
    //strcat(temp, ".txt");
    FILE* fptr = fopen(temp, "r");
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            fscanf(fptr, " %c", &map[i][j]);
        }
    }
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            fscanf(fptr, " %d", &shown[i][j]);
        }
    }
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            fscanf(fptr, " %d", &s_rm[i][j]);
        }
    }
    for(int i = 0; i < 10; i++) {
        fscanf(fptr, " %d", &tem[i]);
    }
    fscanf(fptr, " %d", &tot_monster);
    for(int i = 0; i < tot_monster; i++) {
        fscanf(fptr, " %d", &monster[i].x);
        fscanf(fptr, " %d", &monster[i].y);
        fscanf(fptr, " %d", &monster[i].hp);
        fscanf(fptr, " %d", &monster[i].damage);
        fscanf(fptr, " %d", &monster[i].alive);
        fscanf(fptr, " %d", &monster[i].active);
        fscanf(fptr, " %d", &monster[i].kind);
        fscanf(fptr, " %d", &monster[i].dist);
    }
    // fscanf(fptr, " %lf", &player_hp);
    // fscanf(fptr, " %lf", &player_hunger);
    // fscanf(fptr, " %lf", &player_wealth);
    // fscanf(fptr, " %d", &weapon);
    // for(int i = 0; i < 3; i++)
    //     fscanf(fptr, " %d", &food[i]);
    // for(int i = 0; i < 5; i++)
    //     fscanf(fptr, " %d", &aslahe[i]);
    // for(int i = 0; i < 3; i++)
    //     fscanf(fptr, " %d", &telesm[i]);
    fclose(fptr);
    refresh();
    return;
}

void save_map(char* name_bazikon, int ted_bazi, int level) {
    char* temp = (char*)malloc(200);
    char* temp1 = (char*)malloc(3);
    temp1[0] = (char)(65 + ted_bazi);
    temp1[1] = '\0';
    char* temp2 = (char*)malloc(3);
    temp2[0] = (char)(level + 48);
    temp2[1] = '\0';
    strcpy(temp, name_bazikon);
    strcat(temp, temp1);
    strcat(temp, temp2);
    //strcat(temp, ".txt");
    FILE* fptr = fopen(temp, "w");
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            fprintf(fptr, " %c", map[i][j]);
        }
    }
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            fprintf(fptr, " %d", shown[i][j]);
        }
    }
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            fprintf(fptr, " %d", s_rm[i][j]);
        }
    }
    for(int i = 0; i < 10; i++) {
        fprintf(fptr, " %d", tem[i]);
    }
    fprintf(fptr, " %d", tot_monster);
    for(int i = 0; i < tot_monster; i++) {
        fprintf(fptr, " %d", monster[i].x);
        fprintf(fptr, " %d", monster[i].y);
        fprintf(fptr, " %d", monster[i].hp);
        fprintf(fptr, " %d", monster[i].damage);
        fprintf(fptr, " %d", monster[i].alive);
        fprintf(fptr, " %d", monster[i].active);
        fprintf(fptr, " %d", monster[i].kind);
        fprintf(fptr, " %d", monster[i].dist);
    }
    // fprintf(fptr, " %lf", player_hp);
    // fprintf(fptr, " %lf", player_hunger);
    // fprintf(fptr, " %lf", player_wealth);
    // fprintf(fptr, " %d", weapon);
    // for(int i = 0; i < 3; i++)
    //     fprintf(fptr, " %d", food[i]);
    // for(int i = 0; i < 5; i++)
    //     fprintf(fptr, " %d", aslahe[i]);
    // for(int i = 0; i < 3; i++)
    //     fprintf(fptr, " %d", telesm[i]);
    fclose(fptr);
    refresh();
    return;
}

int validate(int x, int y, int resx, int resy) {
    if(x == resx && y == resy)
        return 1;
    if(x >= 0 && x <= 45 && y >= 0 && y <= 184 && visit[x][y] == 0) {
        if(map[x][y] == '_')
            return 0;
        if(map[x][y] == '|' || map[x][y] == '^')
            return 0;
        if(map[x][y] == '.')
            return 0;
        if(map[x][y] == 'T')
            return 0;
        if(map[x][y] == 'K')
            return 0;
        if(map[x][y] == 'G')
            return 0;
        if(map[x][y] == 'p')
            return 1;
        else if(map[x][y] == '#')
            return 1;
    }
    return 0;
}

int dfs(int bx, int by, int x, int y, int resx, int resy) {
    visit[x][y] = 1;
    int dx[4] = {0, 0, 0, 0};
    int dy[4] = {0, 0, 0, 0};
    if(x == resx && y ==  resy) {
        map[x][y] = '#';
        return 1;
    }
    int shans = 1 + rand()%2;
    if(x == resx && y < resy) {
        if(shans == 0) {
            dx[0] = 1;
            dy[1] = 1;
        }
        else {
            dy[0] = 1;
            dx[1] = 1;
        }
        dx[2] = -1;
        dy[3] = -1;
    }
    else if(x == resx && y > resy) {
        if(shans == 0) {
            dx[0] = -1;
            dy[1] = -1;
        }
        else {
            dy[0] = -1;
            dx[1] = -1;
        }
        dx[2] = 1;
        dy[3] = 1;
    }
    else if(x > resx && y == resy) {
        if(shans == 0) {
            dy[0] = 1;
            dx[1] = -1;
        }
        else {
            dx[0] = -1;
            dy[1] = 1;
        }
        dy[2] = -1;
        dx[3] = 1;
    }
    else if(x < resx && y == resy) {
        if(shans == 0) {
            dy[0] = -1;
            dx[1] = 1;
        }
        else {
            dx[0] = 1;
            dy[1] = -1;
        }
        dy[2] = 1;
        dx[3] = -1;
    }
    if(x < resx && y < resy) {
        if(shans == 1) {
            dy[0] = 1;
            dx[1] = 1;
        }
        else {
            dx[0] = 1;
            dy[1] = 1;
        }
        dx[2] = -1;
        dy[3] = -1;
    }
    else if(x < resx && y > resy) {
        if(shans == 1) {
            dy[0] = -1;
            dx[1] = 1;
        }
        else {
            dx[0] = 1;
            dy[1] = -1;
        }
        dx[2] = -1;
        dy[3] = 1;
    }
    else if(x > resx && y < resy) {
        if(shans == 1) {
            dy[0] = 1;
            dx[1] = -1;
        }
        else {
            dx[0] = -1;
            dy[1] = 1;
        }
        dx[2] = 1;
        dy[3] = -1;
    }
    else if(x > resx && y > resy) {
        if(shans == 1) {
            dy[0] = -1;
            dx[1] = -1;
        }
        else {
            dx[0] = -1;
            dy[1] = -1;
        }
        dx[2] = 1;
        dy[3] = 1;
    }
    for(int i = 0; i < 4; i++) {
        if(validate(x + dx[i], y + dy[i], resx, resy)) {
            if(dfs(bx, by, x + dx[i], y + dy[i], resx, resy)) {
                    map[x][y] = '#';
                return 1;
            }
        }
    }
    return 0;
}

void make_ramz() {
    int len = 4;
    for(int i = 0; i < len; i++) {
        ramz[i] = 48 + rand()%10;
    }
    ramz[len] = '\0';
}
void make_root(int x1, int y1, int x2, int y2) {
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            visit[i][j] = 0;
        }
    }
    dfs(x1, y1, x1, y1, x2, y2);
}

void make_door(int x, int ind, struct room* rms, int rx, int ry) {
    if(x == 0) {
        int res;
        for(res = 0; res < rms->lenth; res++) {
            if(rms->mapc[0][1 + res] == '+') {
                D_X = 0 + rx - 1;
                D_Y = 1 + res + ry;
                rms->mapc[0][1 + res] = '+';
                return;
            }
        }
        res = rand()%(rms->lenth);
        if(rms->mapc[0][1 + res] != '+') {
            D_X = 0 + rx - 1;
            D_Y = 1 + res + ry;
            rms->mapc[0][1 + res] = '+';
            return;
        }
        else {
            make_door(x, ind, rms, rx, ry);
            return;
        }
    }
    if(x == 1) {
        int res;
        for(res = 0; res < rms->lenth; res++) {
            if(rms->mapc[rms->width + 1][1 + res] == '+') {
                D_X = rms->width + 1 + rx + 1;
                D_Y = 1 + res + ry;
                rms->mapc[rms->width + 1][1 + res] = '+';
                return;
            }
        }
        res = rand()%(rms->lenth);
        if(rms->mapc[rms->width + 1][1 + res] != '+') {
            D_X = rms->width + 1 + rx + 1;
            D_Y = 1 + res + ry;
            rms->mapc[rms->width + 1][1 + res] = '+';
            return;
        }
        else {
            make_door(x, ind, rms, rx, ry);
            return;
        }
    }
    if(x == 2) {
        int res;
        for(res = 0; res < rms->width; res++) {
            if(rms->mapc[1 + res][0] == '+') {
                D_X = 1 + res + rx;
                D_Y = 0 + ry - 1;
                rms->mapc[1 + res][0] = '+';
                return;
            }
        }
        res = rand()%(rms->width);
        if(rms->mapc[1 + res][0] != '+') {
            D_X = 1 + res + rx;
            D_Y = 0 + ry - 1;
            rms->mapc[1 + res][0] = '+';
            return;
        }
        else {
            make_door(x, ind, rms, rx, ry);
            return;
        }
    }
    if(x == 3) {
        int res;
        for(res = 0; res < rms->width; res++) {
            if(rms->mapc[1 + res][rms->lenth + 1] != '+') {
                D_X = 1 + res + rx;
                D_Y = rms->lenth + 1 + ry + 1;
                int rsd = rand()%2;
                if(ind == 2 && rsd == 0) {
                    rms->mapc[1 + res][rms->lenth + 1] = '^';
                }
                else if(ind == 6) {
                    rsd = 0;
                    if(rsd == 0) {
                        rms->mapc[1 + res][rms->lenth + 1] = '@';
                    }
                    rsd = 0;
                    if(rsd == 0)
                        rms->mapc[1][1] = 't';
                    make_ramz();
                    rsd = rand()%1;
                    if(rsd == 0) {
                        rsd = rand()%5;
                        rm[rsd].mapc[1][1] = 'n';
                    }
                }
                else
                    rms->mapc[1 + res][rms->lenth + 1] = '+';
                return;
            }
        }
        res = rand()%(rms->width);
        if(rms->mapc[1 + res][rms->lenth + 1] != '+') {
            D_X = 1 + res + rx;
            D_Y = rms->lenth + 1 + ry + 1;
            rms->mapc[1 + res][rms->lenth + 1] = '+';
            return;
        }
        else {
            make_door(x, ind, rms, rx, ry);
            return;
        }
    }
}

void make_root_map(int TOTAL) {
    for(int i = 1; i < TOTAL; i++) {
        int j = rand()%i;
        int x1, y1, x2, y2;
        if(i == 1) {
            make_door(3, j, &rm[j], rm[j].x, rm[j].y);
            x1 = D_X;
            y1 = D_Y;
            make_door(2, i, &rm[i], rm[i].x, rm[i].y);
            x2 = D_X;
            y2 = D_Y;
        }
        if(i == 2) {
            while(j == 0)
                j = rand()%i;
            make_door(3, j, &rm[j], rm[j].x, rm[j].y);
            x1 = D_X;
            y1 = D_Y;
            make_door(2, i, &rm[i], rm[i].x, rm[i].y);
            x2 = D_X;
            y2 = D_Y;
        }
        if(i == 3) {
            while(j == 0 || j == 1)
                j = rand()%i;
            make_door(3, j, &rm[j], rm[j].x, rm[j].y);
            x1 = D_X;
            y1 = D_Y;
            make_door(2, i, &rm[i], rm[i].x, rm[i].y);
            x2 = D_X;
            y2 = D_Y;
        }
        if(i == 4) {
            while(j == 2 || j == 3)
                j = rand()%i;
            make_door(1, j, &rm[j], rm[j].x, rm[j].y);
            x1 = D_X;
            y1 = D_Y;
            make_door(0, i, &rm[i], rm[i].x, rm[i].y);
            x2 = D_X;
            y2 = D_Y;
        }
        if(i == 5) {
            while(j == 3)
                j = rand()%i;
            if(j == 4) {
                make_door(3, j, &rm[j], rm[j].x, rm[j].y);
                x1 = D_X;
                y1 = D_Y;
                make_door(2, i, &rm[i], rm[i].x, rm[i].y);
                x2 = D_X;
                y2 = D_Y;
            }
            else {
                make_door(1, j, &rm[j], rm[j].x, rm[j].y);
                x1 = D_X;
                y1 = D_Y;
                make_door(0, i, &rm[i], rm[i].x, rm[i].y);
                x2 = D_X;
                y2 = D_Y;
            }
        }
        if(i == 6) {
            while(j == 4 || j == 0)
                j = rand()%i;
            if(j == 5) {
                make_door(3, j, &rm[j], rm[j].x, rm[j].y);
                x1 = D_X;
                y1 = D_Y;
                make_door(2, i, &rm[i], rm[i].x, rm[i].y);
                x2 = D_X;
                y2 = D_Y;
            }
            else {
                make_door(1, j, &rm[j], rm[j].x, rm[j].y);
                x1 = D_X;
                y1 = D_Y;   
                make_door(0, i, &rm[i], rm[i].x, rm[i].y);
                x2 = D_X;
                y2 = D_Y;
            }
        }
        if(i == 7) {
            while(j == 0 || j == 1 || j == 4 || j == 5)
                j = rand()%i;
            if(j == 6) {
                make_door(3, j, &rm[j], rm[j].x, rm[j].y);
                x1 = D_X;
                y1 = D_Y;
                make_door(2, i, &rm[i], rm[i].x, rm[i].y);
                x2 = D_X;
                y2 = D_Y;
            }
            else {
                make_door(1, j, &rm[j], rm[j].x, rm[j].y);
                x1 = D_X;
                y1 = D_Y;
                make_door(0, i, &rm[i], rm[i].x, rm[i].y);
                x2 = D_X;
                y2 = D_Y;
            }
        }
        make_root(x1, y1, x2, y2);
    }
}

int check(int level, int x, int y) {
    if(map[x][y] == '|' || map[x][y] == '_' || map[x][y] == 'O' || map[x][y] == 'p' || map[x][y] == 'T' || map[x][y] == 'K' || map[x][y] == 'G' || map[x][y] == '0' || map[x][y] == '1' || map[x][y] == '2' || map[x][y] == '3' || map[x][y] == '4')
        return 0;
    return 1;
}
void print(int level, int i, int j) {
    refresh();
    shown[i][j] = 1;
    mvaddstr(i, 2*j, " ");
    mvaddstr(i, 2*j + 1, " ");
    if(map[i][j] == '0') {
        mvaddstr(i, 2 * j, "👾");
    }
    if(map[i][j] == '1') {
        mvaddstr(i, 2 * j, "🐍");
    }
    if(map[i][j] == '2') {
        mvaddstr(i, 2 * j, "🧌");
    }
    if(map[i][j] == '3') {
        mvaddstr(i, 2 * j, "🐉");
    }
    if(map[i][j] == '4') {
        mvaddstr(i, 2 * j, "👹");
    }
    if(map[i][j] == '6') {
        mvaddstr(i, 2 * j, "\U0001F5E1");
    }
    if(map[i][j] == '7') {
        mvaddstr(i, 2 * j, "\U0001FA84");
    }
    if(map[i][j] == '8') {
        mvaddstr(i, 2 * j, "\U000027B3");
    }
    if(map[i][j] == '|'  || map[i][j] == '_' || map[i][j] == '^') {
        mvaddstr(i, 2 * j, "\U0001F9F1");
    }
    if(map[i][j] == 'T') {
        mvaddstr(i, 2 * j, "\U0001F7EA");
    }
    if(map[i][j] == 'G') {
        mvaddstr(i, 2 * j, "\U0001F7E8");
    }
    if(map[i][j] == 'K') {
        mvaddstr(i, 2 * j, "\U0001F7EB");
    }
    if(map[i][j] == 'g') {
        mvaddstr(i, 2 * j, "\U00002692");
    }
    if(map[i][j] == 'd') {
        mvaddstr(i, 2 * j, "\U0001F5E1");
    }
    if(map[i][j] == 'w') {
        mvaddstr(i, 2 * j, "\U0001FA84");
    }
    if(map[i][j] == 'a') {
        mvaddstr(i, 2 * j, "\U000027B3");
    }
    if(map[i][j] == 'r') {
        mvaddstr(i, 2 * j, "\U00002694");
    }
    if(map[i][j] == '+')
        mvaddstr(i, 2 * j, "\U0001F67E");//1F67E//\U0001F6AA
    if(map[i][j] == '#') {
        mvaddstr(i, 2 * j, "\U0001FB96");
        mvaddstr(i, 2 * j + 1, "\U0001FB96");
    }
    if(map[i][j] == '.' || map[i][j] == 'P') {
        mvaddstr(i, 2 * j, "\U000026AA");
    }
    if(map[i][j] == 's') {
        mvaddstr(i, 2 * j, "\U0001F847");
    }
    if(map[i][j] == 'S') {
        mvaddstr(i, 2 * j, "\U0001F845");
    }
    if(map[i][j] == 'O') {
        mvaddstr(i, 2 * j, "\U000026AB");
    }
    if(map[i][j] == '=') {
        mvaddstr(i, 2 * j, "\U0001F7F0");
    }
    if(map[i][j] == '*') {
        mvaddstr(i, 2 * j, "\U00002B1B");
    }
    if(map[i][j] == 'm') {
        mvaddstr(i, 2 * j, "\U0001FA99");
    }
    if(map[i][j] == 'M') {
        mvaddstr(i, 2 * j, "\U0001F4B0");
    }
    if(map[i][j] == 'c' || map[i][j] == 'j') {
        mvaddstr(i, 2 * j, "🍞");
    }
    if(map[i][j] == 'l') {
        mvaddstr(i, 2 * j, "\U0001F969");
    }
    if(map[i][j] == 'q') {
        mvaddstr(i, 2 * j, "🍾");
    }
    if(map[i][j] == 'f') {
        mvaddstr(i, 2 * j, "\U0001F9A0");
    }
    if(map[i][j] == 'h') {
        mvaddstr(i, 2 * j, "💊");
    }
    if(map[i][j] == 'e') {
        mvaddstr(i, 2 * j, "🚀");
    }
    if(map[i][j] == 'b') {
        mvaddstr(i, 2 * j, "⚡");
    }
    if(map[i][j] == 'V') {
        mvaddstr(i, 2 * j, "🏆");
    }
    if(map[i][j] == 'R') {
        mvaddstr(i, 2 * j, "  ");
        mvaddstr(i, 2 * j, "🕸️");
    }
    if(map[i][j] == '@') {
        mvaddstr(i, 2 * j, "\U0001F7E5");
    }
    if(map[i][j] == 't') {
        mvaddstr(i, 2*j, "🔑");
    }
    if(map[i][j] == 'n') {
        mvaddstr(i, 2*j, "🗝️");
    }
    init_pair(10, COLOR_WHITE, COLOR_WHITE);
    if(map[i][j] == 'A') {
        if(player_color == 0) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "\U0001F535");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 1) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🔴");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 2) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🟢");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 3) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🟡");
            attroff(COLOR_PAIR(10));
        }
    }
}

void show_dfs(int level, int x, int y) {
    refresh();
    visit[x][y] = 1;
    if(map[x][y] == 'p' || map[x][y] == '#')
        return;
    print(level, x, y);
    if(map[x][y] == '#' || map[x][y] == '_' || map[x][y] == '|' || map[x][y] == '^')
        return;
    if(visit[x + 1][y + 1] == 0) {
        show_dfs(level, x + 1, y + 1);
    }
    if(visit[x + 1][y - 1] == 0) {
        show_dfs(level, x + 1, y - 1);
    }
    if(visit[x - 1][y + 1] == 0) {
        show_dfs(level, x - 1, y + 1);
    }
    if(visit[x - 1][y - 1] == 0) {
        show_dfs(level, x - 1, y - 1);
    }
    if(visit[x + 1][y] == 0) {
        show_dfs(level, x + 1, y);
    }
    if(visit[x - 1][y] == 0) {
        show_dfs(level, x - 1, y);
    }
    if(visit[x][y + 1] == 0) {
        show_dfs(level, x, y + 1);
    }
    if(visit[x][y - 1] == 0) {
        show_dfs(level, x, y - 1);
    }
}

void show_corridor(int level, int x, int y, int h) {
    if(h == 0)
        return;
    if(visit[x][y])
        return;
    visit[x][y] = 1;
    if(map[x][y] == '+') {
        print(level, x, y);
        return;
    }
    if(map[x][y] != '#')
        return;
    print(level, x, y);
    show_corridor(level, x + 1, y, h - 1);
    show_corridor(level, x - 1, y, h - 1);
    show_corridor(level, x, y + 1, h - 1);
    show_corridor(level, x, y - 1, h - 1);
}

void show(int level, int x, int y) {
    if(map[x][y] == '#') {
        for(int i = 0; i < 50; i++) {
            for(int j = 0; j < 200; j++) {
                visit[i][j] = 0;
            }
        }
        show_corridor(level, x, y, 5);
        return;
    }
    if(map[x][y] == '+') {
        if(map[x + 1][y] == '#' || map[x + 1][y] == '+')
            print(level, x + 1, y);
        if(map[x - 1][y] == '#' || map[x - 1][y] == '+')
            print(level, x - 1, y);
        if(map[x][y + 1] == '#' || map[x][y + 1] == '+')
            print(level, x, y + 1);
        if(map[x][y - 1] == '#' || map[x][y - 1] == '+')
            print(level, x, y - 1);
    }
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            visit[i][j] = 0;
        }
    }
    show_dfs(level, x, y);
}

void print_all(int level, int x) {
    refresh();
    if(x%2 == 1) {
        for(int i = 0; i < 50; i++) {
            for(int j = 0; j < 200; j++) {
                mvaddstr(i, 2*j, " ");
                mvaddstr(i, 2*j + 1, " ");
    if(map[i][j] == '0') {
        mvaddstr(i, 2 * j, "👾");
    }
    if(map[i][j] == '1') {
        mvaddstr(i, 2 * j, "🐍");
    }
    if(map[i][j] == '2') {
        mvaddstr(i, 2 * j, "🧌");
    }
    if(map[i][j] == '3') {
        mvaddstr(i, 2 * j, "🐉");
    }
    if(map[i][j] == '4') {
        mvaddstr(i, 2 * j, "👹");
    }
    if(map[i][j] == '|' || map[i][j] == '_' || map[i][j] == '^') {
        mvaddstr(i, 2 * j, "\U0001F9F1");
    }
    if(map[i][j] == 'T') {
        mvaddstr(i, 2 * j, "\U0001F7EA");
    }
    if(map[i][j] == 'G') {
        mvaddstr(i, 2 * j, "\U0001F7E8");
    }
    if(map[i][j] == 'K') {
        mvaddstr(i, 2 * j, "\U0001F7EB");
    }
    if(map[i][j] == '+')
        mvaddstr(i, 2 * j, "\U0001F67E");//1F67E//\U0001F6AA
    if(map[i][j] == '#') {
        mvaddstr(i, 2 * j, "\U0001FB96");
        mvaddstr(i, 2 * j + 1, "\U0001FB96");
    }
    if(map[i][j] == '.' || map[i][j] == 'P') {
        mvaddstr(i, 2 * j, "\U000026AA");
    }
if(map[i][j] == 's') {
        mvaddstr(i, 2 * j, "\U0001F847");
    }
    if(map[i][j] == 'S') {
        mvaddstr(i, 2 * j, "\U0001F845");
    }
    if(map[i][j] == 'O') {
        mvaddstr(i, 2 * j, "\U000026AB");
    }
    if(map[i][j] == '=') {
        mvaddstr(i, 2 * j, "\U0001F7F0");
    }
    if(map[i][j] == '*') {
        mvaddstr(i, 2 * j, "\U00002B1B");
    }
        if(map[i][j] == 'm') {
        mvaddstr(i, 2 * j, "\U0001FA99");
    }
    if(map[i][j] == 'M') {
        mvaddstr(i, 2 * j, "\U0001F4B0");
    }
        if(map[i][j] == 'g') {
        mvaddstr(i, 2 * j, "\U00002692");
    }
    if(map[i][j] == 'd') {
        mvaddstr(i, 2 * j, "\U0001F5E1");
    }
    if(map[i][j] == 'w') {
        mvaddstr(i, 2 * j, "\U0001FA84");
    }
    if(map[i][j] == 'a') {
        mvaddstr(i, 2 * j, "\U000027B3");
    }
    if(map[i][j] == 'r') {
        mvaddstr(i, 2 * j, "\U00002694");
    }
    if(map[i][j] == 'V') {
        mvaddstr(i, 2 * j, "🏆");
    }
        if(map[i][j] == 'c' || map[i][j] == 'j') {
        mvaddstr(i, 2 * j, "🍞");
    }
    if(map[i][j] == 'l') {
        mvaddstr(i, 2 * j, "\U0001F969");
    }
    if(map[i][j] == 'q') {
        mvaddstr(i, 2 * j, "🍾");
    }
    if(map[i][j] == 'f') {
        mvaddstr(i, 2 * j, "\U0001F9A0");
    }
        if(map[i][j] == 'h') {
        mvaddstr(i, 2 * j, "💊");
    }
    if(map[i][j] == 'e') {
        mvaddstr(i, 2 * j, "🚀");
    }
    if(map[i][j] == 'b') {
        mvaddstr(i, 2 * j, "⚡");
    }
    if(map[i][j] == 'R') {
        mvaddstr(i, 2 * j, "  ");
        mvaddstr(i, 2 * j, "🕸️");
    }
    if(map[i][j] == '@') {
        mvaddstr(i, 2 * j, "\U0001F7E5");
    }
    if(map[i][j] == 't') {
        //init_pair(11, COLOR_YELLOW, COLOR_YELLOW);
        //attron(COLOR_PAIR(11));
        mvaddstr(i, 2*j, "🔑");
        //attroff(COLOR_PAIR(11));
    }
    if(map[i][j] == '6') {
        mvaddstr(i, 2 * j, "\U0001F5E1");
    }
    if(map[i][j] == '7') {
        mvaddstr(i, 2 * j, "\U0001FA84");
    }
    if(map[i][j] == '8') {
        mvaddstr(i, 2 * j, "\U000027B3");
    }
    if(map[i][j] == 'n') {
        mvaddstr(i, 2*j, "🗝️");
    }
    init_pair(10, COLOR_WHITE, COLOR_WHITE);
    if(map[i][j] == 'A') {
        if(player_color == 0) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "\U0001F535");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 1) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🔴");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 2) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🟢");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 3) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🟡");
            attroff(COLOR_PAIR(10));
        }
    }
            }
        }
    }
    if(x%2 == 0) {
        for(int i = 0; i < 50; i++) {
            for(int j = 0; j < 200; j++) {
                if(shown[i][j] == 0) {
                    mvaddstr(i, 2*j, "  ");
                    continue;
                }
                mvaddstr(i, 2*j, " ");
                mvaddstr(i, 2*j + 1, " ");
    if(map[i][j] == '0') {
        mvaddstr(i, 2 * j, "👾");
    }
    if(map[i][j] == '1') {
        mvaddstr(i, 2 * j, "🐍");
    }
    if(map[i][j] == '2') {
        mvaddstr(i, 2 * j, "🧌");
    }
    if(map[i][j] == '3') {
        mvaddstr(i, 2 * j, "🐉");
    }
    if(map[i][j] == '4') {
        mvaddstr(i, 2 * j, "👹");
    }
    if(map[i][j] == '|' || map[i][j] == '_' || map[i][j] == '^') {
        mvaddstr(i, 2 * j, "\U0001F9F1");
    }
    if(map[i][j] == 'T') {
        mvaddstr(i, 2 * j, "\U0001F7EA");
    }
    if(map[i][j] == 'G') {
        mvaddstr(i, 2 * j, "\U0001F7E8");
    }
    if(map[i][j] == 'K') {
        mvaddstr(i, 2 * j, "\U0001F7EB");
    }
    if(map[i][j] == '+')
        mvaddstr(i, 2 * j, "\U0001F67E");//1F67E//\U0001F6AA
    if(map[i][j] == '#') {
        mvaddstr(i, 2 * j, "\U0001FB96");
        mvaddstr(i, 2 * j + 1, "\U0001FB96");
    }
    if(map[i][j] == '.' || map[i][j] == 'P') {
        mvaddstr(i, 2 * j, "\U000026AA");
    }
if(map[i][j] == 's') {
        mvaddstr(i, 2 * j, "\U0001F847");
    }
    if(map[i][j] == 'S') {
        mvaddstr(i, 2 * j, "\U0001F845");
    }
    if(map[i][j] == '=') {
        mvaddstr(i, 2 * j, "\U0001F7F0");
    }
    if(map[i][j] == '*') {
        mvaddstr(i, 2 * j, "\U00002B1B");
    }
    if(map[i][j] == 'O') {
        mvaddstr(i, 2 * j, "\U000026AB");
    }
        if(map[i][j] == 'm') {
        mvaddstr(i, 2 * j, "\U0001FA99");
    }
    if(map[i][j] == 'M') {
        mvaddstr(i, 2 * j, "\U0001F4B0");
    }
    if(map[i][j] == 'g') {
        mvaddstr(i, 2 * j, "\U00002692");
    }
    if(map[i][j] == 'd') {
        mvaddstr(i, 2 * j, "\U0001F5E1");
    }
    if(map[i][j] == 'w') {
        mvaddstr(i, 2 * j, "\U0001FA84");
    }
    if(map[i][j] == 'a') {
        mvaddstr(i, 2 * j, "\U000027B3");
    }
    if(map[i][j] == 'r') {
        mvaddstr(i, 2 * j, "\U00002694");
    }
    if(map[i][j] == 'c' || map[i][j] == 'j') {
        mvaddstr(i, 2 * j, "🍞");
    }
    if(map[i][j] == 'l') {
        mvaddstr(i, 2 * j, "\U0001F969");
    }
    if(map[i][j] == 'q') {
        mvaddstr(i, 2 * j, "🍾");
    }
    if(map[i][j] == 'f') {
        mvaddstr(i, 2 * j, "\U0001F9A0");
    }
        if(map[i][j] == 'h') {
        mvaddstr(i, 2 * j, "💊");
    }
    if(map[i][j] == 'e') {
        mvaddstr(i, 2 * j, "🚀");
    }
    if(map[i][j] == 'b') {
        mvaddstr(i, 2 * j, "⚡");
    }
    if(map[i][j] == 'R') {
        mvaddstr(i, 2 * j, "  ");
        mvaddstr(i, 2 * j, "🕸️");
    }
    if(map[i][j] == '@') {
        mvaddstr(i, 2 * j, "\U0001F7E5");
    }
    if(map[i][j] == 't') {
        //init_pair(11, COLOR_YELLOW, COLOR_YELLOW);
        //attron(COLOR_PAIR(11));
        mvaddstr(i, 2*j, "🔑");
        //attroff(COLOR_PAIR(11));
    }
    if(map[i][j] == 'n') {
        mvaddstr(i, 2*j, "🗝️");
    }
    if(map[i][j] == '6') {
        mvaddstr(i, 2 * j, "\U0001F5E1");
    }
    if(map[i][j] == '7') {
        mvaddstr(i, 2 * j, "\U0001FA84");
    }
    if(map[i][j] == '8') {
        mvaddstr(i, 2 * j, "\U000027B3");
    }
    if(map[i][j] == 'V') {
        mvaddstr(i, 2 * j, "🏆");
    }
    init_pair(10, COLOR_WHITE, COLOR_WHITE);
    if(map[i][j] == 'A') {
        if(player_color == 0) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "\U0001F535");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 1) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🔴");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 2) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🟢");
            attroff(COLOR_PAIR(10));
        }
        if(player_color == 3) {
            attron(COLOR_PAIR(10));
            mvaddstr(i, 2 * j, "🟡");
            attroff(COLOR_PAIR(10));
        }
    }
            }
        }
    }
}

void check_time() {
    time(&then);
    if(difftime(then, now) >= duration) {
        for(int i = 0; i < 100; i++)
            mvprintw(0, i, " ");
    }
    return;
}

void print_message(int cond, int damage) {
    for(int i = 0; i < 100; i++)
        mvprintw(1, i, " ");
    time(&now);
    if(cond == 80) {
        mvprintw(1, 0, "You Have peaked up ancient Key");
        duration = 4;
    }
    if(cond == 0) {
        mvprintw(1, 0, "You can have at most 5 unit of food");
        duration = 2;
    }
    if(cond == 1) {
        mvprintw(1, 0, "You have peaked up common food");
        duration = 4;
    }
    if(cond == 2) {
        mvprintw(1, 0, "You have peaked up great food");
        duration = 4;
    }
    if(cond == 3) {
        mvprintw(1, 0, "You have peaked up magic food");
        duration = 4;
    }
    if(cond == 4) {
        mvprintw(1, 0, "weapons changed successfully");
        duration = 4;
    }
    if(cond == 5) {
        mvprintw(1, 0, "Mace peaked up successfully");
        duration = 4;
    }
    if(cond == 6) {
        mvprintw(1, 0, "Dagger peaked up successfully");
        duration = 4;
    }
    if(cond == 7) {
        mvprintw(1, 0, "Magic Wand peaked up successfully");
        duration = 4;
    }
    if(cond == 8) {
        mvprintw(1, 0, "Normal arrow peaked up successfully");
        duration = 4;
    }
    if(cond == 9) {
        mvprintw(1, 0, "Sword peaked up successfully");
        duration = 4;
    }
    if(cond == 10) {
        mvprintw(1, 0, "first drop your weapon");
        duration = 2;
    }
    if(cond == 11) {
        mvprintw(1, 0, "You don't have this weapon");
        duration = 2;
    }
    if(cond == 12) {
        mvprintw(1, 0, "weapon changed successfully");
        duration = 2;
    }
    if(cond == 13) {
        mvprintw(1, 0, "weapon dropped sucessfully");
        duration = 2;
    }
    if(cond == 14) {
        mvprintw(1, 0, "health spell picked up secussfully");
        duration = 4;
    }
    if(cond == 15) {
        mvprintw(1, 0, "speed spell picked up secussfully");
        duration = 4;
    }
    if(cond == 16) {
        mvprintw(1, 0, "damage spell picked up secussfully");
        duration = 4;
    }
    if(cond == 17) {
        mvprintw(1, 0, "You earned 5 golds");
        duration = 4;
    }
    if(cond == 18) {
        mvprintw(1, 0, "You earned 30 golds");
        duration = 4;
    }
    if(cond == 19) {
        mvprintw(1, 0, "You don't hold any weapon right now");
        duration = 4;
    }
    if(cond == 20) {
        mvprintw(1, 0, "You killed a Deamon");
        duration = 4;
    }
    if(cond == 21) {
        mvprintw(1, 0, "You killed a Fire Breathing Monster");
        duration = 4;
    }
    if(cond == 22) {
        mvprintw(1, 0, "You killed a Giant");
        duration = 4;
    }
    if(cond == 23) {
        mvprintw(1, 0, "You killed a Snake");
        duration = 4;
    }
    if(cond == 24) {
        mvprintw(1, 0, "You killed a Unⅾeeⅾ");
        duration = 4;
    }
    if(cond == 36) {
        mvprintw(1, 0, "You have eaten corrupt food");
        duration = 4;
    }
    //

    duration = 4;
    if(cond == 25) {
        mvprintw(1, 0, "You have hitted Deamon %d units", damage);
    }
    if(cond == 26) {
        mvprintw(1, 0, "You have hitted Fire Breathing Monster %d units", damage);
    }
    if(cond == 27) {
        mvprintw(1, 0, "You have hitted Giant %d units", damage);
    }
    if(cond == 28) {
        mvprintw(1, 0, "You have hitted Snake %d units", damage);
    }
    if(cond == 29) {
        mvprintw(1, 0, "You have hitted Undead %d units", damage);
    }
    if(cond == 40) {
        mvprintw(1, 0, "%s", ramz);
        duration = 7;
    }
    if(cond == 50) {
        mvprintw(1, 0, "You Got 🟨 Notice!");

    }
    if(cond == 51) {
        mvprintw(1, 0, "You Got 🟧 Notice!");
    }
    if(cond == 52) {
        mvprintw(1, 0, "You Got 🟥 Notice!");
    }
    if(cond == 60) {
        mvprintw(1, 0, "Welcome to New Level");
        duration = 7;
    }
    if(cond == 70) {
        mvprintw(1, 0, "Welcome to New Room");
        duration = 7;
    }
}

void aslahe_menu(char* name_bazikon, int ted_bazi, int level) {
    refresh();
    clear();
    refresh();
    noecho();
    curs_set(0);
    save_map(name_bazikon, ted_bazi, level);
    mvprintw(0, 0, "short range weapons : ");
    mvaddstr(2, 0, "     name of weapons    symbol     number of units     damage     distance      key to use");
    mvprintw(4, 0, ">         Mace            ⚒️              %d              5            1              m", aslahe[0]);
    mvprintw(6, 0, ">         Sword           ⚔️              %d              10           1             r", aslahe[4]);
    mvprintw(8, 0, "long range weapons : ");
    mvprintw(10, 0, ">         Dagger          🗡              %d              12          5              d", aslahe[1]);
    mvprintw(12, 0, ">       Magic Wand        🪄             %d              15          10              m", aslahe[2]);
    mvprintw(14, 0, ">      Normal arrow       ➳              %d              5           5             a", aslahe[3]);
    int p_x = 20;
    int p_y = 0;
    while(true) {
        mvprintw(0, 0, "short range weapons : ");
        mvaddstr(2, 0, "     name of weapons    symbol     number of units     damage     distance      key to use");
        mvprintw(4, 0, ">         Mace            ⚒️              %d              5            1               m", aslahe[0]);
        mvprintw(6, 0, ">         Sword           ⚔️              %d              10           1               r", aslahe[4]);
        mvprintw(8, 0, "long range weapons : ");
        mvprintw(10, 0, ">         Dagger          🗡              %d              12           5               d", aslahe[1]);
        mvprintw(12, 0, ">       Magic Wand        🪄             %d              15           10              o", aslahe[2]);
        mvprintw(14, 0, ">      Normal arrow       ➳              %d              5            5               a", aslahe[3]);
        move(p_x, p_y);
        int ch = getch();
        if(ch == 'm') {
            if(weapon != -1) {
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "first drop your current weapon");
            }
            else if(aslahe[0] == 0){
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "You don't have this weapon");
            }
            else {
                weapon = 0;
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "weapon changed to Mace secessfully");
                break;
            }
        }
        if(ch == 'r') {
            if(weapon != -1) {
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "first drop your current weapon");
            }
            else if(aslahe[4] == 0){
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "You don't have this weapon");
            }
            else {
                weapon = 4;
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "weapon changed to Sword secessfully");
                break;
            }
        }
        if(ch == 'd') {
            if(weapon != -1) {
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "first drop your current weapon");
            }
            else if(aslahe[1] == 0){
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "You don't have this weapon");
            }
            else {
                weapon = 1;
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "weapon changed to Dagger secessfully");
                break;
            }
        }
        if(ch == 'o') {
            if(weapon != -1) {
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "first drop your current weapon");
            }
            else if(aslahe[2] == 0){
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "You don't have this weapon");
            }
            else {
                weapon = 2;
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "weapon changed to Magic Wand secessfully");
                break;
            }
        }
        if(ch == 'a') {
            if(weapon != -1) {
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "first drop your current weapon");
            }
            else if(aslahe[3] == 0){
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "You don't have this weapon");
            }
            else {
                weapon = 3;
                mvprintw(16, 0, "                                              ");
                mvprintw(16, 0, "weapon changed to Normal Arrow secessfully");
                break;
            }
        }
        if(ch == 'w') {
            weapon = -1;
            mvprintw(16, 0, "                                              ");
            mvprintw(16, 0, "weapon dropped secessfully");
        }
        if(ch == 'q')
            break;
    }
    clear();
    refresh();
    noecho();
    curs_set(0);
    load_map(name_bazikon, ted_bazi, level);
    print_all(level, 0);
    refresh();
}

void food_menu(char* name_bazikon, int ted_bazi, int level) {
    refresh();
    clear();
    refresh();
    echo();
    curs_set(1);
    save_map(name_bazikon, ted_bazi, level);
    mvaddstr(0, 0, "     name of foods    symbol     number of units     Description");
    mvprintw(2, 0, ">     common food       🍞              %d           increses health", food[0]);
    mvprintw(4, 0, ">     great food        🥩              %d           increses health + increses power", food[1]);
    mvprintw(6, 0, ">     magic food        🍾              %d           increses health + increses speed", food[2]);
    int p_x = 2;
    int p_y = 0;
    while(true) {
        mvprintw(2, 0, ">     common food       🍞              %d           increses health", food[0]);
        mvprintw(4, 0, ">     great food        🥩              %d           increses health + increses power", food[1]);
        mvprintw(6, 0, ">     magic food        🍾              %d           increses health + increses speed", food[2]);
        move(p_x, p_y);
        int ch = getch();
        if(ch == KEY_DOWN) {
            if(p_x == 6)
                p_x = 2;
            else
                p_x += 2;
        }
        if(ch == KEY_UP) {
            if(p_x == 2)
                p_x = 6;
            else
                p_x -= 2;
        }
        if(ch == '\n') {
            if(p_x == 2) {
                if(food[0] > 0) {
                    food[0]--;
                    if(player_hunger + 30 <= 100)
                        player_hunger += 30;
                    else
                        player_hunger = 100;
                    mvprintw(8, 0, "                                                   ");
                    mvprintw(8, 0, "food increses 30 units");
                }
                else {
                    mvprintw(8, 0, "                                                   ");
                    mvprintw(8, 0, "You don't have this food");
                }
            }
            if(p_x == 4) {
                if(food[1] > 0) {
                    food[1]--;
                    if(player_hunger + 75 <= 100)
                        player_hunger += 75;
                    else
                        player_hunger = 100;
                    tel_power = 7;
                    mvprintw(8, 0, "                                                   ");
                    mvprintw(8, 0, "food increses 75 units");
                }
                else {
                    mvprintw(8, 0, "                                                   ");
                    mvprintw(8, 0, "You don't have this food");
                }
            }
            if(p_x == 6) {
                if(food[2] > 0) {
                    food[2]--;
                    if(player_hunger + 75 <= 100)
                        player_hunger += 75;
                    else
                        player_hunger = 100;
                    tel_speed = 14;
                    mvprintw(8, 0, "                                                   ");
                    mvprintw(8, 0, "food increses 75 units");
                }
                else {
                    mvprintw(8, 0, "                                                   ");
                    mvprintw(8, 0, "You don't have this food");
                }
            }
        }
        if(ch == 'q')
            break;
    }
    clear();
    refresh();
    noecho();
    curs_set(0);
    load_map(name_bazikon, ted_bazi, level);
    print_all(level, 0);
    refresh();
}

void telesm_menu(char* name_bazikon, int ted_bazi, int level) {
    refresh();
    clear();
    refresh();
    echo();
    curs_set(1);
    save_map(name_bazikon, ted_bazi, level);
    mvaddstr(0, 0, "     name of spell    symbol     number of units     Description");
    mvprintw(2, 0, ">       health          💊             %d           increses speed health", telesm[0]);
    mvprintw(4, 0, ">       speed           🚀             %d           increses speed", telesm[1]);
    mvprintw(6, 0, ">       damage          ⚡              %d           increses damage", telesm[2]);
    int p_x = 2;
    int p_y = 0;
    while(true) {
        mvaddstr(0, 0, "     name of spell    symbol     number of units     Description");
        mvprintw(2, 0, ">       health          💊             %d           increses speed health", telesm[0]);
        mvprintw(4, 0, ">       speed           🚀             %d           increses speed", telesm[1]);
        mvprintw(6, 0, ">       damage          ⚡              %d           increses damage", telesm[2]);
        move(p_x, p_y);
        int ch = getch();
        if(ch == KEY_DOWN) {
            if(p_x == 6)
                p_x = 2;
            else
                p_x += 2;
        }
        if(ch == KEY_UP) {
            if(p_x == 2)
                p_x = 6;
            else
                p_x -= 2;
        }
        if(ch == '\n') {
            if(p_x == 2) {
                if(telesm[0] > 0) {
                    telesm[0]--;
                    tel_hp = 10;
                    mvprintw(8, 0, "health spell applied");
                }
                else {
                    mvprintw(8, 0, "You don't have this spell");
                }
            }
            if(p_x == 4) {
                if(telesm[1] > 0) {
                    telesm[1]--;
                    tel_speed = 20;
                    mvprintw(8, 0, "speed spell applied");
                }
                else {
                    mvprintw(8, 0, "You don't have this spell");
                }
            }
            if(p_x == 6) {
                if(telesm[2] > 0) {
                    telesm[2]--;
                    tel_power = 10;
                    mvprintw(8, 0, "power spell applied");
                }
                else {
                    mvprintw(8, 0, "You don't have this spell");
                }
            }
        }
        if(ch == 'q')
            break;
    }
    clear();
    refresh();
    noecho();
    curs_set(0);
    load_map(name_bazikon, ted_bazi, level);
    print_all(level, 0);
    refresh();
}

int check_manhatan(int x1, int y1, int x2, int y2) {
    if(x1 > x2 && x1 - x2 >= 2)
        return 0;
    if(x2 > x1 && x2 - x1 >= 2)
        return 0;
    if(y2 > y1 && y2 - y1 >= 2)
        return 0;
    if(y1 > y2 && y1 - y2 >= 2)
        return 0;
    return 1;
}

void check_monster(int x, int y) {
    for(int i = 0; i < tot_monster; i++) {
        if(monster[i].alive) {
            if(check_manhatan(monster[i].x, monster[i].y, x, y)) {
                if(monster[i].active != 2)
                    monster[i].active = 1;
                player_hp -= monster[i].damage;
                time(&now_h);
            }
        }
    }
}

int next_monster(int ind, int x, int y) {
    int dx[3] = {0, 0, 0};
    int dy[3] = {0, 0, 0};
    int dif = x - monster[ind].x;
    if(dif > 0) {
        dx[0] = 1;
        dx[1] = 0;
        dx[2] = -1;
    }
    if(dif < 0) {
        dx[0] = -1;
        dx[1] = 0;
        dx[2] = 1;
    }
    if(dif == 0) {
        dx[0] = 0;
        dx[1] = 1;
        dx[2] = -1;
    }
    dif = y - monster[ind].y;
    if(dif > 0) {
        dy[0] = 1;
        dy[1] = 0;
        dy[2] = -1;
    }
    if(dif < 0) {
        dy[0] = -1;
        dy[1] = 0;
        dy[2] = 1;
    }
    if(dif == 0) {
        dy[0] = 0;
        dy[1] = 1;
        dy[2] = -1;
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(check(0, monster[ind].x + dx[i], monster[ind].y + dy[j]) && map[monster[ind].x + dx[i]][monster[ind].y + dy[j]] != 'A') {
                map[monster[ind].x][monster[ind].y] = last_monster[ind];
                print(0, monster[ind].x, monster[ind].y);
                last_monster[ind] = map[monster[ind].x + dx[i]][monster[ind].y + dy[j]];
                map[monster[ind].x + dx[i]][monster[ind].y + dy[j]] = (char)(monster[ind].kind + 48);
                print(0, monster[ind].x + dx[i], monster[ind].y + dy[j]);
                monster[ind].x += dx[i];
                monster[ind].y += dy[j];
                return 1;
            }
        }
    }
    return 0;
}
void move_monster(int x, int y) {
    for(int i = 0; i < tot_monster; i++) {
        if(monster[i].alive) {
            if(monster[i].active == 1 && !check_manhatan(monster[i].x, monster[i].y, x, y)) {
                if(monster[i].dist > 0) {
                    if(next_monster(i, x, y))
                        monster[i].dist--;
                }
            }
        }
    }
}

void print_kill(int kind) {
    print_message(kind + 20, 0);
}

void hit_message(int kind, int damage) {
    duration = 4;
    if(kind == 0) {
        print_message(25, damage);
    }
    if(kind == 1) {
        print_message(26, damage);
    }
    if(kind == 2) {
        print_message(27, damage);
    }
    if(kind == 3) {
        print_message(28, damage);
    }
    if(kind == 4) {
        print_message(29, damage);
    }
}

void fire(int x, int y, int damage) {
    if(tel_power > 0)
        damage *= 2;
    for(int i = 0; i < tot_monster; i++) {
        if(monster[i].alive) {
            if(check_manhatan(monster[i].x, monster[i].y, x, y)) {
                monster[i].hp -= damage;
                hit_message(monster[i].kind, damage);
                if(monster[i].hp <= 0) {
                    monster[i].alive = 0;
                    map[monster[i].x][monster[i].y] = last_monster[i];
                    print(0, monster[i].x, monster[i].y);
                    print_kill(monster[i].kind);
                }
            }
        }
    }
}



void throwi(int kind, int x, int y, int dir, int len, int damage) {
    if(tel_power > 0)
        damage *= 2;
    char last_tir;
    if(dir == 1) {
        while(len--) {
            x++;
            if(map[x][y] == '|' || map[x][y] == '_' || map[x][y] == 'T' || map[x][y] == 'G' || map[x][y] == 'K' || map[x][y] == 'p' || map[x][y] == 'O') {
                map[x - 1][y] = (char)(kind + 53);
                print(0, x - 1, y);
                return;
            }
            if(map[x][y] >= '0' && map[x][y] <= '4') {
                for(int i = 0; i < tot_monster; i++) {
                    if(monster[i].alive) {
                        if(monster[i].x == x && monster[i].y == y) {
                            monster[i].hp -= damage;
                            hit_message(monster[i].kind, damage);
                            if(monster[i].hp <= 0) {
                                monster[i].alive = 0;
                                map[monster[i].x][monster[i].y] = last_monster[i];
                                print(0, monster[i].x, monster[i].y);
                                print_kill(monster[i].kind);
                            }
                            if(kind == 2) {
                                monster[i].active = 2;
                            }
                            return;
                        }
                    }
                }
            }
            refresh();
            last_tir = map[x][y];
            refresh();
            map[x][y] = (char)(kind + 53);
            refresh();
            print(0, x, y);
            refresh();
            napms(50);
            refresh();
            map[x][y] = last_tir;
            refresh();
            print(0, x, y);
            refresh();
        }
        map[x][y] = (char)(kind + 53);
        print(0, x, y);
        return;
    }
    if(dir == 2) {
        while(len--) {
            x--;
            if(map[x][y] == '|' || map[x][y] == '_' || map[x][y] == 'T' || map[x][y] == 'G' || map[x][y] == 'K' || map[x][y] == 'p' || map[x][y] == 'O') {
                map[x + 1][y] = (char)(kind + 53);
                print(0, x + 1, y);
                return;
            }
            if(map[x][y] >= '0' && map[x][y] <= '4') {
                for(int i = 0; i < tot_monster; i++) {
                    if(monster[i].alive) {
                        if(monster[i].x == x && monster[i].y == y) {
                            monster[i].hp -= damage;
                            hit_message(monster[i].kind, damage);
                            if(monster[i].hp <= 0) {
                                monster[i].alive = 0;
                                map[monster[i].x][monster[i].y] = last_monster[i];
                                print(0, monster[i].x, monster[i].y);
                                print_kill(monster[i].kind);
                            }
                            if(kind == 2) {
                                monster[i].active = 2;
                            }
                            return;
                        }
                    }
                }
            }
            refresh();
            last_tir = map[x][y];
            refresh();
            map[x][y] = (char)(kind + 53);
            refresh();
            print(0, x, y);
            refresh();
            napms(50);
            refresh();
            map[x][y] = last_tir;
            refresh();
            print(0, x, y);
            refresh();
        }
        map[x][y] = (char)(kind + 53);
        print(0, x, y);
        return;
    }
    if(dir == 3) {
        while(len--) {
            y++;
            if(map[x][y] == '|' || map[x][y] == '_' || map[x][y] == 'T' || map[x][y] == 'G' || map[x][y] == 'K' || map[x][y] == 'p' || map[x][y] == 'O') {
                map[x][y - 1] = (char)(kind + 53);
                print(0, x, y - 1);
                return;
            }
            if(map[x][y] >= '0' && map[x][y] <= '4') {
                for(int i = 0; i < tot_monster; i++) {
                    if(monster[i].alive) {
                        if(monster[i].x == x && monster[i].y == y) {
                            monster[i].hp -= damage;
                            hit_message(monster[i].kind, damage);
                            if(monster[i].hp <= 0) {
                                monster[i].alive = 0;
                                map[monster[i].x][monster[i].y] = last_monster[i];
                                print(0, monster[i].x, monster[i].y);
                                print_kill(monster[i].kind);
                            }
                            if(kind == 2) {
                                monster[i].active = 2;
                            }
                            return;
                        }
                    }
                }
            }
            refresh();
            last_tir = map[x][y];
            refresh();
            map[x][y] = (char)(kind + 53);
            refresh();
            print(0, x, y);
            refresh();
            napms(50);
            refresh();
            map[x][y] = last_tir;
            refresh();
            print(0, x, y);
            refresh();
        }
        map[x][y] = (char)(kind + 53);
        print(0, x, y);
            return;
    }
    if(dir == 4) {
        while(len--) {
            y--;
            if(map[x][y] == '|' || map[x][y] == '_' || map[x][y] == 'T' || map[x][y] == 'G' || map[x][y] == 'K' || map[x][y] == 'p' || map[x][y] == 'O') {
                map[x][y + 1] = (char)(kind + 53);
                print(0, x, y + 1);
                return;
            }
            if(map[x][y] >= '0' && map[x][y] <= '4') {
                for(int i = 0; i < tot_monster; i++) {
                    if(monster[i].alive) {
                        if(monster[i].x == x && monster[i].y == y) {
                            monster[i].hp -= damage;
                            hit_message(monster[i].kind, damage);
                            if(monster[i].hp <= 0) {
                                monster[i].alive = 0;
                                map[monster[i].x][monster[i].y] = last_monster[i];
                                print(0, monster[i].x, monster[i].y);
                                print_kill(monster[i].kind);
                            }
                            if(kind == 2) {
                                monster[i].active = 2;
                            }
                            return;
                        }
                    }
                }
            }
            refresh();
            last_tir = map[x][y];
            refresh();
            map[x][y] = (char)(kind + 53);
            refresh();
            print(0, x, y);
            refresh();
            napms(50);
            refresh();
            map[x][y] = last_tir;
            refresh();
            print(0, x, y);
            refresh();
        }
        map[x][y] = (char)(kind + 53);
        print(0, x, y);
            return;
    }
}

void print_down() {
    if(weapon == 0) {
        mvaddstr(28, 112, "Weapon: \U00002692");
    }
    else if(weapon == 1) {
        mvaddstr(28, 112, "Weapon: \U0001F5E1");
    }
    else if(weapon == 2) {
        mvaddstr(28, 112, "Weapon: \U0001FA84");
    }
    else if(weapon == 3) {
        mvaddstr(28, 112, "Weapon: \U000027B3");
    }
    else if(weapon == 4) {
        mvaddstr(28, 112, "Weapon: \U00002694");
    }
    else {
        mvaddstr(28, 112, "Weapon:      ");
    }
    mvprintw(28, 2, "wealth 🧈🧈 : %.2lf", player_wealth);
    mvprintw(28, 42, "health 💖 : %.2lf", player_hp);
    mvprintw(28, 82, "food 🍏: %.2lf", player_hunger);
}

void edit_user(char* name_bazikon, int ted_bazi) {
    FILE* fptr = fopen("data.txt", "r");
    FILE* fptr2 = fopen("temp.txt", "w");
    char name_user[100];
    char password[100];
    char email[100];
    int emtiaz;
    int tala;
    int ted;
    long int tm;
    while(fscanf(fptr, "%s %s %s %d %d %d %ld", name_user, password, email, &emtiaz, &tala, &ted, &tm) == 7) {
        if(strcmp(name_bazikon, name_user) == 0) {
            emtiaz += (player_wealth + player_hunger/10);
            tala += player_wealth;
            ted++;
        }
        fprintf(fptr2, "%s %s %s %d %d %d %ld\n", name_user, password, email, emtiaz, tala, ted, tm);
    }
    fclose(fptr);
    fclose(fptr2);
    FILE* fptr3 = fopen("data.txt", "w");
    FILE* fptr4 = fopen("temp.txt", "r");
    while(fscanf(fptr4, "%s %s %s %d %d %d %ld", name_user, password, email, &emtiaz, &tala, &ted, &tm) == 7) {
        fprintf(fptr3, "%s %s %s %d %d %d %ld\n", name_user, password, email, emtiaz, tala, ted, tm);
    }
    fclose(fptr3);
    fclose(fptr4);
}

void move_player(int player_x, int player_y, char* name_bazikon, int ted_bazi, int level) {
    if(level == 4) {
        for(int i = 0; i < 50; i++) {
            for(int j = 0; j < 200; j++) {
                if(map[i][j] == 'A') {
                    map[i][j] = '.';
                }
            }
        }
        for(int i = 0; i < 50; i++) {
            int sik = 0;
            for(int j = 0; j < 200; j++) {
                if(map[i][j] == '.') {
                    sik = 1;
                    player_x = i;
                    player_y = j;
                    break;
                }
            }
            if(sik)
                break;
        }
    }
    map[player_x][player_y] = 'A';
    //last_move = '.';
    int ch;
    clear();
    show(level, player_x, player_y);
    print_all(level, 0);
    move(player_x, 2 * player_y);
    int m_ted = 0;
    noecho();
    int ok = 0;
    int next_ch = 0;
    int fsds = 0;
    int fsdss = 0;
    int fsdsss = 0;
    time_t fased1;
    time_t fased2;
    int ted_ramz = 0;
    time(&fased1);
    print_message(60, 0);
    while(1) {
        time(&fased2);
        if(difftime(fased2, fased1) >= 90) {
            for(int i = 0; i < 50; i++) {
                for(int j = 0; j < 200; j++) {
                    if(map[i][j] == 'c') {
                        map[i][j] = 'j';
                    }
                }
            }
        }
        if(tem[s_rm[player_x][player_y]] == 3) {
            clear();
            for(int i = player_x - 2; i <= player_x + 2; i++) {
                for(int j = player_y - 2; j <= player_y + 2; j++) {
                    print(0, i, j);
                }
            }
        }
        print_down();
        check_time();
        move(player_x, player_y * 2);
        if(tel_hp > 0)
            tel_hp--;
        if(tel_power > 0)
            tel_power--;
        if(tel_speed > 0)
            tel_speed--;
        if(ok == 2) {
            ok = 0;
            next_ch = 0;
        }
        int new_room = 0;
        mvprintw(3, 0, "🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰");
        if(last_move == '#')
            new_room = 1;
        if(level == 4) {
            int okss = 1;
            for(int i = 0; i < tot_monster; i++) {
                if(monster[i].alive == 1)
                    okss = 0;
            }
            if(okss) {
                edit_user(name_bazikon, ted_bazi);
                tel_hp = 0;
                tel_speed = 0;
                tel_power = 0;
                player_wealth = 0;
                player_hp = 100;
                player_hunger = 100;
                weapon = 0;
                while(true) {
                    clear();
                    mvprintw(LINES/2, COLS/2, "You Won!");
                    mvprintw(LINES/2 + 2, COLS/2 - 5, "You earnt %.2lf Golds", player_wealth);
                    int dmch = getch();
                    if(dmch == 'q') {
                        bazikon_menu(name_bazikon, ted_bazi + 1);
                        break;
                    }
                }
            }
        }
        if(!ok)
            if(tel_speed == 0 || tel_speed%2 == 1)
                ch = getch();
        if(ch == 'f') {
            ok = 0;
            next_ch = ch;
        }
        if(next_ch == 'f') {
            if(ok == 0) {
                ok = 1;
                if(tel_speed == 0 || tel_speed%2 == 1)
                    ch = getch();
            }
            else if(ok == 2) {
                next_ch = 0;
                ok = 0;
            }
        }
        move(player_x, 2 * player_y);
        if(last_move == 's') {
            if(ch == '>') {
                if(level > 0) {
                    save_map(name_bazikon, ted_bazi, level);
                    load_map(name_bazikon, ted_bazi, level - 1);
                    map[player_x][player_y] = 'A';
                    last_move = 'S';
                    move_player(player_x, player_y, name_bazikon, ted_bazi, level - 1);
                    break;
                }
            }
        }
        if(fsdsss == 1) {
            fsdsss = 0;
        }
        if(last_move == 'j' && fsdsss != 2) {
            map[player_x][player_y] = 'f';
            last_move = 'f';
            fsdsss = 1;
        }
        if(last_move == 'S' || last_move == 'V') {
            if(ch == '<') {
                if(level < 4) {
                    save_map(name_bazikon, ted_bazi, level);
                    load_map(name_bazikon, ted_bazi, level + 1);
                    map[player_x][player_y] = 'A';
                    last_move = 's';
                    move_player(player_x, player_y, name_bazikon, ted_bazi, level + 1);
                    break;
                }
            }
        }
        if(ch == 'p') {
            if(food[0] + food[1] + food[2] > 5) {
                    print_message(0, 0);
            }
            else if(last_move == 'c') {
                food[0]++;
                print_message(1, 0);
            }
            else if(last_move == 'l') {
                food[1]++;
                print_message(2, 0);
            }
            else if(last_move == 'q') {
                food[2]++;
                print_message(3, 0);
            }
            if(last_move == 'g') {
                aslahe[0] = 1;
                print_message(5, 0);
            }
            else if(last_move == 'd') {
                aslahe[1] += 10;
                print_message(6, 0);
            }
            else if(last_move == 'w') {
                aslahe[2] += 8;
                print_message(7, 0);
            }
            else if(last_move == 'a') {
                aslahe[3] += 20;
                print_message(8, 0);
            }
            else if(last_move == 'r') {
                aslahe[4] = 1;
                print_message(9, 0);
            }
            if(last_move == 'h') {
                telesm[0]++;
                print_message(14, 0);
            }
            else if(last_move == 'e') {
                telesm[1]++;
                print_message(15, 0);
            }
            else if(last_move == 'b') {
                telesm[2]++;
                print_message(16, 0);
            }
            else if(last_move == '6') {
                aslahe[1] ++;
                print_message(6, 0);
            }
            else if(last_move == '7') {
                aslahe[2] ++;
                print_message(7, 0);
            }
            else if(last_move == '8') {
                aslahe[3] ++;
                print_message(8, 0);
            }
            else if(last_move == 'n') {
                ancient = 1;
                print_message(80, 0);
            }
            map[player_x][player_y] = '.';
            last_move = '.';
        }
        // taviz aslahe



        if(ch == 'A') {
            if(weapon == 1) {
                if(aslahe[1] == 0) {
                    print_message(30, 0);
                }
                else {
                    int damch = last_partab;
                    if(damch == '4')
                        throwi(1, player_x, player_y, 4, 5, 12);
                    if(damch == '6')
                        throwi(1, player_x, player_y, 3, 5, 12);
                    if(damch == '2')
                        throwi(1, player_x, player_y, 1, 5, 12);
                    if(damch == '8')
                        throwi(1, player_x, player_y, 2, 5, 12);
                    aslahe[1]--;
                }
            }
            else if(weapon == 2) {
                if(aslahe[2] == 0) {
                    print_message(30, 0);
                }
                else {
                    int damch = last_partab;
                    if(damch == '4')
                        throwi(2, player_x, player_y, 4, 10, 15);
                    if(damch == '6')
                        throwi(2, player_x, player_y, 3, 10, 15);
                    if(damch == '2')
                        throwi(2, player_x, player_y, 1, 10, 15);
                    if(damch == '8')
                        throwi(2, player_x, player_y, 2, 10, 15);
                    aslahe[2]--;
                }
            }
            else if(weapon == 3) {
                if(aslahe[3] == 0) {
                    print_message(30, 0);
                }
                else {
                    int damch = last_partab;
                    if(damch == '4')
                        throwi(3, player_x, player_y, 4, 5, 5);
                    if(damch == '6')
                        throwi(3, player_x, player_y, 3, 5, 5);
                    if(damch == '2')
                        throwi(3, player_x, player_y, 1, 5, 5);
                    if(damch == '8')
                        throwi(3, player_x, player_y, 2, 5, 5);
                    aslahe[3]--;
                }
            }
        }



        if(ch == ' ') {
            if(weapon == -1) {
                print_message(19, 0);
            }
            else if(weapon == 0) {
                fire(player_x, player_y, 5);
            }
            else if(weapon == 4) {
                fire(player_x, player_y, 10);
            }
            else if(weapon == 1) {
                if(aslahe[1] == 0) {
                    print_message(30, 0);
                }
                else {
                    int damch = getch();
                    last_partab = damch;
                    if(damch == '4')
                        throwi(1, player_x, player_y, 4, 5, 12);
                    if(damch == '6')
                        throwi(1, player_x, player_y, 3, 5, 12);
                    if(damch == '2')
                        throwi(1, player_x, player_y, 1, 5, 12);
                    if(damch == '8')
                        throwi(1, player_x, player_y, 2, 5, 12);
                    aslahe[1]--;
                }
            }
            else if(weapon == 2) {
                if(aslahe[2] == 0) {
                    print_message(30, 0);
                }
                else {
                    int damch = getch();
                    last_partab = damch;
                    if(damch == '4')
                        throwi(2, player_x, player_y, 4, 10, 15);
                    if(damch == '6')
                        throwi(2, player_x, player_y, 3, 10, 15);
                    if(damch == '2')
                        throwi(2, player_x, player_y, 1, 10, 15);
                    if(damch == '8')
                        throwi(2, player_x, player_y, 2, 10, 15);
                    aslahe[2]--;
                }
            }
            else if(weapon == 3) {
                if(aslahe[3] == 0) {
                    print_message(30, 0);
                }
                else {
                    int damch = getch();
                    last_partab = damch;
                    if(damch == '4')
                        throwi(3, player_x, player_y, 4, 5, 5);
                    if(damch == '6')
                        throwi(3, player_x, player_y, 3, 5, 5);
                    if(damch == '2')
                        throwi(3, player_x, player_y, 1, 5, 5);
                    if(damch == '8')
                        throwi(3, player_x, player_y, 2, 5, 5);
                    aslahe[3]--;
                }
            }
        }
        if(ch == 'm') {
            if(weapon != -1) {
                print_message(10, 0);
            }
            else if(aslahe[0] == 0){
                print_message(11, 0);
            }
            else {
                weapon = 0;
                mvprintw(0, 0, "weapon changed to Mace successfully");
                duration = 4;
            }
        }
        if(ch == 'r') {
            if(weapon != -1) {
                print_message(10, 0);
            }
            else if(aslahe[4] == 0){
                print_message(11, 0);
            }
            else {
                weapon = 4;
                mvprintw(0, 0, "weapon changed to Sword successfully");
                duration = 4;
            }
        }
        if(ch == 'd') {
            if(weapon != -1) {
                print_message(10, 0);
            }
            else if(aslahe[1] == 0){
                print_message(11, 0);
            }
            else {
                weapon = 1;
                mvprintw(0, 0, "weapon changed to Dagger successfully");
                duration = 4;
            }
        }
        if(ch == 'o') {
            if(weapon != -1) {
                print_message(10, 0);
            }
            else if(aslahe[2] == 0){
                print_message(11, 0);
            }
            else {
                weapon = 2;
                mvprintw(0, 0, "weapon changed to Magic Wand successfully");
                duration = 4;
            }
        }
        if(ch == 'a') {
            if(weapon != -1) {
                print_message(10, 0);
            }
            else if(aslahe[3] == 0){
                print_message(11, 0);
            }
            else {
                weapon = 3;
                mvprintw(0, 0, "weapon changed to Normal arrow successfully");
                duration = 4;
            }
        }
        if(ch == 'w') {
            weapon = -1;
            print_message(13, 0);
        }

        // payan taviz aslahe


        if(ch == 'E') {
            food_menu(name_bazikon, ted_bazi, level);
        }
        if(ch == 'I') {
            aslahe_menu(name_bazikon, ted_bazi, level);
            print_message(4, 0);
        }
        if(ch == 'S') {
            char* tttp = (char*)malloc(100);
            refresh();
            clear();
            refresh();
            echo();
            curs_set(1);
            mvprintw(0, 0, "Enter the name for your save: ");
            mvscanw(0, 30, "%s", tttp);
            save_map(name_bazikon, ted_bazi, level);
            FILE* mount = fopen(tttp, "w");
            fprintf(mount, "%d %d %d %d %c %d %d", player_x, player_y, ted_bazi, level, last_move, player_color, hardness);
            fprintf(mount, " %lf", player_hp);
            fprintf(mount, " %lf", player_hunger);
            fprintf(mount, " %lf", player_wealth);
            fprintf(mount, " %d", weapon);
            for(int i = 0; i < 3; i++)
                fprintf(mount, " %d", food[i]);
            for(int i = 0; i < 5; i++)
                fprintf(mount, " %d", aslahe[i]);
            for(int i = 0; i < 3; i++)
                fprintf(mount, " %d", telesm[i]);
            fclose(mount);
            FILE* checki = fopen(The_Name, "r");
            char* checki2 = (char*)malloc(1000);
            int okssss = 1;
            if(checki != NULL) {
                while(fscanf(checki, "%s", checki2) == 1) {
                    if(strcmp(tttp, checki2) == 0) {
                        okssss = 0;
                    }
                }
                fclose(checki);
            }
            if(okssss) {
                FILE* thps = fopen(The_Name, "a+");
                fprintf(thps, "%s\n", tttp);
                fclose(thps);
            }
            for(int i = 0; i < 5; i++) {
                load_map(name_bazikon, ted_bazi, i);
                save_map(tttp, ted_bazi, i);
            }
            refresh();
            clear();
            noecho();
            curs_set(0);
            load_map(name_bazikon, ted_bazi, level);
            print_all(level, 0);
            refresh();
        }
        if(ch == 'q') {
            tel_hp = 0;
            tel_speed = 0;
            tel_power = 0;
            player_wealth = 0;
            player_hp = 100;
            player_hunger = 100;
            weapon = 0;
            char* tttp = (char*)malloc(100);
            strcpy(tttp, "RecentGame_");
            strcat(tttp, name_bazikon);
            save_map(name_bazikon, ted_bazi, level);
            strcpy(tttp, "RecentGame_");
            strcat(tttp, name_bazikon);
            FILE* mount = fopen(tttp, "w");
            fprintf(mount, "%d %d %d %d %c %d %d", player_x, player_y, ted_bazi, level, last_move, player_color, hardness);
            fprintf(mount, " %lf", player_hp);
            fprintf(mount, " %lf", player_hunger);
            fprintf(mount, " %lf", player_wealth);
            fprintf(mount, " %d", weapon);
            for(int i = 0; i < 3; i++)
                fprintf(mount, " %d", food[i]);
            for(int i = 0; i < 5; i++)
                fprintf(mount, " %d", aslahe[i]);
            for(int i = 0; i < 3; i++)
                fprintf(mount, " %d", telesm[i]);
            fclose(mount);
            FILE* checki = fopen(The_Name, "r");
            char* checki2 = (char*)malloc(1000);
            int okssss = 1;
            if(checki != NULL) {
                while(fscanf(checki, "%s", checki2) == 1) {
                    if(strcmp(tttp, checki2) == 0) {
                        okssss = 0;
                    }
                }
                fclose(checki);
            }
            if(okssss) {
                FILE* thps = fopen(The_Name, "a+");
                fprintf(thps, "%s\n", tttp);
                fclose(thps);
            }
            for(int i = 0; i < 5; i++) {
                load_map(name_bazikon, ted_bazi, i);
                save_map(tttp, ted_bazi, i);
            }
            refresh();
            clear();
            noecho();
            curs_set(1);
            //load_map(name_bazikon, ted_bazi, level);
            //print_all(level, 0);
            refresh();
            bazikon_menu(name_bazikon, ted_bazi);
            break;
        }
        if(ch == '6') {
            if(!check(level, player_x, player_y + 1)) {
                ok = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x][player_y + 1];
            print(level, player_x, player_y);
            move(player_x, 2 * (player_y + 1));
            player_y++;
        }
        if(ch == '4') {
            if(!check(level, player_x, player_y - 1)) {
                ok  = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x][player_y - 1];
            print(level, player_x, player_y);
            move(player_x, 2 * (player_y - 1));
            player_y--;
        }
        if(ch == '8') {
            if(!check(level, player_x - 1, player_y)) {
                ok  = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x - 1][player_y];
            print(level, player_x, player_y);
            move(player_x - 1, 2 * player_y);
            player_x--;
        }
        if(ch == '2') {
            if(!check(level, player_x + 1, player_y)){
                ok  = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x + 1][player_y];
            print(level, player_x, player_y);
            move(player_x + 1, 2 * player_y);
            player_x++;
        }
        if(ch == '3') {
            if(!check(level, player_x + 1, player_y + 1)){
                ok  = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x + 1][player_y + 1];
            print(level, player_x, player_y);
            move(player_x + 1, 2 * (player_y + 1));
            player_x++;
            player_y++;
        }
        if(ch == '1') {
            if(!check(level, player_x + 1, player_y - 1)){
                ok  = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x + 1][player_y - 1];
            print(level, player_x, player_y);
            move(player_x + 1, 2 * (player_y - 1));
            player_x++;
            player_y--;
        }
        if(ch == '7') {
            if(!check(level, player_x - 1, player_y - 1)){
                ok  = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x - 1][player_y - 1];
            print(level, player_x, player_y);
            move(player_x - 1, 2 * (player_y - 1));
            player_x--;
            player_y--;
        }
        if(ch == '9') {
            if(!check(level, player_x - 1, player_y + 1)){
                ok  = 2; 
                continue;
            }
            map[player_x][player_y] = last_move;
            last_move = map[player_x - 1][player_y + 1];
            print(level, player_x, player_y);
            move(player_x - 1, 2 * (player_y + 1));
            player_x--;
            player_y++;
        }
        if(ch == 'M') {
            m_ted++;
            print_all(level, m_ted);
        }
        if(ch == 'L') {
            telesm_menu(name_bazikon, ted_bazi, level);
        }
        if(fsds == 1) {
            mvaddstr(player_x, player_y * 2 - 2, "\U00002B1B");
            fsds = 2;
        }
        if(last_move == '^' && fsds != 2) {
            map[player_x][player_y] = '*';
            last_move = '*';
            fsds = 1;
        }
        if(last_move == '@' && (ch == '6' || ch == '9' || ch == '3')) {
            if(ancient == 0) {
                char* tttp = (char*)malloc(100);
            refresh();
            save_map(name_bazikon, ted_bazi, level);
            clear();
            refresh();
            echo();
            curs_set(1);
            mvprintw(0, 0, "Enter password for the Room: ");
            mvscanw(0, 30, "%s", tttp);
            load_map(name_bazikon, ted_bazi, level);
            int fdd = 1;
            if(!(strcmp(tttp, ramz) == 0)) {
                last_move = map[player_x][player_y - 1];
                print(level, player_x, player_y);
                move(player_x, 2 * (player_y - 1));
                player_y -= 1;
                ted_ramz++;
                fdd = 0;
                if(ted_ramz >= 3) {
                    player_hp -= 10;
                }
            }
            make_ramz();
            refresh();
            clear();
            noecho();
            curs_set(0);
            load_map(name_bazikon, ted_bazi, level);
            print_all(level, 0);
            if(fdd == 0)
                print_message(50 + ted_ramz - 1, 0);
            }
            else {
                int tmpsd = rand()%10;
                if(tmpsd == 0) {
                    ancient = 0;
                }
            if(ancient == 0) {
                char* tttp = (char*)malloc(100);
            refresh();
            save_map(name_bazikon, ted_bazi, level);
            clear();
            refresh();
            echo();
            curs_set(1);
            mvprintw(0, 0, "Enter password for the Room: ");
            mvscanw(0, 30, "%s", tttp);
            load_map(name_bazikon, ted_bazi, level);
            int fdd = 1;
            if(!(strcmp(tttp, ramz) == 0)) {
                last_move = map[player_x][player_y - 1];
                print(level, player_x, player_y);
                move(player_x, 2 * (player_y - 1));
                player_y -= 1;
                ted_ramz++;
                fdd = 0;
                if(ted_ramz >= 3) {
                    player_hp -= 10;
                }
            }
            make_ramz();
            refresh();
            clear();
            noecho();
            curs_set(0);
            load_map(name_bazikon, ted_bazi, level);
            print_all(level, 0);
            if(fdd == 0)
                print_message(50 + ted_ramz - 1, 0);
            }
            ancient = 0;
            }
        }
        if(last_move == 't') {
            print_message(40, 0);
        }
        if(last_move == '=') {
            int tmps = s_rm[player_x][player_y];
            if(tmps == 0) {
                show_dfs(level, rm[tmps + 1].x + 2, rm[tmps + 1].y + 2);
                show_dfs(level, rm[4].x + 2, rm[4].y + 2);
            }
            else if(tmps < 3) {
                show_dfs(level, rm[tmps + 1].x + 2, rm[tmps + 1].y + 2);
                show_dfs(level, rm[tmps - 1].x + 2, rm[tmps - 1].y + 2);
            }
            else if(tmps == 3) {
                show_dfs(level, rm[tmps - 1].x + 2, rm[tmps - 1].y + 2);
            }
            else if(tmps == 4) {
                show_dfs(level, rm[tmps + 1].x + 2, rm[tmps + 1].y + 2);
                show_dfs(level, rm[0].x + 2, rm[0].y + 2);
            }
            else if(tmps == 5) {
                show_dfs(level, rm[tmps - 1].x + 2, rm[tmps - 1].y + 2);
            }
        }
        if(fsdss == 1) {
            fsdss = 0;
        }
        if(last_move == 'P' && fsdss != 2) {
            map[player_x][player_y] = 'R';
            last_move = 'R';
            player_hp -= 10;
            fsdss = 1;
        }
        if(last_move == 'm') {
            player_wealth += 5;
            print_message(17, 0);
            map[player_x][player_y] = '.';
            last_move = '.';
        }
        if(last_move == 'M') {
            player_wealth += 30;
            print_message(18, 0);
            map[player_x][player_y] = '.';
            last_move = '.';
        }
        if(map[player_x][player_y] == '+' || map[player_x][player_y] == '#' || map[player_x][player_y] == 'A' || map[player_x][player_y] == '*')
            show(level, player_x, player_y);
        if(last_move == '+' && new_room) {
            print_message(70, 0);
        }
        map[player_x][player_y] = 'A';
        print(level, player_x, player_y);
        move(player_x, player_y * 2);
        if(last_move == 'j') {
            print_message(36, 0);
            player_hunger -= 20;
        }
        move_monster(player_x, player_y);
        check_monster(player_x, player_y);
        time(&then_h);
        if(player_hunger >= 50 && difftime(then_h, now_h) >= 10) {
            if(player_hp + (player_hunger/75) <= 100)
                player_hp += (player_hunger/75);
            else
                player_hp = 100;
            if(tel_hp > 0) {
                if(player_hp + (player_hunger/75) <= 100)
                    player_hp += (player_hunger/75);
                else
                    player_hp = 100;
            }
        }
        if(player_hunger < 20) {
            if(player_hp - ((50 - player_hunger)/100) >= 0)
                player_hp -= ((50 - player_hunger)/100);
            else
                player_hp = 0;
        }
        if(player_hunger - 1 >= 0)
            player_hunger -= 1;
        else
            player_hunger = 0;
        if(player_hp <= 0) {
            tel_hp = 0;
            tel_speed = 0;
            tel_power = 0;
            player_wealth = 0;
            player_hp = 100;
            player_hunger = 100;
            weapon = 0;
            break;
        }
    }
    while(true) {
        clear();
        mvprintw(LINES/2, COLS/2, "Looser!");
        int dmch = getch();
        if(dmch == 'q') {
            bazikon_menu(name_bazikon, ted_bazi);
            break;
        }
    }
    // mvprintw(0, 0, "kiiiiiiiiiiiiiiir");
    // sleep(5);
}

void initial_player(int TOTAL) {
    int tmp = rand()%TOTAL;
    while(tmp == 3 || tmp == 7)
        tmp = rand()%TOTAL;
    int rx = rand()%rm[tmp].width;
    int ry = rand()%rm[tmp].lenth;
    map[rm[tmp].x + 1 + rx][rm[tmp].y + 1 + ry] = 'A';
    initial_room = tmp;
    initial_x = rm[tmp].x + 1 + rx;
    initial_y = rm[tmp].y + 1 + ry;
}

void initial_stair(int TOTAL, int level) {
    int tmp = rand()%TOTAL;
    while(tmp == initial_room)
        tmp = rand()%TOTAL;
    int rx = rand()%rm[tmp].width;
    int ry = rand()%rm[tmp].lenth;
    if(map[rm[tmp].x + 1 + rx][rm[tmp].y + 1 + ry] != '.')
        initial_stair(TOTAL, level);
    initial_room = tmp;
    stair_x = rx + 1;
    stair_y = ry + 1;
    if(level == 3)
        map[rm[tmp].x + 1 + rx][rm[tmp].y + 1 + ry] = 'V';
    else
        map[rm[tmp].x + 1 + rx][rm[tmp].y + 1 + ry] = 'S';
}


void make_tala(int otagh) {
    int tmp;
    int rx, ry;
    if(tem[otagh] == 0) {
        tmp = rand()%6;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'm';
            }
        }
        tmp = rand()%7;
        if(tmp == 0) {
            while(true) {
                rx = rand()%rm[otagh].width;
                ry = rand()%rm[otagh].lenth;
                if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                    continue;
                }
                break;
            }
            map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'M';
        }
    }
    if(tem[otagh] == 1) {
        tmp = rand()%10;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'm';
            }
        }
        tmp = rand()%12;
        if(tmp == 0) {
            while(true) {
                rx = rand()%rm[otagh].width;
                ry = rand()%rm[otagh].lenth;
                if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                    continue;
                }
                break;
            }
            map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'M';
        }
    }
    if(tem[otagh] == 2) {
        tmp = rand()%6;
        if(tmp < 6) {
            for(int i = 0; i < tmp + 1; i++) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'm';
            }
        }
        tmp = 1 + rand()%3;
        while(tmp--) {
            while(true) {
                rx = rand()%rm[otagh].width;
                ry = rand()%rm[otagh].lenth;
                if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                    continue;
                }
                break;
            }
            map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'M';
        }
    }
    if(tem[otagh] == 3) {
        tmp = rand()%10;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'm';
            }
        }
        tmp = rand()%12;
        if(tmp == 0) {
            while(true) {
                rx = rand()%rm[otagh].width;
                ry = rand()%rm[otagh].lenth;
                if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                    continue;
                }
                break;
            }
            map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'M';
        }
    }
}

void make_aslahe(int otagh) {
    int tmp;
    int rx, ry;
    if(tem[otagh] == 0) {
        tmp = rand()%7;
        if(tmp < 1) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%5;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'g';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'd';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'w';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'a';
                }
                if(ttx == 4) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'r';
                }
            }
        }
    }
    if(tem[otagh] == 1) {
        tmp = rand()%10;
        if(tmp < 1) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%5;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'g';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'd';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'w';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'a';
                }
                if(ttx == 4) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'r';
                }
            }
        }
    }
    if(tem[otagh] == 2) {
        tmp = rand()%6;
        if(tmp < 1) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%5;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'g';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'd';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'w';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'a';
                }
                if(ttx == 4) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'r';
                }
            }
        }
    }
    if(tem[otagh] == 3) {
        tmp = rand()%7;
        if(tmp < 1) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%5;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'g';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'd';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'w';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'a';
                }
                if(ttx == 4) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'r';
                }
            }
        }
    }
}

void make_food(int otagh) {
    int tmp;
    int rx, ry;
    if(tem[otagh] == 0) {
        tmp = rand()%7;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%4;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'c';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'l';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'q';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'j';
                }
            }
        }
    }
    if(tem[otagh] == 1) {
        tmp = rand()%8;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%4;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'c';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'l';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'q';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'j';
                }
            }
        }
    }
    if(tem[otagh] == 2) {
        tmp = rand()%5;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%4;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'c';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'l';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'q';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'j';
                }
            }
        }
    }
    if(tem[otagh] == 3) {
        tmp = rand()%9;
        if(tmp < 1) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%4;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'c';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'l';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'q';
                }
                if(ttx == 3) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'j';
                }
            }
        }
    }
}

void make_tale(int otagh) {
    int tmp;
    int rx, ry;
    if(tem[otagh] == 0) {
        tmp = rand()%7;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'P';
            }
        }
    }
    if(tem[otagh] == 1) {
        tmp = rand()%5;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'P';
            }
        }
    }
    if(tem[otagh] == 2) {
        tmp = rand()%5;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'P';
            }
        }
    }
    if(tem[otagh] == 3) {
        tmp = rand()%4;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'P';
            }
        }
    }
}

void make_telesm(int otagh) {
    int tmp;
    int rx, ry;
    if(tem[otagh] == 0) {
        tmp = rand()%7;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'h';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'e';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'b';
                }
            }
        }
    }
    if(tem[otagh] == 1) {
        tmp = rand()%3;
        if(tmp < 3) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'h';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'e';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'b';
                }
            }
        }
    }
    if(tem[otagh] == 2) {
        tmp = rand()%5;
        if(tmp < 2) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'h';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'e';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'b';
                }
            }
        }
    }
    if(tem[otagh] == 3) {
        tmp = rand()%9;
        if(tmp < 1) {
            for(int i = 0; i < tmp + 1; i++) {
                int ttx = rand()%3;
                if(ttx == 0) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'h';
                }
                if(ttx == 1) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'e';
                }
                if(ttx == 2) {
                    while(true) {
                        rx = rand()%rm[otagh].width;
                        ry = rand()%rm[otagh].lenth;
                        if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                            continue;
                        }
                        break;
                    }
                    map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = 'b';
                }
            }
        }
    }
}

void make_monster(int otagh) {
    int tmp;
    int rx, ry;
    if(tem[otagh] == 0) {
        int tek = rand()%2 + hardness*2;
        for(int i = 0; i < tek; i++) {
            tmp = rand()%150;
            if(tmp < 50) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '0';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 5;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 0;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 4;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 90) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '1';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 10;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 1;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 6;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 120) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '2';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 15;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 2;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 8;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 140) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '3';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 20;
                monster[tot_monster].dist = 1e6;
                monster[tot_monster].kind = 3;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 10;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 150) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '4';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 30;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 4;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 15;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
        }
    }
   if(tem[otagh] == 1) {
        int tek = rand()%2 + 1 + hardness*2;
        for(int i = 0; i < tek; i++) {
            tmp = rand()%150;
            if(tmp < 30) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '0';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 5;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 0;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 4;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 60) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '1';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 10;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 1;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 6;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 100) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '2';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 15;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 2;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 8;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 130) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '3';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 20;
                monster[tot_monster].dist = 1e6;
                monster[tot_monster].kind = 3;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 10;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 150) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '4';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 30;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 4;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 15;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
        }
    }
    if(tem[otagh] == 2) {
        int tek = 7 + hardness*2;
        for(int i = 0; i < tek; i++) {
            tmp = rand()%150;
            if(tmp < 20) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '0';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 5;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 0;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 4;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 50) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '1';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 10;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 1;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 6;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 80) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '2';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 15;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 2;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 8;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 110) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '3';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 20;
                monster[tot_monster].dist = 1e6;
                monster[tot_monster].kind = 3;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 10;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 150) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '4';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 30;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 4;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 15;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
        }
    }
    if(tem[otagh] == 3) {
        int tek = 2 + rand()%2 + hardness;
        for(int i = 0; i < tek; i++) {
            tmp = rand()%150;
            if(tmp < 30) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '0';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 5;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 0;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 4;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 60) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '1';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 10;
                monster[tot_monster].dist = 0;
                monster[tot_monster].kind = 1;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 6;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 100) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '2';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 15;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 2;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 8;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 130) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '3';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 20;
                monster[tot_monster].dist = 1e6;
                monster[tot_monster].kind = 3;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 10;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
            else if(tmp < 150) {
                while(true) {
                    rx = rand()%rm[otagh].width;
                    ry = rand()%rm[otagh].lenth;
                    if(map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] != '.') {
                        continue;
                    }
                    break;
                }
                map[rm[otagh].x + 1 + rx][rm[otagh].y + 1 + ry] = '4';
                monster[tot_monster].x = rm[otagh].x + 1 + rx;
                monster[tot_monster].y = rm[otagh].y + 1 + ry;
                monster[tot_monster].hp = 30;
                monster[tot_monster].dist = 5;
                monster[tot_monster].kind = 4;
                monster[tot_monster].alive = 1;
                monster[tot_monster].damage = 15;
                monster[tot_monster].active = 0;
                tot_monster++;
            }
        }
    }
}

void make_app(int level, int TOTAL) {
    for(int i = 0; i < TOTAL; i++) {
        int j = rand()%3;
        while(j--) {
            int rx, ry;
            while(true) {
                rx = rand()%rm[i].width;
                ry = rand()%rm[i].lenth;
                if(map[rm[i].x + 1 + rx][rm[i].y + 1 + ry] != '.') {
                    continue;
                }
                if(map[rm[i].x + 1 + rx + 1][rm[i].y + 1 + ry] == '+') {
                    continue;
                }
                if(map[rm[i].x + 1 + rx - 1][rm[i].y + 1 + ry] == '+') {
                    continue;
                }
                if(map[rm[i].x + 1 + rx][rm[i].y + 1 + ry + 1] == '+') {
                    continue;
                }
                if(map[rm[i].x + 1 + rx][rm[i].y + 1 + ry - 1] == '+') {
                    continue;
                }
                break;
            }
            map[rm[i].x + 1 + rx][rm[i].y + 1 + ry] = 'O';
        }
        j = 1;
        int ytop = rand()%4;
        if(i < 5 && ytop == 0)
        while(j--) {
            int rx, ry;
            while(true) {
                rx = rand()%rm[i].width;
                ry = rand()%rm[i].lenth;
                if(map[rm[i].x + 1 + rx][rm[i].y + 1 + ry] != '.') {
                    continue;
                }
                break;
            }
            map[rm[i].x + 1 + rx][rm[i].y + 1 + ry] = '=';
        }
    }
    tot_monster = 0;
    for(int i = 0; i < TOTAL; i++) {
        make_tala(i);
        make_aslahe(i);
        make_food(i);
        make_telesm(i);
        make_tale(i);
        make_monster(i);
    }
}

void make_new_level(int level, int defualt, int dx1, int dy1, int dl, int dw) {
    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 200; j++) {
            map[i][j] = 'p';
            s_rm[i][j] = 0;
        }
    }
    for(int i = 0; i < 10; i++)
        tem[i] = 0;
    int TOTAL = 6 + rand()%3;
    while(TOTAL - 1 < defualt)
        TOTAL = 6 + rand()%3;
    for(int i = 0; i < TOTAL; i++) {
        rm[i].p_x[0] = -1;
        rm[i].p_x[1] = -1;
        rm[i].p_y[0] = -1;
        rm[i].p_y[1] = -1;
    }
    for(int i = 0; i < TOTAL; i++) {
        if(i == defualt) {
            rm[i].x = dx1;
            rm[i].y = dy1;
            rm[i].lenth = dl;
            rm[i].width = dw;
            continue;
        }
        int x1 = 5 +  rand()%2;
        int y1 = rand()%2;
        int l = 4 + rand()%7;
        int w = 4 + rand()%4;
        if(i > 3)
            x1 += 13;
        y1 += 1 + (i%4)*17;
        rm[i].x = x1;
        rm[i].y = y1;
        rm[i].lenth = l;
        rm[i].width = w;
    }
    if(level == 4) {
        TOTAL = 1;
        rm[0].x = 7;
        rm[0].y = 21;
        rm[0].lenth = 20;
        rm[0].width = 12;
    }
    for(int ind = 0; ind < TOTAL; ind++) {
        for(int i = 0; i < 40; i++) {
            for(int j = 0; j < 40; j++)
                rm[ind].mapc[i][j] = 'p';
        }
    }
    for(int i = 0; i < 10; i++)
        tem[i] = 0;
    int tmp = rand()%5;
    if(tmp == 0) {
        tem[3] = 1;
    }
    else if(tmp == 1) {
        tem[TOTAL - 1] = 1;
    }
    else if(tmp == 2) {
        tem[TOTAL - 1] = 3;
    }
    if(TOTAL == 1) {
        tem[0] = 2;
    }
    for(int ind = 0; ind < TOTAL; ind++) {
        if(tem[ind] == 0) {
            rm[ind].mapc[0][0] = '|';
            rm[ind].mapc[0][rm[ind].lenth + 1] = '|';
            rm[ind].mapc[rm[ind].width + 1][0] = '|';
            rm[ind].mapc[rm[ind].width + 1][rm[ind].lenth + 1] = '|';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][0] = '|';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][rm[ind].lenth + 1] = '|';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[0][i] = '_';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[rm[ind].width + 1][i] = '_';
            for(int i = 1; i < rm[ind].width + 1; i++) {
                for(int j = 1; j < rm[ind].lenth + 1; j++) {
                    rm[ind].mapc[i][j] = '.';
                }
            }
        }
        if(tem[ind] == 1) {
            rm[ind].mapc[0][0] = 'T';
            rm[ind].mapc[0][rm[ind].lenth + 1] = 'T';
            rm[ind].mapc[rm[ind].width + 1][0] = 'T';
            rm[ind].mapc[rm[ind].width + 1][rm[ind].lenth + 1] = 'T';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][0] = 'T';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][rm[ind].lenth + 1] = 'T';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[0][i] = 'T';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[rm[ind].width + 1][i] = 'T';
            for(int i = 1; i < rm[ind].width + 1; i++) {
                for(int j = 1; j < rm[ind].lenth + 1; j++) {
                    rm[ind].mapc[i][j] = '.';
                }
            }
        }
        if(tem[ind] == 2) {
            rm[ind].mapc[0][0] = 'G';
            rm[ind].mapc[0][rm[ind].lenth + 1] = 'G';
            rm[ind].mapc[rm[ind].width + 1][0] = 'G';
            rm[ind].mapc[rm[ind].width + 1][rm[ind].lenth + 1] = 'G';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][0] = 'G';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][rm[ind].lenth + 1] = 'G';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[0][i] = 'G';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[rm[ind].width + 1][i] = 'G';
            for(int i = 1; i < rm[ind].width + 1; i++) {
                for(int j = 1; j < rm[ind].lenth + 1; j++) {
                    rm[ind].mapc[i][j] = '.';
                }
            }
        }
        if(tem[ind] == 3) {
            rm[ind].mapc[0][0] = 'K';
            rm[ind].mapc[0][rm[ind].lenth + 1] = 'K';
            rm[ind].mapc[rm[ind].width + 1][0] = 'K';
            rm[ind].mapc[rm[ind].width + 1][rm[ind].lenth + 1] = 'K';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][0] = 'K';
            for(int i = 1; i < rm[ind].width + 1; i++)
                rm[ind].mapc[i][rm[ind].lenth + 1] = 'K';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[0][i] = 'K';
            for(int i = 1; i < rm[ind].lenth + 1; i++)
                rm[ind].mapc[rm[ind].width + 1][i] = 'K';
            for(int i = 1; i < rm[ind].width + 1; i++) {
                for(int j = 1; j < rm[ind].lenth + 1; j++) {
                    rm[ind].mapc[i][j] = '.';
                }
            }
        }
    }
    if(level > 0 && level < 4)
        rm[defualt].mapc[stair_x][stair_y] = 's';
    for(int ind = 0; ind < TOTAL; ind++) {
        for(int i = 0; i <= rm[ind].width + 1; i++) {
            map[rm[ind].x + i][rm[ind].y] = rm[ind].mapc[i][0];
            s_rm[rm[ind].x + i][rm[ind].y] = ind;
        }
        for(int i = 0; i <= rm[ind].width + 1; i++) {
            map[rm[ind].x + i][rm[ind].y + rm[ind].lenth + 1] = rm[ind].mapc[i][rm[ind].lenth + 1];
            s_rm[rm[ind].x + i][rm[ind].y + rm[ind].lenth + 1] = ind;
        }
        for(int i = 0; i <= rm[ind].lenth + 1; i++) {
            map[rm[ind].x][rm[ind].y + i] = rm[ind].mapc[0][i];
            s_rm[rm[ind].x][rm[ind].y + i] = ind;
        }
        for(int i = 0; i <= rm[ind].lenth + 1; i++) {
            s_rm[rm[ind].x + rm[ind].width + 1][rm[ind].y + i] = ind;
        }
        for(int i = 1; i < rm[ind].width + 1; i++) {
            for(int j = 1; j < rm[ind].lenth + 1; j++) {
                map[rm[ind].x + i][rm[ind].y + j] = rm[ind].mapc[i][j];
                s_rm[rm[ind].x + i][rm[ind].y + j] = ind;
            }
        }
    }
    make_root_map(TOTAL);
        for(int ind = 0; ind < TOTAL; ind++) {
        for(int i = 0; i <= rm[ind].width + 1; i++)
            map[rm[ind].x + i][rm[ind].y] = rm[ind].mapc[i][0];
        for(int i = 0; i <= rm[ind].width + 1; i++)
            map[rm[ind].x + i][rm[ind].y + rm[ind].lenth + 1] = rm[ind].mapc[i][rm[ind].lenth + 1];
        for(int i = 0; i <= rm[ind].lenth + 1; i++)
            map[rm[ind].x][rm[ind].y + i] = rm[ind].mapc[0][i];
        for(int i = 0; i <= rm[ind].lenth + 1; i++)
            map[rm[ind].x + rm[ind].width + 1][rm[ind].y + i] = rm[ind].mapc[rm[ind].width + 1][i];
        for(int i = 1; i < rm[ind].width + 1; i++) {
            for(int j = 1; j < rm[ind].lenth + 1; j++) {
                map[rm[ind].x + i][rm[ind].y + j] = rm[ind].mapc[i][j];
            }
        }
    }
    if(level == 0) {
        initial_player(TOTAL);
        initial_stair(TOTAL, level);
    }
    else if(level < 4) {
        initial_stair(TOTAL, level);
    }
    make_app(level, TOTAL);
}


void make_new_game(char* name_bazikon, int ted_bazi) {
    for(int i = 0; i < 3; i++)
        food[i] = 0;
    for(int i = 0; i < 5; i++)
        aslahe[i] = 0;
    aslahe[0] = 1;
    for(int i = 0; i < 3; i++)
        telesm[i] = 0;
    weapon = 0;
    for(int i = 0; i <= 4; i++) {
        for(int j = 0; j < 50; j++)
        last_monster[j] = '.';
        if(i == 0) {
            make_new_level(0, -1, -1, -1, -1, -1);
            save_map(name_bazikon, ted_bazi, i);
        }
        else {
            make_new_level(i, initial_room, rm[initial_room].x, rm[initial_room].y, rm[initial_room].lenth, rm[initial_room].width);
            save_map(name_bazikon, ted_bazi, i);
        }
        load_map(name_bazikon, ted_bazi, i);
    }
}


// int main() {
//     srand(time(NULL));
//     setlocale(LC_ALL, "");
//     initscr();
//     keypad(stdscr, TRUE);
//     start_color();
//     curs_set(0);
//     char* name_bazikon = (char*)malloc(100);
//     strcpy(name_bazikon , "manam");
//     for(int i = 0; i < 2; i++) {
//         make_new_game(name_bazikon, i);
//         load_map(name_bazikon, i, 0);
//     } 
//     move_player(initial_x, initial_y, name_bazikon, 1, 0);
//     print_all(0, 1);
//     while(1) {
//         int ch = getch();
//     }
//     refresh();
//     endwin();
//     return 0;
// }
