//引入头文件
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

//宏定义
#define HEIGHT 23
#define WIDTH 80
#define USER_1 "user_1.dat"
#define USER_2 "user_2.dat"
#define PRODUCT "product.dat"
#define MES "mes.dat"
#define BUY_RECORD "buy_record.dat"
#define VAULT "vault.dat"
#define DAY_SOLD "day_sold.dat"


struct message{
    char name[30];
    char content[100];
    char contract[20];
    char date[30];
};//保存用户的反馈信息
//记录用户反馈信息
struct record{
    char name[20];
    char product[30];
    int quantity;
    char date[15];
};//保存用户的购买记录
//记录用户购买记录
struct commodity{
    int num;//商品编号
    char name[15];//商品名称
    double in_price;//进价
    double out_price;//售价
    char desc[100];//商品描述
    int count;//库存量
    char sort[30];//类别
    int sold;//销售量
    char provider[50];//生产商
    int cart_count;//顾客放在购物车里面的数量
};
//结构体数组
struct user{
    char name[20];
    char sex[10];
    char phone[20];
    char mail[30];
    char pass[20];
    char pass_double[20];
};
//保存用户的信息
struct day_sold{
    char date[15];
    int count;
};


void start();
void goToXY(int x,int y);
void drawBorder();
void drawTitle();
void admin_main(char *name);
void cus_main(char *name);
void progressBar(char *text);//进度条
void admin_login();
void cus_login();
void admin_register();
void cus_register();
void admin_login_login();
void cus_login_login();
void hideCursor();
void switch_admin(int choice,char *name);
void switch_cus(int choice,char *name);
void del_comm(char *name);
void color_change(char *name);
void send_mes(char *name);
void receive_mes(char *name);
int count();//计算用户反馈信息的条数
void show_page(char *file_name,char *str,char *name,int ver);
void page_up(char *file_name,char *str,int num,char *name,int ver);
void page_down(char *file_name,char *str,int num,char *name,int ver);
void drawInBorder();//画出分页查询的内部表格边框
void change_comm(char *name);
void add_comm(char *name);
void buy_record(char *name);
void buy_product(char *name);
void sort_search(char *name,int ver);
void admin_unsubscribe(char *name);
void cus_unsubscribe(char *name);
void out_file(char *name,int ver);
void info_change(char *name,int ver);
void search_comm(char *name,int ver);
void sales_ranking_query(char *name,int ver);
void buttom_title1(int num,int max_num,int ver);
void buttom_title2(int num,int max_num);
void del_pro(int del_num);
double vault(double out_price,int number);
void alert(char *name);
void sold_chart(char *name);
int count_days(char *min_date,char *max_date);
void show_chart(char *name,int days);
void chart_up(int num,char *name,int days);
void chart_down(int num,char *name,int days);
int count_sold(char * name);
void updown_bottom();
void file_oi(char *name);
void in_file(char *name);
int ver_comm(struct commodity comm);
void move_to_shopping_cart(char *name);
void empty_cart(char *name);
void del_cart(char *name);



int i,j,k;//定义循环变量


int main(){
    system("mode con cols=80 lines=24");
    system("color f1");
    hideCursor();
    start();
    return 0;
}
void start(){
    int state = 0;//保存用户的身份选择信息，0为管理员，1为顾客
    drawBorder();
    drawTitle();
    goToXY(24,9);
    printf("请选择您的身份进行登录或注册：");
    goToXY(26,12);
    printf("①  ★  超市管理员");
    goToXY(26,14);
    printf("②      顾客");
    goToXY(26,16);
    printf("③      退出系统");
    updown_bottom();
    while(TRUE){
        char choice;
        choice = getch();
        if(choice == 72){
            goToXY(30,12+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1){
                state = 2;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == 80){
            goToXY(30,12+state*2);
            printf("\b  ");
            state += 1;
            if(state == 3){
                state = 0;
            }
            goToXY(30,12+state*2);
            printf("★");
        }else if(choice == '\r'){
            switch(state){
                case 0:
                    progressBar("系统正在加载，请稍候！");
                    Sleep(100);
                    system("cls");
                    admin_login();
                    break;

                case 1:
                    progressBar("系统正在加载，请稍候！");
                    Sleep(100);
                    system("cls");
                    cus_login();
                    break;
                case 2:
                    system("cls");
                    drawBorder();
                    goToXY(28,11);
                    printf("感谢您的使用，再见！");
                    goToXY(0,24);
                    exit(0);
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
void admin_main(char *name){
    drawBorder();
    goToXY(60,3);
    printf("欢迎您，%s!",name);
    goToXY(23,22);
    printf("超市的营业额为：%.1lf元",vault(0,0));
    goToXY(28,3);
    printf("****功能列表****");
    goToXY(29,5);
    printf("1.添加商品信息");
    goToXY(29,6);
    printf("2.修改商品信息");
    goToXY(29,7);
    printf("3.分类查询商品");
    goToXY(29,8);
    printf("4.删除商品信息");
    goToXY(29,9);
    printf("5.用户反馈信息");
    goToXY(29,10);
    printf("6.关键字查询");
    goToXY(29,11);
    printf("7.销量排序查询");
    goToXY(29,12);
    printf("8.分页显示商品信息");
    goToXY(29,13);
    printf("9.更新基本信息");
    goToXY(29,14);
    printf("10.销量日报表");
    goToXY(29,15);
    printf("11.更改界面颜色");
    goToXY(29,16);
    printf("12.商品信息导出/导入");
    goToXY(29,17);
    printf("13.注销账户");
    goToXY(29,18);
    printf("14.退出");
    goToXY(25,20);
    printf("请输入您的选择：|");
    goToXY(45,20);
    printf("|");
    goToXY(43,20);
    int choice;
    scanf("%d",&choice);
    switch_admin(choice,name);


}
void switch_admin(int choice,char *name){
	switch(choice){
        case 1:
            add_comm(name);
            break;
        case 2:
            change_comm(name);
            break;
        case 3:
            sort_search(name,1);
            break;
        case 4:
            del_comm(name);
            break;
        case 5:
            receive_mes(name);
            break;
        case 6:
            search_comm(name,1);
            break;
        case 7:
            sales_ranking_query(name,1);
            break;
        case 8:
            show_page(PRODUCT,"商品信息",name,1);
            break;
        case 9:
            info_change(name,1);
            break;
        case 10:
            sold_chart(name);
            break;
        case 11:
            color_change(name);
            break;
        case 12:
            file_oi(name);
            break;
        case 13:
            admin_unsubscribe(name);
            break;
        case 14:
            system("cls");
            start();
            break;
    }
}
void cus_main(char *name){
    drawBorder();
    goToXY(60,3);
    printf("欢迎您，%s!",name);
    goToXY(28,3);
    printf("****功能列表****");
    goToXY(29,5);
    printf("1.选购商品");
    goToXY(29,6);
    printf("2.关键字查询");
    goToXY(29,7);
    printf("3.分类查询商品");
    goToXY(29,8);
    printf("4.反馈超市信息");
    goToXY(29,9);
    printf("5.商品购买记录");
    goToXY(29,10);
    printf("6.销量排序查询");
    goToXY(29,11);
    printf("7.更新基本信息");
    goToXY(29,12);
    printf("8.分页查看商品信息");
    goToXY(29,13);
    printf("9.更改界面颜色");
    goToXY(29,14);
    printf("10.商品信息导出");
    goToXY(29,15);
    printf("11.注销账户");
    goToXY(29,16);
    printf("12.退出");




    goToXY(25,20);
    printf("请输入您的选择：|");
    goToXY(45,20);
    printf("|");
    goToXY(43,20);
    int choice;
    scanf("%d",&choice);
    switch_cus(choice,name);
}
void switch_cus(int choice,char *name){
	switch(choice){
        case 1:
            buy_product(name);
            break;
        case 2:
            search_comm(name,2);
            break;
        case 3:
            sort_search(name,2);
            break;
        case 4:
            send_mes(name);
            break;
        case 5:
            buy_record(name);
            break;
        case 6:
            sales_ranking_query(name,2);
            break;
        case 7:
            info_change(name,2);
            break;
        case 8:
            show_page(PRODUCT,"商品信息",name,2);
            break;
        case 9:
            color_change(name);
            break;
        case 10:
            out_file(name,2);
            break;
        case 11:
            cus_unsubscribe(name);
            break;
        case 12:
        	system("cls");
            start();
            break;
        default:
            break;
    }
}
void progressBar(char *text){
    /*
    goToXY(26,21);
    printf(text);
    goToXY(19,19);
    for(i = 0;i <= 20;i++){
        goToXY(19+i*2,19);
        printf("▌");
        goToXY(69,19);
        printf("%d%%",i*5);
        Sleep(100);
    }
    */
}
void admin_login(){
    int state = 0;//0表示注册，1表示登陆
    drawBorder();
    drawTitle();
    goToXY(24,9);
    printf("请选择登录或注册：");
    goToXY(26,12);
    printf("①  ★  管理员注册");
    goToXY(26,14);
    printf("②      管理员登陆");
    goToXY(26,16);
    printf("③      退出");
    updown_bottom();
    while(TRUE){
        char choice;
        choice = getch();
        if(choice == 72){
            goToXY(30,12+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1){
                state = 2;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == 80){

            goToXY(30,12+state*2);
            printf("\b  ");
            state += 1;
            if(state == 3){
                state = 0;
            }
            goToXY(30,12+state*2);
            printf("★");

        }else if(choice == '\r'){
            switch(state){
                case 0:
                    system("cls");
                    drawBorder();
                    admin_register();
                    break;
                case 1:
                    system("cls");
                    drawBorder();
                    admin_login_login();
                    break;
                case 2:
                    system("cls");
                    start();
                    break;
            }
        }
    }
    getchar();
}
void cus_login(){
    int state = 0;//0表示注册，1表示登陆
    drawBorder();
    drawTitle();
    goToXY(24,9);
    printf("请选择登录或注册：");
    goToXY(26,12);
    printf("①  ★  顾客注册");
    goToXY(26,14);
    printf("②      顾客登陆");
    goToXY(26,16);
    printf("③      退出");
    updown_bottom();
    while(TRUE){
        char choice;
        choice = getch();
        if(choice == 72){
            goToXY(30,12+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1){
                state = 2;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == 80){
            goToXY(30,12+state*2);
            printf("\b  ");
            state += 1;
            if(state == 3){
                state = 0;
            }
            goToXY(30,12+state*2);
            printf("★");
        }else if(choice == '\r'){
            switch(state){
                case 0:
                    system("cls");
                    drawBorder();
                    cus_register();
                    break;

                case 1:
                    system("cls");
                    drawBorder();
                    cus_login_login();
                    break;
                case 2:
                    system("cls");
                    start();
                    break;
            }
        }
    }
    getchar();
}
void admin_register(){
    struct user admin = {"","","","","",""};
    char code[10];
    goToXY(28,3);
    printf("****管理员注册信息****");
    goToXY(20,9);
    printf("昵称：");
    goToXY(20,10);
    printf("性别：");
    goToXY(20,11);
    printf("邮箱：");
    goToXY(20,12);
    printf("手机号：");
    goToXY(20,13);
    printf("管理员注册码：");
    goToXY(20,15);
    printf("密码：");
    goToXY(20,16);
    printf("重复密码：");

    goToXY(27,9);
    scanf("%s",admin.name);
    goToXY(27,10);
    scanf("%s",admin.sex);
    goToXY(27,11);
    scanf("%s",admin.mail);
    goToXY(29,12);
    scanf("%s",admin.phone);
    goToXY(35,13);
    scanf("%s",code);
    goToXY(27,15);
    i=0;
    char pw;
    pw=getch();
    while(pw != 13){
    	if(pw == 8){
			if(i!=0){printf("%c %c",pw,pw);i--;}
        }
        else if(i==20&&pw!=8){}
        else
        {
          	printf("*");
           	admin.pass[i] = pw;
          	i++;
    	}
      	pw = getch();
    }
    admin.pass[i]='\0';
    goToXY(31,16);
    i=0;
    pw=getch();
    while(pw != 13){
		if ( pw == 8){
			if(i!=0) {printf("%c %c",pw,pw);i--;}
        }
        else if(i==20&&pw!=8) {}
        else{
          	printf("*");
           	admin.pass_double[i] = pw;
         	 i++;
        }
       	pw = getch();
    }
    admin.pass_double[i]='\0';



    if((!strcmp(code,"cjhz"))&&(!strcmp(admin.pass,admin.pass_double)))
    {

        FILE *file;
        file = fopen(USER_1,"ab+");
        rewind(file);
        struct user User= {"","","","","",""};
        while(!feof(file))
        {
            int result = fread(&User,sizeof(struct user),1,file);
            if(result != 0)
            {
                if(strcmp(User.name,admin.name)==0)
                break;
            }
        }
        if(feof(file))
        {
            fwrite(&admin,sizeof(struct user),1,file);
            fclose(file);
            system("cls");
            drawBorder();
            goToXY(30,9);
            printf("用户名：%s",admin.name);
            goToXY(24,11);
            printf("管理员身份注册成功，按任意键继续！");
            getch();
            system("cls");
            admin_login();
        }
        else
        {
            fclose(file);
            system("cls");
            drawBorder();
            goToXY(25,11);
            printf("用户名重复，注册失败！");
            getch();
            system("cls");
            admin_login();
        }

    }
    else{
        system("cls");
        drawBorder();
        goToXY(34,11);
        printf("注册失败！");
        getch();
        system("cls");
        admin_login();
    }


}
void cus_register(){
    struct user cus = {"","","","","",""};

    goToXY(28,3);
    printf("****顾客用户注册信息****");
    goToXY(20,9);
    printf("昵称：");
    goToXY(20,10);
    printf("性别：");
    goToXY(20,11);
    printf("邮箱：");
    goToXY(20,12);
    printf("手机号：");
    goToXY(20,15);
    printf("密码：");
    goToXY(20,16);
    printf("重复密码：");


    goToXY(27,9);
    scanf("%s",cus.name);
    goToXY(27,10);
    scanf("%s",cus.sex);
    goToXY(27,11);
    scanf("%s",cus.mail);
    goToXY(29,12);
    scanf("%s",cus.phone);
    goToXY(27,15);
    i=0;
    char pw;
	pw=getch();
    while ( pw != 13){
      	if(pw == 8){
			if(i!=0) {printf("%c %c",pw,pw);i--;}
        }else if(i==20&&pw!=8) {}
        else{
    		printf("*");
           	cus.pass[i] = pw;
          	i++;
        }
       	pw = getch();
    }
    cus.pass[i]='\0';
    goToXY(31,16);
    i=0;
    pw=getch();
    while( pw != 13)
	{
		if(pw == 8)
        {if(i!=0) {printf("%c %c",pw,pw);i--;}}
        else if(i==20&&pw!=8) {}
        else{
          	printf("*");
           	cus.pass_double[i] = pw;
          	i++;
        }
       	pw = getch();
    }
    cus.pass_double[i]='\0';

    if(!strcmp(cus.pass,cus.pass_double))
    {
        FILE *file;
        file = fopen(USER_2,"ab+");
        rewind(file);
        struct user User= {"","","","","",""};
        while(!feof(file))
        {
            int result = fread(&User,sizeof(struct user),1,file);
            if(result != 0)
            {
                if(strcmp(User.name,cus.name)==0)  break;
            }
        }
        if(feof(file))
        {
            fwrite(&cus,sizeof(struct user),1,file);
            fclose(file);
            system("cls");
            drawBorder();
            goToXY(30,9);
            printf("用户名：%s",cus.name);
            goToXY(24,11);
            printf("顾客身份注册成功，按任意键继续！");
            getch();
            system("cls");
            cus_login();
        }
        else
        {
            system("cls");
            drawBorder();
            goToXY(25,11);
            printf("用户名重复，注册失败！");
            getch();
            system("cls");
            cus_login();
        }
    }
    else
    {
        system("cls");
        drawBorder();
        goToXY(25,11);
        printf("两次输入密码不一致，注册失败！");
        getch();
        system("cls");
        cus_login();
        start();
    }

}
void admin_login_login(){
    char login_name[20];
    char login_pass[20];

    drawBorder();
    goToXY(30,3);
    printf("****管理员登陆****");
    goToXY(25,8);
    printf("昵称：");
    goToXY(25,9);
    printf("密码：");

    goToXY(31,8);
    scanf("%s",login_name);
    goToXY(31,9);


    i=0;
    char pw;
    pw=getch();
    while(pw != 13){
        if(pw == 8){if(i!=0) {printf("%c %c",pw,pw);i--;}}
        else if(i==20&&pw!=8) {}
        else{
            printf("*");
            login_pass[i] = pw;
            i++;
        }
        pw = getch();
    }
    login_pass[i]='\0';



    //验证账户
    int correct = 0;//验证状态
    struct user vertify = {"","","","","",""};
    FILE *file = fopen("user_1.dat","ab+");
    rewind(file);
    while(!feof(file)){
        int result = fread(&vertify,sizeof(struct user),1,file);
        if(result != 0){
            if((!strcmp(vertify.name,login_name))&&(!strcmp(vertify.pass,login_pass))){
                correct = 1;
                break;
            }
        }
    }
    fclose(file);

    //progressBar("系统正在验证您的登录信息，请稍候！");
    system("cls");
    if(correct == 1){
        system("cls");
        alert(login_name);
        admin_main(login_name);
    }else if(correct == 0){
        system("cls");
        drawBorder();
        goToXY(30,9);
        printf("用户名：%s",login_name);
        goToXY(23,11);
        printf("用户名或密码错误，按任意键继续！");
        getch();
        system("cls");
        admin_login();
    }

}
void cus_login_login(){
    char login_name[20];
    char login_pass[20];

    drawBorder();
    goToXY(30,3);
    printf("****顾客登陆****");
    goToXY(25,8);
    printf("昵称：");
    goToXY(25,9);
    printf("密码：");

    goToXY(31,8);
    scanf("%s",login_name);
    goToXY(31,9);


    i=0;
    char pw;
    pw=getch();
    while(pw != 13){
        if(pw == 8){if(i!=0) {printf("%c %c",pw,pw);i--;}}
        else if(i==20&&pw!=8) {}
        else{
            printf("*");
            login_pass[i] = pw;
            i++;
        }
        pw = getch();
    }
    login_pass[i]='\0';



    //验证账户
    int correct = 0;//验证状态
    struct user vertify = {"","","","","",""};
    FILE *file = fopen("user_2.dat","ab+");
    rewind(file);
    while(!feof(file)){
        int result = fread(&vertify,sizeof(struct user),1,file);
        if(result != 0){
            if((!strcmp(vertify.name,login_name))&&(!strcmp(vertify.pass,login_pass))){
                correct = 1;
                break;
            }
        }
    }
    fclose(file);

    progressBar("系统正在验证您的登录信息，请稍候！");
    system("cls");
    if(correct == 1){
        system("cls");
        cus_main(login_name);
    }else if(correct == 0){
        system("cls");
        drawBorder();
        goToXY(30,9);
        printf("用户名：%s",login_name);
        goToXY(23,11);
        printf("用户名或密码错误，按任意键继续！");
        getch();
        system("cls");
        cus_login();
    }
}
void hideCursor(){
    CONSOLE_CURSOR_INFO cursor_info;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void del_comm(char *name){
    int del_num;
    system("cls");
    drawBorder();
    goToXY(28,3);
    printf("****删除商品信息****");
    goToXY(24,10);
    printf("请输入要删除的商品编号:");
    scanf("%d",&del_num);
    del_pro(del_num);
    progressBar("正在删除商品，请稍后！");
    system("cls");
    drawBorder();
    goToXY(30,9);
    printf("商品编号：%d",del_num);
    goToXY(25,11);
    printf("商品删除成功，按任意键继续！");
    getch();
    system("cls");
    admin_main(name);
}
void del_pro(int del_num){
    FILE *file = fopen(PRODUCT,"ab+");
    FILE *file_copy = fopen("copy.dat","ab+");
    struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
    rewind(file);
    while(!feof(file)){
        int result = fread(&comm,sizeof(struct commodity),1,file);
        if(result != 0){
            if(comm.num != del_num){
                fwrite(&comm,sizeof(struct commodity),1,file_copy);
            }
        }
    }
    fclose(file);
    fclose(file_copy);
    remove(PRODUCT);
    rename("copy.dat",PRODUCT);
}
void color_change(char *name){
    int state = 0;
    system("cls");
    drawBorder();
    goToXY(28,3);
    printf("****更改界面颜色****");
    goToXY(26,8);
    printf("①  ★  白底黑字(该系统默认主题)");
    goToXY(26,10);
    printf("②      红底蓝字");
    goToXY(26,12);
    printf("③      黑底红字");
    goToXY(26,14);
    printf("④      绿底蓝字");
    goToXY(26,16);
    printf("⑤      黑底绿字");
    goToXY(26,18);
    printf("⑥      绿底白字");
    goToXY(26,20);
    printf("⑦      退出并保存颜色设置");
    while(TRUE){
        char choice;
        choice = getch();
        if(choice == 72){
            goToXY(30,8+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1){
                state = 6;
            }
            goToXY(30,8+state*2);
            printf("★");
        }
        else if(choice == 80){
            goToXY(30,8+state*2);
            printf("\b  ");
            state += 1;
            if(state == 7){
                state = 0;
            }
            goToXY(30,8+state*2);
            printf("★");
        }else if(choice == '\r'){
            switch(state){
                case 0:
                    system("color F0");
                    break;
                case 1:
                    system("color 40");
                    break;
                case 2:
                    system("color 04");
                    break;
                case 3:
                    system("color 21");
                    break;
                case 4:
                    system("color 0A");
                    break;
                case 5:
                    system("color 3f");
                    break;
                case 6:
                    system("cls");
                    admin_main(name);
                    break;
            }
        }
    }
    getchar();
}
void send_mes(char *name){
    struct message mes = {"","","",""};
    system("cls");
    drawBorder();
    goToXY(23,3);
    printf("****反馈信息页面,期待着您的声音！****");
    goToXY(15,8);
    printf("请输入反馈信息：");
    goToXY(10,10);
    printf("请输入您的联系方式，以便我们与您取得联系：");
    goToXY(31,8);
    scanf("%s",mes.content);
    goToXY(52,10);
    scanf("%s",mes.contract);
    strcpy(mes.name,name);

    char date[10];
    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    sprintf(date,"%d-%d-%d",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday);
    strcpy(mes.date,date);

    FILE *file = fopen(MES,"ab+");
    fwrite(&mes,sizeof(struct message),1,file);
    fclose(file);
    goToXY(22,18);
    printf("已经收到您的来信，请您期待更好的我们！");
    goToXY(29,19);
    printf("按任意键返回主界面！");
    getch();
    system("cls");
    cus_main(name);
}
void receive_mes(char *name){

    system("cls");
    drawBorder();
    //goToXY(23,3);
    //printf("****这里存放着%d封用户反馈的信息！****",count_mes());
    show_page(MES,"用户反馈",name,1);

}
int count(char *file_name,char *name){
    int count = 0;
    FILE *file = fopen(file_name,"ab+");
    if(!strcmp(file_name,PRODUCT) || !strcmp(file_name,"copy1.dat") || !strcmp(file_name,"select.dat") || !strcmp(file_name,"tmp_1.dat")||!strcmp(file_name,name)){
        struct commodity tmp = {0,"",0.0,0.0,"",0.0,"",0,"",0};
        rewind(file);
        while(!feof(file)){
            int result = fread(&tmp,sizeof(struct commodity),1,file);
            if(result != 0){
                count ++;
            }
        }
    }else if(!strcmp(file_name,MES)){
        struct message tmp = {"","","",""};
        rewind(file);
        while(!feof(file)){
            int result = fread(&tmp,sizeof(struct message),1,file);
            if(result != 0){
                count ++;
            }
        }
    }else if(!strcmp(file_name,"tmp.dat")){
        struct record tmp = {"","",0,""};
        rewind(file);
        while(!feof(file)){
            int result = fread(&tmp,sizeof(struct record),1,file);
            if(result != 0){
                count ++;
            }
        }
    }else if(!strcmp(file_name,DAY_SOLD)){
        struct day_sold ds = {"",0};
        rewind(file);
        while(!feof(file)){
            int result = fread(&ds,sizeof(struct day_sold),1,file);
            if(result != 0){
                count ++;
            }
        }
    }
    fclose(file);
    return count;
}
void show_page(char *file_name,char *str,char *name,int ver){
    int page_num = 0;//记录当前的翻页数
    system("cls");
    drawBorder();
    goToXY(25,2);
    printf("****以下是查询到的%s****",str);
    drawInBorder();
    buttom_title1(page_num,count(file_name,name)/5 + 1,ver);
    FILE *file = fopen(file_name,"ab+");
    if(!strcmp(file_name,PRODUCT) || !strcmp(file_name,"copy1.dat") || !strcmp(file_name,"select.dat")||!strcmp(file_name,name)){
        if(ver == 1){
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
            goToXY(6,4);
            printf("商品编号 商品名称 商品描述 商品类别 生产商 销售量 库存量 进价 售价");
                for(i = 1;i < 6;i ++){
                    int result = fread(&comm,sizeof(struct commodity),1,file);
                    if(result == 1){
                        goToXY(6,4+3*i);
                        printf("%d",comm.num);
                        goToXY(15,4+3*i);
                        printf("%s",comm.name);
                        goToXY(25,4+3*i);
                        printf("%s",comm.desc);
                        goToXY(33,4+3*i);
                        printf("%s",comm.sort);
                        goToXY(42,4+3*i);
                        printf("%s",comm.provider);
                        goToXY(50,4+3*i);
                        printf("%d",comm.sold);
                        goToXY(56,4+3*i);
                        printf("%d",comm.count);
                        goToXY(63,4+3*i);
                        printf("%.1lf",comm.in_price);
                        goToXY(68,4+3*i);
                        printf("%.1lf",comm.out_price);
                    }else{
                        break;
                    }
                }
        }else if(ver == 2){
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
            goToXY(6,4);
            printf("商品编号\t商品名称\t商品描述\t销量\t生产商\t价格");
            if(!strcmp(file_name,name)) {printf("  数量"); goToXY(52,22);printf("【S】删除");}
            for(i = 1;i < 6;i ++){
                int result = fread(&comm,sizeof(struct commodity),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%d",comm.num);
                    goToXY(16,4+3*i);
                    printf("%s",comm.name);
                    goToXY(32,4+3*i);
                    printf("%s",comm.desc);
                    goToXY(48,4+3*i);
                    printf("%d",comm.sold);
                    goToXY(56,4+3*i);
                    printf("%s",comm.provider);
                    goToXY(64,4+3*i);
                    printf("%.1lf",comm.out_price);
                     if(!strcmp(file_name,name))
                    {
                        goToXY(72,4+3*i);
                        printf("%d",comm.cart_count);
                    }
                }else{
                    break;
                }
            }
        }
    }else if(!strcmp(file_name,MES)){
        struct message mes = {"","","",""};
            goToXY(6,4);
            printf("反馈用户昵称\t反馈内容\t\t联系方式\t反馈日期");
            for(i = 1;i < 6;i ++){
                int result = fread(&mes,sizeof(struct message),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%s",mes.name);
                    goToXY(25,4+3*i);
                    printf("%s",mes.content);
                    goToXY(49,4+3*i);
                    printf("%s",mes.contract);
                    goToXY(65,4+3*i);
                    printf("%s",mes.date);
                }else{
                    break;
                }
            }
    }else if(!strcmp(file_name,"tmp.dat")){
        struct record rec = {"","",0,""};
        goToXY(6,4);
        printf("购买用户昵称\t商品名称\t\t商品件数\t购买日期");
        for(i = 1;i < 6;i ++){
                int result = fread(&rec,sizeof(struct record),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%s",rec.name);
                    goToXY(25,4+3*i);
                    printf("%s",rec.product);
                    goToXY(49,4+3*i);
                    printf("%d",rec.quantity);
                    goToXY(64,4+3*i);
                    printf("%s",rec.date);
                }else{
                    break;
                }
            }
    }else if(!strcmp(file_name,"tmp_1.dat")){
        if(ver == 1){
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号 商品名称 商品描述 商品类别 生产商 销售量 库存量 进价 售价");
                for(i = 1;i < 6;i ++){
                    int result = fread(&comm,sizeof(struct commodity),1,file);
                    if(result == 1){
                        goToXY(6,4+3*i);
                        printf("%d",comm.num);
                        goToXY(15,4+3*i);
                        printf("%s",comm.name);
                        goToXY(25,4+3*i);
                        printf("%s",comm.desc);
                        goToXY(33,4+3*i);
                        printf("%s",comm.sort);
                        goToXY(42,4+3*i);
                        printf("%s",comm.provider);
                        goToXY(50,4+3*i);
                        printf("%d",comm.sold);
                        goToXY(56,4+3*i);
                        printf("%d",comm.count);
                        goToXY(63,4+3*i);
                        printf("%.1lf",comm.in_price);
                        goToXY(68,4+3*i);
                        printf("%.1lf",comm.out_price);
                    }else{
                        break;
                    }
                }
        }else if(ver == 2){
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号\t商品名称\t商品描述\t\t生产商\t商品价格");
            for(i = 1;i < 6;i ++){
                int result = fread(&comm,sizeof(struct commodity),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%d",comm.num);
                    goToXY(16,4+3*i);
                    printf("%s",comm.name);
                    goToXY(32,4+3*i);
                    printf("%s",comm.desc);
                    goToXY(56,4+3*i);
                    printf("%s",comm.provider);
                    goToXY(64,4+3*i);
                    printf("%.1lf",comm.out_price);
                }else{
                    break;
                }
            }
        }

    }
    fclose(file);
    int state = 1;
    int choice;
    while(state){
        switch(choice){
            case 110://N键
                state = 0;
                page_num++;
                if(page_num > count(file_name,name)/5){
                    page_num = count(file_name,name)/5;
                }
                page_down(file_name,str,page_num,name,ver);
                break;
            case 112://P键
                state = 0;
                page_num--;
                if(page_num < 0){
                    page_num = 0;
                }
                page_up(file_name,str,page_num,name,ver);
                break;
            case 98:
            if(ver==2&&strcmp(file_name,name)==0) empty_cart(name);
            else if(ver==2&&strcmp(file_name,name)!=0) move_to_shopping_cart(name);
            break;
            case 115:
            if(ver==2&&strcmp(file_name,name)==0) del_cart(name);
            break;
            case 27:
                state = 0;
                system("cls");
                switch(ver){
                    case 1:
                        admin_main(name);
                        break;
                    case 2:
                        cus_main(name);
                        break;
                }
                break;
            default:
                choice = getch();
        }
    }
}
void page_up(char *file_name,char *str,int num,char *name,int ver){
    int nums = 0;//检索
    system("cls");
    drawBorder();
    buttom_title1(num,count(file_name,name)/5 + 1,ver);
    goToXY(25,2);
    printf("****以下是查询到的%s****",str);
    drawInBorder();
    FILE *file = fopen(file_name,"ab+");

    if(!strcmp(file_name,PRODUCT) || !strcmp(file_name,"copy1.dat") || !strcmp(file_name,"select.dat")||!strcmp(file_name,name)){
        if(ver == 1){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
            goToXY(6,4);
            printf("商品编号 商品名称 商品描述 商品类别 生产商 销售量 库存量 进价 售价");
                for(i = 1;i < 6;i ++){
                    int result = fread(&comm,sizeof(struct commodity),1,file);
                    if(result == 1){
                        goToXY(6,4+3*i);
                        printf("%d",comm.num);
                        goToXY(15,4+3*i);
                        printf("%s",comm.name);
                        goToXY(25,4+3*i);
                        printf("%s",comm.desc);
                        goToXY(33,4+3*i);
                        printf("%s",comm.sort);
                        goToXY(42,4+3*i);
                        printf("%s",comm.provider);
                        goToXY(50,4+3*i);
                        printf("%d",comm.sold);
                        goToXY(56,4+3*i);
                        printf("%d",comm.count);
                        goToXY(63,4+3*i);
                        printf("%.1lf",comm.in_price);
                        goToXY(68,4+3*i);
                        printf("%.1lf",comm.out_price);
                    }else{
                        break;
                    }
                }
        }else if(ver == 2){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号\t商品名称\t商品描述\t销量\t生产商\t商品价格");
             if(!strcmp(file_name,name)) {printf("  数量"); goToXY(52,22);printf("【S】删除");}
            for(i = 1;i < 6;i ++){
                int result = fread(&comm,sizeof(struct commodity),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%d",comm.num);
                    goToXY(16,4+3*i);
                    printf("%s",comm.name);
                    goToXY(32,4+3*i);
                    printf("%s",comm.desc);
                    goToXY(48,4+3*i);
                    printf("%d",comm.sold);
                    goToXY(56,4+3*i);
                    printf("%s",comm.provider);
                    goToXY(64,4+3*i);
                    printf("%.1lf",comm.out_price);
                     if(!strcmp(file_name,name))
                    {
                        goToXY(72,4+3*i);
                        printf("%d",comm.cart_count);
                    }
                }else{
                    break;
                }
            }
        }
    }
    else if(!strcmp(file_name,MES)){
        fseek(file,sizeof(struct message)*5*num,SEEK_SET);
        struct message mes = {"","","",""};
        goToXY(6,4);
        printf("反馈用户昵称\t反馈内容\t\t联系方式\t反馈日期");
            for(i = 1;i < 6;i ++){
                int result = fread(&mes,sizeof(struct message),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%s",mes.name);
                    goToXY(25,4+3*i);
                    printf("%s",mes.content);
                    goToXY(49,4+3*i);
                    printf("%s",mes.contract);
                    goToXY(65,4+3*i);
                    printf("%s",mes.date);
                }else{
                    break;
                }
            }
    }
    else if(!strcmp(file_name,"tmp.dat")){
        fseek(file,sizeof(struct record)*5*num,SEEK_SET);
        struct record rec = {"","",0,""};
        goToXY(6,4);
        printf("购买用户昵称\t商品名称\t\t商品件数\t购买日期");
        for(i = 1;i < 6;i ++){
                int result = fread(&rec,sizeof(struct record),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%s",rec.name);
                    goToXY(25,4+3*i);
                    printf("%s",rec.product);
                    goToXY(49,4+3*i);
                    printf("%d",rec.quantity);
                    goToXY(64,4+3*i);
                    printf("%s",rec.date);
                }else{
                    break;
                }
        }
    }else if(!strcmp(file_name,"tmp_1.dat")){
        if(ver == 1){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号 商品名称 商品描述 商品类别 生产商 销售量 库存量 进价 售价");
                for(i = 1;i < 6;i ++){
                    int result = fread(&comm,sizeof(struct commodity),1,file);
                    if(result == 1){
                        goToXY(6,4+3*i);
                        printf("%d",comm.num);
                        goToXY(15,4+3*i);
                        printf("%s",comm.name);
                        goToXY(25,4+3*i);
                        printf("%s",comm.desc);
                        goToXY(33,4+3*i);
                        printf("%s",comm.sort);
                        goToXY(42,4+3*i);
                        printf("%s",comm.provider);
                        goToXY(50,4+3*i);
                        printf("%d",comm.sold);
                        goToXY(56,4+3*i);
                        printf("%d",comm.count);
                        goToXY(63,4+3*i);
                        printf("%.1lf",comm.in_price);
                        goToXY(68,4+3*i);
                        printf("%.1lf",comm.out_price);
                    }else{
                        break;
                    }
                }
        }else if(ver == 2){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号\t商品名称\t商品描述\t\t生产商\t商品价格");
            for(i = 1;i < 6;i ++){
                int result = fread(&comm,sizeof(struct commodity),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%d",comm.num);
                    goToXY(16,4+3*i);
                    printf("%s",comm.name);
                    goToXY(32,4+3*i);
                    printf("%s",comm.desc);
                    goToXY(56,4+3*i);
                    printf("%s",comm.provider);
                    goToXY(64,4+3*i);
                    printf("%.1lf",comm.out_price);
                }else{
                    break;
                }
            }
        }

    }


    fclose(file);
    int state = 1;
    int choice;
    while(state){
        switch(choice){
            case 110://N键
                state = 0;
                num++;
                if(num > count(file_name,name)/5){
                    num = count(file_name,name)/5;
                }
                page_down(file_name,str,num,name,ver);
                break;
            case 112://P键
                state = 0;
                num--;
                if(num < 0){
                    num = 0;
                }
                page_up(file_name,str,num,name,ver);
                break;
                 case 98:
            if(ver==2&&strcmp(file_name,name)==0) empty_cart(name);
            else if(ver==2&&strcmp(file_name,name)!=0) move_to_shopping_cart(name);
            break;
        case 115:
            if(ver==2&&strcmp(file_name,name)==0) del_cart(name);
            break;
            case 27:
                state = 0;
                system("cls");
                switch(ver){
                    case 1:
                        admin_main(name);
                        break;
                    case 2:
                        cus_main(name);
                        break;
                }
                break;
            default:
                choice = getch();
        }
    }
}
void page_down(char *file_name,char *str,int num,char *name,int ver){
    int nums = 0;//检索
    system("cls");
    drawBorder();
    buttom_title1(num,count(file_name,name)/5 + 1,ver);
    goToXY(25,2);
    printf("****以下是查询到的%s****",str);
    drawInBorder();
    FILE *file = fopen(file_name,"ab+");


    if(!strcmp(file_name,PRODUCT) || !strcmp(file_name,"copy1.dat") || !strcmp(file_name,"select.dat")||!strcmp(file_name,name)){
        if(ver == 1){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
            goToXY(6,4);
            printf("商品编号 商品名称 商品描述 商品类别 生产商 销售量 库存量 进价 售价");
                for(i = 1;i < 6;i ++){
                    int result = fread(&comm,sizeof(struct commodity),1,file);
                    if(result == 1){
                        goToXY(6,4+3*i);
                        printf("%d",comm.num);
                        goToXY(15,4+3*i);
                        printf("%s",comm.name);
                        goToXY(25,4+3*i);
                        printf("%s",comm.desc);
                        goToXY(33,4+3*i);
                        printf("%s",comm.sort);
                        goToXY(42,4+3*i);
                        printf("%s",comm.provider);
                        goToXY(50,4+3*i);
                        printf("%d",comm.sold);
                        goToXY(56,4+3*i);
                        printf("%d",comm.count);
                        goToXY(63,4+3*i);
                        printf("%.1lf",comm.in_price);
                        goToXY(68,4+3*i);
                        printf("%.1lf",comm.out_price);
                    }else{
                        break;
                    }
                }
        }else if(ver == 2){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号\t商品名称\t商品描述\t销量\t生产商\t商品价格");
            if(!strcmp(file_name,name)) {printf("  数量"); goToXY(52,22);printf("【S】删除");}
            for(i = 1;i < 6;i ++){
                int result = fread(&comm,sizeof(struct commodity),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%d",comm.num);
                    goToXY(16,4+3*i);
                    printf("%s",comm.name);
                    goToXY(32,4+3*i);
                    printf("%s",comm.desc);
                    goToXY(48,4+3*i);
                    printf("%d",comm.sold);
                    goToXY(56,4+3*i);
                    printf("%s",comm.provider);
                    goToXY(64,4+3*i);
                    printf("%.1lf",comm.out_price);
                     if(!strcmp(file_name,name))
                    {
                        goToXY(72,4+3*i);
                        printf("%d",comm.cart_count);
                    }
                }else{
                    break;
                }
            }
        }
    }else if(!strcmp(file_name,MES)){
        fseek(file,sizeof(struct message)*5*num,SEEK_SET);
        struct message mes = {"","","",""};
        goToXY(6,4);
        printf("反馈用户昵称\t反馈内容\t\t联系方式\t反馈日期");
            for(i = 1;i < 6;i ++){
                int result = fread(&mes,sizeof(struct message),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%s",mes.name);
                    goToXY(25,4+3*i);
                    printf("%s",mes.content);
                    goToXY(49,4+3*i);
                    printf("%s",mes.contract);
                    goToXY(65,4+3*i);
                    printf("%s",mes.date);
                }else{
                    break;
                }
            }
    }else if(!strcmp(file_name,"tmp.dat")){
        fseek(file,sizeof(struct record)*5*num,SEEK_SET);
        struct record rec = {"","",0,""};
        goToXY(6,4);
        printf("购买用户昵称\t商品名称\t\t商品件数\t购买日期");
        for(i = 1;i < 6;i ++){
                int result = fread(&rec,sizeof(struct record),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%s",rec.name);
                    goToXY(25,4+3*i);
                    printf("%s",rec.product);
                    goToXY(49,4+3*i);
                    printf("%d",rec.quantity);
                    goToXY(64,4+3*i);
                    printf("%s",rec.date);
                }else{
                    break;
                }
            }
    }else if(!strcmp(file_name,"tmp_1.dat")){
        if(ver == 1){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号 商品名称 商品描述 商品类别 生产商 销售量 库存量 进价 售价");
                for(i = 1;i < 6;i ++){
                    int result = fread(&comm,sizeof(struct commodity),1,file);
                    if(result == 1){
                        goToXY(6,4+3*i);
                        printf("%d",comm.num);
                        goToXY(15,4+3*i);
                        printf("%s",comm.name);
                        goToXY(25,4+3*i);
                        printf("%s",comm.desc);
                        goToXY(33,4+3*i);
                        printf("%s",comm.sort);
                        goToXY(42,4+3*i);
                        printf("%s",comm.provider);
                        goToXY(50,4+3*i);
                        printf("%d",comm.sold);
                        goToXY(56,4+3*i);
                        printf("%d",comm.count);
                        goToXY(63,4+3*i);
                        printf("%.1lf",comm.in_price);
                        goToXY(68,4+3*i);
                        printf("%.1lf",comm.out_price);
                    }else{
                        break;
                    }
                }
        }else if(ver == 2){
            fseek(file,sizeof(struct commodity)*5*num,SEEK_SET);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
            goToXY(6,4);
            printf("商品编号\t商品名称\t商品描述\t\t生产商\t商品价格");
            for(i = 1;i < 6;i ++){
                int result = fread(&comm,sizeof(struct commodity),1,file);
                if(result == 1){
                    goToXY(6,4+3*i);
                    printf("%d",comm.num);
                    goToXY(16,4+3*i);
                    printf("%s",comm.name);
                    goToXY(32,4+3*i);
                    printf("%s",comm.desc);
                    goToXY(56,4+3*i);
                    printf("%s",comm.provider);
                    goToXY(64,4+3*i);
                    printf("%.1lf",comm.out_price);
                }else{
                    break;
                }
            }
        }

    }
    fclose(file);
    int state = 1;
    int choice;
    while(state){
        switch(choice){
            case 110://N键
                state = 0;
                num++;
                if(num > count(file_name,name)/5){
                    num = count(file_name,name)/5;
                }
                page_down(file_name,str,num,name,ver);
                break;
            case 112://P键
                state = 0;
                num--;
                if(num < 0){
                    num = 0;
                }
                page_up(file_name,str,num,name,ver);
                break;
                case 98:
            if(ver==2&&strcmp(file_name,name)==0) empty_cart(name);
            else if(ver==2&&strcmp(file_name,name)!=0) move_to_shopping_cart(name);
            break;
        case 115:
            if(ver==2&&strcmp(file_name,name)==0) del_cart(name);
            break;
            case 27:
                state = 0;
                system("cls");
                switch(ver){
                    case 1:
                        admin_main(name);
                        break;
                    case 2:
                        cus_main(name);
                        break;
                }
                break;
            default:
                choice = getch();
        }
    }
}
void drawInBorder(){
    goToXY(5,2);
    for(i = 0;i < 40;i++){
        if(i == 20){
            goToXY(54,2);
        }
        printf("*");
    }
    for(i = 1;i < 7;i++){
        goToXY(5,2+3*i);
        for(j = 0;j < 70;j++){
            printf("-");
        }
    }
}
void add_comm(char *name){
    system("cls");
    drawBorder();
    struct commodity comm = {0,"",0.0,0.0,"",0,"",0,""};
    goToXY(28,3);
    printf("****请输入商品信息****");
    goToXY(20,9);
    printf("商品编号：");
    goToXY(20,10);
    printf("商品名称：");
    goToXY(20,11);
    printf("进价：");
    goToXY(20,12);
    printf("售价：");
    goToXY(20,13);
    printf("商品描述：");
    goToXY(20,14);
    printf("库存量：");
    goToXY(20,15);
    printf("类别：");
    goToXY(20,16);
    printf("销售量：");
    goToXY(20,17);
    printf("生产商：");
    goToXY(31,9);
    scanf("%d",&comm.num);
    goToXY(31,10);
    scanf("%s",comm.name);
    goToXY(27,11);
    scanf("%lf",&comm.in_price);
    goToXY(27,12);
    scanf("%lf",&comm.out_price);
    goToXY(31,13);
    scanf("%s",comm.desc);
    goToXY(29,14);
    scanf("%d",&comm.count);
    goToXY(27,15);
    scanf("%s",comm.sort);
    goToXY(29,16);
    scanf("%d",&comm.sold);
    goToXY(29,17);
    scanf("%s",comm.provider);

    int state_now = 0;
    FILE *file = fopen(PRODUCT,"ab+");
    struct commodity comm_1 = {0,"",0.0,0.0,"",0.0,"",0,""};
    rewind(file);
    while(!feof(file)){
        int result = fread(&comm_1,sizeof(struct commodity),1,file);
        if(result != 0){
            if(comm.num == comm_1.num){
                  state_now = 1;
            }
        }
    }
    fclose(file);
    if(state_now == 1)
    {
        system("cls");
        drawBorder();
        goToXY(25,11);
        printf("商品编号重复，按任意键继续！");
        getch();
        add_comm(name);
    }

    file = fopen(PRODUCT,"ab+");
    fwrite(&comm,sizeof(struct commodity),1,file);
    fclose(file);
    int choice;
    while(TRUE){
        system("cls");
        drawBorder();
        goToXY(20,9);
        printf("是否继续添加商品？请输入Yes/No:");
        char y_n[4];
        gets(y_n);
        if(!strcmp(y_n,"Yes")){
            choice = 1;
            break;
        }
        else if(!strcmp(y_n,"No")){
            choice = 0;
            break;
        }
        else
        printf("输入错误！");
    }
    switch(choice)
    {
        case 1:
            add_comm(name);
            break;
        case 0:
            system("cls");
            admin_main(name);
    }
}
void change_comm(char *name){
    int change_num;
    int state = 0;//表示是否修改成功
    system("cls");
    drawBorder();
    goToXY(28,3);
    printf("****修改商品信息****");
    goToXY(24,10);
    printf("请输入要修改的商品编号:");
    scanf("%d",&change_num);
    FILE *file = fopen(PRODUCT,"ab+");
    FILE *file_copy = fopen("copy.dat","ab+");
    struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
    rewind(file);
    while(!feof(file)){
        int result = fread(&comm,sizeof(struct commodity),1,file);
        if(result != 0){
            if(comm.num != change_num){
                fwrite(&comm,sizeof(struct commodity),1,file_copy);
            }
            if(comm.num == change_num){
                state = 1;
                system("cls");
                int state = 0;
                drawBorder();
                goToXY(24,3);
                printf("请选择您要修改的信息：");
                goToXY(26,6);
                printf("①  ★  进价");
                goToXY(50,6);
                printf("当前：%.1lf",comm.in_price);
                goToXY(26,8);
                printf("②      售价");
                goToXY(50,8);
                printf("当前：%.1lf",comm.out_price);
                goToXY(26,10);
                printf("③      商品描述");
                goToXY(50,10);
                printf("当前：%s",comm.desc);
                goToXY(26,12);
                printf("④      库存");
                goToXY(50,12);
                printf("当前：%d",comm.count);
                goToXY(26,14);
                printf("⑤      类别");
                goToXY(50,14);
                printf("当前：%s",comm.sort);
                goToXY(26,16);
                printf("⑥      销售量");
                goToXY(50,16);
                printf("当前：%d",comm.sold);
                goToXY(26,18);
                printf("⑦      生产商");
                goToXY(50,18);
                printf("当前：%s",comm.provider);
                updown_bottom();
                while(TRUE){
                    char choice;
                    choice = getch();
                    if(choice == 72){
                            goToXY(30,6+state*2);
                            printf("\b  ");
                            state -= 1;
                            if(state == -1){
                                    state = 6;
                            }
                            goToXY(30,6+state*2);
                            printf("★");
                    }
                    else if(choice == 80){
                            goToXY(30,6+state*2);
                            printf("\b  ");
                            state += 1;
                            if(state == 7){
                                    state = 0;
                            }
                            goToXY(30,6+state*2);
                            printf("★");
                    }else if(choice == 27){
                        fclose(file);
                        fclose(file_copy);
                        system("cls");
                        admin_main(name);

                    }else if(choice == '\r'){
                        system("cls");
                        drawBorder();
                        goToXY(24,10);
                        printf("请输入你要修改的信息：");
                        switch(state){
                            case 0:
                                scanf("%lf",&comm.in_price);
                                break;
                            case 1:
                                scanf("%lf",&comm.out_price);
                                break;
                            case 2:
                                scanf("%s",comm.desc);
                                break;
                            case 3:
                                scanf("%d",&comm.count);
                                break;
                            case 4:
                                scanf("%s",comm.sort);
                                break;
                            case 5:
                                scanf("%d",&comm.sold);
                                break;
                            case 6:
                                scanf("%s",comm.provider);
                                break;
                            }
                            fwrite(&comm,sizeof(struct commodity),1,file_copy);
                            break;
                        }
                    }
                }
            }
        }
     fclose(file);
     fclose(file_copy);
     remove(PRODUCT);
     rename("copy.dat",PRODUCT);
     progressBar("正在更改商品信息，请稍后！");
     system("cls");
     drawBorder();
     goToXY(30,9);
     printf("商品编号：%d",change_num);
     switch(state){
        case 0:
            goToXY(22,11);
            printf("您所输入的商品编号不存在！按任意键继续！");
            break;
        case 1:
            goToXY(25,11);
            printf("商品修改成功，按任意键继续！");
            break;
    }
     getch();
     system("cls");

     int choice;
     while(TRUE){
         system("cls");
         drawBorder();
         goToXY(20,9);
         printf("是否继续修改商品信息？请输入Yes/No:");
         char y_n[4];
         gets(y_n);
         if(!strcmp(y_n,"Yes")){
                choice = 1;
                break;
         }
         else if(!strcmp(y_n,"No")){
                choice = 0;
                break;
         }
         else
            printf("输入错误！");
         }
         switch(choice)
         {
            case 1:
                change_comm(name);
                break;

            case 0:
                system("cls");
                admin_main(name);
                break;
         }
}
void buy_record(char *name){
    system("cls");
    drawBorder();
    remove("tmp.dat");
    FILE *file = fopen(BUY_RECORD,"ab+");
    FILE *file_tmp = fopen("tmp.dat","ab+");

    struct record rec = {"","",0,""};
    rewind(file);
    while(!feof(file)){
        int result = fread(&rec,sizeof(struct record),1,file);
        if(result != 0){
            if(!strcmp(name,rec.name)){
                fwrite(&rec,sizeof(struct record),1,file_tmp);
            }
        }
    }

    fclose(file);
    fclose(file_tmp);

    show_page("tmp.dat","购买记录",name,2);
}
void buy_product(char *name){
    int state=0;
    system("cls");
    drawBorder();
    goToXY(28,3);
    printf("请选择购买方式");
    goToXY(26,12);
    printf("①  ★  查询购买");
    goToXY(26,14);
    printf("②      查看购物车");
    while(TRUE)
    {
        char choice;
        choice = getch();
        if(choice == 72)
        {
            goToXY(30,12+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1)
            {
                state = 1;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == 80)
        {
            goToXY(30,12+state*2);
            printf("\b  ");
            state += 1;
            if(state == 2)
            {
                state = 0;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == '\r')
        {
            switch(state)
            {
            case 0:
            {
                int state = 0;//表示查询商品时的状态
                int buy_code;
                int buy_count;
                system("cls");
                drawBorder();
                goToXY(23,3);
                printf("****商品选购页面,期待着您的光临！****");
                goToXY(20,6);
                printf("请输入您要搜索的商品编号：");
                scanf("%d",&buy_code);

                FILE *file = fopen(PRODUCT,"ab+");
                struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
                rewind(file);
                while(!feof(file))
                {
                    int result = fread(&comm,sizeof(struct commodity),1,file);
                    if((result == 1)&&(buy_code == comm.num))
                    {
                        state = 1;
                        break;
                    }
                }
                fclose(file);
                if(state == 1)
                {
                    goToXY(25,8);
                    printf("商品编号：%d",comm.num);
                    goToXY(25,9);
                    printf("商品名称：%s",comm.name);
                    goToXY(25,10);
                    printf("商品描述：%s",comm.desc);
                    goToXY(25,11);
                    printf("商品类别：%s",comm.sort);
                    goToXY(25,12);
                    printf("商品生产商：%s",comm.provider);
                    goToXY(25,13);
                    printf("商品售价：%.1lf",comm.out_price);
                    goToXY(18,16);
                    printf("请输入您要购买的商品件数：");
                    scanf("%d",&buy_count);
                    if(comm.count < buy_count)
                    {
                        system("cls");
                        drawBorder();
                        goToXY(23,11);
                        printf("选购商品库存不足，按联系管理员！");
                        getch();
                        system("cls");
                        cus_main(name);
                    }
                    else
                    {
                        progressBar("系统正在结算，请稍候！");
                        del_pro(buy_code);
                        FILE *file = fopen(PRODUCT,"ab+");
                        comm.sold += buy_count;
                        comm.count -= buy_count;
                        vault(comm.out_price,buy_count);
                        fwrite(&comm,sizeof(struct commodity),1,file);
                        fclose(file);

                        file = fopen(BUY_RECORD,"ab+");
                        struct record rec = {"","",0,""};
                        strcpy(rec.name,name);
                        strcpy(rec.product,comm.name);
                        rec.quantity = buy_count;
                        char date[15];
                        time_t timep;
                        struct tm *p;
                        time (&timep);
                        p=gmtime(&timep);
                        sprintf(date,"%d-%d-%d",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday);
                        strcpy(rec.date,date);
                        fwrite(&rec,sizeof(struct record),1,file);
                        fclose(file);

                        system("cls");
                        drawBorder();
                        goToXY(23,11);
                        printf("选购商品已经购买成功，按任意键继续！");
                        getch();
                        system("cls");
                        cus_main(name);
                    }
                }
                else if(state == 0)
                {
                    goToXY(18,8);
                    printf("暂时未能搜索到你要查找的商品，请期待它的上架！");
                    goToXY(28,14);
                    printf("按任意键继续！");
                    getch();
                    system("cls");
                    cus_main(name);
                }


            }
            case 1:
                system("cls");
                show_page(name,"购物车",name,2);
            }
        }

    }
}
void sort_search(char *name,int ver){
    remove("tmp_1.dat");
    int state = 0;
    system("cls");
    drawBorder();
    char input[20];
    goToXY(23,3);
    printf("****分类查询页面,个性化您的查询！****");
    goToXY(20,7);
    printf("情输入您要查询的商品类别：");
    scanf("%s",input);
    FILE *file_tmp = fopen("tmp_1.dat","ab+");
    FILE *file = fopen(PRODUCT,"ab+");
    struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
    rewind(file);
    while(!feof(file)){
        int result = fread(&comm,sizeof(struct commodity),1,file);
        if((result == 1)&&(!strcmp(comm.sort,input))){
            fwrite(&comm,sizeof(struct commodity),1,file_tmp);
            state = 1;
        }
    }
    fclose(file);
    fclose(file_tmp);
    progressBar("系统正在对该类别信息进行查询，请稍候！");
    if(state == 0){
        system("cls");
        drawBorder();
        goToXY(18,11);
        printf("您所查询的商品类别不存在，按任意键返回主界面！");
        getch();
        switch(ver){
            case 1:
                system("cls");
                admin_main(name);
                break;
            case 2:
                system("cls");
                cus_main(name);
                break;
        }
    }else if(state == 1){
        show_page("tmp_1.dat","分类商品",name,ver);
    }
}
void admin_unsubscribe(char *name){
    int state=0;
    system("cls");
    drawBorder();
    goToXY(28,3);
    printf("你确定要注销该账号？");
    goToXY(26,12);
    printf("①  ★  确定");
    goToXY(26,14);
    printf("②      取消");
    while(TRUE)
    {
        char choice;
        choice = getch();
        if(choice == 72)
        {
            goToXY(30,12+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1)
            {
                state = 1;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == 80)
        {
            goToXY(30,12+state*2);
            printf("\b  ");
            state += 1;
            if(state == 2)
            {
                state = 0;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == '\r')
        {
            switch(state)
            {
            case 0:
               {
                FILE *file = fopen("user_1.dat","ab+");
                FILE *file_copy = fopen("copy.dat","ab+");
                struct user User= {"","","","","",""};
                rewind(file);
                while(!feof(file))
                {
                    int result = fread(&User,sizeof(struct user),1,file);
                    if(result != 0)
                    {
                        if(strcmp(User.name,name)!=0)
                        {
                            fwrite(&User,sizeof(struct user),1,file_copy);
                        }
                    }
                }
                fclose(file);
                fclose(file_copy);
                remove("user_1.dat");
                rename("copy.dat","user_1.dat");
                system("cls");
                drawBorder();
                goToXY(28,9);
                printf("账户注销成功，按任意键退出！");
                getch();
                system("cls");
                start();
                break;}
            case 1:
                system("cls");
                admin_main(name);
            }
        }
    }
}
void cus_unsubscribe(char *name){
    int state=0;
    system("cls");
    drawBorder();
    goToXY(28,3);
    printf("你确定要注销该账号？");
    goToXY(26,12);
    printf("①  ★  确定");
    goToXY(26,14);
    printf("②      取消");
    while(TRUE)
    {
        char choice;
        choice = getch();
        if(choice == 72)
        {
            goToXY(30,12+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1)
            {
                state = 1;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == 80)
        {
            goToXY(30,12+state*2);
            printf("\b  ");
            state += 1;
            if(state == 2)
            {
                state = 0;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == '\r')
        {
            switch(state)
            {
            case 0:
               {
                FILE *file = fopen("user_2.dat","ab+");
                FILE *file_copy = fopen("copy.dat","ab+");
                struct user User= {"","","","","",""};
                rewind(file);
                while(!feof(file))
                {
                    int result = fread(&User,sizeof(struct user),1,file);
                    if(result != 0)
                    {
                        if(strcmp(User.name,name)!=0)
                        {
                            fwrite(&User,sizeof(struct user),1,file_copy);
                        }
                    }
                }
                fclose(file);
                fclose(file_copy);
                remove("user_2.dat");
                rename("copy.dat","user_2.dat");
                system("cls");
                drawBorder();
                goToXY(28,9);
                printf("账户注销成功，按任意键退出！");
                getch();
                system("cls");
                start();
                break;}
            case 1:
                system("cls");
                cus_main(name);
            }
        }

    }
}
void out_file(char *name,int ver){
    if(ver == 1){
        FILE *file_out = fopen("信息导出_管理员.txt","w");
        FILE *file = fopen(PRODUCT,"ab+");
        struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
        while(!feof(file)){
            char info[100];
            int result = fread(&comm,sizeof(struct commodity),1,file);
            if(result == 1){
                sprintf(info,"商品编号：%d-商品名称：%s-商品描述：%s-商品类别：%s-商品生产商：%s-已售量：%d-库存量：%d-进价：%.1lf-售价：%.1lf\n",comm.num,comm.name,comm.desc,comm.sort,comm.provider,comm.sold,comm.count,comm.in_price,comm.out_price);
                fputs(info,file_out);
            }
        }
        fclose(file);
        fclose(file_out);
        system("cls");
        drawBorder();
        progressBar("正在将系统商品数据转存为文件，请稍候！");
        system("cls");
        drawBorder();
        goToXY(25,11);
        printf("商品信息导出成功，按任意键继续！");
        getch();
        system("cls");
        admin_main(name);
    }else if(ver == 2){
        FILE *file_out = fopen("信息导出_顾客用户.txt","w");
        FILE *file = fopen(PRODUCT,"ab+");
        struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
        while(!feof(file)){
            char info[100];
            int result = fread(&comm,sizeof(struct commodity),1,file);
            if(result == 1){
                sprintf(info,"商品编号：%d-商品名称：%s-商品描述：%s-商品类别：%s-商品生产商：%s-商品已售量：%d-商品售价：%.1lf\n",comm.num,comm.name,comm.desc,comm.sort,comm.provider,comm.sold,comm.out_price);
                fputs(info,file_out);
            }
        }
        fclose(file);
        fclose(file_out);
        system("cls");
        drawBorder();
        progressBar("正在将系统商品数据转存为文件，请稍候！");
        system("cls");
        drawBorder();
        goToXY(25,11);
        printf("商品信息导出成功，按任意键继续！");
        getch();
        system("cls");
        cus_main(name);
    }
}
void info_change(char *name,int ver){
     FILE *file;
     if(ver == 1){
        file = fopen(USER_1,"ab+");
     }else if(ver == 2){
        file = fopen(USER_2,"ab+");
    }
    remove("copy.dat");
    FILE *file_copy = fopen("copy.dat","ab+");
     struct user use = {"","","","","",""};
     struct user User= {"","","","","",""};
     rewind(file);
     while(!feof(file)){
         int result = fread(&use,sizeof(struct user),1,file);
         if(result != 0){
             if(strcmp(use.name,name)){
                fwrite(&use,sizeof(struct user),1,file_copy);
             }
             if(!strcmp(use.name,name)){
                system("cls");
                int state = 0;
                drawBorder();
                goToXY(24,3);
                printf("请选择您要修改的信息：");
                goToXY(26,6);
                printf("①  ★  昵称");
                goToXY(46,6);
                printf("当前：%s",use.name);
                goToXY(26,8);
                printf("②      性别");
                goToXY(46,8);
                printf("当前：%s",use.sex);
                goToXY(26,10);
                printf("③      邮箱");
                goToXY(46,10);
                printf("当前：%s",use.mail);
                goToXY(26,12);
                printf("④      手机号");
                goToXY(46,12);
                printf("当前：%s",use.phone);
                goToXY(26,14);
                printf("⑤      密码");
                updown_bottom();
                while(TRUE){
                    char choice;
                    choice = getch();
                    if(choice == 72){
                        goToXY(30,6+state*2);
                        printf("\b  ");
                        state -= 1;
                        if(state == -1){
                            state = 4;
                        }
                        goToXY(30,6+state*2);
                        printf("★");
                    }else if(choice == 27){
                        fclose(file);
                        fclose(file_copy);
                        system("cls");
                        switch(ver){
                            case 1:
                                admin_main(name);
                                break;
                            case 2:
                                cus_main(name);
                                break;
                        }
                    }
                    else if(choice == 80){
                        goToXY(30,6+state*2);
                        printf("\b  ");
                        state += 1;
                        if(state == 5){
                            state = 0;
                        }
                        goToXY(30,6+state*2);
                        printf("★");
                    }else if(choice == '\r'){
                        system("cls");
                        drawBorder();
                        goToXY(24,10);
                        printf("请输入你要修改的信息：");
                        int state_1 = 1;
                        switch(state){
                            case 0:
                                scanf("%s",use.name);
                                char USER_NOW[30];
                                sprintf(USER_NOW,"USER_%d",ver);
                                FILE *file_info;
                                file_info = fopen(USER_NOW,"ab+");
                                rewind(file_info);
                                while(!feof(file))
                                {
                                    int result = fread(&User,sizeof(struct user),1,file);
                                    if(result != 0)
                                    {
                                        if(strcmp(User.name,use.name)==0){
                                            state_1 = 0;
                                            break;
                                        }
                                    }
                                }
                                if(state_1 == 0){
                                    system("cls");
                                    drawBorder();
                                    goToXY(25,11);
                                    printf("用户名重复，信息修改失败！");
                                    getch();
                                    system("cls");
                                    info_change(name,ver);
                                    cus_login();
                                }


                                break;

                            case 1:
                                scanf("%s",use.sex);
                                break;

                            case 2:
                                scanf("%s",use.mail);
                                break;

                            case 3:
                                scanf("%s",use.phone);
                                break;

                            case 4:
                                scanf("%s",use.pass);
                                strcpy(use.pass_double,use.pass);
                                break;
                        }
                        fwrite(&use,sizeof(struct user),1,file_copy);
                        break;
                    }
                }
            }
        }
    }
     fclose(file);
     fclose(file_copy);
     if(ver == 1){
        remove(USER_1);
        rename("copy.dat",USER_1);
     }
     else if(ver == 2){
        remove(USER_2);
        rename("copy.dat",USER_2);
     }
     progressBar("正在更改个人信息，请稍后！");
     system("cls");
     drawBorder();
     goToXY(25,11);
     printf("个人信息修改成功，按任意键继续！");
     getch();
     system("cls");
     if(ver == 1)
        admin_login_login();
     else if(ver == 2)
        cus_login_login();
}
void search_comm(char *name,int ver){
     system("cls");
     drawBorder();
     goToXY(28,3);
     printf("****关键字查询商品****");
     goToXY(24,10);
     printf("请输入关键字:");
     char key[15];
     scanf("%s",key);
     FILE *file = fopen(PRODUCT,"ab+");
     FILE *file_copy;
     file_copy = fopen("copy1.dat","w");
     struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
     rewind(file);
     while(!feof(file)){
         int result = fread(&comm,sizeof(struct commodity),1,file);
         if(result != 0){
             if(strstr(comm.name,key)!=NULL){
                 fwrite(&comm,sizeof(struct commodity),1,file_copy);
             }
         }
     }
     fclose(file);
     fclose(file_copy);
     show_page("copy1.dat","商品信息",name,ver);

}
void sales_ranking_query(char *name,int ver){
    system("cls");
    drawBorder();
    goToXY(23,3);
    printf("****分类查询销量排序****");
    goToXY(20,8);
    char view_sort[30];
    printf("输入您想查看的商品类别：");
    scanf("%s",view_sort);
    FILE *file =fopen("product.dat","ab+");

    struct commodity select_comm= {0,"",0.0,0.0,"",0.0,"",0,""};
    rewind(file);
    struct commodity product_select[1000];
    i=0;
    while(!feof(file))
    {
        int result = fread(&select_comm,sizeof(struct commodity),1,file);
        if(result != 0)
        {
            if(strcmp(select_comm.sort,view_sort)==0)
            {
                product_select[i]=select_comm;
                i++;
            }
        }
    }
    for(j=i-1; j>0; j--)
    {
        for(k=0; k<j; k++)
        {
            if(product_select[k].sold < product_select[k+1].sold)
            {
                struct commodity tmp=product_select[k];
                product_select[k]=product_select[k+1];
                product_select[k+1]=tmp;
            }
        }
    }
    fclose(file);
    FILE *file_select=fopen("select.dat","w");
    rewind(file_select);
    for(j=0; j<i; j++)
    {
        fwrite(&product_select[j],sizeof(struct commodity),1,file_select);
        printf("%s---%s---%d---%d\n",product_select[j].desc,product_select[j].provider,product_select[j].sold,product_select[j].count);
    }
    fclose(file_select);
	show_page("select.dat","销量排序",name,ver);
}
void buttom_title1(int num,int max_num,int ver){
    goToXY(6,21);
    if(ver==1)
    printf("【ESC】返回主界面\t【N】向后翻页\t【P】向前翻页\t当前页码：%d/%d",num+1,max_num);
    else printf("【ESC】返回主界面 【N】向后翻页 【P】向前翻页 【B】购买 当前页码：%d/%d",num+1,max_num);
}
void buttom_title2(int num,int max_num)
{
    goToXY(6,21);

    printf("【ESC】返回主界面\t【N】向后翻页\t【P】向前翻页\t当前页码：%d/%d",num+1,max_num);

}
double vault(double out_price,int number){
    double total = 0.0;
    double total_tmp = 0.0;
    FILE *file;
    file = fopen(VAULT,"ab+");
    int result = fread(&total_tmp,sizeof(double),1,file);
    if(result == 1){
    	total = total_tmp;
	}
    fclose(file);
    total = total + out_price*number;
    file = fopen(VAULT,"w");
    fwrite(&total,sizeof(double),1,file);
    fclose(file);
    return total;
}
void alert(char *name){
    FILE *file = fopen(PRODUCT,"ab+");
    FILE *file_copy = fopen("copy1.dat","w");
    struct commodity comm = {0,"",0.0,0.0,"",0,"",0,""};
    rewind(file);
    int num = 0;
    while(!feof(file)){
        int result = fread(&comm,sizeof(struct commodity),1,file);
        if(result != 0){
            if(comm.count <= 3){
                fwrite(&comm,sizeof(struct commodity),1,file_copy);
                num = 1;
            }
        }
    }
    fclose(file);
    fclose(file_copy);
    if(num == 1)
    {
        show_page("copy1.dat","库存过低的商品",name,1);
    }
}
void sold_chart(char *name){
    remove(DAY_SOLD);
    int days = 0;
    FILE *file = fopen(BUY_RECORD,"ab+");
    system("cls");
    drawBorder();
    progressBar("正在为您生成日销量报表，请稍候！");
    system("cls");
    struct record rec = {"","",0,""};
    rewind(file);
    char min_date[15] = "2020-12-30";

    while(!feof(file)){
        int result = fread(&rec,sizeof(struct record),1,file);
        if(result == 1 && (strcmp(rec.date,min_date) < 0)){
            strcpy(min_date,rec.date);
        }
    }
    char max_date[15];
    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    sprintf(max_date,"%d-%d-%d",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday);
    days = count_days(min_date,max_date);
    FILE *file_day = fopen(DAY_SOLD,"ab+");
    struct day_sold ds = {"",0};
    int count = 0;
    int nouse_year;
    int month;
    int day;
    sscanf(min_date,"%d-%d-%d",&nouse_year,&month,&day);
    char date[15];
    for(i = 0;i < days;i++){
        count = 0;
        sprintf(date,"%d-%d-%d",nouse_year,month,day);
        rewind(file);
        while(!feof(file)){
            int result = fread(&rec,sizeof(struct record),1,file);
            if(result == 1 && !strcmp(rec.date,date)){
                count +=rec.quantity;
            }
        }
        strcpy(ds.date,date);
        ds.count = count;
        fwrite(&ds,sizeof(struct day_sold),1,file_day);
        day ++;
        if(month == 1 || month == 3 || month == 5|| month == 7 || month == 8 || month == 10 || month == 12){
            if(day == 32){
                day = 1;
                month++;
            }
        }else if(month == 2){
            if(day == 29){
                day =1;
                month++;
            }
        }else{
            if(day == 31){
                day =1;
                month++;
            }
        }

    }

    fclose(file);
    fclose(file_day);
    drawBorder();
    drawInBorder();
    goToXY(25,2);
    printf("****以下是最近%d天的日销量情况****",count_sold(name));
    show_chart(name,count_sold(name));
}
int count_sold(char *name){
    return count(DAY_SOLD,name);
}
void show_chart(char *name,int days){
    int page_num = 0;//记录当前的翻页数
    buttom_title2(page_num,count(DAY_SOLD,name)/5 + 1);

    FILE *file = fopen(DAY_SOLD,"ab+");
    struct day_sold ds = {"",0};
    rewind(file);
    for(i = 1;i <= 6;i++){
        int result = fread(&ds,sizeof(struct day_sold),1,file);
        if(result == 1){
            char date[10];
            int month;
            int day;
            sscanf(ds.date,"%d-%d-%d",&k,&month,&day);
            sprintf(date,"%d-%d",month,day);
            goToXY(4,1+3*i);
            printf("%s: ",date);
            for(j = 0;j < ds.count/5 + 1;j++){
                printf("▌");
            }
            goToXY(70,1+3*i);
            printf("%d件",ds.count);
        }
    }

    fclose(file);
    int state = 1;
    int choice = getch();
    while(state){
        switch(choice){
            case 110://N键
                state = 0;
                page_num++;
                if(page_num > count(DAY_SOLD,name)/5){
                    page_num = count(DAY_SOLD,name)/5;
                }
                chart_down(page_num,name,days);
                break;
            case 112://P键
                state = 0;
                page_num--;
                if(page_num < 0){
                    page_num = 0;
                }
                chart_up(page_num,name,days);
                break;
            case 27:
                state = 0;
                system("cls");
                admin_main(name);
                break;
            default:
                choice = getch();
        }
    }
}
void chart_up(int num,char *name,int days){
    int nums = 0;//检索
    system("cls");
    drawBorder();
    drawInBorder();
    buttom_title2(num,count(DAY_SOLD,name)/5 + 1);
    goToXY(25,2);
    printf("****以下是最近%d天的日销量情况****",days);
    FILE *file = fopen(DAY_SOLD,"ab+");
    struct day_sold ds = {"",0};
    rewind(file);
    fseek(file,sizeof(struct day_sold)*5*num,SEEK_SET);
    for(i = 1;i <= 6;i++){
        int result = fread(&ds,sizeof(struct day_sold),1,file);
        if(result == 1){
            char date[15];
            int month;
            int day;
            sscanf(ds.date,"%d-%d-%d",&k,&month,&day);
            sprintf(date,"%d-%d",month,day);
            goToXY(4,1+3*i);
            printf("%s: ",date);
            for(j = 0;j < ds.count/5 + 1;j++){
                printf("▌");
            }
            goToXY(70,1+3*i);
            printf("%d件",ds.count);
        }
    }
    fclose(file);
    int state = 1;
    int choice = getch();
    while(state){
        switch(choice){
            case 110://N键
                state = 0;
                num++;
                if(num > count(DAY_SOLD,name)/5){
                    num = count(DAY_SOLD,name)/5;
                }
                chart_down(num,name,days);
                break;
            case 112://P键
                state = 0;
                num--;
                if(num < 0){
                    num = 0;
                }
                chart_up(num,name,days);
                break;
            case 27:
                state = 0;
                system("cls");
                admin_main(name);
                break;
            default:
                choice = getch();
        }
    }
}
void chart_down(int num,char *name,int days){
    int nums = 0;//检索
    system("cls");
    drawBorder();
    drawInBorder();
    buttom_title2(num,count(DAY_SOLD,name)/5 + 1);
    goToXY(25,2);
    printf("****以下是最近%d天的日销量情况****",days);
    FILE *file = fopen(DAY_SOLD,"ab+");
    struct day_sold ds = {"",0};
    rewind(file);
    fseek(file,sizeof(struct day_sold)*5*num,SEEK_SET);
    for(i = 1;i <= 6;i++){
        int result = fread(&ds,sizeof(struct day_sold),1,file);
        if(result == 1){
            char date[15];
            int month;
            int day;
            sscanf(ds.date,"%d-%d-%d",&k,&month,&day);
            sprintf(date,"%d-%d",month,day);
            goToXY(4,1+3*i);
            printf("%s: ",date);
            for(j = 0;j < ds.count/5 + 1;j++){
                printf("▌");
            }
            goToXY(70,1+3*i);
            printf("%d件",ds.count);
        }
    }
    fclose(file);
    int state = 1;
    int choice = getch();
    while(state){
        switch(choice){
            case 110://N键
                state = 0;
                num++;
                if(num > count(DAY_SOLD,name)/5){
                    num = count(DAY_SOLD,name)/5;
                }
                chart_down(num,name,days);
                break;
            case 112://P键
                state = 0;
                num--;
                if(num < 0){
                    num = 0;
                }
                chart_up(num,name,days);
                break;
            case 27:
                state = 0;
                system("cls");
                admin_main(name);
                break;
            default:
                choice = getch();
        }
    }
}
int count_days(char *min_date,char *max_date){
    int count = 0;
    int max_year;
    int max_month;
    int max_day;
    int min_year;
    int min_month;
    int min_day;
    sscanf(max_date,"%d-%d-%d",&max_year,&max_month,&max_day);
    sscanf(min_date,"%d-%d-%d",&min_year,&min_month,&min_day);
    for(i = min_month + 1;i < max_month;i++){
        if(i == 1 || i == 3 || i == 5|| i == 7 || i == 8 || i == 10 || i == 12){
            count += 31;
        }else if(i == 2){
            count += 28;//暂时不管是不是闰年
        }else{
            count += 30;
        }
    }
    if(max_month != min_month){
        if(min_month == 1 || min_month == 3 || min_month == 5|| min_month == 7 || min_month == 8 || min_month == 10 || min_month == 12 ){
            count += 32 - min_day;
        }else if(min_month == 2){
            count += 29 - min_day;//暂时不管是不是闰年
        }else{
            count += 31 - min_day;
        }
        count += max_day;
    }else{
        count += max_day - min_day + 1;
    }

    return count;
}
void updown_bottom(){
    goToXY(7,21);
    printf("【ENTER】选择进入\t【ESC】返回\t【↓】向下\t【↑】向上");
}
void file_oi(char *name){
    int state = 0;
    system("cls");
    drawBorder();
    goToXY(26,9);
    printf("请选择导出或导入：");
    goToXY(26,12);
    printf("①  ★  信息导入");
    goToXY(26,14);
    printf("②      信息导出");
    updown_bottom();
    while(TRUE){
        char choice;
        choice = getch();
        if(choice == 72){
            goToXY(30,12+state*2);
            printf("\b  ");
            state -= 1;
            if(state == -1){
                state = 2;
            }
            goToXY(30,12+state*2);
            printf("★");
        }
        else if(choice == 80){

            goToXY(30,12+state*2);
            printf("\b  ");
            state += 1;
            if(state == 2){
                state = 0;
            }
            goToXY(30,12+state*2);
            printf("★");

        }else if(choice == '\r'){
            switch(state){
                case 0:
                    in_file(name);
                    break;
                case 1:
                    system("cls");
                    drawBorder();
                    out_file(name,1);
                    break;
            }
        }else if(choice == 27){
            system("cls");
            drawBorder();
            admin_main(name);
        }
    }
    getchar();
}
void in_file(char *name){
    int count = 0;
    system("cls");
    drawBorder();
    char file_in[30],str[150],*result,delims[] = "-",nouse[30];
    goToXY(20,3);
    printf("****在这里你可以将文件中的商品信息导入系统****");
    goToXY(18,8);
    printf("请输入文件夹中的商品信息文件：");
    scanf("%s",&file_in);
    system("copy product.dat pro.dat");
    struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,""};
    FILE *file = fopen(file_in,"r");
    FILE *file_pro = fopen(PRODUCT,"ab+");
    while(fgets(str,150,file)!=NULL){
        str[strlen(str) - 1] = '\0';
		result = strtok( str, delims );
		sscanf(result,"%10s%d",&nouse,&comm.num);
		result = strtok( NULL, delims );
		sscanf(result,"%10s%s",&nouse,&comm.name);
		result = strtok( NULL, delims );
		sscanf(result,"%10s%s",&nouse,&comm.desc);
		result = strtok( NULL, delims );
		sscanf(result,"%10s%s",&nouse,&comm.sort);
		result = strtok( NULL, delims );
		sscanf(result,"%12s%s",&nouse,&comm.provider);
		result = strtok( NULL, delims );
		sscanf(result,"%8s%d",&nouse,&comm.sold);
		result = strtok( NULL, delims );
		sscanf(result,"%8s%d",&nouse,&comm.count);
		result = strtok( NULL, delims );
		sscanf(result,"%6s%lf",&nouse,&comm.in_price);
		result = strtok( NULL, delims );
		sscanf(result,"%6s%lf",&nouse,&comm.out_price);

		if(ver_comm(comm) == 0){
            fwrite(&comm,sizeof(struct commodity),1,file_pro);
            count ++;
		}


	}
	fclose(file);
	fclose(file_pro);
    progressBar("正在将文件中的信息导入，请稍候！");
    system("cls");
    drawBorder();
    if(count != 0){
        goToXY(22,11);
        printf("本次共导入%d条商品信息！按任意键继续！",count);
    }else{
        goToXY(22,10);
        printf("抱歉！在您提供的文件中没有找到商品信息！");
        goToXY(29,11);
        printf("按任意键继续！");
    }
    getch();
    system("cls");
    admin_main(name);
}
int ver_comm(struct commodity comm){
    int state = 0;
    FILE *file = fopen("pro.dat","ab+");
    struct commodity co = {0,"",0.0,0.0,"",0.0,"",0,""};
    rewind(file);
    while(!feof(file)){
        int result = fread(&co,sizeof(struct commodity),1,file);
        if(result == 1 && co.num == comm.num && !strcmp(co.name,comm.name) && !strcmp(co.desc,comm.desc)){
            state = 1;
            break;
        }
    }
    return state;
}
void move_to_shopping_cart(char *name)
{
    goToXY(6,22);
    int select_num,select_count;
    printf("请输入想加入购物车的商品编号");
    scanf("%d",&select_num);
    FILE *file=fopen(PRODUCT,"ab+");
    FILE *file_cart=fopen(name,"ab+");
    struct commodity cart_comm= {0,"",0,0,"",0,"",0,"",0};
    struct commodity test_comm= {0,"",0,0,"",0,"",0,"",0};
    rewind(file);
    j=1;
    while(!feof(file))
    {
        int result = fread(&cart_comm,sizeof(struct commodity),1,file);
        if(result != 0)
        {
            if(cart_comm.num==select_num)
            {
                j=0;
                break;
            }


        }
    }
    if(j)
    {
        system("cls");
        goToXY(28,9);
        printf("没有此商品！");
        system("pause");
        system("cls");
        cus_main(name);
    }

    else
    {
        system("cls");
        goToXY(23,9);
        printf("请输入加入购物车的数量：");
        scanf("%d",&select_count);
        rewind(file);
        while(!feof(file_cart))
        {
            int result = fread(&test_comm,sizeof(struct commodity),1,file_cart);
            if(result != 0)
            {
                if(test_comm.num==select_num)
                {
                    j=1;
                    break;
                }
            }
        }
        if(!j)
        {
            cart_comm.cart_count=select_count;
            fwrite(&cart_comm,sizeof(struct commodity),1,file_cart);
            fclose(file);
            fclose(file_cart);
        }
        else
        {
            test_comm.cart_count+=select_count;


            FILE *file_move = fopen("cop.dat","ab+");
            rewind(file_cart);
            rewind(file_move);
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
            rewind(file_cart);
            while(!feof(file_cart))
            {
                int result = fread(&comm,sizeof(struct commodity),1,file_cart);
                if(result != 0)
                {
                    if(comm.num != test_comm.num)
                    {
                        fwrite(&comm,sizeof(struct commodity),1,file_move);
                    }
                    else
                    {
                        fwrite(&test_comm,sizeof(struct commodity),1,file_move);
                    }
                }
            }
            fclose(file_cart);
            fclose(file_move);
            remove(name);
            rename("cop.dat",name);

        }

        system("cls");
        goToXY(28,9);
        printf("加入成功！");
        system("pause");
        system("cls");
        cus_main(name);
    }


}
void empty_cart(char *name)
{
    int state=0;

    FILE *buy_file=fopen(name,"ab+");
    struct commodity buy_comm= {0,"",0.0,0.0,"",0.0,"",0,"",0};
    rewind(buy_file);
    j=1;
    while(!feof(buy_file))
    {
        int result = fread(&buy_comm,sizeof(struct commodity),1,buy_file);
        if(result != 0)
        {
            FILE *file = fopen(PRODUCT,"ab+");
            struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
            rewind(file);

            while(!feof(file))
            {
                int result = fread(&comm,sizeof(struct commodity),1,file);//找到库房中的商品
                if((result == 1)&&(buy_comm.num == comm.num))
                {
                    state = 1;
                    break;
                }
            }
            fclose(file);
            if(state == 1)
            {
                if(comm.count < buy_comm.cart_count)      //判断是否有货
                {
                    j=0;
                    system("cls");
                    drawBorder();
                    goToXY(23,11);
                    printf("商品%s库存不足,本次购买取消！",buy_comm.name);
                    getch();
                    break;

                }
            }
        }
    }
    state=0;
    if(j==0)
    {
        system("cls");
        cus_main(name);
    }
    else
    {
        rewind(buy_file);
        while(!feof(buy_file))
        {
            int result = fread(&buy_comm,sizeof(struct commodity),1,buy_file);
            if(result != 0)
            {

                FILE *file = fopen(PRODUCT,"ab+");
                struct commodity comm = {0,"",0.0,0.0,"",0.0,"",0,"",0};
                rewind(file);
                while(!feof(file))
                {
                    int result = fread(&comm,sizeof(struct commodity),1,file);//找到库房中的商品
                    if((result == 1)&&(buy_comm.num == comm.num))
                    {
                        state = 1;
                        break;
                    }
                }
                fclose(file);
                if(state == 1)
                {
                    progressBar("系统正在结算，请稍候！");
                    del_pro(buy_comm.num);
                    FILE *file = fopen(PRODUCT,"ab+");
                    comm.sold += buy_comm.cart_count;
                    comm.count -= buy_comm.cart_count;
                    vault(comm.out_price,buy_comm.cart_count);
                    fwrite(&comm,sizeof(struct commodity),1,file);
                    fclose(file);

                    file = fopen(BUY_RECORD,"ab+");
                    struct record rec = {"","",0,""};
                    strcpy(rec.name,name);
                    strcpy(rec.product,comm.name);
                    rec.quantity = buy_comm.cart_count;
                    char date[15];
                    time_t timep;
                    struct tm *p;
                    time (&timep);
                    p=gmtime(&timep);
                    sprintf(date,"%d-%d-%d",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday);
                    strcpy(rec.date,date);
                    fwrite(&rec,sizeof(struct record),1,file);
                    fclose(file);
                }


            }
        }
        system("cls");
        drawBorder();
        goToXY(23,11);
        printf("选购商品已经购买成功，按任意键继续！");
        fclose(buy_file);
        FILE *buy_file=fopen(name,"w");
        fclose(buy_file);
        getch();
        system("cls");
        cus_main(name);
    }
}
void del_cart(char *name)
{   goToXY(6,22);
    int del_num,del_count;
    printf("请输入想删除的商品编号");
    scanf("%d",&del_num);
    FILE *file=fopen(name,"ab+");
    FILE *file_cart_del=fopen("name_cop.dat","ab+");
    struct commodity comm= {0,"",0,0,"",0,"",0,"",0};
    struct commodity comm_move= {0,"",0,0,"",0,"",0,"",0};
    rewind(file);
    j=1;
    while(!feof(file))
    {
        int result = fread(&comm,sizeof(struct commodity),1,file);
        if(result != 0)
        {
            if(comm.num==del_num)
            {
                j=0;
                break;
            }


        }
    }
    if(j)
    {
        system("cls");
        goToXY(26,9);
        printf("购物车中没有此商品！");
        system("pause");
        system("cls");
        cus_main(name);
    }

    else
    {
        system("cls");
        goToXY(23,9);
        printf("请输入删除的数量：");
        goToXY(18,11);
        printf("若输入数量大于购物车中数量,会将该商品全部删除!");
        scanf("%d",&del_count);
        if(comm.cart_count>del_count)
        {
            comm.cart_count-=del_count;
            rewind(file);
            rewind(file_cart_del);
            while(!feof(file))
            {
                int result = fread(&comm_move,sizeof(struct commodity),1,file);
                if(result != 0)
                {
                    if(comm.num != comm_move.num)
                    {
                        fwrite(&comm_move,sizeof(struct commodity),1,file_cart_del);
                    }
                    else
                    {
                        fwrite(&comm,sizeof(struct commodity),1,file_cart_del);
                    }
                }
            }
            fclose(file);
            fclose(file_cart_del);
            remove(name);
            rename("name_cop.dat",name);
        }
        else if(comm.cart_count<=del_count)
        {
            rewind(file);
            rewind(file_cart_del);
            while(!feof(file))
            {
                int result = fread(&comm_move,sizeof(struct commodity),1,file);
                if(result != 0)
                {
                    if(comm.num != comm_move.num)
                    {
                        fwrite(&comm_move,sizeof(struct commodity),1,file_cart_del);
                    }
                }
            }
            fclose(file);
            fclose(file_cart_del);
            remove(name);
            rename("name_cop.dat",name);

        }

        system("cls");
        goToXY(28,9);
        printf("删除成功！");
        system("pause");
        system("cls");
        cus_main(name);
    }



}
