#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#define N 2//<=7��������N��N�еı��
#define WINNUMBER 4//2^WINNUMBER��ʤ��Ŀ��
#define NEWNUMBERPER 1 //��������������ĸ���
int Array_2048[N][N];//�����άN��N������
char name [11] = {'\0'};//����洢����������ַ�����
long highest_score[11][2];//�����ά�������ڴ�����߷�
char highest_name[11][11] = {"?","?","?","?","?","?","?","?","?","?","?"};//�����ά�������ڴ����Ӧ�÷ֵ����������ֵΪ������
int your_NO = 0;//��ǰ�������
long score = 0;//���嵱ǰ�÷�
long highest_number = 0;//����ﵽ���������
int win_number = WINNUMBER;//����ʵ�ֻ�ʤĿ��ĸı�
void welcome_headline(void);//��ӡ��ӭ�ﺯ��
void print_tips(void);//��ӡ��ʾָ���
int read_line (char str[],int n);//�����û�����������
void ING(void);//�������������
void print_paint1(void);//��̬��ӡ2048ͼ������
void print_paint2(void);//��̬��ӡ2048ͼ������
void line(int n);//��ӡ������
void Prinft_Array_2048(void);//��ӡ�������ݺ���
int Make_new_number(int n);//�������������
int read(void);//�����ƶ������
int GO_up(void);//�����жϺ���
int GO_down(void);//�����жϺ���
int GO_left(void);//�����жϺ���
int GO_right(void);//�����жϺ���
int test_highest(void);//��߷��жϺ���
void Make_scoretable(void);//�����÷ְ���
void prinft_scoretable(void);//��ӡ�÷ְ���
int IS_died(void);//�ж���Ϸ�Ƿ��սắ��
int main()
{
    char key;//��ȡ������ַ�
    char command = 0;//��ȡ�����ַ��ж��Ƿ������Ϸ
    int Enter = 0;//�Ĵ�����������������
    int Keep_go = 1;//��Ϸ��������
    long Highest_score = 0; //��¼��ߵ÷�
    int i = 0; //��������
    int a = 0; //��������
    int b = 0; //��������
    ING(); //���������
    system("COLOR F0");//������ɫΪ�ף�����Ϊ��
    welcome_headline();//��ӡ��ӭ��
    system("cls");//�Բ��豣��ı�����������
    do
    {
        {
            system("cls"); //�Բ��豣��ı�����������
            score = your_NO = 0;//�÷�����
            Keep_go = 1;//��Ϸ��������
            win_number = WINNUMBER;//����ʵ�ֻ�ʤĿ��ĸı�
            for(i=0; i<11; i++)
                name[i] = '\0';//�洢����������ַ������ʼ��
            for(a = 0; a < N ; a++)
                for(b = 0; b < N ; b++)
                    Array_2048[a][b] = 0;//��άN��N�������ʼ��
        }
        system("COLOR F0");//������ɫΪ�ף�����Ϊ��
        print_paint1();//��ӡ2048ͼ��
        print_tips();//��ӡ��ʾָ��
        read_line(name,10); //�����û�������
        Make_new_number(NEWNUMBERPER); //���ɵ�һ�������
        do  //������Ϸ
        {
            {
                system("cls");//�Բ��豣��ı�����������
                system("COLOR F0");//������ɫΪ�ף�����Ϊ��
                print_paint2();//��̬��ӡ2048ͼ��
                printf( "\t\t\t\tHi, %3s!",name);//��ӡ�������
                printf("\n\n\t\tWelcome to 2048! ");//��ӡ��ӭ��
                printf("Your mission is to get the number %d!\n\n",(1<<win_number));//��ӡ��ʤĿ��
                Prinft_Array_2048();//��ӡ��������
            }
            {
                printf("Tips:m/M/5:display score rank\n\n");
                printf("\t\ts/S/2:go down\t\ta/A/4:go left\n\n");
                printf("\t\td/D/6:go right\t\tw/W/8:go up \n\n");
                printf("The highest score: %6ld\tYour score: %2ld\n\n",Highest_score,score);
                printf("Enter what your order:\n"); //��ӡ��ʾ���߼�¼�����
            }
            Enter=read();//�����ƶ�����
            {
                switch(Enter)//�ж�λ�Ʒ���λ�ƣ��ж�λ���Ƿ�ɹ���ʧ��Ҫ��������
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
                    prinft_scoretable();//��ӡ�÷ְ�
                    printf("Press any key to keep going\n");
                    scanf("%c",&key);
                    continue;
                    break;
                default :
                    continue;
                }
            }
            if(score>=Highest_score)
                Highest_score=score; //ˢ����߷�
            Make_scoretable(); //ˢ�����а�
            if((highest_number=test_highest())>=win_number) //�Ƿ�Ӯ�ˣ�ѯ���Ƿ����
            {
                win_number++;//��ʤĿ�귭��
                Prinft_Array_2048();//��ӡ��������
                printf("Press any key to continue, enter n/N to end:");
                do
                {
                    scanf("%c",&command);
                }
                while(command=='\n');//����n��N������Ϸ
                printf("\n");
                if(command=='n'||command=='N')break;
            }
            Keep_go = Make_new_number(NEWNUMBERPER); //�����µ��������ͬʱ���Ƿ����ɳɹ���¼��Keep_go��
            if(IS_died()) break; //�����жϣ������־ͽ�������
        }
        while(Keep_go);  //ʧ������
        Make_scoretable(); //ˢ�����а�
        {
            //Game Over�����֡���λ���㣩����ʾ��߷֣���ĳɼ�������ʱ����������ֱ�
            system("cls");
            system("COLOR F0");
            print_paint1();//��ӡ2048ͼ��
            printf("The highest score: %6ld\n",Highest_score);
            printf("Your score: %2ld\n",score);
            Prinft_Array_2048();//��ӡ��������
            printf("\t\t\tGame over!\n\n");
            prinft_scoretable();//��ӡ�÷ְ�
            printf("Play again? Press any key to end, enter y/Y to continue:");
        }
        do
        {
            scanf("%c",&command);
        }
        while(command=='\n');
        printf("\n");
    }
    while(command=='y'||command=='Y');  //�Ƿ�����
    return 0;
}

void ING(void) //������������������ӣ�
{
    srand((unsigned) time(NULL));
}

void welcome_headline(void)//��ӭ�б��ģ�⶯̬��ӡ
{
    char headline0[]="��Ϸ��ʼǰ������󻯴��ڣ�Ч�����ѣ�^.^��������밴�س�";
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
    printf("��Ϸװ���У����Ժ�\n");
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

void print_tips(void)//��ӡ��ʾָ��
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

int read_line (char str[],int n)//�����û�������
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

void print_paint1(void)//��̬��ӡ2048ͼ��
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

void print_paint2(void)//��̬��ӡ2048ͼ��
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

int Make_new_number(int n)//���������
{
    for(int L = 0; L < n ; L++)//��֤����NEWNUMBERPER �������
    {
        int a = 0;
        int b = 0;
        int i = 0;
        int empty_place = 0;
        int temp = 0;
        for(a = 0; a < N ; a++)
            for(b = 0; b < N ; b++)
                empty_place += !(Array_2048[a][b]);//���������жϿ�λ��
        if(empty_place == 0) return 0;//����λΪ���򷵻�0
        temp = rand()%empty_place+1;//����1~empty_place��Χ�ڵ������
        a = b = i = 0;
        while(1)//��������п�λ��ѡ��һ�����2��4
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
        Array_2048[a][b] = 2 << ((rand()%4)/3);//2�������0��1����2��4
    }
    return 1;
}

void line(int n)//��ӡ����
{
    for (int i = 0; i < abs(5-N); ++i)//��֤��񱣳־���
        printf("\t");
    for (int i = 0; i < N; ++i)
    {
        printf("--------");
    }
    printf("-");
    printf("\n");
}

void Prinft_Array_2048(void)//��ӡ��������
{
    for (int i = 0; i < N; ++i)
    {
        line(N);
        for (int k = 0; k <abs(5-N); ++k)//��֤��񱣳־���
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

int read(void)//�����ƶ�����
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

int GO_down(void)//�����ж�
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

int GO_up(void)//�����ж�
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

int GO_left(void)//�����ж�
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

int GO_right(void)//�����ж�
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

int test_highest(void)//��߷��ж�
{
    int a = 0;
    int b = 0;
    int i = 0;
    long highest = 0;
    for(a = 0; a < N ; a++)
    {
        for(b = 0; b < N ; b++)
            if((Array_2048[a][b])>=highest) highest=Array_2048[a][b];//��������ȷ���������
    }
    for(i=0; highest>1; i++)
        highest=highest>>1;//�ж�λ������WINNUMBER�Ƚ�
    return i;
}

void Make_scoretable(void)//�����÷ְ�
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
            //�����ǰ��ҵ÷ָ���ǰ��ҵ÷��򽻻���������
            I = highest_score[(your_NO+1)][1];
            highest_score[(your_NO+1)][1] = highest_score[your_NO][1];
            highest_score[your_NO][1] = I;//����highest_number
            I = highest_score[(your_NO+1)][0];
            highest_score[(your_NO+1)][0] = highest_score[your_NO][0];
            highest_score[your_NO][0] = I;//����score
            strcpy(L,highest_name[your_NO+1]);
            strcpy(highest_name[your_NO+1],highest_name[your_NO]);
            strcpy(highest_name[your_NO],L);//��������
            your_NO++;
        }
        else if((highest_score[your_NO][1]==highest_score[(your_NO+1)][1])&&
                (highest_score[your_NO][0]>highest_score[(your_NO+1)][0]))
        {
            I = highest_score[(your_NO+1)][1];
            highest_score[(your_NO+1)][1] = highest_score[your_NO][1];
            highest_score[your_NO][1] = I;//����highest_number
            I = highest_score[(your_NO+1)][0];
            highest_score[(your_NO+1)][0] = highest_score[your_NO][0];
            highest_score[your_NO][0] = I;//����score
            strcpy(L,highest_name[your_NO+1]);
            strcpy(highest_name[your_NO+1],highest_name[your_NO]);
            strcpy(highest_name[your_NO],L);//��������
            your_NO++;
        }
        else
            break;
    }
}

void prinft_scoretable(void)//��ӡ�÷ְ�
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

int IS_died(void)//�����жϣ������־ͽ�������
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
    return 1;//�жϸ��и����Ƿ����ܹ���ӵ����������򷵻���
}



