//#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>

#define  N 22
# define de_lenth 5//蛇初始长度
# define ROW_MAX 20//地图行
# define LINE_MAX 30//地图列

int ROW = ROW_MAX;
int LINE = LINE_MAX;
int Head_x = ROW_MAX / 2, Head_y = LINE_MAX / 2;//蛇的初始坐标
int Head_v = 5;//判断是否为头
int Tail_x = 0, Tail_y = 0;//蛇尾坐标
int count = 0;//计数
char direct = 'a';//蛇移动的方向
int times = 1;

using namespace std;



typedef struct Snakebody
{
    int x, y;     //身体的坐标
    struct Snakebody *next;    //结构指针
}Snakebody;      //创建保持身体的链表

//int main() {
//    cout << "DataStructure_Snake" << endl;
//    return 0;
//}

/*李锡堃的小组任务3:
 * 让蛇动起来:
 *      1.蛇的移动
 *      2.蛇的方向
 *      3.控制方向
 *      4.调整（倍率，边界等）*/

void MoveTail(int snake[ROW_MAX][LINE_MAX]);//蛇尾部的移动
void run(char map[ROW_MAX][LINE_MAX], int snake[ROW_MAX][LINE_MAX]);//蛇的移动

void MoveTail(int snake[ROW_MAX][LINE_MAX]) {

    if (snake[Tail_x][Tail_y] + 1 == snake[Tail_x - 1][Tail_y]) {

        snake[Tail_x][Tail_y] = 0;
        Tail_x--;
    } else if (snake[Tail_x][Tail_y] + 1 == snake[Tail_x + 1][Tail_y]) {

        snake[Tail_x][Tail_y] = 0;
        Tail_x++;
    } else if (snake[Tail_x][Tail_y] + 1 == snake[Tail_x][Tail_y - 1]) {

        snake[Tail_x][Tail_y] = 0;
        Tail_y--;
    } else {

        snake[Tail_x][Tail_y] = 0;
        Tail_y++;
    }
}

void run(char map[ROW_MAX][LINE_MAX], int snake[ROW_MAX][LINE_MAX]) {
/*
上   -32 0xffffffe0 72 H
下   -32 0xffffffe0 80 P
左   -32 0xffffffe0 75 K
右   -32 0xffffffe0 77 M
*/
    char sh, ch;
    while (1) {

        if (JudgeWall()) {
            /**********判断键盘是否敲击***********/
            if (kbhit()) {

                ch = getch();
                if (ch == -32) {

                    sh = getch();
                    if (direct == 'w') {

                        if (sh == 'P')
                            continue;
                    } else if (direct == 's') {

                        if (sh == 'H')
                            continue;
                    } else if (direct == 'a') {

                        if (sh == 'M')
                            continue;
                    } else {

                        if (sh == 'K')
                            continue;
                    }

                    switch (sh) {

                        case 'H':
                            direct = 'w';
                            break;
                        case 'P':
                            direct = 's';
                            break;
                        case 'K':
                            direct = 'a';
                            break;
                        case 'M':
                            direct = 'd';
                            break;
                    }
                } else {

                    if (direct == 'w') {

                        if (ch == 's' || ch == 'S')
                            continue;
                    } else if (direct == 's') {

                        if (ch == 'w' || ch == 'W')
                            continue;
                    } else if (direct == 'a') {

                        if (ch == 'd' || ch == 'D')
                            continue;
                    } else if (direct == 'd') {

                        if (ch == 'a' || ch == 'A')
                            continue;
                    }

                    switch (ch) {

                        case 'w':
                        case 'W':
                            direct = 'w';
                            break;
                        case 's':
                        case 'S':
                            direct = 's';
                            break;
                        case 'a':
                        case 'A':
                            direct = 'a';
                            break;
                        case 'd':
                        case 'D':
                            direct = 'd';
                            break;
                        case 27:
                            int i, j;
                            for (i = ROW / 2 - 1; i <= ROW / 2 + 1; ++i) {
                                gotoxy(0, i);
                                for (j = 0; j <= LINE; ++j)
                                    putchar(' ');
                            }

                            gotoxy(LINE / 2 - 8 < 0 ? 0 : LINE / 2 - 8, ROW / 2);
                            system("pause");

                            break;

                    }
                }
            }
            /************************************/

            /**************蛇的运动******************/
            switch (direct) {

                case 'w':
                    if (snake[Head_x - 1][Head_y] != 0)
                        return;

                    snake[Head_x - 1][Head_y] = ++Head_v;
                    Head_x--;
                    if (EatFood(map))
                        MoveTail(snake);
                    else
                        CreateFood(map, snake);
                    break;
                case 'a':
                    if (snake[Head_x][Head_y - 1] != 0)
                        return;

                    snake[Head_x][Head_y - 1] = ++Head_v;
                    Head_y--;
                    if (EatFood(map))
                        MoveTail(snake);
                    else
                        CreateFood(map, snake);
                    break;
                case 's':
                    if (snake[Head_x + 1][Head_y] != 0)
                        return;

                    snake[Head_x + 1][Head_y] = ++Head_v;
                    Head_x++;
                    if (EatFood(map))
                        MoveTail(snake);
                    else
                        CreateFood(map, snake);
                    break;
                case 'd':
                    if (snake[Head_x][Head_y + 1] != 0)
                        return;

                    snake[Head_x][Head_y + 1] = ++Head_v;
                    Head_y++;
                    if (EatFood(map))
                        MoveTail(snake);
                    else
                        CreateFood(map, snake);
                    break;
            }
            system("cls");
            TraverseMap(map, snake);
            /****************************************/
        } else
            return;
        dely();
    }
}



/*谭裕仁*/
//游戏界面标记 包括空、墙、食物、蛇头、蛇身
#define KONG 0
#define WALL 1
#define FOOD 2
#define HEAD 3
#define BODY 4

//方向键上下左右 暂停 退出
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ESC 27

void HideCursor();

void CursorJump(int x, int y);

void InitInterface();

void color(int c);

void ReadGrade();

void WriteGrade();

void InitSnake();

void RandFood();

void JudgeFunc(int x, int y);

void DrawSnake(int flag);

void MoveSnake(int x, int y);

void run(int x, int y);

void Game();


int max, grade;

int main() {
#pragma warning (disable:4996)
    max = 0, grade = 0;
    system("title 贪吃蛇");
    system("mode con cols=84 lines=23");
    HideCursor();
    ReadGrade();
    InitInterface();
    InitSnake();
    srand((unsigned int) time(NULL));
    RandFood();
    DrawSnake(1);
    Game();
    return 0;
}

void HideCursor() {
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1;
    curInfo.bVisible = FALSE;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &curInfo);
}

void CursorJump(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
}

//初始化界面
void InitInterface() {
    color(6);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (j == 0 || j == COL - 1) {
                face[i][j] = WALL;
                CursorJump(2 * j, i);
                printf("■");
            } else if (i == 0 || i == ROW - 1) {
                face[i][j] = WALL;
                printf("■");
            } else {
                face[i][j] = KONG;
            }
        }
    }
    color(7);
    CursorJump(0, ROW);
    printf("当前得分:%d", grade);
    CursorJump(COL, ROW);
    printf("历史最高得分:%d", max);
}

//颜色设置
void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);

}

void ReadGrade() {
    FILE *pf = fopen("贪吃蛇最高得分记录.txt", "r");
    if (pf == NULL)
        pf = fopen("贪吃蛇最高得分记录.txt", "w");
    fwrite(&max, sizeof(int), 1, pf);
}

fseek(pf,
0, SEEK_SET);
fread(&max,
sizeof(int), 1, pf);
fclose(pf);
pf = NULL;
}

void WriteGrade() {
    FILE *pf = fopen("贪吃蛇最高得分记录.txt", "w");
    if (pf == NULL) {
        printf("保存最高得分记录失败\n");
        exit(0);
    }
    fwrite(&grade, sizeof(int), 1, pf);
    fclose(pf);
    pf = NULL;
}

//创建食物
void RandFood() {
    int i, j;
    do {

        i = rand() % ROW;
        j = rand() % COL;
    } while (face[i][j] != KONG);
    face[i][j] = FOOD;
    color(12);
    CursorJump(2 * j, i);
    printf("●");
}

//打印蛇与覆盖蛇
void DrawSnake(int flag) {
    if (flag == 1) {
        color(10);
        CursorJump(2 * snake.x, snake.y);
        printf("■");
        for (int i = 0; i < snake.len; i++) {
            CursorJump(2 * body[i].x, body[i].y);
            printf("□");
        }
    } else {
        if (body[snake.len - 1].x != 0) {

            CursorJump(2 * body[snake.len - 1].x, body[snake.len - 1].y);
            printf("  ");
        }
    }
}

/*韩帅恒*/
int gameover;

int x1, y1; // 随机出米

int x, y;

long start;

//=======================================
//类的实现与应用initialize
//=======================================

//下面定义贪吃蛇的坐标类
class snake_position {
public:

    int x, y;      //x表示行，y表示列

    snake_position() {};

    void initialize(int &);//坐标初始化


};

snake_position position[(N - 2) * (N - 2) + 1]; //定义贪吃蛇坐标类数组，有(N-2)*(N-2)个坐标

void snake_position::initialize(int &j) {
    x = 1;

    y = j;
}


//下面定义贪吃蛇的棋盘图

class snake_map {

private:

    char s[N][N];//定义贪吃蛇棋盘，包括墙壁。

    int grade, length;

    int gamespeed; //前进时间间隔

    char direction; // 初始情况下，向右运动

    int head, tail;

    int score;

    bool gameauto;

public:

    snake_map(int h = 4, int t = 1, int l = 4, char d = 77, int s = 0) : length(l), direction(d), head(h), tail(t),
                                                                         score(s) {}

    int updata_game();

    void setpoint();

};

//随机产生米
void snake_map::setpoint() {
    srand(time(0));

    do {

        x1 = rand() % (N - 2) + 1;

        y1 = rand() % (N - 2) + 1;

    } while (s[x1][y1] != ' ');

    s[x1][y1] = '*';
}

char key;

int snake_map::updata_game() {
    gameover = 1;

    key = direction;

    start = clock();

    while ((gameover = (clock() - start <= gamespeed)) && !kbhit());

    //如果有键按下或时间超过自动前进时间间隔则终止循环



    if (gameover) {

        getch();

        key = getch();
    }

    if (key == ' ') {
        while (getch() != ' ') {};//这里实现的是按空格键暂停，按空格键继续的功能，但不知为何原因，需要按两下空格才能继续。这是个bug。
    } else

        direction = key;

    switch (direction) {
        case 72:
            x = position[head].x - 1;
            y = position[head].y;
            break; // 向上

        case 80:
            x = position[head].x + 1;
            y = position[head].y;
            break; // 向下

        case 75:
            x = position[head].x;
            y = position[head].y - 1;
            break; // 向左

        case 77:
            x = position[head].x;
            y = position[head].y + 1; // 向右

    }

    if (!(direction == 72 || direction == 80 || direction == 75 || direction == 77))   // 按键非方向键

        gameover = 0;

    else if (x == 0 || x == N - 1 || y == 0 || y == N - 1)   // 碰到墙壁

        gameover = 0;

    else if (s[x][y] != ' ' && !(x == x1 && y == y1))    // 蛇头碰到蛇身

        gameover = 0;

    else if (x == x1 && y == y1) { // 吃米，长度加1

        length++;

        if (length >= 8 && gameauto) {

            length -= 8;

            grade++;

            if (gamespeed >= 200)

                gamespeed -= 200; // 改变贪吃蛇前进速度

            else

                gamespeed = 100;

        }

        s[x][y] = '#';  //更新蛇头

        s[position[head].x][position[head].y] = '*'; //吃米后将原先蛇头变为蛇身

        head = (head + 1) % ((N - 2) * (N - 2));   //取蛇头坐标

        position[head].x = x;

        position[head].y = y;

        show_game();

        gameover = 1;

        score += grade * 20;  //加分

        setpoint();   //产生米

    } else { // 不吃米

        s[position[tail].x][position[tail].y] = ' ';//将蛇尾置空

        tail = (tail + 1) % ((N - 2) * (N - 2));//更新蛇尾坐标

        s[position[head].x][position[head].y] = '*';  //将蛇头更为蛇身

        head = (head + 1) % ((N - 2) * (N - 2));

        position[head].x = x;

        position[head].y = y;

        s[position[head].x][position[head].y] = '#'; //更新蛇头

        gameover = 1;

    }
    return gameover;

}

