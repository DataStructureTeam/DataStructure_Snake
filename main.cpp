//#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>

#define  N 22
using namespace std;


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

