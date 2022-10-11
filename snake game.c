#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>


int width=20, height=20, gameOver;

int x, y, fruitX, fruitY;
int fruitX1, fruitY1;

int score=0, flag;

int tailX[100], tailY[100];
int tailX1[100], tailY1[100];

int CountTail=0, life=3;
int demolife;

bool specialFood = false;


struct coordinate
{
    int x;
    int y;
    int direction;
};

void setup()
{
    gameOver =0;
    x=width/2;
    y=height/2;

label1:
    fruitX=rand()%18;
    if (fruitX==0)
        goto label1;

label2:
    fruitY=rand()%18;
    if (fruitY==0)
        goto label2;

label3:
    fruitX1=rand()%18;
    if (fruitX1==0)
        goto label3;

label4:
    fruitY1=rand()%18;
    if (fruitY1==0)
        goto label4;
}

void Print()
{

    printf("\tWelcome to the BRAVE IMPACT GAME.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tTeam Members:\n");
    printf("1.Fazle Rabbi Spondon(190041211)\n");
    printf("2.Rifa Sanjita Lamia(190041231)\n");
    printf("3.Md.Ashikur Rahman(190041203)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use A/W/S/D keys to move the collector. You can also use I/O/L/K to move diagonally.\n\n-> You will be provided samples to collect at the several coordinates of the screen which you have to go through. Everytime you collect a sample the length of the bag will be increased by 1 element and thus the score.\n\n-> Here you are provided with three immunity power. Your immunity will decrease as you hit the wall or your own body.\n\n-> You can't pause the game in its middle by pressing any key. \n\n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}


void draw ()
{
    int i, j, k;
    system("cls");

    if(score%80 == 0 && score>=1)
    {
        specialFood = true;
    }

    else
    {
        specialFood = false;
    }

    for (i=0; i<width; i++)
    {
        for (j=0; j<height; j++)
        {
            if (i==0||i==height-1||j==0||j==width-1)
            {
                printf ("*");
            }

            else
            {
                if (i==x && j==y)
                    printf ("O");

                else if (i==fruitX && j == fruitY)
                {
                    if(specialFood==true)
                    {
                        printf("@");
                    }

                    else
                    {
                        printf("S");
                    }
                }

                else
                {
                    int ch=0;

                    for (k=0; k<CountTail; k++)
                    {
                        if (i==tailX[k] && j==tailY[k])
                        {
                            printf("o");
                            ch=1;
                        }
                    }

                    if (ch==0)
                        printf(" ");
                }
            }


        }

        printf("\n");
    }

    printf("SCORE=%d Immunity=%d", score, demolife);
}



void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            flag=1;
            break;
        case 'd':
            flag=2;
            break;
        case 'w':
            flag =3;
            break;
        case 's':
            flag =4;
            break;
        case 'l':
            flag = 5;
            break;
        case 'k':
            flag = 6;
            break;
        case 'i':
            flag = 7;
            break;
        case 'o':
            flag = 8;
            break;
        case 'x':
            gameOver=1;
            break;
        }
    }
}

void MakeLogic()
{
    int i;

    int prevX=tailX[0];
    int prevY=tailY[0];

    int prev2X, prev2Y;

    tailX[0]=x;
    tailY[0]=y;

    for (i=1; i<CountTail; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];

        tailX[i]=prevX;
        tailY[i]=prevY;

        prevX=prev2X;
        prevY=prev2Y;
    }

    int prevX1=tailX1[0];
    int prevY1=tailY1[0];

    int prev2X1, prev2Y1;

    tailX1[0]=x;
    tailY1[0]=y;

    for (i=1; i<CountTail; i++)
    {
        prev2X1=tailX1[i];
        prev2Y1=tailY1[i];

        tailX1[i]=prevX1;
        tailY1[i]=prevY1;

        prevX1=prev2X1;
        prevY1=prev2Y1;
    }

    switch(flag)
    {
    case 1:
        y--;
        break;
    case 2:
        y++;
        break;
    case 3:
        x--;
        break;
    case 4:
        x++;
        break;
    case 5:
        y++;
        x++;
        break;
    case 6:
        y--;
        x++;
        break;
    case 7:
        y--;
        x--;
        break;
    case 8:
        y++;
        x--;
        break;
    default:
        break;
    }

    if (x<=0||x>=width||y<=0||y>=height)
        gameOver=1;

    for (i=0; i<CountTail; i++)
    {
        if (x==tailX[i] && y==tailY[i])
            gameOver=1;
    }

    if(x==fruitX && y==fruitY)
    {
        if(specialFood)
        {
            score+=20;
            CountTail/=2;
        }

        else
        {
            score+=10;
        }

label5:
        fruitX=rand()%19;

        if (fruitX==0)
            goto label5;

label6:
        fruitY=rand()%19;

        if (fruitY==0)
            goto label6;

        CountTail++;
    }
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void load()
{
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++);
        printf("%c",177);
    }
    getch();
}

int Scoreonly()
{
    int result=score;
    system("cls");
    return result;

}


void record()
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);

    for(j=0; plname[j]!='\0'; j++)
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else
            nplname[j]=plname[j];
    }
    nplname[j]='\0';

    fprintf(info,"Player Name :%s\n",nplname);


    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));

    fprintf(info,"Score:%d\n",Scoreonly());
    fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}


int main ()
{
    demolife=life;
    Print();
    system("cls");
    load();


    char c;
    int m, n;

    for (int p=0; p<life; p++)
    {

        setup();
        while(!gameOver)
        {

            draw();
            input();
            MakeLogic();
            for (m=0; m<5000; m++)
            {
                for (n=0; n<10000; n++)
                {

                }
            }
        }
        demolife--;
        if(demolife==0)
        {
            system("cls");
            printf("All immunity used up\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
        }


    }



}

