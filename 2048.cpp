#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#define N 2//<=7用于设置N行N列的表格
#define WINNUMBER 4//2^WINNUMBER获胜的目标
#define NEWNUMBERPER 1 //定义随机数产生的个数
int Array_2048[N][N];//定义二维N行N列数组
char name [11] = {'\0'};//定义存储玩家姓名的字符数组
long highest_score[11][2];//定义二维数组用于储存最高分
char highest_name[11][11] = {"?","?","?","?","?","?","?","?","?","?","?"};//定义二维数组用于储存对应得分的玩家姓名初值为“？”
int your_NO = 0;//当前玩家排名
long score = 0;//定义当前得分
long highest_number = 0;//定义达到的最高数字
int win_number = WINNUMBER;//用于实现获胜目标的改变
void welcome_headline(void);//打印欢迎语函数
void print_tips(void);//打印提示指令函数
int read_line (char str[],int n);//读入用户的姓名函数
void ING(void);//重置随机数函数
void print_paint1(void);//动态打印2048图案函数
void print_paint2(void);//静态打印2048图案函数
void line(int n);//打印数表函数
void Prinft_Array_2048(void);//打印数表内容函数
int Make_new_number(int n);//生成随机数函数
int read(void);//输入移动命令函数
int GO_up(void);//向上判断函数
int GO_down(void);//向下判断函数
int GO_left(void);//向左判断函数
int GO_right(void);//向右判断函数
int test_highest(void);//最高分判断函数
void Make_scoretable(void);//制作得分榜函数
void prinft_scoretable(void);//打印得分榜函数
int IS_died(void);//判断游戏是否终结函数
int main()
{
    char key;//获取输入的字符
    char command = 0;//获取控制字符判断是否继续游戏
    int Enter = 0;//寄存输入命令上下左右
    int Keep_go = 1;//游戏继续进行
    long Highest_score = 0; //记录最高得分
    int i = 0; //用于清零
    int a = 0; //用于清零
    int b = 0; //用于清零
    ING(); //重置随机数
    system("COLOR F0");//背景颜色为白，字体为黑
    welcome_headline();//打印欢迎语
    system("cls");//对不需保存的变量进行清零
    do
    {
        {
            system("cls"); //对不需保存的变量进行清零
            score = your_NO = 0;//得分清零
            Keep_go = 1;//游戏继续进行
            win_number = WINNUMBER;//用于实现获胜目标的改变
            for(i=0; i<11; i++)
                name[i] = '\0';//存储玩家姓名的字符数组初始化
            for(a = 0; a < N ; a++)
                for(b = 0; b < N ; b++)
                    Array_2048[a][b] = 0;//二维N行N列数组初始化
        }
        system("COLOR F0");//背景颜色为白，字体为黑
        print_paint1();//打印2048图案
        print_tips();//打印提示指令
        read_line(name,10); //读入用户的姓名
        Make_new_number(NEWNUMBERPER); //生成第一个随机数
        do  //正常游戏
        {
            {
                system("cls");//对不需保存的变量进行清零
                system("COLOR F0");//背景颜色为白，字体为黑
                print_paint2();//静态打印2048图案
                printf( "\t\t\t\tHi, %3s!",name);//打印玩家姓名
                printf("\n\n\t\tWelcome to 2048! ");//打印欢迎语
                printf("Your mission is to get the number %d!\n\n",(1<<win_number));//打印获胜目标
                Prinft_Array_2048();//打印数表内容
            }
            {
                printf("Tips:m/M/5:display score rank\n\n");
                printf("\t\ts/S/2:go down\t\ta/A/4:go left\n\n");
                printf("\t\td/D/6:go right\t\tw/W/8:go up \n\n");
                printf("The highest score: %6ld\tYour score: %2ld\n\n",Highest_score,score);
                printf("Enter what your order:\n"); //打印提示语、最高记录与分数
            }
            Enter=read();//输入移动命令
            {
                switch(Enter)//判断位移反向，位移，判断位移是否成功（失败要求重来）
                {
                case 2:
                    if(GO_down()!=1) continue;
                    break;
                case 4:
                    if(GO_left()!=1) continue;
                    break;
                case 6:
                    if(GO_right()!=1) continue;
                    break;
                case 8:
                    if(GO_up()!=1) continue;
                    break;
                case 5:
                    prinft_scoretable();//打印得分榜
                    printf("Press any key to keep going\n");
                    scanf("%c",&key);
                    continue;
                    break;
                default :
                    continue;
                }
            }
            if(score>=Highest_score)
                Highest_score=score; //刷新最高分
            Make_scoretable(); //刷新排行榜
            if((highest_number=test_highest())>=win_number) //是否赢了，询问是否继续
            {
                win_number++;//获胜目标翻倍
                Prinft_Array_2048();//打印数表内容
                printf("Press any key to continue, enter n/N to end:");
                do
                {
                    scanf("%c",&command);
                }
                while(command=='\n');//输入n或N结束游戏
                printf("\n");
                if(command=='n'||command=='N')break;
            }
            Keep_go = Make_new_number(NEWNUMBERPER); //生成新的随机数，同时将是否生成成功记录在Keep_go中
            if(IS_died()) break; //死局判断，是死局就结束程序
        }
        while(Keep_go);  //失败跳出
        Make_scoretable(); //刷新排行榜
        {
            //Game Over（死局、空位不足）后显示最高分，你的成绩，结束时你的情况与积分表
            system("cls");
            system("COLOR F0");
            print_paint1();//打印2048图案
            printf("The highest score: %6ld\n",Highest_score);
            printf("Your score: %2ld\n",score);
            Prinft_Array_2048();//打印数表内容
            printf("\t\t\tGame over!\n\n");
            prinft_scoretable();//打印得分榜
            printf("Play again? Press any key to end, enter y/Y to continue:");
        }
        do
        {
            scanf("%c",&command);
        }
        while(command=='\n');
        printf("\n");
    }
    while(command=='y'||command=='Y');  //是否重来
    return 0;
}

void ING(void) //重置随机数（设置种子）
{
    srand((unsigned) time(NULL));
}

void welcome_headline(void)//欢迎列表的模拟动态打印
{
    char headline0[]="游戏开始前建议最大化窗口，效果更佳！^.^操作完毕请按回车";
    char headline1[]="LOADING\0";
    char headline2[]="......\0";
    printf("\n\n\n\n\n\n\t");
    for(int i=0; headline0[i]!='\0'; i++)
    {
        printf("%c",headline0[i]);
        Sleep(50);
    }
    getchar();
    system("cls");
    printf("\n\n\n\n\n\n\t\t\t\t");
    printf("游戏装载中，请稍候\n");
    Sleep(1500);
    system("cls");
    printf("\n\n\n\n\n\n\t\t\t\t");
    for(int i=0; headline1[i]!='\0'; i++)
    {
        printf("%c",headline1[i]);
        Sleep(50);
    }
    for(int j=0; j<3; j++)
    {
        for(int i=0; headline2[i]!='\0'; i++)
        {
            printf("%c",headline2[i]);
            Sleep(500);
        }
        printf("\b\b\b\b\b\b");
        printf("      ");
        printf("\b\b\b\b\b\b");
    }
    Sleep(1000);
}

void print_tips(void)//打印提示指令
{
    char tip1[]="Welcome to 2048! Your mission is to get the number\0";
    char tip2[]="Please enter your name(<= 10 letters):\0";
    for(int i=0; tip1[i]!='\0'; i++)
    {
        printf("%c",tip1[i]);
        Sleep(10);
    }
    printf("%d!\n\n",(1<<win_number));
    for(int i=0; tip2[i]!='\0'; i++)
    {
        printf("%c",tip2[i]);
        Sleep(10);
    }
    printf("\n\n");
}

int read_line (char str[],int n)//读入用户的姓名
{
    int ch , i = 0;
    while((ch = getchar())==' '||ch=='\n'||ch=='\0');
    while(ch!='\n')
    {
        if(i<n)
            str[i] = ch;
        i++;
        ch = getchar();
    }
    str[i]='\0';
    return i;
}

void print_paint1(void)//动态打印2048图案
{
    printf("********************************************************************************");
    Sleep(50);
    printf("********************************************************************************");
    Sleep(50);
    printf("**        **        **   **   ****        *************** **********************");
    Sleep(50);
    printf("**        **        **   **   ****        **************   *********************");
    Sleep(50);
    printf("*******   **  ****  **   **   ****  ****  *************     ********************");
    Sleep(50);
    printf("*******   **  ****  **   **   ****  ****  ************       *******************");
    Sleep(50);
    printf("*******   **  ****  **          **  ****  **********           *****************");
    Sleep(50);
    printf("**        **  ****  **          **        **************   *********************");
    Sleep(50);
    printf("**        **  ****  *******   ****        ************       *******************");
    Sleep(50);
    printf("**   *******  ****  *******   ****  ****  **********           *****************");
    Sleep(50);
    printf("**   *******  ****  *******   ****  ****  *******                 **************");
    Sleep(50);
    printf("**   *******  ****  *******   ****  ****  **************   *********************");
    Sleep(50);
    printf("**        **        **          **        **************   *********************");
    Sleep(50);
    printf("**        **        **          **        **************   *********************");
    Sleep(50);
    printf("********************************************************************************");
    Sleep(50);
    printf("********************************************************************************");
    Sleep(50);
    printf("\n\n");
}

void print_paint2(void)//静态打印2048图案
{
    printf("################################################################################");
    printf("################################################################################");
    printf("##        ##        ##   ##   ####        ############### ######################");
    printf("##        ##        ##   ##   ####        ##############   #####################");
    printf("#######   ##  ####  ##   ##   ####  ####  #############     ####################");
    printf("#######   ##  ####  ##   ##   ####  ####  ############       ###################");
    printf("#######   ##  ####  ##          ##  ####  ##########           #################");
    printf("##        ##  ####  ##          ##        ##############   #####################");
    printf("##        ##  ####  #######   ####        ############       ###################");
    printf("##   #######  ####  #######   ####  ####  ##########           #################");
    printf("##   #######  ####  #######   ####  ####  #######                 ##############");
    printf("##   #######  ####  #######   ####  ####  ##############   #####################");
    printf("##        ##        ##          ##        ##############   #####################");
    printf("##        ##        ##          ##        ##############   #####################");
    printf("################################################################################");
    printf("################################################################################");
    printf("\n\n");
}

int Make_new_number(int n)//生成随机数
{
    for(int L = 0; L < n ; L++)//保证生成NEWNUMBERPER 个随机数
    {
        int a = 0;
        int b = 0;
        int i = 0;
        int empty_place = 0;
        int temp = 0;
        for(a = 0; a < N ; a++)
            for(b = 0; b < N ; b++)
                empty_place += !(Array_2048[a][b]);//历览数组判断空位数
        if(empty_place == 0) return 0;//若空位为零则返回0
        temp = rand()%empty_place+1;//生成1~empty_place范围内的随机数
        a = b = i = 0;
        while(1)//随机在所有空位中选择一个添加2或4
        {
            i += !(Array_2048[a][b]);
            if(i>=temp) break;
            b++;
            if(b>=N)
            {
                a++;
                b=0;
            }
        }
        Array_2048[a][b] = 2 << ((rand()%4)/3);//2随机左移0或1生成2或4
    }
    return 1;
}

void line(int n)//打印数表
{
    for (int i = 0; i < abs(5-N); ++i)//保证表格保持居中
        printf("\t");
    for (int i = 0; i < N; ++i)
    {
        printf("--------");
    }
    printf("-");
    printf("\n");
}

void Prinft_Array_2048(void)//打印数表内容
{
    for (int i = 0; i < N; ++i)
    {
        line(N);
        for (int k = 0; k <abs(5-N); ++k)//保证表格保持居中
            printf("\t");
        for (int j = 0; j < N; ++j)
        {

            printf("|");
            if (Array_2048[i][j] == 0)
            {
                printf("\t");
                continue;
            }
            printf("%2d\t", Array_2048[i][j]);
        }
        printf("|");
        printf("\n");
    }
    line(N);
    printf("\n\n");
}

int read(void)//输入移动命令
{
    char a = 0;
    char b = 0;
    while(1)
    {
        a=b=0;
        do
        {
            scanf("%c",&a);
        }
        while(a=='\n');
        scanf("%c",&b);
        if(b=='\n')
        {
            if(a=='w'||a=='W'||a=='8')return 8;
            if(a=='a'||a=='A'||a=='4')return 4;
            if(a=='s'||a=='S'||a=='2')return 2;
            if(a=='d'||a=='D'||a=='6')return 6;
            if(a=='m'||a=='M'||a=='5')return 5;
        }
    }
}

int GO_down(void)//向下判断
{
    int a = 0;
    int b = 0;
    int t = 0;
    int t1 = 0;
    int t2 = 0;
    int L =0;
    for(b = 0; b < N ; b++)
    {
        for(a = t1 = t2 =N-1, t = 0; a >= 0 ; a--)
        {
            if(Array_2048[a][b]!=0)
            {
                if(Array_2048[a][b]==t)
                {
                    Array_2048[t2][b]=Array_2048[t2][b]<<1;
                    score += Array_2048[a][t2];
                    t2 = t1;
                    t = 0;
                    Array_2048[a][b]=0;
                    L=1;
                }
                else
                {
                    Array_2048[t1][b] = Array_2048[a][b];
                    t= Array_2048[a][b];
                    if(t1!=a)
                    {
                        Array_2048[a][b]=0;
                        L=1;
                    }
                    t2 = t1;
                    t1--;
                }
            }
        }
    }
    return L;
}

int GO_up(void)//向上判断
{
    int a = 0;
    int b = 0;
    int t = 0;
    int t1 = 0;
    int t2 = 0;
    int L =0;
    for(b = 0; b < N ; b++)
    {
        for(a = t = t1 = t2 = 0; a < N ; a++)
        {
            if(Array_2048[a][b]!=0)
            {
                if(Array_2048[a][b]==t)
                {
                    Array_2048[t2][b]=Array_2048[t2][b]<<1;
                    score += Array_2048[a][t2];
                    t2 = t1;
                    t = 0;
                    Array_2048[a][b]=0;
                    L=1;
                }
                else
                {
                    Array_2048[t1][b] = Array_2048[a][b];
                    t= Array_2048[a][b];
                    if(t1!=a)
                    {
                        Array_2048[a][b]=0;
                        L=1;
                    }
                    t2 = t1;
                    t1++;
                }
            }
        }
    }
    return L;
}

int GO_left(void)//向左判断
{
    int a = 0;
    int b = 0;
    int t = 0;
    int t1 = 0;
    int t2 = 0;
    int L =0;
    for(a = 0; a < N ; a++)
    {
        for(b = t = t1 = t2 = 0; b < N ; b++)
        {
            if(Array_2048[a][b]!=0)
            {
                if(Array_2048[a][b]==t)
                {
                    Array_2048[a][t2]=Array_2048[a][t2]<<1;
                    score += Array_2048[a][t2];
                    t2 = t1;
                    t = 0;
                    Array_2048[a][b]=0;
                    L=1;
                }
                else
                {
                    Array_2048[a][t1] = Array_2048[a][b];
                    t= Array_2048[a][b];
                    if(t1!=b)
                    {
                        Array_2048[a][b]=0;
                        L=1;
                    }
                    t2 = t1;
                    t1++;
                }
            }
        }
    }
    return L;
}

int GO_right(void)//向右判断
{
    int a = 0;
    int b = 0;
    int t = 0;
    int t1 = 0;
    int t2 = 0;
    int L =0;
    for(a = 0; a < N ; a++)
    {
        for(b = t1 = t2 = N-1,t = 0; b >= 0 ; b--)
        {
            if(Array_2048[a][b]!=0)
            {
                if(Array_2048[a][b]==t)
                {
                    Array_2048[a][t2]=Array_2048[a][t2]<<1;
                    score += Array_2048[a][t2];
                    t2 = t1;
                    t = 0;
                    Array_2048[a][b]=0;
                    L=1;
                }
                else
                {
                    Array_2048[a][t1] = Array_2048[a][b];
                    t= Array_2048[a][b];
                    if(t1!=b)
                    {
                        Array_2048[a][b]=0;
                        L=1;
                    }
                    t2 = t1;
                    t1--;
                }
            }
        }
    }
    return L;
}

int test_highest(void)//最高分判断
{
    int a = 0;
    int b = 0;
    int i = 0;
    long highest = 0;
    for(a = 0; a < N ; a++)
    {
        for(b = 0; b < N ; b++)
            if((Array_2048[a][b])>=highest) highest=Array_2048[a][b];//历览数组确定最大数组
    }
    for(i=0; highest>1; i++)
        highest=highest>>1;//判断位数，与WINNUMBER比较
    return i;
}

void Make_scoretable(void)//制作得分榜
{
    int i = 0;
    long I = 0;
    char L [11]= {0};
    highest_score[your_NO][0]=score;
    highest_score[your_NO][1]=highest_number;
    for(i=0; i<11; i++)
        highest_name[your_NO][i]=name[i];
    while(your_NO<10)
    {
        if((highest_score[your_NO][1]>highest_score[(your_NO+1)][1])&&
                (highest_score[your_NO][0]>=highest_score[(your_NO+1)][0]))
        {
            //如果当前玩家得分高于前玩家得分则交换二者排名
            I = highest_score[(your_NO+1)][1];
            highest_score[(your_NO+1)][1] = highest_score[your_NO][1];
            highest_score[your_NO][1] = I;//交换highest_number
            I = highest_score[(your_NO+1)][0];
            highest_score[(your_NO+1)][0] = highest_score[your_NO][0];
            highest_score[your_NO][0] = I;//交换score
            strcpy(L,highest_name[your_NO+1]);
            strcpy(highest_name[your_NO+1],highest_name[your_NO]);
            strcpy(highest_name[your_NO],L);//交换名字
            your_NO++;
        }
        else if((highest_score[your_NO][1]==highest_score[(your_NO+1)][1])&&
                (highest_score[your_NO][0]>highest_score[(your_NO+1)][0]))
        {
            I = highest_score[(your_NO+1)][1];
            highest_score[(your_NO+1)][1] = highest_score[your_NO][1];
            highest_score[your_NO][1] = I;//交换highest_number
            I = highest_score[(your_NO+1)][0];
            highest_score[(your_NO+1)][0] = highest_score[your_NO][0];
            highest_score[your_NO][0] = I;//交换score
            strcpy(L,highest_name[your_NO+1]);
            strcpy(highest_name[your_NO+1],highest_name[your_NO]);
            strcpy(highest_name[your_NO],L);//交换名字
            your_NO++;
        }
        else
            break;
    }
}

void prinft_scoretable(void)//打印得分榜
{
    int i = 0;
    char L [11]= {'\0'};
    printf("rank       name  score  highestno.\n");
    for (i=10; i>0; i--)
    {
        strcpy(L,highest_name[i]);
        printf("%2d %10s %6ld",(11-i),L,(highest_score[i][0]));
        if(highest_score[i][1]!=0) printf(" %6d",(1<<(highest_score[i][1])));
        else printf(" 0");
        if(i==your_NO)printf(" \2");
        printf("\n");
    }
}

int IS_died(void)//死局判断，是死局就结束程序
{
    int a = 0;
    int b = 0;
    int i = 0;
    for(a = 0; a < N ; a++)
    {
        for(b = 0; b < N ; b++)
        {
            if(Array_2048[a][b]==0)
            {
                return 0;
            }
        }
    }
    for(b = 0; b < N ; b++)
    {
        for(a = i = 0; a < N ; a++)
        {
            if(Array_2048[a][b]==i)
            {
                return 0;
            }
            else
            {
                i = Array_2048[a][b];
            }
        }
    }
    for(a = 0; a < N ; a++)
    {
        for(b = i = 0; b < N ; b++)
        {
            if(Array_2048[a][b]==i)
            {
                return 0;
            }
            else
            {
                i = Array_2048[a][b];
            }
        }
    }
    return 1;//判断各行各列是否有能够相加的数字若无则返回真
}



