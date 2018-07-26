//引入头文件
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <dos.h>

//宏定义
#define HEIGHT 23
#define WIDTH 80
#define LEN sizeof(struct commodity)
#define FORMAT "%-15d%-15s%-15.1lf%-15.1lf%-15.1lf"
#define DATA comm[i].num,comm[i].name,comm[i].price,comm[i].count,comm[i].total

struct commidity{
    int num;
    char name[15];
    double price;
    double count;
    double total;
} ;
//结构体数组
struct commidity comm[50];



void start();
void goToXY();
void drawBorder();
void drawTitle();
void admin_main();
void cus_main();

int i,j,k;//定义循环变量


int main()
{
    start();

    return 0;
}
void start(){
    int state = 0;//保存用户的身份选择信息，0为管理员，1为顾客
    system("color f1");
    drawBorder();
    drawTitle();
    goToXY(24,9);
    printf("请选择您的身份进行登录或注册：");
    goToXY(26,12);
    printf("①  ★  超市管理员");
    goToXY(26,14);
    printf("②      顾客");

    while(TRUE){
        char choice;
        choice = getch();
        if(choice == '8'){
            goToXY(30,14);
            printf("\b  ");
            goToXY(30,12);
            printf("★");
            state = 0;
        }
        else if(choice == '2'){
            goToXY(30,12);
            printf("\b  ");
            goToXY(30,14);
            printf("★");
            state = 1;
        }else if(choice == '5'){
            switch(state){
                case 0:
                    admin_main();
                    break;

                case 1:
                    cus_main();
                    break;
            }
        }
    }
    getchar();
}
void goToXY(int x,int y){
    COORD position;
    position.X = x;
    position.Y = y;
    HANDLE handle;
    handle=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, position);
}
void drawBorder(){
    goToXY(0,0);
    for(i = 1;i < WIDTH;i++){
        printf("=");
    }
    goToXY(0,0);
    printf("╔");
    goToXY(WIDTH-2,0);
    printf("╗");
    for(i = 1;i < HEIGHT;i++){
        goToXY(0,i);
        printf("║");
        goToXY(WIDTH-2,i);
        printf("║");
    }
    goToXY(0,HEIGHT);
    for(i = 1;i < WIDTH;i++){
            printf("=");
    }
    goToXY(0,HEIGHT);
    printf("╚");
    goToXY(WIDTH-2,HEIGHT);
    printf("╝");
}
void drawTitle(){
    goToXY(25,3);
    for(i = 0;i < 26;i++){
        printf("*");
    }
    goToXY(25,5);
    for(i = 0;i < 26;i++){
        printf("*");
    }
    for(i = 4;i < 5;i++){
        goToXY(25,i);
        printf("*");
        goToXY(50,i);
        printf("*");
    }
    goToXY(30,4);
    printf("欢迎使用MMS V1.0");
}
void admin_main(){
    exit(0);
}
void cus_main(){

}
